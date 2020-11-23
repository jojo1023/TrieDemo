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
	root = new TrieNode<TValue>();
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
	TrieNode<TValue>* current = root;
	for (int i = 0; i < key.size(); i++) {
		char c = key[i];
		if (current->ContainsKey(c)) {
			current = current->Children[c];
		}
		else {
			return NULL;
		}
	}
	return current;
}


template <class TValue>
void Trie<TValue>::Insert(string key, TValue value) {
	TrieNode<TValue>* current = root;
	for (int i = 0; i < key.size(); i++) {
		char c = key[i];
		if (current->ContainsKey(c)) {
			current = current->Children[c];
		}
		else {
			TrieNode<TValue>* newNode = new TrieNode<TValue>();
			current->Children.insert(std::pair<char, TrieNode<TValue>*>(c, newNode));
			current = newNode;
		}
	}
	if (current->HasValue) {
		throw "Key is Already In Trie";
	}
	current->HasValue = true;
	current->Value = value;
	count++;
}

template <class TValue>
vector<TValue> Trie<TValue>::GetValuesWithPrefix(string prefix, int max) {
	vector<TValue> values;
	TrieNode<TValue>* prefixNode = FindNode(prefix);
	if (prefixNode == NULL) {
		return values;
	}
	queue<TrieNode<TValue>*> queue;
	queue.push(prefixNode);
	while (queue.size() > 0)
	{
		TrieNode<TValue>* node = queue.front();
		queue.pop();
		if (values.size() >= max) {
			delete node;
			continue;
		}
		if (node->HasValue) {
			values.push_back(node->Value);
		}
		for (auto child : node->Children) {
			queue.push(child.second);
		}
	}
	return values;
}


template <class TValue>
bool Trie<TValue>::Remove(string key) {
	TrieNode<TValue>* node = FindNode(key);
	if (node == NULL || !node->HasValue) {
		return false;
	}
	node->HasValue = false;
	return true;
}
