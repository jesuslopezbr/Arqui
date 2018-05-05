#include "interfaz.h"
#include <Ice/Ice.h>

using namespace std;
using namespace Demo;

unsigned dni_req(){
  unsigned dni;
  cout << endl << "DNI del usuario: ";
  cin >> dni;
  if(cin.fail())
  {
    clear_fail_state();
  }
  if(dni < 10000000 || dni > 99999999)
  {
    cout << endl << "No se puede tener un menor de 8 caracteres DNI: " << dni << endl;
    return 0;
  }
  else{
    return alta;
  }
}

int main(int argc, char* argv[])
{

  int status = 0, opcion = 0;
  unsigned dni;
  string control;
  string nombre;
  char tarifa;
  unsigned alta;
  unsigned descuento;
  string fact;

  Ice::CommunicatorPtr ic;
  try {
    ic = Ice::initialize(argc, argv);

    Ice::ObjectPrx base = ic->stringToProxy("interfaz:default -p 10000");

    interfazPrx remoteService = interfazPrx::checkedCast(base);
    if (!remoteService)
      throw "Invalid proxy";

    // your client code here!
    int ex = 0, thread_control = 0;
    int times = atoi(argv[1]);

    do
    {
      fact = remoteService->checkFact();
      if(fact != ""){
        cout << fact << endl;
        fact = "";
      }
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
          dni = dni_req();
          control = remoteService->checkUsr(dni,0);
          if(control == "Ok")
          cout << "Nombre del usuario: ";
          cin >> nombre;
          cout << "Tarifa inicial: ";
          cin >> tarifa;
          cout << "Fecha de alta: ";
          cin >> alta;
          cout << "Descuento inicial: ";
          cin >> descuento;
            remoteService->altaUsr(dni, nombre, tarifa, alta, descuento);
          else
            cout << control << endl;
          break;
        case 3:
          dni = dni_req();
          control = remoteService->checkUsr(dni,1);
          if(control = "El usuario con DNI: " << dni << " no esta dado de alta")
            cout << control << endl;
          else{
            control = remoteService->bajaUsr(stoi(control));
            cout << control << endl;
          }
          break;
        case 4:
          dni = dni_req();
          control = remoteService->checkUsr(dni,1);
          if(control = "El usuario con DNI: " << dni << " no esta dado de alta")
            cout << control << endl;
          else{
            cin >> tarifa;
            control = remoteService->cambiarTarifa(dni, tarifa);
            cout << control << endl;
          }
          break;
        case 5:
          if(thread_control == 0){
            cout << endl << "Solicitud de activacion de actualizacion de tarifas al servidor central en curso..." << endl;
            remoteService->actualizarDesc(times);
            cout << endl << "Resultado: Actualizacion automatica de tarifas activado en el servidor. " << endl;
            thread_control = 1;
          }else{
            cout << endl << "Opción ya activada" << endl;
          }
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
  {
      ic->destroy();
  }

  return status;
}
