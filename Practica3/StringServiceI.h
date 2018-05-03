#ifndef __StringServiceI_h__
#define __StringServiceI_h__

#include <StringService.h>

namespace UC3M
{

class StringServiceI : virtual public StringService
{
public:

    virtual ::Ice::Int stringSize(const string& s,
                                  const Ice::Current&);

    virtual string toUpperCase(const string& s,
                                      const Ice::Current&);
};

}

#endif
