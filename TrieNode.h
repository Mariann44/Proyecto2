#pragma once
#include "HashTable.h"
#include "ArrayList.h"

class TrieNode {
public:
	bool isFinal;
	int prefixCount;
	ArrayList<int>* numsLine;
	Dictionary<char, TrieNode*>* children;

	TrieNode() {
		isFinal = false;
		prefixCount = 0;
		numsLine = new ArrayList<int>();
		children = new HashTable<char, TrieNode*>();
	}
	~TrieNode() {
		delete children;
	}
	bool containsChild(char c) {
		return children->contains(c);
	}
	TrieNode* getChild(char c) {
		return children->getValue(c);
	}
	void addChild(char c) {
		children->insert(c, new TrieNode());
	}
	void removeChild(char c) {
		children->remove(c);
	}
	List<char>* getChildren() {
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

