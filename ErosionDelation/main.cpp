#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

int main() {

	Mat src, dst;

	src = imread("Mars.jpg");
	if (src.empty())
	{
		std::cout << "Invalid image (empty)" << std::endl;
		return -1;
	}



	return 0;
}