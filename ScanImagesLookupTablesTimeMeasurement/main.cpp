#include <iostream>
#include <sstream>

#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

Mat& ScanImageAndReduceC(Mat& I, const uchar* const table);
Mat& ScanImageAndReduceIterator(Mat& I, const uchar* const table);

int main(int ac, char** av) {

	if (ac < 3) {
		std::cout << "too few arguments!!!" << std::endl;
		return -1;
	}

	cv::Mat I, J;

	if (ac == 4 && !strcmp(av[3], "G"))
		I = cv::imread(av[1], IMREAD_GRAYSCALE);
	else
		I = cv::imread(av[1], IMREAD_COLOR);

	namedWindow("MarsI");
	imshow("MarsI", I);

	if (I.empty()) {
		std::cout << "The image " << av[1] << " is empty !!" << std::endl;
		return -1;
	}

	int divideWith = 0;
	std::stringstream s;
	s << av[2];
	s >> divideWith;

	if (!divideWith || !s) {
		std::cout << "Incorrect divide number !!!" << std::endl;
		return -1;
	}

	uchar table[256];
	for (int i = 0; i < 256; ++i) {
		table[i] = (uchar) (divideWith * (i / divideWith));
	}

	const int times = 100;
	auto t = (double) getTickCount();

	for (int i = 0; i < times; ++i) {
		cv::Mat clone_i = I.clone();
		J = ScanImageAndReduceC(clone_i, table);
	}

	t = 1000 * ((double)getTickCount() - t) / getTickFrequency();
	t /= times;

	std::cout << "Time of reducing with the C operator [] (averaged for "
	          << times << " runs): " << t << " milliseconds." << std::endl;

	namedWindow("Mars");
	imshow("Mars", J);

	t = (double) getTickCount();
	for (int i = 0; i < times; ++i)
	{
		cv::Mat clone_i = I.clone();
		J = ScanImageAndReduceIterator(clone_i, table);
	}

	t = 1000 * ((double)getTickCount() - t) / getTickFrequency();
	t /= times;

	std::cout << "Time of reducing with the iterator (averaged for "
	     << times << " runs): " << t << " milliseconds."<< std::endl;

	namedWindow("Mars");
	imshow("Mars", J);

	waitKey(0);
	return 0;
}

Mat& ScanImageAndReduceC(Mat& I, const uchar* const table)
{
	// accept only char type matrices
	CV_Assert(I.depth() == CV_8U);

	int channels = I.channels();

	int nRows = I.rows;
	int nCols = I.cols * channels;

	if (I.isContinuous())
	{
		nCols *= nRows;
		nRows = 1;
	}

	int i,j;
	uchar* p;
	for( i = 0; i < nRows; ++i)
	{
		p = I.ptr<uchar>(i);
		for ( j = 0; j < nCols; ++j)
		{
			p[j] = table[p[j]];
		}
	}
	return I;
}

Mat& ScanImageAndReduceIterator(Mat& I, const uchar* const table)
{
	CV_Assert(I.depth() == CV_8U);

	const int chanels = I.channels();

	switch (chanels)
	{
		case 1:
		{
			MatIterator_<uchar> it, end;
			for (it = I.begin<uchar>(), end = I.end<uchar>(); it != end; it++)
			{
				*it = table[*it];
			}
			break ;
		}
		case 3:
		{
			MatIterator_<Vec3b> it, end;
			for (it = I.begin<Vec3b>(), end = I.end<Vec3b>(); it != end; it++)
			{
				(*it)[0] = table[(*it)[0]];
				(*it)[1] = table[(*it)[1]];
				(*it)[2] = table[(*it)[2]];
			}
			break ;
		}
	}
	return I;
}