#include <iostream>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main() {

	double alpha = 0.5, beta, input;

	Mat src1, src2, dst;
	cout << " Simple Linear Blender " << endl;
	cout << "-----------------------" << endl;
	cout << "* Enter alpha [0.0-1.0]: ";

	cin >> input;

	if (input >= 0 && input <= 1)
		alpha = input;

	src1 = imread("2.jpg");
	src2 = imread("3.jpg");

	if (src1.empty()) { cout << "src1 is empty! " << endl; return -1; };
	if (src2.empty()) { cout << "src2 is empty! " << endl; return -1; };

	beta = 1 - alpha;
	addWeighted(src1, alpha, src2, beta, 0.0, dst);

	string nameWindow = "Lena with boobs";
	namedWindow(nameWindow);
	imshow(nameWindow, dst);
	waitKey();
	return 0;
}