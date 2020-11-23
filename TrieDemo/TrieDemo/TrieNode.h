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
	TrieNode();
	~TrieNode();
	TValue Value;
	map<char, TrieNode<TValue>*> Children;
	bool HasValue;
	bool ContainsKey(char key);
};

template <class TValue>
TrieNode<TValue>::TrieNode()
{
	HasValue = false;
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
