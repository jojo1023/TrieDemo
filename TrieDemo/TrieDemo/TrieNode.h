#pragma once
#include <iostream>
#include <map>
#include <string>
using std::map;
using std::string;

template <class TValue>
class TrieNode
{
public:
	TrieNode(TrieNode<TValue>* parent, char key);
	~TrieNode();
	TValue Value;
	map<char, TrieNode<TValue>*> Children;
	bool HasValue;
	TrieNode<TValue>* Parent;
	char Key;
	bool ContainsKey(char key);
};

template <class TValue>
TrieNode<TValue>::TrieNode(TrieNode<TValue>* parent, char key)
{
	Parent = parent;
	HasValue = false;
	Key = key;
}
template <class TValue>
TrieNode<TValue>::~TrieNode()
{
	for (auto child : Children)
	{
		delete child.second;
	}
}

template <class TValue>
bool TrieNode<TValue>::ContainsKey(char key) {
	return Children.find(key) != Children.end();
}
