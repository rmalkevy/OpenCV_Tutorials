#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>


int main(int ac, char** av) {

	if (ac == 2) {
		cv::Mat image = cv::imread(av[1], CV_LOAD_IMAGE_COLOR);

        if (image.empty())
        {
            std::cout << "Image empty" << std::endl;
            return ( 0 );
        }

        cv::Mat gray_image;
        cv::cvtColor(image, gray_image, CV_BGR2GRAY);
        cv::imwrite("/images/gray_Mars.jpg", gray_image);

        std::string nameWindowRGB = "WindowRGB";
        std::string nameWindowGray = "WindowGrey";

        cv::namedWindow(nameWindowRGB);
        cv::namedWindow(nameWindowGray);

        cv::imshow(nameWindowRGB, image);
        cv::imshow(nameWindowGray, gray_image);

        cv::waitKey(0);
	}

    return 0;
}