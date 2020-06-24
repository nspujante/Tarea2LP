#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "escenario.h"
#include "acciones.h"
/*
borrarNodo
----------------
*esc: puntero a tipo escenario
*borrar: puntero a tipo casilla
----------------
libera la memoria del nodo recibido
*/
void borrarNodo(escenario *esc, casilla *borrar){
	if(borrar->tipo==4){
			Bloque *bloc=borrar->puntero;
			free(bloc->contenido);
		}
		free(borrar->puntero);
		free(borrar);
		esc->length--;
}
/*
saltar_encima
----------------
*esc: puntero a tipo escenario
i: entero
----------------
realiza la accion de saltar especificada en la tarea, ve todos los casos posibles
*/
void saltar_encima(escenario *esc, int i){
	if(*(int *)esc->curr->cosa.caracteristica2!=3){
		printf("HICE saltar encima\n");
		int suma;
		suma=esc->posCurr+i;
		if(i>0){ //verifica si es un salto hacia la derecha
			if(suma>esc->length-1){ //verifica si el salto sale del escenario
				printf("Gracias alumnos de lp por ayudarme a recuperar la memoria, pero tu 100 esta en otra tarea\n");
				esc->posCurr=999;
			}
			else if(esc->posCurr==0){ //verifica si el presonaje esta al comienzo de la lista
				if(i==1){
					if(esc->curr->next->tipo==5){
						if(*(int *)esc->curr->next->cosa.caracteristica1==1){
							printf("WHOOOAH! %s se ha caido en un agujero y ha muerto, vuelves al inicio :c\n",(char *)esc->curr->cosa.caracteristica1);
						}
						else{
							casilla *personaje, *borrar;
							personaje=esc->curr;
							borrar=esc->curr->next;
							personaje->next=borrar->next;
							anadirSueloPlano(esc,0);
							borrarNodo(esc, borrar);
							esc->curr=personaje;
							esc->posCurr++;
						}
					}
					else{
						if(esc->curr->next->tipo==2){
							*(int *)esc->curr->cosa.caracteristica2=*(int *)esc->curr->next->cosa.caracteristica2;
						}
						else if(esc->curr->next->tipo==4){
							if(*(int *)esc->curr->next->cosa.caracteristica4==0){
								if(*(int *)esc->curr->cosa.caracteristica2==4){
									*(int *)esc->curr->cosa.caracteristica3+=(*(int *)esc->curr->next->cosa.caracteristica1*2);
								}
								else{
									*(int *)esc->curr->cosa.caracteristica3+=(*(int *)esc->curr->next->cosa.caracteristica1);
								}
							}
							else{
								*(int *)esc->curr->cosa.caracteristica2=*(int *)esc->curr->next->cosa.caracteristica2;
							}
						}
						casilla *personaje, *borrar;
						personaje=esc->curr;
						borrar=esc->curr->next;
						personaje->next=borrar->next;
						anadirSueloPlano(esc,0);
						borrarNodo(esc, borrar);
						esc->curr=personaje;
						esc->posCurr++;
					}
				}
				else{
					casilla *personaje, *borrar;
					int actual;
					personaje=esc->curr;
					actual=esc->posCurr;
					esc->head=esc->curr->next;
					esc->curr=esc->head;
					for(int j=0;j<suma-2;j++){
						esc->curr=esc->curr->next;
					}
					if(esc->curr->next->tipo==5){
						if(*(int *)esc->curr->next->cosa.caracteristica1==1){
							esc->head=personaje;
							esc->curr=personaje;
							esc->posCurr=0;
							printf("WHOOOAH! %s se ha caido en un agujero y ha muerto, vuelves al inicio :c\n",(char *)esc->curr->cosa.caracteristica1);
						}
						else{
							borrar=esc->curr->next;
							personaje->next=borrar->next;
							esc->curr->next=personaje;
							borrarNodo(esc,borrar);
							anadirSueloPlano(esc,actual);
							esc->curr=personaje;
							esc->posCurr=suma;
						}
					}
					else{
						borrar=esc->curr->next;
						if(borrar->tipo==2){
							*(int *)personaje->cosa.caracteristica2=*(int *)borrar->cosa.caracteristica2;
						}
						else if(borrar->tipo==4){
							if(*(int *)borrar->cosa.caracteristica4==0){
								if(*(int *)personaje->cosa.caracteristica2==4){
									*(int *)personaje->cosa.caracteristica3+=(*(int *)borrar->cosa.caracteristica1*2);
								}
								else{
									*(int *)personaje->cosa.caracteristica3+=(*(int *)borrar->cosa.caracteristica1);
								}
							}
							else{
								*(int *)personaje->cosa.caracteristica2=*(int *)borrar->cosa.caracteristica2;
							}
						}
						personaje->next=borrar->next;
						esc->curr->next=personaje;
						borrarNodo(esc,borrar);
						anadirSueloPlano(esc,actual);
						esc->curr=personaje;
						esc->posCurr=suma;
					}
				}

			}
			else{
				casilla *personaje, *borrar;
				int actual;
				personaje=esc->curr;
				actual=esc->posCurr;
				esc->curr=esc->head;
				for(int j=0;j<suma-1;j++){
					esc->curr=esc->curr->next;
				}
				if(esc->curr->next->tipo==5){
					if(*(int *)esc->curr->next->cosa.caracteristica1==1){
						printf("WHOOOAH! %s se ha caido en un agujero y ha muerto, vuelves al inicio :c\n",(char *)personaje->cosa.caracteristica1);
						*(int *)personaje->cosa.caracteristica2=1;
						*(int *)personaje->cosa.caracteristica3=0;
						esc->curr=esc->head;
						for(int j=0; j!=esc->posCurr-1;j++){
							esc->curr=esc->curr->next;
						}
						esc->curr->next=personaje->next;
						personaje->next=esc->head;
						esc->head=personaje;
						esc->curr=personaje;
						esc->posCurr=0;
					}
					else{
						esc->curr=esc->head;
						for(int j=0;j<actual-1;j++){
							esc->curr=esc->curr->next;
						}
						esc->curr->next=personaje->next;
						anadirSueloPlano(esc,actual);
						esc->curr=esc->head;
						for(int j=0;j<suma-1;j++){
							esc->curr=esc->curr->next;
						}
						borrar=esc->curr->next;
						personaje->next=borrar->next;
						esc->curr->next=personaje;
						borrarNodo(esc,borrar);
						esc->curr=personaje;
						esc->posCurr=suma;
					}
				}
				else{
					esc->curr=esc->head;
					for(int j=0;j<actual-1;j++){
						esc->curr=esc->curr->next;
					}
					esc->curr->next=personaje->next;
					anadirSueloPlano(esc,actual);
					esc->curr=esc->head;
					for(int j=0;j<suma-1;j++){
						esc->curr=esc->curr->next;
					}
					borrar=esc->curr->next;
					if(borrar->tipo==2){
						*(int *)personaje->cosa.caracteristica2=*(int *)borrar->cosa.caracteristica2;
					}
					else if(borrar->tipo==4){
						if(*(int *)borrar->cosa.caracteristica4==0){
							if(*(int *)personaje->cosa.caracteristica2==4){
								*(int *)personaje->cosa.caracteristica3+=(*(int *)borrar->cosa.caracteristica1*2);
							}
							else{
								*(int *)personaje->cosa.caracteristica3+=(*(int *)borrar->cosa.caracteristica1);
							}
						}
						else{
							*(int *)personaje->cosa.caracteristica2=*(int *)borrar->cosa.caracteristica2;
						}
					}
					personaje->next=borrar->next;
					esc->curr->next=personaje;
					borrarNodo(esc,borrar);
					esc->curr=personaje;
					esc->posCurr=suma;
				}
			}
		}
		else if(i<0){
			if(esc->posCurr==0 || suma<0){
				printf("HEY! Cuidado, no puedes saltar mas alla del principio del escenario\n");
			}
			else if(suma==0){
				casilla *personaje, *borrar;
				int actual=esc->posCurr;
				personaje=esc->curr;
				esc->curr=esc->head;
				for(int j=0;j<actual-1;j++){ 
					esc->curr=esc->curr->next;
				}
				esc->curr->next=personaje->next;
				personaje->next=esc->head;
				esc->head=personaje;
				borrar=personaje->next;
				personaje->next=borrar->next;
				borrarNodo(esc,borrar);
				anadirSueloPlano(esc,actual);
				esc->curr=personaje;
				esc->posCurr=0;
			}
			else{
				casilla *personaje, *borrar;
				int actual=esc->posCurr;
				personaje=esc->curr;
				esc->curr=esc->head;
				for(int j=0;j<actual-1;j++){ //recorre hasta el nodo anterior al personaje
					esc->curr=esc->curr->next;
				}
				esc->curr->next=personaje->next; //enlaza el nodo anterior de personaje con el siguiente
				esc->curr=esc->head;
				for(int j=0;j<suma-1;j++){ //recorre hasta el nodo anterior de la posicion a reemplazar
					esc->curr=esc->curr->next;
				}
				if(esc->curr->next->tipo==5){
					if(*(int *)esc->curr->next->cosa.caracteristica1==1){
						printf("WHOOOAH! %s se ha caido en un agujero y ha muerto, vuelves al inicio :c\n",(char *)personaje->cosa.caracteristica1);
						*(int *)personaje->cosa.caracteristica2=1;
						*(int *)personaje->cosa.caracteristica3=0;
						personaje->next=esc->head;
						esc->head=personaje;
						esc->curr=personaje;
						esc->posCurr=0;
					}
					else{
						borrar=esc->curr->next;
						personaje->next=borrar->next;
						esc->curr->next=personaje;
						borrarNodo(esc,borrar);
						anadirSueloPlano(esc,actual);
						esc->curr=esc->head;
						esc->posCurr=suma;
					}
				}
				else{
					borrar=esc->curr->next;
					if(borrar->tipo==2){
						*(int *)personaje->cosa.caracteristica2=*(int *)borrar->cosa.caracteristica2;
					}
					else if(borrar->tipo==4){
						if(*(int *)borrar->cosa.caracteristica4==0){
							if(*(int *)personaje->cosa.caracteristica2==4){
								*(int *)personaje->cosa.caracteristica3+=(*(int *)borrar->cosa.caracteristica1*2);
							}
							else{
								*(int *)personaje->cosa.caracteristica3+=(*(int *)borrar->cosa.caracteristica1);
							}
						}
						else{
							*(int *)personaje->cosa.caracteristica2=*(int *)borrar->cosa.caracteristica2;
						}
					}
					personaje->next=borrar->next;
					esc->curr->next=personaje;
					borrarNodo(esc,borrar);
					anadirSueloPlano(esc,actual);
					esc->curr=esc->head;
					esc->posCurr=suma;
				}
			}
		}
	}
	else{
		printf("OH OH! %s esta mareado y no puede saltar\n",(char *)esc->curr->cosa.caracteristica1);
	}
}
/*
caminar_en
----------------
*esc: puntero a tipo escenario
----------------
realiza la accion de caminar especificada en la tarea, ve todos los casos posibles
*/
void caminar_en(escenario *esc){
	printf("HICE caminar en\n");
	if(esc->posCurr==0){
		if(esc->curr->next->tipo==3){
			printf("WHOOOAH! %s se ha topado con %s y ha muerto, vuelves al inicio :c\n",(char *)esc->curr->cosa.caracteristica1,(char *)esc->curr->next->cosa.caracteristica1);
		}
		else if(esc->curr->next->tipo==5){
			if(*(int *)esc->curr->next->cosa.caracteristica1==1){
				printf("WHOOOAH! %s se ha caido en un agujero y ha muerto, vuelves al inicio :c\n",(char *)esc->curr->cosa.caracteristica1);
			}
			else{
				casilla *personaje, *borrar;
				personaje=esc->curr;
				borrar=esc->curr->next;
				personaje->next=borrar->next;
				anadirSueloPlano(esc,0);
				borrarNodo(esc, borrar);
				esc->curr=personaje;
				esc->posCurr++;
			}
		}
		else{
			if(esc->curr->next->tipo==2){
				*(int *)esc->curr->cosa.caracteristica2=*(int *)esc->curr->next->cosa.caracteristica2;
			}
			casilla *personaje, *borrar;
			personaje=esc->curr;
			borrar=esc->curr->next;
			personaje->next=borrar->next;
			anadirSueloPlano(esc,0);
			borrarNodo(esc, borrar);
			esc->curr=personaje;
			esc->posCurr++;
		}
	}
	else if(esc->curr->next==NULL){
		printf("Gracias alumnos de lp por ayudarme a recuperar la memoria, pero tu 100 esta en otra tarea\n");
		esc->posCurr=999;
	}
	else if(esc->curr->next->tipo==3){
		printf("WHOOOAH! %s se ha topado con %s y ha muerto, vuelves al inicio :c\n",(char *)esc->curr->cosa.caracteristica1,(char *)esc->curr->next->cosa.caracteristica1);
		*(int *)esc->curr->cosa.caracteristica2=1;
		*(int *)esc->curr->cosa.caracteristica3=0;
		casilla *personaje;
		personaje=esc->curr;
		esc->curr=esc->head;
		for(int j=0; j!=esc->posCurr-1;j++){
			esc->curr=esc->curr->next;
		}
		esc->curr->next=personaje->next;
		personaje->next=esc->head;
		esc->head=personaje;
		esc->curr=personaje;
		esc->posCurr=0;
	}
	else if(esc->curr->next->tipo==5){
		if(*(int *)esc->curr->next->cosa.caracteristica1==1){
			printf("WHOOOAH! %s se ha caido en un agujero y ha muerto, vuelves al inicio :c\n",(char *)esc->curr->cosa.caracteristica1);
			*(int *)esc->curr->cosa.caracteristica2=1;
			*(int *)esc->curr->cosa.caracteristica3=0;
			casilla *personaje;
			personaje=esc->curr;
			esc->curr=esc->head;
			for(int j=0; j!=esc->posCurr-1;j++){
				esc->curr=esc->curr->next;
			}
			esc->curr->next=personaje->next;
			personaje->next=esc->head;
			esc->head=personaje;
			esc->curr=personaje;
			esc->posCurr=0;
		}
		else{
			casilla *personaje, *borrar;
			personaje=esc->curr;
			borrar=esc->curr->next;
			personaje->next=borrar->next;
			borrarNodo(esc,borrar);
			anadirSueloPlano(esc,esc->posCurr);
			esc->curr=esc->head;
			for(int j=0; j!=esc->posCurr;j++){
				esc->curr=esc->curr->next;
			}
			esc->curr->next=personaje;
			esc->curr=personaje;
			esc->posCurr++;
		}
	}
	else{
		if(esc->curr->next->tipo==2){
			*(int *)esc->curr->cosa.caracteristica2=*(int *)esc->curr->next->cosa.caracteristica2;
		}
		casilla *personaje, *borrar;
		personaje=esc->curr;
		borrar=esc->curr->next;
		personaje->next=borrar->next;
		borrarNodo(esc,borrar);
		anadirSueloPlano(esc,esc->posCurr);
		esc->curr=esc->head;
		for(int j=0; j!=esc->posCurr;j++){
			esc->curr=esc->curr->next;
		}
		esc->curr->next=personaje;
		esc->curr=personaje;
		esc->posCurr++;
	}
}
/*
rushear
----------------
*esc: puntero a tipo escenario
----------------
realiza la accion de rushear especificada en la tarea, ve todos los casos posibles
*/
void rushear(escenario *esc){
	if(*(int *)esc->curr->cosa.caracteristica2==2){
		printf("HICE rushear\n");
		int r=0;
		while(r<3){
			if(esc->posCurr==0){
				if(esc->curr->next->tipo==5){
					if(*(int *)esc->curr->next->cosa.caracteristica1==1){
						printf("WHOOOAH! %s se ha caido en un agujero y ha muerto, vuelves al inicio :c\n",(char *)esc->curr->cosa.caracteristica1);
						r=3;
						*(int *)esc->curr->cosa.caracteristica1=1;
					}
					else{
						casilla *personaje, *borrar;
						personaje=esc->curr;
						borrar=esc->curr->next;
						personaje->next=borrar->next;
						anadirSueloPlano(esc,0);
						borrarNodo(esc, borrar);
						esc->curr=personaje;
						esc->posCurr++;
						r++;
						*(int *)personaje->cosa.caracteristica1=1;
					}
				}
				else{
					casilla *personaje, *borrar;
					personaje=esc->curr;
					borrar=esc->curr->next;
					personaje->next=borrar->next;
					anadirSueloPlano(esc,0);
					borrarNodo(esc, borrar);
					esc->curr=personaje;
					esc->posCurr++;
					r++;
					*(int *)personaje->cosa.caracteristica1=1;
				}
			}
			else if(esc->curr->next==NULL){
				printf("Gracias alumnos de lp por ayudarme a recuperar la memoria, pero tu 100 esta en otra tarea\n");
				r=3;
				esc->posCurr=999;
			}
			else if(esc->curr->next->tipo==5){
				if(*(int *)esc->curr->next->cosa.caracteristica1==1){
					printf("WHOOOAH! %s se ha caido en un agujero y ha muerto, vuelves al inicio :c\n",(char *)esc->curr->cosa.caracteristica1);
					*(int *)esc->curr->cosa.caracteristica2=1;
					*(int *)esc->curr->cosa.caracteristica3=0;
					casilla *personaje;
					personaje=esc->curr;
					esc->curr=esc->head;
					for(int j=0; j!=esc->posCurr-1;j++){
						esc->curr=esc->curr->next;
					}
					esc->curr->next=personaje->next;
					personaje->next=esc->head;
					esc->head=personaje;
					esc->curr=personaje;
					esc->posCurr=0;
					r=3;
					*(int *)personaje->cosa.caracteristica1=1;
				}
				else{
					casilla *personaje, *borrar;
					personaje=esc->curr;
					borrar=esc->curr->next;
					personaje->next=borrar->next;
					borrarNodo(esc,borrar);
					anadirSueloPlano(esc,esc->posCurr);
					esc->curr=esc->head;
					for(int j=0; j!=esc->posCurr;j++){
						esc->curr=esc->curr->next;
					}
					esc->curr->next=personaje;
					esc->curr=personaje;
					esc->posCurr++;
					r++;
					*(int *)personaje->cosa.caracteristica1=1;
				}
			}
			else{
				casilla *personaje, *borrar;
				personaje=esc->curr;
				borrar=esc->curr->next;
				personaje->next=borrar->next;
				borrarNodo(esc,borrar);
				anadirSueloPlano(esc,esc->posCurr);
				esc->curr=esc->head;
				for(int j=0; j!=esc->posCurr;j++){
					esc->curr=esc->curr->next;
				}
				esc->curr->next=personaje;
				esc->curr=personaje;
				esc->posCurr++;
				r++;
				*(int *)personaje->cosa.caracteristica1=1;
			}
		}	
	}
	else{
		printf("OH OH! %s no esta brillando, no puede rushear!\n",(char *)esc->curr->cosa.caracteristica1);
	}
}
/*
taclear_al_frente
----------------
*esc: puntero a tipo escenario
----------------
realiza la accion de taclear especificada en la tarea, ve todos los casos posibles
*/
void taclear_al_frente(escenario *esc){
	printf("HICE taclear al frente\n");
	if(esc->posCurr==0){
		if(esc->curr->next->tipo==3){
			casilla *personaje, *borrar;
			personaje=esc->curr;
			borrar=esc->curr->next;
			personaje->next=borrar->next;
			anadirSueloPlano(esc,0);
			borrarNodo(esc, borrar);
			esc->curr=personaje;
			esc->posCurr++;
		}
		else if(esc->curr->next->tipo==5){
			if(*(int *)esc->curr->next->cosa.caracteristica1==1){
				printf("WHOOOAH! %s se ha caido en un agujero y ha muerto, vuelves al inicio :c\n",(char *)esc->curr->cosa.caracteristica1);
			}
			else{
				printf("WHOOOAH! %s se ha mareado ya que no habia enemigos\n",(char *)esc->curr->cosa.caracteristica1);
				*(int *)esc->curr->cosa.caracteristica2=3;
			}
		}
		else{
			printf("WHOOOAH! %s se ha mareado ya que no habia enemigos\n",(char *)esc->curr->cosa.caracteristica1);
			*(int *)esc->curr->cosa.caracteristica2=3;
		}
	}
	else if(esc->curr->next->tipo==3){
		casilla *personaje, *borrar;
		personaje=esc->curr;
		borrar=esc->curr->next;
		personaje->next=borrar->next;
		borrarNodo(esc,borrar);
		anadirSueloPlano(esc,esc->posCurr);
		esc->curr=esc->head;
		for(int j=0; j!=esc->posCurr;j++){
			esc->curr=esc->curr->next;
		}
		esc->curr->next=personaje;
		esc->curr=personaje;
		esc->posCurr++;
	}
	else if(esc->curr->next==NULL){
		printf("WHOOOAH! %s se ha mareado ya que no habia enemigos\n",(char *)esc->curr->cosa.caracteristica1);
		*(int *)esc->curr->cosa.caracteristica2=3;
	}
	else if(esc->curr->next->tipo==5){
		if(*(int *)esc->curr->next->cosa.caracteristica1==1){
			printf("WHOOOAH! %s se ha caido en un agujero y ha muerto, vuelves al inicio :c\n",(char *)esc->curr->cosa.caracteristica1);
			*(int *)esc->curr->cosa.caracteristica2=1;
			*(int *)esc->curr->cosa.caracteristica3=0;
			casilla *personaje;
			personaje=esc->curr;
			esc->curr=esc->head;
			for(int j=0; j!=esc->posCurr-1;j++){
				esc->curr=esc->curr->next;
			}
			esc->curr->next=personaje->next;
			personaje->next=esc->head;
			esc->head=personaje;
			esc->curr=personaje;
			esc->posCurr=0;
		}
		else{
			printf("WHOOOAH! %s se ha mareado ya que no habia enemigos\n",(char *)esc->curr->cosa.caracteristica1);
			*(int *)esc->curr->cosa.caracteristica2=3;
		}
	}
	else{
		printf("WHOOOAH! %s se ha mareado ya que no habia enemigos\n",(char *)esc->curr->cosa.caracteristica1);
		*(int *)esc->curr->cosa.caracteristica2=3;
	}
}
/*
ver_plata
----------------
*esc: puntero a tipo escenario
i: entero
----------------
printea las monedas que tiene el personaje
*/
void ver_plata(escenario *esc){
	printf("Cantidad de monedas: %i\n",*(int *)esc->curr->cosa.caracteristica3);
}
/*
choice
----------------
*esc: puntero a tipo escenario
accion: entero
*listaAcc: puntero a tipo acciones
----------------
revisa si la accion pedida esta disponible
*/
void choice(int accion, acciones *listaAcc, escenario *esc){
//puchis :c
}
/*
stop
----------------
*esc: puntero a tipo escenario
----------------
revisa si el personaje llego al final del escenario, retorna un 1 si es el caso, 
si todavia le queda retorna 0
*/
int stop(escenario *esc){
	if(esc->posCurr==999){
		return 1;
	}
	return 0;
}