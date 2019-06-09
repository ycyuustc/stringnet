#include "pch.h"
#include "stringnet.h"

bool StringNet::update_region(unsigned pipe, unsigned m)
{
	//std::random_device rd;
	//std::mt19937 gen(rd());
	//std::uniform_real_distribution<double> u(0, 1);
	bool isjump;
	unsigned circle0 = cn;
	std::vector<double> deleted_y = delete_one_region(pipe, m);
	std::vector<unsigned> inserted_index = insert_one_region(pipe, m, 1.0);
	unsigned circle1 = cn;
	

	if (circle1 >= circle0)
	{
		++num_jump;
		isjump = true;
	}
	else
	{
		if (fn_random_uniform() < pow(0.5, double(circle0 - circle1)))
		{
			// std::cout << double(circle0 - circle1) << std::endl;
			++num_jump;
			isjump = true;
		}
		else
		{
			++num_no_jump;
			isjump = false;
			delete_one_region_by_vec(pipe, m, inserted_index);
			insert_one_region_by_vec(pipe, m, deleted_y);
		}
	}

	return isjump;
}