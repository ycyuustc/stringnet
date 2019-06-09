#include "pch.h"
#include "stringnet.h"

void StringNet::region_update(unsigned pipe, unsigned m)
{
	std::vector<unsigned> deleted_index;
	std::vector<double> deleted_y;
	unsigned line1 = pipe;
	unsigned line2 = (pipe + 1) % N;
	auto num_leg = line_index[pipe][m].size();
	auto circle0 = cn;


	for (auto i = 0; i < num_leg; i++)
	{
		if ((line_isright[pipe][m][i]) && (line_index[pipe][m][i] >= N))
		{
			deleted_index.push_back(line_index[pipe][m][i]);
			deleted_y.push_back(line_y[pipe][m][i]);
		}
	}

	for (unsigned n : deleted_index)
		delete_leg(n);

	auto it1 = line_index[line1][m].begin();
	auto it2 = line_y[line1][m].begin();
	auto it3 = line_isright[line1][m].begin();
	while (it2 != line_y[line1][m].end())
	{
		if ((*it3)&&(*it1>=N))
		{
			it1 = line_index[line1][m].erase(it1);
			it2 = line_y[line1][m].erase(it2);
			it3 = line_isright[line1][m].erase(it3);
		}
		else
		{
			++it1;
			++it2;
			++it3;
		}
	}

	it1 = line_index[line2][m].begin();
	it2 = line_y[line2][m].begin();
	it3 = line_isright[line2][m].begin();
	while (it2 != line_y[line2][m].end())
	{
		if ((!(*it3))&&(*it1>=N))
		{
			it1 = line_index[line2][m].erase(it1);
			it2 = line_y[line2][m].erase(it2);
			it3 = line_isright[line2][m].erase(it3);
		}
		else
		{
			++it1;
			++it2;
			++it3;
		}
	}


	std::vector<double> v_insert = generate_poisson(1.0);

	for (double y : v_insert)
		insert_leg(pipe, m, y);

	auto circle1 = cn;

}