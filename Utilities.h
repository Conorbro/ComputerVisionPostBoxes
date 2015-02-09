#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>
#include <iostream>
#include <iostream>
#define PI 3.14159265358979323846

using namespace std;
using namespace cv;

void analyseVideo( VideoCapture& surveillance_video, int starting_frame, bool clean_binary_images );
void detectEdges( Mat& image1);
void show_32bit_image( char* window_name, Mat& passed_image, double zero_maps_to=0.0, double passed_scale_factor=-1.0 );



