# Compilador de C++ y opciones de compilacion

CXX = c++
CXXFLAGS = -ansi -Wall -pedantic -O$(OPTIMIZACION)

# Nivel de optimizacion (por omision, no se optimiza).

OPTIMIZACION = 0

# Modulos objeto y ejecutables.

OBJS = prueba-auto.o fecha.o
EXES = prueba-auto
EXES2 = pruebafecha
OBJS2 = pruebafecha.o fecha.o

# Se obtienen los ejecutables directamente

all: $(EXES)

# Obtencion de los ejecutables.

$(EXES): $(OBJS)
	$(CXX) -o $@ $(LDFLAGS) $^
prueba-auto.o: prueba-auto.cpp fecha.h fct.h
	$(CXX) -c $(CXXFLAGS) $<

$(EXES2): $(OBJS2)
	$(CXX) -o $@ $(LDFLAGS) $^
pruebafecha.o: pruebafecha.cpp fecha.h
	$(CXX) -c $(CXXFLAGS) $<

fecha.o: fecha.cpp fecha.h
	$(CXX) -c $(CXXFLAGS) $<

# Limpieza del directorio.

clean:
	$(RM) $(RMFLAGS) $(EXES) $(EXES2) $(OBJS) $(OBJS2) *~

clean-all: clean
	$(RM) $(RMFLAGS) $(TIEMPOS) $(GRAFICAS)