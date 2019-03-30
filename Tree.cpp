#include <iostream>
#include <stdexcept>
#include "Tree.hpp"


using namespace std;
using ariel::Tree, ariel::Node;

//Implementation of Node class: 

//Constructors & Destructor:

ariel::Node::Node() : Node(0, nullptr, nullptr, nullptr) {} 
ariel::Node::Node(int data) : Node(data, nullptr, nullptr, nullptr) {}
ariel::Node::Node(int data, Node* right, Node* left, Node* parent) :
        data(data), right(right), left(left), parent(parent) {}
         
ariel::Node::~Node(){
	cout << "~node" <<endl;
	if(left!=nullptr){
		delete left;
		left = nullptr;
}
	if(right!=nullptr){
		delete right;
		right = nullptr;
}

}


//Getters & Setters:
void ariel::Node::setData(int data){
	this->data= data;
}
void ariel::Node::setRight(Node* newRight){
	this->right= newRight;
}
void ariel::Node::setLeft(Node* newLeft){
	this->left= newLeft;
}
void ariel::Node::setParent(Node* newParent){
	this->parent= newParent;
}
int ariel::Node::getData() const{
    return this->data;
}
Node* ariel::Node::getRight() const{
    return this->right;
}
Node* ariel::Node::getLeft() const{
    return this->left;
}
Node* ariel::Node::getParent() const{
	return this->parent;
}







//Implemantation of Binary Search Tree class:

//Empty Constructor:
ariel::Tree::Tree(){
	cout << "treeconst" << endl;
	treeRoot= nullptr;
	treeSize= 0;
}

//Destructor:
ariel::Tree::~Tree(){
	cout << "~tree" <<endl;
	if(treeRoot!=nullptr)
	treeRoot == nullptr;
	treeSize = 0;
}

//SHOULD THROW AN EXCEPTION IF TREE IS NOT CHANGE


//Private Methods:




//this following function helps the contains function-
//looks for the i value in the tree and return the node contains that
Node* ariel::Tree::search(Node* leaf, int i){
	if(leaf==nullptr){
		//cout << "search result: didn't find number: " << i << endl;
		return nullptr;	
	}
	else if(i<(leaf->getData()))
		return search(leaf->getLeft(), i);
	else if(i>(leaf->getData()))
		return search(leaf->getRight(), i);
	else
		return leaf;
}

Node* ariel::Tree::minValue(Node* subtree){
	cout << "minvalue" <<endl;
	if(subtree==nullptr){
		return nullptr;
	}
	if(subtree->getLeft() == nullptr) {
		return subtree;
	}
	return minValue(subtree->getLeft());
}

//Public Methods:

Node* ariel::Tree::insert(Node* node, int i){
	cout << "insertn" << endl;
	if(node != nullptr){
		if(i < node->getData()) {
			if(node->getLeft() == nullptr){
				Node* newLeft = new Node(i, nullptr, nullptr, node);
				node->setLeft(newLeft);
				newLeft->setParent(node);
				treeSize++;
				return newLeft;
			}
			else return insert(node->getLeft(), i);
		}
		else{
			if(node->getRight() == nullptr){
				Node* newRight = new Node(i, nullptr, nullptr, node);
				node->setRight(newRight);
				newRight->setParent(node);
				treeSize++;
				return newRight;
			}
			else return insert(node->getRight(), i);
		}
	} 
	else return nullptr;
}
//Insert function: input- number i, insert the number to it location in the Tree
void ariel::Tree::insert(int i){
		cout << "insert" << endl;
		if(treeRoot == nullptr){
			treeRoot = new Node(i);
			treeSize++;
			treeRoot->setParent(nullptr);
			cout << "end of insert" << endl;
		}
		else if (contains(i)){
			cout << "end of insert" << endl;
			throw std::invalid_argument("This number aleady exist");
		}
		else{
			insert(treeRoot, i);
			cout << "end of insert" << endl;
		}
}



//Remove function: input- number i, remove the node holds this number in the tree
//Throw exceptions if this number does not exist
void ariel::Tree::remove(int i){
	cout << "remove" << endl;
	Node* toBeRemoved = search(treeRoot, i);
	if(contains(i) == false) {
		cout << "end of delete alert" << endl;
		throw std::invalid_argument("This Node doesnt exist");
	}
	//case 1: node to be deleted is leaf:
	if(toBeRemoved->getLeft()==nullptr && toBeRemoved->getRight()==nullptr){
		//if this is the root
		cout << "1" << endl;
		if(toBeRemoved->getParent()==nullptr){
			cout << "1.1" << endl;
			treeRoot = toBeRemoved = nullptr;
			treeSize--;
			return;
		}
		//if it is the left child
		else if(toBeRemoved->getData() < toBeRemoved->getParent()->getData()){
		cout << "1.2" << endl;
			toBeRemoved->getParent()->setLeft(nullptr);
			toBeRemoved = nullptr;
			treeSize--;
			return;
		}
		//if it is the right child
		else{
			cout << "1.3" << endl;
			toBeRemoved->getParent()->setRight(nullptr);
			toBeRemoved = nullptr;
			treeSize--;
			return;
		}
	}	//end case 1
	
	//case 2: node to be deleted has only right child:
	else if((toBeRemoved->getLeft()==nullptr) && (toBeRemoved->getRight()!=nullptr)){
		//if this is the root
		cout << "2" << endl;
		if(toBeRemoved->getParent()==nullptr){
			cout << "2.1" << endl;
			treeRoot = toBeRemoved->getRight();
			treeRoot->setParent(nullptr);
			toBeRemoved = nullptr;
			treeSize--;
			return;
		}
		//if it is the left child
		else if(toBeRemoved->getData() < toBeRemoved->getParent()->getData()){
			cout << "2.2" << endl;
			toBeRemoved->getParent()->setLeft(toBeRemoved->getRight());
			toBeRemoved->getRight()->setParent(toBeRemoved->getParent());
			toBeRemoved = nullptr;
			treeSize--;
			return;
		}
		//if it is the right child
		else if(toBeRemoved->getData() > toBeRemoved->getParent()->getData()){
			cout << "2.3" << endl;
			toBeRemoved->getParent()->setRight(toBeRemoved->getRight());
			toBeRemoved->getRight()->setParent(toBeRemoved->getParent());
			toBeRemoved = nullptr;
			treeSize--;
			return;
		}
	}//end case 2
	
	//case 3: node to be deleted has only left child:
	else if((toBeRemoved->getLeft()!=nullptr) && (toBeRemoved->getRight()==nullptr)){
		cout << "3" << endl;
		//if this is the root
		if(toBeRemoved->getParent()==nullptr){
			cout << "3.1" << endl;
			treeRoot = toBeRemoved->getLeft();
			toBeRemoved->getLeft()->setParent(nullptr);
			toBeRemoved = nullptr;
			treeSize--;
			cout << "done 3.1" << endl;
			return;
		}	
		//if it is the left child
		else if(toBeRemoved->getData() < toBeRemoved->getParent()->getData()){
			cout << "3.2" << endl;
			toBeRemoved->getParent()->setLeft(toBeRemoved->getLeft());
			toBeRemoved->getLeft()->setParent(toBeRemoved->getParent());
			toBeRemoved = nullptr;
			treeSize--;
			return;
		}
		//if it is the right child
		else if(toBeRemoved->getData() >= toBeRemoved->getParent()->getData()){
			cout << "3.3" << endl;
			toBeRemoved->getParent()->setRight(toBeRemoved->getLeft());
			toBeRemoved->getLeft()->setParent(toBeRemoved->getParent());
			toBeRemoved = nullptr;
			treeSize--;
			return;
		}
	}//end case 3
	
	//case 4: node to be deleted has two children:
	//get the inorder successor (smallest in the right subtree) 
	else{
		cout << "4" << endl;
		Node* temp = minValue(toBeRemoved->getRight());
		int valueToRemove = temp->getData();
		remove(valueToRemove);
		toBeRemoved->setData(valueToRemove);
	}//end 4 case
	cout << "end of remove" << endl;
}//end remove

//Return the size of the Tree:
int ariel::Tree::size(){
    return treeSize;
}

//Search function: if the tree contains the value of i- returns true.
bool ariel::Tree::contains(int i){
	cout << "contains" << endl;
	if (search(treeRoot, i)== nullptr) return false;
	else return true;
}

//Returns the data in the root
int ariel::Tree::root(){
	cout << "getrootdata" << endl;
	return treeRoot->getData();
}

//Parent function: input- value i, returns the data allocate above this value in the Tree
int ariel::Tree::parent(int i){
	cout << "parent" <<endl;
	if(search(treeRoot, i) == nullptr) throw std::invalid_argument("error");
	else if(search(treeRoot, i)->getParent() == nullptr) throw std::invalid_argument("error");
	return search(treeRoot, i)->getParent()->getData();
}

//Left function: input- value i, returns the left child's data of the input
int ariel::Tree::left(int i){
	cout << "leftchild" <<endl;
	Node* current= search(treeRoot, i);
	if(current == nullptr || current->getLeft() == nullptr) throw std::invalid_argument("error, no node or left child");
	return current->getLeft()->getData();
}

//Right function: input- value i, returns the right child's data of the input
int ariel::Tree::right(int i){
	cout << "rightchild" <<endl;
	Node* current= search(treeRoot, i);
	if(current == nullptr || current->getRight() == nullptr) throw std::invalid_argument("error, no node or right child");
	return current->getRight()->getData();
}

void ariel::Tree::print(Node* node){
	if(node==nullptr) return;
	else {
		print(node->getLeft());
		cout << " [ " << node->getData() << " ]";
		print(node->getRight());
	}
}

//Print the Tree
void ariel::Tree::print(){
	if(treeRoot ==nullptr) cout << "the tree is empty" << endl;
	else{
		print(treeRoot);   
		cout << "done printing" << endl;
	}
}
