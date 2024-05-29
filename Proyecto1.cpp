// Proyecto1.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <string>;
#include <fstream>;
#include <iostream>;
#include "ArrayList.h";
using std::cout;
using std::endl;
using std::getline;
using std::string;
using std::cin;
ArrayList<string> palabras;


int main()
{
    cout << "Bienvenido al proyecto de Indización de texto con Tries" << endl;
    cout << "Por favor inserteme la ruta del archivo ANSI" << endl;
    string ruta;
    getline(cin, ruta);

    std::ifstream archivo(ruta);

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo o no existe." << endl;
    }
    else {
        cout << "El archivo se abrió correctamente." << endl;
        if (!palabras.isEmpty()) {
            palabras.clear();
        }
        string linea;
        while (getline(archivo, linea)) {
            if (linea.size() > 0)
            palabras.append(linea);
        }

        archivo.close();

    }

    while (!palabras.atEnd()) {
    cout << palabras.getPos() << endl;
    cout << palabras.getElement() << endl;
    palabras.next();
}


}

