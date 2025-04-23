#include <stdio.h>
#include <string.h>
#include <ctype.h>


typedef struct {
    char arr[100];
    int cima;
} Pila;

void iniciar(Pila *p) {
    p->cima = -1;
}

int estaVacia(Pila *p) {
    return p->cima == -1;
}

int estaLlena(Pila *p) {
    return p->cima == 99;
}

void apilar(Pila *p, char c) {
    if (!estaLlena(p)) {
        p->arr[++p->cima] = c;
    }
}

char desapilar(Pila *p) {
    if (!estaVacia(p)) {
        return p->arr[p->cima--];
    }
    return '\0';
}

char verCima(Pila *p) {
    if (!estaVacia(p)) {
        return p->arr[p->cima];
    }
    return '\0';
}

int prioridad(char c) {
    switch (c) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case '^': return 3;
        default: return 0;
    }
}

int esOperador(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

void invertirCadena(char *cadena) {
    int n = strlen(cadena);
    for (int i = 0; i < n / 2; ++i) {
        char temp = cadena[i];
        cadena[i] = cadena[n - i - 1];
        cadena[n - i - 1] = temp;
    }
}

//isalnum detecta letras o números.
void infijaAPosfija(char *infija, char *posfija) {
    Pila p;
    iniciar(&p);
    int j = 0;
    for (int i = 0; infija[i] != '\0'; ++i) {
        char c = infija[i];

        if (isalnum(c)) {
            posfija[j++] = c;
        } else if (c == '(') {
            apilar(&p, c);
        } else if (c == ')') {
            while (!estaVacia(&p) && verCima(&p) != '(') {
                posfija[j++] = desapilar(&p);
            }
            desapilar(&p);
        } else if (esOperador(c)) {
            while (!estaVacia(&p) && prioridad(verCima(&p)) >= prioridad(c)) {
                posfija[j++] = desapilar(&p);
            }
            apilar(&p, c);
        }
    }
    while (!estaVacia(&p)) {
        posfija[j++] = desapilar(&p);
    }
    posfija[j] = '\0';
}

void infijaAPrefija(char *infija, char *prefija) {
    invertirCadena(infija);
    for (int i = 0; infija[i] != '\0'; ++i) {
        if (infija[i] == '(') infija[i] = ')';
        else if (infija[i] == ')') infija[i] = '(';
    }
    infijaAPosfija(infija, prefija);
    invertirCadena(prefija);
}

int main() {
    char infija[100], prefija[100], posfija[100];
    int opcion;

    do {
        printf("***Conversion de Notacion***\n");
        printf("1. Insertar expresion en notacion infija\n");
        printf("2. Mostrar en notacion prefija\n");
        printf("3. Mostrar en notacion posfija\n");
        printf("4. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1:
                printf("Ingrese la expresion infija: ");
                fgets(infija, 100, stdin);
                infija[strcspn(infija, "\n")] = '\0';
                break;
            case 2:
                infijaAPrefija(infija, prefija);
                printf("Expresion prefija: %s\n", prefija);
                break;
            case 3:
                infijaAPosfija(infija, posfija);
                printf("Expresion posfija: %s\n", posfija);
                break;
            case 4:
                printf("Saliendo del programa\n");
                break;
            default:
                printf("Opcion no valida.\n");
        }
    } while (opcion != 4);

    return 0;
}