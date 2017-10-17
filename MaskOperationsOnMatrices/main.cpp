#include <iostream>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

void Sharpen(const Mat& myImage, Mat& Result);

int main(int ac, char **av)
{

	if (ac < 2)
	{
		cout << " Too few arguments!!!" << endl;
		return -1;
	}

	Mat origImg, destImg1, destImg2;
	if (ac == 3 && !strcmp(av[2], "G"))
		origImg = imread(av[1], IMREAD_GRAYSCALE);
	else
		origImg = imread(av[1], IMREAD_COLOR);

	if (origImg.empty())
	{
		cout << "Empty image!!!";
		return -1;
	}

	namedWindow("Input", WINDOW_AUTOSIZE);
	namedWindow("Output", WINDOW_AUTOSIZE);

	imshow("Input", origImg);

	auto t = (double)getTickCount();
	Sharpen(origImg, destImg1);
	t = ((double)getTickCount() - t) / getTickFrequency();
	cout << "Time Sharpen  = " << t << endl;

	imshow("Output", destImg1);

	Mat kernel = (Mat_<char>(3,3) << 0, -1, 0,
									 -1, 5, -1,
									 0, -1, 0);

	t = (double)getTickCount();
	filter2D(origImg, destImg2, origImg.depth(), kernel);

	t = ((double)getTickCount() - t) / getTickFrequency();
	cout << "Time filter2D = " << t << endl;


	namedWindow("filter2d");
	imshow("filter2d", destImg2);
	waitKey();

	return 0;
}

void Sharpen(const Mat& myImage, Mat& Result)
{
	CV_Assert(myImage.depth() == CV_8U);

	const int nChannels = myImage.channels();
	Result.create(myImage.size(), myImage.type());
	for (int j = 1; j < myImage.rows - 1; ++j)
	{
		const auto *previous = myImage.ptr<uchar>(j - 1);
		const auto *current  = myImage.ptr<uchar>(j    );
		const auto *next     = myImage.ptr<uchar>(j + 1);

		auto *output = Result.ptr<uchar>(j);
		for (int i = nChannels; i < (myImage.cols - 1) * nChannels; ++i)
		{
			*output++ = saturate_cast<uchar>(5 * current[i] -
			current[i - nChannels] - current[i + nChannels] - previous[i] - next[i]);
		}
	}
	Result.row(0).setTo(Scalar(0));
	Result.row(Result.rows - 1).setTo(Scalar(0));
	Result.col(0).setTo(Scalar(0));
	Result.col(Result.cols - 1).setTo(Scalar(0));
}