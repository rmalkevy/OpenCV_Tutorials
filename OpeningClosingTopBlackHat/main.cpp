#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

static Mat srcImg, dstImg;
static int morphElem = 0;
static int morphSize = 0;
static int morphOperator = 0;
static const int maxOperator = 4;
static const int maxElem = 2;
static const int maxKernelSize = 21;
static const char *nameWindow = "Morphology Transformations Demo";

void MorphologyOperations(int, void*);

int main() {

//	srcImg = imread("Mars.jpg", IMREAD_COLOR);
	srcImg = imread("lena.bmp", IMREAD_COLOR);
	if (srcImg.empty()){
		std::cout << "Invalid image! (empty)" << std::endl;
		return -1;
	}

	namedWindow(nameWindow, WINDOW_AUTOSIZE);

	createTrackbar("Operator: \n 0: Opening - 1: Closing \n 2: Gradient - 3: Top Hat \n 4: Black Hat",
	               nameWindow, &morphOperator, maxOperator, MorphologyOperations);

	createTrackbar("Element: \n 0: Rect - 1: Cross \n 2: Ellipse",
	               nameWindow, &morphElem, maxElem, MorphologyOperations);

	createTrackbar("Kernel size: \n 2n + 1",
	               nameWindow, &morphSize, maxKernelSize, MorphologyOperations);

	MorphologyOperations(0, 0);
	waitKey(0);

	return 0;
}

void    MorphologyOperations(int, void*)
{
	int operation = morphOperator + 2;

	Mat element = getStructuringElement(morphElem,
	                                    Size(2 * morphSize + 1, 2 * morphSize + 1),
	                                    Point(morphSize, morphSize));
	morphologyEx(srcImg, dstImg, operation, element);
	imshow(nameWindow, dstImg);
}