#include <ecf/ECF.h>
#include "SymbRegEvalOp.h"
#include "cartesian/Cartesian.h"


int main(int argc, char **argv) 
{
	StateP state(new State);

	CartesianP cgp (new CGP::Cartesian);
	state->addGenotype(cgp);

	std::vector<std::vector<double>> x1;
	std::vector<std::vector<double>> y1;

	state->setEvalOp(new SymbRegEvalOp(x1, y1));

	state->initialize(argc, argv);
	state->run();

	return 0;
}
