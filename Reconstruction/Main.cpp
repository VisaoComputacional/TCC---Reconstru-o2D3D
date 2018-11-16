// Reconstruction.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AutomatedTests\TestService.h"
#include <string>
#include <iostream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;
using namespace std;

int main(int argc, char **argv)
{
	AutomatedTests::TestService* testService = new AutomatedTests::TestService();

	vector<string> paths_base;
	// Get all paths in structure images
	for (auto & p : fs::directory_iterator(".\\Structured_Images"))
		paths_base.push_back(p.path().string());

	// Run test in all paths
	for each (string path in paths_base)
	{
		int i = 0;
		int total = paths_base.size();

		cout << "--------------------------------------------------------------------" << endl;
		cout << "Executing: " + path.substr(path.find("s\\") + 2, path.size()) << endl;
		cout << "Progress: " + to_string(i) + " | " + to_string(total) << endl;
		cout << "--------------------------------------------------------------------" << endl<< endl << endl << endl;

		string export_path = ".\\Export_Result\\" + path.substr(path.find("s\\") + 2, path.size());
		testService->ReconstructionFF_FP(path + "\\calib.txt", 
											path + "\\im0.png", 
												path + "\\im1.png", 
													path + "\\disp0.pfm", 
														export_path + "_FF_FP.csv");

		testService->Reconstruction_FF(path + "\\calib.txt",
											path + "\\im0.png",
												path + "\\im1.png",
													path + "\\disp0.pfm",
														export_path + "_FF.csv");
		
		testService->Reconstruction_FP(path + "\\calib.txt",
											path + "\\im0.png",
												path + "\\im1.png",
													path + "\\disp0.pfm",
														export_path + "_FP.csv");

		testService->Reconstruction_Default(path + "\\calib.txt",
												path + "\\im0.png",
													path + "\\im1.png",
														path + "\\disp0.pfm",
															export_path + "_FP.csv");

		i++;
		system("cls");
	}

	system("pause");
	return 0;
}

