#ifndef __interfazI_h__
#define __interfazI_h__

#include <interfaz.h>
#include <string>

namespace Demo
{

class interfazI : virtual public interfaz
{
public:

    virtual void checkUsr(::std::string&,
                          ::Ice::Int,
                          ::std::string&,
                          const Ice::Current&);

    virtual void altaUsr(const ::std::string&,
                         const ::std::string&,
                         ::Ice::Byte,
                         const ::std::string&,
                         const ::std::string&,
                         ::std::string&,
                         const Ice::Current&);

    virtual void bajaUsr(const ::std::string&,
                         ::std::string&,
                         const Ice::Current&);

    virtual void actualizarDesc(::Ice::Int,
                                ::std::string&,
                                const Ice::Current&);

    virtual void checkFact(::std::string&,
                           const Ice::Current&);

    virtual void cambiarTarifa(const ::std::string&,
                               ::Ice::Byte,
                               ::std::string&,
                               const Ice::Current&);

    virtual void terminar(::std::string&,
                          const Ice::Current&);
};

}

#endif
