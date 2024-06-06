#pragma once

#include <stdexcept>
#include <iostream>
#include "BSTNode.h"
#include "DLinkedList.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class BSTree {
private:
	BSTree(const BSTree<E>& other) {}
	void operator =(const BSTree<E>& other) {}
	
	BSTNode<E>* root;

	BSTNode<E>* insertAux(BSTNode<E>* current, E element) {
		if (current == nullptr)
			return new BSTNode<E>(element);
		// se puede quitar el siguiente if si se aceptan repetidos
		if (element == current->element)
			throw runtime_error("Duplicated element.");
		if (element < current->element) {
			current->left = insertAux(current->left, element);
			return current;
		}
		else { // es mayor
			current->right = insertAux(current->right, element);
			return current;
		}
	}

	void findAux(BSTNode<E>* current, E element, E* result) {
		if (current == nullptr)
			throw runtime_error("Element not found.");
		if (element == current->element)
			*result = current->element;
		else if (element < current->element)
			findAux(current->left, element, result);
		else
			findAux(current->right, element, result);
	}

	BSTNode<E>* removeAux(BSTNode<E>* current, E element, E* result) {
		if (current == nullptr)
			throw runtime_error("Element not found.");
		if (element < current->element) {
			current->left = removeAux(current->left, element, result);
			return current;
		}
		if (element > current->element) {
			current->right = removeAux(current->right, element, result);
			return current;
		}
		else { // element == current->element
			*result = current->element;
			int children = current->childrenCount();
			if (children == 0) {
				delete current;
				return nullptr;
			}
			if (children == 1) {
				BSTNode<E>* child = current->getOnlyChild();
				delete current;
				return child;
			}
			else { // children == 2
				BSTNode<E>* successor = getSuccessor(current);
				swap(current, successor);
				current->right = removeAux(current->right, element, result);
				return current;
			}
		}
	}
	BSTNode<E>* getSuccessor(BSTNode<E>* current) {
		BSTNode<E>* successor = current->right;
		while (successor->left != nullptr)
			successor = successor->left;
		return successor;
	}
	void swap(BSTNode<E>* node1, BSTNode<E>* node2) {
		E temp = node1->element;
		node1->element = node2->element;
		node2->element = temp;
	}
	bool containsAux(BSTNode<E>* current, E element) {
		if (current == nullptr)
			return false;
		if (element == current->element)
			return true;
		if (element < current->element)
			return containsAux(current->left, element);
		else
			return containsAux(current->right, element);
	}
	void clearAux(BSTNode<E>* current) {
		if (current == nullptr)
			return;
		clearAux(current->left);
		clearAux(current->right);
		delete current;
	}

	void getElementsAux(BSTNode<E>* current, List<E>* elements) {
		if (current == nullptr)
			return;
		getElementsAux(current->left, elements);
		elements->append(current->element);
		getElementsAux(current->right, elements);
	}
	int getSizeAux(BSTNode<E>* current) {
		if (current == nullptr)
			return 0;
		return 1 + getSizeAux(current->left)
			+ getSizeAux(current->right);
	}
	int heightAux(BSTNode<E>* current) {
		if (current == nullptr)
			return 0;
		int leftHeight = heightAux(current->left);
		int rightHeight = heightAux(current->right);
		return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
	}
public:
	BSTree() {
		root = nullptr;
	}
	~BSTree() {
		clear();
	}
	void insert(E element) {
		root = insertAux(root, element);
	}
	E find(E element) {
		E result;
		findAux(root, element, &result);
		return result;
	}
	E remove(E element) {
		E result;
		root = removeAux(root, element, &result);
		return result;
	}
	bool contains(E element) {
		return containsAux(root, element);
	}
	void clear() {
		clearAux(root);
		root = nullptr;
	}
	List<E>* getElements() {
		List<E>* elements = new DLinkedList<E>();
		getElementsAux(root, elements);
		return elements;
	}
	int getSize() {
		return getSizeAux(root);
	}
	void print() {
		List<E>* elements = getElements();
		elements->print();
		delete elements;
	}
	int height() {
		return heightAux(root);
	}
};

