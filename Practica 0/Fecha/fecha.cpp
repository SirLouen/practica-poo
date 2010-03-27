#include "fecha.h"
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cstring>

static bool bisiesto(int anno);
static int diasmes(int mes);
static bool fechainvalida(int dia, int mes, int anno);

static int diasmes(int mes)
{
	int numdias[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
	
	return numdias[mes];
}

static bool bisiesto(int anno)
{
	return (anno % 4 == 0 and (anno % 400 == 0 or anno % 100 != 0));
}

static bool fechainvalida(int dia, int mes, int anno)
{
	return ((dia < 1) || ((mes == 2) && (dia > 29) && bisiesto(anno)) || (dia > diasmes(mes)) || ( mes < 1 || mes > 12) || (anno < annomin || anno > annomax));
}
		

Fecha::Fecha (int dia, int mes, int anno) throw (Fecha::Invalida)
{
	int d,m,a;
	time_t tc;
	time(&tc);	
	
	struct tm* td;
	td = localtime(&tc);
	
	(dia == 0)?d = td->tm_mday:d = dia;
	
	(mes == 0)? m = td->tm_mon+1: m = mes;
	
	(anno == 0)? a = td->tm_year+1900: a = anno;
		
	// comprobacion de fecha correcta
	if(fechainvalida(d,m,a))
		throw Invalida("Error Fecha::Fecha");
	else
	{
		dia_ = d;
		mes_ = m;
		anno_ = a;
	}
}

	
Fecha::Fecha (const char *fecha) throw (Invalida)
{
	int d, m, a, res; 
	
	res = sscanf(fecha, "%d/%d/%d", &d, &m, &a);
	
	if (res != 3)
		throw Invalida("Error Formato Cadena Bajo Nivel Fecha::Fecha");
	else
	{
		if(fechainvalida(d,m,a))
			throw Invalida("Error Fecha::Fecha");
		else
		{
			dia_ = d;
			mes_ = m;
			anno_ = a;
		}
	}
}

Fecha operator +(Fecha f, int num)
{
	time_t tc;
	time(&tc);
	struct tm* td = localtime(&tc);
	
	td->tm_mday = f.dia();
	td->tm_mon = f.mes() - 1;
	td->tm_year = f.anno() - 1900;
	
	td->tm_mday = td->tm_mday + num;
	tc = mktime(td);
	td = localtime(&tc);
	
	//Fecha *h=new Fecha;
	
	f.dia() = td->tm_mday;
	f.mes() = td->tm_mon + 1;
	f.anno() = td->tm_year + 1900;
	
	return f;
}

Fecha operator -(Fecha f, int num)
{
	time_t tc;
	time(&tc);
	struct tm* td = localtime(&tc);
	
	td->tm_mday = f.dia();
	td->tm_mon = f.mes() - 1;
	td->tm_year = f.anno() - 1900;
	
	td->tm_mday = td->tm_mday - num;
	tc = mktime(td);
	td = localtime(&tc);
	
	//Fecha *h=new Fecha;
	
	f.dia() = td->tm_mday;
	f.mes() = td->tm_mon + 1;
	f.anno() = td->tm_year + 1900;
	
	return f;
}

Fecha operator +(int num, Fecha f)
{
	f = f + num;
	return f;
}

Fecha operator -(int num, Fecha f)
{
	f = f - num;
	return f;
}
	
Fecha Fecha::operator += (int num)
{
	*this = *this + num;
	return *this;
}

Fecha Fecha::operator -= (int num)
{
	*this = *this - num;
	return *this;
}

//Postincremento
Fecha Fecha::operator ++(int)
{
	Fecha f = *this;
	
	*this = *this + 1;
	return f;
	
}

//Postdecremento
Fecha Fecha::operator --(int)
{
	Fecha f = *this;
		
	*this = *this - 1;	
	return f;
	
}

//Predecremento
Fecha Fecha::operator --()
{
	*this = *this - 1;
	return *this;
}
//Preincremento
Fecha Fecha::operator ++()
{
	*this = *this + 1;
	return *this;
}

Fecha::operator const char* () const
{
	time_t tc;
	time(&tc);
	struct tm* td = localtime(&tc);
	
	char* cadenafecha = new char[50];
	
	const char* meses[13] = {0,"enero","febrero","marzo","abril","mayo","junio","julio","agosto","septiembre","octubre","noviembre","diciembre"};
	
	const char* diasem[7] = {"domingo","lunes","martes", "miercoles", "jueves", "viernes", "sabado"};
	
	Fecha f = *this;
	
	td->tm_mday = f.dia_;
	td->tm_mon = f.dia_;
	td->tm_year = f.dia_;
	
	mktime(td);
	
	int diasemana = td->tm_wday;  
	
	sprintf(cadenafecha,"%s %d de %s de %d",diasem[diasemana],dia_,meses[mes_],anno_);

	return cadenafecha; 
}
	
bool operator ==(const Fecha &f, const Fecha& g) 
{
	return (f.anno() == g.anno()) && (f.mes() == g.mes()) && (f.dia() == g.dia());
}

bool operator !=(const Fecha& f, const Fecha& g)
{
	return (f.anno() != g.anno()) && (f.mes() != g.mes()) && (f.dia() != g.dia());
}

bool operator >=(const Fecha& g, const Fecha& f)
{
	return (g.anno() >= f.anno()) || ((f.anno() == g.anno()) && (g.mes() >= f.mes())) || ((f.anno() == g.anno()) && (f.mes() == g.mes()) && (g.dia() >= f.dia()));
}

bool operator <=(const Fecha& g, const Fecha& f)
{
	return (g.anno()  <= f.anno()) || ((f.anno() == g.anno()) && (g.mes() <= f.mes())) || ((f.anno() == g.anno()) && (f.mes() == g.mes()) && (g.dia() <= f.dia()));
}

bool operator >(const Fecha& g, const Fecha& f)
{
	return (g.anno() > f.anno())  || ((f.anno() == g.anno()) && (g.mes() > f.mes() )) || ((f.anno() == g.anno()) && (f.mes() == g.mes()) && (g.dia() > f.dia()));
}

bool operator <(const Fecha& g, const Fecha& f)
{
	return (g.anno() < f.anno()) || ((f.anno() == g.anno()) && (g.mes() < f.mes())) || ((f.anno() == g.anno()) && (f.mes() == g.mes()) && (g.dia() < f.dia()));
}
