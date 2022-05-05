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
    int numerador = 0;
    unsigned int denominador = 0;
}Numero;
typedef struct{
    Numero x2 ;
    Numero y2 ;
    Numero z2 ;
    Numero xyz ;
    Numero x ;
    Numero xy ;
    Numero y ;
    Numero yz ;
    Numero z ;
    Numero xz ; 
    Numero d ;            
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

    Numero construirNumero(char, char, char, miembro *);
    bool continuar = true, fraccion, encontrado;
    int i;
    char signo, temp, identificador, iNumerador, iDenominador; 
    Numero numero;
    while(continuar){
        identificador = 0;
        fraccion = false;
        encontrado = false;
        iDenominador = -1;
        if(lista->contenido[0] == '-') signo = NEGATIVO;
        else signo = POSITIVO;

        //este bucle carga el valor del numero y obtiene el identificador del miembro correspondiente
        for( i = 1 ; lista->contenido[i] != 0 ; i++ ){
            temp = lista->contenido[i];

            if(temp == '/'){
                fraccion = true;
                iNumerador = i;
            }
            if( ( (temp >= 'a' && temp <= 'z') || temp == 0) && fraccion == true){
                iDenominador = i;
            }
            if(encontrado == false){
                iNumerador = i;
                encontrado = true;
            } 
            numero = construirNumero(signo, iNumerador, iDenominador, lista);

            if(temp >= 'a' && temp <= 'z'){
                identificador += lista->contenido[i] - 100;
            }if(temp == '^'){
                identificador += lista->contenido[i] - 90;
            }

        }

        //carga el numero construido en su lugar correspondiente de la ecuacion
        switch(identificador){
            case 24:
                ecuacion.x2.numerador += numero.numerador;
                ecuacion.x2.denominador += numero.denominador; 
                break;
            case 25:
                ecuacion.y2.numerador += numero.numerador;
                ecuacion.y2.denominador += numero.denominador; 
                break;
            case 26:
                ecuacion.z2.numerador += numero.numerador;
                ecuacion.z2.denominador += numero.denominador; 
                break;
            case 63:
                ecuacion.xyz.numerador += numero.numerador;
                ecuacion.xyz.denominador += numero.denominador;
                break;
            case 20:
                ecuacion.x.numerador += numero.numerador;
                ecuacion.x.denominador += numero.denominador; 
                break;
            case 41:
                ecuacion.xy.numerador += numero.numerador;
                ecuacion.xy.denominador += numero.denominador; 
                break;
            case 21:
                ecuacion.y.numerador += numero.numerador;
                ecuacion.y.denominador += numero.denominador; 
                break;
            case 43:
                ecuacion.yz.numerador += numero.numerador; 
                ecuacion.yz.denominador += numero.denominador;
                break;
            case 22:
                ecuacion.z.numerador += numero.numerador; 
                ecuacion.z.denominador += numero.denominador;
                break;
            case 42:
                ecuacion.xz.numerador += numero.numerador; 
                ecuacion.xz.denominador += numero.denominador;
                break;
            default :
                ecuacion.d.numerador += numero.numerador;
                ecuacion.d.denominador += numero.denominador;
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
    bool lado = 0, continuar = true;
    int j;
    for(int i = 0 ; continuar ; i++){
        temp = ecuacion[i];
        if(temp == '=') lado = 1;

        if(temp == '+' || temp == '-' || temp == '='){
            puntoDeCreacion = crearElemento(&cabeza,puntoDeCreacion,j,temp,lado);
            j=0;
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
    cout<<endl<<"x2: "<<ecuacion.x2.numerador;
    if(ecuacion.x2.denominador != 0) cout<<"\\"<<ecuacion.x2.denominador;

    cout<<endl<<"y2: "<<ecuacion.y2.numerador;
    if(ecuacion.y2.denominador != 0) cout<<"\\"<<ecuacion.y2.denominador;

    cout<<endl<<"z2: "<<ecuacion.z2.numerador;
    if(ecuacion.z2.denominador != 0) cout<<"\\"<<ecuacion.z2.denominador;

    cout<<endl<<"xyz: "<<ecuacion.xyz.numerador;
    if(ecuacion.xyz.denominador != 0) cout<<"\\"<<ecuacion.xyz.denominador;

    cout<<endl<<"x: "<<ecuacion.x.numerador;
    if(ecuacion.x.denominador != 0) cout<<"\\"<<ecuacion.x.denominador;

    cout<<endl<<"xy: "<<ecuacion.xy.numerador;
    if(ecuacion.xy.denominador != 0) cout<<"\\"<<ecuacion.xy.denominador;

    cout<<endl<<"y: "<<ecuacion.y.numerador;
    if(ecuacion.y.denominador != 0) cout<<"\\"<<ecuacion.y.denominador;

    cout<<endl<<"yz: "<<ecuacion.yz.numerador;
    if(ecuacion.yz.denominador != 0) cout<<"\\"<<ecuacion.yz.denominador;

    cout<<endl<<"z: "<<ecuacion.z.numerador;
    if(ecuacion.z.denominador != 0) cout<<"\\"<<ecuacion.z.denominador;

    cout<<endl<<"xz: "<<ecuacion.xz.numerador;
    if(ecuacion.xz.denominador != 0) cout<<"\\"<<ecuacion.xz.denominador;

    cout<<endl<<"d: "<<ecuacion.d.numerador;
    if(ecuacion.d.denominador != 0) cout<<"\\"<<ecuacion.d.denominador<<endl;
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

Numero construirNumero(char signo, char iNumerador, char iDenominador, miembro *lista){
    Numero numero;
    int i;
    for( i = 1 ; (lista->contenido[iNumerador-i] != '-' && lista->contenido[iNumerador-i] != '+') ; i++ ){ 
        numero.numerador += (lista->contenido[iNumerador-i] - '0') * pow( 10 , (i-1) ) * signo ;
    }
    if(iDenominador != -1){
        for( i = 1 ; lista->contenido[iDenominador-i] != '/' ; i++ ){ 
            numero.denominador += (lista->contenido[iDenominador-i] - '0') * pow( 10 , (i-1) );
        }
    }

    return numero;
}

