#pragma once
#define DEFAULT_MAX_SIZE 1024

#include <stdexcept>
#include <iostream>

using std::runtime_error;
using std::cout;
using std::endl;

template <typename K, typename V>
class MaxHeap
{
private:
	std::pair<K, V>* elements;

	int max;
	int size;

	MaxHeap(const MaxHeap<K, V>& other) {}
	void operator =(const MaxHeap<K, V>& other) {}

	void siftUp(int pos) {
		while (pos != 0 && elements[pos].first > elements[parent(pos)].first) {
			swap(pos, parent(pos));
			pos = parent(pos);
		}
	}

	void siftDown(int pos) {
		while (!isLeaf(pos) && elements[pos].first < elements[maxChild(pos)].first) {
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
		if (rightChild(pos) >= size || elements[leftChild(pos)].first > elements[rightChild(pos)].first) {
			return leftChild(pos);
		}
		return rightChild(pos);
	}

	bool isLeaf(int pos) {
		return leftChild(pos) >= size;
	}

	void swap(int pos1, int pos2) {
		std::pair<K, V> temp = elements[pos1];
		elements[pos1] = elements[pos2];
		elements[pos2] = temp;
	}

public:
	MaxHeap(int max = DEFAULT_MAX_SIZE) {
		elements = new std::pair<K, V>[max];
		size = 0;
		this->max = max;
	}
	~MaxHeap() {
		delete[] elements;
	}
	void insert(std::pair<K, V> element) {
		if (size == max)
			throw runtime_error("Heap is full.");
		elements[size] = element;
		size++;
		siftUp(size - 1);
	}
	std::pair<K, V> first() {
		if (size == 0)
			throw runtime_error("Heap is empty.");
		return elements[0];
	}
	std::pair<K,V> removeFirst() {
		if (size == 0)
			throw runtime_error("Heap is empty.");
		return remove(0);
	}
	std::pair<K,V> remove(int pos) {
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
		cout << "[ ";
		for (int i = 0; i < size; i++) {
			cout << "(" << elements[i].first << ", " << elements[i].second << ") ";
		}
		cout << "]" << endl;
	}


};