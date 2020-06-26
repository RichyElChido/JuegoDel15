//Funciones que refieren a las piezas movibles.

#include <stdio.h>		//Incluimos entrada/salida estandar
#include <GL/glut.h>	//freeglut
#include <unistd.h>
#include <cstdlib>
#include <vector>

int vacio;//Que bloque esta vacio actualmente
int VecinosVacio[4];// Nos dice quien son los vecinos del espacio vacio.
int cuadrantes[16];
//Para controlar los cuadrantes, las llaves son las posiciones del cuadrante
//Y su contenido es el color del que colorearemos.

// Estructura para los vèrtices
struct punto{
  float x, y, z;
  punto(float x1, float y1, float z1) : x(x1), y(y1), z(z1) {};
};

//Estructuro que representa cada bloque, se usan 8 coordenadas.
//Cuadrado Interior
//esd= Esquina Superior Derecha, esi= Esquina Superior Izquierda
//eid= Esquina Interior Derecha, eii= Esquina Interior Izquierda
//Bordes del cuadrado
//bsd= Borde Superior Derecha, bsi= Borde Superior Izquierda
//bid= Borde Interior Derecha, bii= Borde Interior Izquierda
struct bloque{
    punto *esd, *esi, *eii, *eid, *bsd, *bsi, *bii, *bed;
    int id;

    bloque(punto* a, punto* b, punto* c, punto *d, punto *e, punto *f ,punto *g, punto *h,int n){
        esd=a; esi=b; eii=c; eid=d; bsd=e; bsi=f; bii=g; bed=h; id=n;
    };
};

//------------------------------------------------
bloque* Piezas[16];//Guarda los datos de los bloques.
//-----------------------------------------------


// Funcion que calcula las normales
//Genera nuevas coordenadas x,y,z apartir de operaciones entre esas.
punto* calcNormals(punto *v1, punto *v2, punto *v3){
    float xv1 = v1->x;
    float yv1= v1->y;
    float zv1 = v1->z;
    float xv2 = v2->x;
    float yv2 = v2->y;
    float zv2 = v2->z;
    float xv3 = v3->x;
    float yv3 = v3->y;
    float zv3 = v3->z;
    float v2x_v1x = xv2 - xv1;
    float v2y_v1y = yv2 - yv1;
    float v2z_v1z = zv2 - zv1;
    float v3x_v1x = xv3 - xv1;
    float v3y_v1y = yv3 - yv1;
    float v3z_v1z = zv3 - zv1;
    float i = v2y_v1y*v3z_v1z - v3y_v1y*v2z_v1z;
    float j = v3x_v1x*v2z_v1z - v2x_v1x*v3z_v1z;
    float k = v2x_v1x*v3y_v1y - v3x_v1x*v2y_v1y;
    float r = sqrt(i*i + j*j + k*k);
    i = i/r;
    j = j/r;
    k = k/r;    
    return new punto(i, j, k);
}

void setDefaultCoords(){//Al reiniciar y al iniciar el juego, se settean los valores default del juego.

    //Pieza Blanca
    punto* a=new punto(-1.9, 1.9, 0);
    punto* b=new punto(-1.1, 1.9, 0);
    punto* c=new punto(-1.1, 1.1, 0);
    punto* d=new punto(-1.9, 1.1, 0);
    punto* e=new punto(-2, 2, -0.1);
    punto* f=new punto(-1, 2, -0.1);
    punto* g=new punto(-1, 1, -0.1);
    punto* h=new punto(-2, 1, -0.1);
    
    Piezas[0]=new bloque(a,b,c,d,e,f,g,h,0);

    //Pieza Rosa
    a=new punto(-0.9, 1.9, 0);
    b=new punto(-0.1, 1.9, 0);
    c=new punto(-0.1, 1.1, 0);
    d=new punto(-0.9, 1.1, 0);
    e=new punto(-1, 2, -0.1);
    f=new punto(-0, 2, -0.1);
    g=new punto(-0, 1, -0.1);
    h=new punto(-1, 1, -0.1);
    
    Piezas[1]=new bloque(a,b,c,d,e,f,g,h,1);


    //Pieza Roja
    a=new punto(0.1, 1.9, 0);
    b=new punto(0.9, 1.9, 0);
    c=new punto(0.9, 1.1, 0);
    d=new punto(0.1, 1.1, 0);
    e=new punto(0, 2, -0.1);
    f=new punto(1, 2, -0.1);
    g=new punto(1, 1, -0.1);
    h=new punto(0, 1, -0.1);
    
    Piezas[2]=new bloque(a,b,c,d,e,f,g,h,2);


    //Pieza Naraja
    a=new punto(1.1, 1.9, 0);
    b=new punto(1.9, 1.9, 0);
    c=new punto(1.9, 1.1, 0);
    d=new punto(1.1, 1.1, 0);
    e=new punto(1, 2, -0.1);
    f=new punto(2, 2, -0.1);
    g=new punto(2, 1, -0.1);
    h=new punto(1, 1, -0.1);
    
    Piezas[3]=new bloque(a,b,c,d,e,f,g,h,3);

    //Pieza Amarilla
    a=new punto(-1.9, 0.9, 0);
    b=new punto(-1.1, 0.9, 0);
    c=new punto(-1.1, 0.1, 0);
    d=new punto(-1.9, 0.1, 0);
    e=new punto(-2, 1, -0.1);
    f=new punto(-1, 1, -0.1);
    g=new punto(-1, 0, -0.1);
    h=new punto(-2, 0, -0.1);
    
    Piezas[4]=new bloque(a,b,c,d,e,f,g,h,4);

    //Pieza Verde Pasto
    a=new punto(-0.9, 0.9, 0);
    b=new punto(-0.1, 0.9, 0);
    c=new punto(-0.1, 0.1, 0);
    d=new punto(-0.9, 0.1, 0);
    e=new punto(-1, 1, -0.1);
    f=new punto(-0, 1, -0.1);
    g=new punto(-0, 0, -0.1);
    h=new punto(-1, 0, -0.1);
    
    Piezas[5]=new bloque(a,b,c,d,e,f,g,h,5);


    //Pieza Verde
    a=new punto(0.1, 0.9, 0);
    b=new punto(0.9, 0.9, 0);
    c=new punto(0.9, 0.1, 0);
    d=new punto(0.1, 0.1, 0);
    e=new punto(0, 1, -0.1);
    f=new punto(1, 1, -0.1);
    g=new punto(1, 0, -0.1);
    h=new punto(0, 0, -0.1);
    
    Piezas[6]=new bloque(a,b,c,d,e,f,g,h,6);


    //Pieza Turquesa
    a=new punto(1.1, 0.9, 0);
    b=new punto(1.9, 0.9, 0);
    c=new punto(1.9, 0.1, 0);
    d=new punto(1.1, 0.1, 0);
    e=new punto(1, 1, -0.1);
    f=new punto(2, 1, -0.1);
    g=new punto(2, 0, -0.1);
    h=new punto(1, 0, -0.1);
    
    Piezas[7]=new bloque(a,b,c,d,e,f,g,h,7);

    //Pieza Azul
    a=new punto(-1.9, -0.1, 0);
    b=new punto(-1.1, -0.1, 0);
    c=new punto(-1.1, -0.9, 0);
    d=new punto(-1.9, -0.9, 0);
    e=new punto(-2, -0, -0.1);
    f=new punto(-1, -0, -0.1);
    g=new punto(-1, -1, -0.1);
    h=new punto(-2, -1, -0.1);
    
    Piezas[8]=new bloque(a,b,c,d,e,f,g,h,8);

    //Pieza Azul Rey
    a=new punto(-0.9, -0.1, 0);
    b=new punto(-0.1, -0.1, 0);
    c=new punto(-0.1, -0.9, 0);
    d=new punto(-0.9, -0.9, 0);
    e=new punto(-1, -0, -0.1);
    f=new punto(-0, -0, -0.1);
    g=new punto(-0, -1, -0.1);
    h=new punto(-1, -1, -0.1);
    
    Piezas[9]=new bloque(a,b,c,d,e,f,g,h,9);


    //Pieza Azul Oscura
    a=new punto(0.1, -0.1, 0);
    b=new punto(0.9, -0.1, 0);
    c=new punto(0.9, -0.9, 0);
    d=new punto(0.1, -0.9, 0);
    e=new punto(0, -0, -0.1);
    f=new punto(1, -0, -0.1);
    g=new punto(1, -1, -0.1);
    h=new punto(0, -1, -0.1);
    
    Piezas[10]=new bloque(a,b,c,d,e,f,g,h,10);


    //Pieza Morada
    a=new punto(1.1, -0.1, 0);
    b=new punto(1.9, -0.1, 0);
    c=new punto(1.9, -0.9, 0);
    d=new punto(1.1, -0.9, 0);
    e=new punto(1, -0, -0.1);
    f=new punto(2, -0, -0.1);
    g=new punto(2, -1, -0.1);
    h=new punto(1, -1, -0.1);
   
    Piezas[11]=new bloque(a,b,c,d,e,f,g,h,11);

    //Pieza Violeta
    a=new punto(-1.9, -1.1, 0);
    b=new punto(-1.1, -1.1, 0);
    c=new punto(-1.1, -1.9, 0);
    d=new punto(-1.9, -1.9, 0);
    e=new punto(-2, -1, -0.1);
    f=new punto(-1, -1, -0.1);
    g=new punto(-1, -2, -0.1);
    h=new punto(-2, -2, -0.1);
    
    Piezas[12]=new bloque(a,b,c,d,e,f,g,h,12);

    //Pieza Vino
    a=new punto(-0.9, -1.1, 0);
    b=new punto(-0.1, -1.1, 0);
    c=new punto(-0.1, -1.9, 0);
    d=new punto(-0.9, -1.9, 0);
    e=new punto(-1, -1, -0.1);
    f=new punto(-0, -1, -0.1);
    g=new punto(-0, -2, -0.1);
    h=new punto(-1, -2, -0.1);
    
    Piezas[13]=new bloque(a,b,c,d,e,f,g,h,13);


    //Pieza Negra
    a=new punto(0.1, -1.1, 0);
    b=new punto(0.9, -1.1, 0);
    c=new punto(0.9, -1.9, 0);
    d=new punto(0.1, -1.9, 0);
    e=new punto(0, -1, -0.1);
    f=new punto(1, -1, -0.1);
    g=new punto(1, -2, -0.1);
    h=new punto(0, -2, -0.1);
    
    Piezas[14]=new bloque(a,b,c,d,e,f,g,h,14);

    //Pieza Faltante, necesitamos saber su ubicacion para moverla.
    a=new punto(1.1, -1.1, 0);
    b=new punto(1.9, -1.1, 0);
    c=new punto(1.9, -1.9, 0);
    d=new punto(1.1, -1.9, 0);
    e=new punto(1, -1, -0.1);
    f=new punto(2, -1, -0.1);
    g=new punto(2, -2, -0.1);
    h=new punto(1, -2, -0.1);
    
    Piezas[15]=new bloque(a,b,c,d,e,f,g,h,15);//El id 15 siempre es el vacio.
    vacio=15;//Actualizamos la pieza vacia.
    for(int i=0; i< 16;i++){
        cuadrantes[i]=i;//Rellenamos el tablero actual
    }

//añadimos los vertices adyacentes al vacio al stack.
    VecinosVacio[0]=14;//Izquierda
    VecinosVacio[1]=-1;//Derecha
    VecinosVacio[2]=11;//Arriba
    VecinosVacio[3]=-1;//Abajo
    //Siempre estan en el orden: 0=Izquierda 1=Derecha 2=Arriba 3=Abajo
    //-1 significa que no tienen vecino disponible.
}

void selectColor(int n){//Seleccionamos el color y textura. Recordemos que el Blend apaga el GL_Color.
    float ambient2[]  = {1.0f,1.0f,1.0f,0.75f};
    float diffuse2[]  = {1.0f,1.0f,1.0f,0.75f};
    float specular2[] = {1.0f,1.0f,1.0f,0.75f};	
    switch(n){
        case 0: //Blanco
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient2);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  diffuse2);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular2);
	        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS,85);
            glColor3f(1,1,1);
            break;
        case 1: //Rosa
            ambient2[0]=1.0f;ambient2[1]=0.5f;ambient2[2]=0.5f;
            diffuse2[0]=1.0f;ambient2[1]=0.5f;ambient2[2]=0.5f;
            specular2[0]=1.0f;ambient2[1]=0.5f;ambient2[2]=0.5f;
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient2);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  diffuse2);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular2);
	        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 85);
            glColor3f(1,0.5,0.5);
            break;
        case 2:  //Rojo
            ambient2[0]=1.0f;ambient2[1]=0.0f;ambient2[2]=0.0f;
            diffuse2[0]=1.0f;ambient2[1]=0.0f;ambient2[2]=0.0f;
            specular2[0]=1.0f;ambient2[1]=0.0f;ambient2[2]=0.0f;
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient2);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  diffuse2);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular2);
	        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 85);
            glColor3f(1,0.0,0.0);
            break;
        case 3:
            ambient2[0]=1.0f;ambient2[1]=0.5f;ambient2[2]=0.0f;
            diffuse2[0]=1.0f;ambient2[1]=0.5f;ambient2[2]=0.0f;
            specular2[0]=1.0f;ambient2[1]=0.5f;ambient2[2]=0.0f;
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient2);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  diffuse2);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular2);
	        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 85);
            glColor3f(1,0.5,0.0);
            break;
        case 4:
            ambient2[0]=1.0f;ambient2[1]=1.0f;ambient2[2]=0.0f;
            diffuse2[0]=1.0f;ambient2[1]=1.0f;ambient2[2]=0.0f;
            specular2[0]=1.0f;ambient2[1]=1.0f;ambient2[2]=0.0f;
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient2);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  diffuse2);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular2);
	        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 85);
            glColor3f(1.0,1.0,0.0);
            break;
        case 5: 
            ambient2[0]=0.5f;ambient2[1]=1.0f;ambient2[2]=0.0f;
            diffuse2[0]=0.5f;ambient2[1]=1.0f;ambient2[2]=0.0f;
            specular2[0]=0.5f;ambient2[1]=1.0f;ambient2[2]=0.0f;
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient2);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  diffuse2);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular2);
	        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 85);
            glColor3f(0.5,1.0,0.0);
            break;
        case 6:
            ambient2[0]=0.0f;ambient2[1]=1.0f;ambient2[2]=0.0f;
            diffuse2[0]=0.0f;ambient2[1]=1.0f;ambient2[2]=0.0f;
            specular2[0]=0.0f;ambient2[1]=1.0f;ambient2[2]=0.0f;
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient2);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  diffuse2);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular2);
	        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 85);
            glColor3f(0.0,1.0,0.0);
            break;
        case 7:
            ambient2[0]=0.0f;ambient2[1]=1.0f;ambient2[2]=0.5f;
            diffuse2[0]=0.0f;ambient2[1]=1.0f;ambient2[2]=0.5f;
            specular2[0]=0.0f;ambient2[1]=1.0f;ambient2[2]=0.5f;
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient2);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  diffuse2);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular2);
	        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 85);
            glColor3f(0.0,1.0,0.5);
            break;
        case 8: 
            ambient2[0]=0.0f;ambient2[1]=1.0f;ambient2[2]=1.0f;
            diffuse2[0]=0.0f;ambient2[1]=1.0f;ambient2[2]=1.0f;
            specular2[0]=0.0f;ambient2[1]=1.0f;ambient2[2]=1.0f;
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient2);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  diffuse2);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular2);
	        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 85);
            glColor3f(0.0,1.0,1.0);
            break;
        case 9:
            ambient2[0]=0.0f;ambient2[1]=0.5f;ambient2[2]=1.0f;
            diffuse2[0]=0.0f;ambient2[1]=0.5f;ambient2[2]=1.0f;
            specular2[0]=0.0f;ambient2[1]=0.5f;ambient2[2]=1.0f;
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient2);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  diffuse2);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular2);
	        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 85);
            glColor3f(0.0,0.5,1.0);
            break;
        case 10:
            ambient2[0]=0.0f;ambient2[1]=0.0f;ambient2[2]=1.0f;
            diffuse2[0]=0.0f;ambient2[1]=0.0f;ambient2[2]=1.0f;
            specular2[0]=0.0f;ambient2[1]=0.0f;ambient2[2]=1.0f;
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient2);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  diffuse2);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular2);
	        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 85);
            glColor3f(0.0,0.0,1.0);
            break;
        case 11: 
            ambient2[0]=0.5f;ambient2[1]=0.0f;ambient2[2]=1.0f;
            diffuse2[0]=0.5f;ambient2[1]=0.0f;ambient2[2]=1.0f;
            specular2[0]=0.5f;ambient2[1]=0.0f;ambient2[2]=1.0f;
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient2);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  diffuse2);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular2);
	        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 85);
            glColor3f(0.5,0.0,1.0);
            break;
        case 12:
            ambient2[0]=1.0f;ambient2[1]=0.0f;ambient2[2]=1.0f;
            diffuse2[0]=1.0f;ambient2[1]=0.0f;ambient2[2]=1.0f;
            specular2[0]=1.0f;ambient2[1]=0.0f;ambient2[2]=1.0f;
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient2);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  diffuse2);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular2);
	        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 85);
            glColor3f(1.0,0.0,1.0);
            break;
        case 13:
            ambient2[0]=0.5f;ambient2[1]=0.0f;ambient2[2]=0.5f;
            diffuse2[0]=0.5f;ambient2[1]=0.0f;ambient2[2]=0.5f;
            specular2[0]=0.5f;ambient2[1]=0.0f;ambient2[2]=0.5f;
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient2);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  diffuse2);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular2);
	        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 85);
            glColor3f(0.5,0.0,0.5);
            break;
        case 14: 
            ambient2[0]=0.001f;ambient2[1]=0.001f;ambient2[2]=0.001f;
            diffuse2[0]=0.001f;ambient2[1]=0.001f;ambient2[2]=0.001f;
            specular2[0]=0.001f;ambient2[1]=0.001f;ambient2[2]=0.001f;
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient2);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  diffuse2);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular2);
	        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 85);
            glColor3f(0.1,0.1,0.1);
            break;
    }
}

void autoRevolver(){//Revuelve de una forma definida las piezas.
    for(int i=0; i< 16;i++){
        Piezas[i] -> id =i;//Reinciamos el juego.
    }
        int newVacio= 14;
        int tmp= Piezas[newVacio]-> id;
        Piezas[newVacio]-> id = Piezas[vacio] -> id;
        Piezas[vacio] -> id = tmp;
        //Se ve feo, pero revolvemos piezas de forma facil.
        int tmp2= cuadrantes[newVacio];
        cuadrantes[newVacio]=cuadrantes[vacio];
        cuadrantes[vacio]=tmp2;
        vacio=newVacio;
        newVacio= 10;
        tmp= Piezas[newVacio]-> id;
        Piezas[newVacio]-> id = Piezas[vacio] -> id;
        Piezas[vacio] -> id = tmp;
        tmp2= cuadrantes[newVacio];
        cuadrantes[newVacio]=cuadrantes[vacio];
        cuadrantes[vacio]=tmp2;
        vacio=newVacio;
        newVacio= 6;
        tmp= Piezas[newVacio]-> id;
        Piezas[newVacio]-> id = Piezas[vacio] -> id;
        Piezas[vacio] -> id = tmp;
        tmp2= cuadrantes[newVacio];
        cuadrantes[newVacio]=cuadrantes[vacio];
        cuadrantes[vacio]=tmp2;
        vacio=newVacio;
        newVacio= 7;
        tmp= Piezas[newVacio]-> id;
        Piezas[newVacio]-> id = Piezas[vacio] -> id;
        Piezas[vacio] -> id = tmp;
        tmp2= cuadrantes[newVacio];
        cuadrantes[newVacio]=cuadrantes[vacio];
        cuadrantes[vacio]=tmp2;
        vacio=newVacio;
        newVacio= 3;
        tmp= Piezas[newVacio]-> id;
        Piezas[newVacio]-> id = Piezas[vacio] -> id;
        Piezas[vacio] -> id = tmp;
        tmp2= cuadrantes[newVacio];
        cuadrantes[newVacio]=cuadrantes[vacio];
        cuadrantes[vacio]=tmp2;
        vacio=newVacio;
        VecinosVacio[0]=2;VecinosVacio[1]=-1;VecinosVacio[2]=-1;VecinosVacio[3]=7;
        //Y actualizamos los vecinos vacios.
}

void drawPiezas(){//Dibuja los bloques para jugar.

	glBegin(GL_QUADS);		//comenzamos a generar la geometria.
        for(int w=0; w < 16; ++w){//Hacemos esto 15 veces.
            int j=cuadrantes[w];//Dibuja en el cuadrante, j es el cuadrante donde dibujaremos.
            int i=Piezas[j]-> id;//El i es el numero de color de las piezas.
            if(i !=15){//El id 15 es la pieza vacia.      
                selectColor(i);
                //Superficie de arriba.
                punto* normal= calcNormals(Piezas[j]->bsd,Piezas[j]->esd,Piezas[j]->eid );
                glNormal3f(normal-> x, normal -> y, normal ->z);

                glVertex3f(Piezas[j]->esd->x, Piezas[j]->esd->y, Piezas[j]->esd->z );
                glVertex3f(Piezas[j]->esi->x, Piezas[j]->esi->y, Piezas[j]->esi->z );
                glVertex3f(Piezas[j]->eii->x, Piezas[j]->eii->y, Piezas[j]->eii->z );
                glVertex3f(Piezas[j]->eid->x, Piezas[j]->eid->y, Piezas[j]->eid->z );

                //Dibujamos el borde Izquierdo
                normal= calcNormals(Piezas[j]->bsd,Piezas[j]->esd,Piezas[j]->eid );
                glNormal3f(normal-> x, normal -> y, normal ->z);

                glVertex3f(Piezas[j]->bsd->x, Piezas[j]->bsd->y, Piezas[j]->bsd->z );
                glVertex3f(Piezas[j]->esd->x, Piezas[j]->esd->y, Piezas[j]->esd->z );
                glVertex3f(Piezas[j]->eid->x, Piezas[j]->eid->y, Piezas[j]->eid->z );
                glVertex3f(Piezas[j]->bed->x, Piezas[j]->bed->y, Piezas[j]->bed->z );

                //Dibujamos el borde Norte
                normal= calcNormals(Piezas[j]->bsd,Piezas[j]->bsi,Piezas[j]->esi );
                glNormal3f(normal-> x, normal -> y, normal ->z);

                glVertex3f(Piezas[j]->bsd->x, Piezas[j]->bsd->y, Piezas[j]->bsd->z );
                glVertex3f(Piezas[j]->bsi->x, Piezas[j]->bsi->y, Piezas[j]->bsi->z );
                glVertex3f(Piezas[j]->esi->x, Piezas[j]->esi->y, Piezas[j]->esi->z );
                glVertex3f(Piezas[j]->esd->x, Piezas[j]->esd->y, Piezas[j]->esd->z );

                //dibujamos el borde Derecho
                normal = calcNormals(Piezas[j]->esi,Piezas[j]->bsi,Piezas[j]->bii );
                glNormal3f(normal-> x, normal -> y, normal ->z);

                glVertex3f(Piezas[j]->esi->x, Piezas[j]->esi->y, Piezas[j]->esi->z );
                glVertex3f(Piezas[j]->bsi->x, Piezas[j]->bsi->y, Piezas[j]->bsi->z );
                glVertex3f(Piezas[j]->bii->x, Piezas[j]->bii->y, Piezas[j]->bii->z );
                glVertex3f(Piezas[j]->eii->x, Piezas[j]->eii->y, Piezas[j]->eii->z );

                //Dibujamos el borde sur
                normal= calcNormals(Piezas[j]->eid,Piezas[j]->eii,Piezas[j]->bii );
                glNormal3f(normal-> x, normal -> y, normal ->z);

                glVertex3f(Piezas[j]->eid->x, Piezas[j]->eid->y, Piezas[j]->eid->z );
                glVertex3f(Piezas[j]->eii->x, Piezas[j]->eii->y, Piezas[j]->eii->z );
                glVertex3f(Piezas[j]->bii->x, Piezas[j]->bii->y, Piezas[j]->bii->z );
                glVertex3f(Piezas[j]->bed->x, Piezas[j]->bed->y, Piezas[j]->bed->z );
                
            }
        }
    glEnd();
}

bool checkIfResolve(){//Funcion que revisa si el Puzzle ya se soluciono
    bool iguales=true;//Suponemos que Default y Actual son iguales.
    for(int i=0; i < 16; i++){
        if(cuadrantes[i]!=i){
            iguales=false;//Si uno de estos no es igual, entonces aun no se a encontrado solucion.
        }
    }
    return iguales;
}


//Verifica si se puede realizar el movimiento sugerido y si hay un candidato.
//Si es asi, realiza el movimiento. Funciona usando el principio que la pieza vacia 
//tiene en todo momento al menos 2 vecinos y a lo mas 4.
void intentaMover(int dir){
    if(VecinosVacio[dir]!=-1){
        //Swapeamos las ids del color.
        int newVacio= VecinosVacio[dir];
        int tmp= Piezas[newVacio]-> id;
        Piezas[newVacio]-> id = Piezas[vacio] -> id;
        Piezas[vacio] -> id = tmp;
        //Y sus posiciones en el tablero.
        int tmp2= cuadrantes[newVacio];
        cuadrantes[newVacio]=cuadrantes[vacio];
        cuadrantes[vacio]=tmp2;
        //Una vez cambiado de lugar, actualizamos los datos del nuevo vacio.
        int izq= newVacio -1;//Calculamos cual es el cuadrante vecino por la izquierda...
        int der= newVacio +1;//Derecha
        int arr= newVacio -4;//Arriba
        int aba= newVacio +4;//Y abajo. Recuerda que vemos el arreglo como cuadrantes.

        //Actualizamos los vecinos, si no estan dentro del rango de los cuadrantes, marcamos -1.
        if(izq < 16 && izq > -1){VecinosVacio[0]=izq;} else {VecinosVacio[0]=-1;} 
        if(der < 16 && der > -1){VecinosVacio[1]=der;} else {VecinosVacio[1]=-1;}
        if(arr < 16 && arr > -1){VecinosVacio[2]=arr;} else {VecinosVacio[2]=-1;}
        if(aba < 16 && aba > -1){VecinosVacio[3]=aba;} else {VecinosVacio[3]=-1;}
        //IMPORTANTE, Notemos que no podemos llegar a 11,7,3 por la Izquierda ni
        //Ni a 12,8,4 por la derecha. Por lo que estos movimientos quedan prohibidos.
        if(newVacio==12 && izq==11){VecinosVacio[0]=-1;}
        if(newVacio==8 && izq==7){VecinosVacio[0]=-1;}
        if(newVacio==4 && izq==3){VecinosVacio[0]=-1;}

        if(newVacio==11 && der==12){VecinosVacio[1]=-1;}
        if(newVacio==7 && der==8){VecinosVacio[1]=-1;}
        if(newVacio==3 && der==4){VecinosVacio[1]=-1;}
        vacio=newVacio;//Y actualizamos el vacio actual.
    }
}
