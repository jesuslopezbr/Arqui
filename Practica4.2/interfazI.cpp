
#include <interfazI.h>
#include <string>
#include <controlclientes.h>

void
Demo::interfazI::checkUsr(const ::std::string& dni,
                          ::std::string& sout,
                          const Ice::Current& current)
{
  unsigned dni2 = stoul(dni);
  sout << check_usr(dni2);
}

void
Demo::interfazI::altaUsr(const ::std::string& dni,
                         const ::std::string& nombre,
                         ::Ice::Byte tarifa,
                         const ::std::string& alta,
                         const ::std::string& descuento,
                         ::std::string& sout,
                         const Ice::Current& current)
{
  unsigned dni2 = stoul(dni);
  unsigned alta2 = stoul(alta);
  unsigned descuento2 = stoul(descuento);

  sout << alta_usr(dni2, nombre, tarifa, alta2, descuento2);
}

void
Demo::interfazI::bajaUsr(const ::std::string& dni,
                         ::std::string& sout,
                         const Ice::Current& current)
{
  int i = stoi(value);
  sout << baja_usr(i);
}

void
Demo::interfazI::actualizarDesc(::Ice::Int time,
                                ::std::string& sout,
                                const Ice::Current& current)
{
      sout << act_desc(time);
}

void
Demo::interfazI::checkFact(::std::string& sout,
                           const Ice::Current& current)
{
    sout << check_fact();
}

void
Demo::interfazI::cambiarTarifa(const ::std::string& dni,
                               ::Ice::Byte tarifa,
                               ::std::string& sout,
                               const Ice::Current& current)
{
  unsigned dni2 = stoul(dni);
  sout << cambiar_tarifa(dni2, tarifa);
}

void
Demo::interfazI::terminar(::std::string& sout,
                          const Ice::Current& current)
{
    terminarP();
}
