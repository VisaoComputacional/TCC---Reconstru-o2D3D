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
	SiftResult SiftService::Execute(Mat img1, Mat img2, int threshold) 
	{
		//Sift Detector
		cv::SiftFeatureDetector detector(threshold);

		//Key points of images
		vector<KeyPoint> firstImgKeyPoints, secondImgKeyPoints;
		
		//Description of images
		Mat firstImgDescription, secondImgDescription;

		//Matches found in images
		vector<DMatch> matches;

		//-- Draw only "good" matches (i.e. whose distance is less than 3*min_dist )
		std::vector< DMatch > good_matches;

		SiftResult result;
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

		//Outro tipo de match
		/*FlannBasedMatcher matcher;
		matcher.match(firstImgDescription, secondImgDescription, matches);*/

		
	

		result.Matches = matches;
		result.FirstImageKeyPoints = firstImgKeyPoints;
		result.SecondImageKeyPoints = secondImgKeyPoints;
		
		drawMatches(img1, firstImgKeyPoints, img2, secondImgKeyPoints, matches, result.siftImg, Scalar::all(-1), Scalar::all(-1),
			vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
		return result;
	}
}