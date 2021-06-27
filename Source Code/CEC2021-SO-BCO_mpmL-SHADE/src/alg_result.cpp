#include "alg_result.h"
#include "self_implement_functions.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <filesystem>

Result::Result(int ID, int num_run, std::string & fileName, std::string & exp_setting)
{
	ID_ = ID;
	num_of_Run_ = num_run;
	best_fitness_vec_ = std::vector<double>(num_run, 0.0);

	if (!(std::filesystem::exists("output/"))) {
		std::filesystem::create_directory("output/");
	}

	std::string dirName = "output/" + exp_setting + "/";
	if (!(std::filesystem::exists(dirName))) 
	{
		std::filesystem::create_directory(dirName);
		std::filesystem::copy("python/ErrorValue_result.py", dirName);
	}
	
	fresult_ = std::fstream(dirName + fileName, std::ios::out | std::ios::app);
	f_all_result_ = std::fstream(dirName + IntToStr(num_of_Run_, 2) + "run_" + fileName, std::ios::out | std::ios::app);
}

void Result::compute(const double global_optimum, const double threshold)
{
	std::sort(best_fitness_vec_.begin(), best_fitness_vec_.end());

	fitness_best_ = best_fitness_vec_.front();
	fitness_worst_ = best_fitness_vec_.back();
	if (best_fitness_vec_.size() % 2 == 1)
		fitness_median_ = best_fitness_vec_[num_of_Run_ / 2];
	else
		fitness_median_ = (best_fitness_vec_[num_of_Run_ / 2] + best_fitness_vec_[num_of_Run_ / 2 - 1]) / 2;

	double sum = 0.0;
	for (size_t i = 0; i < num_of_Run_; ++i)
	{
		sum += best_fitness_vec_[i];
	}
	fitness_mean_ = sum / num_of_Run_;

	sum = 0.0;
	for (size_t i = 0; i < num_of_Run_; ++i)
	{
		sum += pow((best_fitness_vec_[i] - fitness_mean_), 2);
	}
	fitness_std_ = sqrt(sum / num_of_Run_);
	
	error_best_ = fitness_best_ - global_optimum;
	if (error_best_ <= threshold)		error_best_ = 0;
	error_worst_ = fitness_worst_ - global_optimum;
	if (error_worst_ <= threshold)	error_worst_ = 0;
	error_median_ = fitness_median_ - global_optimum;
	if (error_median_ <= threshold)	error_median_ = 0;
	error_mean_ = fitness_mean_ - global_optimum;
	if (error_mean_ <= threshold)		error_mean_ = 0;

	sum = 0.0;
	for (size_t i = 0; i < num_of_Run_; ++i)
	{
		double error_tmp = best_fitness_vec_[i] - global_optimum;
		if (error_tmp <= pow(10, -8))	error_tmp = 0;

		sum += pow((error_tmp - error_mean_), 2);
	}
	error_std_ = sqrt(sum / num_of_Run_);

	std::cout << "Fitness     Best: " << fitness_best_ << ", worst: " << fitness_worst_ << ", median: " << fitness_median_ << ", mean: " << fitness_mean_ << ", std: " << fitness_std_ << std::endl;
	std::cout << "ErrorValue  Best: " << error_best_ << ", worst: " << error_worst_ << ", median: " << error_median_ << ", mean: " << error_mean_ << ", std: " << error_std_ << std::endl;

}

void Result::outputToFile_Result(const double global_optimum, const double threshold)
{
	// output results to fresult_
	fresult_ << ID_ << ",";
	fresult_ << std::setprecision(16) << error_best_ << ",";
	fresult_ << std::setprecision(16) << error_worst_ << ",";
	fresult_ << std::setprecision(16) << error_median_ << ",";
	fresult_ << std::setprecision(16) << error_mean_ << ",";
	fresult_ << std::setprecision(16) << error_std_ << ",";
	fresult_ << std::endl;
}

void Result::outputToFile_allRuns(const double global_optimum, const double threshold, const std::string mode)
{
	// all runs fitness error values after sorting
	// integrated:	separate the result data into two different column, the first col. is the value after normalization, the second col. is the primitive data
	// primitive:	the primitive errorvalue data
	// default:		the normalization errorvalue data

	int codename = 0;
	if (mode == "integrated")	codename = 1;
	else if (mode == "primitive")	codename = 2;
	else	codename = 0;	// default

	for (int i = 0; i < best_fitness_vec_.size(); ++i)
	{
		switch(codename)
		{
		case 1:		// integrated
		{
			double tmp = best_fitness_vec_[i] - global_optimum;
			double tmp_n = tmp;
			if (tmp_n < threshold)
				tmp_n = 0;

			f_all_result_ << std::setprecision(16) << tmp_n << "," << tmp << std::endl;
			break;
		}
		case 2:		// primitive
		{
			double tmp = best_fitness_vec_[i] - global_optimum;

			f_all_result_ << std::setprecision(16) << tmp << std::endl;
			break;
		}
		default:	// default
		{
			double tmp_n = best_fitness_vec_[i] - global_optimum;
			if (tmp_n < threshold)
				tmp_n = 0;

			f_all_result_ << std::setprecision(16) << tmp_n << std::endl;
			break;
		}
		}
	}
}


void Result::close()
{
	fresult_.close();
	f_all_result_.close();
}