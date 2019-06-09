#include "pch.h"
#include "stringnet.h"

void StringNet::print()
{
	
	std::cout << "**************************************************************************************************************" << std::endl;
	

	/*
	std::cout << " the leg information " << std::endl;
	for (unsigned n = 0; n < N*M; n++)
	{
		//std::cout << leg[n][0][0] << leg[n][0][1] << leg[n][1][0] << leg[n][1][1] << leg[n][2][0] \
		//	<< leg[n][2][1] << leg[n][3][0] << leg[n][3][1] << std::endl;
		std::cout << leg[n][0] << leg[n][1] << leg[n][2] << leg[n][3] << leg[n][4] \
			<< leg[n][5] << leg[n][6] << leg[n][7] << std::endl;
	}

	std::cout << "M=" << M << std::endl;
	std::cout << "N=" << N << std::endl;
	*/

	std::vector<unsigned> **pipe_index;
	std::vector<double> **pipe_y;
	pipe_index = new std::vector<unsigned> *[N];
	pipe_y = new std::vector<double> *[N];
	for (auto n = 0; n < N; n++)
	{
		pipe_index[n] = new std::vector<unsigned> [M];
		pipe_y[n] = new std::vector<double> [M];
	}

	for(auto m = 0; m < M; m++)
		for (auto n = 0; n < N; n++)
		{
			for (auto k = 0; k < line_index[n][m].size(); k++)
				if ((line_isright[n][m][k])&&(line_index[n][m][k]>=N))
				{
					pipe_index[n][m].push_back(line_index[n][m][k]);
					pipe_y[n][m].push_back(line_y[n][m][k]);
				}
		}

	/**
	std::cout << "the line information" << std::endl;
	std::cout << "the position information " << std::endl;
	for (unsigned m = 0; m < M; m++)
	{
		unsigned max_insert = 0;
		for (unsigned n2 = 0; n2 < N; n2++)
			if (line_index[n2][m].size() > max_insert)
				max_insert = line_index[n2][m].size();

		std::cout << "------------------------------------------------------------------------------------------" << std::endl;
		for (unsigned n3 = 0; n3 < max_insert; n3++)
		{
			for (unsigned n = 0; n < N; n++)
			{
				if (line_index[n][m].size() <= n3)
					std::cout << setw(8) << "empty" << "\t\t";
				else
					std::cout << setw(8) << line_y[n][m][n3] << "\t\t";
			}
			std::cout << std::endl;
		}
		
	}
	std::cout << "-----------------------------------------------------------------------------------------------" << std::endl;

	std::cout << "the y position information " << std::endl;
	for (unsigned m = 0; m < M; m++)
	{
		unsigned max_insert = 0;
		for (unsigned n2 = 0; n2 < N; n2++)
			if (line_index[n2][m].size() > max_insert)
				max_insert = line_index[n2][m].size();

		std::cout << "-------------------------------------------------------------------------------------------" << std::endl;
		for (unsigned n3 = 0; n3 < max_insert; n3++)
		{
			for (unsigned n = 0; n < N; n++)
			{
				if (line_index[n][m].size() <= n3)
					std::cout << setw(8) << "empty" << "\t\t";
				else
					std::cout << setw(8) << line_index[n][m][n3] << "\t\t";
			}
			std::cout << std::endl;
		}

	}
	std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
	
	std::cout << "========================================================================" << std::endl;

	*/

	std::cout << "the pipe information" << std::endl;
	std::cout << "the position information " << std::endl;
	for (unsigned m = 0; m < M; m++)
	{
		auto max_insert = 0;
		for (unsigned n2 = 0; n2 < N; n2++)
			if (pipe_index[n2][m].size() > max_insert)
				max_insert = pipe_index[n2][m].size();

		std::cout << "-------------------------------------------------------------------------------------------" << std::endl;
		for (unsigned n3 = 0; n3 < max_insert; n3++)
		{
			for (unsigned n = 0; n < N; n++)
			{
				if (pipe_index[n][m].size() <= n3)
					std::cout << setw(8) << "empty" << "\t\t";
				else
					std::cout << setw(8) << pipe_y[n][m][n3] << "\t\t";
			}
			std::cout << std::endl;
		}

	}
	std::cout << "---------------------------------------------------------------------------------------------" << std::endl;

	std::cout << "the y position information " << std::endl;
	for (unsigned m = 0; m < M; m++)
	{
		unsigned max_insert = 0;
		for (unsigned n2 = 0; n2 < N; n2++)
			if (pipe_index[n2][m].size() > max_insert)
				max_insert = pipe_index[n2][m].size();

		std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
		for (unsigned n3 = 0; n3 < max_insert; n3++)
		{
			for (unsigned n = 0; n < N; n++)
			{
				if (pipe_index[n][m].size() <= n3)
					std::cout << setw(8) << "empty" << "\t\t";
				else
					std::cout << setw(8) << pipe_index[n][m][n3] << "\t\t";
			}
			std::cout << std::endl;
		}

	}
	std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
	std::cout << std::endl;
	std::cout << "========================================================================" << std::endl;

	std::cout << " the circle index condition: " << std::endl;
	for (auto i = 0; i < N; i++)
	{
		std::cout << circle_index[i] << "  ";
	}
	std:cout << std::endl;
	std::cout << " circle number = " << cn << std::endl;

	for (unsigned i = 0; i < N; i++)
	{
		delete[] pipe_index[i];
		delete[] pipe_y[i];
		// delete[] pipe_index[i];
		// delete[] pipe_y[i];
	}
	delete[] pipe_index;
	delete[] pipe_y;

}