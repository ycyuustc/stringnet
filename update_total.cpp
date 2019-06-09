#include "pch.h"
#include "stringnet.h"

double StringNet::update_total(unsigned dis) //ofstream* output)
{
	double sum_up = 0.0;
	double local_value;

	for (unsigned n = 0; n < N; n++)
	{
		for (unsigned m = 0; m < M; m++)
		{
			update_region(n, m);	
		}
	}
	return double(cr_sus())/double(N);
}


double StringNet::update_total(unsigned dis, ofstream* output)
{
	double sum_up = 0.0;
	double local_value;

	for (unsigned n = 0; n < N; n++)
	{
		for (unsigned m = 0; m < M; m++)
		{
			// local_value = -1.5 * double(cr_energy(1)) / N - 0.5;
			//sum_up += local_value;
			// output->write((char *)&local_value, sizeof(double));
			//local_value = double(cr_sus()) / N;
			//sum_up += local_value;
			//output->write((char *)&local_value, sizeof(double));
			update_region(n, m);
			local_value = double(cr_sus()) / N;	
			output->write((char *)&local_value, sizeof(double));
		}
		// if (n % 10 == 0) std::cout << n << std::endl;
		//local_value = double(cr_sus()) / N;
		//output->write((char *)&local_value, sizeof(double));
	}

	// return sum_up / N / M; 
	// return -1.5 * double(cr_energy(1)) / N - 0.5;
	// return cn;
	
	return double(cr_sus()) / double(N);
}