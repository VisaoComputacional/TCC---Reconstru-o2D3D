// Reconstruction.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AutomatedTests\TestService.h"


int main(int argc, char **argv)
{
	AutomatedTests::TestService* testService = new AutomatedTests::TestService();

	//testService->ReconstructionFF_FP();
	testService->Reconstruction_FF();
	//testService->Reconstruction_FP();
	//testService->Reconstruction_Default();

	system("pause");
	return 0;
}

