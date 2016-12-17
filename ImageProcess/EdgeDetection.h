#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
class CEdgeDetection
{
public:
	CEdgeDetection();
	virtual ~CEdgeDetection();

	void edge(const Mat& mat, Mat& edgeMat, int type = 0, int nDirect = 0, int thresh = 10);
	bool CreateFilter(int type, Mat& mfilter);
};

