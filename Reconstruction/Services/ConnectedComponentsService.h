#ifndef SERVICES_COMPONENTS_CONNECTED
#define SERVICES_COMPONENTS_CONNECTED
#include <iostream>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"
#include "../Helpers/ReconstructionDefine.h"
#include "../Helpers/PointsUtilities.h"
#include "../Helpers/Console.h"

using namespace std;
using namespace Algorithms;
using namespace Helpers;

namespace Services {

	// Implementar fun��es do ComponentsConnected utilizando os Algorithms
	class ConnectedComponentsService
	{
	private:
		OpenCV * _openCv;
		float _threshold = 0.02;
		int _interval = 3;
		Size _screenSize = Size(REC_SCREEN_DEFAULT_WIDTH, REC_SCREEN_DEFAULT_HEIGHT);
		Mat DrawFiltering(vector<vector<Point>>& contours, vector<Vec4i>& hierarchy, Mat image, int n);
		double GetBestAverage(vector<vector<Point>> contours);

	public:
		ConnectedComponentsService();
		ConnectedComponentsService(OpenCV* openCV);
		ConnectedComponentsService(OpenCV* openCV, Size imgSize);
		ConnectedComponentsService(OpenCV* openCV, Size imgSize, float threshold, float interval);
		~ConnectedComponentsService();
		vector<Mat> Execute(Mat img);
		vector<Point3f>  ConnectedComponentsService::ExecuteOnCanny(Mat img);
		Mat  ConnectedComponentsService::ExecuteOnCannyDilated(Mat img);
	};

}

#endif