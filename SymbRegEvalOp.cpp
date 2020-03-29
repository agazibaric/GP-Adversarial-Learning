#include <cmath>
#include "ecf/ECF.h"
#include "SymbRegEvalOp.h"
#include "cartesian/Cartesian.h"
#include <sstream>
#include <fstream>


SymbRegEvalOp::SymbRegEvalOp(std::vector<std::vector<double>> x1, std::vector<std::vector<double>> y1) 
{
	this->xs = xs;
	this->ys = ys;
}

// called only once, before the evolution � generates training data
bool SymbRegEvalOp::initialize(StateP state)
{
	/*nSamples = 2;

	for(uint i = 0; i < nSamples; i++) {
    	x1.push_back(i);
		x2.push_back(i + 5);
		x3.push_back(nSamples - i);

		y1.push_back(2 * x1[i]);
		y2.push_back(x1[i] * x2[i] - x3[i]);
		y3.push_back(x1[i] - x2[i] + sin(x3[i]));

	}
	for(uint i = 0; i < x1.size(); ++i) {
	    std::cout << "X1: " << x1[i] << " X2: " << x2[i] << " X3: " << x3[i] << std::endl;
	}
	for(uint i = 0; i < y1.size(); ++i) {
	    std::cout << "Y1: " << y1[i] << " Y2: " << y2[i] << " Y3: " << y3[i] << std::endl;
	}*/

	return true;
}



FitnessP SymbRegEvalOp::evaluate(IndividualP individual)
{
	FitnessP fitness (new FitnessMin);

	CGP::Cartesian* cartesian = (CGP::Cartesian*) individual->getGenotype().get();

	double fitnessValue = 0;

	for (int i = 0; i < nSamples; i++) {
		std::vector<double> x = xs[i];
		std::vector<double> y_true = ys[i];
		uint N = y_true.size();
		std::vector<double> y_pred(N);
		
		cartesian->evaluate(x, y_pred);

		for (int j = 0; j < N; j++) {
			fitnessValue += fabs(y_pred[j] - y_true[j]);
		}
	}

	/*std::vector<double> result(2);
	std::vector<double> inputs(2);
	vector<std::string> buffer;

	for(uint i = 0; i < nSamples; i++)
	{
		inputs[0] = x1[i];
		inputs[1] = x2[i];
		inputs[2] = x3[i];

		cartesian->evaluate(inputs, result);

		fitnessValue += fabs(result[0] - y1[i]);
		fitnessValue += fabs(result[1] - y2[i]);
		fitnessValue += fabs(result[2] - y3[i]);
	}

	fitness->setValue(fitnessValue);
	std::cout << "Fitness value: " << fitnessValue << std::endl;
	if(fitnessValue < best_fitness) {
	    best_fitness = fitnessValue;
	    ofstream myfile;
	    myfile.open("output.txt");
	    for(int i = 0; i < buffer.size(); ++i) {
	        myfile << buffer[i];
	    }
	}
	std::cout << "Funkcija SymbRegEvalOp::evaluate() kraj."<<std::endl;*/
	return fitness;
}
