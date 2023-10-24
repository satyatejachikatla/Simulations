#include <iostream>
#include <vector>
#include <list>
#include <unistd.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <Display/Display.hpp>

#define WINDOW_NAME "Pattern"

using namespace std;
using namespace cv;

static Mat img1;
static Mat img2;
static Grid* grid = nullptr;
static int width;
static int height;

struct color{
	double r;
	double g;
	double b;
};

color getColor(double x){
	if(x < 0)
		x = 0.;
	if (x > 1)
		x = 1.;
	return {x,x,x};
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
	for (int j=0;j<height;j++) {
		for (int i = 0; i < width; i++) {
			color col = getColor(grid->getPixel(i,j));

			img1.at<cv::Vec3b>(j,i)[0] = col.b*255;/*B*/
			img1.at<cv::Vec3b>(j,i)[1] = col.g*255;/*G*/
			img1.at<cv::Vec3b>(j,i)[2] = col.r*255;/*R*/
		}
	}

	resize(img1,img2,img2.size(),0,0,INTER_NEAREST);
}

void OpenCVWindow(){
	GetImage();
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