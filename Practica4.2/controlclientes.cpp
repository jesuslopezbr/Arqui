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
pthread_mutex_t fact_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cambio_desc = PTHREAD_COND_INITIALIZER;

int i = 0, clientes = 0;
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
  pthread_mutex_lock(&clients_mutex);
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
  pthread_mutex_unlock(&clients_mutex);
}

void clear_fail_state(){
  cout << endl << "ERROR -- You did not enter an integer" << endl;
  cin.clear();
  cin.ignore(80, '\n');
}

string check_usr(unsigned dni, int option) {
  imprimir_datos_c1();
  string sout;
  string dni_s;
  stringstream ss;
  pthread_mutex_lock(&clients_mutex);
  if(option == 0){
    for(i=0; i<clientes; i++)
    {
      if(dni == datos_c1[i].dni)
      {
        ss  << "El usuario con DNI: " << dni << " ya figura en el sistema";
        sout = ss.str();
        pthread_mutex_unlock(&clients_mutex);
        return sout;
      }
    }
  }else if(option == 1){
    for(i=0; i<clientes; i++)
    {
      if(dni == datos_c1[i].dni)
      {
        ss << i;
        sout = ss.str();
        pthread_mutex_unlock(&clients_mutex);
        return sout;
      }
    }
  }else if(option == 2){
    for(i=0; i<clientes; i++)
    {
      if(dni == datos_c1[i].dni)
      {
        pthread_mutex_unlock(&clients_mutex);
        return "Ok";
      }
    }

  }
  if (option == 0){
    pthread_mutex_unlock(&clients_mutex);
    return "Ok";
  }
  else if  (option == 1 || option == 2){
    ss << "El usuario con DNI: " << dni << " no esta dado de alta";
    sout = ss.str();
    pthread_mutex_unlock(&clients_mutex);
    return sout;
  }
  else{
    pthread_mutex_unlock(&clients_mutex);
    return "";
  }
}

string alta_usr(unsigned dni, string nombre, char tarifa, unsigned alta, unsigned desc)
{
  int clientes2 = clientes;
  string sout;
  stringstream ss;
  pthread_mutex_lock(&clients_mutex);
  datos_c1[clientes2].dni = dni;
  datos_c1[clientes2].nombre = nombre;
  datos_c1[clientes2].tarifa = tarifa;
  datos_c1[clientes2].alta = alta;
  datos_c1[clientes2].descuento = desc;
  clientes++;
  pthread_mutex_unlock(&clients_mutex);
  ss  << "Cliente con dni " << dni << " añadido.";
  sout = ss.str();

  imprimir_datos_c1();

  return sout;
}

string baja_usr(int i)
{
  unsigned baja;
  int control = 0;
  int j;
  string sout;
  stringstream ss;
  pthread_mutex_lock(&clients_mutex);
  for(j = i; j<clientes;j++)
  {
    datos_c1[j]=datos_c1[j+1];
  }
  clientes--;
  pthread_mutex_unlock(&clients_mutex);
  ss  << "Cliente dado de baja.";
  sout = ss.str();

  imprimir_datos_c1();

  pthread_cond_signal(&cambio_desc);
  return sout;
}

string cambiar_tarifa(unsigned dni, char tarifa)
{
  string sout;
  stringstream ss;
  for(i=0; i<clientes; i++)
  {
    pthread_mutex_lock(&clients_mutex);
    if(dni == datos_c1[i].dni)
    {

      datos_c1[i].tarifa = tarifa;
      datos_c1[i].descuento = 0;
    }
    pthread_mutex_unlock(&clients_mutex);
  }

  ss  << "Tarifa cambiada a " << tarifa << ".";
  sout = ss.str();

  imprimir_datos_c1();

  return sout;
}

void *facturacion(void * time)
{
  int fact = 0;
  string to_s;
  stringstream ss;

  do
  {
    ss.str("");
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
      ss << endl << "Nueva facturacion estimada: " << fact << " euros ";
      pthread_mutex_lock(&fact_mutex);
      fact_s = ss.str();
      fact_c = 1;
      pthread_mutex_unlock(&fact_mutex);
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
  pthread_mutex_lock(&fact_mutex);
  if(fact_c == 1){
    fact_c = 0;
    pthread_mutex_unlock(&fact_mutex);
    return fact_s;
  }else{
    pthread_mutex_unlock(&fact_mutex);
    return "";
  }
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
  pthread_mutex_lock(&loop_mutex);
  loop = 0;
  pthread_mutex_unlock(&loop_mutex);

  pthread_join(h_desc,NULL);
  cout << endl << "Recibida solicitud de terminacion de cliente." << endl;
  cout << endl << "Cliente terminado!" << endl << endl;
}
