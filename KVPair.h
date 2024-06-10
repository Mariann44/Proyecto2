/*Proyecto realizado por : Valeria Marín Barquero y Gabriel Arguedas Solano
*
*Elaborada durante lecciones de Estructuras de Datos por el profesor Mauricio Áviles
* 
* Implementación de un KVPair.
* Un KVPair es una estructura de datos que permite almacenar un par de valores, una clave y un valor.
* Aquí están las funcionalidades principales de la clase KVPair:
* funciones:
* getValue(): Devuelve el valor del par.
* getKey(): Devuelve la clave del par.
* operator =: Asigna un par a otro.
* operator ==: Compara si dos pares son iguales.
* operator <: Compara si un par es menor que otro.
* operator <=: Compara si un par es menor o igual que otro.	
* operator >: Compara si un par es mayor que otro.
* operator >=: Compara si un par es mayor o igual que otro.
* operator !=: Compara si dos pares son diferentes.
* 
*/

#pragma once

#include <iostream>

using std::ostream;
using std::wostream;

template <typename K, typename V>
class KVPair 
{
public:
	K key;
	V value;

	KVPair() {}
	KVPair(K key) {
		this->key = key;
	}
	KVPair(K key, V value) {
		this->key = key;
		this->value = value;
	}
	KVPair(const KVPair<K, V>& other) {
		key = other.key;
		value = other.value;
	}

	V getValue() {
		return value;
	}

	K getKey() {
		return key;
	}



	void operator =(const KVPair<K, V>& other) {
		key = other.key;
		value = other.value;
	}
	bool operator ==(const KVPair<K, V>& other) {
		return key == other.key;
	}
	bool operator <(const KVPair<K, V>& other) {
		return key < other.key;
	}
	bool operator <=(const KVPair<K, V>& other) {
		return key <= other.key;
	}
	bool operator >(const KVPair<K, V>& other) {
		return key > other.key;
	}
	bool operator >=(const KVPair<K, V>& other) {
		return key >= other.key;
	}
	bool operator !=(const KVPair<K, V>& other) {
		return key != other.key;
	}
};

template <typename K, typename V>
wostream& operator <<(wostream &os, const KVPair<K, V> &pair) {
	os << L"(" << pair.key << L", " << pair.value << L")";
	return os;
}