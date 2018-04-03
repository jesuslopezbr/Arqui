#ifndef __StringServiceI_h__
#define __StringServiceI_h__

#include "StringService.h"

namespace UC3M
{

class StringServiceI : public virtual StringService
{
public:

    virtual ::Ice::Int stringSize(const ::std::string&,
                                  const Ice::Current&);

    virtual ::std::string toUpperCase(const ::std::string&,
                                      const Ice::Current&);
};

}

#endif
