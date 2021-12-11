#include <iostream>
#include <vector>
#include <list>
#include <unistd.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <Display/Display.hpp>

#define WINDOW_NAME "StitchPattern"

using namespace std;
using namespace cv;

static Mat img1;
static Mat img2;
static Grid* grid = nullptr;
static int width;
static int height;

struct color{
	int r;
	int g;
	int b;
};

color getColor(int x){
	x = x%8;
	switch(x){
	case 0:
		return {1,0,0};
	case 1:
		return {0,1,0};
	case 2:
		return {0,0,1};
	case 3:
		return {1,1,0};
	case 4:
		return {1,0,1};
	case 5:
		return {0,1,1};
	case 6:
		return {1,1,1};
	case 7:
		return {0,0,0};
	}
	return {0,0,0};
}

void mouse_callback(int  event, int  x, int  y, int  flag, void *param)
{
	x /= SCALE;
	y /= SCALE;
}

void key_callback(int  key)
{
}

void GetImage() {

	int j=0;
	for (int j=0;j<width;j++) {
		for (int i = 0; i < height; i++) {
			color col = getColor(grid->getPixel(j,i));

			img1.at<cv::Vec3b>(j,i)[0] = col.b*255;/*B*/
			img1.at<cv::Vec3b>(j,i)[1] = col.g*255;/*G*/
			img1.at<cv::Vec3b>(j,i)[2] = col.r*255;/*R*/
		}
	}
}

void OpenCVWindow(){
	GetImage();

	resize(img1,img2,img2.size(),0,0,INTER_NEAREST);
	imshow( WINDOW_NAME, img2 );

	int k = waitKey(1);
	key_callback(k);

}

void OpenCVWindowInit(Grid* g) {
	grid = g;

	width = grid->getWidth();
	height = grid->getHeight();

	img1 = Mat(width,height,CV_8UC3,cv::Scalar(0,0,0));
	img2 = Mat(width*SCALE,height*SCALE,CV_8UC3,cv::Scalar(0,0,0));

	namedWindow( WINDOW_NAME, WINDOW_AUTOSIZE );
	setMouseCallback(WINDOW_NAME, mouse_callback);
}