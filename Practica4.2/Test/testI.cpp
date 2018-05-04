
#include <testI.h>
using namespace std;
::Ice::Int
M::TestI::op(const ::std::string& sin,
             ::std::string& sout,
             const Ice::Current& current)
{
    cout << sin << endl;
    sout = "Hello";
    return 0;
}
