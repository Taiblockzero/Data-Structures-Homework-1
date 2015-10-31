#pragma once
#include <iostream>

struct Node
{
	char* str;
	//int times; //amount of times to be repeated
	Node* prev;
public:
	Node() { str = NULL; prev = NULL; }
	~Node() { delete[] str; }
};