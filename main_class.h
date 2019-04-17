/*! @file main_class.h
 * @brief Main Class with the main loop
 */

#ifndef MAIN_CLASS_H_
#define MAIN_CLASS_H_

#include "includes.h"
#include "camera.h"
#include "image_processing.h"


#define TEST_IMAGE_FN "test.bmp"


/*********************************************************************//*!
 * @brief class CMain. 
 * 	Contains the Main Loop and initializes everything that is needed
 * 
 *//*********************************************************************/

class CMain {
public:
	CMain();
	~CMain();
	
	OSC_ERR Init(int argc, char ** argv);
	
	OSC_ERR MainLoop();
	
private:
	CCamera m_camera;
	CImageProcessor m_img_process;
};

#endif /* MAIN_CLASS_H_ */
