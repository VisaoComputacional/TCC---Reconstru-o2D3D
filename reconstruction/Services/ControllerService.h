#ifndef SERVICES_RECONSTRUCTION
#define SERVICES_RECONSTRUCTION

#pragma region [ Services ]

#include "CalibrationService.h"
#include "CannyService.h"
#include "ConnectedComponentsService.h"
#include "DelaunayService.h"
#include "FindRegionsService.h"
#include "FireflyService.h"
#include "RansacService.h"
#include "SiftService.h"
#include "InputImageService.h"

#pragma endregion

namespace Services {

	class ControllerService
	{

		private:
		
			// Algorithms
			OpenCV * _openCv;

			// Services
			CalibrationService* _calibrationService;
			CannyService* _cannyService;
			ConnectedComponentsService* _connectedComponentsService;
			DelaunayService* _delaunayService;
			FindRegionsService* _findRegionsService;
			FireflyService* _fireflyService;
			RansacService* _ransacService;
			SiftService* _siftService;
			InputImageService* _inputImageService;

			// General Properties
			Mat _firstImage;
			Mat _secondImage;
			Mat _firstImageModified;
			Mat _secondImageModified;

			// Delaunay Properties
			vector<Vec6f> _resultDelaunay;
			Mat _inputImageToRender;

			// Sift Properties
			int _siftThreshold;
			vector<PointPair> _resultSift;

			//Ransac Properties
			vector<Point3f> _resultRansac;

			// Canny Properties
			double _cannyLowThresh;
			double _cannyHighTresh;
			int _cannyKernelSize;
			Mat _pointsCanny;

			// Connected Components Properties
			int _connectedComponentsThreshVal;
			Mat _InterestRegionsFirstImage;
			Mat _InterestRegionsSecondImage;

			// Calibration Properties
			float _calibrationB;
			float _calibrationLambda;
			int _calibrationK;
			vector<CustomPoint> _resultCalibration;

			// Fireflies Properties
			int _thresholds;
			int _number_fireflies;
			int _number_generations;

			void LoadServices();

		public:
			ControllerService();
			ControllerService(Mat firstImage, Mat secondImage);
			ControllerService(string pathFirstImage, string pathSecondImage);
			~ControllerService();

			bool CalibrationApply();
			bool CannyApply();
			bool ConnectedComponentsApply();
			bool DelaunayApply();
			bool FindRegionsApply();
			bool RansacApply();
			bool SiftApply();
			bool RenderApply();
			bool FireflyApply();
			bool ReadImages(string pathFirstImage, string pathSecondImage);

			void SetCannyProperties(double cannyLowThresh, double cannyHighTresh, int cannyKernelSize);
			void SetSiftProperties(int siftThreshold);
			void SetConnectedComponentsProperties(int connectedComponentsThreshVal);
			void SetCalibrationProperties(float calibrationB, float calibrationLambda, int calibrationK);
			void SetGeneralProperties();
			void SetFireflyProperties(int thresholds, int number_fireflies, int number_generations);

	};

}

#endif