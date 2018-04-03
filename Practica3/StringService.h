// **********************************************************************
//
// Copyright (c) 2003-2017 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************
//
// Ice version 3.7.0
//
// <auto-generated>
//
// Generated from file `StringService.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>
//

#ifndef __StringService_h__
#define __StringService_h__

//#include <IceUtil/PushDisableWarnings.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/ValueF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
#include <Ice/StreamHelpers.h>
#include <Ice/Comparable.h>
#include <Ice/Proxy.h>
#include <Ice/Object.h>
#include <Ice/GCObject.h>
#include <Ice/Value.h>
#include <Ice/Incoming.h>
#include <Ice/FactoryTableInit.h>
#include <IceUtil/ScopedArray.h>
#include <Ice/Optional.h>
#include <IceUtil/UndefSysMacros.h>

#ifndef ICE_IGNORE_VERSION
#   if ICE_INT_VERSION / 100 != 307
#       error Ice version mismatch!
#   endif
#   if ICE_INT_VERSION % 100 > 50
#       error Beta header file detected
#   endif
#   if ICE_INT_VERSION % 100 < 0
#       error Ice patch level mismatch!
#   endif
#endif

#ifdef ICE_CPP11_MAPPING // C++11 mapping

namespace UC3M
{

class StringService;
class StringServicePrx;

}

namespace UC3M
{

class StringService : public virtual ::Ice::Object
{
public:

    using ProxyType = StringServicePrx;

    virtual bool ice_isA(::std::string, const ::Ice::Current&) const override;
    virtual ::std::vector<::std::string> ice_ids(const ::Ice::Current&) const override;
    virtual ::std::string ice_id(const ::Ice::Current&) const override;

    static const ::std::string& ice_staticId();

    virtual int stringSize(::std::string, const ::Ice::Current&) = 0;
    bool _iceD_stringSize(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string toUpperCase(::std::string, const ::Ice::Current&) = 0;
    bool _iceD_toUpperCase(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool _iceDispatch(::IceInternal::Incoming&, const ::Ice::Current&) override;
};

}

namespace UC3M
{

class StringServicePrx : public virtual ::Ice::Proxy<StringServicePrx, ::Ice::ObjectPrx>
{
public:

    int stringSize(const ::std::string& iceP_s, const ::Ice::Context& context = Ice::noExplicitContext)
    {
        return _makePromiseOutgoing<int>(true, this, &UC3M::StringServicePrx::_iceI_stringSize, iceP_s, context).get();
    }

    template<template<typename> class P = ::std::promise>
    auto stringSizeAsync(const ::std::string& iceP_s, const ::Ice::Context& context = Ice::noExplicitContext)
        -> decltype(::std::declval<P<int>>().get_future())
    {
        return _makePromiseOutgoing<int, P>(false, this, &UC3M::StringServicePrx::_iceI_stringSize, iceP_s, context);
    }

    ::std::function<void()>
    stringSizeAsync(const ::std::string& iceP_s,
                    ::std::function<void(int)> response,
                    ::std::function<void(::std::exception_ptr)> ex = nullptr,
                    ::std::function<void(bool)> sent = nullptr,
                    const ::Ice::Context& context = Ice::noExplicitContext)
    {
        return _makeLamdaOutgoing<int>(response, ex, sent, this, &UC3M::StringServicePrx::_iceI_stringSize, iceP_s, context);
    }

    void _iceI_stringSize(const ::std::shared_ptr<::IceInternal::OutgoingAsyncT<int>>&, const ::std::string&, const ::Ice::Context&);

    ::std::string toUpperCase(const ::std::string& iceP_s, const ::Ice::Context& context = Ice::noExplicitContext)
    {
        return _makePromiseOutgoing<::std::string>(true, this, &UC3M::StringServicePrx::_iceI_toUpperCase, iceP_s, context).get();
    }

    template<template<typename> class P = ::std::promise>
    auto toUpperCaseAsync(const ::std::string& iceP_s, const ::Ice::Context& context = Ice::noExplicitContext)
        -> decltype(::std::declval<P<::std::string>>().get_future())
    {
        return _makePromiseOutgoing<::std::string, P>(false, this, &UC3M::StringServicePrx::_iceI_toUpperCase, iceP_s, context);
    }

    ::std::function<void()>
    toUpperCaseAsync(const ::std::string& iceP_s,
                     ::std::function<void(::std::string)> response,
                     ::std::function<void(::std::exception_ptr)> ex = nullptr,
                     ::std::function<void(bool)> sent = nullptr,
                     const ::Ice::Context& context = Ice::noExplicitContext)
    {
        return _makeLamdaOutgoing<::std::string>(response, ex, sent, this, &UC3M::StringServicePrx::_iceI_toUpperCase, iceP_s, context);
    }

    void _iceI_toUpperCase(const ::std::shared_ptr<::IceInternal::OutgoingAsyncT<::std::string>>&, const ::std::string&, const ::Ice::Context&);

    static const ::std::string& ice_staticId();

protected:

    StringServicePrx() = default;
    friend ::std::shared_ptr<StringServicePrx> IceInternal::createProxy<StringServicePrx>();

    virtual ::std::shared_ptr<::Ice::ObjectPrx> _newInstance() const override;
};

}

namespace Ice
{

}

namespace UC3M
{

using StringServicePtr = ::std::shared_ptr<StringService>;
using StringServicePrxPtr = ::std::shared_ptr<StringServicePrx>;

}

#else // C++98 mapping

namespace IceProxy
{

namespace UC3M
{

class StringService;
void _readProxy(::Ice::InputStream*, ::IceInternal::ProxyHandle< ::IceProxy::UC3M::StringService>&);
::IceProxy::Ice::Object* upCast(::IceProxy::UC3M::StringService*);

}

}

namespace UC3M
{

class StringService;
::Ice::Object* upCast(::UC3M::StringService*);
typedef ::IceInternal::Handle< ::UC3M::StringService> StringServicePtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::UC3M::StringService> StringServicePrx;
typedef StringServicePrx StringServicePrxPtr;
void _icePatchObjectPtr(StringServicePtr&, const ::Ice::ObjectPtr&);

}

namespace UC3M
{

class Callback_StringService_stringSize_Base : public virtual ::IceInternal::CallbackBase { };
typedef ::IceUtil::Handle< Callback_StringService_stringSize_Base> Callback_StringService_stringSizePtr;

class Callback_StringService_toUpperCase_Base : public virtual ::IceInternal::CallbackBase { };
typedef ::IceUtil::Handle< Callback_StringService_toUpperCase_Base> Callback_StringService_toUpperCasePtr;

}

namespace IceProxy
{

namespace UC3M
{

class StringService : public virtual ::Ice::Proxy<StringService, ::IceProxy::Ice::Object>
{
public:

    ::Ice::Int stringSize(const ::std::string& iceP_s, const ::Ice::Context& context = ::Ice::noExplicitContext)
    {
        return end_stringSize(_iceI_begin_stringSize(iceP_s, context, ::IceInternal::dummyCallback, 0, true));
    }

    ::Ice::AsyncResultPtr begin_stringSize(const ::std::string& iceP_s, const ::Ice::Context& context = ::Ice::noExplicitContext)
    {
        return _iceI_begin_stringSize(iceP_s, context, ::IceInternal::dummyCallback, 0);
    }

    ::Ice::AsyncResultPtr begin_stringSize(const ::std::string& iceP_s, const ::Ice::CallbackPtr& del, const ::Ice::LocalObjectPtr& cookie = 0)
    {
        return _iceI_begin_stringSize(iceP_s, ::Ice::noExplicitContext, del, cookie);
    }

    ::Ice::AsyncResultPtr begin_stringSize(const ::std::string& iceP_s, const ::Ice::Context& context, const ::Ice::CallbackPtr& del, const ::Ice::LocalObjectPtr& cookie = 0)
    {
        return _iceI_begin_stringSize(iceP_s, context, del, cookie);
    }

    ::Ice::AsyncResultPtr begin_stringSize(const ::std::string& iceP_s, const ::UC3M::Callback_StringService_stringSizePtr& del, const ::Ice::LocalObjectPtr& cookie = 0)
    {
        return _iceI_begin_stringSize(iceP_s, ::Ice::noExplicitContext, del, cookie);
    }

    ::Ice::AsyncResultPtr begin_stringSize(const ::std::string& iceP_s, const ::Ice::Context& context, const ::UC3M::Callback_StringService_stringSizePtr& del, const ::Ice::LocalObjectPtr& cookie = 0)
    {
        return _iceI_begin_stringSize(iceP_s, context, del, cookie);
    }

    ::Ice::Int end_stringSize(const ::Ice::AsyncResultPtr&);

private:

    ::Ice::AsyncResultPtr _iceI_begin_stringSize(const ::std::string&, const ::Ice::Context&, const ::IceInternal::CallbackBasePtr&, const ::Ice::LocalObjectPtr& cookie = 0, bool sync = false);

public:

    ::std::string toUpperCase(const ::std::string& iceP_s, const ::Ice::Context& context = ::Ice::noExplicitContext)
    {
        return end_toUpperCase(_iceI_begin_toUpperCase(iceP_s, context, ::IceInternal::dummyCallback, 0, true));
    }

    ::Ice::AsyncResultPtr begin_toUpperCase(const ::std::string& iceP_s, const ::Ice::Context& context = ::Ice::noExplicitContext)
    {
        return _iceI_begin_toUpperCase(iceP_s, context, ::IceInternal::dummyCallback, 0);
    }

    ::Ice::AsyncResultPtr begin_toUpperCase(const ::std::string& iceP_s, const ::Ice::CallbackPtr& del, const ::Ice::LocalObjectPtr& cookie = 0)
    {
        return _iceI_begin_toUpperCase(iceP_s, ::Ice::noExplicitContext, del, cookie);
    }

    ::Ice::AsyncResultPtr begin_toUpperCase(const ::std::string& iceP_s, const ::Ice::Context& context, const ::Ice::CallbackPtr& del, const ::Ice::LocalObjectPtr& cookie = 0)
    {
        return _iceI_begin_toUpperCase(iceP_s, context, del, cookie);
    }

    ::Ice::AsyncResultPtr begin_toUpperCase(const ::std::string& iceP_s, const ::UC3M::Callback_StringService_toUpperCasePtr& del, const ::Ice::LocalObjectPtr& cookie = 0)
    {
        return _iceI_begin_toUpperCase(iceP_s, ::Ice::noExplicitContext, del, cookie);
    }

    ::Ice::AsyncResultPtr begin_toUpperCase(const ::std::string& iceP_s, const ::Ice::Context& context, const ::UC3M::Callback_StringService_toUpperCasePtr& del, const ::Ice::LocalObjectPtr& cookie = 0)
    {
        return _iceI_begin_toUpperCase(iceP_s, context, del, cookie);
    }

    ::std::string end_toUpperCase(const ::Ice::AsyncResultPtr&);

private:

    ::Ice::AsyncResultPtr _iceI_begin_toUpperCase(const ::std::string&, const ::Ice::Context&, const ::IceInternal::CallbackBasePtr&, const ::Ice::LocalObjectPtr& cookie = 0, bool sync = false);

public:

    static const ::std::string& ice_staticId();

protected:

    virtual ::IceProxy::Ice::Object* _newInstance() const;
};

}

}

namespace UC3M
{

class StringService : public virtual ::Ice::Object
{
public:

    typedef StringServicePrx ProxyType;
    typedef StringServicePtr PointerType;

    virtual ~StringService();

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::emptyCurrent) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::emptyCurrent) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::emptyCurrent) const;

    static const ::std::string& ice_staticId();

    virtual ::Ice::Int stringSize(const ::std::string&, const ::Ice::Current& = ::Ice::emptyCurrent) = 0;
    bool _iceD_stringSize(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string toUpperCase(const ::std::string&, const ::Ice::Current& = ::Ice::emptyCurrent) = 0;
    bool _iceD_toUpperCase(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool _iceDispatch(::IceInternal::Incoming&, const ::Ice::Current&);

protected:

    virtual void _iceWriteImpl(::Ice::OutputStream*) const;
    virtual void _iceReadImpl(::Ice::InputStream*);
};

inline bool operator==(const StringService& lhs, const StringService& rhs)
{
    return static_cast<const ::Ice::Object&>(lhs) == static_cast<const ::Ice::Object&>(rhs);
}

inline bool operator<(const StringService& lhs, const StringService& rhs)
{
    return static_cast<const ::Ice::Object&>(lhs) < static_cast<const ::Ice::Object&>(rhs);
}

}

namespace Ice
{

}

namespace UC3M
{

template<class T>
class CallbackNC_StringService_stringSize : public Callback_StringService_stringSize_Base, public ::IceInternal::TwowayCallbackNC<T>
{
public:

    typedef IceUtil::Handle<T> TPtr;

    typedef void (T::*Exception)(const ::Ice::Exception&);
    typedef void (T::*Sent)(bool);
    typedef void (T::*Response)(::Ice::Int);

    CallbackNC_StringService_stringSize(const TPtr& obj, Response cb, Exception excb, Sent sentcb)
        : ::IceInternal::TwowayCallbackNC<T>(obj, cb != 0, excb, sentcb), _response(cb)
    {
    }

    virtual void completed(const ::Ice::AsyncResultPtr& result) const
    {
        ::UC3M::StringServicePrx proxy = ::UC3M::StringServicePrx::uncheckedCast(result->getProxy());
        ::Ice::Int ret;
        try
        {
            ret = proxy->end_stringSize(result);
        }
        catch(const ::Ice::Exception& ex)
        {
            ::IceInternal::CallbackNC<T>::exception(result, ex);
            return;
        }
        if(_response)
        {
            (::IceInternal::CallbackNC<T>::_callback.get()->*_response)(ret);
        }
    }

private:

    Response _response;
};

template<class T> Callback_StringService_stringSizePtr
newCallback_StringService_stringSize(const IceUtil::Handle<T>& instance, void (T::*cb)(::Ice::Int), void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_StringService_stringSize<T>(instance, cb, excb, sentcb);
}

template<class T> Callback_StringService_stringSizePtr
newCallback_StringService_stringSize(T* instance, void (T::*cb)(::Ice::Int), void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_StringService_stringSize<T>(instance, cb, excb, sentcb);
}

template<class T, typename CT>
class Callback_StringService_stringSize : public Callback_StringService_stringSize_Base, public ::IceInternal::TwowayCallback<T, CT>
{
public:

    typedef IceUtil::Handle<T> TPtr;

    typedef void (T::*Exception)(const ::Ice::Exception& , const CT&);
    typedef void (T::*Sent)(bool , const CT&);
    typedef void (T::*Response)(::Ice::Int, const CT&);

    Callback_StringService_stringSize(const TPtr& obj, Response cb, Exception excb, Sent sentcb)
        : ::IceInternal::TwowayCallback<T, CT>(obj, cb != 0, excb, sentcb), _response(cb)
    {
    }

    virtual void completed(const ::Ice::AsyncResultPtr& result) const
    {
        ::UC3M::StringServicePrx proxy = ::UC3M::StringServicePrx::uncheckedCast(result->getProxy());
        ::Ice::Int ret;
        try
        {
            ret = proxy->end_stringSize(result);
        }
        catch(const ::Ice::Exception& ex)
        {
            ::IceInternal::Callback<T, CT>::exception(result, ex);
            return;
        }
        if(_response)
        {
            (::IceInternal::Callback<T, CT>::_callback.get()->*_response)(ret, CT::dynamicCast(result->getCookie()));
        }
    }

private:

    Response _response;
};

template<class T, typename CT> Callback_StringService_stringSizePtr
newCallback_StringService_stringSize(const IceUtil::Handle<T>& instance, void (T::*cb)(::Ice::Int, const CT&), void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_StringService_stringSize<T, CT>(instance, cb, excb, sentcb);
}

template<class T, typename CT> Callback_StringService_stringSizePtr
newCallback_StringService_stringSize(T* instance, void (T::*cb)(::Ice::Int, const CT&), void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_StringService_stringSize<T, CT>(instance, cb, excb, sentcb);
}

template<class T>
class CallbackNC_StringService_toUpperCase : public Callback_StringService_toUpperCase_Base, public ::IceInternal::TwowayCallbackNC<T>
{
public:

    typedef IceUtil::Handle<T> TPtr;

    typedef void (T::*Exception)(const ::Ice::Exception&);
    typedef void (T::*Sent)(bool);
    typedef void (T::*Response)(const ::std::string&);

    CallbackNC_StringService_toUpperCase(const TPtr& obj, Response cb, Exception excb, Sent sentcb)
        : ::IceInternal::TwowayCallbackNC<T>(obj, cb != 0, excb, sentcb), _response(cb)
    {
    }

    virtual void completed(const ::Ice::AsyncResultPtr& result) const
    {
        ::UC3M::StringServicePrx proxy = ::UC3M::StringServicePrx::uncheckedCast(result->getProxy());
        ::std::string ret;
        try
        {
            ret = proxy->end_toUpperCase(result);
        }
        catch(const ::Ice::Exception& ex)
        {
            ::IceInternal::CallbackNC<T>::exception(result, ex);
            return;
        }
        if(_response)
        {
            (::IceInternal::CallbackNC<T>::_callback.get()->*_response)(ret);
        }
    }

private:

    Response _response;
};

template<class T> Callback_StringService_toUpperCasePtr
newCallback_StringService_toUpperCase(const IceUtil::Handle<T>& instance, void (T::*cb)(const ::std::string&), void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_StringService_toUpperCase<T>(instance, cb, excb, sentcb);
}

template<class T> Callback_StringService_toUpperCasePtr
newCallback_StringService_toUpperCase(T* instance, void (T::*cb)(const ::std::string&), void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_StringService_toUpperCase<T>(instance, cb, excb, sentcb);
}

template<class T, typename CT>
class Callback_StringService_toUpperCase : public Callback_StringService_toUpperCase_Base, public ::IceInternal::TwowayCallback<T, CT>
{
public:

    typedef IceUtil::Handle<T> TPtr;

    typedef void (T::*Exception)(const ::Ice::Exception& , const CT&);
    typedef void (T::*Sent)(bool , const CT&);
    typedef void (T::*Response)(const ::std::string&, const CT&);

    Callback_StringService_toUpperCase(const TPtr& obj, Response cb, Exception excb, Sent sentcb)
        : ::IceInternal::TwowayCallback<T, CT>(obj, cb != 0, excb, sentcb), _response(cb)
    {
    }

    virtual void completed(const ::Ice::AsyncResultPtr& result) const
    {
        ::UC3M::StringServicePrx proxy = ::UC3M::StringServicePrx::uncheckedCast(result->getProxy());
        ::std::string ret;
        try
        {
            ret = proxy->end_toUpperCase(result);
        }
        catch(const ::Ice::Exception& ex)
        {
            ::IceInternal::Callback<T, CT>::exception(result, ex);
            return;
        }
        if(_response)
        {
            (::IceInternal::Callback<T, CT>::_callback.get()->*_response)(ret, CT::dynamicCast(result->getCookie()));
        }
    }

private:

    Response _response;
};

template<class T, typename CT> Callback_StringService_toUpperCasePtr
newCallback_StringService_toUpperCase(const IceUtil::Handle<T>& instance, void (T::*cb)(const ::std::string&, const CT&), void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_StringService_toUpperCase<T, CT>(instance, cb, excb, sentcb);
}

template<class T, typename CT> Callback_StringService_toUpperCasePtr
newCallback_StringService_toUpperCase(T* instance, void (T::*cb)(const ::std::string&, const CT&), void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_StringService_toUpperCase<T, CT>(instance, cb, excb, sentcb);
}

}

#endif

#include <IceUtil/PopDisableWarnings.h>
#endif
