#include "stdafx.h"
#include "BatchReconstruction.h"

namespace AutomatedTests {
	/*  string path_calib = ".\\Others Files\\Cable-perfect\\calib.txt";
		string path_img1 = ".\\Others Files\\Cable-perfect\\im0.png";
		string path_img2 = ".\\Others Files\\Cable-perfect\\im1.png";
		string path_disparity = ".\\Others Files\\Cable-perfect\\disp0.pfm";
		string path_export = ".\\Others Files\\results.csv";

		string path_unstructured1 = ".\\Others Files\\unstructured01.png";
		string path_unstructured2 = ".\\Others Files\\unstructured02.png";*/

	BatchReconstruction::BatchReconstruction()
	{
		_time = new Time();
	}

	BatchReconstruction::~BatchReconstruction()
	{
	}

	void BatchReconstruction::Add(string pathFirstStructuredImage, string pathSecondStructuredImage, string pathFirstUnstructuredImage,
		string pathSecondUnstructuredImage, string pathCalib, string pathDisparity, string pathExportComparison)
	{
		ReconstructionTest obj;
		obj.PathCalib = pathCalib;
		obj.PathDisparity = pathDisparity;
		obj.PathExportComparison = pathExportComparison;
		obj.PathFirstStructuredImage = pathFirstStructuredImage;
		obj.PathSecondStructuredImage = pathSecondStructuredImage;
		obj.PathFirstUnstructuredImage = pathFirstUnstructuredImage;
		obj.PathSecondUnstructuredImage = pathFirstUnstructuredImage;

		ListReconstructions.push_back(obj);
	}


#pragma region [ Load Properties Methods ]

	void BatchReconstruction::LoadPropertiesExample()
	{
		for (int i = 0; i < 10; i++)
		{
			Add(
				".\\Others Files\\Cable-perfect\\im0_" + to_string(i) + ".png",
				".\\Others Files\\Cable-perfect\\im1_" + to_string(i) + ".png",
				".\\Others Files\\unstructured01_" + to_string(i) + ".png",
				".\\Others Files\\unstructured02_" + to_string(i) + ".png",
				".\\Others Files\\Cable-perfect\\calib_" + to_string(i) + ".txt",
				".\\Others Files\\Cable-perfect\\disp0_" + to_string(i) + ".pfm",
				".\\Others Files\\results_" + to_string(i) + ".csv"
			);
		}
	}

#pragma endregion


#pragma region [ Test Methods ]

	void BatchReconstruction::Test()
	{
		int i = 0;
		map<string, double> resultBatchFFFP;
		map<string, double> resultBatchFF;
		map<string, double> resultBatchFP;
		map<string, double> resultBatchDefault;

		AutomatedTests::TestService* testService = new AutomatedTests::TestService();

		vector<string> paths_base;
		// Get all paths in structure images
		for (auto & p : fs::directory_iterator(".\\Structured_Images"))
			paths_base.push_back(p.path().string());

		// Run test in all paths
		for each (string path in paths_base)
		{
			if (i < 3) {
				i++;
				continue;
			}
			int total = paths_base.size();
			
			cout << "--------------------------------------------------------------------" << endl;
			cout << "Executing: " + path.substr(path.find("s\\") + 2, path.size()) << endl;
			cout << "Progress: " + to_string(i) + " | " + to_string(total) << endl;
			cout << "--------------------------------------------------------------------" << endl << endl << endl << endl;

			string export_path_FFFP = ".\\Reports\\Export_Result\\FF_FP\\" + path.substr(path.find("s\\") + 2, path.size());
			string export_path_FF = ".\\Reports\\Export_Result\\FF\\" + path.substr(path.find("s\\") + 2, path.size());
			string export_path_FP = ".\\Reports\\Export_Result\\FP\\" + path.substr(path.find("s\\") + 2, path.size());
			string export_path_Default = ".\\Reports\\Export_Result\\DEFAULT\\" + path.substr(path.find("s\\") + 2, path.size());

			testService->ReconstructionFF_FP(path + "\\calib.txt",
				path + "\\im0.png",
				path + "\\im1.png",
				path + "\\disp0.pfm",
				export_path_FFFP + "_FF_FP.csv",
				"",
				&resultBatchFFFP);

			testService->Reconstruction_FF(path + "\\calib.txt",
				path + "\\im0.png",
				path + "\\im1.png",
				path + "\\disp0.pfm",
				export_path_FF + "_FF.csv",
				"",
				&resultBatchFF);

			testService->Reconstruction_FP(path + "\\calib.txt",
				path + "\\im0.png",
				path + "\\im1.png",
				path + "\\disp0.pfm",
				export_path_FP + "_FP.csv",
				"",
				&resultBatchFP);

			testService->Reconstruction_Default(path + "\\calib.txt",
				path + "\\im0.png",
				path + "\\im1.png",
				path + "\\disp0.pfm",
				export_path_Default + "_DEF.csv",
				"",
				&resultBatchDefault);

			i++;

			system("cls");
		}

		Export::Csv(resultBatchFFFP, ".\\Reports\\resultBatchFFFP.csv");
		Export::Csv(resultBatchFF, ".\\Reports\\resultBatchFF.csv");
		Export::Csv(resultBatchFP, ".\\Reports\\resultBatchFP.csv");
		Export::Csv(resultBatchDefault, ".\\Reports\\resultBatchDefault.csv");
	}

#pragma endregion	

}

