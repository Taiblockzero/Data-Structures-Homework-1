#include "Stack.h"
#include <iostream>

Stack::Stack(char* input)
{
	this->input = new char[strlen(input) + 1];
	strcpy(this->input, input);

	tos = NULL;
	size = 0;
	maxBracketLevel = 0;
	//currBracketLevel = 0;
	//nodesPerLevel = NULL;
}

Stack::~Stack()
{
	delete[] input;
	//delete[] nodesPerLevel;
	
	if (size == 1)
		delete tos;

	else if (size > 1)
	{
		Node* tmp;
		while (size > 1)
		{
			tmp = tos->prev;
			delete tos;
			tos = tmp;
			size--;
		}
		delete tos;
	}
	


}

void Stack::setMaxBracketLevel()
{
	int max = 0; //max bracket level
	int current = 0; //current bracket level
	
	for (int i = 0; i < strlen(input); ++i)
	{
		if ('(' == input[i])
		{
			current++;
		}
		else if (')' == input[i])
		{
			current--;
		}
		if (current > max)
		{
			max = current;
		}
	}
	
	maxBracketLevel = max;
}

/*void Stack::fillNodesPerLevel()
{
	nodesPerLevel = new int[maxBracketLevel];

	//bracketLevel is current bracket level, sBracketLevel is searched bracket level
	//nodesCnt is counter for nodes in the current bracket level
	for (int bracketLevel = 0, sBracketLevel = maxBracketLevel, nodesCnt = 0; 
	     sBracketLevel > 0; --sBracketLevel)
	{
		for (int i = 0; i < strlen(input); ++i)
		{
			if ('(' == input[i])
				bracketLevel++;
			else if (')' == input[i])
				bracketLevel--;
			//if ('(' == input[i] is in order to do these things only once
			if ('(' == input[i] && bracketLevel == sBracketLevel)
				nodesCnt++;
		}
		nodesPerLevel[sBracketLevel - 1] = nodesCnt; //level 1 is in array index 0, level 2 is in index 1 and so on
	}
}*/

void Stack::fillStack()
{
	setMaxBracketLevel();
	if (0 == maxBracketLevel)
	{
		push(createNode(maxBracketLevel, input)); //First creates the node and then pushes it to top of stack
	}
	else
	{
		bool firstRun = true;
		//The functions will be run for bracket levels from (maxBracketLevel - 1) to bracket level 0 included
		for (int i = 1; i <= maxBracketLevel; ++i)
		{
			if (firstRun)
			{
				push(createNode(maxBracketLevel - i, input)); //First creates the node and then pushes it to top of stack
				firstRun = false;
			} 
			else
				push(createNode(maxBracketLevel - i, tos->str)); //First creates the node and then pushes it to top of stack


		}
	}
}

Node* Stack::createNode(int bracketLevel, char* input)
{
	//Part 1 - Turning expression into string
	int currBL = 0; //current bracket level
	char buffer[1000]; //see what you can do about this!!!
	int iBuf = 0; //buffer index
	int i = 0;
	int inputLen = strlen(input);
	for (; i < inputLen; ++i)
	{
		if ('(' == input[i])
		{
			currBL++;
			buffer[iBuf] = input[i];
			iBuf++;
		}
		else if (')' == input[i])
			currBL--;

		if (currBL < bracketLevel)
		{
			buffer[iBuf] = input[i];
			iBuf++;
		}

		else if (currBL == bracketLevel)
		{
			if (input[i] >= 'A' && input[i] <= 'Z')
			{
				buffer[iBuf] = input[i];
				iBuf++;
			}
			else if (input[i] >= '1' && input[i] < '9')
			{
				char* buf2 = decode(i, input); 
				int buf2Len = strlen(buf2);
				for (int j = 0; j < buf2Len; ++j)
				{
					buffer[iBuf] = buf2[j];
					iBuf++;
				}
				delete[] buf2;

				while (input[i] != ')') //skips the expression decoded by decode()
					i++;
			}
		}
	}
	buffer[iBuf] = '\0';

	//Part 2 - Creating Node
	int bufLen = strlen(buffer);
	Node* returnNode = new Node;

	returnNode->str = new char[bufLen + 1];
	int k = 0;
	for (; k < bufLen; ++k)
		returnNode->str[k] = buffer[k];
	returnNode->str[k] = '\0';

	return returnNode;
}

void Stack::push(Node* toBePushed)
{
	if (NULL != tos) //if stack isn't empty
		toBePushed->prev = tos;
	tos = toBePushed;
	size++;
}

char* Stack::decode(int index, char* input)
{
	//Part 1 - getting "how many times expression will be repeated"
	char number[50]; 
	int i = index;
	int j = 0;
	for (; input[i] != '('; ++i, ++j)
	{
		number[j] = input[i];
	}
	number[j] = '\0';
	int timesRepeated = atoi(number);

	//Part 2 - Getting the string from inside the brackets (example: "AB" from 2(AB))
	
	//input[i] is currently the opening bracket '(' of the expression
	++i; //now input[i] is the first letter after the opening bracket
	char buffer[1000];
	int k = 0;
	for (; input[i] != ')'; ++i, ++k)
	{
		buffer[k] = input[i];
	}
	buffer[k] = '\0';

	int bufLen = strlen(buffer);
	char* bracketString = new char[bufLen + 1]; //string from inside the brackets
	int cnt = 0;
	for (; cnt < bufLen; ++cnt)
	{
		bracketString[cnt] = buffer[cnt];
	}
	bracketString[cnt] = '\0';

	//Part 3 - concatenating the string with itself
	char* destinationString = new char[(strlen(bracketString) * timesRepeated) + 1];
	strcpy(destinationString, bracketString);

	for (int cnt2 = 0; cnt2 < timesRepeated - 1; ++cnt2)
	{
		strcat(destinationString, bracketString);
	}

	delete[] bracketString;

	return destinationString;
}

char* Stack::getResult()
{
	return tos->str;
}