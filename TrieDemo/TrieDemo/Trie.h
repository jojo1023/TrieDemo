#pragma once
#include "TrieNode.h"
#include <vector>
#include <queue>
using std::vector;
using std::queue;

template <class TValue>
class Trie
{
public:
	Trie();
	~Trie();
	int GetCount();
	bool ContainsKey(string key);
	TValue GetValue(string key);
	void SetValue(string key, TValue value);

	void Insert(string key, TValue value);
	bool Remove(string key);
	vector<TValue> GetValuesWithPrefix(string prefix, int max);

private:
	TrieNode<TValue>* root;
	TrieNode<TValue>* FindNode(string key);
	int count = 0;
};


template <class TValue>
Trie<TValue>::Trie()
{
	root = new TrieNode<TValue>(NULL, 0);
}

template <class TValue>
Trie<TValue>::~Trie()
{
	delete root;
}
template <class TValue>
int Trie<TValue>::GetCount()
{
	return count;
}



template <class TValue>
bool Trie<TValue>::ContainsKey(string key) {
	TrieNode<TValue>* node = FindNode(key);
	return node != NULL && node->HasValue;
}

template <class TValue>
TValue Trie<TValue>::GetValue(string key) {
	TrieNode<TValue>* node = FindNode(key);
	if (node == NULL) {
		throw "Key is Not in Trie";
	}
	if (!node->HasValue) {
		throw "Key Does Not Have Value";
	}
	return node->Value;
}

template <class TValue>
void Trie<TValue>::SetValue(string key, TValue value) {
	TrieNode<TValue>* node = FindNode(key);
	if (node == NULL) {
		throw "Key is Not in Trie";
	}
	node->HasValue = true;
	node->Value = value;
}


template <class TValue>
TrieNode<TValue>* Trie<TValue>::FindNode(string key) {
	TrieNode<TValue>* currentNode = root;
	for (int i = 0; i < key.length(); i++) {
		char c = key[i];
		if (currentNode->ContainsKey(c)) {
			currentNode = currentNode->Children[c];
		}
		else {
			return NULL;
		}
	}
	return currentNode;
}


template <class TValue>
void Trie<TValue>::Insert(string key, TValue value) {
	TrieNode<TValue>* currentNode = root;
	for (int i = 0; i < key.length(); i++) {
		char c = key[i];
		if (currentNode->ContainsKey(c)) {
			currentNode = currentNode->Children[c];
		}
		else {
			TrieNode<TValue>* newNode = new TrieNode<TValue>(currentNode, c);
			currentNode->Children.insert(std::pair<char, TrieNode<TValue>*>(c, newNode));
			currentNode = newNode;
		}
	}
	if (currentNode->HasValue) {
		throw "Key Already in Trie";
	}
	currentNode->HasValue = true;
	currentNode->Value = value;
	count++;
}

template <class TValue>
vector<TValue> Trie<TValue>::GetValuesWithPrefix(string prefix, int max) {
	vector<TValue> values;
	TrieNode<TValue>* prefixNode = FindNode(prefix);
	if (prefixNode == NULL) {
		return values;
	}
	queue<TrieNode<TValue>*> nodesToSearch;
	nodesToSearch.push(prefixNode);
	while (nodesToSearch.size() > 0)
	{
		TrieNode<TValue>* currentNode = nodesToSearch.front();
		nodesToSearch.pop();
		if (currentNode->HasValue) {
			values.push_back(currentNode->Value);
			if (max >= 0 && values.size() >= max) {
				return values;
			}
		}
		for (auto child : currentNode->Children)
		{
			nodesToSearch.push(child.second);
		}
	}
	return values;
}


template <class TValue>
bool Trie<TValue>::Remove(string key) {

	TrieNode<TValue>* node = FindNode(key);
	if (node == NULL || !node->HasValue || node == root) {
		return false;
	}

	node->HasValue = false;
	count--;
	return true;
}
