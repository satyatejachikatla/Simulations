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
	if( key == 'q') {
		exit(EXIT_SUCCESS);
	}
}

Mat GetImage() {

	Mat img(height,width,CV_8UC3,cv::Scalar(0,0,0));
	const std::vector<vec3>& img_vec = config.universe_obj->getImage();

	unsigned int nx=config.width;
	unsigned int ny=config.height;

	for (int j = ny-1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			size_t pixel_index = j*nx + i;
			int ir = int(255.99*img_vec[pixel_index].r());
			int ig = int(255.99*img_vec[pixel_index].g());
			int ib = int(255.99*img_vec[pixel_index].b());
			
			ir = (ir > 255 ? 255 : ir) < 0 ? 0 : ir;
			ig = (ig > 255 ? 255 : ig) < 0 ? 0 : ig;
			ib = (ib > 255 ? 255 : ib) < 0 ? 0 : ib;

			img.at<cv::Vec3b>(ny-j-1,i)[0] = ib;/*B*/
			img.at<cv::Vec3b>(ny-j-1,i)[1] = ig;/*G*/
			img.at<cv::Vec3b>(ny-j-1,i)[2] = ir;/*R*/
		}
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

void OpenCVWindowInit(DisplayConfig& c) {

	config = c;
	width = c.width;
	height = c.height;

	img1 = Mat(width,height,CV_8UC3,cv::Scalar(0,0,0));
	img2 = Mat(width*SCALE,height*SCALE,CV_8UC3,cv::Scalar(0,0,0));

	namedWindow( WINDOW_NAME, WINDOW_AUTOSIZE );
	setMouseCallback(WINDOW_NAME, mouse_callback);
}