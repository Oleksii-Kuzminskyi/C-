#include "Tree.h"
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>


bool insert_node(Node* &root, const int value)
{
	if (!root)
	{
		root = new Node(value);
		return true;
	}

	bool insert_result = false;

	if (value >= root->value)
	{
		insert_result = insert_node(root->right, value);
	}
	else
	{
		insert_result = insert_node(root->left, value);
	}

	return insert_result;
}

void free_tree(Node* &root)
{
	if (!root)
	{
		return;
	}

	if (root->left)
	{
		free_tree(root->left);
	}
	if (root->right)
	{
		free_tree(root->right);
	}

	delete root;
	root = nullptr;
}

void print_node(const Node* root, std::ostream& os)
{
	if (!root)
	{
		return;
	}

	if (root->left)
	{
		print_node(root->left, os);
	}

	os << root->value << std::endl;

	if (root->right)
	{
		print_node(root->right, os);
	}
}

bool check_order(const Node* root)
{
	if (!root)
	{
		return false;
	}

	std::ofstream outfile("order.txt", std::ios_base::out);
	if (!outfile.is_open())
	{
		return false;
	}
	print_node(root, outfile);
	outfile.close();


	std::ifstream infile("order.txt", std::ios_base::in);
	if (!infile.is_open())
	{
		return false;
	}
	std::vector<int> TreeElements;
	while (!infile.eof())
	{
		std::string temp;
		std::getline(infile, temp);
		if (temp.empty())
		{
			continue;
		}
		TreeElements.push_back(std::stoi(temp));
	}
	infile.close();

	return std::is_sorted(TreeElements.begin(), TreeElements.end());
}



static Node* min_node(Node* root)
{
	Node* temp = root;
	while (temp && temp->left)
	{
		temp = temp->left;
	}
	return temp;
}

static bool remove_min(Node * &root)
{
	if (!root)
	{
		return false;
	}

	if (root->left)
	{
		return remove_min(root->left);
	}

	//in case minimal element has right child
	Node* temp = root->right;
	delete root;
	root = temp;
	temp = nullptr;

	return true;
}


bool remove_node(Node* &root, const int removal_value)
{
	if (!root)
	{
		return false;
	}

	if (removal_value < root->value)
	{
		return remove_node(root->left, removal_value);
	}
	else if (removal_value > root->value)
	{
		return remove_node(root->right, removal_value);
	}

	//else found desired element to remove

	//case 1: element is leaf
	if (!root->left && !root->right)
	{
		delete root;
		root = nullptr;
		return true;
	}

	//case 2.1: element has one left child
	if (root->left && !root->right)
	{
		Node* temp = root->left;
		delete root;
		root = temp;
		temp = nullptr;
		return true;
	}
	//case 2.2: element has one right child
	if (!root->left && root->right)
	{
		Node* temp = root->right;
		delete root;
		root = temp;
		temp = nullptr;
		return true;
	}

	//case 3: element has two children
	if (root->left && root->right)
	{
		//find min element in right sub-tree
		Node* min = min_node(root->right);

		//copy value of min to root
		root->value = min->value;

		remove_min(root->right);
		min = nullptr;

		//hip hip hooray
		return true;
	}


	return false;
}


bool is_valid(const Node* root)
{
	if (!root)
	{
		return true;
	}


	if (root->left)
	{
		if (root->value <= root->left->value)
		{
			return false;
		}
		if (!is_valid(root->left))
		{
			return false;
		}
	}

	if (root->right)
	{
		if (root->value > root->right->value)
		{
			return false;
		}
		if (!is_valid(root->right))
		{
			return false;
		}
	}

	return true;
}


bool is_same(const Node* root1, const Node* root2)
{
	if (!root1 && !root2)
	{
		return true;
	}

	if ((!root1 && root2) || (root1 && !root2))
	{
		return false;
	}

	if (root1->value != root2->value)
	{
		return false;
	}

	
	return (is_same(root1->left, root2->left) && is_same(root1->right, root2->right));
}
