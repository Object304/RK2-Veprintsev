#include "tasks_rk2.h"
using namespace std;

int Node::countNodes = 0;
queue<Node*> stack;
int sizeOld = 1;
int nameToFind;
Node* elToFind = nullptr;

Node::Node() {
	parent = nullptr;
	name = countNodes;
}

Node::Node(int nameNode) {
	parent = nullptr;
	name = countNodes;
	countNodes++;
}

Node::~Node() {}

Graph::Graph() {
	head = nullptr;
}

Graph::Graph(int countNodes) {
	buildTreeBFS(countNodes);
}

void Graph::Destruct() {
	if (stack.empty())
		return;
	Node* el;
	el = stack.front();
	list<Node*>::iterator it = el->listChilds.begin();
	while (it != el->listChilds.end()) {
		stack.push(*it);
		it++;
	}
	delete el;
	el = nullptr;
	stack.pop();
	Destruct();
}

Graph::~Graph() {
	stack.push(head);
	Destruct();
}

int Graph::_buildTreeBFS(int countNodes) {
	Node* el = stack.front();
	Node* child;
	if (countNodes == 1) {
		while (true) {
			child = new Node(countNodes);
			child->parent = el;
			el->listChilds.push_back(child);
			stack.pop();
			if (stack.empty()) {
				return Node::countNodes;
			}
			el = stack.front();
		}
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
		_buildTreeBFS(countNodes - 1);
	}
	else {
		_buildTreeBFS(countNodes);
	}
	return Node::countNodes;
}

int Graph::buildTreeBFS(int countNodes) {
	sizeOld = countNodes;
	Node* Tree = new Node(countNodes); 
	int ans = 0;
	if (countNodes > 0) {
		stack.push(Tree);
		ans = _buildTreeBFS(countNodes);
	}
	head = Tree;
	head->parent = nullptr;
	sizeOld = 1;
	Node::countNodes = 0;
	return ans;
}

int Graph::buildTreeDFS(int countNodes) {
	return -1;
}

void Graph::_BFS() {
	Node* el;
	el = stack.front();
	if (el->listChilds.empty()) {
		stack = {};
		return;
	}
	string str;
	str += to_string(el->name) + "{";
	list<Node*>::iterator it = el->listChilds.begin();
	while (it != el->listChilds.end()) {
		stack.push(*it);
		str += to_string((*it)->name) + ",";
		it++;
	}
	stack.pop();
	str[str.length() - 1] = '}';
	FILE* fLog = fopen("bfs_res.txt", "a");
	fprintf(fLog, "%s\n", str.c_str());
	fclose(fLog);
	_BFS();
}

void Graph::BFS() {
	Node* el = head;
	stack.push(el);
	_BFS();
}

void Graph::DFS() {}

std::pair<bool, std::list<int>> Graph::searchDFS(int nameNode) {

	return std::pair<bool, std::list<int>>();
}

void Graph::findEl() {
	Node* el;
	el = stack.front();
	if (el->name == nameToFind) {
		stack = {};
		elToFind = el;
		return;
	}
	list<Node*>::iterator it = el->listChilds.begin();
	while (it != el->listChilds.end()) {
		stack.push(*it);
		it++;
	}
	stack.pop();
	if (stack.empty()) {
		return;
	}
	findEl();
}

pair<bool, list<int>> Graph::searchBFS(int nameNode) {
	nameToFind = nameNode;
	Node* _head = head;
	stack.push(_head);
	findEl();
	pair<bool, list<int>> ans;
	if (elToFind == nullptr) {
		ans.first = false;
		return pair<bool, list<int>>();
	}
	list<int> parents;
	while (elToFind->parent != nullptr) {
		elToFind = elToFind->parent;
		int name = elToFind->name;
		parents.push_back(name);
	}
	elToFind = nullptr;
	ans.first = true;
	ans.second = parents;
	return ans;
}
