#include <cmath>
#include "ecf/ECF.h"
#include "EstimationOp.h"
#include "cartesian/Cartesian.h"
#include <sstream>
#include <fstream>


EstimationOp::EstimationOp(vector<vector<double>> x1, vector<vector<double>> y1)
{
	this->xs = x1;
	this->ys = y1;
}


bool EstimationOp::initialize(StateP state)
{
	nSamples = xs.size();
	return true;
}


FitnessP EstimationOp::evaluate(IndividualP individual)
{
	CGP::Cartesian* cartesian = (CGP::Cartesian*) individual->getGenotype().get();
	FitnessP fitness (new FitnessMin);
	double fitnessValue = 0;

	for (int i = 0; i < nSamples; i++) {
		vector<double> x = xs[i];
		vector<double> y_true = ys[i];
		vector<double> y_pred;
		
		cartesian->evaluate(x, y_pred);

		for (int j = 0, n = y_true.size(); j < n; j++) {
			//fitnessValue += fabs(y_pred[j] - y_true[j]);
			fitnessValue += pow(y_pred[j] - y_true[j], 2);
		}
	}

	fitness->setValue(fitnessValue);
	return fitness;
}
