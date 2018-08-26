#include "stdafx.h"
#include "SiftService.h"

namespace Services {

	SiftService::SiftService()
	{
		_openCv = new OpenCV();
	}
	
	SiftService::SiftService(OpenCV* openCv)
	{
		_openCv = openCv;
	}

	SiftService::~SiftService()
	{
	}

	//Detect fiducial points on the image
	vector<PointPair> SiftService::Execute(Mat img1, Mat img2, int threshold) {
#pragma warning("Rever codigo, verificar resultado da funcao utilizando uma imagem dos pontos ligados")

		//Result of matches
		vector<PointPair> result;

		//Sift Detector
		cv::SiftFeatureDetector detector(threshold);

		//Key points of images
		vector<KeyPoint> firstImgKeyPoints, secondImgKeyPoints;
		
		//Description of images
		Mat firstImgDescription, secondImgDescription;

		//Matches found in images
		vector<DMatch> matches;

		//Auxiliar Custom Points
		CustomPoint auxPoint1(0, 0, 0);
		CustomPoint auxPoint2(0, 0, 0);

		//Auxiliar PointPair
		PointPair auxPair(auxPoint1, auxPoint2);

		//Number of lines and columns of the image
		float lin = img1.rows;
		float col = img1.cols;

		//Clear keypoints and matches vector
		firstImgKeyPoints.clear();
		secondImgKeyPoints.clear();
		matches.clear();

		//Finding images keypoints
		firstImgKeyPoints = _openCv->SiftDetector(&detector, img1);
		secondImgKeyPoints = _openCv->SiftDetector(&detector, img2);

		//Describing the images
		firstImgDescription = _openCv->SiftDescriptor(img1, firstImgKeyPoints);
		secondImgDescription = _openCv->SiftDescriptor(img2, secondImgKeyPoints);

		//Finding matches with Brute Force Matcher
		matches = _openCv->BFMatcher(firstImgDescription, secondImgDescription);

		//Loop that build the matches vector  
		for (int i = 0; i< matches.size(); i++) {

			//Calculations to keep points inside the resolution of the image
			auxPair.FirstPoint.X = -4.0 + (firstImgKeyPoints[i].pt.x / (col / 8.0));
			auxPair.FirstPoint.Y =	4.0 - (firstImgKeyPoints[i].pt.y / (lin / 8.0));
			auxPair.FirstPoint.Z = 0;

			//Calculations to keep points inside the resolution of the image
			auxPair.SecondPoint.X = -4.0 + (secondImgKeyPoints[matches[i].trainIdx].pt.x / (col / 8.0));
			auxPair.SecondPoint.Y = 4.0 - (secondImgKeyPoints[matches[i].trainIdx].pt.y / (lin / 8.0));
			auxPair.SecondPoint.Z = 0;

			//Simple filter by Y axis
			if (abs(auxPair.FirstPoint.Y - auxPair.SecondPoint.Y) > 0.2)
				continue;

			result.push_back(auxPair);
		}

		return result;
	}
}