#include "LearnMap.h"
#include <iostream>
#include <map>
#include <unordered_map>

void PrintSTDMap(const std::map<std::string, std::string>& map)
{
	std::cout << "Map content:" << std::endl;
	// Items in the map are std::pair
	for (const std::pair<std::string, std::string>& item : map)
	{
		std::cout << item.first << ": " << item.second << std::endl;
	}
	std::cout << std::endl;
}

void LearnStdMap()
{
	// Init map with keys and values
	std::cout << "Learn std::map" << std::endl;
	std::map<std::string, std::string> phoneNumbers = 
	{
		{ "John", "555-1234" },
		{ "Jane", "555-1235" },
		{ "Joe", "555-1236" }
	};
	PrintSTDMap(phoneNumbers);

	std::cout << "Add Jill number" << std::endl;
	phoneNumbers["Jill"] = "555-1237";
	PrintSTDMap(phoneNumbers);

	std::cout << "Change Jane number" << std::endl;
	phoneNumbers["Jane"] = "555-9999";
	PrintSTDMap(phoneNumbers);

	// Find item
	std::cout << "Find Jane number" << std::endl;
	auto it = phoneNumbers.find("Jane");
	if (it != phoneNumbers.end())
	{
		std::cout << "Found Jane: " << it->second << std::endl;
	}
	else
	{
		std::cout << "Jane not found" << std::endl;
	}

	std::cout << "Erase Jane number" << std::endl;
	phoneNumbers.erase("Jane");
	PrintSTDMap(phoneNumbers);

	std::cout << "Clear map" << std::endl;
	phoneNumbers.clear();
	PrintSTDMap(phoneNumbers);
	
	std::cout << std::endl;
}

void LearnMultimap()
{
	std::cout << "Learn std::multimap" << std::endl;

	std::multimap<std::string, std::string> phoneNumbers =
	{
		{ "John", "555-1234" },
		{ "John", "454-4554" },
		{ "Jane", "555-1237" }
	};

	std::cout << "Print all John numbers" << std::endl;
	auto range = phoneNumbers.equal_range("John");
	for (auto it = range.first; it != range.second; ++it)
	{
		std::cout << it->first << ": " << it->second << std::endl;
	}

	std::cout << "Remove one of the John numbers" << std::endl;
	auto it = phoneNumbers.find("John");

	if (it != phoneNumbers.end())
	{
		phoneNumbers.erase(it);
	}

	std::cout << "Print all John numbers" << std::endl;
	range = phoneNumbers.equal_range("John");
	for (auto it = range.first; it != range.second; ++it)
	{
		std::cout << it->first << ": " << it->second << std::endl;
	}

	std::cout << std::endl;
}

// std::map is based on balanced binary tree
struct BinaryTreeNode
{
	std::string key;
	std::string value;

	int height = 0;

	// We need parent to be able to remove node from tree
	BinaryTreeNode* parent = nullptr;

	// Left is always less than current node
	BinaryTreeNode* left = nullptr;

	// Right is always greater than current node
	BinaryTreeNode* right = nullptr;
};

struct BinaryTree
{
	BinaryTreeNode* head = nullptr;
};

int GetHeight(BinaryTreeNode* node)
{
	if (node == nullptr)
		return 0;

	return node->height;
}

int GetNodeBalance(BinaryTreeNode* N) {
	if (N == nullptr)
		return 0;
	return GetHeight(N->left) - GetHeight(N->right);
}

BinaryTreeNode* RotateRight(BinaryTreeNode* y)
{
	BinaryTreeNode* x = y->left;
	BinaryTreeNode* T2 = x->right;
	// Perform rotation
	x->right = y;
	y->left = T2;
	// Update heights
	y->height = std::max(GetHeight(y->left), GetHeight(y->right)) + 1;
	x->height = std::max(GetHeight(x->left), GetHeight(x->right)) + 1;
	// Return new root
	return x;
}

BinaryTreeNode* RotateLeft(BinaryTreeNode* x)
{
	BinaryTreeNode* y = x->right;
	BinaryTreeNode* T2 = y->left;
	// Perform rotation
	y->left = x;
	x->right = T2;
	// Update heights
	x->height = std::max(GetHeight(x->left), GetHeight(x->right)) + 1;
	y->height = std::max(GetHeight(y->left), GetHeight(y->right)) + 1;
	// Return new root
	return y;
}

// Complexity O(log(n))
BinaryTreeNode* InsertToTree(BinaryTreeNode* node, const std::string& key, const std::string& value)
{
	if (node == nullptr)
	{
		BinaryTreeNode* newNode = new BinaryTreeNode();
		newNode->key = key;
		newNode->value = value;
		return newNode;
	}
	if (key < node->key)
	{
		node->left = InsertToTree(node->left, key, value);
	}
	else if (key > node->key)
	{
		node->right = InsertToTree(node->right, key, value);
	}
	else
	{
		// Duplicate keys are not allowed
		return node;
	}
	// Update height of this ancestor node
	node->height = 1 + std::max(GetHeight(node->left), GetHeight(node->right));
	// Get the balance factor of this ancestor node to check whether this node became unbalanced
	int balance = GetNodeBalance(node);
	// If this node becomes unbalanced, then there are 4 cases
	// Left Left Case
	if (balance > 1 && key < node->left->key)
		return RotateRight(node);
	// Right Right Case
	if (balance < -1 && key > node->right->key)
		return RotateLeft(node);
	// Left Right Case
	if (balance > 1 && key > node->left->key)
	{
		node->left = RotateLeft(node->left);
		return RotateRight(node);
	}
	// Right Left Case
	if (balance < -1 && key < node->right->key)
	{
		node->right = RotateRight(node->right);
		return RotateLeft(node);
	}
	// return the (unchanged) node pointer
	return node;
}

// Complexity O(log(n))
BinaryTreeNode* FindInTree(BinaryTreeNode* node, const std::string& key)
{
	if (node == nullptr)
		return nullptr;
	if (key < node->key)
	{
		return FindInTree(node->left, key);
	}
	else if (key > node->key)
	{
		return FindInTree(node->right, key);
	}
	else
	{
		return node;
	}
}

BinaryTreeNode* FindMin(BinaryTreeNode* node)
{
	if (node == nullptr)
	{
		return nullptr;
	}

	if (node->left == nullptr)
	{
		return node;
	}
		
	return FindMin(node->left);
}

// Complexity O(log(n))
BinaryTreeNode* RemoveFromTree(BinaryTreeNode* root, const std::string& key)
{
	if (root == nullptr)
	{
		return root;
	}

	if (key < root->key)
	{
		root->left = RemoveFromTree(root->left, key);
	}
	else if (key > root->key)
	{
		root->right = RemoveFromTree(root->right, key);
	}
	else 
	{
		if (root->left == nullptr || root->right == nullptr) 
		{
			BinaryTreeNode* temp = root->left ? root->left : root->right;

			if (temp == nullptr)
			{
				temp = root;
				root = nullptr;
			}
			else 
			{
				*root = *temp;
			}

			delete temp;
		}
		else 
		{
			BinaryTreeNode* temp = FindMin(root->right);
			root->key = temp->key;
			root->value = temp->value;
			root->right = RemoveFromTree(root->right, temp->key);
		}
	}

	if (root == nullptr)
	{
		return root;
	}
	
	root->height = 1 + std::max(GetHeight(root->left), GetHeight(root->right));

	int balance = GetNodeBalance(root);

	if (balance > 1) {
		if (GetNodeBalance(root->left) >= 0)
		{
			return RotateRight(root);
		}
		else 
		{
			root->left = RotateLeft(root->left);
			return RotateRight(root);
		}
	}

	if (balance < -1) 
	{
		if (GetNodeBalance(root->right) <= 0)
		{
			return RotateLeft(root);
		}	
		else 
		{
			root->right = RotateRight(root->right);
			return RotateLeft(root);
		}
	}

	return root;
}

void PrintTree(BinaryTreeNode* node)
{
	if (node == nullptr)
		return;
	PrintTree(node->left);
	std::cout << node->key << " " << node->value << std::endl;
	PrintTree(node->right);
}

void PrintBinaryTree(BinaryTree& tree)
{
	PrintTree(tree.head);
}

std::string& FindOrAddToBinaryTree(BinaryTree& tree, const std::string& key)
{
	BinaryTreeNode* node = FindInTree(tree.head, key);
	if (node == nullptr)
	{
		tree.head = InsertToTree(tree.head, key, "");
		node = FindInTree(tree.head, key);
	}
	return node->value;
}

void RemoveFromBinaryTree(BinaryTree& tree, const std::string& key)
{
	RemoveFromTree(tree.head, key);
}

void LearnBinaryTree()
{
	std::cout << "Learn binary tree" << std::endl;

	std::cout << "Fill binary tree" << std::endl;
	BinaryTree tree;
	FindOrAddToBinaryTree(tree, "Ann") = "555-1234";
	FindOrAddToBinaryTree(tree, "Lil") = "555-1235";
	FindOrAddToBinaryTree(tree, "Kane") = "555-1236";
	FindOrAddToBinaryTree(tree, "Jill") = "555-1237";
	FindOrAddToBinaryTree(tree, "Sally") = "555-9999";
	FindOrAddToBinaryTree(tree, "Bob") = "555-9998";
	FindOrAddToBinaryTree(tree, "Jack") = "555-1238";
	FindOrAddToBinaryTree(tree, "Zack") = "555-1237";
	PrintBinaryTree(tree);

	std::cout << "Remove some items from binary tree" << std::endl;
	RemoveFromBinaryTree(tree, "Ann");
	RemoveFromBinaryTree(tree, "Sally");
	RemoveFromBinaryTree(tree, "Jack");
	PrintBinaryTree(tree);

	std::cout << std::endl;
}

void LearnMap()
{
	std::cout << "Learn Map" << std::endl;

	LearnStdMap();
	LearnMultimap();
	LearnBinaryTree();

	std::cout << std::endl;
}
