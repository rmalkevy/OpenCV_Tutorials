#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace cv;
using namespace std;

int main() {

	double alpha, beta;

	cout << "Alpha must be a number [1.0 - 3.0]. "
	     << "alpha = "; cin >> alpha;
	cout << "Beta must be a number [0 - 100]"
	     << " beta = "; cin >> beta;

	if (alpha < 1 || alpha > 3)
		alpha = 1;
	if (beta < 0 || beta > 100)
		beta = 0;

	Mat img = imread("1.jpg");
	if (img.empty())
	{
		cout << "Image empty !" << endl;
		return -1;
	}

	Mat newImg = Mat::zeros(img.size(), img.type());

	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			for (int c = 0; c < 3; c++)
			{
				newImg.at<Vec3b>(i,j)[c] =
				saturate_cast<uchar>(alpha * (img.at<Vec3b>(i,j)[c]) + beta);
			}
		}
	}
	string originalImg = "OriginalImg";
	string processedImg = "ProcessedImg";
	namedWindow(originalImg);
	namedWindow(processedImg);

	imshow(originalImg, img);
	imshow(processedImg, newImg);

	waitKey(500000);
	return 0;
}
