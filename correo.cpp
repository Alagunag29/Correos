#include <iostream>
#include <fstream>
#include "time.h"
#include "correo.h"
#include <locale.h>
#include <string.h>
#include <cstring>

// system("/usr/bin/clear") limpiar pantalla en linux =>  System("CLS") para windows
// Setlocale(LC_TYPE, idioma) para acentos 
 
void escrituraRegistro(char corr[20], char con[20], char nom[20], char fec[20]);


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
	getline(cin, p); 
	cout<<"Ingrese correo: ";
   	getline(cin, p);
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
		escrituraRegistro(correo, contrasenia, nombre, fechaC);
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
			cout<<"*********************************"<<endl;
		}
	}
	cin.ignore(1024, '\n');
	cin.get(); 
}

void bandejaSalida(char correo[20]){
	BandejaSalida *r;
	for(r=cabezaSalida; r!=NULL; r=r->siguiente){
		if( strcmp(r->correoEmisor, correo) == 0  ){
     		cout<<"Enviado a : "<<r->correoReceptor <<endl;                                                     
        	cout<<"Asunto:  "<<r->mensajeEnviado <<endl;                                                       
			cout<<"Enviado hace: "<<r->fechaEnvio;
			cout<<"******************************"<<endl;
		}
	}
	cin.ignore(1024, '\n');
	cin.get(); 
}
void escrituraSalida(char correo[20], char usuario[20], char fecha[40], char mensaje[80]){
	ofstream entrada;
	entrada.open("salida.txt", ios::out|ios::app);
	if(entrada.fail()){
		cout<<"Error al abrir el archivo..."<<endl;
		exit(1);
	}
	entrada<<correo<<endl;
	entrada<<usuario<<endl;
	entrada<<fecha<<endl;
	entrada<<mensaje<<endl;
	entrada.close();
}

void escrituraEntrada(char usuario[20], char correo[20], char fecha[40], char mensaje[80]){
	ofstream entrada;
	entrada.open("entrada.txt", ios::out|ios::app);
	if(entrada.fail()){
		cout<<"Error al abrir el archivo..."<<endl;
		exit(1);
	}
	entrada<<usuario<<endl;
	entrada<<correo<<endl;
	entrada<<fecha<<endl;
	entrada<<mensaje<<endl;
	entrada.close();
}

void escrituraRegistro(char corr[20], char con[20], char nom[20], char fec[20]){
	ofstream entrada;
	entrada.open("registro.txt", ios::out|ios::app);
	if(entrada.fail()){
		cout<<"Error al abrir el archivo..."<<endl;
		exit(1);	
	}
	entrada<<corr<<endl;
	entrada<<con<<endl;
	entrada<<nom<<endl;
	entrada<<fec<<endl;

	entrada.close();
}

void lecturaEntrada(){
	char usuario[20], correo[20], fecha[40], mensaje[80];
	ifstream salida;
	salida.open("entrada.txt", ios::in);
	if( salida.fail() ){
		cout<<"Error al abrir el archivo"<<endl;
		exit(1);
	}

	while( !salida.eof() ){
		salida.getline(usuario, 20);
		salida.getline(correo, 20);
		salida.getline(fecha, 40);
		salida.getline(mensaje, 80);
		creacionBandejaEntrada(usuario, correo, fecha, mensaje);
	}
	salida.close();
}

void lecturaSalida(){
	char correo[20], usuario[20], fecha[40], mensaje[80];
	ifstream salida;
	salida.open("salida.txt", ios::in);
	if(salida.fail()){
		cout<<"Error al abrir el archivo"<<endl;
		exit(1);
	}

	while( !salida.eof() ){
		salida.getline(correo, 20);
		salida.getline(usuario, 20);
		salida.getline(fecha, 40);
		salida.getline(mensaje, 80);
		creacionBandejaSalida(correo, usuario, fecha, mensaje);
	}
	salida.close();
}

void lecturaRegistro(){
	char correo[20], contrasenia[20], nombre[40], fechaC[80];
	ifstream salida;
	salida.open("registro.txt", ios::in);
	if(salida.fail()){
		cout<<"Error al abrir el archivo"<<endl;
		exit(1);
	}	
	while(!salida.eof()){
		salida.getline(correo, 20);
		salida.getline(contrasenia, 20);
		salida.getline(nombre, 40);
		salida.getline(fechaC, 80);
		creacionRegistro(correo, contrasenia, nombre, fechaC);
	}
}

void sesionIniciada(char correo[20], int opcion){
	system("/usr/bin/clear");
	time_t t, i;
	char *mensaje, *usuario, *fecha;
	string p;
	if(opcion == 1){
		getline(cin, p);
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
			escrituraSalida(correo, usuario, fecha, mensaje);
			creacionBandejaEntrada(usuario, correo, fecha, mensaje);
			escrituraEntrada(usuario, correo, fecha, mensaje);
			cout<<"Enviando ...";
			cin.ignore(1024, '\n');
		}else{
			cout<<"Correo no existente...";
			cin.ignore(1024, '\n');
		}
	}else if(opcion == 2){
		bandejaEntrada(correo);
	}else if(opcion == 3){
		bandejaSalida(correo);
	}else if(opcion == 4){
		eliminarCuenta(correo);
		cout<<"Cuenta eliminada...";
		cin.ignore(1024, '\n');
	}
}

using namespace std;
int main(){
	
	setlocale(LC_CTYPE, "Spanish"); 
	bool sw = true; int opcion;
	char correo[20], contrasenia[20];
	lecturaRegistro();
	lecturaSalida();
	lecturaEntrada();
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
				int opcion1;
				while(true){
					menuSesion();
					cin>>opcion1;
					sesionIniciada(correo, opcion1);
					if(opcion1 == 5){
						cout<<"Sesion finalizada...";
						break;	
					}
				}
				cin.ignore(1024, '\n');
			}else{
				cout<<"Error usuario y contraseña no coinciden..."<<endl;
				cin.ignore(1024, '\n');
				cin.get();	
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
