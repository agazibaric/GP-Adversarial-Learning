#pragma once
#include "ecf/ECF.h"
#include "cartesian/Cartesian.h"
#include "DataManager.h"

class ExplorationOp : public EvaluateOp
{
public:
	ExplorationOp(DataManagerP dataManager);
	FitnessP evaluate(IndividualP individual);
	bool initialize(StateP);

	typedef boost::shared_ptr<ExplorationOp> ExplorationOpP;

	DataManagerP dataManager;

};
typedef boost::shared_ptr<ExplorationOp> ExplorationOpP;
