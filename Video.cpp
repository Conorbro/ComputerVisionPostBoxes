#include "Utilities.h"
#include "opencv2/video/tracking.hpp"
#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write

void detectMovement(Mat current_frame, Mat foreground_mask){

		int count_white = countNonZero(foreground_mask > 110);				//Count White pixels greater than the set threshold
		if(count_white < 20000){											//If not moving - check post
			cout << "STILL FRAME DETECTED - CHECKING FOR POST..." << endl;
			cout << endl;
			detectEdges(current_frame);
		}
		else {cout << "MOVING FRAME DETECTED - SKIPPING..." << endl;		//Else - ignore current frame as movement detected
		cout << endl;
		}

}

void analyseVideo( VideoCapture& surveillance_video, int starting_frame, bool clean_binary_images )
{
	
    Mat current_frame, thresholded_image;
	surveillance_video.set(CV_CAP_PROP_POS_FRAMES,starting_frame);
	surveillance_video >> current_frame;
	BackgroundSubtractorMOG2 gmm; 
	Mat foreground_mask;

	double frame_rate = surveillance_video.get(CV_CAP_PROP_FPS);
	double time_between_frames = 1000.0/frame_rate;
	while (!current_frame.empty())
    {
 		double duration = static_cast<double>(getTickCount());
	
		// Update the Gaussian Mixture Model
        gmm(current_frame, foreground_mask);
		// Clean the resultant binary (moving pixel) mask using an opening.
		threshold(foreground_mask,thresholded_image,150,255,THRESH_BINARY);

		// Create an average background image (just for information)
        Mat mean_background_image;
        gmm.getBackgroundImage(mean_background_image);

		imshow("GMM Moving", foreground_mask);

		//Check for movement between frames
		detectMovement(current_frame, foreground_mask);

		//Delay before moving onto next frame
		duration = static_cast<double>(getTickCount())-duration;
		duration /= getTickFrequency()/1000.0;
		int delay = (time_between_frames>duration) ? (time_between_frames-duration) : 1;
		char c = cvWaitKey(delay);
		
	 	surveillance_video >> current_frame;
	}
}


