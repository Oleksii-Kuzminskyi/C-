#include <sstream>
#include "gtest/gtest.h"
#include "Tree.h"
#include "MemLeakDetector.h"


TEST(BST, Memory_Insert_One)
{
	MemoryLeakDetector leak_guard;
	Node* root = nullptr;

	EXPECT_TRUE(insert_node(root, 5));
	EXPECT_TRUE(root != nullptr);
	EXPECT_TRUE(root->value == 5);

	free_tree(root);
}

TEST(BST, Memory_Insert_Two1)
{
	MemoryLeakDetector leak_guard;
	Node* root = nullptr;

	EXPECT_TRUE(insert_node(root, 4));
	EXPECT_TRUE(insert_node(root, 3));

	EXPECT_TRUE(root != nullptr);
	EXPECT_TRUE(root->value == 4);

	EXPECT_TRUE(root->left != nullptr);
	EXPECT_TRUE(root->left->value == 3);

	free_tree(root);
}

TEST(BST, Memory_Insert_Two2)
{
	MemoryLeakDetector leak_guard;
	Node* root = nullptr;

	EXPECT_TRUE(insert_node(root, 4));
	EXPECT_TRUE(insert_node(root, 6));

	EXPECT_TRUE(root != nullptr);
	EXPECT_TRUE(root->value == 4);

	EXPECT_TRUE(root->right != nullptr);
	EXPECT_TRUE(root->right->value == 6);

	free_tree(root);
}

TEST(BST, Memory_Insert_Three)
{
	MemoryLeakDetector leak_guard;
	Node* root = nullptr;

	EXPECT_TRUE(insert_node(root, 4));
	EXPECT_TRUE(insert_node(root, 3));
	EXPECT_TRUE(insert_node(root, 6));

	EXPECT_TRUE(root->left != nullptr);
	EXPECT_TRUE(root->left->value == 3);

	EXPECT_TRUE(root != nullptr);
	EXPECT_TRUE(root->value == 4);

	EXPECT_TRUE(root->right != nullptr);
	EXPECT_TRUE(root->right->value == 6);

	free_tree(root);
}

TEST(BST, Memory_Insert_Multiple)
{
	MemoryLeakDetector leak_guard;
	Node* root = nullptr;

	EXPECT_TRUE(insert_node(root, 4));
	EXPECT_TRUE(insert_node(root, 3));
	EXPECT_TRUE(insert_node(root, 6));
	EXPECT_TRUE(insert_node(root, 5));
	EXPECT_TRUE(insert_node(root, 2));
	EXPECT_TRUE(insert_node(root, 9));
	EXPECT_TRUE(insert_node(root, 7));
	EXPECT_TRUE(insert_node(root, 8));

	free_tree(root);
}


TEST(BST, Check_Order_Empty)
{
	MemoryLeakDetector leak_guard;
	Node* root = nullptr;
	EXPECT_TRUE(check_order(root) == false);
}

TEST(BST, Check_Order_OneEl)
{
	MemoryLeakDetector leak_guard;
	Node* root = nullptr;

	EXPECT_TRUE(insert_node(root, 4));
	EXPECT_TRUE(check_order(root) == true);

	free_tree(root);
}

TEST(BST, Check_Order_TwoEl)
{
	MemoryLeakDetector leak_guard;
	Node* root = nullptr;

	EXPECT_TRUE(insert_node(root, 4));
	EXPECT_TRUE(insert_node(root, 3));
	EXPECT_TRUE(insert_node(root, 6));

	EXPECT_TRUE(check_order(root) == true);

	free_tree(root);
}

TEST(BST, Check_Order_ThreeEl)
{
	MemoryLeakDetector leak_guard;
	Node* root = nullptr;

	EXPECT_TRUE(insert_node(root, 4));
	EXPECT_TRUE(insert_node(root, 3));
	EXPECT_TRUE(insert_node(root, 6));
	EXPECT_TRUE(check_order(root) == true);

	free_tree(root);
}

TEST(BST, Check_Order_Multiple)
{
	MemoryLeakDetector leak_guard;
	Node* root = nullptr;

	EXPECT_TRUE(insert_node(root, 4));
	EXPECT_TRUE(insert_node(root, 3));
	EXPECT_TRUE(insert_node(root, 6));
	EXPECT_TRUE(insert_node(root, 5));
	EXPECT_TRUE(insert_node(root, 2));
	EXPECT_TRUE(insert_node(root, 9));
	EXPECT_TRUE(insert_node(root, 7));
	EXPECT_TRUE(insert_node(root, 8));
	EXPECT_TRUE(check_order(root) == true);

	free_tree(root);
}


TEST(BST, Remove_Leaf)
{
	MemoryLeakDetector leak_guard;
	Node* root = nullptr;

	EXPECT_TRUE(insert_node(root, 4));
	EXPECT_TRUE(remove_node(root, 4));

	EXPECT_TRUE(root == nullptr);

	free_tree(root);
}

TEST(BST, Remove_LeftChild)
{
	MemoryLeakDetector leak_guard;
	Node* root = nullptr;

	EXPECT_TRUE(insert_node(root, 4));
	EXPECT_TRUE(insert_node(root, 3));
	EXPECT_TRUE(remove_node(root, 3));

	EXPECT_TRUE(root->value == 4);

	EXPECT_TRUE(check_order(root) == true);

	free_tree(root);
}

TEST(BST, Remove_RightChild)
{
	MemoryLeakDetector leak_guard;
	Node* root = nullptr;

	EXPECT_TRUE(insert_node(root, 4));
	EXPECT_TRUE(insert_node(root, 3));
	EXPECT_TRUE(insert_node(root, 6));
	EXPECT_TRUE(remove_node(root, 6));

	EXPECT_TRUE(root->value == 4);

	EXPECT_TRUE(check_order(root) == true);

	free_tree(root);
}

TEST(BST, Remove_Root_WithChildren)
{
	MemoryLeakDetector leak_guard;
	Node* root = nullptr;

	EXPECT_TRUE(insert_node(root, 4));
	EXPECT_TRUE(insert_node(root, 3));
	EXPECT_TRUE(insert_node(root, 6));
	EXPECT_TRUE(remove_node(root, 4));

	EXPECT_TRUE(root != nullptr);
	EXPECT_TRUE(root->value == 6);

	EXPECT_TRUE(root->left != nullptr);
	EXPECT_TRUE(root->left->value == 3);

	EXPECT_TRUE(root->right == nullptr);

	EXPECT_TRUE(check_order(root) == true);

	free_tree(root);
}


TEST(BST, Remove_Case4)
{
	MemoryLeakDetector leak_guard;
	Node* root = nullptr;

	EXPECT_TRUE(insert_node(root, 4));
	EXPECT_TRUE(insert_node(root, 3));
	EXPECT_TRUE(insert_node(root, 6));
	EXPECT_TRUE(insert_node(root, 5));
	EXPECT_TRUE(insert_node(root, 2));
	EXPECT_TRUE(insert_node(root, 9));
	EXPECT_TRUE(insert_node(root, 7));
	EXPECT_TRUE(insert_node(root, 8));
	EXPECT_TRUE(insert_node(root, 20));
	EXPECT_TRUE(insert_node(root, 10));

	EXPECT_TRUE(remove_node(root, 4));
	EXPECT_TRUE(check_order(root) == true);


	free_tree(root);
}

TEST(BST, Remove_Case5)
{
	MemoryLeakDetector leak_guard;
	Node* root = nullptr;

	EXPECT_TRUE(insert_node(root, 4));
	EXPECT_TRUE(insert_node(root, 3));
	EXPECT_TRUE(insert_node(root, 6));
	EXPECT_TRUE(insert_node(root, 5));
	EXPECT_TRUE(insert_node(root, 2));
	EXPECT_TRUE(insert_node(root, 9));
	EXPECT_TRUE(insert_node(root, 7));
	EXPECT_TRUE(insert_node(root, 8));
	EXPECT_TRUE(insert_node(root, 20));
	EXPECT_TRUE(insert_node(root, 10));

	EXPECT_TRUE(remove_node(root, 6));
	EXPECT_TRUE(check_order(root) == true);


	free_tree(root);
}


TEST(BST, Remove_Case6)
{
	MemoryLeakDetector leak_guard;
	Node* root = nullptr;

	EXPECT_TRUE(insert_node(root, 4));
	EXPECT_TRUE(insert_node(root, 3));
	EXPECT_TRUE(insert_node(root, 6));
	EXPECT_TRUE(insert_node(root, 5));
	EXPECT_TRUE(insert_node(root, 2));
	EXPECT_TRUE(insert_node(root, 9));
	EXPECT_TRUE(insert_node(root, 7));
	EXPECT_TRUE(insert_node(root, 8));
	EXPECT_TRUE(insert_node(root, 20));
	EXPECT_TRUE(insert_node(root, 10));

	EXPECT_TRUE(remove_node(root, 20));
	EXPECT_TRUE(check_order(root) == true);


	free_tree(root);
}

TEST(BST, Remove_UnexistingEl)
{
	MemoryLeakDetector leak_guard;
	Node* root = nullptr;

	EXPECT_TRUE(insert_node(root, 4));
	EXPECT_TRUE(insert_node(root, 3));
	EXPECT_TRUE(insert_node(root, 6));
	EXPECT_TRUE(insert_node(root, 5));
	EXPECT_TRUE(insert_node(root, 2));
	EXPECT_TRUE(insert_node(root, 9));
	EXPECT_TRUE(insert_node(root, 7));
	EXPECT_TRUE(insert_node(root, 8));
	EXPECT_TRUE(insert_node(root, 20));
	EXPECT_TRUE(insert_node(root, 10));

	EXPECT_TRUE(remove_node(root, 23) == false);
	EXPECT_TRUE(check_order(root) == true);


	free_tree(root);
}

TEST(BST, Remove_TwiceSameElement)
{
	MemoryLeakDetector leak_guard;
	Node* root = nullptr;

	EXPECT_TRUE(insert_node(root, 4));
	EXPECT_TRUE(insert_node(root, 3));
	EXPECT_TRUE(insert_node(root, 6));
	EXPECT_TRUE(insert_node(root, 5));
	EXPECT_TRUE(insert_node(root, 2));
	EXPECT_TRUE(insert_node(root, 9));
	EXPECT_TRUE(insert_node(root, 7));
	EXPECT_TRUE(insert_node(root, 8));
	EXPECT_TRUE(insert_node(root, 20));
	EXPECT_TRUE(insert_node(root, 10));

	EXPECT_TRUE(remove_node(root, 7));
	EXPECT_TRUE(remove_node(root, 7) == false);
	EXPECT_TRUE(check_order(root) == true);


	free_tree(root);
}



TEST(BST, IsSame_ALL_NULL)
{
	MemoryLeakDetector leak_guard;
	Node* root1 = nullptr;
	Node* root2 = nullptr;


	EXPECT_TRUE(is_same(root1, root2) == true);

	free_tree(root1);
	free_tree(root2);
}


TEST(BST, IsSame_R1_AND_NOT_R2)
{
	MemoryLeakDetector leak_guard;
	Node* root1 = nullptr;
	Node* root2 = nullptr;

	insert_node(root1, 5);
	EXPECT_TRUE(is_same(root1, root2) == false);

	free_tree(root1);
	free_tree(root2);
}


TEST(BST, IsSame_NOT_R1_AND_R2)
{
	MemoryLeakDetector leak_guard;
	Node* root1 = nullptr;
	Node* root2 = nullptr;

	insert_node(root2, 5);
	EXPECT_TRUE(is_same(root1, root2) == false);

	free_tree(root1);
	free_tree(root2);
}

TEST(BST, IsSame_R1_AND_R2)
{
	MemoryLeakDetector leak_guard;
	Node* root1 = nullptr;
	Node* root2 = nullptr;

	insert_node(root1, 5);
	insert_node(root2, 5);
	EXPECT_TRUE(is_same(root1, root2) == true);

	free_tree(root1);
	free_tree(root2);
}

TEST(BST, IsSame_EQ_INSERTION)
{
	MemoryLeakDetector leak_guard;
	Node* root1 = nullptr;
	Node* root2 = nullptr;

	insert_node(root1, 5);
	insert_node(root1, 1);
	insert_node(root1, 9);
	insert_node(root1, 8);
	insert_node(root1, 15);


	insert_node(root2, 5);
	insert_node(root2, 1);
	insert_node(root2, 9);
	insert_node(root2, 8);
	insert_node(root2, 15);


	EXPECT_TRUE(is_same(root1, root2) == true);

	free_tree(root1);
	free_tree(root2);
}


TEST(BST, IsSame_NOT_EQ_INSERTION)
{
	MemoryLeakDetector leak_guard;
	Node* root1 = nullptr;
	Node* root2 = nullptr;

	insert_node(root1, 5);
	insert_node(root1, 1);
	insert_node(root1, 9);
	insert_node(root1, 8);
	insert_node(root1, 15);


	insert_node(root2, 9);
	insert_node(root2, 15);
	insert_node(root2, 8);
	insert_node(root2, 5);
	insert_node(root2, 1);


	EXPECT_TRUE(is_same(root1, root2) == false);

	free_tree(root1);
	free_tree(root2);
}