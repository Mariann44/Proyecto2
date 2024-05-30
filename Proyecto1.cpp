// Proyecto1.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <string>
#include <fstream>
#include <iostream>
#include "ArrayList.h"
#include "DlinkedList.h"
#include <locale>
#include <codecvt>


using std::cout;
using std::endl;
using std::getline;
using std::string;
using std::cin;
ArrayList<string> palabras;
DLinkedList<string> alfabeto;

void rellenarAlfabeto() {
	alfabeto.append("a");
	alfabeto.append("b");
	alfabeto.append("c");
	alfabeto.append("d");
	alfabeto.append("e");
	alfabeto.append("f");
	alfabeto.append("g");
	alfabeto.append("h");
	alfabeto.append("i");
	alfabeto.append("j");
	alfabeto.append("k");
	alfabeto.append("l");
	alfabeto.append("m");
	alfabeto.append("n");
	alfabeto.append("ñ");
	alfabeto.append("o");
	alfabeto.append("p");
	alfabeto.append("q");
	alfabeto.append("r");
	alfabeto.append("s");
	alfabeto.append("t");
	alfabeto.append("u");
	alfabeto.append("v");
	alfabeto.append("w");
	alfabeto.append("x");
	alfabeto.append("y");
	alfabeto.append("z");
	alfabeto.append("á");
	alfabeto.append("é");
	alfabeto.append("í");
	alfabeto.append("ó");
	alfabeto.append("ú");
	alfabeto.append("ü");
	alfabeto.append("A");
	alfabeto.append("B");
	alfabeto.append("C");
	alfabeto.append("D");
	alfabeto.append("E");
	alfabeto.append("F");
	alfabeto.append("G");
	alfabeto.append("H");
	alfabeto.append("I");
	alfabeto.append("J");
	alfabeto.append("K");
	alfabeto.append("L");
	alfabeto.append("M");
	alfabeto.append("N");
	alfabeto.append("Ñ");
	alfabeto.append("O");
	alfabeto.append("P");
	alfabeto.append("Q");
	alfabeto.append("R");
	alfabeto.append("S");
	alfabeto.append("T");
	alfabeto.append("U");
	alfabeto.append("V");
	alfabeto.append("W");
	alfabeto.append("X");
	alfabeto.append("Y");
	alfabeto.append("Z");
	alfabeto.append("Á");
	alfabeto.append("É");
	alfabeto.append("Í");
	alfabeto.append("Ó");
	alfabeto.append("Ú");
	alfabeto.append("Ü");
	
}

void separarPalabras(std::wstring linea) {
	std::wstring palabra = L"";
	std::locale loc("es_ES.UTF-8");
	for (unsigned int i = 0; i < linea.size(); i++) {
		if (std::isalpha(linea[i], loc)) {
			palabra += linea[i];
		}
		else {
			if (palabra.size() > 0) {
				std::wcout << palabra << std::endl;
				palabra = L"";
			}
		}
	}
}




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
	rellenarAlfabeto();
	cout << alfabeto.contains("á");
	
 
	
	rellenarAlfabeto();
	palabras.goToStart();
	while (!palabras.atEnd()) {
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		std::wstring wide = converter.from_bytes(palabras.getElement());
		separarPalabras(wide);
		palabras.next();
	}
	return 0;
	

}

