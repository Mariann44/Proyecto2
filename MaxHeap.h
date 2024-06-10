/*Proyecto realizado por : Valeria Marín Barquero y Gabriel Arguedas Solano
*
* 
* Implementación de un MaxHeap.
* Un MaxHeap es una estructura de datos que permite almacenar un conjunto de elementos y mantener el elemento más grande en la raíz.
* Aquí están las funcionalidades principales de la clase MaxHeap:
* funciones:
* insert(KVPair<K, V> element): Inserta un elemento en el heap.
* first(): Devuelve el elemento más grande del heap.
* removeFirst(): Elimina y devuelve el elemento más grande del heap.
* remove(int pos): Elimina y devuelve el elemento en la posición dada.
* clear(): Elimina todos los elementos del heap.
* getSize(): Devuelve la cantidad de elementos en el heap.
* isEmpty(): Devuelve true si el heap está vacío.
* print(): Imprime todos los elementos en el heap.
* 
*/





#pragma once
#define DEFAULT_MAX_SIZE 32768

#include "KVPair.h"
#include <stdexcept>
#include <iostream>

using std::wcout;
using std::runtime_error;
using std::cout;
using std::endl;

template <typename K, typename V>
class MaxHeap
{
private:
    KVPair<K, V>* elements;

    int max;
    int size;

    MaxHeap(const MaxHeap<K, V>& other) {}
    void operator =(const MaxHeap<K, V>& other) {}

    void siftUp(int pos) {
        while (pos != 0 && elements[pos] > elements[parent(pos)]) {
            swap(pos, parent(pos));
            pos = parent(pos);
        }
    }

    void siftDown(int pos) {
        while (!isLeaf(pos) && elements[pos] < elements[maxChild(pos)]) {
            int mChild = maxChild(pos);
            swap(pos, mChild);
            pos = mChild;
        }
    }

    int parent(int pos) {
        return (pos - 1) / 2;
    }
    int leftChild(int pos) {
        return 2 * pos + 1;
    }
    int rightChild(int pos) {
        return 2 * pos + 2;
    }
    int maxChild(int pos) {
        if (rightChild(pos) >= size || elements[leftChild(pos)] > elements[rightChild(pos)]) {
            return leftChild(pos);
        }
        return rightChild(pos);
    }

    bool isLeaf(int pos) {
        return leftChild(pos) >= size;
    }

    void swap(int pos1, int pos2) {
        KVPair<K, V> temp = elements[pos1];
        elements[pos1] = elements[pos2];
        elements[pos2] = temp;
    }

public:
    MaxHeap(int max = DEFAULT_MAX_SIZE) {
        elements = new KVPair<K, V>[max];
        size = 0;
        this->max = max;
    }
    ~MaxHeap() {
        delete[] elements;
    }


    void insert(KVPair<K, V> element) {
        if (size == max) {
            cout << "heap está llenito" << endl;
            throw runtime_error("Heap is full.");

        }
        elements[size] = element;
        size++;
        siftUp(size - 1);
    }
    KVPair<K, V> first() {
        if (size == 0)
            throw runtime_error("Heap is empty.");
        return elements[0];
    }
    KVPair<K,V> removeFirst() {
        if (size == 0)
            throw runtime_error("Heap is empty.");
        return remove(0);
    }
    KVPair<K,V> remove(int pos) {
        if (size == 0)
            throw runtime_error("Heap is empty.");
        if (pos < 0 || pos >= size)
            throw runtime_error("Index out of bounds.");
        swap(pos, size - 1);
        size--;
        siftDown(0);
        return elements[size];
    }
    void clear() {
        size = 0;
    }
    int getSize() {
        return size;
    }
    bool isEmpty() {
        return size == 0;
    }
    void print() {
        wcout << "[ ";
        for (int i = 0; i < size; i++) {
            wcout << elements[i] << " ";
        }
        wcout << "]" << endl;
    }

};