#include "pch.h"
#include "stringnet.h"


struct search_result StringNet::find_leg(unsigned line, unsigned m, double y)
{
	struct search_result res;
	unsigned tm;
	unsigned ind;

	if (line_y[line][m].empty())
	{
		res.ind = 0;

		tm = m - 1;
		while (line_index[line][tm].empty())
		{
			tm = tm - 1;
		}
		res.up = line_index[line][tm].back();
		res.up_isright = line_isright[line][tm].back();

		tm = m + 1;
		while (line_index[line][tm].empty())
		{
			tm = tm + 1;
		}
		res.down = line_index[line][tm].front();
		res.down_isright = line_isright[line][tm].front();

	}
	else
	{
		if (line_y[line][m].front() > y)
		{
			res.down = line_index[line][m].front();
			res.down_isright = line_isright[line][m].front();
			tm = m - 1;
			while (line_index[line][tm].empty())
			{
				tm = tm - 1;
			}
			res.up = line_index[line][tm].back();
			res.up_isright = line_isright[line][tm].back();
			res.ind = 0;

		}
		else if (line_y[line][m].back() < y)
		{
			res.up = line_index[line][m].back();
			res.up_isright = line_isright[line][m].back();
			tm = m + 1;
			while (line_index[line][tm].empty())
			{
				tm = tm + 1;
			}
			res.down = line_index[line][tm].front();
			res.down_isright = line_isright[line][tm].front();
			res.ind = line_index[line][m].size();
		}
		else
		{
			ind = 0;
			while (line_y[line][m][ind] < y) ind = ind + 1;
			if (line_y[line][m][ind] == y)
			{
				res.up = 0;
				res.up_isright = false;
				res.down = 0;
				res.down_isright = false;
				res.ind = 0;
				res.success = false;
				return res;
			}
			res.up = line_index[line][m][ind - 1];
			res.up_isright = line_isright[line][m][ind - 1];
			res.down = line_index[line][m][ind];
			res.down_isright = line_isright[line][m][ind];
			res.ind = ind;

		}
	}

	res.success = true;
	return res;

}