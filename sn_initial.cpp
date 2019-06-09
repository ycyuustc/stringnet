#include "pch.h"
#include "stringnet.h"

void StringNet::sn_initial(double lambda)
{
	for (unsigned n = 0; n < N; n++)
	{
		for (unsigned m = 0; m < M; m++)
		{
			std::vector<double> vec = generate_poisson(lambda);
			for (double y : vec)
			{

				insert_leg(n, m, y);
				// std::cout << "circle number now =" << cn << std::endl;
			}

		}
		// if (n % 10 == 0) std::cout << n << std::endl;
	}
}