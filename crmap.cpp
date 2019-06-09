#include "pch.h"
#include "stringnet.h"

double* StringNet::crmap(unsigned dis)
{
	double* res;
	res = new double[N];
	for (unsigned i = 0; i < N; i++)
	{
		//unsigned i2 = (i + dis) % N;
		if (circle_index[i] == circle_index[(i + dis) % N])
			res[i] = 1.0;
		else
			res[i] = 0.0;
	}

	return res;
}