#include "pch.h"
#include "stringnet.h"

int StringNet::cr_energy(unsigned dis)
{
	int sum_up = 0;
	for (unsigned i = 0; i < N; i++)
	{
		if (circle_index[i] == circle_index[(i + dis) % N])
			sum_up += 1;
	}

	return sum_up;
}