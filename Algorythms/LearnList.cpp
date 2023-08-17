#include "LearnList.h"
#include <assert.h>
#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <queue>
#include <set>

struct LinkedListNode
{
	int value = 0;
	LinkedListNode* next = nullptr;
};

struct LinkedList
{
	LinkedListNode* head = nullptr;
};

void AddNode(LinkedList& list, int value)
{
	// Find last node
	LinkedListNode** node = &list.head;
	while (*node != nullptr)
	{
		node = &(*node)->next;
	}

	*node = new LinkedListNode;
	(*node)->value = value;
	(*node)->next = nullptr;
}

int& GetNodeValue(LinkedList& list, int index)
{
	LinkedListNode* node = list.head;
	for (int i = 0; i < index; i++)
	{
		node = node->next;
		assert(node != nullptr); // Out of range
	}
	return node->value;
}

int GetListLength(LinkedList& list)
{
	int length = 0;
	LinkedListNode* node = list.head;
	while (node != nullptr)
	{
		length++;
		node = node->next;
	}
	return length;
}

void RemoveNode(LinkedList& list, int index)
{
	LinkedListNode** node = &list.head;
	for (int i = 0; i < index; i++)
	{
		node = &(*node)->next;
		assert(*node != nullptr); // Out of range
	}
	LinkedListNode* next = (*node)->next;
	delete *node;
	*node = next;
}

void EraseList(LinkedList& list)
{
	LinkedListNode* node = list.head;
	while (node != nullptr)
	{
		LinkedListNode* next = node->next;
		delete node;
		node = next;
	}
	list.head = nullptr;
}

void PrintList(const LinkedList& list)
{
	LinkedListNode* node = list.head;
	while (node != nullptr)
	{
		std::cout << node->value << " ";
		node = node->next;
	};
}

void LearnHandMadeList()
{
	std::cout << "LearnHandMadeList" << std::endl;

	std::cout << "New list: ";
	LinkedList list;
	for (int i = 0; i < 10; i++)
	{
		AddNode(list, i);
	}
	PrintList(list);
	std::cout << std::endl;

	std::cout << "Get node 5 value: ";
	int& value = GetNodeValue(list, 5);
	std::cout << value << std::endl;

	std::cout << "Change node 5 value to 100: ";
	value = 100;
	PrintList(list);
	std::cout << std::endl;

	std::cout << "Remove node 5: ";
	RemoveNode(list, 5);
	PrintList(list);
	std::cout << std::endl;

	std::cout << "List length: " << GetListLength(list) << std::endl;
	EraseList(list);
	
	std::cout << std::endl;
}

void PrintStdList(const std::list<int>& list)
{
	for (int i : list)
	{
		std::cout << i << " ";
	}
}

void LearnSTLList()
{
	std::cout << "LearnSTLList" << std::endl;

	std::list<int> list = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	std::cout << "New list: ";
	PrintStdList(list);
	std::cout << std::endl;

	std::cout << "Get node 5 value: ";
	std::list<int>::iterator it = list.begin();
	for (int i = 0; i < 5; i++)
	{
		it++;
	}
	std::cout << *it << std::endl;

	std::cout << "Change node 5 value to 100: ";
	*it = 100;
	PrintStdList(list);
	std::cout << std::endl;


	std::cout << "Insert node 5: ";
	list.insert(it, 43);
	PrintStdList(list);
	std::cout << std::endl;

	// it is invalid now

	std::cout << "Remove node 5: ";
	it = list.begin();
	for (int i = 0; i < 5; i++)
	{
		it++;
	}
	list.erase(it);
	PrintStdList(list);
	std::cout << std::endl;

	std::cout << "List length: " << list.size() << std::endl;

	std::cout << "Add node at the end: ";
	list.push_back(1000);
	PrintStdList(list);
	std::cout << std::endl;

	std::cout << "Add node at the begin: ";
	list.push_front(-1000);
	PrintStdList(list);
	std::cout << std::endl;

	std::cout << "Remove node at the end: ";
	list.pop_back();
	PrintStdList(list);
	std::cout << std::endl;

	std::cout << "Remove node at the begin: ";
	list.pop_front();
	PrintStdList(list);
	std::cout << std::endl;

	std::cout << "Swap list: ";
	std::list<int> list2 = { 100, 200, 300 };
	list.swap(list2);
	PrintStdList(list);

	std::cout << std::endl;
}

struct FamilyTreeNode
{
	std::string name;
	FamilyTreeNode* parent = nullptr;
	FamilyTreeNode* spouse = nullptr;
	std::vector<FamilyTreeNode*> children;
};

void AddChild(FamilyTreeNode& parent, const std::string& name)
{
	FamilyTreeNode* child = new FamilyTreeNode;
	child->name = name;
	child->parent = &parent;
	parent.children.push_back(child);
}

void AddSpouse(FamilyTreeNode& node, const std::string& name)
{
	FamilyTreeNode* spouse = new FamilyTreeNode;
	spouse->name = name;
	spouse->spouse = &node;
	node.spouse = spouse;
}

void PrintFamilyTreeNode(const FamilyTreeNode& node, int level)
{
	for (int i = 0; i < level; i++)
	{
		std::cout << "  ";
	}
	std::cout << node.name;
	if (node.spouse != nullptr)
	{
		std::cout << " + " << node.spouse->name;
	}
	std::cout << std::endl;
}

void PrintFamilyTree(const FamilyTreeNode& node, int level = 0)
{
	PrintFamilyTreeNode(node, level);
	for (FamilyTreeNode* child : node.children)
	{
		PrintFamilyTree(*child, level + 1);
	}
}

void DeleteFamilyTree(FamilyTreeNode& node)
{
	for (FamilyTreeNode* child : node.children)
	{
		DeleteFamilyTree(*child);
	}
	delete &node;
}

void LearnFamilyTree()
{
	std::cout << "LearnFamilyTree" << std::endl;
	FamilyTreeNode* root = new FamilyTreeNode;
	root->name = "Ivan";
	AddChild(*root, "Petr");
	AddChild(*root, "Sergey");
	AddChild(*root, "Olga");
	AddSpouse(*root->children[0], "Anna");
	AddChild(*root->children[0], "Vasya");
	AddChild(*root->children[0], "Masha");
	AddChild(*root->children[0], "Dasha");
	AddSpouse(*root->children[1], "Natalya");
	AddChild(*root->children[1], "Vanya");
	AddChild(*root->children[1], "Sasha");
	AddChild(*root->children[1], "Pasha");
	AddSpouse(*root->children[2], "Irina");
	AddChild(*root->children[2], "Vova");
	AddChild(*root->children[2], "Sveta");
	AddChild(*root->children[2], "Lena");
	PrintFamilyTree(*root);
	DeleteFamilyTree(*root);
	std::cout << std::endl;	
}


struct CityGraphNode
{
	std::string name;
	std::vector<CityGraphNode*> neighbours;
};

void LinkNodes(CityGraphNode& left, CityGraphNode& right)
{
	left.neighbours.push_back(&right);
	right.neighbours.push_back(&left);
}

void PrintGraph(CityGraphNode* start)
{
	// BFS algorythm

	std::queue<CityGraphNode*> q;
	std::set<CityGraphNode*> visited; // We will learn sets later

	q.push(start);
	visited.insert(start);

	while (!q.empty())
	{
		CityGraphNode* city = q.front();
		q.pop();

		std::cout << city->name << " -> ";

		for (CityGraphNode* neighbour : city->neighbours)
		{
			std::cout << neighbour->name << " ";
			if (visited.find(neighbour) == visited.end())
			{
				q.push(neighbour);
				visited.insert(neighbour);
			}
		}
		std::cout << "\n";
	}
}

std::vector<CityGraphNode*> FindPath(CityGraphNode& from, CityGraphNode& to)
{
	// BFS algorythm (finds shortest route)
	std::vector<CityGraphNode*> path;

	std::queue<CityGraphNode*> frontier;
	std::map<CityGraphNode*, CityGraphNode*> cameFrom; // We will learn maps later

	frontier.push(&from);

	cameFrom[&from] = nullptr;

	while (!frontier.empty())
	{
		CityGraphNode* current = frontier.front();
		frontier.pop();

		if (current == &to)
		{
			std::vector<CityGraphNode*> path;
			while (current != nullptr)
			{
				path.push_back(current);
				current = cameFrom[current];
			}
			std::reverse(path.begin(), path.end());
			return path;
		}

		for (CityGraphNode* next : current->neighbours)
		{
			if (cameFrom.find(next) == cameFrom.end())
			{
				frontier.push(next);
				cameFrom[next] = current;
			}
		}
	}

	// No path found, return empty path
	return {};
}

void PrintRoute(const std::vector<CityGraphNode*>& route)
{
	for (CityGraphNode* node : route)
	{
		std::cout << node->name;
		if (node != route.back())
		{
			std::cout << " -> ";
		}
	}
}

void LearnGraph()
{
	std::cout << "Learn graph" << std::endl;

	CityGraphNode moscow = { "Moscow" };
	CityGraphNode voronezh = { "Voronezh" };
	CityGraphNode tula = { "Tula" };
	CityGraphNode saintPetersburg = { "Saint Petersburg" };
	CityGraphNode smolensk = { "Smolensk" };
	LinkNodes(moscow, tula);
	LinkNodes(tula, saintPetersburg);
	LinkNodes(moscow, smolensk);
	LinkNodes(moscow, voronezh);
	PrintGraph(&voronezh);

	std::cout << "Route from Voronezh to Saint Petersburg: ";
	PrintRoute(FindPath(voronezh, saintPetersburg));
	std::cout << std::endl;

	std::cout << "Route from Tula to Smolensk: ";
	PrintRoute(FindPath(tula, smolensk));
	std::cout << std::endl;

	std::cout << std::endl;
}

void LearnList()
{
	std::cout << "LearnList" << std::endl;

	LearnHandMadeList();
	LearnSTLList();
	LearnFamilyTree();
	LearnGraph();

	std::cout << std::endl;
}
