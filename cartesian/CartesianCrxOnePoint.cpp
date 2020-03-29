#include "CartesianCrxOnePoint.h"
#include "Cartesian_c.h"

namespace CGP {

	void CartesianCrxOnePoint::registerParameters(StateP state)
	{
		myGenotype_->registerParameter(state, "crx.onepoint", (voidP) new double(0), ECF::DOUBLE);
	}


	bool CartesianCrxOnePoint::initialize(StateP state)
	{
		voidP sptr = myGenotype_->getParameterValue(state, "crx.onepoint");
		probability_ = *((double*)sptr.get());
		return true;
	}


	bool CartesianCrxOnePoint::mate(GenotypeP gen1, GenotypeP gen2, GenotypeP child)
	{
		Cartesian* p1 = (Cartesian*)(gen1.get());
		Cartesian* p2 = (Cartesian*)(gen2.get());
		Cartesian* ch = (Cartesian*)(child.get());

		//crossing point is any integer value in parents
		int crsPoint = state_->getRandomizer()->getRandomInteger(p1->size());

		for (unsigned long i = 0; i < p1->size(); i++) {
			if (i < crsPoint) {
				ch->at(i) = p1->at(i);
			}
			else {
				ch->at(i) = p2->at(i);
			}
		}

		return true;
	}

}

