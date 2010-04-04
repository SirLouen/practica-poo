#ifndef CADENA_H_
#define CADENA_H_

#include <stdexcept>

class Cadena
{
	public:
		// Aqui tenemos constructor predeterminado, y luego dos constructores de conversion desde un entero pero explicitamente y desde un entero y caracter.
		explicit Cadena(int tam = 0, char caracter = ' ');
		
		// Constructor de Copia
		Cadena (const Cadena& otra);
		// Constructor de Conversion de cadena de caracteres de bajo nivel a Cadena.
		Cadena (const char *cadena);
		// Conversion de Cadena a cadena de caracteres de bajo nivel, y Metodo observador del atributo cadena_
		operator const char* () const { return cadena_; }
		
		// Sobrecarga del operador de asignacion para Cadena y para cadenas de caracteres de bajo nivel
		Cadena& operator =(const Cadena& otra);
		Cadena& operator =(const char *cadena);
		// Metodo observador del atributo tamaño
		unsigned int longitud() const { return tam_; }
		// Sobrecarga del operador de suma con asignacion para la concatenacion
		Cadena& operator += (const Cadena &otra);
		
		// Sobrecarga del operador de suma para la concatenacion
		friend Cadena operator +(const Cadena& a, const Cadena& b);
		
		
		// Sobrecarga del operador de indice, observador y modificador
		char operator[](int i) const;
		char& operator[](int i);
		
		// Metodo equivalente a operador indice pero con control de excepciones, como observador y modificador
		char at(unsigned int i) const throw(std::out_of_range);
		char& at(unsigned int i) throw(std::out_of_range);
		
		const char* subcadena(unsigned int pos, unsigned int tam) throw(std::out_of_range);
		
		~Cadena(){ delete[] cadena_; }


	private:
		char *cadena_;
		unsigned int tam_;
};

		// Sobrecarga de los operadores de comparacion
		
		bool operator >=(const Cadena &una, const Cadena &otra);
		bool operator <=(const Cadena &una, const Cadena &otra);
		bool operator >(const Cadena &una, const Cadena &otra);
		bool operator <(const Cadena &una, const Cadena &otra);
		bool operator ==(const Cadena &una, const Cadena &otra);
		bool operator !=(const Cadena &una, const Cadena &otra);

#endif
