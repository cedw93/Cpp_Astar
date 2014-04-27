/*
 * main.h
 *
 *  Created on: 11 Mar 2014
 *      Author: chris
 */

#ifndef MAIN_H_
#define MAIN_H_



Node* initiateStart(int m[20][20]);
Node* generateLeftChild(Node* parent, int m[20][20]);
Node* generateRightChild(Node* parent, int m[20][20]);
Node* generateAboveChild(Node* parent, int m[20][20]);
Node* generateBelowChild(Node* parent, int m[20][20]);
bool checkInClosedList(std::vector<Node*>& v, int x, int y);
bool placeInOpen(std::list<Node*>& v,int x, int y);

void checkPath(Node *end, int m[20][20]);
void calcManhattanDistance(Node *node, int m[20][20]);
void printMap(int m[20][20]);


#endif /* MAIN_H_ */
