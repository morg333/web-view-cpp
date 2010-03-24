/*! @file camera.h
 * @brief Camera Class
 *  All Pictures are aligned to PICTURE_ALIGNMENT
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <leancv.h>

#include "includes.h"


/* @brief struct ROI. Region of Interest, default values are for the whole picture */
struct ROI {
	ROI(uint16 low_x=0, uint16 low_y=0, uint16 width=OSC_CAM_MAX_IMAGE_WIDTH, uint16 height=OSC_CAM_MAX_IMAGE_HEIGHT)
		: low_x(low_x), low_y(low_y), width(width), height(height) {}
	
	uint16 low_x;
	uint16 low_y;
	uint16 width;
	uint16 height;
};


enum ColorType {
	ColorType_none, // No valid image yet
	ColorType_gray, // Image from a grayscale sensor
	ColorType_raw, // Raw image from a color sensor
	ColorType_debayered // Debayered image from a color sensor
};

#define PICTURE_ALIGNMENT LCV_IMG_ALIGN



class CCamera {
public:
	CCamera();
	~CCamera();
	
	/*! @brief Initializes the camera module 
	 * NOTE: Oscar Framework must be initialized before this call!
	 */
	OSC_ERR Init(const ROI& region_of_interest, uint8 buffer_count=2
			, EnOscCamPerspective perspective=OSC_CAM_PERSPECTIVE_DEFAULT);
	
	
	
	/*! @brief get the latest picture and do debayering if needed 
	 * returns the image or NULL on error
	 * Picture is aligned to PICTURE_ALIGNMENT
	 */
	IplImage* ReadLatestPicture();
	
	
	/*! @brief Read the current captured picture.
	 *  like ReadLatestPicture, but waits for image to be captured
	 *  call CapturePicture and ReadPicture if you want the most actual picture
	 */
	IplImage* ReadPicture(uint16 max_age=0, uint16 timeout=0);
	
	
	/*! @brief setup a capture an return immediately */
	OSC_ERR CapturePicture();
	
	
	/*! @brief get region of interest */
	const ROI& getROI() const { return(m_roi); }
	
	void setROI(const ROI& new_roi) { 
		m_roi=new_roi; m_bRoi_changed=true; 
		OscCamSetAreaOfInterest(m_roi.low_x, m_roi.low_y, m_roi.width, m_roi.height);
	}
	
	
	ColorType getColorType() { return(m_color_type); }
	void setColorType(ColorType type) { m_color_type=type; }
	/*! @brief getAppropriateColorType: returns color type depending on hardware: either gray or color */
	ColorType getAppropriateColorType();
	
	
	EnOscCamPerspective getPerspective() { return(m_perspective); }
	void setPerspective(EnOscCamPerspective perspective) { 
		m_perspective=perspective;
		OscCamSetupPerspective(m_perspective);
	}
	
	
	/*! @brief Align an image pointer to a multiple of PICTURE_ALIGNMENT
	 * IMPORTANT: make sure, pic is PICTURE_ALIGNMENT bytes larger than needed!
	 * Note: OpenCV needs aligned pictures 
	 */
	static uint8* AlignPicture(const uint8* pic);
	static uint32 AlignSize(uint32 size);
	
private:
	IplImage* HandlePictureColoringAndSize(uint8* pic_data);
	/* set new imageheader if channel_count is not the same or size is not same as from camera */
	void AdjustImageHeader(IplImage** img, int channel_count);
	IplImage* m_img;
	
	uint8* m_img_data;
	uint8* m_al_img_data; /*! @brief aligned pointer to m_img_data */
	
	uint8* m_frame_buffer_ids;
	uint8_t* m_frame_buffers;
	ROI m_roi;
	bool m_bRoi_changed; /* if true, m_img header must be reinitialized */
	
	int m_buffer_count;
	ColorType m_color_type;
	EnOscCamPerspective m_perspective;
};


#endif /* CAMERA_H_ */
