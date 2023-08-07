#include "LearnUnorderedMap.h"
#include <iostream>
#include <unordered_map>

struct MyVector
{
	int x;
	int y;
};

// We need to define hash function and comparator for our key
bool operator==(const MyVector& lhs, const MyVector& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

// We will learn about functional objects later
template<>
struct std::hash<MyVector>
{
	std::size_t operator()(const MyVector& key) const
	{
		return std::hash<int>()(key.x) ^ (std::hash<int>()(key.y) << 1); // We need to combine hashes somehow
	}
};

void LearnStdUnorderedMap()
{
	std::cout << "Learn std::unordered_map" << std::endl;

	std::unordered_map<MyVector, std::string> namedPoints = 
	{
		{ { 0, 0 }, "Origin" },
		{ { 1, 0 }, "Point 1" },
		{ { 0, 1 }, "Point 2" },
		{ { 1, 1 }, "Point 3" },
	};
	
	// We can use operator[] to get value by key
	std::cout << "namedPoints[{0, 0}] = " << namedPoints[{0, 0}] << std::endl;
	std::cout << "namedPoints[{1, 0}] = " << namedPoints[{1, 0}] << std::endl;

	// unordered map is not sorted
	for (const auto& item: namedPoints)
	{
		std::cout << "namedPoints[{ " << item.first.x << ", " << item.first.y << " }] = " << item.second << std::endl;
	}

	// Mostly the same as std::map

	std::cout << std::endl;
}

const int HASH_TABLE_SIZE = 100;

struct HashTableNode
{
	std::string key;
	std::string value;
	HashTableNode* next = nullptr;
};

struct HashTable
{
	HashTableNode* nodes[HASH_TABLE_SIZE] = { nullptr };
};

int GetHash(const std::string& key)
{
	int hash = 0;
	for (char c : key)
	{
		hash += c;
	}
	return hash % HASH_TABLE_SIZE;
}

// Complexity: O(1)
void AddToHashTable(HashTable& hashTable, const std::string& key, const std::string& value)
{
	int hash = GetHash(key);
	HashTableNode* node = hashTable.nodes[hash];
	if (node == nullptr)
	{
		node = new HashTableNode();
		node->key = key;
		node->value = value;
		hashTable.nodes[hash] = node;
	}
	else
	{
		while (node->next != nullptr)
		{
			node = node->next;
		}
		node->next = new HashTableNode();
		node->next->key = key;
		node->next->value = value;
	}
}

// Complexity: O(1)
std::string GetFromHashTable(const HashTable& hashTable, const std::string& key)
{
	int hash = GetHash(key);
	HashTableNode* node = hashTable.nodes[hash];
	while (node != nullptr)
	{
		if (node->key == key)
		{
			return node->value;
		}
		node = node->next;
	}
	return "";
}

void PrintHashTable(const HashTable& hashTable)
{
	for (int i = 0; i < HASH_TABLE_SIZE; ++i)
	{
		HashTableNode* node = hashTable.nodes[i];
		while (node != nullptr)
		{
			std::cout << node->key << ": " << node->value << std::endl;
			node = node->next;
		}
	}
}

// Complexity: O(1)
void RemoveFromHashTable(HashTable& hashTable, const std::string& key)
{
	int hash = GetHash(key);
	HashTableNode* node = hashTable.nodes[hash];
	if (node == nullptr)
	{
		return;
	}
	if (node->key == key)
	{
		hashTable.nodes[hash] = node->next;
		delete node;
		return;
	}
	while (node->next != nullptr)
	{
		if (node->next->key == key)
		{
			HashTableNode* next = node->next->next;
			delete node->next;
			node->next = next;
			return;
		}
		node = node->next;
	}
}

void LearnHashTable()
{
	std::cout << "Learn hash table" << std::endl;

	HashTable hashTable;
	AddToHashTable(hashTable, "key1", "value1");
	AddToHashTable(hashTable, "key2", "value2");
	AddToHashTable(hashTable, "key3", "value3");
	std::cout << "HashTable:" << std::endl;
	PrintHashTable(hashTable);

	std::cout << "hey1 = " << GetFromHashTable(hashTable, "key1") << std::endl;

	RemoveFromHashTable(hashTable, "key2");
	std::cout << "HashTable:" << std::endl;
	PrintHashTable(hashTable);

	std::cout << std::endl;
}

void LearnUnorderedMap()
{
	std::cout << "Learn unordered_map" << std::endl;

	LearnStdUnorderedMap();
	LearnHashTable();

	std::cout << std::endl;
}
