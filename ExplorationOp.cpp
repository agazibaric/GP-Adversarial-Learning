#include "ExplorationOp.h"


ExplorationOp::ExplorationOp(DataManagerP dataManager)
{
	this->dataManager = dataManager;
}


bool ExplorationOp::initialize(StateP)
{
	return true;
}


FitnessP ExplorationOp::evaluate(IndividualP individual)
{
	FitnessP fitness(new FitnessMax);

	FloatingPoint::FloatingPoint* inputFloat = (FloatingPoint::FloatingPoint*) individual->getGenotype().get();
	vector<double> input = inputFloat->realValue;
	vector<double> pred_output;
	vector<double> real_output;

	// Get predicted output
	CGP::Cartesian* model = (CGP::Cartesian*) dataManager->getModel().get();
	model->evaluate(input, pred_output);

	// Get real output
	dataManager->getTargetSystem()->evaluate(input, real_output);

	double error = 0.;
	for (int i = 0, n = pred_output.size(); i < n; i++) {
		error += pow(pred_output[i] - real_output[i], 2);
	}

	fitness->setValue(error);
	return fitness;

}
