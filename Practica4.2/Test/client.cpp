#include <testI.h>
#include <Ice/Ice.h>

using namespace std;
using namespace M;


int
main(int argc, char* argv[])
{

  int status = 0;
  string text = "";

  Ice::CommunicatorPtr ic;
  try {
    ic = Ice::initialize(argc, argv);

    Ice::ObjectPrx base = ic->stringToProxy("StringService:default -p 10000");

    StringServicePrx remoteService = StringServicePrx::checkedCast(base);
    if (!remoteService)
      throw "Invalid proxy";

    // your client code here!

    cout << remoteService->op("do it",text) << endl;
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
