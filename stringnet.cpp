#include "pch.h"
#include "stringnet.h"


StringNet::StringNet(unsigned tN, unsigned tM)
{
	std::random_device rd;
	gen = new std::mt19937(rd());

	M = tM;
	N = tN;
	num_jump = 0;
	num_no_jump = 0;
	max_leg = tN;
	cn = tN;
	red_square = tN;

	line_index = new vector<unsigned> *[tN];
	line_y = new vector<double> *[tN];
	line_isright = new vector<bool> *[tN];

	circle_index = new unsigned[tN];

	for (unsigned i = 0; i < tN; i++)
	{
		line_index[i] = new vector<unsigned>[tM];
		line_y[i] = new vector<double>[tM];
		line_isright[i] = new vector<bool>[tM];

		// pipe_index[i] = new vector<unsigned>[tM];
		// pipe_y[i] = new vector<double>[tM];

		circle_index[i] = i;
		if (i % 2 == 0)
			circle_red.push_back(1);
		else
			circle_red.push_back(-1);

	}

	//unsigned* temp_matrix;
	//vector<unsigned> temp_matrix = { 0,0,0,0,0,0,0,0 };
	for (unsigned i = 0; i < 2*tN*tM; i++)
	{
		//temp_matrix = new unsigned [8];
		leg.push_back(0);
		leg.push_back(0);
		leg.push_back(0);
		leg.push_back(0);
		leg.push_back(0);
		leg.push_back(0);
		leg.push_back(0);
		leg.push_back(0);
	}

	for (unsigned n = 0; n < 2*tN*tM; n++)
	{
		leg[8 * n] = 0;
		leg[8 * n + 1] = 0;
		leg[8 * n + 2] = 0;
		leg[8 * n + 3] = 0;
		leg[8 * n + 4] = 0;
		leg[8 * n + 5] = 0;
		leg[8 * n + 6] = 0;
		leg[8 * n + 7] = 0;

	}

	for (unsigned p = 0; p < N; p++)
	{
		line_index[p][0].push_back(p);
		line_y[p][0].push_back(0.0);
		line_isright[p][0].push_back(true);
		line_index[p][M - 1].push_back(p);
		line_y[p][M - 1].push_back(1.0);
		line_isright[p][M - 1].push_back(true);


		//leg[p][0] = p;
		leg[8 * p] = p;
		//leg[p][1] = 0;
		leg[8 * p + 1] = 0;
		//leg[p][2] = p;
		leg[8 * p + 2] = p;
		//leg[p][3] = 1;
		leg[8 * p + 3] = 1;
	}

}


	StringNet::~StringNet()
	{
		for (unsigned i = 0; i < N; i++)
		{
			delete[] line_index[i];
			delete[] line_y[i];
			delete[] line_isright[i];
			// delete[] pipe_index[i];
			// delete[] pipe_y[i];
		}
		delete[] line_index;
		delete[] line_y;
		delete[] line_isright;
		// delete[] pipe_index;
		// delete[] pipe_y;

		/*
		for (unsigned i = 0; i < N*M; i++)
		{
			for (auto i2 = 0; i2 < 4; i2++)
				delete[] leg[i][i2];
			delete[] leg[i];
		}
		delete[] leg;
		*/

		//for (unsigned i = 0; i < leg.size(); i++)
		//{
		//	delete[] leg[i];
		//}

		delete[] gen;

	}







