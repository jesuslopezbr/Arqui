#ifndef __interfazI_h__
#define __interfazI_h__

#include <interfaz.h>

namespace Demo
{

class interfazI : virtual public interfaz
{
public:

    virtual void checkUsr(const ::std::string&,
                          ::std::string&,
                          const Ice::Current&);

    virtual void altaUsr(const ::std::string&,
                         const ::std::string&,
                         ::Ice::Byte,
                         const ::std::string&,
                         const ::std::string&,
                         const Ice::Current&);

    virtual void bajaUsr(const ::std::string&,
                         const Ice::Current&);

    virtual void actualizarDesc(::Ice::Int,
                                const Ice::Current&);

    virtual void cambiarTarifa(const ::std::string&,
                               const Ice::Current&);

    virtual void terminar(const Ice::Current&);
};

}

#endif
