#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

static Mat srcImg, dstErosion, dstDilation;
static int erosionElem = 0;
static int erosionSize = 0;
static int dilationElem = 0;
static int dilationSize = 0;
static int const maxElem = 2;
static int const maxKernelSize = 21;

void    Erosion(int, void*);
void    Dilation(int, void*);

int main() {

	//srcImg = imread("Mars.jpg", IMREAD_COLOR);
	srcImg = imread("lena.bmp", IMREAD_COLOR);
	if (srcImg.empty())
	{
		std::cout << "Invalid image (empty)" << std::endl;
		return -1;
	}

	namedWindow("Erosion Demo", WINDOW_AUTOSIZE);
	namedWindow("Dilation Demo", WINDOW_AUTOSIZE);
	moveWindow("Dilation Demo", srcImg.cols, 0);

	createTrackbar("Element:\n0: Rect: \n 1: Cross: \n 2: Ellipse", "Erosion Demo",
	               &erosionElem, maxElem, Erosion);

	createTrackbar("Kernel size:\n2n + 1", "Erosion Demo",
	               &erosionSize, maxKernelSize, Erosion);

	createTrackbar("Element:\n0: Rect: \n 1: Cross: \n 2: Ellipse", "Dilation Demo",
	               &dilationElem, maxElem, Dilation);

	createTrackbar("Kernel size:\n2n + 1", "Dilation Demo",
	               &dilationSize, maxKernelSize, Dilation);

	waitKey();
	return 0;
}

void    Erosion(int, void*)
{
	int erosion_type = 0;
	if (erosionElem == 0) {
		erosion_type = MORPH_RECT;
	}
	else if (erosionElem == 1) {
		erosion_type = MORPH_CROSS;
	}
	else if (erosionElem == 2) {
		erosion_type = MORPH_ELLIPSE;
	}

	Mat element = getStructuringElement(erosion_type,
	                                    Size(2 * erosionSize + 1, 2 * erosionSize + 1),
	                                    Point(erosionSize, erosionSize));

	erode(srcImg, dstErosion, element);
	imshow("Erosion Demo", dstErosion);
}

void    Dilation(int, void*)
{
	int dilation_type = 0;
	if (dilationElem == 0) {
		dilation_type = MORPH_RECT;
	}
	else if (dilationElem == 1) {
		dilation_type = MORPH_CROSS;
	}
	else if (dilationElem == 2) {
		dilation_type = MORPH_ELLIPSE;
	}

	Mat element = getStructuringElement(dilation_type,
	                                    Size(2 * dilationSize + 1, 2 * dilationSize + 1),
	                                    Point(dilationSize, dilationSize));

	dilate(srcImg, dstDilation, element);
	imshow("Dilation Demo", dstDilation);
}