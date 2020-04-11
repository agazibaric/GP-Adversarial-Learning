#include "CartesianCrxHalfUniform.h"
#include "Cartesian_c.h"

namespace CGP {

    void CartesianCrxHalfUniform::registerParameters(StateP state)
    {
        myGenotype_->registerParameter(state, "crx.halfuniform", (voidP) new double(0), ECF::DOUBLE);
    }


    bool CartesianCrxHalfUniform::initialize(StateP state)
    {
        voidP sptr = myGenotype_->getParameterValue(state, "crx.halfuniform");
        probability_ = *((double*)sptr.get());
        return true;
    }


    bool CartesianCrxHalfUniform::mate(GenotypeP gen1, GenotypeP gen2, GenotypeP child)
    {
        Cartesian* p1 = (Cartesian*) (gen1.get());
        Cartesian* p2 = (Cartesian*) (gen2.get());
        Cartesian* ch = (Cartesian*) (child.get());

        int randomParentChooser;
        for(unsigned long i = 0; i < p1->size()/2; i++) {
            randomParentChooser = state_->getRandomizer()->getRandomInteger(0, 1);
            switch (randomParentChooser) {
                case 0:
                    ch->at(i) = p1->at(i);
                    break;
                default:
                    ch->at(i) = p2->at(i);
                    break;
            }
        }

        return true;
    }

}

