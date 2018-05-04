#ifndef __testI_h__
#define __testI_h__

#include <test.h>
//base

namespace M
{

class TestI : public virtual Test
{
public:

    virtual int op(::std::string&,
                   ::std::string&,
                   const Ice::Current&) override;
};

}

#endif
