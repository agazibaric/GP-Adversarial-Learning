#include "DataManager.h"


DataManager::DataManager() {
	this->randomizer = (RandomizerP)(new SimpleRandomizer);
}

DataManager::~DataManager() {}

bool DataManager::isOver()
{
	return initialized && (roundCount >= maxRounds || validationPassed);
}

void DataManager::roundPassed()
{
	roundCount++;
}

void DataManager::setModel(GenotypeP model)
{
	this->model = model;
	if (this->bestValidationModel == NULL) {
		this->bestValidationModel = model;
	}
}

GenotypeP DataManager::getModel()
{
	return this->model;
}

void DataManager::setInput(vector<vector<double>> inputs)
{
	this->inputs = inputs;
}

void DataManager::setOutput(vector<vector<double>> outputs)
{
	this->outputs = outputs;
}

vector<vector<double>> DataManager::getInputs()
{
	return inputs;
}

vector<vector<double>> DataManager::getOutputs()
{
	return outputs;
}

void DataManager::addTrainingData(vector<double> input, vector<double> output)
{
	inputs.push_back(input);
	outputs.push_back(output);
}

void DataManager::setTargetSystem(TargetSystemP targetSystem)
{
	this->targetSystem = targetSystem;
}

TargetSystemP DataManager::getTargetSystem()
{
	return this->targetSystem;
}

void DataManager::setMaxRounds(uint maxRounds)
{
	this->maxRounds = maxRounds;
}

uint DataManager::getMaxRounds()
{
	return this->maxRounds;
}

uint DataManager::getRoundCount()
{
	return this->roundCount;
}

vector<vector<double>> DataManager::getValidationInputs()
{
	return this->inputs_val;
}

vector<vector<double>> DataManager::getValidationOutputs()
{
	return this->outputs_val;
}

void DataManager::addValidationData(vector<double> input, vector<double> output)
{
	inputs_val.push_back(input);
	outputs_val.push_back(output);
}

void DataManager::setValidationInput(vector<vector<double>> inputs)
{
	this->inputs_val = inputs;
}

void DataManager::setValidationOutput(vector<vector<double>> outputs)
{
	this->outputs_val = outputs;
}

bool DataManager::isValidationPassed()
{
	return validationPassed;
}

void DataManager::setValidationPassed(bool validationPassed)
{
	this->validationPassed = validationPassed;
}

void DataManager::setValidationModel(GenotypeP model, double error)
{
	if (!this->bestValidationModel || this->bestValidationError > error) {
		this->bestValidationError = error;
		this->bestValidationModel = model;
	}
}

GenotypeP DataManager::getBestValidationModel()
{
	return this->bestValidationModel;
}

double DataManager::getBestValidationError()
{
	return this->bestValidationError;
}

bool DataManager::isInitialized()
{
	return this->initialized;
}

void DataManager::setIsInitialized(bool initialized)
{
	this->initialized = initialized;
}

void DataManager::setValidationPassError(double validationPassError)
{
	this->validationPassError = validationPassError;
}

double DataManager::getValidationPassError()
{
	return this->validationPassError;
}


