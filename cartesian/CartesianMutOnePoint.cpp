#include "CartesianMutOnePoint.h"
#include "Cartesian_c.h"
#include <cmath>
#include <algorithm>

namespace CGP
{

	void CartesianMutOnePoint::registerParameters(StateP state)
	{
		myGenotype_->registerParameter(state, "mut.onepoint", (voidP) new double(0), ECF::DOUBLE);
	}


	bool CartesianMutOnePoint::initialize(StateP state)
	{
		voidP sptr = myGenotype_->getParameterValue(state, "mut.onepoint");
		probability_ = *((double*)sptr.get());
		return true;
	}


	bool CartesianMutOnePoint::mutate(GenotypeP gene)
	{
		Cartesian* cart = (Cartesian*)(gene.get());
		RandomizerP randP = cart->state_->getRandomizer();
		const uint size = cart->getGenomeSize();
		const uint randomGeneIndex = randP->getRandomInteger(0, size - 1); // Gene that will be mutated
		const uint nOutputs = cart->nOutputs;
		const uint nVariables = cart->nVariables;
		const uint rows = cart->nRows;
		const uint cols = cart->nCols;
		const uint levelsBack = cart->nLevelsBack;
		const uint nFunctions = cart->nFunctions;
		const uint maxArity = cart->maxArity;
		const uint nInputs = cart->nInputs;
		uint newGene = 0;

		if (randomGeneIndex < size - nOutputs) {
			if (randomGeneIndex % (maxArity + 1) == 0) {
				// Function gene
				newGene = randP->getRandomInteger(0, nFunctions - 1);
			}
			else {
					// Input gene
					uint randomNode = randomGeneIndex / (maxArity + 1);
					uint nodeColumn = randomNode / rows;
					int minColumn = nodeColumn - levelsBack;
					uint lowerBound = nInputs + minColumn * rows;
					if (minColumn < 0) lowerBound = 0;
					uint upperBound = nInputs + nodeColumn * rows;
					newGene = randP->getRandomInteger(lowerBound, upperBound - 1);
			}
		}
		else {
			// Output gene
			uint upperBound = nInputs + rows * cols;
			uint lowerBound = 0;
			newGene = randP->getRandomInteger(lowerBound, upperBound - 1);
		}

		cart->at(randomGeneIndex) = newGene;

		return true;
	}

}


