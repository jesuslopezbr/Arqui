#include "interfaz.h"
#include <Ice/Ice.h>

using namespace std;
using namespace Demo;

int main(int argc, char* argv[])
{

  int status = 0, opcion = 0;

  Ice::CommunicatorPtr ic;
  try {
    ic = Ice::initialize(argc, argv);

    Ice::ObjectPrx base = ic->stringToProxy("interfaz:default -p 10000");

    interfazPrx remoteService = interfazPrx::checkedCast(base);
    if (!remoteService)
      throw "Invalid proxy";

    // your client code here!
    int ex = 0, thread_control = 0;

    do
    {

      do
      {
        cout << endl << "[1] Imprimir datos de clientes";
        cout << endl << "[2] Alta de usuario";
        cout << endl << "[3] Baja de usuario";
        cout << endl << "[4] Cambio de tarifa";
        cout << endl << "[5] Actualizar descuentos";
        cout << endl << "[6] Terminar" << endl;
        cout << endl << "Opcion: ";

        cin >> opcion;
        cout << endl;

        if(cin.fail()){
          cout << endl << "ERROR -- You did not enter an integer" << endl;
          cin.clear();
          cin.ignore(80, '\n');
        }
      }while(opcion < 1 || opcion > 6);


      switch(opcion)
      {
        case 1:
          //imprimir_datos_c1();
          cout << "Opción no disponible\n";
          break;
        case 2:
          remoteService->altaUsr();
          break;
        case 3:
          remoteService->bajaUsr();
          break;
        case 4:
          remoteService->cambiarTarifa();
          break;
        case 5:
          if(thread_control == 0){
            int times = atoi(argv[1]);
            remoteService->actualizarDesc(times);
            thread_control = 1;
          }else
            printf("Opción ya activada\n");
          break;
        case 6:
          remoteService->terminar();
          ex = 1;
          break;
        default:
          break;
      }

    }while(ex == 0);


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
