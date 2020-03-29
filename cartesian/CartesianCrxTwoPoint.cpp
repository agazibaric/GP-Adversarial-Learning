#include "CartesianCrxTwoPoint.h"
#include "Cartesian_c.h"

namespace CGP {

    void CartesianCrxTwoPoint::registerParameters(StateP state)
    {
        myGenotype_->registerParameter(state, "crx.twopoint", (voidP) new double(0), ECF::DOUBLE);
    }


    bool CartesianCrxTwoPoint::initialize(StateP state)
    {
        voidP sptr = myGenotype_->getParameterValue(state, "crx.twopoint");
        probability_ = *((double*)sptr.get());
        return true;
    }


    bool CartesianCrxTwoPoint::mate(GenotypeP gen1, GenotypeP gen2, GenotypeP child)
    {
        Cartesian* p1 = (Cartesian*) (gen1.get());
        Cartesian* p2 = (Cartesian*) (gen2.get());
        Cartesian* ch = (Cartesian*) (child.get());

        //crossing point is any integer value in parents
        int crsPointFirst = state_->getRandomizer()->getRandomInteger(p1->size());
        int crsPointSecond;
        do {
            crsPointSecond = state_->getRandomizer()->getRandomInteger(p1->size());
        } while(crsPointFirst == crsPointSecond);

        for(unsigned long i = 0; i < p1->size(); i++) {
            if(i<crsPointFirst || i>=crsPointSecond) {
                ch->at(i) = p1->at(i);
            }
            else {
                ch->at(i) = p2->at(i);
            }
        }

        return true;
    }

}

