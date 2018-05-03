#include <string>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>

using namespace std;

#define MAX_CLIENTES 50

pthread_t h_desc, h_factura;
pthread_mutex_t clients_mutex;
pthread_mutex_t loop_mutex;
pthread_cond_t cambio_desc;

int i = 0, clientes = 0;
int loop = 1;

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

void alta_usr()
{
  unsigned alta;
  int clientes2 = clientes;
  int a = 0;
  cout << endl << "DNI del usuario: ";
  cin >> alta;

  if(cin.fail())
  {
    clear_fail_state();
    a = 1;
  }

  if(alta < 10000000 || alta > 99999999)
  {
    cout << endl << "No se puede tener un menor de 8 caracteres DNI: " << alta << endl;
    a = 1;
  }

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
    cout << endl << "Solicitud de alta al servidor central en curso..." << endl;
    cout << "Resultado: Usuario dado de alta" << endl;
  }
}

void baja_usr()
{
  unsigned baja;
  int control = 0;
  int j;

  cout << endl << "Indique el DNI del usuario que quiere dar de baja: ";
  cin >> baja;

  for(i=0; i<clientes; i++)
  {
    if(baja == datos_c1[i].dni)
    {
      for(j = i; j<clientes;j++)
      {
        datos_c1[j]=datos_c1[j+1];
      }

      cout << endl << "El usuario con DNI: " << baja << " ha sido dado de baja" << endl;
      clientes--;
      pthread_cond_signal(&cambio_desc);
      control = 1;
    }
  }

  if(control == 0)
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
      datos_c1[i].descuento = 0;
    }
  }
}

void *facturacion(void * time)
{
  int fact = 0;

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
      cout << endl << "Nueva facturacion estimada: " << fact << " euros" << endl;
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

void terminar()
{
  cout << "Avisando a cliente de la terminacion!" << endl;
  cout << "Servidor terminado!" << endl << endl;
}

int main (int argc, char *argv[])
{
  int ex = 0, opcion = 0;
  int ch, thread_control = 0;
  long time = atoi(argv[1]);

  pthread_mutex_init(&clients_mutex,NULL);
  pthread_mutex_init(&loop_mutex,NULL);
  pthread_cond_init(&cambio_desc, NULL);

  do
  {

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
        if(thread_control == 0){
          ch = pthread_create(&h_desc, NULL, actualizar_desc, (void *)time);
          cout << "Solicitud de activacion de actualizacion de tarifas al servidor central en curso..." << endl;
          cout << "Resultado: Actualizacion automatica de tarifas activado en el servidor. " << endl;
          if(ch){
            printf("ERROR: return code from pthread_create() is %d\n", ch);
            exit(-1);
          }
          thread_control = 1;
        }else
          printf("Opción ya activada\n");
        break;
      case 6:
        pthread_mutex_unlock(&clients_mutex);

        pthread_mutex_lock(&loop_mutex);
        loop = 0;
        pthread_mutex_unlock(&loop_mutex);

        pthread_join(h_desc,NULL);

        pthread_mutex_destroy(&clients_mutex);
        pthread_mutex_destroy(&loop_mutex);
        pthread_cond_destroy(&cambio_desc);
        terminar();
        pthread_exit(NULL);
        ex = 1;
        break;
      default:
        break;
    }

    pthread_mutex_unlock(&clients_mutex);

  }while(ex == 0);

  return 0;
}
