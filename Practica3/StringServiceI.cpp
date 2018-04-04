
#include <StringServiceI.h>

::Ice::Int
UC3M::StringServiceI::stringSize(const string& s,
                                 const Ice::Current& current)
{
    return 0;
}

::std::string
UC3M::StringServiceI::toUpperCase(const string& s,
                                  const Ice::Current& current)
{
    return s;
}
