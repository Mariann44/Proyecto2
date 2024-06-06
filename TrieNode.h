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

