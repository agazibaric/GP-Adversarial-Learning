#ifndef EstimationOp_h
#define EstimationOp_h
 
 
class EstimationOp : public EvaluateOp
{
public:
	
	EstimationOp(std::vector<std::vector<double>> x1, std::vector<std::vector<double>> y1);

	FitnessP evaluate(IndividualP individual);
	bool initialize(StateP);
	
	// domain
	vector<std::vector<double>> xs;

	// codomain
	vector<std::vector<double>> ys;

	uint nSamples;
};
typedef boost::shared_ptr<EstimationOp> EstimationOpP;

#endif // EstimationOp_h
