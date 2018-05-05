module Demo {
 interface interfaz {
  void checkUsr(string dni,out string sout);
  void altaUsr(string dni, string nombre, byte tarifa, string alta, string descuento,out string sout);
  void bajaUsr(string dni, out string sout);
  void actualizarDesc(int time, out string sout);
  void checkFact(out string sout);
  void cambiarTarifa(string dni, byte, tarifa, out string sout);
  void terminar(out string sout);
 };
};
