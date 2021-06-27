#ifndef EXPERIMENT__
#define EXPERIMENT__

#include <fstream>
#include "alg_base.h"
#include <vector>

class Experiment
{
public:
	explicit Experiment(std::string algo_str = "", std::string prob_setting = "", std::vector<size_t> prob_ID = {}, int dim = 0);
	const std::string & algo_name() const { return algo_name_; }
	const std::string & problem_setting() const { return problem_setting_; }
	const std::vector<size_t> & problem_id() const { return problem_id_; }
	const size_t & problem_id(const size_t i) const { return problem_id_[i]; }
	const size_t problem_num() const { return problem_id_.size(); }
	const int & dim() const { return dim_; }

private:
	std::string algo_name_;
	std::vector<size_t> problem_id_;
	std::string problem_setting_;
	int dim_;
};

class ExperimentSet
{
public:
	explicit ExperimentSet(std::ifstream &ifile);

	Experiment & operator[](std::size_t i) { return exps[i]; }
	const Experiment & operator[](std::size_t i) const { return exps[i]; }

	std::size_t size() const { return exps.size(); }
	bool empty() const { return size() == 0; }
	void resize(std::size_t t) { exps.resize(t); }
	void push_back(const Experiment &exp) { exps.push_back(exp); }
	void clear() { exps.clear(); }
private:
	std::vector<Experiment> exps;
};


#endif // !EXPERIMENT__
