/*Proyecto realizado por : Valeria Marín Barquero y Gabriel Arguedas Solano
*
*Estructura elaborada durante lecciones de Estructuras de Datos por el profesor Mauricio Áviles
*
*implementación de una lista utilizando un array. 
*Hereda de la clase List y utiliza un array para almacenar los elementos. Aquí están las funcionalidades principales de la clase ArrayList:
*funciones:
*  insert(E element): Inserta un elemento en la posición actual de la lista.
* append(E element): Inserta un elemento al final de la lista.
* expand(): Duplica el tamaño del array.
* set(E element): Reemplaza el elemento actual con el elemento dado.
* remove(): Elimina el elemento actual y devuelve su valor.
* clear(): Elimina todos los elementos de la lista.
* goToStart(): Mueve la posición actual al inicio de la lista.
* goToEnd(): Mueve la posición actual al final de la lista.
* goToPos(int pos): Mueve la posición actual a la posición dada.
* next(): Mueve la posición actual al siguiente elemento.
* previous(): Mueve la posición actual al elemento anterior.
* atStart(): Devuelve true si la posición actual está al inicio de la lista.
* atEnd(): Devuelve true si la posición actual está al final de la lista.....
*
*/
#pragma once

#define DEFAULT_MAX_SIZE 1024

#include <stdexcept>
#include <iostream>
#include "List.h"
using std::wcout;

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class ArrayList : public List<E> {
protected: // se ponen protected cuando una subclase debe accederlos
	E* elements;
	int max;
	int size;
	int pos;

public:
	ArrayList(int max = DEFAULT_MAX_SIZE) {
		elements = new E[max];
		this->max = max;
		size = pos = 0;
	}
	~ArrayList() {
		delete[] elements;
	}

	void insert(E element) {
		if (size == max) 
			expand();
		for (int i = size; i > pos; i--) 
			elements[i] = elements[i - 1];
		elements[pos] = element;
		size++;
	}

	void append(E element) {
		if (size == max)
			expand();
		elements[size] = element;
		size++;
	}

	void expand() {
		E* newElements = new E[max * 2];
		for (int i = 0; i < size; i++)
			newElements[i] = elements[i];
		delete[] elements;
		elements = newElements;
		max *= 2;
	}


	void set(E element) {
		if (pos == size)
			throw runtime_error("No current element.");
		elements[pos] = element;
	}
	E remove() {
		if (size == 0)
			throw runtime_error("List is empty.");
		if (pos == size)
			throw runtime_error("No current element.");
		E result = elements[pos];
		for (int i = pos; i < size - 1; i++)
			elements[i] = elements[i + 1];
		size--;
		return result;
	}
	void clear() {
		pos = size = 0;
	}
	E getElement() {
		if (size == 0)
			throw runtime_error("List is empty.");
		if (pos == size)
			throw runtime_error("No current element.");
		return elements[pos];
	}
	void goToStart() {
		pos = 0;
	}
	void goToEnd() {
		pos = size;
	}
	void goToPos(int pos) {
		if (pos < 0 || pos > size)
			throw runtime_error("Index out of bounds.");
		this->pos = pos;
	}
	void next() {
		if (pos < size)
			pos++;
	}
	void previous() {
		if (pos > 0)
			pos--;
	}
	bool atStart() {
		return pos == 0;
	}
	bool atEnd() {
		return pos == size;
	}
	int getSize() {
		return size;
	}
	int getPos() {
		return pos;
	}

	bool isEmpty() {
		return size == 0;
	}

	void print() {
		wcout << "[ ";
		for (int i = 0; i < size; i++)
			wcout << elements[i] << " ";
		wcout << "]" << endl;
	}

	void printPuntero() {
		cout << "[ ";
		for (int i = 0; i < size; i++)
			cout << *elements[i] << " "; // uso del operador *
		cout << "]" << endl;
	}

	void printPunteroConIndice() {
		cout << "[ ";
		for (int i = 0; i < size; i++)
			cout << i << ". " << *elements[i] << " "; // uso del operador *
		cout << "]" << endl;
	} 


};

