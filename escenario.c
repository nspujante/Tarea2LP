#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "escenario.h"

/*
crearPersonaje
----------------
sin parametros
----------------
Crea un struct de tipo Personaje, pide memoria para este y retorna un puntero a esa memoria
*/
Personaje *crearPersonaje(){
	Personaje newPersonaje, *pNewPersonaje;
	printf("Ingrese el nombre del personaje: ");
	scanf("%s",newPersonaje.nombre);
	newPersonaje.estado=1;
	newPersonaje.monedas=0;
	pNewPersonaje=(Personaje *)malloc(sizeof(Personaje));
	*pNewPersonaje=newPersonaje;
	return pNewPersonaje;
}
/*
crearObjeto
----------------
sin parametros
----------------
Crea un struct de tipo Objeto, pide memoria para este y retorna un puntero a esa memoria
*/
Objeto *crearObjeto(){
	Objeto newObjeto, *pNewObjeto;
	printf("Ingrese el nombre del objeto: ");
	scanf("%s",newObjeto.nombre);
	printf("Ingrese el estado que otorga el objeto\n");
	printf("1: health, 2: brillante, 3: mareado, 4: wario: ");
	scanf("%i",&newObjeto.estado);
	pNewObjeto=(Objeto *)malloc(sizeof(Objeto));
	*pNewObjeto=newObjeto;
	return pNewObjeto;
}
/*
crearEnemigo
----------------
sin parametros
----------------
Crea un struct de tipo Enemigo, pide memoria para este y retorna un puntero a esa memoria
*/
Enemigo *crearEnemigo(){
	Enemigo newEnemigo, *pNewEnemigo;
	printf("Ingrese el nombre del enemigo: ");
	scanf("%s",newEnemigo.nombre);
	pNewEnemigo=(Enemigo *)malloc(sizeof(Enemigo));
	*pNewEnemigo=newEnemigo;
	return pNewEnemigo;
}
/*
crearBloque
----------------
sin parametros
----------------
Crea un struct de tipo Personaje, pide memoria para este y retorna un puntero a esa memoria
*/
Bloque *crearBloque(){
	Bloque newBloque, *pNewBloque;
	printf("Ingrese el tipo de contenido del bloque\n");
	printf("0: monedas, 1: Objeto: ");
	scanf("%i",&newBloque.tipo);
	if(newBloque.tipo==1){
		newBloque.contenido=crearObjeto();
	}
	else{
		printf("Ingrese la cantidad de monedas a colocar: ");
		int *cant;
		cant=(int *)malloc(sizeof(int));
		scanf("%i",cant);
		newBloque.contenido=cant;
	}
	pNewBloque=(Bloque *)malloc(sizeof(Bloque));
	*pNewBloque=newBloque;
	return pNewBloque;
}
/*
crearSuelo
----------------
sin parametros
----------------
Crea un struct de tipo Suelo, pide memoria para este y retorna un puntero a esa memoria
*/
Suelo *crearSuelo(){
	Suelo newSuelo, *pNewSuelo;
	printf("Ingrese el tipo de suelo\n");
	printf("0: piso firme, 1: agujero finito: ");
	scanf("%i",&newSuelo.tipo);
	pNewSuelo=(Suelo *)malloc(sizeof(Suelo));
	*pNewSuelo=newSuelo;
	return pNewSuelo;
}
/*
crearEscenario
----------------
sin parametros
----------------
setea un nuevo escenario, pide memoria para este y retorna un puntero a esa memoria
*/
escenario *crearEscenario(){
	escenario *newEscenario=(escenario *)malloc(sizeof(escenario));
	newEscenario->head=NULL;
	newEscenario->curr=NULL;
	newEscenario->tail=NULL;
	newEscenario->length=0;
	newEscenario->posCurr=0;
	return newEscenario;
}
/*
crearCasilla
----------------
sin parametros
----------------
setea una nueva casilla, pide memoria para esta y retorna un puntero a esa memoria
*/
casilla *crearCasilla(){
	casilla *newCasilla=(casilla *)malloc(sizeof(casilla));
	newCasilla->puntero=NULL;
	newCasilla->cosa.caracteristica1=NULL;//ver el buen uso de void pointer #######
	newCasilla->cosa.caracteristica2=NULL;
	newCasilla->cosa.caracteristica3=NULL;
	newCasilla->cosa.caracteristica4=NULL;
	newCasilla->next=NULL;
	return newCasilla;
}
/*
crearMundo
----------------
*esc: puntero a tipo escenario
cant: entero
----------------
rellena el escenario con casillas de suelo plano
*/
void crearMundo(escenario *esc,int cant){
		casilla *newCasilla=crearCasilla();
		newCasilla->tipo=5;
		Suelo *suel=(Suelo *)malloc(sizeof(Suelo));
		suel->tipo=0;
		newCasilla->puntero=suel;
		newCasilla->cosa.caracteristica1=&suel->tipo;
		esc->head=newCasilla;
		esc->tail=newCasilla;
		esc->curr=newCasilla;
		esc->length++;
	for(int i=0;i<cant-1;i++){
		casilla *newCasilla=crearCasilla();
		newCasilla->tipo=5;
		Suelo *suel=(Suelo *)malloc(sizeof(Suelo));
		suel->tipo=0;
		newCasilla->puntero=suel;
		newCasilla->cosa.caracteristica1=&suel->tipo;
		esc->curr->next=newCasilla;
		esc->tail=newCasilla;
		esc->curr=newCasilla;
		esc->length++;
	}
	esc->curr=esc->head;//deja la lista en el principio
}
/*
printear
----------------
*esc: puntero a tipo escenario
tipo: entero
----------------
define que hay que printear dependiendo del tipo de casilla actual
*/
void printear(escenario *esc, int tipo){
	if(tipo==1){
			printf("Personaje\n");
			printf("Nombre: %s\n",(char *)esc->curr->cosa.caracteristica1);
			if(*(int *)esc->curr->cosa.caracteristica2==1){
				printf("Estado: Normal\n");
			}
			else if(*(int *)esc->curr->cosa.caracteristica2==2){
				printf("Estado: Brillante\n");
			}
			else if(*(int *)esc->curr->cosa.caracteristica2==3){
				printf("Estado: Mareado\n");
			}
			else if(*(int *)esc->curr->cosa.caracteristica2==4){
				printf("Estado: Wario\n");
			}
			printf("Monedas: %i\n",*(int *)esc->curr->cosa.caracteristica3);
			printf("-----------------\n");
		}
		else if(tipo==2){
			printf("Objeto\n");
			printf("Nombre: %s\n",(char *)esc->curr->cosa.caracteristica1);
			if(*(int *)esc->curr->cosa.caracteristica2==1){
				printf("Otorga: Health\n");
			}
			else if(*(int *)esc->curr->cosa.caracteristica2==2){
				printf("Otorga: Brillante\n");
			}
			else if(*(int *)esc->curr->cosa.caracteristica2==3){
				printf("Otorga: Mareado\n");
			}
			else if(*(int *)esc->curr->cosa.caracteristica2==4){
				printf("Otorga: Wario\n");
			}
			printf("-----------------\n");
		}
		else if(tipo==3){
			printf("Enemigo\n");
			printf("Nombre: %s\n",(char *)esc->curr->cosa.caracteristica1);
			printf("-----------------\n");
		}
		else if(tipo==4){
			printf("Bloque\n");
			if(*(int *)esc->curr->cosa.caracteristica4==0){
				printf("Contenido: Monedas\n");
				printf("Monedas: %i\n",*(int *)esc->curr->cosa.caracteristica1);
			}
			else{
				printf("Contenido: Objeto\n");
				printf("Nombre: %s\n",(char *)esc->curr->cosa.caracteristica1);
				if(*(int *)esc->curr->cosa.caracteristica2==1){
					printf("Otorga: Health\n");
				}
				else if(*(int *)esc->curr->cosa.caracteristica2==2){
					printf("Otorga: Mareado\n");
				}
				else if(*(int *)esc->curr->cosa.caracteristica2==3){
					printf("Otorga: Wario\n");
				}
				else if(*(int *)esc->curr->cosa.caracteristica2==4){
					printf("Otorga: Brillante\n");
				}
			}
			printf("-----------------\n");
		}
		else if(tipo==5){
			printf("Suelo\n");
			if(*(int *)esc->curr->cosa.caracteristica1==0){
				printf("Tipo: Piso firme\n");
			}
			else if(*(int *)esc->curr->cosa.caracteristica1==1){
				printf("Tipo: Agujero infinito\n");
			}
			printf("-----------------\n");
		}
}
/*
mostrar
----------------
*esc: puntero a tipo escenario
i: entero
----------------
printea la casilla solicitada
*/
void mostrar(escenario *esc, int i){
	if(esc->length-1<i){
		printf("El indice supera el largo del escenario\n");
	}
	else if(esc->posCurr==i){
		printf("-----------------\n");//separaciones
		printear(esc, esc->curr->tipo);
	}
	else if(esc->posCurr<i){
		casilla *auxPos;
		int pos=esc->posCurr;
		auxPos=esc->curr;
		while(esc->posCurr!=i){
			esc->curr=esc->curr->next;
			esc->posCurr++;
		}
		printf("-----------------\n");
		printear(esc, esc->curr->tipo);
		esc->curr=auxPos;
		esc->posCurr=pos;
	}
	else if(esc->posCurr>i){
		casilla *auxPos;
		int pos=esc->posCurr;
		auxPos=esc->curr;
		esc->curr=esc->head;
		esc->posCurr=0;
		while(esc->posCurr!=i){
			esc->curr=esc->curr->next;
			esc->posCurr++;
		}
		printf("-----------------\n");
		printear(esc, esc->curr->tipo);
		esc->curr=auxPos;
		esc->posCurr=pos;
	}
}
/*
mostrar_todo
----------------
*esc: puntero a tipo escenario
----------------
printea todas las casillas de la lista
*/
void mostrar_todo(escenario *esc){
	if(esc->length==0){
		printf("Escenario Vacio\n");
	}
	else{
		casilla *aux=esc->curr;
		esc->curr=esc->head;
		printf("-----------------\n");//separaciones
		for(int i=0;i<esc->length;i++){
			printear(esc, esc->curr->tipo);
			esc->curr=esc->curr->next;
		}
		esc->curr=aux;
	}
}
/*
anadir_elemento
----------------
*esc: puntero a tipo escenario
*ele: puntero a tipo elemento
*memEle: puntero a void (direccion de memoria del struct del elemento)
tipoEle: entero (tipo de elemento de la casilla)
i: entero
----------------
anade un nuevo nodo a la lista
*/
void anadir_elemento(escenario *esc, elemento *ele, void *memEle, int tipoEle, int i){ //cuidado con el maximo
	if(i>esc->length){//arreglar esto
		printf("El indice supera el largo de la lista\n");
	}
	else if(i==0){
		if(esc->length==0){ //Siempre se parte con el personaje
			casilla *newCasilla=crearCasilla();
			newCasilla->tipo=tipoEle;
			newCasilla->puntero=memEle;
			newCasilla->cosa=*ele;
			esc->head=newCasilla;
			esc->curr=newCasilla;
			esc->tail=newCasilla;
			esc->length++;
		}
		else{
			casilla *newCasilla=crearCasilla();
			newCasilla->next=esc->head;
			newCasilla->tipo=tipoEle;
			newCasilla->cosa=*ele;
			newCasilla->puntero=memEle;
			esc->head=newCasilla;
			esc->length++;
			esc->curr=newCasilla;
		}
	}
	else if(i==esc->length){
		casilla *auxPos;
		int pos=esc->posCurr;
		auxPos=esc->curr;
		esc->curr=esc->tail;
		casilla *newCasilla=crearCasilla();
		esc->curr->next=newCasilla;
		newCasilla->tipo=tipoEle;
		newCasilla->cosa=*ele;
		newCasilla->puntero=memEle;
		esc->tail=newCasilla;
		esc->curr=newCasilla;
		esc->length++;
		esc->curr=auxPos;
		esc->posCurr=pos;
		
	}
	else{
		casilla *auxPos;
		int pos=esc->posCurr;
		auxPos=esc->curr;
		esc->curr=esc->head;
		esc->posCurr=0;
		while(esc->posCurr!=i-1){
			esc->curr=esc->curr->next;
			esc->posCurr++;
		}
		casilla *newCasilla=crearCasilla();
		newCasilla->next=esc->curr->next;
		esc->curr->next=newCasilla;
		newCasilla->tipo=tipoEle;
		newCasilla->cosa=*ele;
		newCasilla->puntero=memEle;
		esc->curr=newCasilla;
		esc->length++;
		esc->curr=auxPos;
		esc->posCurr=pos;
	}
}
/*
borrar_elemento
----------------
*esc: puntero a tipo escenario
i: entero
----------------
borra el elemento pedido de la lista
*/
void borrar_elemento(escenario *esc, int i){
	if(esc->length-1<i){
		printf("El indice supera el largo del escenario\n");
	}
	else if(i==0){
		if(esc->length==1){
			if(esc->head->tipo==4){
				Bloque *bloc=esc->head->puntero;
				free(bloc->contenido);
			}
			free(esc->head->puntero);
			free(esc->head);
			esc->head=NULL;
			esc->curr=NULL;
			esc->tail=NULL;
			esc->length=0;
			esc->posCurr=0;
		}
		else{
			casilla *aux;
			aux=esc->head;
			esc->head=esc->head->next;
			esc->curr=esc->head;
			if(aux->tipo==4){
				Bloque *bloc=aux->puntero;
				free(bloc->contenido);
			}
			free(aux->puntero);
			free(aux);
			esc->length--;
		}
	}
	else if(i==esc->length-1){
		casilla *auxPos;
		int pos=esc->posCurr;
		auxPos=esc->curr;
		esc->curr=esc->head;
		esc->posCurr=0;
		while(esc->posCurr!=esc->length-2){
			esc->curr=esc->curr->next;
			esc->posCurr++;
		}
		esc->tail=esc->curr;
		if(esc->curr->next->tipo==4){
			Bloque *bloc=esc->curr->next->puntero;
			free(bloc->contenido);
		}
		free(esc->curr->next->puntero);
		free(esc->curr->next);
		esc->length--;
		esc->curr=auxPos;
		esc->posCurr=pos;
	}
	else{
		casilla *auxPos;
		int pos=esc->posCurr;
		auxPos=esc->curr;
		esc->curr=esc->head;
		esc->posCurr=0;
		while(esc->posCurr!=i-1){
			esc->curr=esc->curr->next;
			esc->posCurr++;
		}
		casilla *aux;
		aux=esc->curr->next;
		esc->curr->next=esc->curr->next->next;
		if(esc->curr->next->tipo==4){
			Bloque *bloc=esc->curr->next->puntero;
			free(bloc->contenido);
		}
		free(aux->puntero);
		free(aux);
		esc->length--;
		esc->curr=auxPos;
		esc->posCurr=pos;
	}
}
/*
borrar_todo
----------------
*esc: puntero a tipo escenario
----------------
borra todas las casillas de la lista
*/
void borrar_todo(escenario *esc){
	esc->curr=esc->head;
	int larguito=esc->length;
	for(int i=0; i<larguito; i++){
		casilla *aux;
		aux=esc->curr;
		esc->curr=esc->curr->next;
		if(aux->tipo==4){
			Bloque *bloc=aux->puntero;
			free(bloc->contenido);
		}
		free(aux->puntero);
		free(aux);
		esc->length--;
	}
}
/*
anadirPersonaje
----------------
*esc: puntero a tipo escenario
----------------
ayuda a anadir_elemento dandole los parametros necesarios
*/
void anadirPersonaje(escenario *esc){
	Personaje *per=crearPersonaje();
	elemento cosa;
	cosa.caracteristica1=per->nombre;
	cosa.caracteristica2=&per->estado;
	cosa.caracteristica3=&per->monedas;
	anadir_elemento(esc,&cosa,per,1,0);
	esc->posCurr=0;
	esc->curr=esc->head;
}

/*
anadirObjeto
----------------
*esc: puntero a tipo escenario
i: entero
----------------
ayuda a anadir_elemento dandole los parametros necesarios
*/
void anadirObjeto(escenario *esc, int i){
	Objeto *obj=crearObjeto();
	elemento cosa;
	cosa.caracteristica1=obj->nombre;
	cosa.caracteristica2=&obj->estado;
	anadir_elemento(esc,&cosa,obj,2,i);
}
/*
anadirEnemigo
----------------
*esc: puntero a tipo escenario
i: entero
----------------
ayuda a anadir_elemento dandole los parametros necesarios
*/
void anadirEnemigo(escenario *esc, int i){
	Enemigo *ene=crearEnemigo();
	elemento cosa;
	cosa.caracteristica1=ene->nombre;
	anadir_elemento(esc,&cosa,ene,3,i);
}
/*
anadirBloque
----------------
*esc: puntero a tipo escenario
i: entero
----------------
ayuda a anadir_elemento dandole los parametros necesarios
*/
void anadirBloque(escenario *esc, int i){
	Bloque *bloc=crearBloque();
	elemento cosa;
	if(bloc->tipo==1){
		Objeto *obj;
		obj=bloc->contenido;
		cosa.caracteristica1=obj->nombre;
		cosa.caracteristica2=&obj->estado;
		cosa.caracteristica4=&bloc->tipo;
	}
	else{
		cosa.caracteristica1=bloc->contenido;
		cosa.caracteristica4=&bloc->tipo;
	}
	anadir_elemento(esc,&cosa,bloc,4,i);
}
/*
anadirSuelo
----------------
*esc: puntero a tipo escenario
i: entero
----------------
ayuda a anadir_elemento dandole los parametros necesarios
*/
void anadirSuelo(escenario *esc, int i){
	Suelo *suel=crearSuelo();
	elemento cosa;
	cosa.caracteristica1=&suel->tipo;
	anadir_elemento(esc,&cosa,suel,5,i);
}
/*
anadirSueloPlano
----------------
*esc: puntero a tipo escenario
i: entero
----------------
ayuda a anadir_elemento dandole los parametros necesarios y definiendo por defecto el suelo plano
*/
void anadirSueloPlano(escenario *esc, int i){
	Suelo newSuelo, *pNewSuelo;
	newSuelo.tipo=0;
	pNewSuelo=(Suelo *)malloc(sizeof(Suelo));
	*pNewSuelo=newSuelo;
	elemento cosa;
	cosa.caracteristica1=&pNewSuelo->tipo;
	anadir_elemento(esc,&cosa,pNewSuelo,5,i);
}
/*
sacarLargo
----------------
*esc: puntero a tipo escenario
i: entero
----------------
retorna el largo de la lista
*/
int sacarLargo(escenario *esc){
	return esc->length;
}