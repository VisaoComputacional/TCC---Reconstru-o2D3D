// Reconstruction.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AutomatedTests\BatchReconstruction.h"
#include <string>
#include <iostream>

using namespace AutomatedTests;

int main(int argc, char **argv)
{
	BatchReconstruction* batch = new BatchReconstruction();

	batch->Test();

	system("pause");
	return 0;
}

