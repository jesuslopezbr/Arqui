#include <StringServiceI.h>
#include <StringService.h>
#include <Ice/Ice.h>

using namespace std;
using namespace UC3M;

int
main(int argc, char* argv[]){
  int status = 0;
  Ice::CommunicatorPtr ic;
  try{
    ic = Ice::initialize(argc,argv);
    Ice::ObjectAdapterPtr adapter =
      ic -> createObjectAdapterWithEndpoints("asii_adapter",
        "default -p 10000");
    Ice::ObjectPtr object = new StringServiceI;
    adapter -> add(object, ic -> stringToIdentity("StringService"));
    adapter -> activate();
    ic -> waitForShutdown();
  } catch (const Ice::Exception& e){
    cerr << e << endl;
    status = 1;
  } catch (const char* msg){
    cerr << msg << endl;
    status = 1;
  }

  if (ic){
    try{
      ic -> destroy();
    } catch (const Ice::Exception& e){
      cerr << e << endl;
      status = 1;
    }
  }
  return status;
}
