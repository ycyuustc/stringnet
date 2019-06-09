#include "pch.h"
#include "stringnet.h"

unsigned StringNet::insert_leg(unsigned pipe, unsigned m, double y)
{
	unsigned line1 = pipe;
	unsigned line2 = (pipe + 1) % N;
	struct search_result res1 = find_leg(line1, m, y);
	struct search_result res2 = find_leg(line2, m, y);

	if (!(res1.success && res2.success))
	{
		std::cout << "dangerous!!! y position: " << y << " pipe = " << pipe << " m = " << m << std::endl;
		return 0;
	}

	unsigned new_leg;
	if (stack_leg.empty())
	{
		new_leg = max_leg;
		max_leg++;	
	}
	else
	{
		new_leg = stack_leg.top();
		stack_leg.pop();
	}

	if (8 * new_leg >= leg.size())
	{
		leg.push_back(0);
		leg.push_back(0);
		leg.push_back(0);
		leg.push_back(0);
		leg.push_back(0);
		leg.push_back(0);
		leg.push_back(0);
		leg.push_back(0);
	}

	auto left_up = res1.up;
	auto left_down = res1.down;
	auto right_up = res2.up;
	auto right_down = res2.down;
	auto left_up_isright = res1.up_isright;
	auto left_down_isright = res1.down_isright;
	auto right_up_isright = res2.up_isright;
	auto right_down_isright = res2.down_isright;
	auto left_ind = res1.ind;
	auto right_ind = res2.ind;

		
	// update the left up leg:
	if (left_up < N)
	{
		leg[8 * left_up + 2] = new_leg;
		leg[8 * left_up + 3] = 2;
		leg[8 * new_leg + 0] = left_up;
		leg[8 * new_leg + 1] = 0;
	}
	else
	{
		if (left_up_isright)
		{
			leg[8 * left_up + 2] = new_leg;
			leg[8 * left_up + 3] = 2;
			leg[8 * new_leg + 0] = left_up;
			leg[8 * new_leg + 1] = 3;
		}
		else
		{
			leg[8 * left_up + 6] = new_leg;
			leg[8 * left_up + 7] = 2;
			leg[8 * new_leg + 0] = left_up;
			leg[8 * new_leg + 1] = 1;
		}
	}

	//update the left down:
	if (left_down < N)
	{
		leg[8 * left_down + 0] = new_leg;
		leg[8 * left_down + 1] = 3;
		leg[8 * new_leg + 2] = left_down;
		leg[8 * new_leg + 3] = 1;
	}
	else
	{
		if (left_down_isright)
		{
			leg[8 * left_down + 0] = new_leg;
			leg[8 * left_down + 1] = 3;
			leg[8 * new_leg + 2] = left_down;
			leg[8 * new_leg + 3] = 2;
		}
		else
		{
			leg[8 * left_down + 4] = new_leg;
			leg[8 * left_down + 5] = 3;
			leg[8 * new_leg + 2] = left_down;
			leg[8 * new_leg + 3] = 0;
		}
	}

	// update the right up:
	if (right_up < N)
	{
		leg[8 * right_up + 2] = new_leg;
		leg[8 * right_up + 3] = 0;
		leg[8 * new_leg + 4] = right_up;
		leg[8 * new_leg + 5] = 0;
	}
	else
	{
		if (!right_up_isright)
		{
			leg[8 * right_up + 6] = new_leg;
			leg[8 * right_up + 7] = 0;
			leg[8 * new_leg + 4] = right_up;
			leg[8 * new_leg + 5] = 1;
		}
		else
		{
			leg[8 * right_up + 2] = new_leg;
			leg[8 * right_up + 3] = 0;
			leg[8 * new_leg + 4] = right_up;
			leg[8 * new_leg + 5] = 3;
		}
	}

	//update the right down:
	if (right_down < N)
	{
		leg[8 * right_down + 0] = new_leg;
		leg[8 * right_down + 1] = 1;
		leg[8 * new_leg + 6] = right_down;
		leg[8 * new_leg + 7] = 1;
	}
	else
	{
		if (!right_down_isright)
		{
			leg[8 * right_down + 4] = new_leg;
			leg[8 * right_down + 5] = 1;
			leg[8 * new_leg + 6] = right_down;
			leg[8 * new_leg + 7] = 0;
		}
		else
		{
			leg[8 * right_down + 0] = new_leg;
			leg[8 * right_down + 1] = 1;
			leg[8 * new_leg + 6] = right_down;
			leg[8 * new_leg + 7] = 2;
		}
	}

	// begin from the left_up direction to run a circle:
	direction = 0;
	ind = new_leg;
	v_circle1.clear();
	v_circle2.clear();
	unsigned ind0;
	while (true)
	{
		ind0 = ind;
		ind = leg[8 * ind0 + 2 * direction];
		direction = leg[8 * ind0 + 2 * direction + 1];

		if (ind < N) v_circle1.push_back(ind);
		if (ind == new_leg) break;
	}

	if (direction != 0)  //back from the different direction
	{
		cn--;
		if (!v_circle1.empty())
		{
			direction = 2;
			ind = new_leg;
			while (true)
			{
				ind0 = ind;
				ind = leg[8 * ind0 + 2 * direction];
				direction = leg[8 * ind0 + 2 * direction + 1];

				if (ind < N) v_circle2.push_back(ind);
				if (ind == new_leg) break;
			}
			if (!v_circle2.empty())
			{
				if (v_circle1.size() >= v_circle2.size())
				{
					stack_circle.push(circle_index[v_circle2[0]]);
					auto temp_index = circle_index[v_circle1[0]];
					for (unsigned n : v_circle2)
						circle_index[n] = temp_index;
				}
				else
				{
					stack_circle.push(circle_index[v_circle1[0]]);
					auto temp_index = circle_index[v_circle2[0]];
					for (unsigned n : v_circle1)
						circle_index[n] = temp_index;
				}
			}
		}
	}

	else  //back frome the same direction
	{
		cn++;
		if (!v_circle1.empty())
		{
			direction = 1;
			ind = new_leg;
			while (true)
			{
				ind0 = ind;
				ind = leg[8 * ind0 + 2 * direction];
				direction = leg[8 * ind0 + 2 * direction + 1];

				if (ind < N) v_circle2.push_back(ind);
				if (ind == new_leg) break;
			}
			if (!v_circle2.empty())
			{
				if (v_circle1.size() >= v_circle2.size())
				{
					unsigned temp_index = stack_circle.top();
					stack_circle.pop();
					for (unsigned n : v_circle2)
						circle_index[n] = temp_index;
				}
				else
				{
					unsigned temp_index = stack_circle.top();
					stack_circle.pop();
					for (unsigned n : v_circle1)
						circle_index[n] = temp_index;
				}
			}
		}

	}

	// update the line_index, line_y, line_isright 
	line_index[line1][m].insert(line_index[line1][m].begin() + left_ind, new_leg);
	line_y[line1][m].insert(line_y[line1][m].begin() + left_ind, y);
	line_isright[line1][m].insert(line_isright[line1][m].begin() + left_ind, true);

	line_index[line2][m].insert(line_index[line2][m].begin() + right_ind, new_leg);
	line_y[line2][m].insert(line_y[line2][m].begin() + right_ind, y);
	line_isright[line2][m].insert(line_isright[line2][m].begin() + right_ind, false);

	/*
	std::cout << line1 << "  " << line2 << "  " << m << std::endl;
	for (auto nn : line_index[line1][m])
		std::cout << nn << std::endl;
	for (auto nn : line_y[line1][m])
		std::cout << nn << std::endl;
	std::cout << " ================================ " << std::endl;
	for (auto nn : line_index[line2][m])
		std::cout << nn << std::endl;
	for (auto nn : line_y[line2][m])
		std::cout << nn << std::endl;
	std::cout << " ================================ " << std::endl;
	*/


	return new_leg;

}