// Proyecto Final, Juego del 15 por Ricardo Enrique Pérez Villanueva.

#include <math.h>
#include <stdio.h>		//Incluimos entrada/salida estandar
#include <GL/glut.h>	//freeglut
#include <GL/gl.h>
#include <unistd.h>

//#include "coords.h"
#include "Caja.h"
#include "Piezas.h"

//Coordenadas para rotar la camara.
float rotarX=0;
float rotarY=0;
float rotarZ=0;
bool inicio= true;//Si se esta cargando el juego. Se usa para poner las piezas en su lugar default.
bool scramble= false;//Si se quiere revolver.
bool movimiento=false;//Si ya se ha ejecutado un movimiento. Se usa para diferenciar el estado Default con la solucion.
bool solido=false;//Si se muestran como vidrio o madera.

void mySetLight(){//Se añade una luz en la posicion 1,1,1,1.
	float light0_position[] = {1.0,  1.0, 1.0, 1.0};	
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glEnable(GL_LIGHT0);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
}

//Funcion para inicializar a freeglut y configurar unas cosas de OpenGL
void myInit(const char* progName) {
		glutInitDisplayMode(GLUT_SINGLE 	//Le decimos a glut que necesitamos single framebuffer (FB)
							| GLUT_RGBA 	//con colores RGBA (con canal alfa),
							| GLUT_DEPTH);	//y un Z buffer (para profundidad).
		glutInitWindowSize(1000, 1000);		//Tamaño de la ventana
		glutInitWindowPosition(100, 100);	//Posición inicial de la ventana
		glutCreateWindow(progName);			//Desplegamos la ventana
		glClearColor(0.0, 0.0, 0.0, 0.0);	//glClear dejará la pantalla con este color (Negro)
}


//Funcion para cuando se redimensione la pantalla
void myReshape(int w,int h) {
		glViewport(0,0,w,h); // Reajusta el tamaño del objeto con forme se avanza
		glMatrixMode(GL_PROJECTION); // Matriz de proyección, no afecta el objeto
		glLoadIdentity(); // Para eliminar los valores de la matriz que ya tenpia guardada.
		gluPerspective(60.0, (double)w / (double)h, 0.1, 30.0);
		glMatrixMode(GL_MODELVIEW); // Matriz que modela el objeto.
		glLoadIdentity(); // Para eliminar los valores de la matriz que ya tenpia guardada.
}

//Funcion para dibujar en el FB.
void myDisplay() {
        glEnable(GL_DEPTH_TEST);
        float ambient[]  = {0.2125f, 0.1275f, 0.054f,1.0f};
	    float diffuse[]  = {0.714f, 0.4284f, 0.18144f,1.0f};
	    float specular[] = {0.393548f, 0.271906f, 0.166721f,1.0f};
	    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 					 
	    glEnable(GL_LIGHTING);
      	glShadeModel(GL_SMOOTH);
        if(solido){
            glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
            glEnable(GL_COLOR_MATERIAL);
        }
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  diffuse);
	    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 5);
		glLoadIdentity();					//Cargamos la matriz identidad.
		gluLookAt(0.0f , 0.0f, 5.0f, 0.0f , 0.0f, 0.2f , 0.0f, 1.0f,  0.0f);
        glRotated(rotarX,1, 0, 0);
	    glRotated(rotarY,0,1,0);
	    glRotated(rotarZ,0, 0, 1);//Matriz que permite rotar la camara.
        drawCaja();
        if(inicio){//Si es el inicio del juego, configuramos las posiciones Default
            setDefaultCoords();
            inicio=false;
        }
        if(scramble){//Si se activo la revolucion de piezas, se ejecuta la rutina.
            autoRevolver();
            scramble=false;
        }
        if(!solido){//Si queremos verlo como bloques solidos o como vidrio.	
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
        drawPiezas();//Dibujamos las piezas.
        if (movimiento && checkIfResolve()){//Vemos si el juego esta resuelto y no es el estado Default
            glutSetWindowTitle("Has solucionado el Puzzle!");//Si asi es, entonces mostramos el mensaje de victoria.
        }
        else{glutSetWindowTitle("Puzzle del 15");}//De otro modo, mostramos el nombre Default
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_LIGHTING);
        if(solido){//Hacemos Disable de lo que tengamos el solido.
            glDisable(GL_COLOR_MATERIAL);
        } else {glDisable(GL_BLEND);}
		glutSwapBuffers();	//Desplegamos el FB actual y nos movemos a otro FB
}

void myKeyboard(unsigned char key, int xx, int yy) {//Función que rota la cámara con las teclas. 
    switch(key){
	    case 'w':
            rotarX+=3;
            break;
      	case 's':
            rotarX-=3;
            break;
      	case 'd':
            rotarY+=3;
            break;
      	case 'a':
            rotarY-=3;
            break;
        case 'x':
            rotarZ+=3;
            break;
        case 'z':
            rotarZ-=3;
            break;
        case 'v'://cambia el estado de las piezas.
            solido= !solido;
            break;
        case 'u'://Revuelve el juego
            scramble=true;
            movimiento=true;
            break;
        case 'r'://Reinicia el juego
            rotarX=0;
            rotarY=0;
            rotarZ=0;
            inicio=true;
            movimiento=false;
            break;
    }
    glutPostRedisplay();
}

//Funcion extra que decide y mueve la piezas con las flechas direccionales
void moverPieza(int key, int x, int y){
	switch(key){
  	case GLUT_KEY_LEFT:
        intentaMover(1);
        movimiento=true;
        break;
	case GLUT_KEY_RIGHT:
        intentaMover(0);
        movimiento=true;
        break;
  	case GLUT_KEY_UP:
        intentaMover(3);
        movimiento=true;
        break;
  	case GLUT_KEY_DOWN:
        intentaMover(2);
        movimiento=true;
        break;
	}
    glutPostRedisplay();//Solo actualizamos cuando se toca una tecla.
}
//Función main
int main(int argc, char** argv) {//Main que imprime las instrucciones
        printf("Juego del 15 por Ricardo Enrique Perez Villanueva\n");
        printf("\n");
        printf("Objetivo: Ordenar las piezas de forma de arcoiris, es decir blanco, rosa,\n");
        printf("rojo, naranja, amarillo, verde pasto, verde, verde turquesa, azul cielo, azul\n");
        printf("azul rey, purpura, magenta, morado y negro. \n");
        printf("\n");
        printf("r = Resetear cámara y posiciones de bloques.\n");
        printf("w = Rota hacia arriba en Y\n");
        printf("s = Rota hacia abajo en Y\n");
        printf("a = Rota hacia izquierda en X\n");
        printf("d = Rota hacia derecha en X\n");
        printf("z = Rota hacia atras en Z\n");
        printf("x = Rota hacia adelante en Z\n");
        printf("u = Revuelve el puzzle de una forma predeterminada. \n");
        printf("Flecha Derecha = Trata de mover la pieza vacia con un movimiento derecho \n");
        printf("Flecha Izquierda = Trata de mover la pieza vacia con un movimiento izquierda \n");
        printf("Flecha Arriba = Trata de mover la pieza vacia con un movimiento hacia arriba \n");
        printf("Flecha Abajo = Trata de mover la pieza vacia con un movimiento hacia abajo \n");
        printf("v = Muestra las piezas como de Solidas o Cristal (Quita/Añade GlColorMaterial). \n");
        printf("\n");
		glutInit(&argc, argv);			//Inicializamos freeglut
		myInit("Puzzle del 15");	//Llamamos nuestra función
		//Le pasamos las funciones a freeglut
        mySetLight();
		glutKeyboardFunc(myKeyboard);
        glutSpecialFunc(moverPieza);
		glutDisplayFunc(myDisplay);		//Se llama cada vez que se llama glutPostRedisplay();
		glutReshapeFunc(myReshape);		//Se llama cada vez que se cambia el tamaño de la pantalla.
		glutMainLoop();					//MainLoop.
		return 0;
}
