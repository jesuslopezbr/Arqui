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
  act_desc(time);
}

void
Demo::interfazI::cambiarTarifa(const Ice::Current& current)
{
  cambiar_tarifa();
}

void
Demo::interfazI::terminar(const Ice::Current& current)
{
  terminarP();
}
