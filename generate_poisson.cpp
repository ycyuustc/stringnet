#include "pch.h"
#include "stringnet.h"

using namespace std;

vector<double> StringNet::generate_poisson(double lambda)
{
	//std::random_device rd;
	//auto seed = rd();
	//std::mt19937* gen;
	//gen = new std::mt19937(seed);
	//gen = new std::mt19937(rd());

	std::poisson_distribution<unsigned> d(lambda);
	std::uniform_real_distribution<double> u(0, 1);

	//double temp = d(*gen);
	unsigned num_leg = d(*gen);
	std::vector<double> v_res(num_leg);

	double ru;
	for (unsigned i = 0; i < num_leg; i++)
	{
		/*
		do
		{
			ru = u(gen);
		} while (ru == 0.0);
		v_res[i] = ru;
		*/
		v_res[i] = u(*gen);
	}
	//delete[] gen;

	return v_res;
}