// Reconstruction.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AutomatedTests\BatchReconstruction.h"
#include <string>
#include <iostream>

using namespace AutomatedTests;

int main(int argc, char **argv)
{
	/*BatchReconstruction* batch = new BatchReconstruction();
	batch->Test();*/
	map<string, double> resultBatchFFFP;
	Import::CalculateAverage(".\\Reports\\Export_Result\\FF_FP", resultBatchFFFP);
	Export::Csv(resultBatchFFFP, ".\\Reports\\average_FF_FP.csv");

	map<string, double> resultBatchFF;
	Import::CalculateAverage(".\\Reports\\Export_Result\\FF", resultBatchFF);
	Export::Csv(resultBatchFF, ".\\Reports\\average_FF.csv");

	map<string, double> resultBatchFP;
	Import::CalculateAverage(".\\Reports\\Export_Result\\FP", resultBatchFP);
	Export::Csv(resultBatchFP, ".\\Reports\\average_FP.csv");

	map<string, double> resultBatchDefault;
	Import::CalculateAverage(".\\Reports\\Export_Result\\DEFAULT", resultBatchDefault);
	Export::Csv(resultBatchDefault, ".\\Reports\\average_DEFAULT.csv");

	system("pause");
	return 0;
}

