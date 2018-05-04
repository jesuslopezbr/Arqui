#ifndef __testI_h__
#define __testI_h__

#include <test.h>

namespace M
{

class TestI : virtual public Test
{
public:

    virtual ::Ice::Int op(const ::std::string&,
                          ::std::string&,
                          const Ice::Current&);
};

}

#endif
