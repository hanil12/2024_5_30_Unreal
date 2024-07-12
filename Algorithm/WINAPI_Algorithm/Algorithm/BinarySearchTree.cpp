#include "BinarySearchTree.h"

BinarySearchTree::~BinarySearchTree()
{
	// TODO : 노드들 삭제 필요
}

void BinarySearchTree::Insert(int key)
{
	Node* newNode = new Node(key);

	if (_root == nullptr)
	{
		_root = newNode;
		return;
	}

	Node* node = _root;
	Node* parent = nullptr;

	// 자리 찾기, 부모 찾기
	while (true)
	{
		if(node == nullptr)
			break;

		parent = node;
		if (key < node->key)
		{
			node = node->left;
		}
		else
		{
			node = node->right;
		}
	}

	newNode->parent = parent;
	if (key < parent->key)
	{
		parent->left = newNode;
	}
	else
	{
		parent->right = newNode;
	}
}

void BinarySearchTree::PrintTree(Node* node)
{
	if(node == nullptr)
		return;

	// Tree의 전위순회 : 부모 - 왼쪽 자식들 - 오른쪽 자식들
	// Tree의 중위순회 : 왼쪽 자식들 - 부모 - 오른쪽 자식들
	// Tree의 후위순회 : 왼쪽 자식들 - 오른쪽 자식들 - 부모
	cout << node->key << endl;
	PrintTree(node->left);
	PrintTree(node->right);
}

Node* BinarySearchTree::Search(Node* node, int key)
{
	if(node == nullptr)
		return nullptr;

	if(key == node->key)
		return node;

	if(key < node->key)
		return Search(node->left, key);
	else
		return Search(node->right, key);

	return nullptr;
}

Node* BinarySearchTree::Min(Node* node)
{
	if(node == nullptr)
		return nullptr;

	if(node->left != nullptr)
		return Min(node->left);

	return node;
}

Node* BinarySearchTree::Max(Node* node)
{
	if (node == nullptr)
		return nullptr;

	if (node->right != nullptr)
		return Max(node->right);

	return node;
}

Node* BinarySearchTree::Previous(Node* node)
{
	return nullptr;
}

Node* BinarySearchTree::Next(Node* node)
{
	return nullptr;
}

void BinarySearchTree::Delete(Node* node)
{
}

void BinarySearchTree::Replace(Node* node1, Node* node2)
{
}
