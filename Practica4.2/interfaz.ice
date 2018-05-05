module Demo {
 interface interfaz {
  void check_usr(string dni,out string sout)
  void altaUsr(unsigned dni, string nombre, char tarifa, unsigned alta, unsigned descuento);
  void bajaUsr(unsigned dni);
  void actualizarDesc(int time);
  void cambiarTarifa(unsigned dni);
  void terminar();
 };
};
