#ifndef TREE_H_
#define TREE_H_
#include <iostream>

struct Node
{
	Node* left;
	Node* right;
	int value;
	Node(int newvalue = 0)
	{
		left = right = nullptr;
		value = newvalue;
	}
};

bool insert_node(Node* &root, const int value);
void free_tree(Node* &root);
void print_node(const Node* root, std::ostream& os);
bool check_order(const Node* root);

bool remove_node(Node* &root, const int removal_value);
bool is_same(const Node * root1, const Node * root2);
bool is_valid(const Node * root);


#endif
