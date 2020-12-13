#include <iostream>
#include <vector>
#include <list>
#include <unistd.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <Display.hpp>

#define WINDOW_NAME "Flocking"
#define SCALE 10

using namespace std;
using namespace cv;

static Flock* flock;
static Mat img1;
static Mat img2;

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

	int nx,ny;

	nx=width;
	ny=height;

	cv::Mat img(ny,nx,CV_8UC3,cv::Scalar(0,0,0));

	for ( auto boid : flock->GetBoids() ) {

			int ir,ig,ib;
			int i,j;

			glm::vec2 positon = boid.GetPosition();
			i = positon.x;
			j = positon.y;

			ir = ig = ib = 255;

			img.at<cv::Vec3b>(j,i)[0] = ib;/*B*/
			img.at<cv::Vec3b>(j,i)[1] = ig;/*G*/
			img.at<cv::Vec3b>(j,i)[2] = ir;/*R*/
	}

	return img;


}

void OpenCVWindow() {

	img1 = GetImage();

	resize(img1,img2,img2.size(),0,0,INTER_NEAREST);
	imshow( WINDOW_NAME, img2 );

	int k = waitKey(1);
	key_callback(k);

}

void OpenCVWindowInit(Flock& f) {

	width = f.GetWidth();
	height = f.GetHeight();

	flock = &f;

	img1 = Mat(height,width,CV_8UC3,cv::Scalar(0,0,0));
	img2 = Mat(height*SCALE,width*SCALE,CV_8UC3,cv::Scalar(0,0,0));

	namedWindow( WINDOW_NAME, WINDOW_AUTOSIZE );
	setMouseCallback(WINDOW_NAME, mouse_callback);
}