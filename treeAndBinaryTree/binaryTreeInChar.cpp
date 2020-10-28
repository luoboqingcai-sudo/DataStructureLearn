#include<iostream>
#include<stack>
#include<queue>
#include"Predefine.h"
using namespace std;


typedef struct BiTNode {
	char data;
	BiTNode *lchild, *rchild;
}BiTNode;

class Destroy {
public:
	bool operator()(BiTNode *T){
		delete T;
		return !(T = NULL);
	}
};

class Visit {
public:
	int operator()(BiTNode* T){
		cout << T->data << " ";
		return 1;
	}
};


Status CreateBiTree(BiTNode *&T);
Status DestroyTree(BiTNode *T);
template<class FunctionType>
Status PostOrderTraverse(BiTNode *T, FunctionType &function);
template<class FunctionType>
Status InOrderTraverse(BiTNode *T, FunctionType &function);
template<class FunctionType>
Status LevelOrderTraverse(BiTNode *T, FunctionType &function);
int GetBiTNodeNumber(BiTNode *T);
int GetBiTNodeLevel(BiTNode *T);

/**
* param: if it is (BiTNode *T), can't be nullptr 
*        because it just mean a local nullpter in function
* BiTNode *&T a null pointer reference
* return Statue, just return OK
*/
Status CreateBiTree(BiTNode *&T)
{
	char ch;
	cin >> ch;
	if (ch == 'N') T = NULL;
	else {
		T = new BiTNode;
		T->data = ch;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
	return OK;
}

Status DestroyTree(BiTNode *T) {
	Destroy destroy;
	return PostOrderTraverse(T->lchild, destroy);
}

template<class FunctionType>
Status PostOrderTraverse(BiTNode *T, FunctionType &function) {
	if (T) {
		if (PostOrderTraverse(T->lchild, function)) {
			if (PostOrderTraverse(T->rchild, function)) {
				if (function(T)) {
					return OK;
				}
				else {
					return ERROR;
				}
			}
		}
	}
	return OK;
}

template<class FunctionType>
Status InOrderTraverse(BiTNode *T, FunctionType &function) {
	stack<BiTNode*> BiTNodeStack;
	if (T) {
		BiTNodeStack.push(T);
		T = T->lchild;
	}
	while (!BiTNodeStack.empty()) {
		if (T) {
			BiTNodeStack.push(T);
			T = T->lchild;
		}
		else {
			T = BiTNodeStack.top();
			BiTNodeStack.pop();
			function(T);
			T = T->rchild;
		}
	}
	return OK;
}

template<class FunctionType>
Status LevelOrderTraverse(BiTNode *T, FunctionType &function) {
	queue<BiTNode*> BiTNodeQueue;
	if (T) {
		BiTNodeQueue.push(T);
	}
	while (!BiTNodeQueue.empty()) {
		T = BiTNodeQueue.front();
		BiTNodeQueue.pop();
		if (T) {
			function(T);
			BiTNodeQueue.push(T->lchild);
			BiTNodeQueue.push(T->rchild);
		}
	}
	return OK;
}

int GetBiTNodeNumber(BiTNode *T) {
	if (T) {
		return GetBiTNodeNumber(T->lchild) + GetBiTNodeNumber(T->rchild) + 1;
	}
	else {
		return 0;
	}
}

int GetBiTNodeLevel(BiTNode *T) {
	if (T) {
		return max(GetBiTNodeLevel(T->lchild), GetBiTNodeLevel(T->rchild)) + 1;
	}
	else return 0;
}


int main() {

	BiTNode *rootPointer;
	Visit visit;
	CreateBiTree(rootPointer);
	cout << "中序遍历的结果为：";
	InOrderTraverse(rootPointer, visit);
	cout << endl << "后序遍历的结果为：";
	PostOrderTraverse(rootPointer, visit);
	cout << endl << "层次遍历的结果为：";
	LevelOrderTraverse(rootPointer, visit);
	cout << endl;
	cout << "二叉树的层次：" << GetBiTNodeLevel(rootPointer) << endl;
	cout << "二叉树的节点数目：" << GetBiTNodeNumber(rootPointer) << endl;
	// DestroyTree(rootPointer);
	return 0;
}