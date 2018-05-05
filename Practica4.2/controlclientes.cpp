#include <string>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <controlclientes.h>
#include <sstream>


using namespace std;

#define MAX_CLIENTES 50

pthread_t h_desc, h_factura;
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t loop_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cambio_desc = PTHREAD_COND_INITIALIZER;

int i = 0, clientes = 0, ex = 0;
int loop = 1;
string fact_s;
int fact_c = 0;

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
    cout << endl << "ERROR -- You did not enter an integer" << endl;
    cin.clear();
    cin.ignore(80, '\n');
}

string check_usr(unsigned dni, int option) {
  string sout;
  string dni_s;
  stringstream ss;
  if(option == 0){
    for(i=0; i<clientes; i++)
    {
      if(dni == datos_c1[i].dni)
      {
        //dni_s = std::to_string(dni);
        ss  << "El usuario con DNI: " << dni_s << " ya figura en el sistema";
        sout = ss.str();
        return sout;
        break;
      }
    }
  }else if(option == 1){
    for(i=0; i<clientes; i++)
    {
      if(dni == datos_c1[i].dni)
      {
        ss << i;
        sout = ss.str();
        return sout;
      }
    }
  }
  if (option == 0)
    return "Ok";
  else if  (option == 1){
    ss << "El usuario con DNI: " << dni << " no esta dado de alta";
    //dni_s = std::to_string(dni);
    sout = ss.str();
    return sout;
  }
  else
  return "";
}

string  alta_usr(unsigned dni, string nombre, char tarifa, unsigned alta, unsigned desc)
{
  int clientes2 = clientes;

    datos_c1[clientes2].dni = dni;
    datos_c1[clientes2].nombre = nombre;
    datos_c1[clientes2].tarifa = tarifa;
    datos_c1[clientes2].alta = alta;
    datos_c1[clientes2].descuento = desc;
    clientes++;
    return "Recibida solicitud de alta de cliente.";
}

string baja_usr(int i)
{
  unsigned baja;
  int control = 0;
  int j;

  for(j = i; j<clientes;j++)
  {
    datos_c1[j]=datos_c1[j+1];
  }

  clientes--;
  pthread_cond_signal(&cambio_desc);
  return "Recibida solicitud de baja de cliente.";


}

string cambiar_tarifa(unsigned dni, char tarifa)
{

  for(i=0; i<clientes; i++)
  {
    pthread_mutex_lock(&clients_mutex);
    if(dni == datos_c1[i].dni)
    {

      datos_c1[i].tarifa = tarifa;
      datos_c1[i].descuento = 0;
      break;
    }
    pthread_mutex_unlock(&clients_mutex);
  }
  return "Recibida solicitud de cambio de tarifa." ;
}

void *facturacion(void * time)
{
  int fact = 0;
  string to_s;
  stringstream ss;

  do
  {
    pthread_mutex_unlock(&loop_mutex);

    fact = 0;

    pthread_mutex_lock(&clients_mutex);

    pthread_cond_wait(&cambio_desc, &clients_mutex);

    pthread_mutex_lock(&loop_mutex);
    if(loop){
      for(i=0; i<clientes; i++)
      {
          if(datos_c1[i].tarifa == 'A'){
            fact += 800;
          }else if(datos_c1[i].tarifa == 'B'){
            fact += 600;
          }else if(datos_c1[i].tarifa == 'C'){
            fact += 300;
          }
      }
      ss << "Nueva facturacion estimada: " << fact << " euros ";
      fact_s = ss.str();
      cout << endl << fact << "--> Aviso enviado a los clientes."<< endl;
    }
    pthread_mutex_unlock(&loop_mutex);

    pthread_mutex_unlock(&clients_mutex);

    pthread_mutex_lock(&loop_mutex);

  }while(loop);

  pthread_mutex_unlock(&loop_mutex);
  pthread_exit(NULL);
}

void *actualizar_desc(void * time)
{
  long sle = (long) time * 1000000;
  int ch;
  int cambio = 0;

  ch = pthread_create(&h_factura, NULL, facturacion, (void *)time);
  if(ch)
  {
    printf("ERROR: return code from pthread_create() is %d\n", ch);
    exit(-1);
  }

  do
  {
    cambio = 0;
    pthread_mutex_unlock(&loop_mutex);

    usleep(sle);

    for(i=0; i<clientes; i++)
    {
        pthread_mutex_lock(&clients_mutex);

        if(datos_c1[i].tarifa == 'A'){
          if(datos_c1[i].alta < 2008 && datos_c1[i].descuento != 30)
          {
            datos_c1[i].descuento = 30;
            cambio = 1;
          }
          else if(datos_c1[i].alta >= 2009 && datos_c1[i].alta <= 2012 && datos_c1[i].descuento != 40)
          {
            datos_c1[i].descuento = 40;
            cambio = 1;
          }
          else if(datos_c1[i].alta > 2012 && datos_c1[i].descuento != 25)
          {
            datos_c1[i].descuento = 25;
            cambio = 1;
          }
        }
        else if(datos_c1[i].tarifa == 'B' && datos_c1[i].descuento != 25)
        {
            datos_c1[i].descuento = 25;
            cambio = 1;
        }
        else if(datos_c1[i].tarifa == 'C' && datos_c1[i].descuento != 30)
        {
          datos_c1[i].descuento = 30;
          cambio = 1;
        }
        pthread_mutex_unlock(&clients_mutex);
    }

    if(cambio)
    {
        pthread_cond_signal(&cambio_desc);
    }

    pthread_mutex_lock(&loop_mutex);

  }while(loop);

  pthread_mutex_unlock(&loop_mutex);
  pthread_cond_signal(&cambio_desc);
  pthread_join(h_factura,NULL);
  pthread_exit(NULL);
}

string check_fact(){
  if(fact_c == 1){
    fact_c = 0;
    return fact_s;
  }else
    return "";
}

void act_desc(long time)
{
  int ch = pthread_create(&h_desc, NULL, actualizar_desc, (void *)time);
  cout << endl << "Recibida solicitud de actualizacion de tarifas." << endl;
  if(ch){
    printf("ERROR: return code from pthread_create() is %d\n", ch);
    exit(-1);
  }
}

void terminarP()
{
  pthread_mutex_unlock(&clients_mutex);

  pthread_mutex_lock(&loop_mutex);
  loop = 0;
  pthread_mutex_unlock(&loop_mutex);

  pthread_join(h_desc,NULL);
  cout << endl << "Recibida solicitud de terminacion.";
  cout << endl << "Servidor terminado!" << endl << endl;
  pthread_exit(NULL);
  ex = 1;
}
