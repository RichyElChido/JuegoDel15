Juego del 15 hecho por Ricardo Enrique Pérez Villanueva

Instrucciones: Ejecute primero make, despues ./puzzle y lee la terminal por instrucciones.

Instrucciones y controles:
---------------------------------
Juego del 15 por Ricardo Enrique Perez Villanueva\n);

        Objetivo: Ordenar las piezas de forma de arcoiris, es decir blanco, rosa, rojo, naranja, amarillo, verde pasto, verde, verde turquesa, azul cielo, azul, azul rey, purpura, magenta, morado y negro.

        r = Resetear cámara y posiciones de bloques.
        w = Rota hacia arriba en Y
        s = Rota hacia abajo en Y
        a = Rota hacia izquierda en X
        d = Rota hacia derecha en X
        z = Rota hacia atras en Z
        x = Rota hacia adelante en Z
        u = Revuelve el puzzle de una forma predeterminada.
        Flecha Derecha = Trata de mover la pieza vacia con un movimiento derecho
        Flecha Izquierda = Trata de mover la pieza vacia con un movimiento izquierda
        Flecha Arriba = Trata de mover la pieza vacia con un movimiento hacia arriba
        Flecha Abajo = Trata de mover la pieza vacia con un movimiento hacia abajo
        v = Muestra las piezas como de Solidas o Cristal (Quita/Añade GlColorMaterial).
--------------------------------
La piezas se pueden ver como joyas o como piezas de plastico usando Blend y GlColor.
Recuerda que cuando resuelves el puzzle, se actualizará la cabecera de la ventana.
Ejemplo de controles:
    EN estado Default, si presionas Izquierda, no pasará nada, porque no hay pieza que al moverse a la izquierda cubra el espacio vacio.
    En cambio, si se presiona derecha, se movera la pieza morada, hacia la izquierda, por lo que cubrira el espacio vacio.
    Piensa que es un juego touch, y hacia la direccion donde mueves el dedo, se movera la piezas.
Notas:
*La pieza Purpura parece mas oscura que la Morada, pero (aparentemente) no es asi. Recuerda el orden donde empezaron.
*El tablero esta conformado de la siguiente forma:

                        |0 |1 |2 |3 |
                        |4 |5 |6 |7 |
                        |8 |9 |10|11|
                        |12|13|14|15|

Cada numero representa un cuadrante. Se explica mejor en el codigo.
