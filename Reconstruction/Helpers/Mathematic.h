#ifndef HELPERS_MATHEMATIC
#define HELPERS_MATHEMATIC
#include <iostream>
#include <fstream>
#include <experimental/filesystem>

#include "../Algorithms/OpenCV.h"
#include "../Algorithms/OpenGL.h"
#include "../Helpers/Time.h"
#include "../Helpers/StringHelper.h"
#include "../Entities/CameraProperties.h"

namespace fs = std::experimental::filesystem;
using namespace std;
using namespace Algorithms;
using namespace Entities;

namespace Helpers {

	class Mathematic
	{
		public:
			Mathematic();
			~Mathematic();

			static double StandardDeviation(vector<double> vec);
			static double Variance(vector<double> vec);
			static double Average(vector<double> vec);
	};
}

#endif