#include<iostream>
#include<fstream>
#include<stdio.h>
#include<string>
#include<stdlib.h>
using namespace std;

//Variables
int opcion = 0;
string producto;

//Creacion del archivo base
ofstream archivo;

//Funciones
void productonuevo();
void buscarproducto();
void actualizarproducto();
void eliminarproducto();
void capturardatos();
void existencias();


int main(){

while (true) { // Bucle infinito
    cout << "************************" << endl;
    cout << "* Control de productos *" << endl;
    cout << "*       Farmacia       *" << endl;
    cout << "************************\n\n" << endl;

do {
cout << "Menu de opciones:" << endl;
    cout << "1) Producto nuevo" << endl;
    cout << "2) Buscar producto" << endl;
    cout << "3) Actualizar producto" << endl;
    cout << "4) Eliminar producto" << endl;
    cout << "5) Capturar datos producto" << endl;
    cout << "6) Ver producto sin existencia" << endl;

cout << "\nSeleccione una opcion: "; cin >> opcion; cout << endl;

if (opcion < 1 || opcion > 6) {
    cout << "\nOpcion no valida\n" << endl;
    cin.ignore();
    system("cls");
    continue;
}

} while (opcion < 1 || opcion > 6);

    switch (opcion) {
        case 1:
            cout << "Producto nuevo" << endl;
            productonuevo();
        break;
        case 2:
            cout << "Buscar producto" << endl;
            buscarproducto();
        break;
        case 3:
            cout << "Actualizar producto" << endl;
            actualizarproducto();
        break;
        case 4:
            cout << "Eliminar producto" << endl;
            eliminarproducto();
        break;
        case 5:
            cout << "Capturar datos producto" << endl;
            capturardatos();
        break;
        case 6:
            cout << "Ver producto sin existencia" << endl;
            existencias();
        break;
        default:
        break;
    }

cout << "\nPresione Enter para continuar..." << endl;
cin.ignore();
system("cls");
}
    return 0;
}


//Funciones
void productonuevo(){
    fstream archivo;

    if (!archivo) {
        cout << "Error: No se pudo abrir el archivo original.\n";
        return;
    }

    archivo.open("productos.txt", ios::app); //Abrimos el archivo para añadir texto

    cout << "Ingrese el producto nuevo: ";
    cin.ignore();
    getline(cin,producto);

    archivo << producto << endl;
    archivo.close();
}

void buscarproducto(){

    ifstream archivo; // Abrir archivo en modo lectura
    archivo.open("productos.txt", ios::in);

    if (!archivo) {
        cout << "Error: No se pudo abrir el archivo.\n";
        return;
    }

    string productoBuscado;
    string linea;
    bool encontrado = false;

    cin.ignore(); 
    cout << "Cual es el producto que desea buscar?: ";
    getline(cin, productoBuscado);

    while (getline(archivo, linea)) { // Leer el codig linea por l�nea
        if (linea == productoBuscado) {
            encontrado = true;
            break;
        }
    }

    archivo.close();

    if (encontrado) {
        cout << "El producto '" << productoBuscado << "' esta registrado en el archivo.\n";
    } else {
        cout << "El producto '" << productoBuscado << "' no se encuentra en el archivo.\n";
    }
}



void actualizarproducto(){

}

void eliminarproducto(){
	ifstream archivoEntrada("productos.txt"); // Archivo original
    ofstream archivoTemporal("productos_temp.txt"); // Archivo temporal para almacenar los datos modificados

    if (!archivoEntrada) {
        cout << "Error: No se pudo abrir el archivo original.\n";
        return;
    }

    if (!archivoTemporal) {
        cout << "Error: No se pudo crear el archivo temporal.\n";
        return;
    }

    string productoAEliminar;
    string linea;
    bool encontrado = false;

    cin.ignore(); // Limpiar el buffer para usar getline
    cout << "Ingrese el nombre del producto que desea eliminar: ";
    getline(cin, productoAEliminar);

    // Leer el archivo l�nea por l�nea y copiar los datos al archivo temporal
    while (getline(archivoEntrada, linea)) {
        if (linea == productoAEliminar) {
            encontrado = true; // Producto encontrado, no se copia al archivo temporal
        } else {
            archivoTemporal << linea << endl; // Copiar las l�neas que no coinciden
        }
    }

    archivoEntrada.close();
    archivoTemporal.close();


    if (encontrado) {
        remove("productos.txt"); // Eliminar el archivo original
        rename("productos_temp.txt", "productos.txt"); // Renombrar el archivo temporal
        cout << "El producto '" << productoAEliminar << "' ha sido eliminado con �xito.\n";
    } else {
        remove("productos_temp.txt"); // Eliminar el archivo temporal si no se uso
        cout << "El producto '" << productoAEliminar << "' no se encuentra en el archivo.\n";
    }

}

void capturardatos(){

}

void existencias(){

}
