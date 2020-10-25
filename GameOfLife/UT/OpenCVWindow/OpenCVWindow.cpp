#include <iostream>
#include <unistd.h>
#include <OpenCVWindow/OpenCVWindow.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

#define WINDOW_NAME "GameOfLife"
#define SCALE 20

using namespace std;
using namespace cv;

static CellMap* mouse_callback_GameOfLife=nullptr;

void mouse_callback(int  event, int  x, int  y, int  flag, void *param)
{
	if (mouse_callback_GameOfLife == nullptr) return;

	x /= SCALE;
	y /= SCALE;

	if (event == EVENT_LBUTTONDBLCLK) {
		cout << "MakeCellAlive : " << x << " " << y << endl;
		mouse_callback_GameOfLife->MakeCellAlive(x,y);
	}

	if (event == EVENT_RBUTTONDBLCLK) {
		cout << "MakeCellDie : " << x << " " << y << endl;
		mouse_callback_GameOfLife->MakeCellDie(x,y);
	}
}

Mat ConvertToImage(CellMap* GameOfLife,CellMapFactoryConfig& config) {

	int nx,ny;
	nx=config.width;
	ny=config.height;

	cv::Mat img(ny,nx,CV_8UC3,cv::Scalar(0,0,0));

	for (int j = 0; j < ny; j++) {
		for (int i = 0; i < nx; i++) {
			int ir,ig,ib;
			ir = ig = ib = 255*GameOfLife->GetCell(i,j);

			img.at<cv::Vec3b>(j,i)[0] = ib;/*B*/
			img.at<cv::Vec3b>(j,i)[1] = ig;/*G*/
			img.at<cv::Vec3b>(j,i)[2] = ir;/*R*/
		}
	}

	return img;

}


void OpenCVWindow(CellMap* GameOfLife,CellMapFactoryConfig& config) {

	Mat img1(config.width,config.height,CV_8UC3,cv::Scalar(0,0,0));
	Mat img2(config.width*SCALE,config.height*SCALE,CV_8UC3,cv::Scalar(0,0,0));


	img1 = ConvertToImage(GameOfLife,config);

	resize(img1,img2,img2.size(),0,0,INTER_NEAREST);
	imshow( WINDOW_NAME, img2 );

	waitKey(1);

	sleep(1);
}

void OpenCVWindowInit(CellMap* GameOfLife,CellMapFactoryConfig& config) {
	mouse_callback_GameOfLife=GameOfLife;
	namedWindow( WINDOW_NAME, WINDOW_AUTOSIZE );
	setMouseCallback(WINDOW_NAME, mouse_callback);
}