

/* opencv */
//#include <cv.h>

//#include <image_processing.h>

#include "image_processing.h"


CImageProcessor::CImageProcessor() {
	m_tmp_img_data=new char[3*OSC_CAM_MAX_IMAGE_HEIGHT*OSC_CAM_MAX_IMAGE_WIDTH 
			+ PICTURE_ALIGNMENT];
	m_tmp_img=(char*)CCamera::AlignPicture((uint8*)m_tmp_img_data);
	
	for(uint32 i=0; i<3; i++) {
		/* index 0 is 3 channels and indicies 1/2 are 1 channel deep */
		m_proc_image[i] = lcvCreateImage( cvSize( OSC_CAM_MAX_IMAGE_WIDTH, OSC_CAM_MAX_IMAGE_HEIGHT ), IPL_DEPTH_8U, (i == 0) ? 3 : 1 );
	}
}

CImageProcessor::~CImageProcessor() {
	delete[](m_tmp_img_data);

	for(uint32 i=0; i<3; i++) {
		lcvReleaseImage(&m_proc_image[i]);
	}
}

IplImage* CImageProcessor::GetProcImage(uint32 i) {
	if(2 < i) {
		i = 2;
	}
	return m_proc_image[i];
}

int CImageProcessor::DoProcess(IplImage** image) {
	
	if(!image || !*image) return(EINVALID_PARAMETER);
	
	IplImage* img=*image;


	if(img->nChannels == 1) {
		uint8* in = (uint8*) img->imageData;
		uint8* out = (uint8*) m_proc_image[0]->imageData;

		/* create 3 channel image with blue channel enhanced in m_proc_image[0] */
		for(int32 y = 0; y < img->height*img->width; y+=img->width) {
				for(int32 x = 0; x < img->width; x++) {
					for(int32 c = 0; c < m_proc_image[0]->nChannels; c++) {
						out[(y+x)*m_proc_image[0]->nChannels+c] = (c == 0) ? in[y+x] : (in[y+x] >> 2);
					}
				}
		}

		/* simple copy to m_proc_image[0] */
		memcpy(m_proc_image[1]->imageData, img->imageData, img->imageSize);

	} else {
		/* simple copy to m_proc_image[0] */
		memcpy(m_proc_image[0]->imageData, img->imageData, img->imageSize);

		uint8* in = (uint8*) img->imageData;
		uint8* out = (uint8*) m_proc_image[1]->imageData;
		/* create a b/w image in m_proc_image[1] */
		for(int32 y = 0; y < img->height*img->width; y+=img->width) {
				for(int32 x = 0; x < img->width; x++) {
					double R = in[img->nChannels*(y+x) + 0];
					double G = in[img->nChannels*(y+x) + 1];
					double B = in[img->nChannels*(y+x) + 2];

					out[y+x] = (uint8) (0.299 * R + 0.587 * G + 0.114 * B);
				}
		}
	}

	//lcvBmpWrite(img, "img.bmp");
	//lcvBmpWrite(img_bin, "img_bin.bmp");
	
	return(SUCCESS);
}









