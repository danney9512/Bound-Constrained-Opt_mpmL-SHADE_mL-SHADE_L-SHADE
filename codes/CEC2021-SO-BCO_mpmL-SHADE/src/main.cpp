//=========================================================================================
// Multi-population Modified L-SHADE for Single Objective Bound Constrained Optimization
// mpmL-SHADE
//=========================================================================================
// Authors     : Yann-Chern Jou
//               Shuo-Ying Wang
//               Jia-Fong Yeh
//				 Tsung-Che Chiang
// Version     : v1.2
// Created on  : Jan. 05, 2021
// Language	   : C++ (std C++17)
//
// More details on the following papers:
// CEC2021
// "Multi-population Modified L-SHADE for Single Objective Bound Constrained Optimization"(mpmL-SHADE)
// CEC2020
// "Modified L-SHADE for single objective real-parameter optimization"(mL-SHADE)
//  
//=========================================================================================

#include "problem.h"
#include "problem_set.h"
#include "problem_test_functions.h"
#include "alg_population.h"
#include "alg_base.h"
#include "alg_L-SHADE.h"
#include "alg_mL-SHADE.h"
#include "alg_mpmL-SHADE.h"
#include "alg_log.h"
#include "alg_result.h"
#include "experiment.h"
#include "self_implement_functions.h"

#include <omp.h>

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <vector>

using namespace std;


int main()
{
	// Set random seed
	srand(time(0));

	constexpr bool loadRandomSeed = false;

	// Load random seed
	vector<double> rand_seeds;
	if (loadRandomSeed)
	{
		string randomseed_filename = "input_data/_Rand_Seeds.txt";
		ifstream rand_seed_file(randomseed_filename);
		if (!rand_seed_file)
		{
			cout << "Error msg: Can't load the random seed file." << endl;
		}
		else
		{
			double tmp = 0.0;
			while (rand_seed_file >> tmp)
			{
				rand_seeds.push_back(tmp);
			}
		}
	}



	// Load experiment's setting
	string experiment_filename = "experiment_list.ini";
	ifstream exp_list_ini(experiment_filename);
	if (!exp_list_ini)
	{
		cout << "Error msg: Can't load the experiments." << endl;
		cout << "Terminate this program!" << endl;
		return 0;
	}
	ExperimentSet exp_set(exp_list_ini);
	

	// The local variables of experiments
	constexpr size_t NumOfRuns = 30;
	const double result_threshold = pow(10, -8);

	string algo_name = "", exp_setting = "";
	int problem_dim = 0;
	size_t problem_id = 0;

	BaseEA* ea = nullptr;

	// Compute time initialize
	double START, END;

	// Exp start
	cout << fixed << setprecision(15) << "==================== Experiment Start ====================" << endl << endl;
	
	START = clock();

	for (size_t i = 0; i < exp_set.size(); ++i)
	{
		// Load the parameters setting of benchmark problems for each experiment
		string problem_path = "exp_problems/" + exp_set[i].problem_setting() + "/";
		string problem_filename = problem_path + "problem_list_D" + IntToStr(exp_set[i].dim(), 2) + ".ini";

		ifstream prob_set_ini(problem_filename);
		if (!prob_set_ini)
		{
			cout << "Error msg: Can't load the problems' definition." << endl;
			cout << "Terminate this experiment!" << endl;
			break;
		}
		CPromblemSet prob_set(prob_set_ini);


		// local variables of experiment
		algo_name = exp_set[i].algo_name();
		exp_setting = exp_set[i].problem_setting();
		problem_dim = exp_set[i].dim();


		for (size_t j = 0; j < exp_set[i].problem_num(); ++j)
		{
			problem_id = exp_set[i].problem_id(j);
			prob_set[problem_id - 1].set_func_setting_name(exp_setting);


			// ********************************************* //
			// You can add your own algorithm name here ! //
			// ********************************************* //
			if (algo_name == "L-SHADE")
			{
				ea = new L_SHADE();
			}
			else if (algo_name == "mL-SHADE")
			{
				ea = new mL_SHADE();
			}
			else if (algo_name == "mpmL-SHADE")
			{
				ea = new mpmL_SHADE();
			}
			else // Skip this experiment if we can't recognize the alorithm
			{
				cout << "Error msg: Can't recognize the algorithm." << endl;
				continue;
			}


			// Loading algorithm parameter's setting
			string algo_ini_str = "experiments/" + algo_name + "/exp_CEC2021_" + IntToStr(problem_id, 2) + "_D" + IntToStr(problem_dim, 2) + ".ini";
			ifstream exp_algo_para_ini(algo_ini_str);

			if (!exp_algo_para_ini)
			{
				cout << "Error msg: Can't load the algorithm's parameters, check the .ini file's path." << endl;
			}
			else
			{
				// setting algorithm parameter
				ea->Setup(exp_algo_para_ini);

				string result_filename = algo_name + "_F" + IntToStr(problem_id, 2) + "_D" + IntToStr(problem_dim, 2) + ".csv";
				Result result(problem_id, NumOfRuns, result_filename, exp_setting);

				cout << "Experiment in F" << IntToStr(problem_id, 2) << " D" << IntToStr(problem_dim, 2) << ", " << algo_name << " solves " << prob_set[problem_id - 1].name() << " (" << exp_setting << ")" << endl;

				// Running EA
				omp_set_dynamic(0);			// Explicitly disable dynamic teams
				omp_set_num_threads(8);		// Set num of CPU thread

				#pragma omp parallel
				{
					#pragma omp for
					for (int run = 0; run < NumOfRuns; ++run)
					{
						// Set randomseed by random seed table
						/*
						size_t seed_ind = (problem_dim / 10 * problem_id * NumOfRuns + (run)) - NumOfRuns;
						seed_ind = seed_ind % 1000;

						time_t rand_seed = rand_seeds[seed_ind];
						srand(time(&rand_seed) ^ omp_get_thread_num());
						*/

						// Set random seed for each run or use time(0)
						srand(time(0) ^ omp_get_thread_num());

						Population solutions;
						solutions.setRun(run);

						ea->Solve(&solutions, prob_set[problem_id - 1]);

						result[run] = solutions[0].fitness();
						cout << "Run " << run << ", best fitness: " << solutions[0].fitness() << endl;
					}
				}

				result.compute(prob_set[problem_id - 1].global_optimum(), result_threshold);
				result.outputToFile_Result(prob_set[problem_id - 1].global_optimum(), result_threshold);
				result.outputToFile_allRuns(prob_set[problem_id - 1].global_optimum(), result_threshold, "integrated");
				result.close();

				cout << "Experiment " << j + 1 << " ended." << endl << endl;


				if (ea != nullptr) delete ea;
			}
		}
		
	}


	END = clock();
	cout << "==================== All Experiment end ====================" << endl << endl;
	cout << "Execution Time: " << (END - START) / CLOCKS_PER_SEC << " sec" << endl << endl;


	system("pause");
	return 0;
}