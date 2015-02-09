#include "Utilities.h"

Mat current_frame;

int main(int argc, const char** argv)
{
	//Set file location for video
	char* file_location = "Media/";

	// Load video(s)
	char* video_files[] = { 
		"Postboxes.avi"
		 };
	int number_of_videos = sizeof(video_files)/sizeof(video_files[0]);
	VideoCapture* video = new VideoCapture[number_of_videos];
	for (int video_file_no=0; (video_file_no < number_of_videos); video_file_no++)
	{
		string filename(file_location);
		filename.append(video_files[video_file_no]);
		video[video_file_no].open(filename);
		if( !video[video_file_no].isOpened() )
		{
			cout << "Cannot open video file: " << filename << endl;
			return -1;
		}
	}

	//Run Program
	analyseVideo(video[0],0,true);
	

}
