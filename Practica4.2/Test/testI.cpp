
#include <testI.h>

int
M::TestI::op(::std::string& sin,
             ::std::string& sout,
             const Ice::Current& current)
{
    cout << sin << endl;
    sout = "Hello";
    return 0;
}
