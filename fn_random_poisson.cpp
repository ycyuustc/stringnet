#include "pch.h"
#include "stringnet.h"

double StringNet::fn_random_poisson(double lambda)
{
	//std::random_device rd;
	//std::mt19937 gen(rd());
	std::poisson_distribution<unsigned> d(lambda);
	
	return d(*gen);
}