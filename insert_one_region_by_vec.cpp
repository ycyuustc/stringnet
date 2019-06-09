#include "pch.h"
#include "stringnet.h"


std::vector<unsigned> StringNet::insert_one_region_by_vec(unsigned pipe, unsigned m, std::vector<double> vec)
{
	std::vector<unsigned> inserted_index;

	for (double y : vec)
	{
		unsigned n = insert_leg(pipe, m, y);
		if (n != 0) inserted_index.push_back(n);
	}

	return inserted_index;
}