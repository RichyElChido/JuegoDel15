//Funciones que estan relacionadas con la caja de madera.

#include <stdio.h>		//Incluimos entrada/salida estandar
#include <GL/glut.h>	//freeglut
#include <unistd.h>

void drawCaja(){//Dibuja una caja de 4.1 x 4.1, de profundidad 1.
	glBegin(GL_QUADS);		//comenzamos a generar la geometria.
        glColor3f(0.6, 0.3, 0.1);
        //Borde Superior
        glNormal3f(0,0, 1); 
        glVertex3f(-2.1, 2.1, 0.0);
        glVertex3f(2.1, 2.1, 0.0);
        glVertex3f(2.0, 2.0, 0.0);
        glVertex3f(-2.0, 2.0, 0.0);

            //Borde Derecho
        glNormal3f(0,0, 1);
        glVertex3f(2.0, 2.0, 0.0); 
        glVertex3f(2.1, 2.1, 0.0); 
        glVertex3f(2.1, -2.1, 0.0);
        glVertex3f(2.0, -2.0, 0.0);

                //Borde Inferior
        glNormal3f(0,0, -1); 
        glVertex3f(-2.0, -2.0, 0.0); 
        glVertex3f(2.0, -2.0, 0.0);
        glVertex3f(2.1, -2.1, 0.0);  
        glVertex3f(-2.1, -2.1, 0.0);

                //Borde Izquierdo
        glNormal3f(0,0, 1); 
        glVertex3f(-2.1, 2.1, 0.0);
        glVertex3f(-2.1, -2.1, 0.0);
        glVertex3f(-2.0, -2.0, 0.0);  
        glVertex3f(-2.0, 2.0, 0.0);

        glColor3f(0.4, 0.15, 0.01);
        //Lado Interior Superior
        glNormal3f(0, -1, 0); 
        glVertex3f(-2.0, 2.0, 0.0);
        glVertex3f(-2.0, 2.0, -1.0);  
        glVertex3f(2.0, 2.0, -1.0);
        glVertex3f(2.0, 2.0, 0.0);

        //Lado Interior Derecho
        glNormal3f(-1, 0, 0); 
        glVertex3f(2.0, 2.0, 0.0);
        glVertex3f(2.0, 2.0, -1.0);  
        glVertex3f(2.0, -2.0, -1.0);
        glVertex3f(2.0, -2.0, 0.0);

        //Lado Interior Izquierdo
        glNormal3f(-1,0, 0); 
        glVertex3f(-2.0, 2.0, 0.0);
        glVertex3f(-2.0, 2.0, -1.0); 
        glVertex3f(-2.0, -2.0, -1.0); 
        glVertex3f(-2.0, -2.0, 0.0);

        //Lado Interior Inferior
        glNormal3f(0, -1, 0); 
        glVertex3f(-2.0, -2.0, 0.0);
        glVertex3f(-2.0, -2.0, -1.0); 
        glVertex3f(2.0, -2.0, -1.0); 
        glVertex3f(2.0, -2.0, 0.0); 

        glColor3f(0.6, 0.3, 0.1);

        //Lado Exterior Superior
        glNormal3f(0, -1, 0); 
        glVertex3f(-2.1, 2.1, 0.0);
        glVertex3f(-2.1, 2.1, -1.0);
        glVertex3f(2.1, 2.1, -1.0);
        glVertex3f(2.1, 2.1, 0.0); 

        //Lado Exterior Derecho
        glNormal3f(-1,0, 0); 
        glVertex3f(2.1, 2.1, 0.0);
        glVertex3f(2.1, 2.1, -1.0); 
        glVertex3f(2.1, -2.1, -1.0); 
        glVertex3f(2.1, -2.1, 0.0);

        //Lado Exterior Izquierdo
        glNormal3f(-1,0, 0); 
        glVertex3f(-2.1, 2.1, 0.0);
        glVertex3f(-2.1, 2.1, -1.0);
        glVertex3f(-2.1, -2.1, -1.0);  
        glVertex3f(-2.1, -2.1, 0.0); 

        //Lado Exterior Inferior
        glNormal3f(-1,0, 0); 
        glVertex3f(-2.1, -2.1, 0.0);
        glVertex3f(-2.1, -2.1, -1.0);  
        glVertex3f(2.1, -2.1, -1.0);
        glVertex3f(2.1, -2.1, 0.0);

        //Parte de abajo.
        glNormal3f(0,0, 1); 
        glVertex3f(-2.1, 2.1, -1.0);
        glVertex3f(-2.1, -2.1, -1.0);
        glVertex3f(2.1, -2.1, -1.0);
        glVertex3f(2.1, 2.1, -1.0);

        
    glEnd(); //Terminamos de dibujar.

} 
