#ifndef _ACCIONES_H
#define _ACCIONES_H

typedef struct dun{
	void (*funcion)();
	int identificador;
	struct dun *next;
}dun;

typedef struct acciones{
	dun *curr;
	dun *head;
	dun *tail;
	int length;
	int posCurr;
}acciones;

void borrarNodo(escenario *esc, casilla *borrar);
void saltar_encima(escenario *esc, int i);
void caminar_en(escenario *esc);
void rushear(escenario *esc);
void taclear_al_frente(escenario *esc);
void ver_plata(escenario *esc);
void choice(int accion, acciones *listaAcc, escenario *esc);
int stop(escenario *esc);

#endif