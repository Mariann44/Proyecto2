/*Proyecto realizado por : Valeria Marín Barquero y Gabriel Arguedas Solano
*
*Estructura elaborada durante lecciones de Estructuras de Datos por el profesor Mauricio Áviles
* 
* Implementación de un TrieNode.
* Un TrieNode es un nodo que se utiliza en un Trie. Contiene un diccionario de hijos, una bandera que indica si es una palabra final, un contador de prefijos y una lista de líneas.
* Aquí están las funcionalidades principales de la clase TrieNode:
* funciones:
* containsChild(wchar_t c): Devuelve true si el nodo tiene un hijo con el caracter dado.
* getChild(wchar_t c): Devuelve el hijo con el caracter dado.
* addChild(wchar_t c): Agrega un hijo con el caracter dado.
* removeChild(wchar_t c): Elimina el hijo con el caracter dado.
* getChildren(): Devuelve una lista con los caracteres de los hijos.
* getIsFinal(): Devuelve true si el nodo es una palabra final.
* setIsFinal(bool isFinal): Establece si el nodo es una palabra final.
* getPrefixCount(): Devuelve la cantidad de prefijos que tienen la palabra que termina en este nodo.
* setPrefixCount(int prefixCount): Establece la cantidad de prefijos que tienen la palabra que termina en este nodo.
* increaseCount(): Incrementa el contador de prefijos.
* decreaseCount(): Decrementa el contador de prefijos.
* addNumLine(int numLine): Agrega una línea a la lista de líneas.
* 
*/



#pragma once
#include "HashTable.h"
#include "ArrayList.h"
#include "DlinkedList.h"
#include "BSTDictionary.h"

#include <iostream>
#include <string>

using std::wstring;
using std::wcout;

class TrieNode {
public:
	bool isFinal;
	int prefixCount;
	DLinkedList<int>* numsLine;
	Dictionary<wchar_t, TrieNode*>* children;

	TrieNode() {
		isFinal = false;
		prefixCount = 0;
		numsLine = new DLinkedList<int>();
		children = new BSTDictionary<wchar_t, TrieNode*>();
	}
	~TrieNode() {
		delete children;
	}
	bool containsChild(wchar_t c) {
		return children->contains(c);
	}
	TrieNode* getChild(wchar_t c) {
		return children->getValue(c);
	}
	void addChild(wchar_t c) {
		children->insert(c, new TrieNode());
	}
	void removeChild(wchar_t c) {
		children->remove(c);
	}
	List<wchar_t>* getChildren() {
		return children->getKeys();
	}

	bool getIsFinal() {
		return isFinal;
	}

	void setIsFinal(bool isFinal) {
		this->isFinal = isFinal;
	}

	int getPrefixCount() {
		return prefixCount;
	}
	
	void setPrefixCount(int prefixCount) {
		this->prefixCount = prefixCount;
	}

	void increaseCount() {
		prefixCount++;
	}

	void decreaseCount() {
		prefixCount--;
	}

	void addNumLine(int numLine) {
		numsLine->append(numLine);
	}
};

