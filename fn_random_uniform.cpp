#include "pch.h"
#include "stringnet.h"

double StringNet::fn_random_uniform()
{
	//std::random_device rd;
	//std::mt19937 gen(rd());
	std::uniform_real_distribution<double> u(0, 1);

	return u(*gen);

}