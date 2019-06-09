#include "pch.h"
#include "stringnet.h"

void StringNet::delete_leg(unsigned new_leg)
{
	unsigned left_up = leg[8 * new_leg];
	unsigned left_down = leg[8 * new_leg + 2];
	unsigned right_up = leg[8 * new_leg + 4];
	unsigned right_down = leg[8 * new_leg + 6];

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
		cn++;
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
					// stack_circle.push(v_circle2[0]);
					auto temp_index = stack_circle.top();
					stack_circle.pop();
					// auto temp_index = circle_index[v_circle1[0]];
					for (unsigned n : v_circle2)
						circle_index[n] = temp_index;
				}
				else
				{
					// stack_circle.push(v_circle1[0]);
					auto temp_index = stack_circle.top();
					stack_circle.pop();
					// auto temp_index = circle_index[v_circle2[0]];
					for (unsigned n : v_circle1)
						circle_index[n] = temp_index;
				}
			}
		}
	}

	else  //back frome the same direction
	{
		cn--;
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

	// update left up
	if (left_up < N)
	{
		leg[8 * left_up + 2] = leg[8 * new_leg + 2];
		leg[8 * left_up + 3] = leg[8 * new_leg + 3];
	}
	else
	{
		if (leg[8 * new_leg + 1] == 3)
		{
			leg[8 * left_up + 2] = leg[8 * new_leg + 2];
			leg[8 * left_up + 3] = leg[8 * new_leg + 3];
		}
		else
		{
			leg[8 * left_up + 6] = leg[8 * new_leg + 2];
			leg[8 * left_up + 7] = leg[8 * new_leg + 3];
		}
	}

	// update left down
	if (left_down < N)
	{
		leg[8 * left_down + 0] = leg[8 * new_leg + 0];
		leg[8 * left_down + 1] = leg[8 * new_leg + 1];
	}
	else
	{
		if (leg[8 * new_leg + 3] == 2)
		{
			leg[8 * left_down + 0] = leg[8 * new_leg + 0];
			leg[8 * left_down + 1] = leg[8 * new_leg + 1];
		}
		else
		{
			leg[8 * left_down + 4] = leg[8 * new_leg + 0];
			leg[8 * left_down + 5] = leg[8 * new_leg + 1];
		}
	}

	// update right up
	if (right_up < N)
	{
		leg[8 * right_up + 2] = leg[8 * new_leg + 6];
		leg[8 * right_up + 3] = leg[8 * new_leg + 7];
	}
	else
	{
		if (leg[8 * new_leg + 5] == 1)
		{
			leg[8 * right_up + 6] = leg[8 * new_leg + 6];
			leg[8 * right_up + 7] = leg[8 * new_leg + 7];
		}
		else
		{
			leg[8 * right_up + 2] = leg[8 * new_leg + 6];
			leg[8 * right_up + 3] = leg[8 * new_leg + 7];
		}
	}

	// update right down
	if (right_down < N)
	{
		leg[8 * right_down + 0] = leg[8 * new_leg + 4];
		leg[8 * right_down + 1] = leg[8 * new_leg + 5];
	}
	else
	{
		if (leg[8 * new_leg + 7] == 0)
		{
			leg[8 * right_down + 4] = leg[8 * new_leg + 4];
			leg[8 * right_down + 5] = leg[8 * new_leg + 5];
		}
		else
		{
			leg[8 * right_down + 0] = leg[8 * new_leg + 4];
			leg[8 * right_down + 1] = leg[8 * new_leg + 5];
		}
	}

	stack_leg.push(new_leg);
}