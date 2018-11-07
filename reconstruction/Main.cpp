// Reconstruction.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Services\TestService.h"


using namespace Services;
using namespace Helpers;

int main(int argc, char **argv)
{
	TestService* testService = new TestService();

	testService->ReconstructionFF_FP(argc, argv);
	testService->Reconstruction_FF(argc, argv);
	testService->Reconstruction_FP(argc, argv);
	testService->Reconstruction_Default(argc, argv);

	system("pause");
	return 0;
}

