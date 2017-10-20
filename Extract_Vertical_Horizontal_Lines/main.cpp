#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

void ShowWaitDestroy(const char *winName, Mat &img);

int main() {

	Mat src = imread("AVA_FB.jpg", IMREAD_GRAYSCALE);
	if (src.empty())
	{
		std::cout << "Invalid image (empty)!!!" << std::endl;
		return -1;
	}

	resize(src, src, Size(), 0.3, 0.3, INTER_NEAREST);

	namedWindow("Original", WINDOW_AUTOSIZE);
	imshow("Original", src);
	moveWindow("Original", 0, 0);

	Mat grey;
	if (src.channels() == 3) {
		cvtColor(src, grey, CV_BGR2GRAY);
	} else {
		grey = src;
	}

	ShowWaitDestroy("Grey", grey);

	Mat bw;
	adaptiveThreshold(~grey, bw, 255, CV_ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, -2);
	ShowWaitDestroy("Binary image", bw);

	Mat horizontal = bw.clone();
	Mat vertical = bw.clone();


	// Extract horizontal lines
	int horizontal_size = horizontal.cols / 40;

	Mat horizontalStructure = getStructuringElement(MORPH_RECT, Size(horizontal_size, 1));

	// Apply morphology operations
	erode(horizontal, horizontal, horizontalStructure, Point(-1, -1));
	dilate(horizontal, horizontal, horizontalStructure, Point(-1, -1));

	ShowWaitDestroy("Horizontal lines", horizontal);


	// Extract vertical lines
	int vertical_size = vertical.rows / 40;

	Mat verticalStructure = getStructuringElement(MORPH_RECT, Size(1, vertical_size));

	// Apply morphology operations

	erode(vertical, vertical, verticalStructure, Point(-1, -1));
	dilate(vertical, vertical, verticalStructure, Point(-1, -1));

	ShowWaitDestroy("Vertical lines", vertical);

	Mat sumImages = vertical + horizontal; // Bonus from me :)
	bitwise_not(sumImages, sumImages);
	// Invert image
//	bitwise_not(vertical, vertical);
//	ShowWaitDestroy("Vertical bitwise not", vertical);

	// Extract edges and smooth image according to the logic
	// 1. extract edges
	// 2. dilate(edges)
	// 3. src.copyTo(smooth)
	// 4. blur smooth img
	// 5. smooth.copyTo(src, edges)


//	// Step 1
//	Mat edges;
//	adaptiveThreshold(vertical, edges, 255, CV_ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 3, -2);
//	ShowWaitDestroy("Extract edges", edges);
//
//	// Step 2
	Mat kernel = Mat::ones(2, 2, CV_8UC1);
//	dilate(edges, edges, kernel);
//	ShowWaitDestroy("Dilating edges", edges);
//
//	// Step 3
//	Mat smooth;
//	vertical.copyTo(smooth);
//
//	// Step 4
//	blur(smooth, smooth, Size(2, 2));
//
//	// Step 5
//	smooth.copyTo(vertical, edges);
//
//	ShowWaitDestroy("Vertical end processing", vertical);

	// My own addition to this tutorial

	// Step 1
	Mat myEdges;
	adaptiveThreshold(sumImages, myEdges, 255, CV_ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 3, -2);
	ShowWaitDestroy("Extract edges", myEdges);

	// Step 2
	dilate(myEdges, myEdges, kernel);
	ShowWaitDestroy("Dilating edges", myEdges);

	// Step 3
	Mat mySmooth;
	vertical.copyTo(mySmooth);

	// Step 4
	blur(mySmooth, mySmooth, Size(2, 2));

	// Step 5
	mySmooth.copyTo(sumImages, myEdges);

	ShowWaitDestroy("Vertical end processing", sumImages);

	ShowWaitDestroy("SumImages", sumImages);

	return 0;
}

void ShowWaitDestroy(const char* winName, Mat &img){

	namedWindow(winName);
	moveWindow(winName, 500, 0);
	imshow(winName, img);
	waitKey();
	destroyWindow(winName);
}