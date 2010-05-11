/*! @file image_processing.h
 * @brief Image Manipulation class
 */

#ifndef IMAGE_PROCESSING_H_
#define IMAGE_PROCESSING_H_

#include <leancv.h>

#include "includes.h"
#include "camera.h"



class CImageProcessor {
public:
	CImageProcessor();
	~CImageProcessor();
	
	int DoProcess(IplImage** image);
private:
	char* m_tmp_img_data;
	char* m_tmp_img;
	
};


#endif /* IMAGE_PROCESSING_H_ */
