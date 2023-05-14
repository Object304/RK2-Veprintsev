#include "tasks_rk2.h"
using namespace std;

int Node::countNodes = 0;

Node::Node() {
	parent = nullptr;
	name = countNodes;
	//countNodes++;
}

Node::Node(int nameNode) {
	parent = nullptr;
	name = countNodes;
	countNodes++;
}

Node::~Node() {

}

Graph::Graph() {
	head = nullptr;
}

Graph::Graph(int countNodes) {
	if ((countNodes & 0x01) == 0x00) {
		buildTreeBFS(countNodes);
		return;
	}
	if ((countNodes & 0x01) != 0x00) {
		buildTreeDFS(countNodes);
		return;
	}
	cout << "wrong input" << endl;
	head = nullptr;
}

Graph::~Graph() {
	delete head;
}

void Graph::buildBFS(Node*& el, int countNodes) {
	Node* child;
	for (int i = 0; i < countNodes; i++) {
		child = new Node(countNodes);
		child->parent = el;
		el->listChilds.push_back(child);
	}
	list<Node*>::iterator it = el->listChilds.begin();
	for (int i = 0; i < countNodes; i++) {
		buildBFS(*it, countNodes - 1);
	}
}

int Graph::buildTreeBFS(int countNodes) {
	Node* Tree = new Node(countNodes);
	buildBFS(Tree, countNodes);
	head = Tree;
	//head->parent = nullptr;
	Node::countNodes = 0;
	return 0;
}

int Graph::buildTreeDFS(int countNodes) {
	Node* Tree = new Node(countNodes);
	head = Tree;
	head->parent = nullptr;
	return 0;
}

void Graph::BFS() {

}

void Graph::DFS() {

}

std::pair<bool, std::list<int>> Graph::searchDFS(int nameNode) {

	return std::pair<bool, std::list<int>>();
}

std::pair<bool, std::list<int>> Graph::searchBFS(int nameNode) {

	return std::pair<bool, std::list<int>>();
}
