// Proyecto1.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <string>
#include <fstream>
#include <iostream>
#include "ArrayList.h"
#include "DlinkedList.h"
#include <locale>
#include <cwctype>
#include <codecvt>
#include <cctype>  

using std::cout;
using std::endl;
using std::getline;
using std::string;
using std::cin;
using std::wstring;
using std::wcout;

ArrayList<wstring> palabras;

wchar_t aMinuscula(wchar_t vocalTildada) {
		return std::tolower(static_cast<unsigned char>(vocalTildada));
}



void separarPalabras(wstring linea) {
	setlocale(LC_ALL, "es_ES.utf8");
	wstring palabra = L"";
	for (unsigned int i = 0; i < linea.size(); i++) {
		
		wchar_t letra = aMinuscula(linea[i]);
		if (iswalpha(letra)) { 
			
			palabra += letra;
			
		}
		else {
			if (palabra.size() > 0) {
				wcout << palabra << endl;
				palabra = L"";
			}
		}
	}
}




int main()
{
    wcout << "Bienvenido al proyecto de Indización de texto con Tries" << endl;
    wcout << "Por favor metame la ruta del archivo ANSI" << endl;

    string ruta;
    getline(cin, ruta);

	std::locale::global(std::locale(""));
	std::wifstream archivo(ruta);
	archivo.imbue(std::locale());

	if (!archivo.is_open()) {
		wcout << L"No se pudo abrir el archivo o no existe." << endl;
	}
	else {
		wcout << L"El archivo se abrió correctamente." << endl;
		if (!palabras.isEmpty()) {
			palabras.clear();
		}
		wstring linea;
		while (getline(archivo, linea)) {
			if (linea.size() > 0)
				palabras.append(linea);
		}

		archivo.close();
	}


	
	
	palabras.goToStart();
	while (!palabras.atEnd()) {

		separarPalabras(palabras.getElement());
		palabras.next();
	}
	
 
	
	
	
	return 0;
	

}

