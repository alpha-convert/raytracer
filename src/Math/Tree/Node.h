#pragma once

#include <functional>
#include <iostream>

template <typename T>
class Node{
public:
	T val;
	Node<T>* left;
	Node<T>* right;

	Node(T i){
		val = i;
		left = 0;
		right = 0;
	};

	void Insert(T i){
		//TODO: <? <=?
		if(i <= val){
			//TODO: Case when you're actually inserting 0
			if(left == 0){
				MakeLeft(i);
			} else {
				left->Insert(i);
			}
		}

		if(i > val){
			if(right == 0){
				MakeRight(i);
			} else {
				right->Insert(i);
			}
		}
	}

	void RecursiveDelete(){
		if(right) right->RecursiveDelete();
		if(left) left->RecursiveDelete();
		delete this;
	}

	void MakeLeft(T i){
		left = new Node<T>(i);
	}

	void MakeRight(T i){
		right = new Node<T>(i);
	}

	void DeleteLeft(){
		delete left;
	}
	void DeleteRight(){
		delete right;
	}

	Node<T>* Search(T item){
		if(val == item) return this;
		if(item < val && left) return left->Search(item);
		if(item > val && right) return right->Search(item);
		return 0;
	}


	void RecursiveApply(const std::function<T(T)>& f){
		if(left) left->RecursiveApply(f);
		if(right) right->RecursiveApply(f);
		val = f(val);
	}

	void RecursivePrint(){
		if(left) left->RecursivePrint();
		if(right) right->RecursivePrint();
		if(left){
			std::cout << "\"" << val << "\" -> \"" <<  left->val << "\"" << std::endl; 
		}
		if(right){
			std::cout << "\"" << val << "\" -> \"" <<  right->val << "\"" << std::endl; 
		}
	}


};
