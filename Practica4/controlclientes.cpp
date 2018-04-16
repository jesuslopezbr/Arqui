#include <string.h>
#include <iostream>
using namespace std;

#define MAX_CLIENTES 50

int i = 0, clientes = 0;

struct info_cliente
{
  unsigned dni;
  string nombre;
  char tarifa;
  unsigned alta;
  unsigned descuento;
};
typedef struct info_cliente info_cliente_t;

info_cliente_t datos_c1[MAX_CLIENTES];

void menu()
{
  cout << endl << "[1] Imprimir datos de clientes";
  cout << endl << "[2] Alta de usuario";
  cout << endl << "[3] Baja de usuario";
  cout << endl << "[4] Cambio de tarifa";
  cout << endl << "[5] Actualizar descuentos";
  cout << endl << "[6] Terminar" << endl;
  cout << endl << "Opcion: ";
}

void imprimir_datos_c1()
{
  if(datos_c1[0].dni == NULL)
  {
    cout << endl << "No hay clientes dados de alta" << endl;
  }
  else
  {
    for(i=0; i<clientes; i++)
    {
      cout << i+1 << ": " << datos_c1[i].dni << " | " << datos_c1[i].nombre << " | " << datos_c1[i].tarifa << " | " << datos_c1[i].alta << " | " << datos_c1[i].descuento << endl;
    }
  }
}

void alta_usr()
{
  unsigned alta;
  int clientes2 = clientes;
  int a = 0;
  cout << endl << "DNI del usuario: ";
  cin >> alta;
  for(i=0; i<clientes; i++)
  {
    if(alta == datos_c1[i].dni)
    {
      cout << endl << "El usuario con DNI: " << alta << " ya figura en el sistema" << endl;
      a = 1;
      break;
    }
  }
  if(a == 0)
  {
    datos_c1[clientes2].dni = alta;
    cout << "Nombre del usuario: ";
    cin >> datos_c1[clientes2].nombre;
    cout << "Tarifa inicial: ";
    cin >> datos_c1[clientes2].tarifa;
    cout << "Fecha de alta: ";
    cin >> datos_c1[clientes2].alta;
    cout << "Descuento inicial: ";
    cin >> datos_c1[clientes2].descuento;
    clientes++;
  }
}

void baja_usr()
{
  unsigned baja;
  cout << endl << "Indique el DNI del usuario que quiere dar de baja: ";
  cin >> baja;
  for(i=0; i<clientes; i++)
  {
    if(baja == datos_c1[i].dni)
    {
      datos_c1[i]=datos_c1[i+1];
      cout << endl << "El usuario con DNI: " << baja << " ha sido dado de baja" << endl;
      clientes--;
    }
  }
  if((datos_c1[i].dni != baja) && (i == clientes))
  {
    cout << endl << "El usuario con DNI: " << baja << " no esta dado de alta" << endl;
  }
}

void cambiar_tarifa()
{
  unsigned tar_dni;
  char tar_tar;
  cout << endl << "Indique el DNI del usuario que quiere cambiar la tarifa: ";
  cin >> tar_dni;
  for(i=0; i<clientes; i++)
  {
    if(tar_dni == datos_c1[i].dni)
    {
      cout << endl << "Nueva tarifa: ";
      cin >> tar_tar;
      datos_c1[i].tarifa = tar_tar;
      cout << endl << "Tarifa actualizada" << endl;
    }
  }
}

int main (int argc, char *argv[])
{
  int ex = 0, opcion = 0;

  do{

    do
    {
      menu();
      cin >> opcion;
      cout << endl;
    }while(opcion < 1 || opcion > 6);

    switch(opcion)
    {
      case 1:
        imprimir_datos_c1();
        break;
      case 2:
        alta_usr();
        break;
      case 3:
        baja_usr();
        break;
      case 4:
        cambiar_tarifa();
        break;
      case 6:
        ex = 1;
        break;
      default:
        break;
    }

  }while(ex == 0);

  return 0;
}
