#pragma once
#include <cmath>
using namespace std;

class TargetSystem
{
public:
	TargetSystem() {};
	virtual ~TargetSystem() {};
	virtual void evaluate(vector<double>& input, vector<double>& output) = 0;

};

typedef boost::shared_ptr<TargetSystem> TargetSystemP;


template <class T>
class TestSystemT : public TargetSystem
{
public:
	TestSystemT();
	~TestSystemT();
	void evaluate(vector<T>& inputs, vector<T>& result);
};

typedef TestSystemT<double> TestSystem;

template <class T>
TestSystemT<T>::TestSystemT()
{}

template <class T>
TestSystemT<T>::~TestSystemT()
{}

template <class T>
void TestSystemT<T>::evaluate(vector<T>& inputs, vector<T>& result)
{
	result.push_back(inputs[1] * inputs[0] + sin(inputs[0]) + 1.);
}
