#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "escenario.h"
#include "acciones.h"

int main(){
	escenario *esc;
	esc=crearEscenario();//inicia la lista enlazada
	int largo,eleccion=6;
	printf("Gracias por ser parte del programa de recuperacion de memoria de Mario\n");
	printf("Para empezar, ingrese el largo del escenario: ");
	scanf("%i",&largo);
	crearMundo(esc,largo);//rellena con pisos planos
	printf("-----------------------\n");
	printf("Creacion del escenario\n");
	printf("-----------------------\n");
	printf("A continuacion puede personalizar el escenario a su gusto\n");
	printf("ADVERTENCIA! El personaje se inicia en la casilla 0, asi que si ingresas algo en esa casilla sera borrado\n");
	while(eleccion!=0){
		printf("-----------------------\n");
		printf("Ingrese alguna de las siguientes opciones:\n");
		printf("1: Mostrar\n");
		printf("2: Mostrar todo\n");
		printf("3: Anadir elemento\n");
		printf("4: Borrar elemento\n");
		printf("5: Borrar todo\n");
		printf("0: Terminar de editar\n");
		printf("-----------------------\n");
		scanf("%i",&eleccion);
		if(eleccion==1){
			int posPrint;
			printf("Ingrese la casilla a mostrar: ");
			scanf("%i",&posPrint);
			mostrar(esc,posPrint);
		}
		else if(eleccion==2){
			mostrar_todo(esc);
		}
		else if(eleccion==3){
			int eleNum,posEle;
			printf("-----------------------\n");
			printf("Ingrese el elemento a anadir:\n");
			printf("1: Objeto\n");
			printf("2: Enemigo\n");
			printf("3: Bloque\n");
			printf("4: Suelo\n");
			printf("-----------------------\n");
			scanf("%i",&eleNum);
			printf("Ingrese la posicion en donde desea agregar el elemento: ");
			scanf("%i",&posEle);
			if(eleNum==1){
				if(sacarLargo(esc)<largo){
					anadirObjeto(esc,posEle);
				}
				else{
					borrar_elemento(esc,posEle);
					anadirObjeto(esc,posEle);
				}
			}
			else if(eleNum==2){
				if(sacarLargo(esc)<largo){
					anadirEnemigo(esc,posEle);
				}
				else{
					borrar_elemento(esc,posEle);
					anadirEnemigo(esc,posEle);
				}
			}
			else if(eleNum==3){
				if(sacarLargo(esc)<largo){
					anadirBloque(esc,posEle);
				}
				else{
					borrar_elemento(esc,posEle);
					anadirBloque(esc,posEle);
				}
			}
			else if(eleNum==4){
				if(sacarLargo(esc)<largo){
					anadirSuelo(esc,posEle);
				}
				else{
					borrar_elemento(esc,posEle);
					anadirSuelo(esc,posEle);
				}
			}
			else{
				printf("Opcion invalida, no se agrego nada\n");
			}
		}
		else if(eleccion==4){
			int intBorrar;
			printf("Ingrese la posicion de la casilla a borrar: ");
			scanf("%i",&intBorrar);
			borrar_elemento(esc,intBorrar);
		}
		else if(eleccion==5){
			borrar_todo(esc);
			printf("Ahora el escenario se encuentra vacio\n");
		}
		else if(eleccion!=0){
			printf("Ingrese una opcion valida\n");
		}
	}
	printf("-----------------------\n");
	printf("A jugar!\n");
	printf("-----------------------\n");
	borrar_elemento(esc,0);
	anadirPersonaje(esc);
	printf("El escenario quedo de la siguiente forma\n");
	mostrar_todo(esc);
	int jugar=1;
	while(jugar==1){
		printf("-----------------------\n");
		printf("Ingrese alguna de las siguientes opciones:\n");
		printf("1: Saltar encima\n");
		printf("2: Caminar\n");
		printf("3: Rushear\n");
		printf("4: Taclear al frente\n");
		printf("5: Ver plata\n");
		printf("6: Mostrar\n");
		printf("7: Mostrar todo\n");
		printf("0: Salir del juego\n");
		printf("-----------------------\n");
		scanf("%i",&eleccion);
		if(eleccion==1){
			int salto;
			printf("Ingrese la cantidad de casillas a saltar: ");
			scanf("%i",&salto);
			saltar_encima(esc,salto);
			if(stop(esc)==1){
				jugar=0;
			}
		}
		else if(eleccion==2){
			caminar_en(esc);
			if(stop(esc)==1){
				jugar=0;
			}
		}
		else if(eleccion==3){
			rushear(esc);
			if(stop(esc)==1){
				jugar=0;
			}
		}
		else if(eleccion==4){
			taclear_al_frente(esc);
		}
		else if(eleccion==5){
			ver_plata(esc);
		}
		else if(eleccion==6){
			int posPrint;
			printf("Ingrese la casilla a mostrar: ");
			scanf("%i",&posPrint);
			mostrar(esc,posPrint);
		}
		else if(eleccion==7){
			mostrar_todo(esc);
		}
		else if(eleccion==0){
			jugar=0;
		}
		else{
			printf("Ingrese una opcion valida\n");
		}
	}
	borrar_todo(esc);
	free(esc);
	return 0;	
}