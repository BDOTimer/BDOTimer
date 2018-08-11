///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
///   Пример простейшего делегата.                                             |
///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo

#include <iostream>
//--детали реализации простейшего делегата------------------------------------->
namespace detail{

    struct empty;
    
    struct icaller
    {
        virtual ~icaller(){}
        virtual void operator()()const = 0;
    };
    
    template<class F,class O = empty>
    struct tcaller: icaller
    {
        tcaller(O o, const F& f) : mObj(o), mMethod(f)
        {}
            
        void operator()()const { (mObj.*mMethod)(); }
        
        mutable O mObj;
        mutable F mMethod;
    };
    
    template<class F>
    struct tcaller<F, empty>: icaller
    {
        tcaller(const F& f) : mFunctor(f) {} 
        void operator()()const { mFunctor(); }
        mutable F mFunctor;
    };
    
}//namespace detail


//--собственно сам делегат:----------------------------------------------------v
//  синтаксис: 
//    connector con = функция;
//    connector con = функор;
//    connector con(объект, указатель_на_метод);

struct connector       
{
   ~connector() { delete caller; }

    template<class F> connector(const F& f)
        : caller( new detail::tcaller<F>(f) )    
    {}
    
    template<class O, class F> connector(O& o, const F& f)
        : caller( new detail::tcaller<F, O&>(o, f) )    
    {}
    template<class O, class F> connector(const O& o, const F& f)
        : caller( new detail::tcaller<F, const O&>(o, f) )    
    {}
    
    void operator()()const { (*caller)(); }
    
    detail::icaller* 
        caller;
    
};
