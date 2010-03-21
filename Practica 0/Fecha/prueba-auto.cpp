#include "fecha.h"
#include "fct.h"
#include <ctime>
using namespace std;

#define fecha_is_eq(f, d, m, y)\
  (f.dia() == d && f.mes() == m && f.anno() == y)

#define chk_eq_fecha(f, d, m, y)\
  fct_xchk(\
    fecha_is_eq(f,d,m,y),\
    "failed chk_eq_fecha:\n<%02d/%02d/%04d>!=<%02d/%02d/%04d>",\
    f.dia(), f.mes(), f.anno(), d, m, y)

FCT_BGN() {
  int annoSistema, mesSistema, diaSistema;

  FCT_FIXTURE_SUITE_BGN(Fecha) {
    FCT_SETUP_BGN() {
      const time_t ahora = time(0);
      const tm* fecha = localtime(&ahora);
      annoSistema = 1900 + fecha->tm_year;
      mesSistema = 1 + fecha->tm_mon;
      diaSistema = fecha->tm_mday;
    }
    FCT_SETUP_END();

    FCT_TEARDOWN_BGN() {
    }
    FCT_TEARDOWN_END();

    FCT_TEST_BGN(Ctor: dia - mes - anyo) {
      const Fecha f(9, 10, 1999);
      chk_eq_fecha(f, 9, 10, 1999);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Ctor: dia - mes) {
      const Fecha f(3, 7);
      chk_eq_fecha(f, 3, 7, annoSistema);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Ctor: dia) {
      const Fecha f(2);
      chk_eq_fecha(f, 2, mesSistema, annoSistema);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Ctor: sin argumentos) {
      const Fecha f;
      chk_eq_fecha(f, diaSistema, mesSistema, annoSistema);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Ctor: copia) {
      const Fecha f(2, 3, 2000);
      const Fecha g(f);
      chk_eq_fecha(f, g.dia(), g.mes(), g.anno());
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Ctor: cadena 2/2/4) {
      const Fecha f("10/12/2011");
      chk_eq_fecha(f, 10, 12, 2011);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Ctor: cadena 1/1/4) {
      const Fecha f = "1/5/2010";
      chk_eq_fecha(f, 1, 5, 2010);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Ctor: dia no valido) {
      try {
        Fecha f(31, 6, 2009);
        fct_chk(!"Se esperaba una excepción");
      } catch (Fecha::Invalida) {
        fct_chk(true);
      }
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Ctor: mes no valido) {
      try {
        Fecha f(1, -1, 2020);
        fct_chk(!"Se esperaba una excepción");
      } catch (Fecha::Invalida) {
        fct_chk(true);
      }
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Ctor: anno no valido) {
      try {
        Fecha f(1, 1, -1);
        fct_chk(!"Se esperaba una excepción");
      } catch (Fecha::Invalida) {
        fct_chk(true);
      }
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Preincremento) {
      Fecha f(31, 3, 2010);
      Fecha g(++f);
      chk_eq_fecha(f, 1, 4, 2010);
      chk_eq_fecha(g, 1, 4, 2010);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Postdecremento) {
      Fecha f(1, 1, 2010);
      Fecha g(f--);
      chk_eq_fecha(f, 31, 12, 2009);
      chk_eq_fecha(g, 1, 1, 2010);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Suma de dias - dias + fecha) {
      const Fecha f(30, 4, 2003);
      const Fecha g(10 + f);
      chk_eq_fecha(g, 10, 5, 2003);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Resta de dias - fecha - dias) {
      const Fecha f(1, 4, 2008);
      const Fecha g(f - 10);
      chk_eq_fecha(g, 22, 3, 2008);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Suma con asignacion) {
      Fecha f(5, 5, 2005);
      f += 3;
      chk_eq_fecha(f, 8, 5, 2005);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Resta con asignacion) {
      Fecha f(2, 7, 2010);
      f -= 2;
      chk_eq_fecha(f, 30, 6, 2010);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Asignacion entre fechas) {
      Fecha f(1, 1, 2001);
      Fecha g(3, 4, 2005);
      g = f;
      chk_eq_fecha(g, 1, 1, 2001);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Conversion implicita) {
      const Fecha f(2, 4, 2006);
      fct_chk(strstr(f, "domingo") != 0);
      fct_chk(strstr(f, "abril") != 0);
      fct_chk(strstr(f, "2006") != 0);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Comparacion: igualdad) {
      const Fecha f(1, 2, 2000);
      const Fecha g(f);
      const Fecha h(2, 3, 2001);
      fct_chk(f == g);
      fct_chk(!(f == h));
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Comparacion: desigualdad) {
      const Fecha f(1, 2, 2000);
      const Fecha g(f);
      const Fecha h(2, 3, 2001);
      fct_chk(!(f != g));
      fct_chk(f != h);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Comparacion: mayor) {
      const Fecha f(10, 2, 2000);
      const Fecha g(15, 2, 2000);
      const Fecha h(20, 1, 2000);
      const Fecha i(10, 5, 2000);
      const Fecha j(30, 5, 1999);
      const Fecha k(1, 1, 2004);
      fct_chk(!(f > f));
      fct_chk(g > f);
      fct_chk(f > h);
      fct_chk(i > f);
      fct_chk(f > j);
      fct_chk(k > f);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Comparacion: mayor o igual) {
      const Fecha f(10, 2, 2000);
      const Fecha g(15, 2, 2000);
      const Fecha h(20, 1, 2000);
      const Fecha i(10, 5, 2000);
      const Fecha j(30, 5, 1999);
      const Fecha k(1, 1, 2004);
      fct_chk(f >= f);
      fct_chk(g >= f);
      fct_chk(f >= h);
      fct_chk(i >= f);
      fct_chk(f >= j);
      fct_chk(k >= f);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Comparacion: menor) {
      const Fecha f(10, 2, 2000);
      const Fecha g(15, 2, 2000);
      const Fecha h(20, 1, 2000);
      const Fecha i(10, 5, 2000);
      const Fecha j(30, 5, 1999);
      const Fecha k(1, 1, 2004);
      fct_chk(!(f < f));
      fct_chk(f < g);
      fct_chk(h < f);
      fct_chk(f < i);
      fct_chk(j < f);
      fct_chk(f < k);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Comparacion: menor o igual) {
      const Fecha f(10, 2, 2000);
      const Fecha g(15, 2, 2000);
      const Fecha h(20, 1, 2000);
      const Fecha i(10, 5, 2000);
      const Fecha j(30, 5, 1999);
      const Fecha k(1, 1, 2004);
      fct_chk(f <= f);
      fct_chk(f <= g);
      fct_chk(h <= f);
      fct_chk(f <= i);
      fct_chk(j <= f);
      fct_chk(f <= k);
    }
    FCT_TEST_END();
  }
  FCT_FIXTURE_SUITE_END();
}
FCT_END()
