
#include <interfazI.h>

void
Demo::interfazI::checkUsr(const ::std::string& dni,
                          ::std::string& sout,
                          const Ice::Current& current)
{
}

void
Demo::interfazI::altaUsr(const ::std::string& dni,
                         const ::std::string& nombre,
                         ::Ice::Byte tarifa,
                         const ::std::string& alta,
                         const ::std::string& descuento,
                         const Ice::Current& current)
{
}

void
Demo::interfazI::bajaUsr(const ::std::string& dni,
                         const Ice::Current& current)
{
}

void
Demo::interfazI::actualizarDesc(::Ice::Int time,
                                const Ice::Current& current)
{
}

void
Demo::interfazI::cambiarTarifa(const ::std::string& dni,
                               const Ice::Current& current)
{
}

void
Demo::interfazI::terminar(const Ice::Current& current)
{
}
