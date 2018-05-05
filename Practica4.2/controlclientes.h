#include <string>


void menu();

void imprimir_datos_c1();

void clear_fail_state();

std::string check_usr(unsigned dni, int option);

std::string alta_usr(unsigned dni, std::string nombre, char tarifa, unsigned alta, unsigned desc);

std::string baja_usr(int i);

std::string cambiar_tarifa(unsigned dni, char tarifa);

std::string check_fact();

void *facturacion(void * time);

void *actualizar_desc(void * time);

void act_desc(int time);

void terminarP();
