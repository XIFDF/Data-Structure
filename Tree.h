#pragma once
#include <vector>
namespace dataStructure{
class Node
{
public:
	Node() :val(0), left(nullptr), right(nullptr) {}; 
	Node(int val) :val(val), left(nullptr), right(nullptr) {};
	Node(int& val, Node* left, Node* right) :val(val), left(left), right(right) {};
	~Node() = default;

	int val;
	Node* left;
	Node* right;
};

class Tree
{
public:
	Tree() :total(0), root(nullptr) {};
	~Tree() = default;

	void add(Node*& root, Node* newNode)
	{
		if (root == nullptr) {
			root = newNode;
			total++;
			return;
		}
		if (root->val > newNode->val) {
			add(root->left, newNode);
		}
		else {
			add(root->right, newNode);
		}
	}
	void add(Node* newNode) {
		add(this->root, newNode);
	}

	void LdrRecursion(Node* root, std::vector<int>& result) {
		if (root == nullptr) {
			return;
		}
		LdrRecursion(root->left, result);
		result.push_back(root->val);
		LdrRecursion(root->right, result);
	}

	void LdrRecursion(std::vector<int>& result) {
		LdrRecursion(root, result);
	}
private:
	int total;
	Node* root;
};

}