
#include <controlclientes.h>
#include <interfazI.h>
#include <string>
#include <iostream>

using namespace std;

void
Demo::interfazI::checkUsr(const ::std::string& dni,
                          ::Ice::Int opcion,
                          ::std::string& sout,
                          const Ice::Current& current)
{
  cout << endl << dni << endl;
  unsigned dni2 = stoul(dni,nullptr,0);
  cout << dni2 << endl;
  sout = check_usr(dni2,opcion);
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
  cout << "Recibida solicitud de alta de cliente." << endl;
  unsigned dni2 = stoul(dni,nullptr,0);
  unsigned alta2 = stoul(alta,nullptr,0);
  unsigned descuento2 = stoul(descuento,nullptr,0);

  sout = alta_usr(dni2, nombre, tarifa, alta2, descuento2);
}

void
Demo::interfazI::bajaUsr(const ::std  ::string& dni,
                         ::std::string& sout,
                         const Ice::Current& current)
{
  cout << "Recibida solicitud de baja de cliente." << endl;
  int i = stoi(dni,nullptr,0);
  sout = baja_usr(i);
}

void
Demo::interfazI::actualizarDesc(::Ice::Int time,
                                ::std::string& sout,
                                const Ice::Current& current)
{
  act_desc(time);
}

void
Demo::interfazI::checkFact(::std::string& sout,
                           const Ice::Current& current)
{
  sout = check_fact();
}

void
Demo::interfazI::cambiarTarifa(const ::std::string& dni,
                               ::Ice::Byte tarifa,
                               ::std::string& sout,
                               const Ice::Current& current)
{
  cout << "Recibida solicitud de cambio de tarifa." << endl;
  unsigned dni2 = stoul(dni,nullptr,0);
  sout = cambiar_tarifa(dni2, tarifa);
}

void
Demo::interfazI::terminar(::std::string& sout,
                          const Ice::Current& current)
{
      terminarP();
}
