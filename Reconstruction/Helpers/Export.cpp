#include "stdafx.h"
#include "Export.h"

namespace Helpers {

	Export::Export()
	{

	}
	
	Export::~Export()
	{
	}
	
	bool Export::Json(vector<Point3f> listPoints, string pathDirectory)
	{
		try
		{
			int raiz = sqrt(listPoints.size());
			int column = raiz + 1, line = listPoints.size();
			int range = raiz;
			if (raiz > 10)
				range = raiz * 0.8;
			if (raiz > 100)
				range = raiz * 0.4;
			if (raiz > 1000)
				range = raiz * 0.005;
			if (raiz > 10000)
				range = raiz * 0.0005;

			int bestLine = raiz, bestColumn = raiz;
			while (range > 0) {
				if (column * line < listPoints.size()) {
					bestLine = line;
					bestColumn = column;
				}
				column--;
				line++;
				range--;
			}

			ofstream file;
			file.open(pathDirectory + "\\stereoCameraCalibration.json");
			file << "{\"Column\": " + to_string(bestColumn);
			file << ", ";
			file << "\"Line\": " + to_string(bestLine);
			file << ", ";
			file << "\"Values\": [";
			for each (Point3f item in listPoints)
			{
				file << "{ " << "\"X\": " << item.x << ", \"Y\": " << item.y << ", \"Z\": " << item.z << "},";
			}
			file << "]}";
			file.close();
		}
		catch (const std::exception&)
		{
			return false;
		}

		return true;
	}

	bool Export::Obj(vector<Point3f> listPoints, string pathDirectory)
	{
		try
		{
			int raiz = sqrt(listPoints.size());
			int column = raiz + 1, line = listPoints.size();
			int range = raiz;
			if (raiz > 10)
				range = raiz * 0.8;
			if (raiz > 100)
				range = raiz * 0.4;
			if (raiz > 1000)
				range = raiz * 0.005;
			if (raiz > 10000)
				range = raiz * 0.0005;

			int bestLine = raiz, bestColumn = raiz;
			while (range > 0) {
				if (column * line < listPoints.size()) {
					bestLine = line;
					bestColumn = column;
				}
				column--;
				line++;
				range--;
			}

			ofstream file;
			file.open(pathDirectory + "\\stereoCameraCalibration.obj");
			file << "L " << to_string(bestLine) << endl;
			file << "C " << to_string(bestColumn) << endl;

			for each (Point3f item in listPoints)
			{
				file << "v " << item.x << " " << item.y << " " << item.z << endl;
			}

			file.close();
		}
		catch (const std::exception&)
		{
			return false;
		}

		return true;
	}

	bool Export::Obj(vtkActor * vtkActor, string pathDirectory)
	{
		try
		{
			ExportVtk().ExportObj(vtkActor, pathDirectory);

			return true;
		}
		catch (const std::exception& ex)
		{
			cout << "Exception Export VTK obj: " << ex.what() << endl;
			return false;
		}
	}

	bool Export::Csv(Helpers::Time time, string pathDirectory)
	{
		try
		{
			vector<TimeExecution> list = time.Get();
			vector<vector<string>> excelValues;
			string exportText = "";
			int maxQtd = 0;
			ofstream file;

			file.open(pathDirectory);
			if (file.is_open()) {
				// setting columns name on csv
				for (int i = 0; i < list.size(); i++)
				{
					exportText += list[i].GetName();
					int sizeMethod = list[i].Get().size();
					if (sizeMethod > maxQtd)
						maxQtd = sizeMethod;

					if ((i + 1) != list.size()) {
						exportText += Splitter;
					}
				}
				exportText += "\n";

				// bulding matriz
				for (int i = 0; i < list.size(); i++)
				{
					// each method
					vector<long> listTimes = list[i].Get();
					for (int j = 0; j < listTimes.size(); j++)
					{
						// each time inside each method
						if (excelValues.size() <= j)
							excelValues.push_back(*new vector<string>());

						excelValues[j].push_back(to_string(listTimes[j]));
					}
				}

				// setting values on csv
				for each (vector<string> row in excelValues)
				{
					for each (string col in row)
					{
						exportText += col + Splitter;
					}

					exportText += "\n";
				}

				file << exportText;
				
				file.close();
			}
						
			return true;
		}
		catch (const std::exception& ex)
		{
			cout << "Exception Export CSV: " << ex.what() << endl;
			return false;
		}
	}

	bool Export::Csv(vector<ReconstructionComparison> reconstructionComparison, string pathDirectory, string coordinates)
	{
		try
		{
			if (coordinates == "")
				throw exception("Coordinates cannot be null or empty");

			string exportText = "";
			string data = "";
			bool exportLine = true;
			ofstream file;

			file.open(pathDirectory);
			if (file.is_open()) {
				// setting header
				for (char& c : coordinates) {
					string coord(&c);
					string header = "Reconstruction Coord " + coord + Splitter + "Map Coord " + coord + Splitter + "Error " + coord + Splitter;

					StringHelper::Append(exportText, header);
				}

				StringHelper::Append(exportText, "\n");

				// setting data
				for each (ReconstructionComparison item in reconstructionComparison)
				{
					exportLine = true;

					for (char& c : coordinates) {
						switch (c)
						{
							case 'x':
								if (isinf(item.Reconstruction.x) || isinf(item.Map.x) || isinf(item.Error.x)) {
									exportLine = false;
									continue;
								}

								data = to_string(item.Reconstruction.x) + Splitter + to_string(item.Map.x) + Splitter + to_string(item.Error.x) + Splitter;
								break;
							case 'y':
								if (isinf(item.Reconstruction.y) || isinf(item.Map.y) || isinf(item.Error.y)) {
									exportLine = false;
									continue;
								}

								data = to_string(item.Reconstruction.y) + Splitter + to_string(item.Map.y) + Splitter + to_string(item.Error.y) + Splitter;
								break;
							case 'z':
								if (isinf(item.Reconstruction.z) || isinf(item.Map.z) || isinf(item.Error.z)) {
									exportLine = false;
									continue;
								}

								data = to_string(item.Reconstruction.z) + Splitter + to_string(item.Map.z) + Splitter + to_string(item.Error.z) + Splitter;
								break;
						}

						if (exportLine) {
							std::replace(data.begin(), data.end(), '.', ',');
							StringHelper::Append(exportText, data);
						}
					}
					
					if(exportLine)
						StringHelper::Append(exportText, "\n");
				}
			}

			file << exportText;

			file.close();

			return true;
		}
		catch (const std::exception& ex)
		{
			cout << "Exception Export CSV: " << ex.what() << endl;
			return false;
		}
	}

	bool Export::Csv(map<string, double> result, string pathDirectory)
	{
		try {
			string exportText = "";
			string data = "";
			bool exportLine = true;
			ofstream file;

			file.open(pathDirectory);
			if (file.is_open()) {
				// setting header
				string header = "Image" + Splitter + "Error" + Splitter + "\n";
				StringHelper::Append(exportText, header);

				// setting data
				map<string, double>::iterator it;
				for (it = result.begin(); it != result.end(); it++)
				{
					// it->first(key) / it->second(value)
					string error = to_string(it->second);
					std::replace(error.begin(), error.end(), '.', ',');
					StringHelper::Append(exportText, it->first + Splitter + error + Splitter + "\n");
				}
			}
			
			file << exportText;
			file.close();

			return true;
		}
		catch (const std::exception& ex)
		{
			cout << "Exception Export CSV: " << ex.what() << endl;
			return false;
		}
	}

	bool Export::Csv(map<string, AverageDeviationStd*> result, string pathDirectory)
	{
		try {
			string exportText = "";
			string data = "";
			bool exportLine = true;
			ofstream file;

			file.open(pathDirectory);
			if (file.is_open()) {
				// setting header
				string header = "Image" + Splitter + "Average" + Splitter +"Standard Deviation" + Splitter + "\n";
				StringHelper::Append(exportText, header);

				// setting data
				map<string, AverageDeviationStd*>::iterator it;
				for (it = result.begin(); it != result.end(); it++)
				{
					// it->first(key) / it->second(value)
					string average = to_string(it->second->Average);
					string deviation = to_string(it->second->Deviation);
					std::replace(average.begin(), average.end(), '.', ',');
					std::replace(deviation.begin(), deviation.end(), '.', ',');
					StringHelper::Append(exportText, it->first + Splitter + average + Splitter + deviation + Splitter + "\n");
				}
			}

			file << exportText;
			file.close();

			return true;
		}
		catch (const std::exception& ex)
		{
			cout << "Exception Export CSV: " << ex.what() << endl;
			return false;
		}
	}
}