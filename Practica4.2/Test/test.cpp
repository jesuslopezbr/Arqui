// **********************************************************************
//
// Copyright (c) 2003-2018 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************
//
// Ice version 3.7.1
//
// <auto-generated>
//
// Generated from file `test.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>
//

#include <test.h>
#include <IceUtil/PushDisableWarnings.h>
#include <Ice/LocalException.h>
#include <Ice/ValueFactory.h>
#include <Ice/OutgoingAsync.h>
#include <Ice/InputStream.h>
#include <Ice/OutputStream.h>
#include <IceUtil/PopDisableWarnings.h>

#if defined(_MSC_VER)
#   pragma warning(disable:4458) // declaration of ... hides class member
#elif defined(__clang__)
#   pragma clang diagnostic ignored "-Wshadow"
#elif defined(__GNUC__)
#   pragma GCC diagnostic ignored "-Wshadow"
#endif

#ifndef ICE_IGNORE_VERSION
#   if ICE_INT_VERSION / 100 != 307
#       error Ice version mismatch!
#   endif
#   if ICE_INT_VERSION % 100 > 50
#       error Beta header file detected
#   endif
#   if ICE_INT_VERSION % 100 < 1
#       error Ice patch level mismatch!
#   endif
#endif

#ifdef ICE_CPP11_MAPPING // C++11 mapping

namespace
{

const ::std::string iceC_M_Test_ids[2] =
{
    "::Ice::Object",
    "::M::Test"
};
const ::std::string iceC_M_Test_ops[] =
{
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping",
    "op"
};
const ::std::string iceC_M_Test_op_name = "op";

}

bool
M::Test::ice_isA(::std::string s, const ::Ice::Current&) const
{
    return ::std::binary_search(iceC_M_Test_ids, iceC_M_Test_ids + 2, s);
}

::std::vector<::std::string>
M::Test::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector<::std::string>(&iceC_M_Test_ids[0], &iceC_M_Test_ids[2]);
}

::std::string
M::Test::ice_id(const ::Ice::Current&) const
{
    return ice_staticId();
}

const ::std::string&
M::Test::ice_staticId()
{
    static const ::std::string typeId = "::M::Test";
    return typeId;
}

/// \cond INTERNAL
bool
M::Test::_iceD_op(::IceInternal::Incoming& inS, const ::Ice::Current& current)
{
    _iceCheckMode(::Ice::OperationMode::Normal, current.mode);
    auto istr = inS.startReadParams();
    ::std::string iceP_sin;
    istr->readAll(iceP_sin);
    inS.endReadParams();
    ::std::string iceP_sout;
    int ret = this->op(::std::move(iceP_sin), iceP_sout, current);
    auto ostr = inS.startWriteParams();
    ostr->writeAll(iceP_sout, ret);
    inS.endWriteParams();
    return true;
}
/// \endcond

/// \cond INTERNAL
bool
M::Test::_iceDispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair<const ::std::string*, const ::std::string*> r = ::std::equal_range(iceC_M_Test_ops, iceC_M_Test_ops + 5, current.operation);
    if(r.first == r.second)
    {
        throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
    }

    switch(r.first - iceC_M_Test_ops)
    {
        case 0:
        {
            return _iceD_ice_id(in, current);
        }
        case 1:
        {
            return _iceD_ice_ids(in, current);
        }
        case 2:
        {
            return _iceD_ice_isA(in, current);
        }
        case 3:
        {
            return _iceD_ice_ping(in, current);
        }
        case 4:
        {
            return _iceD_op(in, current);
        }
        default:
        {
            assert(false);
            throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
        }
    }
}
/// \endcond

/// \cond INTERNAL
void
M::TestPrx::_iceI_op(const ::std::shared_ptr<::IceInternal::OutgoingAsyncT<Test::OpResult>>& outAsync, const ::std::string& iceP_sin, const ::Ice::Context& context)
{
    _checkTwowayOnly(iceC_M_Test_op_name);
    outAsync->invoke(iceC_M_Test_op_name, ::Ice::OperationMode::Normal, ::Ice::FormatType::DefaultFormat, context,
        [&](::Ice::OutputStream* ostr)
        {
            ostr->writeAll(iceP_sin);
        },
        nullptr,
        [](::Ice::InputStream* istr)
        {
            Test::OpResult v;
            istr->readAll(v.sout, v.returnValue);
            return v;
        });
}
/// \endcond

/// \cond INTERNAL
::std::shared_ptr<::Ice::ObjectPrx>
M::TestPrx::_newInstance() const
{
    return ::IceInternal::createProxy<TestPrx>();
}
/// \endcond

const ::std::string&
M::TestPrx::ice_staticId()
{
    return Test::ice_staticId();
}

#else // C++98 mapping

namespace
{

const ::std::string iceC_M_Test_op_name = "op";

}

/// \cond INTERNAL
::IceProxy::Ice::Object* ::IceProxy::M::upCast(Test* p) { return p; }

void
::IceProxy::M::_readProxy(::Ice::InputStream* istr, ::IceInternal::ProxyHandle< Test>& v)
{
    ::Ice::ObjectPrx proxy;
    istr->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new Test;
        v->_copyFrom(proxy);
    }
}
/// \endcond

::Ice::AsyncResultPtr
IceProxy::M::Test::_iceI_begin_op(const ::std::string& iceP_sin, const ::Ice::Context& context, const ::IceInternal::CallbackBasePtr& del, const ::Ice::LocalObjectPtr& cookie, bool sync)
{
    _checkTwowayOnly(iceC_M_Test_op_name, sync);
    ::IceInternal::OutgoingAsyncPtr result = new ::IceInternal::CallbackOutgoing(this, iceC_M_Test_op_name, del, cookie, sync);
    try
    {
        result->prepare(iceC_M_Test_op_name, ::Ice::Normal, context);
        ::Ice::OutputStream* ostr = result->startWriteParams(::Ice::DefaultFormat);
        ostr->write(iceP_sin);
        result->endWriteParams();
        result->invoke(iceC_M_Test_op_name);
    }
    catch(const ::Ice::Exception& ex)
    {
        result->abort(ex);
    }
    return result;
}

::Ice::Int
IceProxy::M::Test::end_op(::std::string& iceP_sout, const ::Ice::AsyncResultPtr& result)
{
    ::Ice::AsyncResult::_check(result, this, iceC_M_Test_op_name);
    ::Ice::Int ret;
    if(!result->_waitForResponse())
    {
        try
        {
            result->_throwUserException();
        }
        catch(const ::Ice::UserException& ex)
        {
            throw ::Ice::UnknownUserException(__FILE__, __LINE__, ex.ice_id());
        }
    }
    ::Ice::InputStream* istr = result->_startReadParams();
    istr->read(iceP_sout);
    istr->read(ret);
    result->_endReadParams();
    return ret;
}

void IceProxy::M::Test::_iceI_end_op(::std::string& iceP_sout, ::Ice::Int& ret, const ::Ice::AsyncResultPtr& result)
{
    ::Ice::AsyncResult::_check(result, this, iceC_M_Test_op_name);
    if(!result->_waitForResponse())
    {
        try
        {
            result->_throwUserException();
        }
        catch(const ::Ice::UserException& ex)
        {
            throw ::Ice::UnknownUserException(__FILE__, __LINE__, ex.ice_id());
        }
    }
    ::Ice::InputStream* istr = result->_startReadParams();
    istr->read(iceP_sout);
    istr->read(ret);
    result->_endReadParams();
}

/// \cond INTERNAL
::IceProxy::Ice::Object*
IceProxy::M::Test::_newInstance() const
{
    return new Test;
}
/// \endcond

const ::std::string&
IceProxy::M::Test::ice_staticId()
{
    return ::M::Test::ice_staticId();
}

M::Test::~Test()
{
}

/// \cond INTERNAL
::Ice::Object* M::upCast(Test* p) { return p; }

/// \endcond

namespace
{
const ::std::string iceC_M_Test_ids[2] =
{
    "::Ice::Object",
    "::M::Test"
};

}

bool
M::Test::ice_isA(const ::std::string& s, const ::Ice::Current&) const
{
    return ::std::binary_search(iceC_M_Test_ids, iceC_M_Test_ids + 2, s);
}

::std::vector< ::std::string>
M::Test::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&iceC_M_Test_ids[0], &iceC_M_Test_ids[2]);
}

const ::std::string&
M::Test::ice_id(const ::Ice::Current&) const
{
    return ice_staticId();
}

const ::std::string&
M::Test::ice_staticId()
{
#ifdef ICE_HAS_THREAD_SAFE_LOCAL_STATIC
    static const ::std::string typeId = "::M::Test";
    return typeId;
#else
    return iceC_M_Test_ids[1];
#endif
}

/// \cond INTERNAL
bool
M::Test::_iceD_op(::IceInternal::Incoming& inS, const ::Ice::Current& current)
{
    _iceCheckMode(::Ice::Normal, current.mode);
    ::Ice::InputStream* istr = inS.startReadParams();
    ::std::string iceP_sin;
    istr->read(iceP_sin);
    inS.endReadParams();
    ::std::string iceP_sout;
    ::Ice::Int ret = this->op(iceP_sin, iceP_sout, current);
    ::Ice::OutputStream* ostr = inS.startWriteParams();
    ostr->write(iceP_sout);
    ostr->write(ret);
    inS.endWriteParams();
    return true;
}
/// \endcond

namespace
{
const ::std::string iceC_M_Test_all[] =
{
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping",
    "op"
};

}

/// \cond INTERNAL
bool
M::Test::_iceDispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair<const ::std::string*, const ::std::string*> r = ::std::equal_range(iceC_M_Test_all, iceC_M_Test_all + 5, current.operation);
    if(r.first == r.second)
    {
        throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
    }

    switch(r.first - iceC_M_Test_all)
    {
        case 0:
        {
            return _iceD_ice_id(in, current);
        }
        case 1:
        {
            return _iceD_ice_ids(in, current);
        }
        case 2:
        {
            return _iceD_ice_isA(in, current);
        }
        case 3:
        {
            return _iceD_ice_ping(in, current);
        }
        case 4:
        {
            return _iceD_op(in, current);
        }
        default:
        {
            assert(false);
            throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
        }
    }
}
/// \endcond

/// \cond STREAM
void
M::Test::_iceWriteImpl(::Ice::OutputStream* ostr) const
{
    ostr->startSlice(ice_staticId(), -1, true);
    ::Ice::StreamWriter< Test, ::Ice::OutputStream>::write(ostr, *this);
    ostr->endSlice();
}

void
M::Test::_iceReadImpl(::Ice::InputStream* istr)
{
    istr->startSlice();
    ::Ice::StreamReader< Test, ::Ice::InputStream>::read(istr, *this);
    istr->endSlice();
}
/// \endcond

/// \cond INTERNAL
void
M::_icePatchObjectPtr(TestPtr& handle, const ::Ice::ObjectPtr& v)
{
    handle = TestPtr::dynamicCast(v);
    if(v && !handle)
    {
        IceInternal::Ex::throwUOE(Test::ice_staticId(), v);
    }
}
/// \endcond

namespace Ice
{
}

#endif
