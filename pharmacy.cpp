#include<iostream>
#include<fstream>
#include<stdio.h>
#include<string>
#include<stdlib.h>
#include<algorithm>
using namespace std;

// Variables
int opcion = 0;
string producto, descripcion;

// Creación del archivo base
ofstream archivo;

// Funciones
void productonuevo();
void buscarproducto();
void actualizarproducto();
void eliminarproducto();
void capturardatos();
void existencias();
void capitalizacion();

int main(){

    while (true) { // Bucle infinito
        do {
        cout << "************************" << endl;
        cout << "* Control de productos *" << endl;
        cout << "*       Farmacia       *" << endl;
        cout << "************************\n\n" << endl;

            cout << "Menu de opciones:" << endl;
            cout << "1) Producto nuevo" << endl;
            cout << "2) Buscar producto" << endl;
            cout << "3) Actualizar producto" << endl;
            cout << "4) Eliminar producto" << endl;
            cout << "5) Capturar datos producto (Cantidad)" << endl;
            cout << "6) Ver producto sin existencia" << endl;

            cout << "\nSeleccione una opcion: "; cin >> opcion; cout << endl;

            if (cin.fail()) {
                cin.clear(); // Limpiar el estado de error
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada
                system("cls");
                continue;
            }
            
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

// Funciones

void productonuevo(){
    fstream archivo;

    if (!archivo) {
        cout << "Error: No se pudo abrir el archivo original.\n";
        return;
    }

    archivo.open("productos.txt", ios::app); // Abrimos el archivo para añadir texto

    cout << "Ingrese el nombre del producto nuevo: ";
    cin.ignore();
    getline(cin, producto);
    capitalizacion();
    
    cout << "Ingrese una breve descripcion del producto: ";
    getline(cin, descripcion);

    // Guardamos el producto y su descripcion en el archivo
    archivo << "Cantidad: 0 | " << producto << " | " << descripcion << endl;
    archivo.close();

    cout << "Producto ingresado correctamente." << endl;
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
    producto = productoBuscado;
    capitalizacion();  // Capitalizar el nombre del producto
    productoBuscado = producto;

    while (getline(archivo, linea)) { // Leer el archivo línea por línea
        if (linea.find(productoBuscado) != string::npos) { // Si se encuentra el producto en la línea
            encontrado = true;

            // Extraer la cantidad (subcadena entre "Cantidad:" y " |")
            size_t posCantidad = linea.find("Cantidad:") + 9;
            size_t posBarra = linea.find(" |", posCantidad);
            string cantidad_str = linea.substr(posCantidad, posBarra - posCantidad);
            int cantidad = stoi(cantidad_str);

            // Extraer el nombre del producto (entre las dos barras verticales)
            size_t posProducto = linea.find("|") + 2;
            size_t posProductoFinal = linea.find("|", posProducto);
            string productoNombre = linea.substr(posProducto, posProductoFinal - posProducto);

            // Extraer la descripción (todo lo que sigue después de la segunda barra vertical)
            string descripcion = linea.substr(posProductoFinal + 2);

            // Mostrar la información completa del producto encontrado
            cout << "Producto encontrado:\n";
            cout << "Nombre: " << productoNombre << endl;
            cout << "Cantidad: " << cantidad << endl;
            cout << "Descripcion: " << descripcion << endl;
            break;  // Salir del bucle una vez encontrado el producto
        }
    }

    if (!encontrado) {
        cout << "El producto '" << productoBuscado << "' no se encuentra en el archivo.\n";
    }

    archivo.close();
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
    producto = productoAEliminar;
    capitalizacion();
    productoAEliminar = producto;

    // Leer el archivo linea por linea y copiar los datos al archivo temporal
    while (getline(archivoEntrada, linea)) {
        if (linea.find(productoAEliminar) != string::npos) {
            encontrado = true; // Producto encontrado, no se copia al archivo temporal
        } else {
            archivoTemporal << linea << endl; // Copiar las lineas que no coinciden
        }
    }

    archivoEntrada.close();
    archivoTemporal.close();

    if (encontrado) {
        remove("productos.txt"); // Eliminar el archivo original
        rename("productos_temp.txt", "productos.txt"); // Renombrar el archivo temporal
        cout << "El producto '" << productoAEliminar << "' ha sido eliminado con éxito.\n";
    } else {
        remove("productos_temp.txt"); // Eliminar el archivo temporal si no se usó
        cout << "El producto '" << productoAEliminar << "' no se encuentra en el archivo.\n";
    }
}

void capturardatos(){
    int cantidad = 0;
    string productoBuscado;
    string linea;
    bool encontrado = false;
    string contenidoArchivo;

    // Solicitar el nombre del producto
    cout << "Ingrese el nombre del producto para capturar la cantidad: ";
    cin.ignore();  // Limpiar el buffer de entrada
    getline(cin, productoBuscado);
    producto = productoBuscado;
    capitalizacion();  // Capitalizar el nombre del producto
    productoBuscado = producto;

    // Abrir el archivo para lectura
    ifstream archivo("productos.txt");
    if (!archivo) {
        cout << "Error: No se pudo abrir el archivo.\n";
        return;
    }

    // Leer todo el archivo y almacenar en una variable
    while (getline(archivo, linea)) {
        if (linea.find(productoBuscado) != string::npos) {
            encontrado = true;
            
            // Solicitar la nueva cantidad
            cout << "Cantidad de " << productoBuscado << ": ";
            cin >> cantidad;

            // Modificar la cantidad en la línea
            size_t posCantidad = linea.find("Cantidad: ");
            if (posCantidad != string::npos) {
                // Reemplazar la cantidad
                linea.replace(posCantidad + 10, linea.find(" |", posCantidad) - posCantidad - 10, to_string(cantidad));
            }
        }
        contenidoArchivo += linea + "\n";
    }

    archivo.close();

    if (!encontrado) {
        cout << "El producto '" << productoBuscado << "' no se encuentra en el archivo.\n";
    } else {
        // Escribir el contenido modificado de vuelta al archivo
        ofstream archivoSalida("productos.txt");
        archivoSalida << contenidoArchivo;
        archivoSalida.close();
        cout << "Cantidad actualizada con éxito.\n";
    }
}

void existencias(){
    ifstream archivo("productos.txt");
    string linea;
    int numeroProducto = 1; // Para enumerar los productos

    if (!archivo) {
        cout << "Error: No se pudo abrir el archivo.\n";
        return;
    }

    cout << "Listado de productos y existencias:\n";

    // Leer el archivo línea por línea
    while (getline(archivo, linea)) {
        // Buscar la palabra "Cantidad:" en la línea
        size_t posCantidad = linea.find("Cantidad:");
        if (posCantidad != string::npos) {
            // Extraer la cantidad
            string cantidad_str = linea.substr(posCantidad + 9, linea.find(" |", posCantidad) - posCantidad - 9); // Extrae la cantidad
            int cantidad = stoi(cantidad_str);

            // Extraer el nombre del producto (lo que está entre las barras verticales)
            string productoNombre = linea.substr(linea.find("|") + 2, linea.find("|", linea.find("|") + 1) - (linea.find("|") + 2));

            // Mostrar el producto con su cantidad y el estado de existencia
            if (cantidad == 0) {
                cout << numeroProducto << ". " << productoNombre << " (Sin existencias)" << endl;
            } else {
                cout << numeroProducto << ". " << productoNombre << " (" << cantidad << " unidades)" << endl;
            }

            numeroProducto++;  // Aumentar el número del producto para la siguiente línea
        }
    }

    archivo.close();
    cin.get();
}

void capitalizacion(){
    transform(producto.begin(), producto.end(), producto.begin(), [](unsigned char c) {return tolower(c);});
    producto[0] = toupper(producto[0]);
}