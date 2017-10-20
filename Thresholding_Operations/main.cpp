#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

static const char* winName = "Thresholding Operations Demo";

static int thresholdType = 3;
static int thresholdValue = 0;
static const int maxType = 4;
static const int maxValue = 255;
static const int maxBinaryValue = 255;

static Mat srcImg, srcGray, dstImg;

static const char* trackbarType =
		"Type: \n 0: Binary \n 1: Binary inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero inverted";
static const char* trackbarValue = "Value";

void    ThresholdDemo(int, void*);

int main() {

	srcImg = imread("Mars.jpg");
	if (srcImg.empty())
	{
		std::cout << "Error image(empty)" << std::endl;
		return -1;
	}

	cvtColor(srcImg, srcGray, COLOR_BGR2GRAY);
	namedWindow(winName, WINDOW_AUTOSIZE);

	createTrackbar(trackbarType, winName, &thresholdType, maxType, ThresholdDemo);
	createTrackbar(trackbarValue, winName, &thresholdValue, maxValue, ThresholdDemo);

	ThresholdDemo(0, 0);

	while (true){
		auto c = (char)waitKey(20);
		if (c == 27) { break ; }
	}
	return 0;
}

void ThresholdDemo(int, void*)
{
	threshold(srcGray, dstImg, thresholdValue, maxBinaryValue, thresholdType);
	imshow(winName, dstImg);
}