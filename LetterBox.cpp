#include "Utilities.h"
#include "opencv2/video/tracking.hpp"
#include <cxcore.hpp>

int letterBox0;
int letterBox1;
int letterBox2;
int letterBox3;
int letterBox4;
int letterBox5;

int TP = 0;	//True Positives
int TN = 0;	//True Negatives

int countWhitePixelsInBox(Mat &image, int rowMin, int rowMax, int colMin, int colMax){
	int white_pixels = 0;
	for(int col=colMin; col<colMax; col++){
			for(int row=rowMin; row<rowMax; row++){
			if(image.at<uchar>(row, col) == 255){
				white_pixels++;
			}
		}
	}
	return white_pixels;
}

bool checkMail(int currentPixels){

	if(currentPixels<160){
	TP++;
	return false;
	}
	TN++;
	return true;

}

void detectEdges( Mat& image1)
{

	Mat image1_gray, image2_gray, abs_gradient;
	cvtColor(image1, image1_gray, CV_BGR2GRAY);
	int contour_count = 0;
	
	//Compute Vertical Partial Derivative
	Mat vertical_partial_derivative;
	Sobel(image1_gray,vertical_partial_derivative,CV_32F,1,0);

	//Display the vertical partial derivative. (Essentially, displaying the vertical lines in the frame).
	show_32bit_image("Vertical Partial Derivative", vertical_partial_derivative);

	//Convert Vertical Partial Derivative from CV_32F to CV_8UC3 so we can count the white pixels
	Mat Temp;
	vertical_partial_derivative.convertTo(Temp, CV_8UC3);
	
	//Count White Pixels in Vertical Partial Derivative 
	 letterBox0  = countWhitePixelsInBox(Temp, 120, 142, 20, 105);
	 letterBox1	 =  countWhitePixelsInBox(Temp, 120, 142, 120, 200);
	 letterBox2  = countWhitePixelsInBox(Temp, 235, 260, 20, 105);
	 letterBox3  = countWhitePixelsInBox(Temp, 235, 260, 120, 200);
	 letterBox4  = countWhitePixelsInBox(Temp, 344, 372, 20, 105);
	 letterBox5  = countWhitePixelsInBox(Temp, 344, 372, 120, 200);

	//Printing out pixel counts for debugging & demonstration purposes
	cout << "White Pixels Letter Box 0 = " << letterBox0 << endl;
	cout << "White Pixels Letter Box 1 = " << letterBox1 << endl;
	cout << "White Pixels Letter Box 2 = " << letterBox2 << endl;
	cout << "White Pixels Letter Box 3 = " << letterBox3 << endl;
	cout << "White Pixels Letter Box 4 = " << letterBox4 << endl;
	cout << "White Pixels Letter Box 5 = " << letterBox5 << endl;
	cout << endl;


	//cout << "True Positives = " << TP;
	//cout << "True Negatives = " << TN;
	//cout << endl;

	if(!checkMail(letterBox0)){
		cout << "You've got mail in letter box 0" << endl;
		putText(image1, "MAIL", cvPoint(30,100), 
    FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);
	}
	if(!checkMail(letterBox1)){
		cout << "You've got mail in letter box 1" << endl;
		putText(image1, "MAIL", cvPoint(120,100), 
    FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);
	}
	if(!checkMail(letterBox2)){
		cout << "You've got mail in letter box 2" << endl;
		putText(image1, "MAIL", cvPoint(30,200), 
    FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);
	}
	if(!checkMail(letterBox3)){
		cout << "You've got mail in letter box 3" << endl;
		putText(image1, "MAIL", cvPoint(120,200), 
    FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);
	}
	if(!checkMail(letterBox4)){
		cout << "You've got mail in letter box 4" << endl;
		putText(image1, "MAIL", cvPoint(30,300), 
    FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);
	} 
	if(!checkMail(letterBox5)){
		cout << "You've got mail in letter box 5" << endl;
		putText(image1, "MAIL", cvPoint(120,300), 
    FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);
	}
	cout << endl;
	imshow("Live", image1);

}
