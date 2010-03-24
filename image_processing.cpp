
//#include <image_processing.h>

/* opencv */
//#include <cv.h>


#include "image_processing.h"




CImageProcesser::CImageProcesser() {
	m_tmp_img_data=new char[3*OSC_CAM_MAX_IMAGE_HEIGHT*OSC_CAM_MAX_IMAGE_WIDTH 
			+ PICTURE_ALIGNMENT];
	m_tmp_img=(char*)CCamera::AlignPicture((uint8*)m_tmp_img_data);
}

CImageProcesser::~CImageProcesser() {	
	delete[](m_tmp_img_data);
}

int CImageProcesser::DoProcess(IplImage* img) {
	
	if(!img) return(EINVALID_PARAMETER);
	
	/*
	imgSobel((unsigned char*)img->imageData, img->height, img->width
			, (unsigned char*)m_tmp_img, 200);
	
	for(int i=0; i<img->imageSize; ++i) {
		img->imageData[i] = (char)(m_tmp_img[i] > 0 ? 255 : 0);
	}*/
	
	
	return(SUCCESS);
	
	/*
	IplImage* pImg_dst=lcvCreateImageHeader(cvSize(img->width, img->height), img->depth, img->nChannels);
	pImg_dst->imageDataOrigin=pImg_dst->imageData=(char*)m_tmp_img;
	
	
	cvCanny(img, pImg_dst, 50, 100);
	//cvCornerHarris(pImg, pImg_dst, 5); // <- fp
	
	//cvLaplace(pImg, pImg_dst, 1);
	//cvSobel(pImg, pImg_dst, 1, 0);  //pImg_dst must be IPL_DEPTH_16S
	
	//cvConvertScaleAbs(pImg_dst, pImg);
	memcpy(img->imageData, pImg_dst->imageData, img->imageSize);
	
	lcvReleaseImageHeader(&pImg_dst);
	*/
	
	return(SUCCESS);
}









