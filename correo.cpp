#include <iostream>
#include <fstream>
#include "time.h"
#include "correo.h"
#include <locale.h>

// system("/usr/bin/clear") limpiar pantalla en linux =>  System("CLS") para windows
// Setlocale(LC_TYPE, idioma) para acentos 
 
using namespace std;
int main(){
	
	setlocale(LC_CTYPE, "Spanish"); 
	bool sw = true; int opcion;
	while(sw){
  		menuPrincipal();
		cin>>opcion;
		if(opcion == 1){
			//Inicio sesion
			system("/usr/bin/clear");

			menuSesion();
		}else if(opcion == 2){
			//Registro
			menuRegistro();
		}else if(opcion == 3){
			//salida
			sw = false;
		}else{
			cout<<"Opcion incorrecta";
		}
	}		
}

