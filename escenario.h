#ifndef _ESCENARIO_H
#define _ESCENARIO_H

typedef struct Personaje{
	char nombre[100];
	int estado; //1 normal 2 brillante 3 mareado 4 wario
	int monedas;
}Personaje;

typedef struct Objeto{
	char nombre[100];
	int estado; //1 health 2 mareado 3 wario 4 brillante
}Objeto;

typedef struct Enemigo{
	char nombre[100];
}Enemigo;

typedef struct Bloque{ //Revisar el void *****
	void *contenido;
	int tipo; //0 monedas 1 Objeto
}Bloque;

typedef struct Suelo{
	int tipo; //0 piso firme 1 agujero 
}Suelo;

//#########################################################
// lista enlazada

typedef struct elemento{
	void *caracteristica1;
	void *caracteristica2;
	void *caracteristica3;
	void *caracteristica4;
}elemento;

typedef struct casilla{ //nodo
	elemento cosa;
	int tipo;
	void *puntero;//puntero para guardar la direccion de memoria de la estructura a liberar
	struct casilla *next;
}casilla;

typedef struct escenario{ //lista
	casilla *curr;
	casilla *head;
	casilla *tail;
	int length;
	int posCurr;
}escenario;

Personaje *crearPersonaje();
Objeto *crearObjeto();
Enemigo *crearEnemigo();
Bloque *crearBloque();
Suelo *crearSuelo();
escenario *crearEscenario();
casilla *crearCasilla();
void crearMundo(escenario *esc,int cant);
void printear(escenario *esc, int tipo);
void mostrar(escenario *esc, int i);
void mostrar_todo(escenario *esc);
void anadir_elemento(escenario *esc, elemento *ele, void *memEle, int tipoEle, int i);
void borrar_elemento(escenario *esc, int i);
void borrar_todo(escenario *esc);
void anadirPersonaje(escenario *esc);
void anadirObjeto(escenario *esc, int i);
void anadirEnemigo(escenario *esc, int i);
void anadirBloque(escenario *esc, int i);
void anadirSuelo(escenario *esc, int i);
void anadirSueloPlano(escenario *esc, int i);
int sacarLargo(escenario *esc);

#endif