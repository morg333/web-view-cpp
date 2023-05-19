

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












/*********************************************************************************************************
 * 	
 *  	TESTAT - EBV - FS23
 *  	BY ODERMATT MARCO
 * 	
 * 		DOES DO THINGS WITH IMAGES
 * 		BINNING AND STUFF OFC.
 * 		
 * 
*********************************************************************************************************/


int CImageProcessor::DoProcess(cv::Mat* image) {
	//check for error
	if(!image) return(EINVALID_PARAMETER);	


// ---------------------------
// ---- Prepare Data ---------
// ---------------------------
	cv::Mat grayImage;
	cv::Mat colorImage;

	// make a grayscale image regardless of the image
	if(image->channels() > 1) {
		cv::cvtColor(*image, grayImage, cv::COLOR_RGB2GRAY);	//if color image, convert to grayscale img
		colorImage = image->clone();
	}
	else {
		grayImage = *image;
		cv::cvtColor(*image, colorImage, cv::COLOR_GRAY2RGB);
	}


// ---------------------------
// ---- Init -----------------
// ---------------------------
	//because if defined in IF statement, it might not have been called before...
	//init for binary Image
	cv::Mat binaryImage;
	//init for region Labeling
	cv::Mat labelImage;
	//init for bounding box image
	cv::Mat resultImage = grayImage.clone();


// ---------------------------
// ---- Do the Processing ----
// ---------------------------
	if(mPrevImage.size() != cv::Size())	//is data fine? has it allready passed once?$
	{
		// -- do all the processing in here --

	// ---- processXY ----
		

	// ---- processXY ----
		



	// ---- processXY ----
		


	}	
	else	//if the first time
	{
		//#todo output a black image for the output if it was the first time
		//diffImage = grayImage * 0;		//output at least a black image with correct pixel dimensions
	}

// ---------------------------
// ---- Age and save ---------
// ---------------------------
	mPrevImage = grayImage.clone();		//generate image for next round

// ---------------------------
// ---- Output ---------------
// ---------------------------
	*m_proc_image[0] = labelImage;
	*m_proc_image[1] = mBkgrImage;
	*m_proc_image[2] = resultImage;
















		//#todo finishing touches
		//modify diff image so noise is not present
		//diffImage.at<uint8>(0,0)=255;		//set one pixel to max value
		//diffImage.at<uint8>(1,0)=0;			//set one pixel to min value

	// ---- 3) Visualisierung übungen ---
		//*m_proc_image[0] = labelImage;
		//*m_proc_image[1] = binaryImage;
		//*m_proc_image[2] = resultImage;

















		/*		UNUSED CODE

		#define USE_SIMPLECONTOUR (1)
		// ---- Testat gedöns ----
#if (USE_SIMPLECONTOUR)
			double alpha = 0.9;
			cv::addWeighted(mBkgrImage, alpha, grayImage, 1-alpha, 0, mBkgrImage);
#else
			double alpha = 0.9;
			for(unsigned int idx = 0 ; idx < contours.size(); idx++ ) {
				//area
				double area = cv::contourArea(contours[idx]);
				//bounding rectangle
				cv::Rect rect = cv::boundingRect(contours[idx]);
				//center of gravity
				// center of mass
				cv::Moments moment = cv::moments(contours[idx]);
				double cx = moment.m10 / moment.m00;
				double cy = moment.m01 / moment.m00;
				//to draw counter to index idx in image
				cv::drawContours(resultImage, contours, idx, cv::Scalar(255), 1, 8 );
			}
#endif



// code for Processinc

		// ---- a) Difference Image ----
			cv::Mat diffImage;
			cv::absdiff(grayImage, mPrevImage, diffImage);

		// ---- b) Binarisierung ----
			double threshold = 50;
			cv::threshold(diffImage, binaryImage, threshold, 255, cv::THRESH_BINARY);

		// ---- c) Morphologie ----
			cv::Mat kernel = cv::Mat::ones(5, 5, CV_8UC1);
			cv::morphologyEx(binaryImage, binaryImage, cv::MORPH_CLOSE, kernel);

		// ---- d) Region Labeling ----
			cv::Mat stats, centroids;
			connectedComponentsWithStats(binaryImage, labelImage, stats, centroids);

			//access values from Labeled Images data
			for (int i = 1; i < stats.rows; i++) {
			int topLeftx = stats.at<int>(i, 0);
			int topLefty = stats.at<int>(i, 1);
			int width = stats.at<int>(i, 2);
			int height = stats.at<int>(i, 3);
			int area = stats.at<int>(i, 4);
			double cx = centroids.at<double>(i, 0);
			double cy = centroids.at<double>(i, 1);

			//draw bounding box over image copy
			cv::Rect rect(topLeftx, topLefty, width, height);
			cv::rectangle(resultImage, rect, cv::Scalar(255, 0, 0));
			//draw centerPoint onto image
			cv::Point2d cent(cx, cy);
			cv::circle(resultImage, cent, 5, cv::Scalar(128, 0, 0), -1);
			}	//end Labeling

*/





	return(SUCCESS);
}









