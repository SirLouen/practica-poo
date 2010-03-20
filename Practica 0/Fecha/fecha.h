#ifndef FECHA_H_
#define FECHA_H_


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
			
		
		Fecha(int dia=0, int mes=0, int anno=0) throw (Invalida);
		
		
		
	private:
		int dia_,mes_,anno_;