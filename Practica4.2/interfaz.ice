module Demo {
 interface interfaz {
  void checkUsr(string dni,out string sout);
  void altaUsr(string dni, string nombre, char tarifa, string alta, string descuento);
  void bajaUsr(string dni);
  void actualizarDesc(int time);
  void cambiarTarifa(string dni);
  void terminar();
 };
};
