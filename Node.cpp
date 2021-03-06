/*
 * Node.cpp
 *
 *  Created on: 11 Mar 2014
 *      Author: chris
 */

#include <stdlib.h>

#include "Node.h"

Node::Node(){

	this->xCoord = 0;
	this->yCoord = 0;
	this->value = 0;
	this->parent = NULL;
	this->fCost = 0;
	this->gCost = 0;
	this->hCost = 0.0;

}

Node::Node(int _x, int _y, int _value, int cost, Node* parent){

	this->xCoord = _x;
	this->yCoord = _y;
	this->value = _value;
	this->gCost = cost;
	this->parent = parent;
	this->hCost = 0.0;
	this->fCost = 0;

}

void Node::setParent(Node* par){

	this->parent = par;

}

int Node::getX(){

	return xCoord;

}

int Node::getY(){

	return yCoord;

}

int Node::getValue(){

	return value;

}

double Node::getGCost(){

	return gCost;
}

double Node::getFCost(){

	return gCost + hCost;

}

double Node::getHCost(){

	return hCost;

}

Node* Node::getParent(){

	return parent;
}

void Node::setHCost(double cost){

	this->hCost = cost;

}

Node::~Node(){

	delete(this);
}


