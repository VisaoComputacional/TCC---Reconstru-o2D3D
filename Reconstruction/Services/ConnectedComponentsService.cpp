#include "stdafx.h"
#include "ConnectedComponentsService.h"

namespace Services {

	ConnectedComponentsService::ConnectedComponentsService()
	{
		_openCv = new OpenCV();
		_threshold = 1;
	}

	ConnectedComponentsService::ConnectedComponentsService(OpenCV* openCV, float threshold)
	{
		_openCv = openCV;
		_threshold = threshold;
	}

	ConnectedComponentsService::ConnectedComponentsService(OpenCV* openCV)
	{
		_openCv = openCV;
		_threshold = 1;
	}

	ConnectedComponentsService::~ConnectedComponentsService()
	{
	}

	Mat ConnectedComponentsService::Execute(Mat img)
	{
		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;

		findContours(img, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

		Mat result = Mat::zeros(img.size(), CV_8UC3);

		if (!contours.empty() && !hierarchy.empty())
		{
			// iterate through all the top-level contours,
			// draw each connected component with its own random color
			int idx = 0;
			for (; idx >= 0; idx = hierarchy[idx][0])
			{
				Scalar color((rand() & 255), (rand() & 255), (rand() & 255));
				drawContours(result, contours, idx, color, CV_FILLED, 8, hierarchy);
			}
		}

		return result;
	}

}