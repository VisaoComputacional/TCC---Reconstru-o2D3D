// Reconstruction.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Services\TestService.h"

using namespace Services;
using namespace Helpers;

int main(int argc, char **argv)
{
	TestService* testService = new TestService();

	testService->Reconstruction(argc, argv);
	//testService->Render(argc, argv);
	//testService->ReconstructionWithTimeExecution(argc, argv);
	//testService->ConnectedComponents();
	system("pause");
	return 0;
}

