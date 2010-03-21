#include "fecha.h"
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <iostream>

static bool bisiesto(int anno);
static int diasmes(int mes);
static bool fechainvalida(int dia, int mes, int anno);
static bool esnumero(char a);

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

static bool esnumero(char a)
{
	return ((a - '0') >= 0 && (a - '0') <= 9);
}
		

Fecha::Fecha (int dia, int mes, int anno) throw (Fecha::Invalida)
{
	int d,m,a;
	time_t tc;
	time(&tc);	
	
	struct tm* td;
	td = localtime(&tc);
	
	if (dia == 0)
		d = td->tm_mday;
	else
		d = dia;
	
	if (mes == 0)
		m = td->tm_mon+1;
	else
		m = mes;
	
	if (anno == 0)
		a = td->tm_year+1900;
	else
		a = anno;
		
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
	int d, m, a;
	
	// TIPO DD/MM/AAAA
	if (esnumero(fecha[0]) && esnumero(fecha[1]) && fecha[2] == '/' && esnumero(fecha[3]) && esnumero(fecha[4]) && fecha[5] == '/' && esnumero(fecha[6]) && esnumero(fecha[7]) && esnumero(fecha[8]) && esnumero(fecha[9]))
	{
		d = (fecha[0] - '0')*10 + (fecha[1] - '0');
		m = (fecha[3] - '0')*10 + (fecha[4] - '0');
		a = (fecha[6] - '0')*1000 + (fecha[7] - '0')*100 + (fecha[8] - '0')*10 + (fecha[9] - '0');
	}
	// TIPO D/MM/AAAA
	else if (esnumero(fecha[0]) && fecha[1] == '/' && esnumero(fecha[2]) && esnumero(fecha[3]) && fecha[4] == '/' && esnumero(fecha[5]) && esnumero(fecha[6]) && esnumero(fecha[7]) && esnumero(fecha[8]))
	{
		d = (fecha[0] - '0');
		m = (fecha[2] - '0')*10 + (fecha[3] - '0');
		a = (fecha[5] - '0')*1000 + (fecha[6] - '0')*100 + (fecha[7] - '0')*10 + (fecha[8] - '0');
	}
	// TIPO DD/M/AAAA
	else if (esnumero(fecha[0]) && esnumero(fecha[1]) && fecha[2] == '/' && esnumero(fecha[3]) && fecha[4] == '/' && esnumero(fecha[5]) && esnumero(fecha[6]) && esnumero(fecha[7]) && esnumero(fecha[8]))
	{
		d = (fecha[0] - '0')*10 + (fecha[1] - '0');
		m = (fecha[3] - '0');
		a = (fecha[5] - '0')*1000 + (fecha[6] - '0')*100 + (fecha[7] - '0')*10 + (fecha[8] - '0');
	}
	// TIPO D/M/AAAA
	else if (esnumero(fecha[0]) && fecha[1] == '/' && esnumero(fecha[2]) && fecha[3] == '/' && esnumero(fecha[4]) && esnumero(fecha[5]) && esnumero(fecha[6]) && esnumero(fecha[7]))
	{
		d = (fecha[0] - '0');
		m = (fecha[2] - '0');
		a = (fecha[4] - '0')*1000 + (fecha[5] - '0')*100 + (fecha[6] - '0')*10 + (fecha[7] - '0');
	}		
	else
		throw Invalida("Error Formato Cadena Bajo Nivel Fecha::Fecha");
	
	if(fechainvalida(d,m,a))
		throw Invalida("Error Fecha::Fecha");
	else
	{
		dia_ = d;
		mes_ = m;
		anno_ = a;
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
	
	td->tm_mday = td->tm_mday  + num;
	tc = mktime(td);
	td = localtime(&tc);
	
	
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
	
	td->tm_mday = td->tm_mday  - num;
	tc = mktime(td);
	td = localtime(&tc);
	
	
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

Fecha Fecha::operator ++(int)
{
	Fecha f(*this);
	
	*this = *this + 1;
	return f;
	
}

Fecha Fecha::operator --(int)
{
	Fecha f(*this);
	
	*this = *this - 1;	
	return f;
	
}

Fecha Fecha::operator --()
{
	*this = *this - 1;
	return *this;
}

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
	int diasemana;
	char* cadenafecha;
	cadenafecha = (char*)malloc(sizeof(char)*50);
	char diasem[15], mescadena[15];
	
	Fecha f = *this;
	
	td->tm_mday = f.dia_;
	td->tm_mon = f.dia_;
	td->tm_year = f.dia_;
	
	mktime(td);
	
	diasemana = td->tm_wday;
	
	switch (diasemana)
	{
		case 1:
		{sprintf(diasem, "lunes");}
		break;
		case 2:
		{sprintf(diasem, "martes");}
		break;
		case 3:
		{sprintf(diasem, "miercoles");}
		break;
		case 4:
		{sprintf(diasem, "jueves");}
		break;
		case 5:
		{sprintf(diasem, "viernes");}
		break;
		case 6:
		{sprintf(diasem, "sabado");}
		break;
		case 0:
		{sprintf(diasem, "domingo");}       
    }
	
	switch (mes_)
	{
		case 1:
		{sprintf(mescadena, "enero");}
		break;
		case 2:
		{sprintf(mescadena, "febrero");}
		break;
		case 3:
		{sprintf(mescadena, "marzo");}
		break;
		case 4:
		{sprintf(mescadena, "abril");}
		break;
		case 5:
		{sprintf(mescadena, "mayo");}
		break;
		case 6:
		{sprintf(mescadena, "junio");}
		break;
		case 7:
		{sprintf(mescadena, "julio");} 
		break;
		case 8:
		{sprintf(mescadena, "agosto");}
		break;
		case 9:
		{sprintf(mescadena, "septiembre");}
		break;
		case 10:
		{sprintf(mescadena, "octubre");}
		break;
		case 11:
		{sprintf(mescadena, "noviembre");}
		break;
		case 12:
		{sprintf(mescadena, "diciembre");}
		break; 
	}
		   
	
	sprintf(cadenafecha,"%s %d de %s de %d",diasem,dia_,mescadena,anno_);

	return cadenafecha; 
}
	
bool Fecha::operator ==(const Fecha& f) const
{
	return (f.anno_ == (*this).anno_) && (f.mes_ == (*this).mes_) && (f.dia_ == (*this).dia_);
}

bool Fecha::operator !=(const Fecha& f) const
{
	return (f.anno_ != (*this).anno_) && (f.mes_ != (*this).mes_) && (f.dia_ != (*this).dia_);
}

bool Fecha::operator >=(const Fecha& f) const
{
	return ((*this).anno_ >= f.anno_) || ((f.anno_ == (*this).anno_) && ((*this).mes_ >= f.mes_)) || ((f.anno_ == (*this).anno_) && (f.mes_ == (*this).mes_) && ((*this).dia_ >= f.dia_));
}

bool Fecha::operator <=(const Fecha& f) const
{
	return ((*this).anno_  <= f.anno_) || ((f.anno_ == (*this).anno_) && ((*this).mes_ <= f.mes_)) || ((f.anno_ == (*this).anno_) && (f.mes_ == (*this).mes_) && ((*this).dia_ <= f.dia_));
}

bool Fecha::operator >(const Fecha& f) const
{
	return ((*this).anno_ > f.anno_)  || ((f.anno_ == (*this).anno_) && ((*this).mes_ > f.mes_ )) || ((f.anno_ == (*this).anno_) && (f.mes_ == (*this).mes_) && ((*this).dia_ > f.dia_));
}

bool Fecha::operator <(const Fecha& f) const
{
	return ((*this).anno_ < f.anno_) || ((f.anno_ == (*this).anno_) && ((*this).mes_ < f.mes_)) || ((f.anno_ == (*this).anno_) && (f.mes_ == (*this).mes_) && ((*this).dia_ < f.dia_));
}
