#include <string.h>
#include <pthread.h>
#include <stdlib.h>

#include <iostream>
#include <stdio.h>

using namespace std;

#define MAX_CLIENTES 50
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

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
  if(datos_c1[0].dni == 0)
  {
    cout << endl << "No hay clientes dados de alta" << endl;
  }
  else
  {
    cout << "Listado de clientes:" << endl;
    for(i=0; i<clientes; i++)
    {
      cout << i+1 << ": " << datos_c1[i].dni << " | " << datos_c1[i].nombre << " | " << datos_c1[i].tarifa << " | " << datos_c1[i].alta << " | " << datos_c1[i].descuento << endl;
    }
  }
}

void clear_fail_state(){
    cout << "ERROR -- You did not enter an integer";

    // get rid of failure state
    cin.clear();
    cin.ignore(80, '\n');

}

void alta_usr()
{
  unsigned alta;
  int clientes2 = clientes;
  int a = 0;
  cout << endl << "DNI del usuario: ";
  cin >> alta;

  if(cin.fail()){
    clear_fail_state();
    a=1;
  }

  if(alta < 10000000 && alta > 99999999){
    cout << endl << "No se puede tener un menor de 8 caracteres DNI: " << alta << endl;
    a  = 1;
  }

  for(i=0; i<clientes; i++)
  {
      if(alta == datos_c1[i].dni){
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
    cout << endl << "Solicitud de alta al servidor central en curso..." << endl;
    cout << "Resultado: Usuario dado de alta" << endl;
  }
}

void baja_usr()
{
  unsigned baja;
  cout << endl << "Indique el DNI del usuario que quiere dar de baja: ";
  cin >> baja;
  for(i=0; i<clientes; i++){
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
      cout << endl << "Solicitud de cambio de tarifa al servidor central en curso..." << endl;
      cout << "Resultado: Cambio de tarifa efectuado" << endl;
    }
  }
}

void *actualizar_desc(void * time)
{
  long sle = (long) time;
  pthread_mutex_lock(&clients_mutex);
  for(i=0; i<clientes; i++)
  {
      if(datos_c1[i].tarifa == 'A' && datos_c1[i].descuento != 40){
        if(datos_c1[i].alta < 2008)
          datos_c1[i].descuento = 30;
        else if(datos_c1[i].alta >= 2009 && datos_c1[i].alta <= 2012)
          datos_c1[i].descuento = 40;
        else if(datos_c1[i].alta > 2012)
          datos_c1[i].descuento = 25;
        else
          datos_c1[i].descuento = 0;
      }else if(datos_c1[i].tarifa == 'B' && datos_c1[i].descuento != 25){
          datos_c1[i].descuento = 25;
      }else if(datos_c1[i].tarifa == 'C' && datos_c1[i].descuento != 30){
        datos_c1[i].descuento = 30;
      }
    }
    pthread_mutex_unlock(&clients_mutex);
    pthread_exit(NULL);
}

void terminar()
{
  cout << "Avisando a cliente de la terminacion!" << endl;
  cout << "Servidor terminado!" << endl << endl;
}

int main (int argc, char *argv[])
{
  int ex = 0, opcion = 0;
  pthread_t h_desc;
  int ch;
  long time = atoi(argv[1]);

  // pthread_mutex_t clients_mutex;
  //pthread_mutex_init(&clients_mutex,NULL);


  do{

    do
    {
      menu();
      cin >> opcion;
      cout << endl;
      if(cin.fail())
        clear_fail_state();
    }while(opcion < 1 || opcion > 6);
    pthread_mutex_lock(&clients_mutex);
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
      case 5:
        ch = pthread_create(&h_desc, NULL, actualizar_desc, (void *)time);
        if(ch){
          printf("ERROR; return code from pthread_create() is %d\n", ch);
          exit(-1);
        }

        break;
      case 6:
        pthread_exit(NULL);
        terminar();
        ex = 1;
        break;
      default:
        break;
    }

    pthread_mutex_unlock(&clients_mutex);


  }while(ex == 0);

  return 0;
}
