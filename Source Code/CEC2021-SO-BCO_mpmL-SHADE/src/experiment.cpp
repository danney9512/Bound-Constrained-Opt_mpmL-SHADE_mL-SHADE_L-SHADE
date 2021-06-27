
#include "experiment.h"
#include <string>

Experiment::Experiment(std::string algo_str, std::string prob_setting, std::vector<size_t> prob_ID, int dim)
{
	algo_name_ = algo_str;
	problem_id_ = prob_ID;
	problem_setting_ = prob_setting;
	dim_ = dim;
}

ExperimentSet::ExperimentSet(std::ifstream &ifile)
{
	std::string algo_str, problem_setting;
	size_t num_problem, tmp_ID;
	int dim;

	std::string dummy;
	while (ifile >> dummy)
	{
		std::vector<size_t> prob_ID = {};

		ifile >> dummy >> dummy >> num_problem;
		ifile >> dummy >> dummy;
		for (size_t i = 0; i < num_problem; ++i)
		{
			ifile >> tmp_ID;
			prob_ID.push_back(tmp_ID);
		}
		ifile >> dummy >> dummy >> problem_setting;
		ifile >> dummy >> dummy >> dim;
		ifile >> dummy >> dummy >> algo_str;
		
		exps.push_back(Experiment(algo_str, problem_setting, prob_ID, dim));
	}
}