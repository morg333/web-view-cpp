

#include "image_processing.h"


CImageProcessor::CImageProcessor() {
	for(uint32 i=0; i<3; i++) {
		/* index 0 is 3 channels and indicies 1/2 are 1 channel deep */
		m_proc_image[i] = new cv::Mat();
	}
}

CImageProcessor::~CImageProcessor() {
	for(uint32 i=0; i<3; i++) {
		delete m_proc_image[i];
	}
}

cv::Mat* CImageProcessor::GetProcImage(uint32 i) {
	if(2 < i) {
		i = 2;
	}
	return m_proc_image[i];
}

int CImageProcessor::DoProcess(cv::Mat* image) {

	cv::Mat grayImage;
	
	if(!image) return(EINVALID_PARAMETER);	
        
		//	make gray	

        if(image->channels()>1) {
			cv::cvtColor(*image, grayImage, cv::COLOR_RGB2GRAY);	//if color image, convert to grayscale img
		}
		else {
			grayImage = *image;
		}



		cv::Mat diffImage;
		cv::Mat mask;

		if (mPrevImage.size() != cv::Size())	//is data fine? has it allready passed once
		{
			//mPrevImage = grayImage;
			//mPrevImage *= 0;
			//mPrevImage += (0.5 * 128);

			cv::absdiff(mPrevImage, *image, diffImage);	//create difference between this and last image
			//diffImage = cv::abs(mPrevImage - *image);	//same procut, just slightly different code

			cv::abs(diffImage);
			


			//modify diff image so noise is not present
			diffImage.at<uint8>(0,0)=255;		//set one pixel to max value
			diffImage.at<uint8>(1,0)=0;			//set one pixel to min value
		}
		else
		{
			diffImage = *image * 0;		//output at least a black image with correct pixel dimensions
		}

		mPrevImage = grayImage.clone();		//generate image for next round






        cv::subtract(cv::Scalar::all(255), *image,*m_proc_image[0]);
		*m_proc_image[1] = grayImage;
		*m_proc_image[2] = diffImage;
		


        
		// use *m_proc_image[ ... ] 0 up to 2 for output image
      //  cv::imwrite("dx.png", *m_proc_image[0]);
      //  cv::imwrite("dy.png", *m_proc_image[1]);

	return(SUCCESS);
}









