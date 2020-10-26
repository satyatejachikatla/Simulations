#include <iostream>
#include <unistd.h>
#include <OpenCVWindow/OpenCVWindow.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

#define WINDOW_NAME "GameOfLife"
#define CONSIDER_STEP_DEFAULT true
#define SCALE 1

using namespace std;
using namespace cv;

static CellMap* callback_GameOfLife=nullptr;
static bool consider_step=CONSIDER_STEP_DEFAULT;

void mouse_callback(int  event, int  x, int  y, int  flag, void *param)
{
	if (callback_GameOfLife == nullptr) return;

	x /= SCALE;
	y /= SCALE;

	if (event == EVENT_LBUTTONDBLCLK) {
		cout << "MakeCellAlive : " << x << " " << y << endl;
		callback_GameOfLife->MakeCellAlive(x,y);
	}

	if (event == EVENT_RBUTTONDBLCLK) {
		cout << "MakeCellDie : " << x << " " << y << endl;
		callback_GameOfLife->MakeCellDie(x,y);
	}
}

void key_callback(int  key)
{
	if (callback_GameOfLife == nullptr) return;

	if (key == ' ') {
		//cout << "Taking Step" << endl;
		consider_step=true;
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


void OpenCVWindow(CellMap* GameOfLife,CellMapFactoryConfig& config,int step) {

	if(!consider_step) step=0; 
	consider_step=CONSIDER_STEP_DEFAULT;

	GameOfLife->Step(step);

	Mat img1(config.width,config.height,CV_8UC3,cv::Scalar(0,0,0));
	Mat img2(config.width*SCALE,config.height*SCALE,CV_8UC3,cv::Scalar(0,0,0));


	img1 = ConvertToImage(GameOfLife,config);

	resize(img1,img2,img2.size(),0,0,INTER_NEAREST);
	imshow( WINDOW_NAME, img2 );

	int k = waitKey(1);
	key_callback(k);

	usleep(1000);
}

void OpenCVWindowInit(CellMap* GameOfLife,CellMapFactoryConfig& config) {
	callback_GameOfLife=GameOfLife;
	namedWindow( WINDOW_NAME, WINDOW_AUTOSIZE );
	setMouseCallback(WINDOW_NAME, mouse_callback);
}