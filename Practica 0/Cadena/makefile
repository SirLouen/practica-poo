# Compilador de C++ y opciones de compilacion

CXX = c++
CXXFLAGS = -ansi -Wall -pedantic -O$(OPTIMIZACION)

# Nivel de optimizacion (por omision, no se optimiza).

OPTIMIZACION = 0

# Modulos objeto y ejecutables.

OBJS = prueba-auto.o cadena.o
EXES = prueba-auto
EXES2 = pruebacadena
OBJS2 = pruebacadena.o cadena.o

# Se obtienen los ejecutables directamente

all: $(EXES)

# Obtencion de los ejecutables.

$(EXES): $(OBJS)
	$(CXX) -o $@ $(LDFLAGS) $^
prueba-auto.o: prueba-auto.cpp cadena.h fct.h
	$(CXX) -c $(CXXFLAGS) $<

$(EXES2): $(OBJS2)
	$(CXX) -o $@ $(LDFLAGS) $^
pruebacadena.o: pruebacadena.cpp cadena.h
	$(CXX) -c $(CXXFLAGS) $<

cadena.o: cadena.cpp cadena.h
	$(CXX) -c $(CXXFLAGS) $<

# Limpieza del directorio.

clean:
	$(RM) $(RMFLAGS) $(EXES) $(EXES2) $(OBJS) $(OBJS2) *~

clean-all: clean
	$(RM) $(RMFLAGS) $(TIEMPOS) $(GRAFICAS)