#include <iostream>
#include <fstream>
#include "time.h"
#include "correo.h"
#include <locale.h>
#include <string.h>
#include <cstring>

// system("/usr/bin/clear") limpiar pantalla en linux =>  System("CLS") para windows
// Setlocale(LC_TYPE, idioma) para acentos 
 

/*Estructura de registro de usuarios*/
typedef struct Registro{
	char correo[20];
	char contrasenia[20];
	char nombre[50];
	char fechaCreacion[50];
	Registro *siguiente;
	Registro *anterior;

}Registro;

Registro *nodoRegistro, *cabeza=NULL, *cola=NULL;

/* estructura de mensajes de salida */
typedef struct BandejaSalida{
	char correoEmisor[20];
    char correoReceptor[20];
	char fechaEnvio[50];
	char mensajeEnviado[80];
	BandejaSalida *siguiente;
	BandejaSalida *anterior;	
}BandejaSalida;

BandejaSalida *nodoBandejaSalida, *cabezaSalida=NULL, *colaSalida=NULL;

/* estrutura de mensajes de entrada*/
typedef struct BandejaEntrada{
	char correoReceptor[20];
	char correoEmisor[20];
	char fechaEntrada[50];
	char mensajeEntrada[80];
	BandejaEntrada *siguiente;
	BandejaEntrada *anterior;
}BandejaEntrada;

BandejaEntrada *nodoBandejaEntrada, *cabezaEntrada=NULL, *colaEntrada=NULL;

/*creacion de la lista Registro*/
void creacionRegistro(char corr[20], char con[20], char nom[20], char fec[20]){
	nodoRegistro = (struct Registro*)malloc(sizeof(Registro));
	strcpy(nodoRegistro->correo, corr);
	strcpy(nodoRegistro->contrasenia, con);
	strcpy(nodoRegistro->nombre, nom);
	strcpy(nodoRegistro->fechaCreacion, fec);
	nodoRegistro->siguiente = NULL;
	nodoRegistro->anterior = NULL;

	if(cabeza == NULL){
		cabeza = cola = nodoRegistro;
	}else{
		nodoRegistro->anterior = cola;
		cola->siguiente = nodoRegistro;
		cola = cola->siguiente;	
	}
}

/*creacion de la lista mensajes de salida*/
void creacionBandejaSalida(char corEmi[20], char corRec[20], char fecEnv[40], char menEnvi[80]){
	nodoBandejaSalida = (struct BandejaSalida*)malloc(sizeof(BandejaSalida));
	strcpy(nodoBandejaSalida->correoEmisor, corEmi);
	strcpy(nodoBandejaSalida->correoReceptor, corRec);
	strcpy(nodoBandejaSalida->fechaEnvio, fecEnv);
	strcpy(nodoBandejaSalida->mensajeEnviado, menEnvi);
	nodoBandejaSalida->siguiente = NULL;
	nodoBandejaSalida->anterior = NULL;
	
	if(cabezaSalida == NULL){
		cabezaSalida = colaSalida = nodoBandejaSalida;
	}else{
		nodoBandejaSalida->anterior = colaSalida;
		colaSalida->siguiente = nodoBandejaSalida;
		colaSalida = colaSalida->siguiente;
	}
}

/* creacion de la lista mensaje entrada*/
void creacionBandejaEntrada(char corRec[20], char corEmi[20], char fecEnt[40], char menEnt[80]){
	nodoBandejaEntrada = (struct BandejaEntrada*)malloc(sizeof(BandejaEntrada));
	strcpy(nodoBandejaEntrada->correoReceptor, corRec);
	strcpy(nodoBandejaEntrada->correoEmisor, corEmi);
	strcpy(nodoBandejaEntrada->fechaEntrada, fecEnt);
	strcpy(nodoBandejaEntrada->mensajeEntrada, menEnt);
	nodoBandejaEntrada->siguiente = NULL;
	nodoBandejaEntrada->anterior = NULL;

			
	if(cabezaEntrada == NULL){
		cabezaEntrada = colaEntrada = nodoBandejaEntrada;
	}else{
		nodoBandejaEntrada->anterior = colaEntrada;
		colaEntrada->siguiente = nodoBandejaEntrada;
		colaEntrada = colaEntrada->siguiente;
	}
}

/*saber si el usuario existe*/
bool busquedaRegistro(char correo[20], char contrasenia[20]){
	Registro *r;
	bool existe = false;
	for(r=cabeza; r!=NULL; r=r->siguiente){
		if( (strcmp(r->correo, correo) == 0 ) && (strcmp(r->contrasenia, contrasenia) == 0) ){
			existe = true;
			break;
		}
	}
	return existe;
}

bool busquedaRegistro(char correo[20]){
	Registro *r;
	bool existe = false;
	for(r=cabeza; r!= NULL; r=r->siguiente){
		if(strcmp(r->correo, correo) == 0){
			existe = true;
			break;
		}
	}
	return existe;
}
/*dar de baja a la cuenta*/
void eliminarCuenta(char correo[20]){
	Registro *r, *auxAnt, *auxSig ; bool sw = false;
	while( (r != NULL) && (sw == false)){
		if(strcmp(r->correo, correo) == 0){
			sw = true;
		}
		r = r->siguiente;
	}
	if(sw == true){
		auxAnt = r->anterior;
		auxSig = r->siguiente;
		auxAnt->siguiente = auxSig;
		auxSig->anterior = auxAnt;
		free(r);
	}
}


void llenarRegistro(){
	time_t t, i;
	char *correo, *contrasenia, *nombre, *fechaC;
	string p;
	
	cout<<"Ingrese correo: "; getline(cin, p);
	correo = strdup(p.c_str());
	cout<<"Ingrese contraseña: "; getline(cin, p);
	contrasenia = strdup(p.c_str());
	cout<<"Ingrese nombre: "; getline(cin, p);
	nombre = strdup(p.c_str());
	i = time(&t);
	p = ctime(&i);
	fechaC = strdup(p.c_str());
	if( !busquedaRegistro(correo) ){
		creacionRegistro(correo, contrasenia, nombre, fechaC);
	}else{
		cout<<"No se puede crear cuenta existente ...";	
	}
		
}

/* Bandeja entrada y salida*/

void bandejaEntrada(char correo[20]){
	BandejaEntrada *r;
	for(r=cabezaEntrada; r!=NULL; r=r->siguiente){
		if( strcmp(r->correoReceptor, correo) == 0 ){
			cout<<"Enviado por: "<<r->correoEmisor<<endl;
			cout<<"Asunto:  "<<r->mensajeEntrada<<endl;
			cout<<"Enviado hace: "<<r->fechaEntrada;
		}
	}
}

void bandejaSalida(char correo[20]){
	BandejaSalida *r;
	for(r=cabezaSalida; r!=NULL; r=r->siguiente){
        cout<<"Enviado por: "<<r->correoReceptor <<endl;                                                     
        cout<<"Asunto:  "<<r->mensajeEnviado <<endl;                                                       
		cout<<"Enviado hace: "<<r->fechaEnvio;
	}
}



void sesionIniciada(char correo[20], int opcion){
	system("/usr/bin/clear");
	time_t t, i;
	char *mensaje, *usuario, *fecha;
	cin>> opcion;
	string p;
	 if(opcion == 1){
		system("/usr/bin/clear");
		cout<<"Ingrese correo"<<endl;
		cout<<"Para: "; getline(cin, p);
		usuario = strdup(p.c_str());
		cout<<"Asunto: "; getline(cin, p);
		mensaje = strdup(p.c_str());
		i = time(&t);
		p = ctime(&i);
		fecha = strdup(p.c_str());
		if(busquedaRegistro(usuario)){
			creacionBandejaSalida( correo, usuario, fecha, mensaje);	
		}
	}else if(opcion == 2){
		bandejaEntrada(correo);
	}else if(opcion == 3){
		bandejaSalida(correo);
	}else if(opcion == 4){
		eliminarCuenta(correo);
	}else if(opcion == 5){
		cout<<"sesion finalizada";
	}
}


using namespace std;
int main(){
	
	setlocale(LC_CTYPE, "Spanish"); 
	bool sw = true; int opcion;
	char correo[20], contrasenia[20];

	while(sw){
  		menuPrincipal();
		cin>>opcion;
		if(opcion == 1){
			//Inicio sesion
			system("/usr/bin/clear");
			cout<<"Ingrese correo de usuario: ";
			cin>>correo;
			cout<<"Ingrese contraseña: ";
			cin>>contrasenia;
			if( busquedaRegistro(correo, contrasenia) ){
				while(true){
					menuSesion();
					cin>>opcion;
					sesionIniciada(correo, opcion);
					if(opcion == 5) break;
				}
			}else{
				cout<<"Error usuario y contraseña no coinciden...";	
			}
			
		}else if(opcion == 2){
			//Registro
			menuRegistro();
			llenarRegistro();
		}else if(opcion == 3){
			//salida
			sw = false;
		}else{
			cout<<"Opcion incorrecta";
		}
	}		
}
