#include "pch.h"
#include "stringnet.h"


std::vector<unsigned> StringNet::insert_one_region(unsigned pipe, unsigned m, double lambda)
{

	std::vector<double> vec = generate_poisson(lambda);
	std::vector<unsigned> inserted_index;

	for (double y : vec)
	{
		unsigned n = insert_leg(pipe, m, y);
		if (n!=0) inserted_index.push_back(n);
	}

	return inserted_index;
}