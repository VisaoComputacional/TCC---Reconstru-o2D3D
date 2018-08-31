#include "stdafx.h"
#include "TestService.h"

namespace Services {

	TestService::TestService()
	{
		_time = new Time();
	}

	TestService::~TestService()
	{
	}

	void lala() {
		ControllerService* controller = new ControllerService(".\\Others Files\\TestImage.jpg", ".\\Others Files\\TestImage.jpg");

		controller->DisplayImages();
	}

	void TestService::TimeExecution()
	{
		cout << "======= Start Test Execution ======= " << endl;

		ControllerService* controller = new ControllerService(".\\Others Files\\TestImage.jpg", ".\\Others Files\\TestImage.jpg");

		cout << &ControllerService::DisplayImages << endl;

		_time->Run(lala, "DisplayImages");

		cout << "======== End Test Execution ======== " << endl;
	}


	void TestService::Reconstruction(int argc, char **argv)
	{
		cout << "======= Start Test ======= " << endl;

		ControllerService* controller = new ControllerService(".\\Others Files\\cabeca_1.png", ".\\Others Files\\cabeca_2.png");

		controller->SetFireflyProperties(1, 50, 100);
		controller->SetCannyProperties(50, 700, 3);
		controller->SetConnectedComponentsProperties(0);
		controller->SetGeneralProperties();
		controller->SetSiftProperties(0);
		controller->SetCalibrationProperties(0, 0, 1);
		controller->SetRenderProperties(&argc, argv);

		//controller->FireflyApply();	
		//controller->DisplayImages();

		/*------------------------------------------------------*/

		//controller->ConnectedComponentsApply();
		//controller->FindRegionsApply();
		//controller->SiftApply();
		//controller->RansacApply();
		//controller->CalibrationApply();
		//controller->CannyApply();
		//controller->DelaunayApply();
		//controller->RenderApply();

		//-------------- Test all ---------------------

		CannyService *canny = new CannyService();
		RenderService *teste = new RenderService();
		SiftService *sift = new SiftService();
		CalibrationService *calibracao = new CalibrationService(1, 1, new OpenCV());
		imread(".\\Others Files\\cabeca_1.png");
		imread(".\\Others Files\\cabeca_2.png");
		ResultSift result = sift->Execute(imread(".\\Others Files\\cabeca_1.png"), imread(".\\Others Files\\cabeca_2.png"), 1000);
		Convert *convert = new Convert();

		//vector<Point3f> calibra = calibracao->CalculateStereoCameraCalibration(convert->DMatchToPointPair(result.Matches, result.FirstImageKeyPoints, result.SecondImageKeyPoints));
		vector<PointPair> points = convert->DMatchToPointPair(result.Matches, result.FirstImageKeyPoints, result.SecondImageKeyPoints);

		vector<Point3f> _pts;
		for each (PointPair point_ in points)
		{
			_pts.push_back(point_.FirstPoint);
		}

		teste->TestExecute(&argc, argv, _pts);


		//---------- TestsDelauney -----------------

		//CannyService *canny = new CannyService();
		//DelaunayService *teste = new DelaunayService();
		//teste->TestExecute(canny->Execute(imread(".\\Others Files\\TestImage.jpg"), 50, 700, 3));

		//---------- TestsFirefly ------------------

		//FireflyService *test = new FireflyService();
		//test->TestExecute(".\\Others Files\\TestImage.jpg", 1, 50, 100);

		//---------- TestRender ------------------
		//CannyService *canny = new CannyService();
		//RenderService *teste = new RenderService();
		//teste->TestExecute(&argc, argv);
		//teste->TestExecute(&argc, argv, canny->Execute(imread(".\\Others Files\\TestImage.jpg"), 50, 700, 3));

		// ---------- TestCanny -------------
		//CannyService *canny = new CannyService();
		//canny->TestExecute(imread(".\\Others Files\\TestImage.jpg"), 50, 700, 3);

		// ---------- TestRansac -------------

		cout << "======== End Test ======== " << endl;
	}
}