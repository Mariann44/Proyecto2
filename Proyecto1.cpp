// Proyecto1.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//


#include <Windows.h>
#include <string>
#include <fstream>
#include <iostream>
#include "ArrayList.h"
#include "DlinkedList.h"
#include <locale>
#include <cwctype>
#include <codecvt>
#include <cctype>  
#include "Trie.h"
#include <limits>
#include "MinHeap.h" 
#include "MaxHeap.h" 


using std::cout;
using std::endl;
using std::getline;
using std::string;
using std::cin;
using std::wcin;
using std::wstring;
using std::wcout;

Trie trie;
ArrayList<wstring> palabras;
ArrayList<string> ignorar;
MaxHeap<int, string> top;
void menububu();


int StringtoInt(string str)
 { 
	try {
		int num = stoi(str);
		return num;
	}
	catch (const std::invalid_argument& ia) {
		cout << "Usted no digito un nÃºmero. \n";
		menububu();
		
	}
	catch (const std::out_of_range& oor) {
		cout << "El numero esta fuera de rango. \n";
		menububu();
	
	}
	catch (const std::exception& e) {
		cout << "Error desconocido. \n";
		menububu();
	
	}
	
}

string conversor(wstring palabra) {
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
	std::string palabra_str = converter.to_bytes(palabra);
	return palabra_str;
}

void rellenarMaxHeap(ArrayList<string> *palabras) {
	palabras->goToStart();
	while (!palabras->atEnd()) {
		std::pair<int, string> par; 
		par.first = trie.cantidadAparicion(palabras->getElement());
		par.second = palabras->getElement();
		top.insert(par);
		palabras->next();
	}
	top.print();

}


void imprimirLias(ArrayList<int>* lineas) {
	lineas->goToStart();
	while (!lineas->atEnd()) {
		cout << "Linea " << lineas->getElement() << ": ";
		palabras.goToPos(lineas->getElement());
		wcout << palabras.getElement() << endl;
		lineas->next();
	}
	cout << endl;
}

void consultarPrefijo(string prefijo){
	List<string>* palabrasL = trie.getMatches(prefijo);
	
	palabrasL->goToStart();
	while (!palabrasL->atEnd()) {
		ArrayList<int>* lineas = trie.getLines(palabrasL->getElement());

		cout << "La cantidad de veces que aparece la palabra: ";
		cout << palabrasL->getElement();
		cout << " es " << trie.cantidadAparicion(palabrasL->getElement()) << endl;
		cout << "En las lineas: " << endl;
		imprimirLias(lineas);
		palabrasL->next();
	}
	delete palabrasL;
}

void consultarPalabra(string palabra) {
	if (trie.containsWord(palabra)) {
		cout << "La cantidad de veces que aparece la palabra: " << palabra << " es " << trie.cantidadAparicion(palabra) << endl;
		cout << "En las lineas: " << endl;
		imprimirLias(trie.getLines(palabra));
		
	}
	else {
		cout << "La palabra no se encuentra en el texto" << endl;
	}
}

void consultarPorLargo(int largo) {
	MinHeap<string>* words = new MinHeap<string>();
	words = trie.getMatchesWithLength(largo);
	

	while (!words->isEmpty()) {
		string element = words->removeFirst();
		ArrayList<int>* lineas = trie.getLines(element);
		cout << "La cantidad de veces que aparece la palabra: ";
		cout << element;
		cout << " es " << trie.cantidadAparicion(element) << endl;
		cout << "En las lineas: " << endl;
		imprimirLias(lineas);

	}
	delete words;
}



void menububu() {
	cout << "Elija una opcion" << endl;
	cout << "a) Consulta por prefijo a;lsdkjf;alskfj" << endl;
	cout << "b) Buscar palabra" << endl;
	cout << "c) Buscar por cantidad de letras" << endl;
	cout << "d) Palabras mas utilizadas" << endl;
	cout << "e) Cargar otro archivo" << endl;
	cout << "f) BOLIVIANO" << endl;

	string opcion;
	getline(cin, opcion);

	if (opcion == "a") {
		cout << "Ingrese el prefijo" << endl;
		wstring prefijo;
		getline(wcin, prefijo);
		consultarPrefijo(conversor(prefijo));
		menububu();
	}
	else if (opcion == "b") {
		cout << "Ingrese la palabra" << endl;
		string palabra;
		getline(cin, palabra);
		consultarPalabra(palabra);
		cout << "chequea como se menea 5" << endl;
		menububu();
	
	}
	else if (opcion == "c") {
		cout << "Ingrese la cantidad de letras" << endl;
		string cantidad;
		getline(cin, cantidad);
		consultarPorLargo(StringtoInt(cantidad));
		menububu();

	}
	else if (opcion == "d") {
		return;
	}
	else if (opcion == "e") {
		cout << "Ingrese la ruta del archivo" << endl;
		string ruta;
		getline(cin, ruta);
	}
	else if (opcion == "f") {
		cout << "Adios popo" << endl;
		return;
	}
	else {
		cout << "Opcion invalida" << endl;

	}
}

wchar_t aMinuscula(wchar_t vocalTildada) {
		return std::tolower(static_cast<unsigned char>(vocalTildada));
}

void menuTop() {
	cout << "Elija una opcion" << endl;
	cout << "a) Ver Top" << endl;
	cout << "b) Salir" << endl;

	string opcion;
	getline(cin, opcion);
	if (opcion == "a") {


	}
	else if (opcion == "b") {
		cout << "Adios poposao" << endl;
		menububu();
	}
	else {
		cout << "Opcion invalida" << endl;
		menuTop();
	}

}



void separarPalabras(wstring linea, int numDeLinea) {
	setlocale(LC_ALL, "es_ES.utf8");
	wstring palabra = L"";
	for (unsigned int i = 0; i < linea.size(); i++) {
		
		wchar_t letra = aMinuscula(linea[i]);
		if (iswalpha(letra)) { 
			
			palabra += letra;
			
		}
		else {
			if (palabra.size() > 0) {
				
                // Convertir wstring a string
                std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
                std::string palabra_str = converter.to_bytes(palabra);
                
                // Insertar la palabra en el Trie
                trie.insert(palabra_str, numDeLinea);

				palabra = L"";
			}
		}
	}
}




int main()
{
	setlocale(LC_ALL, "spanish");
	SetConsoleCP(1252);
	SetConsoleOutputCP(1252);
	
	string rutaArchivoIgnorado = "C:\\Users\\Lenovo\\Desktop\\Ignorar.txt";
	std::ifstream archivoIgnorado(rutaArchivoIgnorado.c_str());

	if (!archivoIgnorado.is_open()) {
		cout << "No se pudo abrir el archivo o no existe." << endl;
	}
	else {
		if (!ignorar.isEmpty()) {
			ignorar.clear();
		}
		string linea;
		while (getline(archivoIgnorado, linea)) {
			if (linea.size() > 0)
				ignorar.append(linea);
		}
		archivoIgnorado.close();
	}


	


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

		separarPalabras(palabras.getElement(), palabras.getPos());
		palabras.next();
	}

	rellenarMaxHeap(trie.getWords());
	menububu();

	return 0;
	

}

