#include "Cartesian.h"
#include <cctype>
#include <map>
#include <vector>


namespace CGP {


Cartesian::Cartesian(void)
{
	name_ = "Cartesian";
}


Cartesian::~Cartesian(void)
{}


Cartesian* Cartesian::copy()
{
	Cartesian *newObject = new Cartesian(*this);

	// no deep copy code needed

	return newObject;
}


vector<CrossoverOpP> Cartesian::getCrossoverOp()
{
	vector<CrossoverOpP> crxOps;
	crxOps.push_back((CrossoverOpP) (new CartesianCrxOnePoint));
	crxOps.push_back((CrossoverOpP) (new CartesianCrxTwoPoint));
	crxOps.push_back((CrossoverOpP) (new CartesianCrxHalfUniform));
	crxOps.push_back((CrossoverOpP) (new CartesianCrxUniform));

	return crxOps;
}


vector<MutationOpP> Cartesian::getMutationOp()
{
	vector<MutationOpP> mutOps;
	mutOps.push_back((MutationOpP) (new CartesianMutOnePoint));
	mutOps.push_back((MutationOpP) (new CartesianMutNonSilent));
	mutOps.push_back((MutationOpP) (new CartesianMutSilent));
    mutOps.push_back((MutationOpP) (new CartesianMutNewParameterLess));

    return mutOps;
}


void Cartesian::registerParameters(StateP state)
{
	registerParameter(state, "numoutputs", (voidP) (new uint(1)), ECF::UINT, "number of functional outputs (default: 1)");
	registerParameter(state, "numrows", (voidP) (new uint(1)), ECF::UINT, "number of rows (default: 1)");
	registerParameter(state, "numcols", (voidP) (new uint(100)), ECF::UINT, "number of columns (default: 100)");
	registerParameter(state, "levelsback", (voidP) (new uint(1)), ECF::UINT, "number of previous columns to be used as possible inputs (default: 1)");
	registerParameter(state, "numvariables", (voidP) (new uint(1)), ECF::UINT, "number of input variables (default: 1)");
	registerParameter(state, "constantset", (voidP) (new string), ECF::STRING, "set of functions to use (default: none)");
	registerParameter(state, "functionset", (voidP) (new string), ECF::STRING, "set of input constants (default: none)");
}


bool Cartesian::initialize(StateP state)
{
//	std::cout << "How many time was i called?" << std::endl;
	state_ = state;

	stringstream ss;
	string names,name;
	voidP sptr;

	// create and initialize the function set
	functionSet = static_cast<FunctionSetP> (new FunctionSet);
	functionSet->initialize(state_);


	uint number;
	//Simple parameters
	sptr = getParameterValue(state, "numvariables");
	number = *((uint*) sptr.get());
	if(number <= 0) {
	    cerr << "Genotype initialization error: Number of variables is lesser than 1 or can not be parsed into a number." << endl;
	    return false;
	}
	nVariables = number;

	sptr = getParameterValue(state,"numoutputs");
	number = *((uint*) sptr.get());
	if(number <= 0) {
	    cerr << "Genotype initialization error: Number of outputs is lesser than 1 or can not be parsed into a number." << endl;
	    return false;
	}
    nOutputs = number;

	sptr = getParameterValue(state,"numrows");
	number = *((uint*) sptr.get());
    if(number <= 0) {
        cerr << "Genotype initialization error: Number of rows is lesser than 1 or can not be parsed into a number." << endl;
        return false;
    }
    nRows = number;

    sptr = getParameterValue(state,"numcols");
    number = *((uint*) sptr.get());
    if(number <= 0) {
        cerr << "Genotype initialization error: Number of columns is lesser than 1 or can not be parsed into a number." << endl;
        return false;
    }
    nCols = number;

    sptr = getParameterValue(state,"levelsback");
    number = *((uint*) sptr.get());
    if(number <= 0) {
    	cerr << "Genotype initialization error: Number of columns is lesser than 1 or can not be parsed into a number." << endl;
    	return false;
    }
    nLevelsBack = number;

	sptr = getParameterValue(state,"constantset");
	names = *((string*) sptr.get());
	number = 0;
	ss.str("");
	ss.clear();
	ss << names;
	while(ss >> name) {
		++number;
	}
	nConstants = number;
	nInputs = nConstants + nVariables;

    //Functionset parametri su malo složeniji
    sptr = getParameterValue(state, "functionset");
    names = *((string*) sptr.get());
    ss.str("");
    ss.clear();
    ss << names;
    name="";

	while(ss >> name) {
		functionSet->addFunction(name);
		nFunctions++;
	}

	map<string, FunctionP>::iterator it;
	for (it = functionSet->mFunctionSet.begin(); it != functionSet->mFunctionSet.end(); it++) {
		uint nArgs = it->second->getNumberOfArguments();
		if (nArgs > maxArity)
		{
			maxArity = nArgs;
		}
	}

	buildRandomGenome();

	return true;
}


void Cartesian::read(XMLNode &xCart)
{
	string s = xCart.getText(0);
	istringstream ss(s);
	string token;
	uint i = 0;
	while (getline(ss, token, ' '))
	{
		this->at(i++) = stoi(token);
	}
}


void Cartesian::write(XMLNode &xCart)
{
	xCart = XMLNode::createXMLTopNode("Cartesian");
	stringstream sValue;
	sValue << this->size();
	xCart.addAttribute("size", sValue.str().c_str());

	sValue.str("");

	// write genome to sValue
	std::vector<uint>& genome = *this;
	for(uint i = 0; i < genome.size(); i++)
		sValue << genome[i] << " ";

	xCart.addText(sValue.str().c_str());
}


uint Cartesian::getGenomeSize()
{
	return this->size();
}


void Cartesian::buildRandomGenome()
{
	// create genome given user defined parameters
	for (int i = 0; i < nCols; i++)
	{
		for (int j = 0; j < nRows; j++)
		{
			this->push_back((uint)(state_->getRandomizer()->getRandomInteger(nFunctions)));
			for (int k = 0; k < maxArity; k++)
			{
				uint xZ = randomInput(i);
				this->push_back(xZ);
			}
		}
	}
	for (int i = 0; i < nOutputs; i++)
	{
		this->push_back(randomOutput());
	}
}

uint Cartesian::randomInput(uint column)
{
	int min = column > nLevelsBack ? nRows * (column - nLevelsBack) + nInputs : 0;
	int max = nRows * column + nInputs;
	return (uint)(state_->getRandomizer()->getRandomInteger(min, max - 1));
}

uint Cartesian::randomOutput()
{
	// input can be output
	int min = nLevelsBack > nCols ? 0 : nRows * (nCols - nLevelsBack);
	int max = nRows * nCols + nInputs;
	return (uint)(state_->getRandomizer()->getRandomInteger(min, max - 1));
}

void Cartesian::printFenotype()
{
	stringstream sValue;
	sValue << "\n-------------- FENOTYPE --------------\n";
	for (int outputIndex = this->size() - nOutputs; outputIndex < this->size(); outputIndex++) {
		int output = this->at(outputIndex);
		string s = getGenotypeString(output);
		sValue << s;
		sValue << "\n";
	}
	sValue << "--------------------------------------\n";
	cout << sValue.str() << endl;
}

string Cartesian::getGenotypeString(int nodeIndex)
{
	stringstream sValue;

	if (nodeIndex < nInputs) {
		sValue << "x";
		sValue << nodeIndex;
	}
	else
	{
		sValue << "(";
		int functionIndex = (nodeIndex - nInputs) * (maxArity + 1);
		int functionID = this->at(functionIndex);
		FunctionP fun = functionSet->vFunctions[functionID];
		int nArgs = fun->getNumberOfArguments();
		if (nArgs == 1) {
			sValue << fun->getName();
			sValue << this->getGenotypeString(this->at(functionIndex + 1));
		}
		else if (nArgs == 2) {
			string inputString = this->getGenotypeString(this->at(functionIndex + 1));
			sValue << inputString;
			sValue << fun->getName();
			inputString = this->getGenotypeString(this->at(functionIndex + 2));
			sValue << inputString;
		}
		else {
			// TODO
			sValue << "Not supported";
		}
		sValue << ")";
	}
	return sValue.str();
}




void Cartesian::evaluate(vector<double>& inputData, vector<double>& results) {
    vector<double> working_vector (inputData);
    vector<double> operands;
    double result = 0;
    for(int i = 0; i < this->size() - nOutputs; i++) {
        int operatorID = this->operator[](i);
        int numberOfArguments = functionSet->vFunctions[operatorID]->getNumberOfArguments();
        for(int k = i + 1; k < i + numberOfArguments + 1; k++) {
            operands.push_back(working_vector[this->operator[](k)]);
        }
        functionSet->vFunctions[operatorID]->evaluate(operands, result);
        working_vector.push_back(result);
        operands.clear();
        result = 0;
		i += maxArity;
    }
    for(int i = this->size() - nOutputs; i < this->size(); i++) {
        results.push_back(working_vector[this->operator[](i)]);
    }
}


}





