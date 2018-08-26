// Reconstruction.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Services\ControllerService.h"

using namespace Services;

int main()
{
	cout << "======= Start Test ======= " << endl;

	ControllerService* controller = new ControllerService();
	
	controller->SetFireflyProperties(1, 50, 100);
	controller->SetCannyProperties(0, 0, 0);
	controller->SetConnectedComponentsProperties(0);
	controller->SetGeneralProperties();
	controller->SetSiftProperties(0);
	controller->SetCalibrationProperties(0, 0, 1);

	//controller->ReadImages("", "");
	//controller->FireflyApply();
	//controller->ConnectedComponentsApply();
	//controller->FindRegionsApply();
	//controller->SiftApply();
	//controller->RansacApply();
	//controller->CalibrationApply();
	//controller->CannyApply();
	//controller->DelaunayApply();
	//controller->RenderApply();

	//---------- Tests -----------------
	DelaunayService *teste = new DelaunayService();
	teste->TestExecute();

	cout << "======== End Test ======== " << endl;

	return 0;
}

