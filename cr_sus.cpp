#include "pch.h"
#include "stringnet.h"

int StringNet::cr_sus()
{
	int* v_finished;
	v_finished = new int[N] {0};
	int res = 0;
	int res_local;
	for (unsigned i = 0; i < N; i++)
	{	
		if (v_finished[i] == 0)
		{
			if (i % 2 == 0)
				res_local = 1;
			else
				res_local = -1;

			for (unsigned j = i + 1; j < N; j++)
			{
				if (v_finished[j] == 0)
				{
					if (circle_index[j] == circle_index[i])
					{
						if (j % 2 == 0)
							res_local = res_local + 1;
						else
							res_local = res_local -1;

						v_finished[j] = 1;
					}
				}
			}
			v_finished[i] = 1;
			res = res + res_local * res_local;
			// std::cout << res_local << std::endl;
		}
	}

	return res;
}