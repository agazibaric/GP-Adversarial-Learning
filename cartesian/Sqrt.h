#ifndef Sqrt_h
#define Sqrt_h
#include "Function.h"
namespace CGP
{
    template <class T>
    class SqrtT : public Function
    {
    public:
        SqrtT();
        ~SqrtT();

        void evaluate(std::vector<T>& inputs, T& result);
    };

    typedef SqrtT<double> Sqrt;

    template <class T>
    SqrtT<T>::SqrtT()
    {
        name_ = "sqrt";
        nArguments_ = 1;
    }

    template  <class T>
    SqrtT<T>::~SqrtT()
    {}

    template  <class T>
    void SqrtT<T>::evaluate(vector<T> &inputs, T &result)
    {
        result = sqrt(inputs[0]);
    }
}
#endif //Sqrt_h
