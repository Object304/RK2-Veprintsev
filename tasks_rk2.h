#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <list>
#include <queue>
#include <string>

struct Node {
	Node();
	Node(int nameNode);
	~Node();

	Node* parent;
	std::list<Node*> listChilds;
	int name;
	static int countNodes;
};

class Graph {
private:
	Node* head;
	//void buildBFS(Node*& Tree, int countNodes);

	int _buildTreeBFS(int countNodes);
	void findEl();
	void _BFS();
	void Destruct();

	//����� ����� ������ ����� �������, ������� ����� ������������
public:
	Graph();
	Graph(int countNodes);
	~Graph();
	/*
		output		:	-1 - ���� ������� �� �����������
					:	������������� ����� -- ����� �����
		author		:
		date		:
	*/
	int buildTreeBFS(int countNodes);
	/*
		output		:	-1 - ���� ������� �� �����������
					:	������������� ����� -- ����� �����
		author		:
		date		:
	*/
	int buildTreeDFS(int countNodes);

	void BFS();
	void DFS();
	/*
		description	:	������� ������ ���� �� ��� �����
		input 		:	nameNode -- ��� ����
		output		:	{bool -- ���� �����, list<int> -- ������ ��� ����� �� ������������}
		description	:	��������� DFS -- ����� � �������, BSF -- ����� � ������
		author		:
		date		:
	*/
	std::pair<bool, std::list<int>> searchDFS(int nameNode);
	std::pair<bool, std::list<int>> searchBFS(int nameNode);
};
