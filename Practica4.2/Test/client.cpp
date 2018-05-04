#include <testI.h>
#include <test.h>
#include <Ice/Ice.h>

using namespace std;
using namespace M;


int
main(int argc, char* argv[])
{

  int status = 0;
  string text = "";
  string opcion;

  Ice::CommunicatorPtr ic;
  try {
    ic = Ice::initialize(argc, argv);

    Ice::ObjectPrx base = ic->stringToProxy("Test:default -p 10000");

    TestPrx remoteService = TestPrx::checkedCast(base);
    if (!remoteService)
      throw "Invalid proxy";

    // your client code here!

    remoteService->op("",text);
    cout << text;
    cin >> opcion;
    remoteService->op("opcion",text);
    cout << text;

  } catch (const Ice::Exception& ex) {

    cerr << ex << endl;
    status = 1;
  } catch (const char* msg) {

    cerr << msg << endl;
    status = 1;

  }

  if (ic)
  ic->destroy();

  return status;
}
