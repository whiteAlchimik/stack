
#include <iostream>
#include <algorithm>

#include "Stack.h"

using namespace std;

int main()
{
	Stack<int> stack;

	stack.push(0);
	stack.push(1);
	stack.push(2);
	stack.push(15);
	stack.push(-5);
	stack.push(8);

	auto it_elem = find(stack.begin(), stack.end(), 15);
	if (it_elem != stack.end())
		cout << *(it_elem) << endl;
	else
		cout << "not find" << endl;

	auto it_elem1 = find(stack.begin(), stack.end(), -8);
	if (it_elem1 != stack.end())
		cout << *(it_elem1) << endl;
	else
		cout << "not find" << endl;

	stack.pop();
	stack.pop();
	stack.pop();

	auto it_elem3 = find(stack.begin(), stack.end(), 15);
	if (it_elem3 != stack.end())
		cout << *(it_elem3) << endl;
	else
		cout << "not find" << endl;

	cout << endl << "stack: " << endl;
	copy(stack.cbegin(), stack.cend(), ostream_iterator<int>(cout, "\n"));

	auto itb = stack.begin();
	auto ite = stack.end();
	cout << "stack" << endl;
	for (; itb != ite; itb++)
		cout << *(itb) << endl;

	itb = stack.begin();

	*(itb) = 4;

	cout << endl << "stack: " << endl;
	copy(stack.cbegin(), stack.cend(), ostream_iterator<int>(cout, "\n"));

	itb = stack.begin();
	ite = stack.end();

	for (; itb != ite; itb++)
		*(itb) += 8;

	cout << endl << "stack: " << endl;
	copy(stack.cbegin(), stack.cend(), ostream_iterator<int>(cout, "\n"));

	return 0;
}