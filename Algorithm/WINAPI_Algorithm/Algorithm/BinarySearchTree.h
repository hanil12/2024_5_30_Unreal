#pragma once

#include <iostream>

using namespace std;

struct Node
{
	Node() {}
	Node(int key) : key(key) {}

	Node* left = nullptr;
	Node* right = nullptr;

	Node* parent = nullptr;

	int key = -1;
	int data = 0;
};

class BinarySearchTree
{
public:
	BinarySearchTree() {}
	~BinarySearchTree();

	void Insert(int key);
	void PrintTree(Node* node);

	Node* Search(Node* node, int key);
	Node* Min(Node* node);
	Node* Max(Node* node);

	void Delete(Node* node);

	Node* _root = nullptr;

private:
	Node* Previous(Node* node);
	Node* Next(Node* node);
	void Replace(Node* node1, Node* node2);
};