#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace cv;

int main() {

	Mat input_img = (Mat_<uchar>(8, 8) <<
	        0, 0, 0, 0, 0, 0, 0, 0,
			0, 255, 255, 255, 0, 0, 0, 255,
			0, 255, 255, 255, 0, 0, 0, 0,
			0, 255, 255, 255, 0, 255, 0, 0,
			0, 0, 255, 0, 0, 0, 0, 0,
			0, 0, 255, 0, 0, 255, 255, 0,
			0, 255, 0, 255, 0, 0, 255, 0,
			0, 255, 255, 255, 0, 0, 0, 0);

	Mat kernel = (Mat_<int>(3, 3) <<
			0, 1, 0,
			1, -1, 1,
			0, 1, 0);

	Mat output_img;
	morphologyEx(input_img, output_img, MORPH_HITMISS, kernel);

	const int rate = 50;
	kernel = (kernel + 1) * 127;
	kernel.convertTo(kernel, CV_8U);

	resize(kernel, kernel, Size(), rate, rate, INTER_NEAREST);
	imshow("Kernel", kernel);
	moveWindow("Kernel", 0, 0);

	resize(input_img, input_img, Size(), rate, rate, INTER_NEAREST);
	imshow("Original", input_img);
	moveWindow("Original", 0, 200);

	resize(output_img, output_img, Size(), rate, rate, INTER_NEAREST);
	imshow("Hit or Miss", output_img);
	moveWindow("Hit or Miss", 500, 200);

	waitKey();
	return 0;
}