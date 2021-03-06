#include "stdafx.h"
#include "Mathematic.h"

namespace Helpers {

	Mathematic::Mathematic()
	{

	}

	Mathematic::~Mathematic()
	{
	}

	double Mathematic::Variance(vector<double> vec)
	{
		int size = vec.size();

		double variance = 0;
		double t = vec[0];
		for (int i = 1; i < size; i++)
		{
			t += vec[i];
			double diff = ((i + 1) * vec[i]) - t;
			variance += (diff * diff) / ((i + 1.0) *i);
		}

		return variance / (size - 1);
	}

	double Mathematic::Average(vector<double> vec)
	{
		double average = 0.0;

		for each (double item in vec)
		{
			average += item;
		}

		return average / vec.size();
	}

	double Mathematic::StandardDeviation(vector<double> vec)
	{
		return sqrt(Variance(vec));
	}

}