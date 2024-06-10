/*Proyecto realizado por : Valeria Marín Barquero y Gabriel Arguedas Solano
*
*Estructura elaborada durante lecciones de Estructuras de Datos por el profesor Mauricio Áviles
* 
* Implementación de una lista doblemente enlazada.
* Una lista doblemente enlazada es una estructura de datos que permite almacenar un conjunto de elementos y acceder a ellos de manera secuencial.
* Aquí están las funcionalidades principales de la clase DLinkedList:
* funciones:
* insert(E element): Inserta un elemento en la lista.
* append(E element): Inserta un elemento al final de la lista.
* set(E element): Reemplaza el elemento actual con el elemento dado.
* remove(): Elimina el elemento actual y devuelve su valor.
* clear(): Elimina todos los elementos de la lista.
* getElement(): Devuelve el elemento actual.
* goToStart(): Mueve la posición actual al inicio de la lista.
* goToEnd(): Mueve la posición actual al final de la lista.
* goToPos(int pos): Mueve la posición actual a la posición dada.
* next(): Mueve la posición actual al siguiente elemento.
* previous(): Mueve la posición actual al elemento anterior.
* atStart(): Devuelve true si la posición actual está al inicio de la lista.
* atEnd(): Devuelve true si la posición actual está al final de la lista.
* getSize(): Devuelve la cantidad de elementos en la lista.
* getPos(): Devuelve la posición actual.
* print(): Imprime todos los elementos en la lista.
* contains(E element): Devuelve true si el elemento está en la lista.
* 
*/



#pragma once
#include <stdexcept>
#include <iostream>
#include "List.h"
#include "DNode.h"

using std::runtime_error;
using std::cout;
using std::endl;
using std::wcout;

template <typename E>
class DLinkedList :  public List<E>
{
private:
	DNode<E>* head;
	DNode<E>* tail;
	DNode<E>* current;
	int size;

public:
	DLinkedList() {
		current = head = new DNode<E>(nullptr, nullptr);
		head->next = tail = new DNode<E>(nullptr, head);
		size = 0;
	}
	~DLinkedList() {
		clear();
		delete head;
		delete tail;
	}
	void insert(E element) {
		current->next = current->next->previous 
			= new DNode<E>(element, current->next, current);
		size++;
	}
	void append(E element) {
		tail->previous = tail->previous->next 
			= new DNode<E>(element, tail, tail->previous);
		size++;
	}
	void set(E element) {
		if (size == 0)
			throw runtime_error("List is empty.");
		if (current->next == tail)
			throw runtime_error("No current element.");
		current->next->element = element;
	}
	E remove() {
		if (size == 0)
			throw runtime_error("List is empty.");
		if (current->next == tail)
			throw runtime_error("No current element.");
		E result = current->next->element;
		current->next = current->next->next;
		delete current->next->previous;
		current->next->previous = current;
		size--;
		return result;
	}
	void clear() {
		while (head->next != tail) {
			head->next = head->next->next;
			delete head->next->previous;
		}
		current = tail->previous = head;
		size = 0;
	}
	E getElement() {
		if (size == 0)
			throw runtime_error("List is empty.");
		if (current->next == tail)
			throw runtime_error("No current element.");
		return current->next->element;
	}
	void goToStart() {
		current = head;
	}
	void goToEnd() {
		current = tail->previous;
	}
	void goToPos(int pos) {
		if (pos < 0 || pos > size)
			throw runtime_error("Index out bounds.");
		current = head;
		for (int i = 0; i < pos; i++) {
			current = current->next;
		}
	}
	void next() {
		if (current != tail->previous)
			current = current->next;
	}
	void previous() {
		if (current != head)
			current = current->previous;
	}
	bool atStart() {
		return current == head;
	}
	bool atEnd() {
		return current == tail->previous;
	}
	int getSize() {
		return size;
	}
	int getPos() {
		// Elaborado por Alejandro Madrigal
		DNode<E>* temp = head;
		int i;
		for (i = 0; current != temp; i++)
			temp = temp->next;
		return i;
	}
	void print() {
		wcout << "[ ";
		DNode<E>* temp = head->next;
		while (temp != tail) {
			wcout << temp->element << " ";
			temp = temp->next;
		}
		wcout << "]" << endl;
	}
	bool contains(E element) {
		goToStart();
		while (!atEnd()) {
			if (element == getElement()) {
				return true;
			}
			next();
		}
		return false;
	}
};

