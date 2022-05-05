#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<math.h>
using namespace std;

#define CHARS_ECUACION 100
#define ANCHO_MIEMBRO 10
#define FINAL NULL
#define POSITIVO 1
#define NEGATIVO -1

typedef struct{
    char signo;
    int numero = 0;
    char identificador[3];
}indice;

typedef struct nodo{
    struct nodo *siguiente;
    char contenido[ANCHO_MIEMBRO];
    char signo;
    indice numero;
}miembro;

typedef struct{
    double x2 = 0;
    double y2 = 0;
    double z2 = 0;
    double xyz = 0;
    double x = 0;
    double xy = 0;
    double y = 0;
    double yz = 0;
    double z = 0;
    double xz = 0; 
    double d = 0;            
}componentes;

char* leerEcuacion(void){

    char *ecuacion;
    ecuacion = (char *)malloc(sizeof(char)*CHARS_ECUACION);
    cout<<"introduzca una ecuacion: \televar a una potencia se escrive: n^p\n\t\t\t\tpor favor no omita signos '+'\n";
    cin>>ecuacion;

    return ecuacion;
}

componentes construirEcuacion(miembro *lista){
    componentes ecuacion;
    double construirNumero(char signo, int indice, miembro *lista);
    bool continuar = true;
    int i;
    char signo, temp, identificador; 
    double numero;
    while(continuar){
        identificador = 0;
        if(lista->contenido[0] == '-') signo = NEGATIVO;
        else signo = POSITIVO;

        for( i = 1 ; lista->contenido[i] != 0 ; i++ ){
            temp = lista->contenido[i];

            if(temp == '.') numero = construirNumero(signo,i,lista);

            if(temp >= 'a' && temp <= 'z'){
                identificador += lista->contenido[i] - 100;
            }if(temp == '^'){
                identificador += lista->contenido[i] - 90;
            }

        }

        switch(identificador){
            case 24:
                ecuacion.x2 += numero; 
                break;
            case 25:
                ecuacion.y2 += numero; 
                break;
            case 26:
                ecuacion.z2 += numero; 
                break;
            case 63:
                ecuacion.xyz += numero;
                break;
            case 20:
                ecuacion.x += numero; 
                break;
            case 41:
                ecuacion.xy += numero; 
                break;
            case 21:
                ecuacion.y += numero; 
                break;
            case 43:
                ecuacion.yz += numero; 
                break;
            case 22:
                ecuacion.z += numero; 
                break;
            case 42:
                ecuacion.xz += numero; 
                break;
            default :
                ecuacion.d += numero;
                break;
        }

        if(lista->siguiente != NULL){
            lista = lista->siguiente;
        }else{
            continuar = false;
        }

    }

    return ecuacion;
}

miembro* separar(char ecuacion[]){
    miembro* crearElemento(miembro **, miembro *, int, char, bool);
    miembro *puntoDeCreacion, *cabeza = NULL;
    char temp;
    bool decimal, lado = 0, continuar = true;
    int j;
    for(int i = 0 ; continuar ; i++){
        temp = ecuacion[i];
        if(temp == '=') lado = 1;
        if(temp == '.') decimal = true;

        if(temp == '+' || temp == '-' || temp == '='){
            puntoDeCreacion = crearElemento(&cabeza,puntoDeCreacion,j,temp,lado);
            decimal = false;
            j=0;
        }

        if( ( (temp >= 'a' && temp <= 'z') || temp == 0) && decimal == false ){
            puntoDeCreacion->contenido[j] = '.';
            puntoDeCreacion->contenido[j+1] = '0';

            decimal = true;
            j+=2;
        }

        puntoDeCreacion->contenido[j] = temp;
        j++;

        if(ecuacion[i] == 0) continuar = false;
    }
    puntoDeCreacion->siguiente = FINAL;
    puntoDeCreacion->contenido[j] = 0;

    return cabeza;
}

void imprimirLista(miembro *lista){
    while(lista->siguiente != NULL){
        cout<<lista->contenido<<endl;
        lista = lista->siguiente;
    }cout<<lista->contenido<<endl;
}

void imprimirEcuacion(componentes ecuacion){
    cout<<endl<<"x2: "<<ecuacion.x2;
    cout<<endl<<"y2: "<<ecuacion.y2;
    cout<<endl<<"z2: "<<ecuacion.z2;
    cout<<endl<<"xyz: "<<ecuacion.xyz;
    cout<<endl<<"x: "<<ecuacion.x;
    cout<<endl<<"xy: "<<ecuacion.xy;
    cout<<endl<<"y: "<<ecuacion.y;
    cout<<endl<<"yz: "<<ecuacion.yz;
    cout<<endl<<"z: "<<ecuacion.z;
    cout<<endl<<"xz: "<<ecuacion.xz;
    cout<<endl<<"d: "<<ecuacion.d<<endl;
}


int main(void){
    char *ecuacionBruta;
    componentes ecuacion;
    miembro *lista;
    system("cls");
    ecuacionBruta = leerEcuacion();
    lista = separar(ecuacionBruta);
    imprimirLista(lista);
    ecuacion = construirEcuacion(lista);
    imprimirEcuacion(ecuacion);
}

miembro* crearElemento(miembro **cabeza, miembro *anterior, int j, char signo, bool lado){
    miembro *nuevo;
    nuevo = (miembro *)malloc(sizeof(miembro));

    if(*cabeza != NULL){
        anterior->contenido[j] = 0;
        anterior->siguiente = nuevo;
    }else{
        *cabeza = nuevo;
    }

    if( (signo == '+' && lado == 0) || (signo == '-' && lado == 1) ){
        nuevo->signo = POSITIVO;
    }else{
        nuevo->signo = NEGATIVO;
    }

    return nuevo;
}

double construirNumero(char signo, int indice, miembro *lista){
    double numero = 0;
    int i,aux;
    for( i = 1 ; (lista->contenido[indice-i] != '-' && lista->contenido[indice-i] != '+') ; i++ ){ 
        numero += (lista->contenido[indice-i] - '0') * pow( 10 , (i-1) ) * signo ;
    }for( i = 1 ; !(( (lista->contenido[indice+i] >= 'a') && (lista->contenido[indice+i] <= 'z')) || lista->contenido[indice+i] == 0) ; i++){
        numero += (double)( (lista->contenido[indice+i] - '0') * pow( 10 , -(i) ) * signo) ; 
    }

    return numero;
}

