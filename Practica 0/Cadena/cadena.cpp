#include "cadena.h"
#include <iostream>
#include <cstring>

Cadena::Cadena(int tam, char cadena) : tam_(tam)
{
	cadena_ = new char[tam];
	for (int i = 0; i < tam; ++i) 
		cadena_[i] = cadena;
	
	cadena_[tam] = '\0';
}

Cadena::Cadena(const Cadena& otra)
{
	tam_ = otra.tam_;
	cadena_ = new char[tam_];
	strcpy(cadena_, otra.cadena_);
}

Cadena::Cadena (const char *cadena)
{
	tam_ = strlen(cadena);
	cadena_ = new char[tam_];
	strcpy((*this).cadena_, cadena);
	// REDUNDANTE?
	(*this).cadena_[tam_] = '\0';
}

Cadena& Cadena::operator =(const Cadena& otra)
{
	if (cadena_ != otra.cadena_)
	{
		(*this).tam_ = otra.tam_;
		(*this).cadena_ = new char[(*this).tam_];
		strcpy((*this).cadena_,otra.cadena_);
	}
	
	return (*this);
}

Cadena& Cadena::operator =(const char *cadena)
{
	(*this).tam_ = strlen(cadena);
	(*this).cadena_ = new char[(*this).tam_];
	strcpy((*this).cadena_,cadena);
	// REDUNDANTE?
	(*this).cadena_[(*this).tam_] = '\0';
	
	return (*this);
}

Cadena& Cadena::operator +=(const Cadena &otra)
{
	// Creamos valores temporales para la concatenacion
	int tam = (*this).tam_ + otra.tam_ + 1;
	char* cadena = new char[tam];
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
	Cadena cadena(tam);
	
	delete[] cadena.cadena_;
	cadena.cadena_ = new char[tam];
	strcpy(cadena.cadena_, a.cadena_);
	strcat(cadena.cadena_, b.cadena_);
	
	return cadena;
}

bool Cadena::operator >=(const Cadena &otra)
{
	return strcmp((*this).cadena_, otra.cadena_) >= 0;
}

bool Cadena::operator <=(const Cadena &otra)
{
	return strcmp((*this).cadena_, otra.cadena_) <= 0;
}

bool Cadena::operator >(const Cadena &otra)
{
	return strcmp((*this).cadena_, otra.cadena_) > 0;
}

bool Cadena::operator <(const Cadena &otra)
{
	return strcmp((*this).cadena_, otra.cadena_) < 0;
}

bool Cadena::operator ==(const Cadena &otra)
{
	return strcmp((*this).cadena_, otra.cadena_) == 0;
}

bool Cadena::operator !=(const Cadena &otra)
{
	return strcmp((*this).cadena_, otra.cadena_) != 0;
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
	if (i >= (*this).tam_ || i < 0)
		throw std::out_of_range("at(): Fuera de Rango");
	
	return (*this).cadena_[i];
}

char& Cadena::at(unsigned int i) throw(std::out_of_range)
{
	if (i >= (*this).tam_ || i < 0)
		throw std::out_of_range("at(): Fuera de Rango");
	
	return (*this).cadena_[i];
}

const char* Cadena::subcadena(int pos, int tam) throw(std::out_of_range)
{
	if (pos+tam >= (*this).tam_ || pos < 0 || tam < 0)
		throw std::out_of_range("subcadena(): Fuera de Rango");
	
	
	else
	{
		char* cadena;
		cadena = new char[tam];
	
		for (int i = 0; i < tam; i++) 
			cadena[i] = (*this).cadena_[i+pos];
		cadena[tam] = '\0';

		return cadena;
	}
}
