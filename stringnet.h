#pragma once
// test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"


using namespace std;
using std::vector;

//extern ofstream output;
//extern ifstream input;
//extern ofstream output2;
//extern ifstream input2;

//extern std::random_device rd;
//extern std::mt19937 gen;


typedef struct search_result
{
	unsigned up;
	unsigned down;
	unsigned ind;
	bool up_isright;
	bool down_isright;
	bool success;
}search_result;


class StringNet
{
public:
	// the variables: ======================================================================
	unsigned N;
	unsigned M;
	unsigned num_jump;
	unsigned num_no_jump;
	vector<unsigned> **line_index; // the information of the index of leg
	vector<double> **line_y;
	vector<bool> **line_isright;
	vector<unsigned> leg;
	//vector<vector<unsigned>> leg;
	// vector<unsigned> **pipe_index;
	// vector<double> **pipe_y;
	//unsigned ***leg;
	// double *leg_betay;

	unsigned *circle_index;
	vector<int> circle_red;
	std::stack<unsigned> stack_leg;
	std::stack<unsigned> stack_circle;
	unsigned max_leg;
	unsigned cn;
	int red_square;

	// temperate variables: 
	unsigned direction;
	unsigned ind;
	unsigned ind0;
	vector<unsigned> v_circle1;
	vector<unsigned> v_circle2;

	//std::random_device rd;
	//std::mt19937 gen;
	std::mt19937* gen;

	// the functions :  =================================================================
	void print();
	struct search_result find_leg(unsigned line, unsigned m, double y);
	unsigned insert_leg(unsigned pipe, unsigned m, double y);
	void delete_leg(unsigned new_leg);
	void region_update(unsigned pipe, unsigned m);
	bool update_region(unsigned pipe, unsigned m);
	vector<double> delete_one_region(unsigned pipe, unsigned m);
	void delete_one_region_by_vec(unsigned pipe, unsigned m, vector<unsigned> vec);
	vector<unsigned> insert_one_region(unsigned pipe, unsigned m, double lambda);
	vector<unsigned> insert_one_region_by_vec(unsigned pipe, unsigned m, vector<double> vec);
	void sn_initial(double lambda);
	double update_total(unsigned dis); //, ofstream* output);
	double update_total(unsigned dis, ofstream* output);
	double* crmap(unsigned dis);
	int cr_energy(unsigned dis);
	int cr_sus();
	double fn_random_uniform();
	double fn_random_poisson(double lambda);
	vector<double> generate_poisson(double lambda);

	StringNet(unsigned tN, unsigned tM);
	~StringNet();
	
};



