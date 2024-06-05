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