#include <iostream>
#include <opencv2/core/hal/interface.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main() {

	Mat img = imread("Mars.jpg");
	Mat grey;
	cvtColor(img, grey, COLOR_BGR2GRAY);
	Mat sobelx;
	Sobel(grey, sobelx, CV_32F, 1, 0);
	double minVal, maxVal;
	minMaxLoc(sobelx, &minVal, &maxVal); //find minimum and maximum intensities
	Mat draw;
	sobelx.convertTo(draw, CV_8U, 255.0/(maxVal - minVal), -minVal * 255.0/(maxVal - minVal));
	namedWindow("image", WINDOW_AUTOSIZE);
	imshow("image", draw);
	waitKey();

	return 0;
}