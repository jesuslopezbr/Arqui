
#include <testI.h>
using namespace std;
::Ice::Int
M::TestI::op(const ::std::string& sin,
             ::std::string& sout,
             const Ice::Current& current)
{

    sout = "DNI:";
    cout <<"El Dni es " << sin << endl;
    sout = "Nombre:";
    cout <<"El Nombre es " << sin << endl;
    sout = "Nombre:";
    return 0;
}
