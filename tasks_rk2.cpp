#include "tasks_rk2.h"
using namespace std;

int Node::countNodes = 0;
queue<Node*> stack;
int sizeOld = 1;
int nameToFind;
Node* elToFind = nullptr;
string DSFcontainer;

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
	stack = {};
	return ans;
}

int Graph::_buildTreeDFS(int countNodes, Node* el) {
	if (countNodes == 0)
		return Node::countNodes;
	Node* child;
	for (int i = 0; i < countNodes; i++) {
		child = new Node(countNodes);
		child->parent = el;
		el->listChilds.push_back(child);
		_buildTreeDFS(countNodes - 1, child);
	}
	return Node::countNodes;
}

int Graph::buildTreeDFS(int countNodes) {
	Node* Tree = new Node(countNodes);
	int ans = 0;
	if (countNodes > 0) {
		ans = _buildTreeDFS(countNodes, Tree);
	}
	head = Tree;
	head->parent = nullptr;
	Node::countNodes = 0;
	return ans;
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
	stack = {};
}

void Graph::_DFS(int countNodes, Node* el) {
	if (countNodes == -1)
		return;
	DSFcontainer += to_string(el->name);
	if (countNodes != 0)
		DSFcontainer += "{";
	list<Node*>::iterator it = el->listChilds.begin();
	for (int i = 0; i < countNodes; i++) {
		_DFS(countNodes - 1, *it);
		if (i != countNodes - 1)
			DSFcontainer += ",";
		it++;
	}
	if (countNodes != 0)
		DSFcontainer += '}';
}

void Graph::DFS() {
	_DFS(head->listChilds.size(), head);
	FILE* fLog = fopen("dfs_res.txt", "w");
	fprintf(fLog, "%s\n", DSFcontainer.c_str());
	fclose(fLog);
	DSFcontainer = "";
}

void findDFS(int countNodes, Node* el) {
	if (el->name == nameToFind) {
		elToFind = el;
		return;
	}
	if (countNodes == -1)
		return;
	list<Node*>::iterator it = el->listChilds.begin();
	for (int i = 0; i < countNodes; i++) {
		findDFS(countNodes - 1, *it);
		it++;
	}
}

std::pair<bool, std::list<int>> Graph::searchDFS(int nameNode) {
	nameToFind = nameNode;
	findDFS(head->listChilds.size(), head);

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
