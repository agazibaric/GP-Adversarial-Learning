#ifndef NLog_h
#define NLog_h
#include "Function.h"
namespace CGP {

    template <class T>
    class NlogT : public Function
    {
    public:
        NlogT();
        ~NlogT();

        void evaluate(std::vector<T>& inputs, T& result);
    };

    typedef NlogT<double> Ln;

    template <class T>
    NlogT<T>::NlogT()
    {
        name_ = "ln";
        nArguments_ = 1;
    }

    template  <class T>
    NlogT<T>::~NlogT()
    {}

    template  <class T>
    void NlogT<T>::evaluate(vector<T> &inputs, T &result)
    {
        result = log(inputs[0]);
    }
}
#endif //NLog_h
