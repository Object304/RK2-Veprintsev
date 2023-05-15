#include "tasks_rk2.h"
using namespace std;

int Node::countNodes = 0;
queue<Node*> stack;
int sizeOld = 1;

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
	sizeOld = countNodes;
	Node* Tree = new Node(countNodes);
	//Tree->enterCount--;
	stack.push(Tree);
	buildTreeBFS(countNodes);
	head = Tree;
	head->parent = nullptr;
	Node::countNodes = 0;
}

Graph::~Graph() {
	delete head;
}

//void Graph::buildBFS(Node*& el, int countNodes) {
//	if (stack.empty())
//		return;
//	
//	Node* child;
//	for (int i = 0; i < countNodes; i++) {
//		child = new Node(countNodes);
//		child->parent = el;
//		el->listChilds.push_back(child);
//		stack.push(child);
//	}
//
//
//
//
//
//	if (countNodes == 0)
//		return;
//	list<Node*>::iterator it = el->listChilds.begin();
//	while (it != el->listChilds.end()) {
//		if (el->enterCount > (*it)->enterCount) {
//			buildBFS(*it, countNodes - 1);
//		}
//		it++;
//	}
//	/*for (int i = 0; i < countNodes; i++) {
//		buildBFS(*it, countNodes - 1);
//	}*/
//
//	el->enterCount++;
//
//	Node* child;
//	for (int i = 0; i < countNodes; i++) {
//		child = new Node(countNodes);
//		child->parent = el;
//		el->listChilds.push_back(child);
//	}
//	if (zero) {
//		zero = false;
//		buildBFS(child->parent, countNodes);
//	}
//	/*else
//		buildBFS(child->parent, countNodes + 1);*/
//}

int Graph::buildTreeBFS(int countNodes) {
	Node* el = stack.front();
	Node* child;
	if (countNodes == 1) {
		for (int i = 0; i < sizeOld; i++) {
			child = new Node(countNodes);
			child->parent = el;
			el->listChilds.push_back(child);
			stack.push(child);
			stack.pop();
		}
		return 0;
	}
	for (int i = 0; i < countNodes; i++) {
		child = new Node(countNodes);
		child->parent = el;
		el->listChilds.push_back(child);
		stack.push(child);
	}
	stack.pop();
	if (stack.size() == sizeOld) {
		sizeOld *= countNodes - 1;
		buildTreeBFS(countNodes - 1);
	}
	else {
		buildTreeBFS(countNodes);
	}
	return 0;
}

int Graph::buildTreeDFS(int countNodes) {
	return -1;
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
