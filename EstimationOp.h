#ifndef EstimationOp_h
#define EstimationOp_h
#include "DataManager.h"

 
class EstimationOp : public EvaluateOp
{
public:
	
	// EstimationOp(std::vector<std::vector<double>> x1, std::vector<std::vector<double>> y1);
	EstimationOp(DataManagerP dataManager);

	void registerParameters(StateP state);
	FitnessP evaluate(IndividualP individual);
	bool initialize(StateP);
	
	// domain
	vector<std::vector<double>> xs;

	// codomain
	vector<std::vector<double>> ys;

	DataManagerP dataManager;

	uint nInputs;
	uint nOutputs;
	uint validationSize;
};
typedef boost::shared_ptr<EstimationOp> EstimationOpP;

#endif // EstimationOp_h
