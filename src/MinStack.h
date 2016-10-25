#pragma once

#include <stack>

using namespace std;

class MinStack {
	stack<int> valS;
	stack<int> minS;
public:
	void push(int x) {
		valS.push(x);
		if (minS.empty() || x < minS.top()) { minS.push(x); }
	}

	void pop() {
		int top = valS.top();
		valS.pop();
		if (!minS.empty() && top == minS.top()) { minS.pop(); }
	}

	int top() {
		return valS.top();
	}

	int getMin() {
		return minS.empty() ? valS.top() : minS.top();
	}
};
