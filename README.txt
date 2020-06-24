Nicolás Pujante
201873533-7
Requisitos:
Tener todos los .c, .h y el makefile en la misma carpeta
Procedimiento:
Ingresar make para compilar y luego make run para correr.
Consideraciones:
Se considera que el usuario realiza siempre inputs validos (hay algunos puntos que permiten inputs invalidos, pero no todos).
Se considera que el usuario comienza a jugar siempre con el largo original dado por el (si se borra todo el escenario hay que volver a llenarlo).
Si quiere añadir un elemento a la lista cuando está llena se puede realizar sin borra un nodo antes.
Al añadir, se asume que el usuario ingresa una posición valida (la enumeracion parte desde el 0, por lo que si el alrgo es de 3
se podria ingresar 0,1,2).
Caminar no puede romper Bloques.
Al taclear, el personaje solo se mueve si el siguiente es un enemigo o hay un agujero, en ese caso cae y muere.
Rushear no toma objetos ni rompe bloques, además, si entre el rusheo hay un agujero, se cae.
Si bien no definí la lista de acciones disponibles ni use choice, el programa sigue teniendo las restricciones pedidas para el uso de acciones
(no se puede saltar estando mareado y no se puede rushear sin estar en estado brillante).
Creo que eso, porfa no lo maten, parece ser que el cuerpo humano solo resiste 96 punteros :c
Sorry por la ensalada de codigo, me di cuenta demasiado tarde que a lo mejor convenia usar switch.