#include "EdgeDetection.h"
#include <vector>


CEdgeDetection::CEdgeDetection()
{
}


CEdgeDetection::~CEdgeDetection()
{
}

void CEdgeDetection::edge(const Mat& mat, Mat& edgeMat, int type /*= 0*/, int nDirect /*= 0*/, int thresh /*= 10*/)
{
	assert(mat.data != nullptr);
	cv::Mat filter;
	if (true == CreateFilter(type, filter))
	{
		cout << filter << endl;
		vector<Mat> BGRChannels;
		cv::split(mat, BGRChannels);
		int rowNumber = mat.rows; //第0个维度
		int colNumber = mat.cols; //第1个维度

		edgeMat.create(rowNumber, colNumber, CV_8UC1);

		for (int k = 0; k < 3; k++)
		{
			BGRChannels[k].convertTo(BGRChannels.at(k), CV_32FC1);			
		}

		for (int i = 0; i < rowNumber; i++)
		{
			for (int j = 0; j < colNumber; j++)
			{
				int iMin = (i - 1) > 0 ? (i - 1) : 0;
				int iMax = (i + 1) < (rowNumber - 1) ? (i + 1) : (rowNumber - 1);
				int jMin = (j - 1) > 0 ? (j - 1) : 0;
				int jMax = (j + 1) < (colNumber - 1) ? (j + 1) : (colNumber - 1);
				Mat imgROI0 = BGRChannels[0](cv::Range(iMin, iMax + 1), cv::Range(jMin, jMax + 1));
				Mat imgROI1 = BGRChannels[1](cv::Range(iMin, iMax + 1), cv::Range(jMin, jMax + 1));
				Mat imgROI2 = BGRChannels[2](cv::Range(iMin, iMax + 1), cv::Range(jMin, jMax + 1));
				Mat filterROI = filter(cv::Range(iMin - i + 1, iMax - i + 1 + 1), cv::Range(jMin - j + 1, jMax - j + 1 + 1));
				/*cout << filterROI << endl;
				cout << imgROI0 << endl;
				cout << imgROI1 << endl;
				cout << imgROI2 << endl;*/

				double value0 = imgROI0.dot(filterROI);
				double value1 = imgROI1.dot(filterROI);
				double value2 = imgROI2.dot(filterROI);
				uchar ave = cv::saturate_cast<uchar>((value0 + value1 + value2) / 3);
				/*cout << "i = " << i << "  j = " << j << endl;*/
				edgeMat.at<uchar>(i, j) = ave;
			}
		}

	}
}

bool CEdgeDetection::CreateFilter(int type, Mat& mfilter)
{
	switch (type)
	{
	case 0:
		mfilter = (Mat_<float>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
	default:
		break;
	}

	return mfilter.data == nullptr ? false : true;
}
