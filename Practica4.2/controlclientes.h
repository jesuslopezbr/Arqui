void menu();

void imprimir_datos_c1();

void clear_fail_state();

string check_usr(unsigned dni, int option);

string alta_usr(unsigned dni, string nombre, char tarifa, unsigned alta, unsigned desc);

string baja_usr(int i);

string cambiar_tarifa(unsigned dni, char tarifa);

void *facturacion(void * time);

void *actualizar_desc(void * time);

void act_desc(int time);

void terminarP();
