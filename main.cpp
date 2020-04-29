#include <ecf/ECF.h>
#include "EstimationOp.h"
#include "ExplorationOp.h"
#include "cartesian/Cartesian.h"
#include "DataManager.h"


/*
	Estimation phase represents symbolic regression
	where we try to find the model that best describes training dataset.
	Model is evaluated against training dataset found so far.
*/
void estimation_phase(int argc, char **argv, DataManagerP dataManager)
{
	// Initialize and start the Estimation Phase
	StateP state_estimation(new State);
	CartesianP cgp(new CGP::Cartesian);
	state_estimation->addGenotype(cgp);

	// Get training data collected so far
	//vector<vector<double>> xs = dataManager->getInputs();
	//vector<vector<double>> ys = dataManager->getOutputs();

	//EstimationOpP explorationOp(new EstimationOp(xs, ys));
	EstimationOpP estimationOp(new EstimationOp(dataManager));
	state_estimation->setEvalOp(estimationOp);
	state_estimation->initialize(argc, argv);
	state_estimation->run();

	// Get best model and set it in DataManager to be used in next exploration phase
	vector<IndividualP> best = state_estimation->getHoF()->getBest();
	GenotypeP bestModel = best[0]->getGenotype();
	dataManager->setModel(bestModel);

}

/*
	Exploration phase tries to find the best test that will be added to the training dataset.
	It starts new evolutionary computation with genotype represented as floating point vector.
	That vector represetns input into target system. 
	Tests are evaluated against the best model found in previous estimation phase.
	When the evolutionary computation is over, the best input is recorded.
	Corresponding output is got by invoking target system with the best input.
*/
void exploration_phase(int argc, char **argv, DataManagerP dataManager) 
{
	// Initalize and start the Exploration Phase (finding best input-output pair)
	StateP state_exploration(new State);
	FloatingPointP gen(new FloatingPoint::FloatingPoint);
	state_exploration->addGenotype(gen);
	ExplorationOpP explorationOp(new ExplorationOp(dataManager));
	state_exploration->setEvalOp(explorationOp);
	state_exploration->initialize(argc, argv);
	state_exploration->run();

	// Get best test (floating point vector input)
	vector<IndividualP> best = state_exploration->getHoF()->getBest();
	FloatingPoint::FloatingPoint* bestInputFloat = (FloatingPoint::FloatingPoint*) best[0]->getGenotype().get();
	vector<double> bestInput = bestInputFloat->realValue;

	// Evaluate best input on target system and receive it's output
	vector<double> output;
	dataManager->getTargetSystem()->evaluate(bestInput, output);

	// Add new test to the training dataset
	dataManager->addTrainingData(bestInput, output);

}

/*
	In Validation phase best model found in estimation phase is tested on validation dataset.
	Results are recorded in dataManager.
*/
void validation(DataManagerP dataManager) 
{
	CGP::Cartesian* cartesian = (CGP::Cartesian*) dataManager->getModel().get();
	double maxError = dataManager->getValidationPassError();
	double error = 0.;
	uint nOutputs = cartesian->nOutputs;

	vector<vector<double>> inputs_val = dataManager->getValidationInputs();
	vector<vector<double>> outputs_val = dataManager->getValidationOutputs();

	for (int i = 0, n = inputs_val.size(); i < n; i++) {
		vector<double> x = inputs_val[i];
		vector<double> y_true = outputs_val[i];
		vector<double> y_pred;

		cartesian->evaluate(x, y_pred);

		for (int j = 0; j < nOutputs; j++) {
			error += pow(y_pred[j] - y_true[j], 2);
		}
	}

	if (error <= maxError) {
		cartesian->printFenotype();
	}

	dataManager->setValidationModel(dataManager->getModel(), error);
	dataManager->setValidationPassed(error <= maxError);
}


/*
	Adversarial Learning (Coevolution) flow:
		INITIALIZATION (done in EstimationOp::initialize)
		WHILE validation is not passed and number of rounds is less then maxRounds 
		      (or some other condition that could be managed in DataManager) DO:
			  ESTIMATION PHASE
			  EXPLORATION PHASE
			  VALIDATION PHASE
*/
int main(int argc, char **argv) 
{	
	char parameters_estimation[] = "parameters-estimation.txt";
	char parameters_exploration[] = "parameters-exploration.txt";
	
	DataManagerP dataManager(new DataManager);

	while (!dataManager->isOver()) {
		argv[1] = parameters_estimation;
		estimation_phase(argc, argv, dataManager);

		argv[1] = parameters_exploration;
		exploration_phase(argc, argv, dataManager);

		validation(dataManager);

		dataManager->roundPassed();
	}

	
	CGP::Cartesian* cartesian = (CGP::Cartesian*) dataManager->getBestValidationModel().get();
	cartesian->printFenotype();
	cout << "Validation error: " << dataManager->getBestValidationError() << endl;
	cout << "Validation passed: " << dataManager->isValidationPassed() << endl;
	cout << "Number of rounds: " << dataManager->getRoundCount() << endl;

	getchar();
	return 0;
}
