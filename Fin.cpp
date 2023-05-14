#include <iostream>
#include <string>
using namespace std;

// Estructura Ab
struct Nodo {
string nombre;
int numero;
float* tiempos;
int numTiempos;
int height;
Nodo* izquierdo;
Nodo* derecho;
};

//Crear un nuevo nodo
Nodo* crearNodo(string nombre, int numero, float tiempo) {
Nodo* nodo = new Nodo();
nodo->nombre = nombre;
nodo->numero = numero;
nodo->tiempos = new float[1];
nodo->tiempos[0] = tiempo;
nodo->numTiempos = 1;
nodo->height = 1;
nodo->izquierdo = NULL;
nodo->derecho = NULL;
return nodo;
}

//obtener la altura de un nodo
int getHeight(Nodo* nodo) {
if (nodo == NULL) {
return 0;
}
return nodo->height;
}

//Factor de balance de un nodo, profe desde aqui hasta abajo todo lo relacionado con balanceo lo saque lo saque de youtube ome, es que aja estaba complicado esta parte.
int getBalanceFactor(Nodo* nodo) {
if (nodo == NULL) {
return 0;
}
return getHeight(nodo->izquierdo) - getHeight(nodo->derecho);
}

//realizar una rotación hacia la derecha
Nodo* rotacionDerecha(Nodo* y) {
Nodo* x = y->izquierdo;
Nodo* T2 = x->derecho;

x->derecho = y;
y->izquierdo = T2;

y->height = max(getHeight(y->izquierdo), getHeight(y->derecho)) + 1;
x->height = max(getHeight(x->izquierdo), getHeight(x->derecho)) + 1;

return x;

}


Nodo* rotacionIzquierda(Nodo* x) {
Nodo* y = x->derecho;
Nodo* T2 = y->izquierdo;


y->izquierdo = x;
x->derecho = T2;

x->height = max(getHeight(x->izquierdo), getHeight(x->derecho)) + 1;
y->height = max(getHeight(y->izquierdo), getHeight(y->derecho)) + 1;

return y;

}

// insertar un nodo en el árbol
Nodo* insertarNodo(Nodo* root, string nombre, int numero, float tiempo) {
if (root == NULL) {
return crearNodo(nombre, numero, tiempo);
}
if (numero < root->numero) {
root->izquierdo = insertarNodo(root->izquierdo, nombre, numero, tiempo);
}
else if (numero > root->numero) {
root->derecho = insertarNodo(root->derecho, nombre, numero, tiempo);
}
else {
// Agregar tiempo adicional
root->numTiempos++;
float* temp = new float[root->numTiempos];
for (int i = 0; i < root->numTiempos - 1; i++) {
temp[i] = root->tiempos[i];
}
temp[root->numTiempos - 1] = tiempo;
delete[] root->tiempos;
root->tiempos = temp;
return root;
}

root->height = max(getHeight(root->izquierdo), getHeight(root->derecho)) + 1;

int balanceFactor = getBalanceFactor(root);

// C.izquierda-izquierda
if (balanceFactor > 1 && numero < root->izquierdo->numero) {
    return rotacionDerecha(root);
}

// C. derecha-derecha
if (balanceFactor < -1 && numero > root->derecho->numero) {
    return rotacionIzquierda(root);
}

// C. izquierda-derecha
if (balanceFactor > 1 && numero > root->izquierdo->numero) {
    root->izquierdo = rotacionIzquierda(root->izquierdo);
    return rotacionDerecha(root);
}

// C.derecha-izquierda
if (balanceFactor < -1 && numero < root->derecho->numero) {
    root->derecho = rotacionDerecha(root->derecho);
    return rotacionIzquierda(root);
}

return root;

}

// Función para imprimir el árbol en orden
void imprimirArbol(Nodo* root) {
if (root == NULL) {
return;
}
imprimirArbol(root->izquierdo);
cout << root->nombre << " (" << root->numero << "): ";
for (int i = 0; i < root->numTiempos; i++) {
cout << root->tiempos[i] << " ";
}
cout << endl;
imprimirArbol(root->derecho);
}

// Función para liberar la memoria del árbol
void liberarArbol(Nodo* root) {
if (root == NULL) {
return;
}
liberarArbol(root->izquierdo);
liberarArbol(root->derecho);
delete[] root->tiempos;
delete root;
}

// Esta ahi humilde el menú

int mostrarMenu() {
int opcion;
cout << "BIEMVEMIDO: " << endl;
cout << "1. Registrar atleta" << endl;
cout << "2. Ver atletas registrados" << endl;
cout << "3. Salir" << endl;
cout << "Opcion: ";
cin >> opcion;
return opcion;
}

// principal
int main() {
Nodo* root = NULL;
int opcion = 0;
while (opcion != 3) {
opcion = mostrarMenu();
if (opcion == 1) {
string nombre;
int numero;
float tiempo;
cout << "Nombre: ";
cin >> nombre;
cout << "Numero: ";
cin >> numero;
bool deseaIngresarMasTiempos = true;
while (deseaIngresarMasTiempos) {
cout << "Tiempo: ";
cin >> tiempo;
root = insertarNodo(root, nombre, numero, tiempo);
char respuesta;
cout << "Desea ingresar otro tiempo? (s/n): ";
cin >> respuesta;
if (respuesta == 'n' || respuesta == 'N') {
deseaIngresarMasTiempos = false;
}
}
}
else if (opcion == 2) {
imprimirArbol(root);
}
}
liberarArbol(root);
return 0;
}