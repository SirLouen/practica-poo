#include "cadena.h"
#include "fct.h"
#include <cstdlib>
using namespace std;

FCT_BGN() {
  FCT_SUITE_BGN(Cadena) {
    FCT_TEST_BGN(Ctor: repetir caracter ciertas veces) {
      Cadena a(5, '*');
      fct_chk(strcmp(a, "*****") == 0);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Ctor: entero - repite espacios) {
      Cadena a(10);
      fct_chk(strcmp(a, "          ") == 0);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Ctor: sin parametros - vacia) {
      Cadena a;
      fct_chk(strcmp(a, "") == 0);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Ctor: por copia de otra cadena) {
      Cadena a(3);
      Cadena b(a);
      fct_chk(strcmp(b, "   ") == 0);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Ctor: desde cadena de bajo nivel) {
      Cadena a("hola");
      fct_chk(strcmp(a, "hola") == 0);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Asignar una cadena a otra) {
      Cadena a("adios");
      Cadena b;
      a = b;
      fct_chk(strcmp(a, b) == 0);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Asignar una cadena de bajo nivel) {
      Cadena a;
      a = "lembas";
      fct_chk(strcmp(a, "lembas") == 0);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Observadora de longitud: cadena vacia) {
      const Cadena a;
      fct_chk(a.longitud() == 0);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Observadora de longitud: cadena no vacia) {
      const char *s = "saludos cordiales";
      const Cadena a(s);
      fct_chk(a.longitud() == strlen(s));
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Concatenacion: con +=) {
      Cadena a("cram");
      a += Cadena(" y lembas");
      fct_chk(strcmp(a, "cram y lembas") == 0);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Concatenacion: con +) {
      Cadena a("hola"), b("adios");
      Cadena c = a + b;
      fct_chk(strcmp(a + b, "holaadios") == 0);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Comparacion: igualdad) {
      fct_chk(Cadena("hola") == Cadena("hola"));
      fct_chk(!(Cadena("hola") == Cadena("adios")));
      fct_chk(!(Cadena("hola") == Cadena("holas")));
      fct_chk(!(Cadena("holas") == Cadena("hola")));
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Comparacion: desigualdad) {
      fct_chk(!(Cadena("hola") != Cadena("hola")));
      fct_chk(Cadena("hola")  != Cadena("adios"));
      fct_chk(Cadena("hola")  != Cadena("holas"));
      fct_chk(Cadena("holas") != Cadena("hola"));
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Comparacion: menor que) {
      fct_chk(Cadena("") < Cadena("x"));
      fct_chk(Cadena("a") < Cadena("b"));
      fct_chk(!(Cadena("ab") < Cadena("ab")));
      fct_chk(!(Cadena("ca") < Cadena("aa")));
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Comparacion: menor o igual que) {
      fct_chk(Cadena("") <= Cadena("x"));
      fct_chk(Cadena("a") <= Cadena("b"));
      fct_chk(Cadena("ab") <= Cadena("ab"));
      fct_chk(!(Cadena("ca") <= Cadena("aa")));
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Comparacion: mayor que) {
      fct_chk(!(Cadena("") > Cadena("x")));
      fct_chk(!(Cadena("a") > Cadena("b")));
      fct_chk(!(Cadena("ab") > Cadena("ab")));
      fct_chk(Cadena("ca") > Cadena("aa"));
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Comparacion: mayor o igual que) {
      fct_chk(!(Cadena("") >= Cadena("x")));
      fct_chk(!(Cadena("a") >= Cadena("b")));
      fct_chk(Cadena("ab") >= Cadena("ab"));
      fct_chk(Cadena("ca") >= Cadena("aa"));
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Leer caracter: [] y posicion valida) {
      const Cadena a("abcd");
      fct_chk(a.operator[](0) == 'a');
      fct_chk(a.operator[](3) == 'd');
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Leer caracter: [] y posicion no valida) {
      const Cadena a;
      a.operator[](0);
      fct_chk(true);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Leer caracter: at y posicion valida) {
      const Cadena a("abcd");
      fct_chk(a.at(0) == 'a');
      fct_chk(a.at(3) == 'd');
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Leer caracter: at y posicion no valida) {
      const Cadena a;
      try {
        a.at(0);
        fct_chk(!"Se esperaba excepción");
      } catch (out_of_range) {
        fct_chk(true);
      }
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Escribir caracter: []) {
      Cadena a("abcd");
      a.operator[](2) = 'x';
      fct_chk(strcmp(a, "abxd") == 0);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Escribir caracter: at()) {
      Cadena a("abcd");
      a.at(2) = 'x';
      fct_chk(strcmp(a, "abxd") == 0);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Subcadena: caso normal) {
      Cadena a("eenie meenie moe");
      fct_chk(strcmp(a.subcadena(6,6), "meenie") == 0);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Subcadena: posicion inicial mayor que longitud) {
      Cadena a("0123456789");
      try {
        a.subcadena(10, 10);
        fct_chk(!"Se esperaba excepción");
      } catch (out_of_range) {
        fct_chk(true);
      }
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Subcadena: posicion inicial negativa) {
      Cadena a("0123456789");
      try {
        a.subcadena(-1, 10);
        fct_chk(!"Se esperaba excepción");
      } catch (out_of_range) {
        fct_chk(true);
      }
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Subcadena: tamanyo mayor que longitud restante) {
      Cadena a("0123456789");
      try {
        a.subcadena(9,2);
        fct_chk(!"Se esperaba excepción");
      } catch (out_of_range) {
        fct_chk(true);
      }
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Subcadena: tamanyo negativo) {
      Cadena a("0123456789");
      try {
        a.subcadena(9,-1);
        fct_chk(!"Se esperaba excepción");
      } catch (out_of_range) {
        fct_chk(true);
      }
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Subcadena: tamanyo excesivo) {
      Cadena a("0123456789");
      try {
        a.subcadena(9,1000);
        fct_chk(!"Se esperaba excepción");
      } catch (out_of_range) {
        fct_chk(true);
      }
    }
    FCT_TEST_END();
  };
  FCT_SUITE_END();
}
FCT_END()
