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

int i = 0, clientes = 0, ex = 0;
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

void menu();

void imprimir_datos_c1();

void clear_fail_state();

void alta_usr();

void baja_usr();

void cambiar_tarifa();

void *facturacion(void * time);

void *actualizar_desc(void * time);

void terminarP();
