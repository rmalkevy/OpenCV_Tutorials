#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

int main() {

	Mat mars = imread("Mars.jpg");
	circle(mars,
	       Point(150,150),
	       100,
	       Scalar( 0, 0, 255 ),
	       //FILLED,
	       LINE_4);

	namedWindow("Mars");
	imshow("Mars", mars);
	waitKey();

	return 0;
}