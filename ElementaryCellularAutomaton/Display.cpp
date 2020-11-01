#include <iostream>
#include <vector>
#include <list>
#include <unistd.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <Display.hpp>

#define WINDOW_NAME "Wolfman"
#define SCALE 10

using namespace std;
using namespace cv;

static Mat img1;
static Mat img2;
static list< vector<bool> > img_v;
static int width;
static int height;

void mouse_callback(int  event, int  x, int  y, int  flag, void *param)
{
	x /= SCALE;
	y /= SCALE;
}

void key_callback(int  key)
{
}

Mat GetImage() {

	Mat img(height,width,CV_8UC3,cv::Scalar(0,0,0));
	int j=0;
	for (list< vector<bool> >::iterator it=img_v.begin(); it != img_v.end(); it++,j++) {
		for (int i = 0; i < it->size(); i++) {
			int ir,ig,ib;
			ir = ig = ib = 255*it->at(i);

			img.at<cv::Vec3b>(j,i)[0] = ib;/*B*/
			img.at<cv::Vec3b>(j,i)[1] = ig;/*G*/
			img.at<cv::Vec3b>(j,i)[2] = ir;/*R*/
		}
	}

	return img;

}

void OpenCVWindow(vector<bool>& v) {

	img_v.pop_front();
	img_v.push_back(v);

	img1 = GetImage();

	resize(img1,img2,img2.size(),0,0,INTER_NEAREST);
	imshow( WINDOW_NAME, img2 );

	int k = waitKey(1);
	key_callback(k);

}

void OpenCVWindowInit(int w,int h) {

	width = w;
	height = h;

	img1 = Mat(width,height,CV_8UC3,cv::Scalar(0,0,0));
	img2 = Mat(width*SCALE,height*SCALE,CV_8UC3,cv::Scalar(0,0,0));

	for(int i=0;i<h;i++) img_v.push_back(vector<bool>(w,0));

	namedWindow( WINDOW_NAME, WINDOW_AUTOSIZE );
	setMouseCallback(WINDOW_NAME, mouse_callback);
}