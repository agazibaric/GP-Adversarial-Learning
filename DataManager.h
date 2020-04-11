#ifndef DataManager_h
#define DataManager_h
#include <ecf/ECF.h>
#include <./target_system/TargetSystem.h>

class DataManager
{
public:

	DataManager();

	~DataManager();

	bool isOver();

	void roundPassed();

	void setModel(GenotypeP model);

	GenotypeP getModel();

	void setInput(vector<vector<double>> inputs);

	void setOutput(vector<vector<double>> outputs);

	vector<vector<double>> getInputs();

	vector<vector<double>> getOutputs();

	void addTrainingData(vector<double> input, vector<double> output);
	
	void setTargetSystem(TargetSystemP targetSystem);

	TargetSystemP getTargetSystem();

	void setMaxRounds(uint maxRounds);

	uint getMaxRounds();

	uint getRoundCount();

	vector<vector<double>> getValidationInputs();

	vector<vector<double>> getValidationOutputs();

	void addValidationData(vector<double> input, vector<double> output);

	void setValidationInput(vector<vector<double>> inputs);

	void setValidationOutput(vector<vector<double>> outputs);

	bool isValidationPassed();

	void setValidationPassed(bool validationPassed);

	void setValidationModel(GenotypeP model, double error);

	GenotypeP getBestValidationModel();

	double getBestValidationError();


private:
	// Training dataset
	vector<vector<double>> inputs;
	vector<vector<double>> outputs;

	// Validation dataset
	vector<vector<double>> inputs_val;
	vector<vector<double>> outputs_val;

	GenotypeP model;
	GenotypeP bestValidationModel = NULL;
	TargetSystemP targetSystem;
	uint roundCount = 0;
	uint maxRounds;
	bool validationPassed = false;
	double bestValidationError;
};

typedef boost::shared_ptr<DataManager> DataManagerP;


#endif 