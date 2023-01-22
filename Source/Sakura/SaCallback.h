/*************************************************************
Sakura Game Framework : SaCallback.h
Author: Darrell Blake

Template magic to attempt to create a nice callback system. 
I'm not sure what I think about this yet. I think I like it 
but it's ugly and possibly over-engineered when I could have 
just used C function pointers everywhere :) Also not sure of 
any overheads.

Since writing this class I found a similar and no-doubt better 
system here: http://www.codeproject.com/cpp/FastDelegate.asp. 
It might be worth switching to this if performance proves to 
be an issue.
*************************************************************/

#ifndef _SA_CALLBACK_H
#define _SA_CALLBACK_H

#include "SaCore.h"

namespace Sakura
{
    //This allows us to force an explicit conversion to an empty callback.
    class NullCallback {};

    //
    // Two parameter callback.
    //
    template<typename P1=void, typename P2=void>
    class SaCallback
    {
    public:
        typedef void (*Func)(void*, P1, P2);
        SaCallback() : m_pFunction(NULL), m_pObject(NULL) {}
        SaCallback(NullCallback) : m_pFunction(NULL), m_pObject(NULL) {}
        SaCallback(Func pFunc, void* pObject) : m_pFunction(pFunc), m_pObject(pObject) {}
        void operator()(P1 p1, P2 p2) const
        {
            if (m_pFunction)
                (*m_pFunction)(m_pObject, p1, p2);
        }

    private:
        Func    m_pFunction;
        void*   m_pObject;
    };

    //
    // One parameter callback.
    //
    template<typename P1>
    class SaCallback<P1>
    {
    public:
        typedef void (*Func)(void*, P1);
        SaCallback() : m_pFunction(NULL), m_pObject(NULL) {}
        SaCallback(NullCallback) : m_pFunction(NULL), m_pObject(NULL) {}
        SaCallback(Func pFunc, void* pObject) : m_pFunction(pFunc), m_pObject(pObject) {}
        void operator()(P1 p1) const
        {
            if (m_pFunction)
                (*m_pFunction)(m_pObject, p1);
        }

    private:
        Func    m_pFunction;
        void*   m_pObject;
    };

    //
    // Zero parameter callback.
    //
    template <>
    class SaCallback <>
    {
    public:
        typedef void (*Func)(void*);
        SaCallback() : m_pFunction(NULL), m_pObject(NULL) {}
        SaCallback(NullCallback) : m_pFunction(NULL), m_pObject(NULL) {}
        SaCallback(Func pFunc, void* pObject) : m_pFunction(pFunc), m_pObject(pObject) {}
        void operator()() const
        {
            if (m_pFunction)
                (*m_pFunction)(m_pObject);
        }

    private:
        Func    m_pFunction;
        void*   m_pObject;
    };

    //
    // Two parameter member function binder.
    //
    template<class T, typename P1=void, typename P2=void>
    class SaMemberFuncCallbackBinder
    {
    private:
        template<void (T::*Func)(P1, P2)>
        static void FunctionWrapper(void* pObject, P1 p1, P2 p2)
        {
            (static_cast<T*>(pObject)->*Func)(p1, p2);
        }

    public:
        template<void (T::*Func)(P1, P2)>
        static SaCallback<P1, P2> Bind(T* pObject)
        {
            return SaCallback<P1, P2>(&SaMemberFuncCallbackBinder::FunctionWrapper<Func>, pObject);
        }
    };

    template<class T, typename P1, typename P2>
    SaMemberFuncCallbackBinder<T, P1, P2> SaCallbackFactory(void (T::*Func)(P1, P2))
    {
        return SaMemberFuncCallbackBinder<T, P1, P2>();
    }

    //
    // Two parameter non-member function binder.
    //
    template<typename P1=void, typename P2=void>
    class SaFuncCallbackBinder
    {
    private:
        template<void (*Func)(P1, P2)>
        static void FunctionWrapper(void*, P1 p1, P2 p2)
        {
            return (*Func)(p1, p2);
        }

    public:
        template<void (*Func)(P1, P2)>
        static SaCallback<P1, P2> Bind()
        {
            return SaCallback<P1, P2>(&SaFuncCallbackBinder::FunctionWrapper<Func>, NULL);
        }
    };

    template<typename P1, typename P2>
    SaFuncCallbackBinder<P1, P2> SaCallbackFactory(void (*)(P1, P2))
    {
        return SaFuncCallbackBinder<P1, P2>();
    }

    //
    // One parameter member function binder.
    //
    template<class T, typename P1>
    class SaMemberFuncCallbackBinder<T,P1>
    {
    private:
        template<void (T::*Func)(P1)>
        static void FunctionWrapper(void* pObject, P1 p1)
        {
            (static_cast<T*>(pObject)->*Func)(p1);
        }

    public:
        template<void (T::*Func)(P1)>
        static SaCallback<P1> Bind(T* pObject)
        {
            return SaCallback<P1>(&SaMemberFuncCallbackBinder::FunctionWrapper<Func>, pObject);
        }
    };

    template<class T, typename P1>
    SaMemberFuncCallbackBinder<T, P1> SaCallbackFactory(void (T::*Func)(P1))
    {
        return SaMemberFuncCallbackBinder<T, P1>();
    }

    //
    // One parameter non-member function binder.
    //
    template<typename P1>
    class SaFuncCallbackBinder<P1>
    {
    private:
        template<void (*Func)(P1)>
        static void FunctionWrapper(void* pObject, P1 p1)
        {
            return (*Func)(p1);
        }

    public:
        template<void (*Func)(P1)>
        static SaCallback<P1> Bind()
        {
            return SaCallback<P1>(&SaFuncCallbackBinder::FunctionWrapper<Func>, NULL);
        }
    };

    template<typename P1>
    SaFuncCallbackBinder<P1> SaCallbackFactory(void (*)(P1))
    {
        return SaFuncCallbackBinder<P1>();
    }

    template<typename P1>
    class SaNoCallbackBinder
    {
    public:
        template<void (*Func)(P1)>
        static SaCallback<P1> Bind()
        {
            return SaCallback<P1>();
        }
    };

    template<typename P1>
    SaCallback<P1> SaNoCallbackFactory()
    {
        return SaNoCallbackBinder<P1>();
    }

    //
    // Zero parameter member function binder.
    //
    template<class T>
    class SaMemberFuncCallbackBinder<T>
    {
    private:
        template<void (T::*Func)()>
        static void FunctionWrapper(void* pObject)
        {
            (static_cast<T*>(pObject)->*Func)();
        }

    public:
        template<void (T::*Func)()>
        static SaCallback<> Bind(T* pObject)
        {
            return SaCallback<>(&SaMemberFuncCallbackBinder::FunctionWrapper<Func>, pObject);
        }
    };

    template<class T>
    SaMemberFuncCallbackBinder<T> SaCallbackFactory(void (T::*Func)())
    {
        return SaMemberFuncCallbackBinder<T>();
    }

    //
    // Zero parameter non-member function binder.
    //
    template<>
    class SaFuncCallbackBinder<>
    {
    private:
        template<void (*Func)()>
        static void FunctionWrapper(void* pObject)
        {
            return (*Func)();
        }

    public:
        template<void (*Func)()>
        static SaCallback<> Bind()
        {
            return SaCallback<>(&SaFuncCallbackBinder::FunctionWrapper<Func>, NULL);
        }
    };

    template<typename>
    SaFuncCallbackBinder<> SaCallbackFactory(void (*)())
    {
        return SaFuncCallbackBinder<>();
    }

    //Macros to help keep the syntax sane.
    #define BIND_MEMBER_FUNC(memberFuncPtr, instancePtr) (SaCallbackFactory(memberFuncPtr).Bind<memberFuncPtr>(instancePtr))
    #define BIND_FUNC(funcPtr) (SaCallbackFactory(funcPtr).Bind<funcPtr>())
    #define NO_CALLBACK NullCallback()
}

#endif  //_SA_CALLBACK_H
