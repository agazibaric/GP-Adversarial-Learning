#ifndef Sub_h
#define Sub_h
#include "Function.h"
namespace CGP
{
    template <class T>
    class SubT: public Function
    {
    public:
        SubT();
        ~SubT();

        void evaluate(std::vector<T>& inputs, T& result);
    };

    typedef SubT<double> Sub;
    template <class T>
    SubT<T>::SubT()
    {
        name_ = "-";
        nArguments_ = 2;
    }

    template <class T>
    SubT<T>::~SubT()
    {}

    template <class T>
    void SubT<T>::evaluate(vector<T> &inputs, T &result)
    {
        result = inputs[0] - inputs[1];
    }

}
#endif //Sub_h
