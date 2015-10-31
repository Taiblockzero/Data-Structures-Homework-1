//Bracket level - The amount of brackets you're in; Example: ((A)), Here A is in bracket level 2

#pragma once
#include "Node.h"

class Stack
{
private:
	char* input;
	Node* tos;
	int size;
	int maxBracketLevel; //max bracket level
	//int currBracketLevel; //current bracket level
	//int* nodesPerLevel; //array containing how many nodes there are for each bracket level
public:
	Stack(char* input);
	~Stack();
private:
	void setMaxBracketLevel();
	//void fillNodesPerLevel();
public:
	void fillStack();
	char* getResult();
private: //Functions that fillStack() uses
	Node* createNode(int bracketLevel, char* input);
	void push(Node* toBePushed);
private:
	//Function decode() is used by createNode()
	char* decode(int index, char* input); //decodes expression that has no expressions in it into string (example: 2(AB))
};