/*Proyecto realizado por : Valeria Marín Barquero y Gabriel Arguedas Soloano
*
*Estructura elaborada durante lecciones de Estructuras de Datos por el profesor Mauricio Áviles
* 
* Implementación de un Trie.
* Un Trie es una estructura de datos que permite almacenar un conjunto de palabras y realizar búsquedas de palabras o prefijos de palabras.
* Aquí están las funcionalidades principales de la clase Trie:
* funciones:
* insert(wstring word, int line): Inserta una palabra en el Trie.
* containsWord(wstring word): Devuelve true si la palabra está en el Trie.
* containsPrefix(wstring prefix): Devuelve true si el prefijo está en el Trie.
* prefixCount(wstring prefix): Devuelve la cantidad de palabras que tienen el prefijo dado.
* remove(wstring word): Elimina una palabra del Trie.
* clear(): Elimina todas las palabras del Trie.
* getMatches(wstring prefix): Devuelve una lista con todas las palabras que tienen el prefijo dado.
* getSize(): Devuelve la cantidad de palabras en el Trie.
* print(): Imprime todas las palabras en el Trie.
* printLines(wstring word): Imprime las líneas en las que aparece una palabra.
* cantidadAparicion(wstring word): Devuelve la cantidad de veces que aparece una palabra.
* getLines(wstring word): Devuelve una lista con las líneas en las que aparece una palabra.
* getMatchesWithLength(int length): Devuelve una lista con todas las palabras de un largo dado.
* getWords(): Devuelve una lista con todas las palabras en el Trie.
* 
* 
*/

#pragma once

#include <string>
#include <iostream>
#include <stdexcept>
#include "TrieNode.h"
#include "DLinkedList.h"
#include "ArrayList.h"
#include "MinHeap.h"

using std::wstring;
using std::wcout;
using std::cout;
using std::endl;
using std::runtime_error;

class Trie {
private:
	TrieNode* root;

	TrieNode* findNode(wstring word) {
		TrieNode* current = root;
		for (unsigned int i = 0; i < word.size(); i++) {
			if (!current->containsChild(word[i]))
				return nullptr;
			current = current->getChild(word[i]);
		}
		return current;
	}
	void clearAux(TrieNode* current) {
		List<wchar_t>* children = current->getChildren();
		children->goToStart();
		while (!children->atEnd()) {
			wchar_t c = children->getElement();
			TrieNode* child = current->getChild(c);
			clearAux(child);
			children->next();
		}
		delete children;
		delete current;
	}
	void getMatchesAux(TrieNode* current, wstring prefix, List<wstring>* words) {
		if (current->isFinal)
			words->append(prefix);
		List<wchar_t>* children = current->getChildren();
		for (children->goToStart(); !children->atEnd(); children->next()) {
			wchar_t c = children->getElement();
			getMatchesAux(current->getChild(c), prefix + c, words);
		}
		delete children;
	}

public:
	Trie() {
		root = new TrieNode();
	}
	~Trie() {
		clear();
		delete root;
	}
	void insert(wstring word, int line) {
		TrieNode* current = findNode(word);
		if (current != nullptr) {
			current->addNumLine(line);
			return;

		}
		current = root;
		for (unsigned int i = 0; i < word.size(); i++) {
			current->prefixCount++;
			if (!current->containsChild(word[i]))
				current->addChild(word[i]);
			current = current->getChild(word[i]);
		}
		current->prefixCount++;
		current->isFinal = true;
		current->addNumLine(line);

	}
	bool containsWord(wstring word) {
		TrieNode* current = findNode(word);
		if (current == nullptr) return false;
		return current->isFinal;
	}
	bool containsPrefix(wstring prefix) {
		TrieNode* current = findNode(prefix);
		if (current == nullptr) return false;
		return true;
	}
	int prefixCount(wstring prefix) {
		TrieNode* current = findNode(prefix);
		if (current == nullptr) return 0;
		return current->prefixCount;
	}
	void remove(wstring word) {
		if (!containsWord(word))
			throw runtime_error("Word not found.");
		TrieNode* current = root;
		for (unsigned int i = 0; i < word.size(); i++) {
			current->prefixCount--;
			TrieNode* child = current->getChild(word[i]);
			if (child->prefixCount == 1)
				current->removeChild(word[i]);
			if (current->prefixCount == 0)
				delete current;
			current = child;
		}
		current->prefixCount--;
		current->isFinal = false;
		if (current->prefixCount == 0) 
			delete current;
	}
	void clear() {
		clearAux(root);
		root = new TrieNode();
	}
	List<wstring>* getMatches(wstring prefix) {
		List<wstring>* words = new DLinkedList<wstring>();
		TrieNode* current = findNode(prefix);
		if (current != nullptr)
			getMatchesAux(current, prefix, words);
		return words;
	}
	int getSize() {
		return root->prefixCount;
	}
	void print() {
		List<wstring>* words = new DLinkedList<wstring>();
		words = getMatches(L"");
		words->print();
		delete words;
	}

	void printLines(wstring word) {
		TrieNode* current = findNode(word);
		if (current == nullptr) {
			cout << "Word not found." << endl;
			return;
		}
		current->numsLine->print();
	}

	int cantidadAparicion(wstring word) {
		TrieNode* current = findNode(word);
		if (current == nullptr) {
			return 0;
		}
		return current->numsLine->getSize();
	}

	List<int>* getLines(wstring word) {
		TrieNode* current = findNode(word);
		if (current == nullptr) {
			return nullptr;
		}
		return current->numsLine;
	}

	void getMatchesWithLengthAux(TrieNode* current, wstring prefix, MinHeap<wstring>* words, int length) {
		if (current->isFinal && prefix.size() == length)
			words->insert(prefix);
		List<wchar_t>* children = current->getChildren();
		for (children->goToStart(); !children->atEnd(); children->next()) {
			wchar_t c = children->getElement();
			getMatchesWithLengthAux(current->getChild(c), prefix + c, words, length);
		}
		delete children;
	}

	MinHeap<wstring>* getMatchesWithLength(int length) {
		MinHeap<wstring>* words = new MinHeap<wstring>();
		getMatchesWithLengthAux(root, L"", words, length);
		return words;
	}

	DLinkedList<wstring>* getWords() {
		DLinkedList<wstring>* words = new DLinkedList<wstring>();
		getMatchesAux(root, L"", words);
		return words;
	}


};

