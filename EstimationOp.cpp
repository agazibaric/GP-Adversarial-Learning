#include <cmath>
#include "ecf/ECF.h"
#include "EstimationOp.h"
#include "cartesian/Cartesian.h"
#include <sstream>
#include <fstream>


EstimationOp::EstimationOp(DataManagerP dataManager)
{
	this->dataManager = dataManager;
}

void EstimationOp::registerParameters(StateP state)
{
	state->getRegistry()->registerEntry("nInputs", (voidP)(new uint(1)), ECF::UINT);
	state->getRegistry()->registerEntry("nOutputs", (voidP)(new uint(1)), ECF::UINT);
	state->getRegistry()->registerEntry("validationSize", (voidP)(new uint(10)), ECF::UINT);
	state->getRegistry()->registerEntry("ubound", (voidP)(new double(10)), ECF::DOUBLE);
	state->getRegistry()->registerEntry("lbound", (voidP)(new double(-10)), ECF::DOUBLE);
	state->getRegistry()->registerEntry("validationPassError", (voidP)(new double(1)), ECF::DOUBLE);
	state->getRegistry()->registerEntry("maxRounds", (voidP)(new uint(10)), ECF::UINT);
}

/*
	In Initialization target system is initialized, first random test(s) created,
	validation dataset created which will be used in Validation phase.
*/
bool EstimationOp::initialize(StateP state)
{
	if (!this->dataManager->isInitialized()) {
		// Read parameters
		voidP sptr = state->getRegistry()->getEntry("nInputs");
		nInputs = *((uint*)sptr.get());
		sptr = state->getRegistry()->getEntry("nOutputs");
		nOutputs = *((uint*)sptr.get());
		sptr = state->getRegistry()->getEntry("validationSize");
		uint validationSize = *((uint*)sptr.get());
		sptr = state->getRegistry()->getEntry("ubound");
		double ubound = *((double*)sptr.get());
		sptr = state->getRegistry()->getEntry("lbound");
		double lbound = *((double*)sptr.get());
		sptr = state->getRegistry()->getEntry("validationPassError");
		double validationPassError = *((double*)sptr.get());
		sptr = state->getRegistry()->getEntry("maxRounds");
		uint maxRounds = *((uint*)sptr.get());

		dataManager->setMaxRounds(maxRounds);
		dataManager->setValidationPassError(validationPassError);

		// Create target system
		TargetSystemP targetSystem = (TargetSystemP)(new TestSystem);
		dataManager->setTargetSystem(targetSystem);

		vector<double> input;
		vector<double> output;

		// Create first random test
		for (uint i = 0; i < nInputs; i++) {
			input.push_back(lbound + (ubound - lbound) * dataManager->randomizer->getRandomDouble());
		}
		dataManager->getTargetSystem()->evaluate(input, output);
		dataManager->addTrainingData(input, output);

		// Add validation dataset
		for (int t = 0; t < validationSize; t++) {
			vector<double> input_val;
			vector<double> output_val;

			for (uint i = 0; i < nInputs; i++) {
				input_val.push_back(lbound + (ubound - lbound) * dataManager->randomizer->getRandomDouble());
			}

			dataManager->getTargetSystem()->evaluate(input_val, output_val);
			dataManager->addValidationData(input_val, output_val);
		}

		this->dataManager->setIsInitialized(true);
	}

	return true;
}




FitnessP EstimationOp::evaluate(IndividualP individual)
{
	CGP::Cartesian* cartesian = (CGP::Cartesian*) individual->getGenotype().get();
	FitnessP fitness (new FitnessMin);
	double fitnessValue = 0;

	this->xs = dataManager->getInputs();
	this->ys = dataManager->getOutputs();

	uint nSamples = this->xs.size();
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
