// Reconstruction.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AutomatedTests\BatchReconstruction.h"
#include <string>
#include <iostream>

using namespace AutomatedTests;

int main(int argc, char **argv)
{
	/*
	BatchReconstruction* batch = new BatchReconstruction();
	batch->Test();

	map<string, AverageDeviationStd*> resultBatchFFFP;
	Import::CalculateAverage(".\\Reports\\Export_Result\\FF_FP", resultBatchFFFP);
	Export::Csv(resultBatchFFFP, ".\\Reports\\average_FF_FP.csv");

	map<string, AverageDeviationStd*> resultBatchFF;
	Import::CalculateAverage(".\\Reports\\Export_Result\\FF", resultBatchFF);
	Export::Csv(resultBatchFF, ".\\Reports\\average_FF.csv");

	map<string, AverageDeviationStd*> resultBatchFP;
	Import::CalculateAverage(".\\Reports\\Export_Result\\FP", resultBatchFP);
	Export::Csv(resultBatchFP, ".\\Reports\\average_FP.csv");

	map<string, AverageDeviationStd*> resultBatchDefault;
	Import::CalculateAverage(".\\Reports\\Export_Result\\DEFAULT", resultBatchDefault);
	Export::Csv(resultBatchDefault, ".\\Reports\\average_DEFAULT.csv");
	
	map<string, double> *result = new map<string, double>();*/
	TestService* test = new	TestService();
	/*test->ReconstructionFF_FP(
		".\\Structured_Images\\_tests\\calib.txt",
		".\\Structured_Images\\_tests\\tennis_frameprincipal.png",
		".\\Structured_Images\\_tests\\tennis_frameprincipal2.png",
		".\\Structured_Images\\_tests\\disp0.pfm",
		".\\Reports\\test.csv",
		new map<string, double>()
	);*/

	test->Reconstruction_FP(
		".\\Structured_Images\\_tests\\calib.txt",
		".\\Structured_Images\\_tests\\aberta_frameprincipal.png",
		".\\Structured_Images\\_tests\\aberta_frameprincipal2.png",
		".\\Structured_Images\\_tests\\disp0.pfm",
		".\\Reports\\test.csv",
		new map<string, double>()
	);

	system("pause");
	return 0;
}

