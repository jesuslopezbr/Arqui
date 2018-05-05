#ifndef __interfazI_h__
#define __interfazI_h__

#include <interfaz.h>

namespace Demo
{

class interfazI : virtual public interfaz
{
public:

    virtual void altaUsr(const Ice::Current&);

    virtual void bajaUsr(const Ice::Current&);

    virtual void actualizarDesc(::Ice::Int,
                                const Ice::Current&);

    virtual void cambiarTarifa(const Ice::Current&);

    virtual void terminar(const Ice::Current&);
};

}

#endif
