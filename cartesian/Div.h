#ifndef Div_h
#define Div_h
#include "Function.h"
namespace CGP
{
    template <class T>
    class DivT : public Function
    {
    public:
        DivT();
        ~DivT();

        void evaluate(std::vector<T>& inputs, T& result);
    };

    typedef DivT<double> Div;

    template <class T>
    DivT<T>::DivT()
    {
        name_ = "/";
        nArguments_ = 2;
    }

    template <class T>
    DivT<T>::~DivT()
    {}

    template <class T>
    void DivT<T>::evaluate(vector<T> &inputs, T &result)
    {
        result = inputs[0] / inputs[1];
    }



}

#endif //Div_h
