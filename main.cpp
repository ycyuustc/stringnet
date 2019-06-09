#include "pch.h"
#include "stringnet.h"
#include <time.h>


using namespace std;
using namespace chrono;

int main()
{
	unsigned N = 4;
	unsigned M = 2;
	unsigned num_iter = 50000;

	SYSTEMTIME st = { 0 };
	GetLocalTime(&st);
	printf("%d-%02d-%02d %02d:%02d:%02d\n",
		st.wYear,
		st.wMonth,
		st.wDay,
		st.wHour,
		st.wMinute,
		st.wSecond);

	/*
	StringNet sn1 = StringNet(N, M);
	sn1.insert_leg(0, 0, 0.5);
	sn1.insert_leg(1, 0, 0.6);
	sn1.insert_leg(2, 0, 0.7);
	sn1.insert_leg(3, 0, 0.2);
	sn1.insert_leg(0, 0, 0.3);
	sn1.delete_leg(4);
	sn1.delete_leg(8);
	*/

	//omp_set_num_threads(1);

	// std::cout << "initialized circle number = " << sn.cn << endl;
	// std::cout << "initialized leg number = " << sn.max_leg << endl;
	string path = "E:\\vs\\sn_sus\\data\\";
	string header_name = to_string(st.wMonth) + to_string(st.wDay) + to_string(st.wHour) + to_string(st.wMinute);
	header_name = header_name + "_" + to_string(N) + "_" + to_string(M) + "_" + to_string(num_iter) + "_";

	auto start = system_clock::now();
	////////////////////////   main loop   ////////////////////////////////////////////////
#pragma omp parallel num_threads(4) 
	{
		int tid = omp_get_thread_num();
		std::random_device rd;

		double local_energy;
		StringNet sn = StringNet(N, M);
		//std::cout << sn.cr_sus() << std::endl;
		sn.sn_initial(1.0);
		//std::cout << sn.cr_sus() << std::endl;

		ofstream output1;
		ifstream input1;

		ofstream output2;
		ifstream input2;

		string file_name1 = path + header_name +  "by_step_th_" + to_string(tid) + ".txt";
		string file_name2 = path + header_name + "by_iter_th_" + to_string(tid) + ".txt";

		output1.open(file_name1, ios::out | ios::binary);
		output2.open(file_name2, ios::out | ios::binary);
		for (auto i = 0; i < num_iter; i++)
		{
			local_energy = sn.update_total(1, &output1);
			output2.write((char *)&local_energy, sizeof(double));
			if (i % 20 == 0)
			{
				printf("%d thread's %d -th iteration energy %f \n", tid, i, local_energy);
			}
			delete[] sn.gen;
			sn.gen = new std::mt19937(rd());
		}
		output1.close();
		output2.close();

		std::cout << "thread:" << tid << " jump: " << sn.num_jump << std::endl;
		std::cout << "thread:" << tid << " no jump: " << sn.num_no_jump << std::endl;
		
	}
	////////////////////////   end  main loop   //////////////////////////////////////////


	auto end = system_clock::now();
	
	auto duration = duration_cast<microseconds>(end - start);
	cout << " time spend " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "second" << endl;
	std::cout << "finished" << std::endl;
	
	return 0;

}