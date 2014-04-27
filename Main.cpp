/*
 * Main.cpp
 *
 *  Created on: 11 Mar 2014
 *      Author: chris
 */

#include <iostream>
#include <ostream>
#include <vector>
#include <queue>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <list>

#include "Node.h"
#include "main.h"

int main(){

	int map[20][20] = {{0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,2},
			{0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
			{0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,0,0,0,0},
			{0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0},
			{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0},
			{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0},
			{0,0,3,0,0,1,1,1,1,1,1,1,0,0,0,0,1,0,0,0},
			{0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0},
			{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0},
			{0,0,0,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0}};

	using namespace std;

	list<Node*> openList;
	vector<Node*> closedList;

	Node *end;
	Node *start = initiateStart(map);
	openList.push_front(start);
	cout <<"Start index: x " << start->getX() << " y " <<start->getY() << endl;

	while (!openList.empty()) {

		Node *best = openList.front();
		openList.pop_front();
		if(!checkInClosedList(closedList, best->getX(), best->getY())){
			calcManhattanDistance(best, map);

			if(best->getValue() == 3){
				end = best;
				cout <<"end index: x " << end->getX() << " y " <<end->getY() << endl;
				checkPath(end, map);
				for (std::list<Node*>::iterator iter = openList.begin(); iter != openList.end(); ++iter) {
					(*iter)-> ~Node();
				}

				exit(1);
			}

			if(map[best->getX()][best->getY()-1] != 1 && best->getY() - 1 > -1){
				if(placeInOpen(openList,best->getX(), best->getY() - 1)){
					openList.push_front(generateLeftChild(best, map));
				}
			}
			//to the right
			if(map[best->getX()][best->getY()+1] != 1 && best->getY() + 1 < 20){
				if(placeInOpen(openList,best->getX(), best->getY() + 1)){
					openList.push_front(generateRightChild(best, map));
				}
			}

			//above
			if(map[best->getX()-1][best->getY()] != 1 && best->getX() - 1 > -1){
				if(placeInOpen(openList,best->getX()-1, best->getY())){
					openList.push_front(generateAboveChild(best, map));
				}
			}

			//below
			if(map[best->getX()+1][best->getY()] != 1 && best->getX() + 1 < 20){
				if(placeInOpen(openList,best->getX()+1, best->getY())){
					openList.push_front(generateBelowChild(best, map));
				}
			}


			closedList.push_back(best);
		}

		openList.sort(NodeComparator());
	}

	return 0;
}


Node* initiateStart(int m[20][20]){

	Node *start;
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 20; j++){
			if(m[i][j] == 2){
				start = new Node(i, j, m[i][j], 0, NULL);
			}

		}
	}

	return start;

}

Node* generateLeftChild(Node *parent, int m[20][20]){

	Node *child;

	child = new Node(parent->getX(), parent->getY() - 1, m[parent->getX()][parent->getY() - 1],
			parent->getGCost() + 1, parent);
	calcManhattanDistance(child, m);

	return child;

}

Node* generateRightChild(Node *parent, int m[20][20]){

	Node *child;

	child = new Node(parent->getX() , parent->getY() + 1, m[parent->getX()][parent->getY() + 1],
			parent->getGCost() + 1, parent);
	calcManhattanDistance(child, m);

	return child;

}

Node* generateAboveChild(Node *parent, int m[20][20]){

	Node *child;

	child = new Node(parent->getX() - 1, parent->getY(), m[parent->getX() - 1][parent->getY()],
			parent->getGCost() + 1, parent);

	calcManhattanDistance(child, m);

	return child;

}

Node* generateBelowChild(Node *parent, int m[20][20]){

	Node *child;

	child = new Node(parent->getX() + 1, parent->getY(), m[parent->getX() + 1][parent->getY()],
			parent->getGCost() + 1, parent);

	calcManhattanDistance(child, m);

	return child;

}

void calcManhattanDistance(Node *node, int m[20][20]){

	int tempX;
	int tempY;
	double manhattanDistance;
	int differenceX;
	int differenceY;

	//std::cout << "node x: " << node->getX() << " node y: " << node->getY() << std::endl;

	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 20; j++){
			if(m[i][j] == 3){
				tempX = i;
				tempY = j;
			}
		}
	}


	//sum of term difference, none of these can be negative hense the std::abs
	differenceX = tempX - node->getX();
	differenceY = tempY - node->getY();

	manhattanDistance = std::abs(differenceX) + std::abs(differenceY);

	//std::cout << "Manhattan distance: " << manhattanDistance << std::endl;

	node->setHCost(manhattanDistance);

}

bool checkInClosedList(std::vector<Node*>& v,int x, int y){

	for (std::vector<Node*>::iterator iter = v.begin(); iter != v.end(); ++iter) {
		if((*iter)->getX() == x && (*iter)->getY() == y){
			return true;
		}
	}

	return false;

}

bool placeInOpen(std::list<Node*>& v,int x, int y){

	for (std::list<Node*>::iterator iter = v.begin(); iter != v.end(); ++iter) {
		if((*iter)->getX() == x && (*iter)->getY() == y){
			return false;
		}
	}
	return true;

}

void checkPath(Node *end, int m[20][20]){
	int tempX, tempY;
	Node *temp = end;

	while(temp != NULL){
		tempX = temp->getX();
		tempY = temp->getY();
		std:: cout << tempX << " " << tempY << std::endl;
		m[tempX][tempY] = 4;
		temp = temp->getParent();
	}
	printMap(m);
}

void printMap(int m[20][20]){

	std::cout << "printy mcprint" << std::endl;
	for(int i = 0; i< 20; i++){
		for(int j = 0; j< 20; j++){
			std::cout << m[i][j];
		}
		std::cout<<std::endl;
	}

}


