#ifndef FECHA_H_
#define FECHA_H_

#define annomin 1600
#define annomax 2200

class Fecha
{
	public:
		
		class Invalida
		{
			public:
				Invalida(const char *porque): porque_(porque) {};
				const char* por_que() { return porque_; }
			private:
				const char *porque_;
		};
			
		// Contructor Predeterminado y Constructores de Conversion de 1, 2 y 3 enteros
		explicit Fecha(int dia=0, int mes=0, int anno=0) throw (Invalida);
		// Constructor de Conversion de Cadena de Bajo nivel
		Fecha (const char *fecha) throw (Invalida);
		// Operador de asignacion y constructor de copia por defecto validos
		
		// Metodos observadores de dia, mes y año
		int dia() const { return dia_; }
		int mes() const { return mes_; }
		int anno() const { return anno_; }
		
		// Metodos modificadores de dia, mes y año
		int& dia() { return dia_; }
		int& mes() { return mes_; }
		int& anno() { return anno_; }
		
		// Metodos de incremento/decremento con asignacion de dias
		Fecha& operator +=(int num);
		Fecha& operator -=(int num);
		
		// Metodos de incremento/decremento unario sufijo
		Fecha operator ++ (int);
		Fecha operator -- (int);
		
		// Metodos de incremento/decremento unario perfijo
		Fecha& operator ++ ();
		Fecha& operator -- ();
		
		// Conversion de Fecha a cadena de bajo nivel
		operator const char* () const;
		
		// Metodos de incremento/decremento de dias
		Fecha operator +(int num) const;
		Fecha operator -(int num) const;
	
		
	private:
		int dia_,mes_,anno_;
};

		// Metodos de incremento/decremento de dias
		Fecha operator +(int num, const Fecha& f);
		Fecha operator -(int num, const Fecha& f);

		// Metodos de comparacion
		bool operator ==(const Fecha& f, const Fecha& g);
		bool operator !=(const Fecha& f, const Fecha& g);
		bool operator >=(const Fecha& f, const Fecha& g);
		bool operator <=(const Fecha& f, const Fecha& g);
		bool operator >(const Fecha& f, const Fecha& g);
		bool operator <(const Fecha& f, const Fecha& g);

	
#endif
