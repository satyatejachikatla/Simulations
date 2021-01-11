#include <iostream>
#include <vector>
#include <list>
#include <unistd.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <Display.cuh>

#define WINDOW_NAME "BlackHole"
#define SCALE 10

using namespace std;
using namespace cv;

static Mat img1;
static Mat img2;

static int width;
static int height;

static DisplayConfig config;

void mouse_callback(int  event, int  x, int  y, int  flag, void *param) {
	x /= SCALE;
	y /= SCALE;
}

void key_callback(int  key) {

}

Mat GetImage() {

	Mat img(height,width,CV_8UC3,cv::Scalar(0,0,0));

	return img;

}

void OpenCVWindow() {

	img1 = GetImage();

	resize(img1,img2,img2.size(),0,0,INTER_NEAREST);
	imshow( WINDOW_NAME, img2 );

	int k = waitKey(1);
	key_callback(k);

}

void OpenCVWindowInit(DisplayConfig& c) {

	config = c;
	width = c.width;
	height = c.height;

	img1 = Mat(width,height,CV_8UC3,cv::Scalar(0,0,0));
	img2 = Mat(width*SCALE,height*SCALE,CV_8UC3,cv::Scalar(0,0,0));

	namedWindow( WINDOW_NAME, WINDOW_AUTOSIZE );
	setMouseCallback(WINDOW_NAME, mouse_callback);
}