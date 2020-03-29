#ifndef SymbRegEvalOp_h
#define SymbRegEvalOp_h
 
 
class SymbRegEvalOp : public EvaluateOp
{
public:
	
	SymbRegEvalOp(std::vector<std::vector<double>> x1, std::vector<std::vector<double>> y1);

	FitnessP evaluate(IndividualP individual);
	bool initialize(StateP);
	
	// domain
	std::vector<std::vector<double>> xs;

	// codomain
	std::vector<std::vector<double>> ys;

	uint nSamples;
};
typedef boost::shared_ptr<SymbRegEvalOp> SymbRegEvalOpP;

#endif // SymbRegEvalOp_h
