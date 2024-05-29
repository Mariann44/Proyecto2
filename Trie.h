#pragma once

#include <string>
#include <iostream>
#include <stdexcept>
#include "TrieNode.h"
#include "DLinkedList.h"

using std::string;
using std::cout;
using std::endl;
using std::runtime_error;

class Trie {
private:
	TrieNode* root;

	TrieNode* findNode(string word) {
		TrieNode* current = root;
		for (unsigned int i = 0; i < word.size(); i++) {
			if (!current->containsChild(word[i]))
				return nullptr;
			current = current->getChild(word[i]);
		}
		return current;
	}
	void clearAux(TrieNode* current) {
		List<char>* children = current->getChildren();
		children->goToStart();
		while (!children->atEnd()) {
			char c = children->getElement();
			TrieNode* child = current->getChild(c);
			clearAux(child);
			children->next();
		}
		delete children;
		delete current;
	}
	void getMatchesAux(TrieNode* current, string prefix, List<string>* words) {
		if (current->isFinal)
			words->append(prefix);
		List<char>* children = current->getChildren();
		for (children->goToStart(); !children->atEnd(); children->next()) {
			char c = children->getElement();
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
	void insert(string word) {
		if (containsWord(word))
			throw runtime_error("Duplicated word.");
		TrieNode* current = root;
		for (unsigned int i = 0; i < word.size(); i++) {
			current->prefixCount++;
			if (!current->containsChild(word[i]))
				current->addChild(word[i]);
			current = current->getChild(word[i]);
		}
		current->prefixCount++;
		current->isFinal = true;
	}
	bool containsWord(string word) {
		TrieNode* current = findNode(word);
		if (current == nullptr) return false;
		return current->isFinal;
	}
	bool containsPrefix(string prefix) {
		TrieNode* current = findNode(prefix);
		if (current == nullptr) return false;
		return true;
	}
	int prefixCount(string prefix) {
		TrieNode* current = findNode(prefix);
		if (current == nullptr) return 0;
		return current->prefixCount;
	}
	void remove(string word) {
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
	List<string>* getMatches(string prefix) {
		List<string>* words = new DLinkedList<string>();
		TrieNode* current = findNode(prefix);
		if (current != nullptr)
			getMatchesAux(current, prefix, words);
		return words;
	}
	int getSize() {
		return root->prefixCount;
	}
	void print() {
		List<string>* words = new DLinkedList<string>();
		words = getMatches("");
		words->print();
		delete words;
	}
};

