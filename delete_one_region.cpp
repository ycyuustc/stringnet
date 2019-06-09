#include "pch.h"
#include "stringnet.h"


std::vector<double> StringNet::delete_one_region(unsigned pipe, unsigned m)
{
	std::vector<unsigned> deleted_index;
	std::vector<double> deleted_y;
	unsigned line1 = pipe;
	unsigned line2 = (pipe + 1) % N;
	auto num_leg = line_index[pipe][m].size();

	for (auto i = 0; i < num_leg; i++)
	{
		if ((line_isright[pipe][m][i]) && (line_index[pipe][m][i] >= N))
		{
			deleted_index.push_back(line_index[pipe][m][i]);
			deleted_y.push_back(line_y[pipe][m][i]);
		}
	}

	for (unsigned n : deleted_index)
	{
		delete_leg(n);
		// std::cout << "delete leg :" << n << std::endl;
	}
	auto it1 = line_index[line1][m].begin();
	auto it2 = line_y[line1][m].begin();
	auto it3 = line_isright[line1][m].begin();
	while (it2 != line_y[line1][m].end())
	{
		if ((*it3) && (*it1 >= N))
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
		if ((!(*it3)) && (*it1 >= N))
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

	/*
	vector<int> vec(100000, 888);
	for (int i = 0; i < 100000 - 10; ++i) vec.pop_back();
	cout << vec.capacity() << endl;
	vector<int>(vec).swap(vec);
	cout << vec.capacity() << endl;
	*/

	if ((line_index[line1][m].size() <= 6) && line_index[line1][m].capacity() > 6)
	{
		vector<unsigned>(line_index[line1][m]).swap(line_index[line1][m]);
		vector<double>(line_y[line1][m]).swap(line_y[line1][m]);
		vector<bool>(line_isright[line1][m]).swap(line_isright[line1][m]);
	}
	if ((line_index[line2][m].size() <= 6) && line_index[line2][m].capacity() > 6)
	{
		vector<unsigned>(line_index[line2][m]).swap(line_index[line2][m]);
		vector<double>(line_y[line2][m]).swap(line_y[line2][m]);
		vector<bool>(line_isright[line2][m]).swap(line_isright[line2][m]);
	}

	return deleted_y;
}