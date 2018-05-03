#include <controlclientes.h>
#include <interfazI.h>

void
Demo::interfazI::altaUsr(const Ice::Current& current)
{
  alta_usr();
}

void
Demo::interfazI::bajaUsr(const Ice::Current& current)
{
  baja_usr();
}

void
Demo::interfazI::actualizarDesc(::Ice::Int time,
                                const Ice::Current& current)
{
  int ch = pthread_create(&h_desc, NULL, actualizar_desc, (void *)time);
  cout << "Solicitud de activacion de actualizacion de tarifas al servidor central en curso..." << endl;
  cout << "Resultado: Actualizacion automatica de tarifas activado en el servidor. " << endl;
  if(ch){
    printf("ERROR: return code from pthread_create() is %d\n", ch);
    exit(-1);
  }
}

void
Demo::interfazI::cambiarTarifa(const Ice::Current& current)
{
  cambiar_tarifa();
}

void
Demo::interfazI::terminar(const Ice::Current& current)
{
  loop = 0;
  pthread_join(h_desc,NULL);
  terminar();
  pthread_exit(NULL);
  ex = 1;
}
