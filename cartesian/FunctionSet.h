#ifndef FunctionSet_h
#define FunctionSet_h
#include "Function.h"


namespace CGP
{
	class FunctionSet
	{
	public:
		FunctionSet();

		bool initialize(StateP state);

		/**
		Activate function (mark as used)
		*/
		bool addFunction(string name);



		~FunctionSet() {}
		
		std::map <std::string, FunctionP> mAllFunctions;	//<! map of existing (implemented) functions
		std::vector <FunctionP> vFunctions;					//<! vector of active (actual used) functions
		std::map <std::string, FunctionP> mFunctionSet;		//!< map of active (actual used) functions

		StateP state_;

	};	

	typedef boost::shared_ptr<FunctionSet> FunctionSetP;
	typedef std::map <std::string, FunctionP>::iterator func_iter;
}


#endif /* FunctionSet_h */