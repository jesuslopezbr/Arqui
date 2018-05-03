#include <controlclientes.h>

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

void terminarP()
{
  cout << "Avisando a cliente de la terminacion!" << endl;
  cout << "Servidor terminado!" << endl << endl;
}