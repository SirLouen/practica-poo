#include "cadena.h"
#include <iostream>
#include <cstring>

Cadena::Cadena(int tam, char cadena) : tam_(tam)
{
	cadena_ = new char[tam+1];
	for (int i = 0; i < tam; ++i) 
		cadena_[i] = cadena;
	
	cadena_[tam] = '\0';
}

Cadena::Cadena(const Cadena& otra)
{
	tam_ = otra.tam_;
	cadena_ = new char[tam_+1];
	strcpy(cadena_, otra.cadena_);
}

Cadena::Cadena (const char *cadena)
{
	tam_ = strlen(cadena);
	cadena_ = new char[tam_+1];
	strcpy((*this).cadena_, cadena);
}

Cadena& Cadena::operator =(const Cadena& otra)
{
	if (cadena_ != otra.cadena_)
	{
		(*this).tam_ = otra.tam_;
		(*this).cadena_ = new char[(*this).tam_+1];
		strcpy((*this).cadena_,otra.cadena_);
	}
	
	return (*this);
}

Cadena& Cadena::operator =(const char *cadena)
{
	(*this).tam_ = strlen(cadena);
	(*this).cadena_ = new char[(*this).tam_+1];
	strcpy((*this).cadena_,cadena);
	
	return (*this);
}

Cadena& Cadena::operator +=(const Cadena &otra)
{
	// Creamos valores temporales para la concatenacion
	int tam = (*this).tam_ + otra.tam_ + 1;
	char* cadena = new char[tam];
	
	// Creamos una cadena temporal
	strcpy(cadena,(*this).cadena_);
	
	// Traspasamos los nuevos valores temporales al objeto final
	delete[] (*this).cadena_;	
	(*this).tam_ = tam;
	(*this).cadena_ = new char[tam];
	strcpy((*this).cadena_, cadena);
	strcat((*this).cadena_, otra.cadena_);
	
	return *this;
}

Cadena operator +(const Cadena& a, const Cadena& b)
{	
	int tam = a.tam_ + b.tam_ + 1;
	Cadena cadena;
	
	cadena.cadena_ = new char[tam];
	strcpy(cadena.cadena_, a.cadena_);
	strcat(cadena.cadena_, b.cadena_);
	
	return cadena;
}

bool operator >=(const Cadena &una, const Cadena &otra)
{
	return strcmp(una, otra) >= 0;
}

bool operator <=(const Cadena &una, const Cadena &otra)
{
	return strcmp(una, otra) <= 0;
}

bool operator >(const Cadena &una, const Cadena &otra)
{
	return strcmp(una, otra) > 0;
}

bool operator <(const Cadena &una, const Cadena &otra)
{
	return strcmp(una, otra) < 0;
}

bool operator ==(const Cadena &una, const Cadena &otra)
{
	return strcmp(una, otra) == 0;
}

bool operator !=(const Cadena &una, const Cadena &otra)
{
	return strcmp(una, otra) != 0;
}

char Cadena::operator[](int i) const
{
	return (*this).cadena_[i];
}

char& Cadena::operator[](int i)
{
	return (*this).cadena_[i];
}

char Cadena::at(unsigned int i) const throw(std::out_of_range)
{
	if (i < 0 || i >= (*this).tam_)
		throw std::out_of_range("at(): Fuera de Rango");
	
	return (*this).cadena_[i];
}

char& Cadena::at(unsigned int i) throw(std::out_of_range)
{
	if (i < 0 || i >= (*this).tam_)
		throw std::out_of_range("at(): Fuera de Rango");
	
	return (*this).cadena_[i];
}

const char* Cadena::subcadena(unsigned int pos, unsigned int tam) throw(std::out_of_range)
{
	if ( tam < 0 || pos < 0 || pos > (*this).tam_ || tam > (*this).tam_ || pos+tam >= (*this).tam_)
		throw std::out_of_range("subcadena(): Fuera de Rango");
		
	else
	{
		char* cadena;
		cadena = new char[tam+1];
	
		for (unsigned int i = 0; i < tam; i++) 
			cadena[i] = (*this).cadena_[i+pos];
		cadena[tam] = '\0';

		return cadena;
	}
}
