#include "Stack.h"
#include <iostream>
using namespace std;

int main()
{
	char* result;

	Stack s1("A");
	s1.fillStack();
	result = s1.getResult();
	cout << result << endl;

	Stack s2("AB");
	s2.fillStack();
	result = s2.getResult();
	cout << result << endl;

	Stack s3("3(A)");
	s3.fillStack();
	result = s3.getResult();
	cout << result << endl;

	Stack s4("3(AB2(B))");
	s4.fillStack();
	result = s4.getResult();
	cout << result << endl;
	
	Stack s5("12(ZQ)");
	s5.fillStack();
	result = s5.getResult();
	cout << result << endl;

	Stack s6("2(2(A)3(B))");
	s6.fillStack();
	result = s6.getResult();
	cout << result << endl;

	return 0;
}