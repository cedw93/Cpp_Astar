/*
 * Node.h
 *
 *  Created on: 11 Mar 2014
 *      Author: chris
 */

#ifndef NODE_H_
#define NODE_H_


class Node{

private:

	int xCoord;
	int yCoord;
	int value;
	double fCost;
	double gCost;
	double hCost;
	Node* parent;

public:

	Node();
	Node(int x, int y, int value, int cost, Node* parent);
	void setParent(Node* parent);
	int getX();
	int getY();
	int getValue();
	double getHCost();
	double getFCost();
	double getGCost();
	Node* getParent();
	void setHCost(double hCost);
	~Node();
};

struct NodeComparator {
	bool operator()(Node* first, Node* second) {

		return (first->getFCost() < second->getFCost());

	}
};

#endif /* NODE_H_ */
