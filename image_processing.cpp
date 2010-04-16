

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

int CImageProcesser::DoProcess(IplImage** image) {
	
	if(!image || !*image) return(EINVALID_PARAMETER);
	
	
	
	return(SUCCESS);
}









