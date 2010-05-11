

/* opencv */
//#include <cv.h>

//#include <image_processing.h>

#include "image_processing.h"


CImageProcessor::CImageProcessor() {
	m_tmp_img_data=new char[3*OSC_CAM_MAX_IMAGE_HEIGHT*OSC_CAM_MAX_IMAGE_WIDTH 
			+ PICTURE_ALIGNMENT];
	m_tmp_img=(char*)CCamera::AlignPicture((uint8*)m_tmp_img_data);
	
}

CImageProcessor::~CImageProcessor() {
	delete[](m_tmp_img_data);
}

int CImageProcessor::DoProcess(IplImage** image) {
	
	if(!image || !*image) return(EINVALID_PARAMETER);
	
	IplImage* img=*image;

	//do something with img
	
	
	
	return(SUCCESS);
}









