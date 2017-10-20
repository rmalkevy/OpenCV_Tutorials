#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace cv;

static const char* winName = "Pyramids Demo";

int main() {

	Mat src = imread("Mars.jpg");
	if (src.empty())
	{
		std::cout << "Error opening image!!!(empty)" << std::endl;
		return -1;
	}

	while (true)
	{
		imshow(winName, src);
		auto c = (char)waitKey(0);

		if (c == 27) { break ; }

		if (c == 'o') {
			pyrDown(src, src, Size(src.cols / 2, src.rows / 2));
			std::cout << "Zoom out, decrease by 2!" << std::endl;
		}
		else if (c == 'i') {
			pyrUp(src, src, Size(src.cols * 2, src.rows * 2));
			std::cout << "Zoom in, increase by 2!" << std::endl;
		}
	}
	return 0;
}