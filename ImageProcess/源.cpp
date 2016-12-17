#include <iostream>
#include <string>
#include "EdgeDetection.h"

void main()
{
	CEdgeDetection ced;
	cv::Mat img = cv::imread("Lenna.jpg");
	cv::Mat edgimg;
	ced.edge(img, edgimg);
	namedWindow("dege");
	cv::imshow("dege", edgimg);
	waitKey(0);
}