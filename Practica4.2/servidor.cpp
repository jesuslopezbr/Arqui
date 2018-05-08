#include "interfazI.h"
#include <Ice/Ice.h>

using namespace std;
using namespace Demo;

int main(int argc, char* argv[])
{
  string port = argv[1];
 int status = 0;
 Ice::CommunicatorPtr ic;
 try {
   ic = Ice::initialize(argc, argv);
   Ice::ObjectAdapterPtr adapter =
   ic->createObjectAdapterWithEndpoints("asii_adapter",
   "default -p " << port);
   Ice::ObjectPtr object = new interfazI;
   adapter->add(object, ic->stringToIdentity("interfaz"));
   adapter->activate();
   ic->waitForShutdown();
 } catch (const Ice::Exception& e) {
   cerr << e << endl;
   status = 1;
 } catch (const char* msg) {
   cerr << msg << endl;
   status = 1;
 }

 if (ic) {
   try {
     ic->destroy();
   } catch (const Ice::Exception& e) {
     cerr << e << endl;
     status = 1;
   }
 }
 return status;
}
