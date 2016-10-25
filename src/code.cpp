// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <map>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <set>
#include <unordered_set>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct TreeLinkNode {
	int val;
	TreeLinkNode *left, *right, *next;
	TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

void PrintVecotr(vector<int>& v)
{
	for(size_t i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;
}

void PrintVecotr(vector<string>& v)
{
	for(size_t i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;
}

void DeleteNode(ListNode* p)
{
	cout << "delete " << p->val << endl;
	delete p;
}

/*
Given an array of integers, find two numbers such that they add up to a specific target number.

The function twoSum should return indices of the two numbers such that they add up to the target, 
where index1 must be less than index2. 
Please note that your returned answers (both index1 and index2) are not zero-based.

You may assume that each input would have exactly one solution.

Input: numbers={2, 7, 11, 15}, target=9
Output: index1=1, index2=2
*/
vector<int> twoSum(vector<int>& numbers, int target)
{
	map<int, int> numMap;
	for(size_t i = 0; i < numbers.size(); i++)
	{
		int toFind = target - numbers[i];
		if (numMap.find(toFind) == numMap.end())
		{
			numMap[numbers[i]] = i;
			continue;
		}

		vector<int> result;
		result.push_back(numMap[toFind]+1);
		result.push_back(i+1);
		return result;
	}
	return vector<int>();
}

void RunTwoSum()
{
	vector<int> numbers;
	for(int i = 0; i < 10000; i++)
	{
		numbers.push_back(i + 100);
	}

	vector<int> result = twoSum(numbers, 3000);
	cout << result[0] << ":" << numbers[result[0]-1] << "+" << result[1] << ":" << numbers[result[1]-1] << endl;
}

/*
 * Given a string, find the length of the longest substring without repeating characters. 
 * For example, the longest substring without repeating letters for "abcabcbb" is "abc", 
 * which the length is 3. For "bbbbb" the longest substring is "b", with the length of 1.
*/
int lengthOfLongestSubstring(string s) {
	int maxLen = 0;
	int subStrLen = 0;
	size_t i = 0, j = 0;
	map<char, int> charMap;		
	for(; i < s.length(); )
	{
		for(; j < s.length(); j++)
		{
			char next = s.at(j);
			if (charMap.find(next) != charMap.end() && charMap[next] != -1)
			{
				subStrLen = j - i;
				if (subStrLen > maxLen) 
				{ 
					maxLen = subStrLen; 
					cout << maxLen << ":" << s.substr(i, subStrLen).c_str() << endl;
				}
				int tmp = charMap[next] + 1;
				for(int k = i; k <= charMap[next]; k++)
				{
					charMap[s.at(k)] = -1;
				}
				i = tmp;
				break;
			}
			else
			{
				charMap[next] = j;
			}
		}
		if (j == s.length())
		{
			subStrLen = j -i;
			break;
		}
	}
	if (subStrLen > maxLen) 
	{ 
		maxLen = subStrLen; 
		cout << maxLen << ":" << s.substr(i, subStrLen).c_str() << endl;
	}
	return maxLen;
}

/*
基本思路是维护一个窗口，每次关注窗口中的字符串，在每次判断中，左窗口和右窗口选择其一向前移动。
同样是维护一个HashSet, 正常情况下移动右窗口，如果没有出现重复则继续移动右窗口，如果发现重复
字符，则说明当前窗口中的串已经不满足要求，继续移动有窗口不可能得到更好的结果，此时移动左窗口，
直到不再有重复字符为止，中间跳过的这些串中不会有更好的结果，因为他们不是重复就是更短。因为左
窗口和右窗口都只向前，所以两个窗口都对每个元素访问不超过一遍，因此时间复杂度为O(2*n)=O(n),是
线性算法。空间复杂度为HashSet的size,也是O(n).
*/
int lengthOfLongestSubstring_2(string s) 
{
	if (s.length() == 0) return 0;
	int maxLen = 1;
	int left = 0;
	int right = 1;
	map<char, int> pos;
	pos[s.at(0)] = 0;
	while(right < s.length())
	{
		char c = s.at(right);
		if (pos.find(c) == pos.end())
		{
			int len = right - left + 1;
			if (len > maxLen) maxLen = len;
			pos[c] = right;
			right++;
		}
		else
		{
			while(s.at(left) != c)
			{
				pos.erase(s.at(left));
				left++;
			}
			left++;
			right++;
		}
	}
	return maxLen;  
}

void RunLongestSubStr()
{
	//string s = "wlrbbmqbhcdarzowkkyhiddqscdxrjmowfrxsjybldbefsarcbynecdyggxxpklorellnmpapqfwkhopkmco";
	string s = "hnwnkuewhsqmgbbuqcljjivswmdkqtbxixmvtrrbljptnsnfwzqfjmafadrrwsofsbcnuvqhffbsaqxwpqcac";
	int len = lengthOfLongestSubstring_2(s);
	cout << len << endl;
}

/*
Remove Duplicates from Sorted Array
Given a sorted array, remove the duplicates in place such that each element appear only once 
and return the new length.			
Do not allocate extra space for another array, you must do this in place with constant memory.
For example,
Given input array A = [1,1,2],	  
Your function should return length = 2, and A is now [1,2].
*/
int removeDuplicates(int a[], int n) 
{	
	int valIndex = 0;
	for (int i = 1; i < n; i++)
	{
		if (a[i] != a[valIndex])
		{		
			valIndex++;
			if (valIndex < i)
			{
				a[valIndex] = a[i];
			}			
		}
	}
	return ++valIndex;
}

/*
Remove Duplicates from Sorted Array II
Follow up for "Remove Duplicates":
What if duplicates are allowed at most twice?

For example,
Given sorted array A = [1,1,1,2,2,3],  
Your function should return length = 5, and A is now [1,1,2,2,3].
*/
int removeDuplicatesAtMostTwo(int a[], int n) 
{	
	int valIndex = 0;
	int dup = 1;
	for (int i = 1; i < n; i++)
	{
		if (a[i] == a[valIndex])
		{
			if (dup < 2)
			{
				valIndex++;
				a[valIndex] = a[i];
				dup++;
			}
			else
			{
				continue;
			}
		}
		else
		{		
			valIndex++;
			if (valIndex < i)
			{
				a[valIndex] = a[i];
			}
			dup = 1;
		}
	}
	return valIndex+1;
}

void RunRemoveDup()
{
	int a[] = {1, 1, 2, 3, 3, 3, 4, 5, 6, 7, 7, 7, 7, 7, 8};
	int len = removeDuplicatesAtMostTwo(a, 15);
	cout << len << ":";
	for(int i = 0; i < len; i++)
	{
		cout << a[i] << ", ";
	}
	cout << endl;

	int a2[] = {1, 1, 2, 3, 3, 3, 4, 5, 6, 7, 7, 7, 7, 7, 8};
	int len2 = removeDuplicates(a2, 15);
	cout << len2 << ":";
	for(int i = 0; i < len2; i++)
	{
		cout << a2[i] << " ";
	}
	cout << endl;
}

int binarySearch(vector<int> a, int target)
{
	int l = 0;
	int r = a.size() - 1;
	while(l < r)
	{
		int mid = (l + r)/2;
		if (a[mid] == target)
		{
			return mid;
		}
		else if (target < a[mid])
		{
			r = mid - 1;
		}
		else 
		{
			l = mid + 1;
		}
	}
	if (a[l] == target)
	{
		return l;
	}

	return -1;
}


void RunBinarySearch()
{
	cout << "==== Binary Search ====" << endl;
	vector<int> a;
	for (int i = 0; i < 15; i++)
	{
		a.push_back(i);
		cout << i << ":" << a[i] << ",";
	}
	cout << endl;
	int pos = binarySearch(a, 7);
	cout << 7 << " at " << pos << endl;
	pos = binarySearch(a, 13);
	cout << 13 << " at " << pos << endl;
	pos = binarySearch(a, 1);
	cout << 1 << " at " << pos << endl;
	pos = binarySearch(a, 6);
	cout << 6 << " at " << pos << endl;
	pos = binarySearch(a, 14);
	cout << 14 << " at " << pos << endl;
}

/*
Search in Rotated Sorted Array 
Suppose a sorted array is rotated at some pivot unknown to you beforehand.
(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2). 
You are given a target value to search. If found in the array return its index, otherwise return -1. 
You may assume no duplicate exists in the array.
*/
int searchRotatedSortedArray(int a[], int n, int target)
{
	int l = 0; 
	int r = n-1;
	while(l <= r)
	{
		int mid = (l + r) / 2;
		if (target == a[mid]) { return mid; }
		if (a[l]<a[mid])
		{
			if (target <= a[mid] && target >= a[l])
			{
				r = mid - 1;
			}
			else
			{
				l = mid+1;
			}
		}
		else
		{
			if (target >= a[mid] && target <= a[r])
			{
				l = mid+1;
			}
			else
			{
				r = mid - 1;
			}
		}
	}

	return -1;
}

void RunSearchRotatedSortedArray()
{
	int b[] = {1, 3};				 

	searchRotatedSortedArray(b, 2, 0);

	int a[] = {7,8,9,10,11,12,13,14,15,1,2,3,4,5,6};
	for (int i = 0; i < 15; i++)
	{
		cout << i << ":" << a[i] << ",";
	}
	cout << endl;
	int pos = searchRotatedSortedArray(a, 15, 7);
	cout << 7 << " at " << pos << endl;
	pos = searchRotatedSortedArray(a, 15, 13);
	cout << 13 << " at " << pos << endl;
	pos = searchRotatedSortedArray(a, 15, 1);
	cout << 1 << " at " << pos << endl;
	pos = searchRotatedSortedArray(a, 15, 6);
	cout << 6 << " at " << pos << endl;
}

/*
Follow up for "Search in Rotated Sorted Array":
What if duplicates are allowed?

Would this affect the run-time complexity? How and why?

Write a function to determine if a given target is in the array.
*/
int searchRotatedSortedArray_II(int a[], int n, int target)
{
	int left = 0;
	int right = n - 1;
	while(left < right)
	{
		int mid = (left + right) / 2;
		if (a[mid] == target) return true;

		if (a[left] < a[mid])
		{
			if (target >= a[left] && target <= a[mid])
			{
				right = mid - 1;
				continue;
			}
			else
			{
				left = mid + 1;
				continue;
			}
		}
		else if (a[left] > a[mid])
		{
			if (target >= a[mid] && target <= a[right])
			{
				left = mid + 1;
				continue;
			}
			else
			{
				right = mid - 1;
				continue;
			}
		}
		else
		{
			int tmp = a[left];
			while(left <= mid && a[left] == tmp)
			{
				left++;
			}
		}
	}

	return false;
}

/* Add Two Numbers 
You are given two linked lists representing two non-negative numbers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
*/
ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) 
{
	if (l1 == NULL)
	{
		return l2;
	}
	if (l2 == NULL)
	{
		return l1;
	}

	ListNode* p1 = l1;
	ListNode* p2 = l2;
	ListNode* pre = NULL;
	ListNode* head = NULL;
	int carry = 0;
	while(p1 != NULL || p2 != NULL)
	{
		int value = 0;
		int tmp1 = 0; 
		int tmp2 = 0;

		if (p1 != NULL)
		{
			tmp1 = p1->val;
			p1 = p1->next;
		}
		if (p2 != NULL)
		{
			tmp2 = p2->val;
			p2 = p2->next;
		}
		value = tmp1 + tmp2 + carry;
		
		if (value >= 10)
		{
			value -= 10;
			carry = 1;
		}
		else 
		{
			carry = 0;
		}

		ListNode *node = new ListNode(value);
		
		if (pre != NULL)
		{
			pre->next = node;
			pre = node;
		}
		if (head == NULL)
		{
			head = node;		
			pre = node;
		}
	}
	if (carry > 0)
	{
		ListNode *n = new ListNode(1);
		pre->next = n;
	}

	return head;
}

/*
Longest Palindromic Substring 
Given a string S, find the longest palindromic substring in S. 
You may assume that the maximum length of S is 1000, and there exists one unique longest palindromic substring.
*/
string longestPalindrome(string s) {
	int len = s.length();
	if (len == 1) { return s; }
	if (len == 2) { return s; }
	int maxLen = 0;
	int pos = -1;
	for (int i = 1; i < len; i++)
	{
		int palLen = 1;
		int tmp = min(i, len - i - 1);
		for(int j = 1; j <= tmp; j++)
		{
			if (s.at(i-j) == s.at(i+j))
			{
				palLen+=2;
			}
			else
			{
				break;
			}
		}
		if (maxLen < palLen) { maxLen = palLen; pos = i; }
		palLen = 0;
		tmp = min(i, len - i);
		for(int k = 1; k <= tmp; k++)
		{
			if (s.at(i-k) == s.at(i+k-1))
			{
				palLen+=2;
			}
			else
			{
				break;
			}
		}
		if (maxLen < palLen) { maxLen = palLen; pos = i; }
	}
	string sub = s.substr(pos-maxLen/2, maxLen);
	return sub;
}

string longestPalindromeDP(string s) 
{
	int len = s.length();
	int** r = new int*[len];
	for(int i = 0; i < len; i++)
	{
		r[i] = new int[len];
		memset(r[i], 0, len * sizeof(int));
	}

	for(int i = 0; i < len; i++)
	{
		r[i][i] = 1;
		if (i < len-1 && s.at(i) == s.at(i+1))
		{
			r[i][i+1] = 2;
		}
	}		

	int maxLen = 2;
	int b = -1, e = -1;
	for(int i = len - 3; i >= 0; i--)
	{
		for (int j = i+2; j < len; j++)
		{
			if ((r[i+1][j-1] > 0) && s.at(i) == s.at(j))
			{
				r[i][j] = r[i+1][j-1] + 2;
				if (r[i][j] > maxLen) {maxLen = r[i][j]; b = i; e = j;}
			}
		}
	}

	cout << endl;
	for(int i = 0; i < len; i++)
	{
		for(int j = 0; j < len; j++)
		{
			cout << r[i][j] << " ";
		}
		
		cout << endl;
	}

	cout << "maxLen:" << maxLen << ",i:" << b << ",j:" << e << endl;

	string sub = s.substr(b, e-b+1);

	for(int i = 0; i < len; i++)
	{
		delete[] r[i];
	}
	delete r;

	return sub;
}

void RunLongestPalindrome()
{
	cout << "==== LongestPalindrome ====" << endl;
	string s = "abb";
	string sub = longestPalindrome(s);
	cout << sub.c_str() << endl;

	s = "ccb";
	sub = longestPalindrome(s);
	cout << sub.c_str() << endl;

	s = "ccbccbccd";
	sub = longestPalindrome(s);
	cout << sub.c_str() << endl;
}

void RunLongestPalindromeDP()
{
	string s = "abbaccddccabbabbdefedbba";
	cout << "==== LongestPalindromeDP ====" << endl;
	cout << s.c_str() << endl;
	
	string sub = longestPalindromeDP(s);
	cout << sub.c_str() << endl;
}

/*
Binary Tree Level Order Traversal
Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

For example:
Given binary tree {3,9,20,#,#,15,7},
3
/ \
9  20
/  \
15   7
return its level order traversal as:
[
[3],
[9,20],
[15,7]
]
*/
vector<vector<int> > PrintBinaryTreeByLevel(TreeNode* root)
{
	vector<vector<int> > r;
	if (root == NULL)
	{
		return r;
	}
	vector<int> cur;
	r.push_back(cur);

	queue<TreeNode*> q;
	int nextLevel = 0;
	int curLevel = 1;
	int printed = 0;
	q.push(root);
	while(!q.empty())
	{
		if (printed == curLevel)
		{
			//cout << endl;
			vector<int> next;
			r.push_back(next);
			curLevel = nextLevel;
			nextLevel = 0;
			printed = 0;
		}

		TreeNode *n = q.front();
		q.pop();
		if (n->left != NULL) { q.push(n->left); nextLevel++; }
		if (n->right != NULL) { q.push(n->right); nextLevel++; }
		r[r.size() - 1].push_back(n->val);
		printed++;
	}
	//reverse(r.begin(), r.end());
	return r;
}

/*
Given a binary tree, return the zigzag level order traversal of its nodes' values. (ie, from left to right, then right to left for the next level and alternate between).

For example:
Given binary tree {3,9,20,#,#,15,7},
3
/ \
9  20
/  \
15   7
return its zigzag level order traversal as:
[
[3],
[20,9],
[15,7]
]
*/
vector<vector<int> > zigzagLevelOrder(TreeNode *root)
{
	vector<vector<int> > r;
	if (root == NULL)
	{
		return r;
	}
	vector<int> cur;
	r.push_back(cur);

	queue<TreeNode*> q;
	int nextLevel = 0;
	int curLevel = 1;
	int printed = 0;
	q.push(root);
	bool ltor = true;
	while(!q.empty())
	{
		if (printed == curLevel)
		{
			if (!ltor)
			{
				reverse(r[r.size() - 1].begin(), r[r.size() - 1].end());
			}
			ltor = !ltor;
			vector<int> next;
			r.push_back(next);
			curLevel = nextLevel;
			nextLevel = 0;
			printed = 0;
		}

		TreeNode *n = q.front();
		q.pop();
		if (n->left != NULL) { q.push(n->left); nextLevel++; }
		if (n->right != NULL) { q.push(n->right); nextLevel++; }
		r[r.size() - 1].push_back(n->val);
		printed++;
	}
	if (!ltor)
	{
		reverse(r[r.size() - 1].begin(), r[r.size() - 1].end());
	}
	return r;
}

void DeleteTree(TreeNode* root)
{
	if (root == NULL)
	{
		return;
	}
	DeleteTree(root->left);
	DeleteTree(root->right);
	cout << "delete " << root->val << endl;
	delete root;
}

void RunPrintBinaryTreeByLevel()
{
	TreeNode* root = new TreeNode(1);
	root->left = new TreeNode(2);
	root->right = new TreeNode(3);
	root->left->right = new TreeNode(4);
	root->right->left = new TreeNode(5);
	root->right->left->left = new TreeNode(7);

	cout << "==== RunPrintBinaryTreeByLevel ====" << endl;
 	vector<vector<int> > r = PrintBinaryTreeByLevel(root);
	for (size_t i = 0; i < r.size(); i++)
	{
		PrintVecotr(r[i]);
	}

	DeleteTree(root);
}

/*
Longest Consecutive Sequence 
Given an unsorted array of integers, find the length of the longest consecutive elements sequence.

For example,
Given [100, 4, 200, 1, 3, 2],
The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.

Your algorithm should run in O(n) complexity.
*/
int longestConsecutive(const vector<int> &num) 
{
	map<int, int> numMap;

	for(size_t i = 0; i < num.size(); i++)
	{
		numMap[num[i]] = 1;
	}

	int maxLen = 0;
	
	int s, e;
	for (size_t i = 0; i < num.size(); i++)
	{
		if (numMap[num[i]] != 1)
		{
			continue;
		}
		int len = 0;
		size_t j;
		size_t k;
		for(j = 1; j < num.size() - 1; j++)
		{
			if (numMap.find(num[i]+j) == numMap.end())
			{				
				break;				
			}
			len++;
			numMap[num[i]+j] = -1;
		}
		for(k = 1; k < num.size() - 1; k++)
		{
			if (numMap.find(num[i]-k) == numMap.end())
			{
				break;
			}
			len++;
			numMap[num[i]-k] = -1;
		}
		numMap[num[i]] = -1;
		if (maxLen < len) { maxLen = len; s = num[i] - k + 1; e = num[i] + j - 1; }
	}

	cout << s << " - " << e << ":" << maxLen << endl;
	return maxLen; 
}

void RunLongestConsecutive()
{
	vector<int> num;
	num.push_back(100);
	num.push_back(1);
	num.push_back(4);
	num.push_back(3);
	num.push_back(20);
	num.push_back(2);
	num.push_back(11);
	num.push_back(12);
	num.push_back(13);
	num.push_back(8);
	num.push_back(9);
	num.push_back(15);
	num.push_back(14);
	num.push_back(10);

	int len = longestConsecutive(num);
}

/*
Plus One 
Given a non-negative number represented as an array of digits, plus one to the number.	  
The digits are stored such that the most significant digit is at the head of the list.
*/
vector<int> plusOne(vector<int> &digits) 
{
	int carry = 1;
	for(int i = digits.size() - 1; i >= 0 && carry > 0; i--)
	{
		int val = digits[i] + carry;
		if (val >= 10)
		{
			val -= 10;
			carry = 1;
		}
		else
		{
			carry = 0;
		}
		digits[i] = val;
	}
	if (carry > 0)
	{
		digits.insert(digits.begin(), 1);
	}
	return digits;
}


void RunPlusOne()
{
	cout << "==== Plus One ====" << endl;
	vector<int> num;
	num.push_back(6);
	num.push_back(9);
	num.push_back(9);
	num.push_back(9);
	num.push_back(9);
	num.push_back(9);
	plusOne(num);
	PrintVecotr(num);
}

/*
Climbing Stairs 
You are climbing a stair case. It takes n steps to reach to the top. 
Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
*/
int climbStairs(int n) 
{
	if (n == 1) { return 1; }
	if (n == 2) { return 2; }
	int prevprev = 1;
	int prev = 2;
	int result = 0;
	for(int i = 3; i <= n; i++)
	{
		result = prevprev + prev;
		prevprev = prev;
		prev = result;		
	}
	return result;
}

void RunClimbStairs()
{
	cout << "==== Climb Stairs ====" << endl;
	int r = climbStairs(3);
	cout << "3: " << r << endl;
	r = climbStairs(9);
	cout << "9: " << r << endl;
}

/*
Set Matrix Zeroes 
Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in place.

Follow up:
Did you use extra space?
A straight forward solution using O(mn) space is probably a bad idea.
A simple improvement uses O(m + n) space, but still not the best solution.
Could you devise a constant space solution?
*/
void setZeroes(vector<vector<int> > &matrix)
{
	if (matrix.empty()) { return; }

	int r = matrix.size();
	int c = matrix[0].size();
	bool *row = new bool[r];
	memset(row, 0, sizeof(bool)*r);
	bool *col = new bool[c];
	memset(col, 0, sizeof(bool)*c);
	
	for(int i = 0; i < r; i++)
	{
		for(int j = 0; j < c; j++)
		{
			if (matrix[i][j] == 0)
			{
				row[i] = true;
				col[j] = true;
			}
		}
	}

	for(int i = 0; i < r; i++)
	{
		if (row[i] == true)
		{
			fill(matrix[i].begin(), matrix[i].end(), 0);
		}
	}
	for (int i = 0; i < c; i++)
	{
		if (col[i] == true)
		{
			for (int j = 0; j < r; j++)
			{
				matrix[j][i] = 0;
			}
		}
	}

	delete[] row;
	delete[] col;
}

void setZeroesII(vector<vector<int> > &matrix)
{
	if (matrix.empty()) { return; }

	const size_t m = matrix.size();
	const size_t n = matrix[0].size();
	bool row_has_zero = false; // 第一行是否存在0
	bool col_has_zero = false; // 第一列是否存在0
	for (size_t i = 0; i < n; i++) 
	{
		if (matrix[0][i] == 0) 
		{
			row_has_zero = true;
			break;
		}
	}
	for (size_t i = 0; i < m; i++)
	{
		if (matrix[i][0] == 0) 
		{
			col_has_zero = true;
			break;
		}
	}
	for (size_t i = 1; i < m; i++)
	{
		for (size_t j = 1; j < n; j++)
		{
			if (matrix[i][j] == 0) {
				matrix[0][j] = 0;
				matrix[i][0] = 0;
			}
		}
	}
	for (size_t i = 1; i < m; i++)
	{
		for (size_t j = 1; j < n; j++)
		{
			if (matrix[i][0] == 0 || matrix[0][j] == 0)
			{
				matrix[i][j] = 0;
			}
		}
	}
	if (row_has_zero)
	{
		for (size_t i = 0; i < n; i++)
		{
			matrix[0][i] = 0;
		}
	}
	if (col_has_zero)
	{
		for (size_t i = 0; i < m; i++)
		{
			matrix[i][0] = 0;
		}
	}
}

void RunZeorMatrix()
{
	vector<vector<int> > matrix;
	int r[] = {9, 1, 2, 3, 4, 5, 6, 7, 8};
	vector<int> row1(r, r + sizeof(r)/sizeof(int));
	vector<int> row2(r, r + sizeof(r)/sizeof(int));
	row2[1] = 0;
	vector<int> row3(r, r + sizeof(r)/sizeof(int));
	row3[4] = 0;
	vector<int> row4(r, r + sizeof(r)/sizeof(int));
	vector<int> row5(r, r + sizeof(r)/sizeof(int));
	vector<int> row6(r, r + sizeof(r)/sizeof(int));
	row6[8] = 0;
	vector<int> row7(r, r + sizeof(r)/sizeof(int));
	matrix.push_back(row1);
	matrix.push_back(row2);
	matrix.push_back(row3);
	matrix.push_back(row4);
	matrix.push_back(row5);
	matrix.push_back(row6);
	matrix.push_back(row7);

	for(size_t i = 0; i < matrix.size(); i++)
	{
		PrintVecotr(matrix[i]);
	}
	cout << "----" << endl;
	setZeroesII(matrix);
	cout << "==== Zero Matrix ====" << endl;
	for(size_t i = 0; i < matrix.size(); i++)
	{
		PrintVecotr(matrix[i]);
	}
}

ListNode *reverseBetween(ListNode *head, int m, int n) 
{
	if (head == NULL) return NULL;
	if (head->next == NULL) return head;

	ListNode *p = head;
	int index = 0;
	ListNode *preHalf = NULL;
	ListNode *midTail = NULL;
	ListNode *midHead = NULL;
	ListNode *pre = NULL;
	ListNode *tmp = NULL;
	while(p != NULL)
	{
		index++;
		if (index < m){ preHalf = p; p=p->next; continue; }
		if (index == m) 
		{
			midTail = p;
		}
		if (index == n)
		{
			midHead = p;
		}
		else if (index > n)
		{
			if (preHalf != NULL)
			{
				preHalf->next = midHead;
			}
			midTail->next = p;
			break;
		}
		tmp = p->next;
		p->next = pre;
		pre = p;
		p = tmp;
	}

	if (m == 1)
	{
		return midHead;
	}
	else
	{
		return head;
	}
}

ListNode* doPrintList(ListNode* head)
{
	if (head == NULL) return NULL;
	cout << head->val << ", ";
	doPrintList(head->next);
	return head;
}

ListNode* PrintList(ListNode *head)
{
 	ListNode* h = doPrintList(head);
	cout << endl;
	return h;
}

void DeleteList(ListNode *head)
{
	if (head == NULL) return;
	ListNode *p = head->next;
	cout << "delete " << head->val << endl;
	delete head;
	DeleteList(p);
}

void RunReverseBetween()
{
	ListNode *head = new ListNode(1);
	ListNode *p = head;
	for (int i = 0; i < 10; i++)
	{
		p->next = new ListNode(i+2);
		p = p->next;
	}
	cout << "==== reverse between ====" << endl;
	doPrintList(head);
	cout << endl;
 	doPrintList(reverseBetween(head, 2, 5));
	cout << endl;
	doPrintList(reverseBetween(head, 2, 5));
	cout << endl;
	doPrintList(reverseBetween(head, 1, 1));
	cout << endl;
	doPrintList(reverseBetween(head, 11, 11));
	cout << endl;
	ListNode *newHead = doPrintList(reverseBetween(head, 1, 11));
	cout << endl;
	DeleteList(newHead);
}

/*
Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two partitions.

For example,
Given 1->4->3->2->5->2 and x = 3,
return 1->2->2->4->3->5.
*/
ListNode* partitionList(ListNode* head, int x)
{
	if (head == NULL) return NULL;
	if (head->next == NULL) return head;

	ListNode* smallHead = NULL, *smallTail = NULL, *bigHead = NULL, *bigTail = NULL;
	ListNode* p = head;
	while(p != NULL)
	{
		if (p->val < x)
		{
			if (smallHead == NULL)
			{
				smallHead = p;
			}
			else
			{
				smallTail->next = p;
			}
			smallTail = p;
		}
		else
		{
			if (bigHead == NULL)
			{
				bigHead = p;				
			}
			else
			{
				bigTail->next = p;
			}
			bigTail = p;
		}
		p=p->next;
	}
	if (bigTail != NULL)
	{
		bigTail->next = NULL;
	}
	if (smallTail != NULL)
	{
		smallTail->next = bigHead;
		return smallHead;
	}
	else
	{
		return bigHead;
	}
}

ListNode* partitionList_2(ListNode* head, int x)
{
	ListNode smallHead(-1), bigHead(-1);
	ListNode *curS = &smallHead;
	ListNode *curB = &bigHead;
	ListNode* p = head;
	while(p != NULL)
	{
		if (p->val < x)
		{
			curS->next = p;
			curS = p;
		}
		else
		{
			curB->next = p;
			curB = p;
		}
		p=p->next;
	}
	curS->next = bigHead.next;
	curB->next = NULL;
	return smallHead.next;
}

void RunPartitionList()
{
	ListNode *head = new ListNode(1);
	ListNode *p = head;
	for (int i = 10; i > 0; i--)
	{
		p->next = new ListNode(i+2);
		p = p->next;
	}
	cout << "==== partition list ====" << endl;
	doPrintList(head);
	cout << endl;
	ListNode* h = partitionList_2(head, 10);
	doPrintList(h);
	cout << endl;
	DeleteList(h);
}

/*
Given a sorted linked list, delete all duplicates such that each element appear only once.

For example,
Given 1->1->2, return 1->2.
Given 1->1->2->3->3, return 1->2->3.
*/
ListNode *deleteDuplicates(ListNode *head)
{
	if (head == NULL) return NULL;
	ListNode dummy(head->val+1);
	ListNode *cur = head;
	ListNode *pre = &dummy;
	while(cur != NULL)
	{
		if (cur->val != pre->val)
		{
			pre->next = cur;
			pre = cur;
			cur = cur->next;	
		}
		else
		{
			ListNode* tmp = cur;
			cur = cur->next;	
			cout << "delete " << tmp->val << endl;
			delete tmp;			
		}			
	}
	pre->next = NULL;
	return dummy.next;
}

void RunDeleteDuplicates()
{
	ListNode *head = new ListNode(1);
	ListNode *p = head;
	for (int i = 2; i < 20; i++)
	{
		p->next = new ListNode(i/2 + 1);
		p = p->next;
	}

	cout << "==== delete dup ====" << endl;
	doPrintList(head);
	cout << endl;
	ListNode* h = deleteDuplicates(head);
	doPrintList(h);
	cout << endl;

	DeleteList(h);
}

/*
Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.

For example,
Given 1->2->3->3->4->4->5, return 1->2->5.
Given 1->1->1->2->3, return 2->3.
*/
ListNode *deleteDuplicatesII(ListNode *head)
{
	if (head == NULL) return NULL;
	ListNode dummy(head->val+1);
	ListNode *pre = &dummy;
	ListNode *cur = head;
	while(cur != NULL)
	{
		ListNode *p = cur->next;
		while(p != NULL && p->val == cur	->val)
		{
			ListNode *tmp = p;
			p = p->next;
			cout << "delete " << tmp->val << endl;
			delete tmp;
		}
		if (p != cur->next)
		{
			cout << "delete " << cur->val << endl;
			delete cur;
			cur = p;
			continue;
		}
		else
		{
			pre->next = cur;
			pre = cur;
			cur	= cur->next;
		}
	}
	pre->next = NULL;
	return dummy.next;
}

ListNode *deleteDuplicatesRecursive(ListNode *head)
{
	if (head == NULL) return NULL;
	if (head->next == NULL) return head;
 	ListNode *p = head->next;
	while(p != NULL && p->val == head->val)
	{
		ListNode *tmp = p->next;
		cout << "delete " << p->val << endl;
		delete p;
		p = tmp;
	}
	if (p != head->next)
	{
		ListNode* h = deleteDuplicatesRecursive(p);
		cout << "delete " << head->val << endl;
		delete head;

		return h;
	}
	else
	{
		head->next = deleteDuplicatesRecursive(head->next);
		return head;
	}
	
}

void RunDeleteDuplicatesII()
{
	ListNode *head = new ListNode(1);
	ListNode *p = head;
	for (int i = 2; i < 20; i++)
	{
		p->next = new ListNode(i/2 + 1);
		p = p->next;
	}
	for (int i = 0; i < 10; i++)
	{
		p->next = new ListNode(100 + i);
		p= p->next;
	}

	cout << "==== delete dup II====" << endl;
	doPrintList(head);
	cout << endl;
	ListNode* h = deleteDuplicatesRecursive(head);
	doPrintList(h);
	cout << endl;

	DeleteList(h);
}

/*
Given a list, rotate the list to the right by k places, where k is non-negative.

For example:
Given 1->2->3->4->5->NULL and k = 2,
return 4->5->1->2->3->NULL.
*/
ListNode *rotateRight(ListNode *head, int k)
{
	if (head == NULL) return NULL;
	if (head->next == NULL) return head;

	ListNode *p = head;
	int len = 0;
	while(p->next != NULL)
	{
		len++;
		p=p->next;
	}
	len++;
	p->next = head;
	int i;
	for(p = head, i = 1; i < len - k%len; i++, p=p->next)
	{
		;
	}
	ListNode *newHead = p->next;
	p->next = NULL;
	return newHead;
}

void RunRotateRight()
{
	ListNode *head = new ListNode(1);
	ListNode *p = head;
	for (int i = 2; i <= 10; i++)
	{
		p->next = new ListNode(i);
		p = p->next;
	}

	cout << "==== rotate right ====" << endl;
	doPrintList(head);
	cout << endl;
	ListNode* h = rotateRight(head, 2);
	doPrintList(h);
	cout << endl;
	DeleteList(h);
}

/*
Given a linked list, remove the nth node from the end of list and return its head.

For example,

Given linked list: 1->2->3->4->5, and n = 2.

After removing the second node from the end, the linked list becomes 1->2->3->5.
Note:
Given n will always be valid.
Try to do this in one pass.
*/
ListNode *removeNthFromEnd(ListNode *head, int n)
{
	if (head == NULL) return NULL;
	ListNode *p = head;
	ListNode *q = head;
	for(int i = 0; i < n-1; i++)
	{
		p = p->next;
	}
	ListNode dummp(0);
	dummp.next = head;
	ListNode *pre = &dummp;
	while(p->next != NULL)
	{
		p = p->next;
		pre = q;
		q = q->next;
	}
	ListNode *tmp = q;
	pre->next = q->next;
	DeleteNode(tmp);
	return dummp.next;
}

void RunRemoveNthFromEnd()
{
	ListNode *head = new ListNode(1);
	ListNode *p = head;
	for (int i = 2; i <= 10; i++)
	{
		p->next = new ListNode(i);
		p = p->next;
	}

	cout << "==== Remove Nth from end ====" << endl;
	PrintList(head);
 	ListNode *h = removeNthFromEnd(head, 6);
	PrintList(h);
	DeleteList(h);
}

/*
Swap Nodes in Pairs
Given a linked list, swap every two adjacent nodes and return its head.

For example,
Given 1->2->3->4, you should return the list as 2->1->4->3.

Your algorithm should use only constant space. You may not modify the values in the list, only nodes itself can be changed.
*/
ListNode *swapPairs(ListNode *head)
{
	if (head == NULL) return NULL;
	ListNode *p1 = head;
	ListNode *p2 = head->next;
	ListNode dummy(0);
	dummy.next = head;
	ListNode *pre = &dummy;
	while(p1 != NULL && p2 != NULL)
	{
		ListNode *tmp = p2->next;
		p2->next = p1;
		pre->next = p2;
		p1->next = tmp;
		pre = p1;

		p1 = tmp;
		if (p1 == NULL)
		{
			break;
		}
		p2 = p1->next;
	}

	return dummy.next;
}

void RunSwapPairs()
{
	ListNode *head = new ListNode(1);
	ListNode *p = head;
	for (int i = 2; i <= 20; i++)
	{
		p->next = new ListNode(i);
		p = p->next;
	}

	cout << "==== Sawp Pairs ====" << endl;
	PrintList(head);
	ListNode* h = swapPairs(head);
	PrintList(h);
	DeleteList(h);
}

ListNode *reverseList(ListNode *head, ListNode *tail)
{
	ListNode *pre = NULL;
	
	for(ListNode* p = head; p != tail;)
	{
		ListNode *tmp = p->next;
		p->next = pre;
		pre = p;
		p = tmp;
	}
	tail->next = pre;
	return tail;
}

/*
Reverse Nodes in k-Group 
Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.	 
If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is. 
You may not alter the values in the nodes, only nodes itself may be changed.					
Only constant memory is allowed.   
For example,
Given this linked list: 1->2->3->4->5	 
For k = 2, you should return: 2->1->4->3->5	  
For k = 3, you should return: 3->2->1->4->5
*/
ListNode *reverseKGroup(ListNode *head, int k) 
{
	if (head == NULL) return NULL;
	ListNode dummy(0);
	dummy.next = head;
	ListNode* preTail = &dummy;
	ListNode* h = head;
	while(true)
	{
		ListNode* p = h;
		for (int i = 1; i < k && p != NULL; i++, p = p->next)
		{
			;
		}
		if (p == NULL)
		{
			preTail->next = h;
			break;
		}
		ListNode* tmp = p->next;

		ListNode* t = p;
		ListNode* newHead = reverseList(h, t);
		ListNode* newTail = h;
		preTail->next = newHead;
		preTail = newTail;
		h = tmp;
	}

	return dummy.next;
}

ListNode *reverseKGroupRecursive(ListNode *head, int k) 
{
	if (head == NULL) return NULL;
	ListNode dummy(0);
	dummy.next = head;
	ListNode* preTail = &dummy;
	//todo
	return NULL;
}

void RunReverseKGroup()
{
	ListNode *head = new ListNode(1);
	ListNode *p = head;
	for (int i = 2; i <= 21; i++)
	{
		p->next = new ListNode(i);
		p = p->next;
	}
	
	cout << "==== Reverse KGroup ====" << endl;
	PrintList(head);
	ListNode* h = reverseKGroup(head, 20);
	PrintList(h);
	DeleteList(h);
}

int reverseInt(int x)
{
	int neg = 1;
	if (x < 0) { neg = -1; x = -1 * x;}
	int result = 0;
	for (; x > 0; x = x / 10)
	{
		int t = x % 10;
		result = result * 10 + t; 
	}
	return result * neg;
}

/*
String to Integer (atoi) 
Implement atoi to convert a string to an integer.	   
Hint: Carefully consider all possible input cases. 
If you want a challenge, please do not see below and ask yourself what are the possible input cases.	
Notes: It is intended for this problem to be specified vaguely (ie, no given input specs). 
You are responsible to gather all the input requirements up front.
*/
int myatoi(const char *str)
{
	int result = 0;
	int sign = 1;
	bool leadingspace = true;
	bool haveSign = false;
	const char *p = str;
	for(; *p != '\0'; p++)
	{
		char c = *p;
		if (c == ' ')
		{
			if (leadingspace) continue;
			else return result * sign;
		}
		if (c == '+' || c == '-')
		{
			if (haveSign)
			{
				return result * sign;
			}
			if (c == '-') 
			{
				sign = -1;
			}
			haveSign = true;
			leadingspace = false;
			continue;
		}
		if (c > '9' || c < '0')
		{
			return result * sign;
		}
		leadingspace = false;
		int v = c - '0';
		if (sign == 1 && (INT_MAX - v)/10 < result) {return INT_MAX;}
		if (sign == -1 && (INT_MAX - v)/10 < result) {return INT_MIN;}
		result = result * 10 + v;
	}

	return result * sign;
}

void RunAoti()
{
	const char *p = "  +0 123";
	cout << myatoi(p);
}

/*
Palindrome Number 
Determine whether an integer is a palindrome. Do this without extra space.
*/
bool isPalindrome(int x) {
	if (INT_MIN == x) return false;
	if (x < 0) return false;
	int high = 1;
	for(high = 1; ; high = high * 10)
	{
		if (x / high < 10)
		{
			break;
		}
	}
	while (high > 0)
	{
		int h = x / high;
		int l = x % 10;
		if (h != l)
		{
			return false;
		}
		x = (x - (h * high)) / 10;
		high /= 100;
	}
	return true;
}

void RunIsPalindrome()
{
	isPalindrome(1000021);
}

struct RandomListNode 
{
	int val;
	RandomListNode *next;
	RandomListNode *random;
	RandomListNode(int v) : val(v), next(NULL), random(NULL) {}
};

/*
A linked list is given such that each node contains an additional random pointer 
which could point to any node in the list or null.

Return a deep copy of the list.
*/
RandomListNode *copyRandomList(RandomListNode *head)
{
	if (head == NULL) return head;

	for (RandomListNode *p = head; p != NULL;)
	{
		RandomListNode *node = new RandomListNode(p->val);
		RandomListNode *tmp = p->next;
		p->next = node;
		node->next = tmp;
		p = tmp;
	}

	for (RandomListNode *p = head; p != NULL;)
	{
		if (p->random != NULL)
		{
			p->next->random = p->random->next;
		}
		p=p->next->next;
	}

	RandomListNode dummy(0);
	RandomListNode *cur = &dummy;
	for (RandomListNode *p = head; p != NULL;)
	{
		cur->next = p->next;
		cur = p->next;
		p->next = p->next->next;
		p = p->next;
	}

	return dummy.next;
}

void PrintRandomList(RandomListNode* head)
{
	for (RandomListNode *p = head; p != NULL; p = p->next)
	{
		cout << p->val << " ";
		if (p->random != NULL) { cout << "random: " << p->random->val << ". "; }
	}
	cout << endl;
}

void DeleteRandomList(RandomListNode *head)
{
	for (RandomListNode *p = head; p!= NULL;)
	{
		RandomListNode *tmp = p->next;
		cout << "delete " << p->val; 
		//if (p->randmon != NULL) { cout << ",random " << p->randmon->val; }
		cout << endl;
		delete p;
		p = tmp;
	}
}

void RunCopyRandomList()
{
	RandomListNode head(0);
	RandomListNode p1(1);
	RandomListNode p2(2);
	RandomListNode p3(3);
	RandomListNode p4(4);
	RandomListNode p5(5);

	cout << "==== Copy Random Pointer List ====" << endl;
	head.next = &p1;
	head.random = &p1;
	p1.next = &p2;
	p2.next = &p3;
	p2.random = &p5;
	p3.next = &p4;
	p3.random = &p5;
	p4.next = &p5;
	cout << "orig: ";
	PrintRandomList(&head);
	RandomListNode *n = copyRandomList(&head);
	cout << "copied: ";
	PrintRandomList(n);
	DeleteRandomList(n);	
}

/*
Given a singly linked list L: L0→L1→…→Ln-1→Ln,
reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…

You must do this in-place without altering the nodes' values.

For example,
Given {1,2,3,4}, reorder it to {1,4,2,3}.
*/
bool hasCycle(ListNode *head)
{
	if (head == NULL || head->next == NULL) return false;
	ListNode *fast = head;
	ListNode *slow = head;
	while(fast != NULL && fast->next != NULL)
	{
		slow = slow->next;
		fast = fast->next->next;
		if (fast == slow) { return true; }
	}
	return false;
}

ListNode* ReverseList(ListNode* head)
{
	ListNode dummy(0);
	dummy.next = head;
	for (ListNode* cur = head->next; cur != NULL;)
	{
		ListNode *tmp = cur->next;
		cur->next = dummy.next;
		dummy.next = cur;
		cur = tmp;
	}
	head->next = NULL;
	return dummy.next;
}

/*
Given a singly linked list L: L0→L1→…→Ln-1→Ln,
reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…				   
You must do this in-place without altering the nodes' values. 
For example,
Given {1,2,3,4}, reorder it to {1,4,2,3}.
*/
void reorderList(ListNode *head)
{
	if (head == NULL || head->next == NULL) return;
	ListNode* slow = head;
	ListNode* fast = head;
	while(fast != NULL && fast->next != NULL)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	ListNode *mid;
	if (fast == NULL)
	{
		mid = slow;
	}
	else
	{
		mid = slow->next;
	}
	// reverse mid
	ListNode* reversed = ReverseList(mid);
	ListNode *p1 = head, *p2 = reversed;
	while (p2 != NULL)
	{
		ListNode *tmp1 = p1->next;
		ListNode *tmp2 = p2->next;
		p1->next = p2;
		p2->next = tmp1;
		p1 = tmp1;
		p2 = tmp2;
	}
	if (p1 != NULL) p1->next = NULL;
}

void RunReorderList()
{
	ListNode p1(1);
	ListNode p2(2);
	ListNode p3(3);
	ListNode p4(4);
	ListNode p5(5);
	ListNode p6(6);
	ListNode p7(7);
	p1.next = &p2;
	p2.next = &p3;
	p3.next = &p4;
	p4.next = &p5;
	p5.next = &p6;
	p6.next = &p7;

	cout << "==== Reorder List ====" << endl;
	PrintList(&p1);
	reorderList(&p1);
	PrintList(&p1);
}

/*
Evaluate the value of an arithmetic expression in Reverse Polish Notation.	 
Valid operators are +, -, *, /. Each operand may be an integer or another expression.	  
Some examples:
["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6
*/
int evalRPN(vector<string> &tokens) 
{
	stack<int> s;
	for (size_t i = 0; i < tokens.size(); i++)
	{
		string t = tokens.at(i);
		if (strcmp(t.c_str(), "+") == 0)
		{
			int x = s.top();
			s.pop();
			int y = s.top();
			s.pop();
			int v = x+y;
			s.push(v);
		}
		else if (strcmp(t.c_str(), "-") == 0)
		{
			int x = s.top();
			s.pop();
			int y = s.top();
			s.pop();
			int v = y-x;
			s.push(v);
		}
		else if (strcmp(t.c_str(), "*") == 0)
		{
			int x = s.top();
			s.pop();
			int y = s.top();
			s.pop();
			int v = x*y;
			s.push(v);
		}
		else if (strcmp(t.c_str(), "/") == 0)
		{
			int x = s.top();
			s.pop();
			int y = s.top();
			s.pop();
			int v = y/x;
			s.push(v);
		}
		else
		{
			int v = stoi(t);
			s.push(v);
		}
	}
	return s.top();
}

void RunEvalRPN()
{
	vector<string> tokens;
	tokens.push_back("2");
	tokens.push_back("1");
	tokens.push_back("+");
	tokens.push_back("3");
	tokens.push_back("*");
	cout << "==== eval RPN ====" << endl;
	int v = evalRPN(tokens);
	PrintVecotr(tokens);
	cout << v << endl;
}

/*
Largest Rectangle in Histogram 
Given n non-negative integers representing the histogram's bar height 
where the width of each bar is 1, find the area of largest rectangle in the histogram.

Above is a histogram where width of each bar is 1, given height = [2,1,5,6,2,3].

The largest rectangle is shown in the shaded area, which has area = 10 unit.

For example,
Given height = [2,1,5,6,2,3],
return 10.
*/
int largestRectangleArea(vector<int> &height)
{
	stack<int> s;
	height.push_back(0);
	int result = 0;
	for (size_t i = 0; i < height.size(); i++)
	{
		int cur = height[i];
		if (s.empty() || cur > height[s.top()])
		{
			s.push(i);
		}
		else
		{
			while (!s.empty())
			{
				int top = s.top();
				if (height[top] < cur) break;
				s.pop();
				int r = height[top] * (s.empty()?i:i - s.top()-1);
				if (r > result) result = r;
			}
			s.push(i);
		}
	}
	return result;
}

void RunLargestRectangleArea()
{
	vector<int> h;
	h.push_back(2);
	h.push_back(1);
	h.push_back(2);
	//h.push_back(6);
	//h.push_back(2);
	//h.push_back(3);

	cout << "==== Largest Rectangle Area ====" << endl;
	PrintVecotr(h);
	int r = largestRectangleArea(h);
	cout << r << endl;
}

vector<int> preorderTraversal(TreeNode *root)
{
	vector<int> r;
	stack<TreeNode*> s;
	TreeNode *n = root;
	while(!s.empty() || n != NULL)
	{
		if (n == NULL)
		{
			n = s.top();
			s.pop();
			continue;
		}
		r.push_back(n->val);
		if(n->right != NULL) { s.push(n->right); }
		n = n->left;
	}
	return r;
}

void RunPreorderTraversal()
{
	TreeNode root(0);
	TreeNode n1(1), n2(2), n3(3), n4(4), n5(5), n6(6);
	root.left = &n1;
	root.right = &n2;
	n1.left = &n3;
	n1.right = &n4;
	n2.left = &n5;
	n2.right = &n6;

	cout << "==== Pre order traversal ====" << endl;
	vector<int> r = preorderTraversal(&root);
	PrintVecotr(r);
}

vector<int> inorderTraversal(TreeNode *root) 
{
	vector<int> r;
	stack<TreeNode*> s;
	TreeNode*p = root;
	while(p != NULL || !s.empty())
	{
		if (p == NULL)
		{
			TreeNode *top = s.top();
			s.pop();
			r.push_back(top->val);
			p = top->right;
			continue;
		}
		s.push(p);
		p = p->left;
	}
	return r;
}

vector<int> postorderTraversal(TreeNode *root)
{
	vector<int> res;
	if (root == NULL) return res;
	
	stack<TreeNode*> s1;
	stack<TreeNode*> s2;
	s1.push(root);
	while(!s1.empty())
	{
		TreeNode *p = s1.top();
		s1.pop();
		s2.push(p);
		
		if (p->left)
		{
			s1.push(p->left);
		}
		if (p->right)
		{
			s1.push(p->right);
		}
	}
	
	while(!s2.empty())
	{
		TreeNode *p = s2.top();
		res.push_back(p->val);
		s2.pop();
    }
	return res;
}

/*
Given two binary trees, write a function to check if they are equal or not.

Two binary trees are considered equal if they are structurally identical and the nodes have the same value.
*/
bool isSameTree(TreeNode *p, TreeNode *q)
{
	if (p==NULL && q==NULL) {return true;}
	if (p==NULL || q==NULL) {return false;}
	if (p->val != q->val) {return false;}
	if (!isSameTree(p->left, q->left)) {return false;}
	if (!isSameTree(p->right, q->right)) {return false;}
	return true;
	/*
	if (p->val == q->val && isSameTree(p->left,q->left) && isSameTree(p->right, q->right))
	{
		return true;
	}
	return false;
	*/
}

/*
Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).	
For example, this binary tree is symmetric:

1
/ \
2   2
/ \ / \
3  4 4  3
But the following is not:
1
/ \
2   2
\   \
3    3
Note:
Bonus points if you could solve it both recursively and iteratively.
*/
bool isSymmetric(TreeNode *root) 
{
	if (root == NULL) return true;
	queue<TreeNode*> lq;
	queue<TreeNode*> rq;
	TreeNode* left = root->left;
	TreeNode* right = root->right;
	if (left != NULL) lq.push(left);
	if (right != NULL) rq.push(right);

	while (!lq.empty() && !rq.empty())
	{
		left = lq.front();
		lq.pop();
		right = rq.front();
		rq.pop();

		if (left != NULL && right != NULL)
		{
			if (left->val != right->val) return false;
		}
		else if(left != NULL || right != NULL)
		{
			return false;
		}

		if (left != NULL)
		{
			lq.push(left->left);
			lq.push	(left->right);
		}

		if (right != NULL)
		{
			rq.push(right->right);
			rq.push(right->left);
		}
	}

	if (!lq.empty() || !rq.empty()) return false;

	return true;
}

bool isMirror(TreeNode* left, TreeNode *right)
{
	if (left == NULL && right == NULL)
	{
		return true;
	}
	if(left == NULL || right == NULL)
	{
		return false;
	}
	if (left->val != right->val)
	{
		return false;
	}
	if (!isMirror(left->left, right->right))
	{
		return false;
	}
	if (!isMirror(left->right, right->left))
	{
		return false;
	}
	return true;
}

bool isSymmetricR(TreeNode *root) 
{
	if (root == NULL) return true;

	return isMirror(root->left, root->right);
}

/*
Balanced Binary Tree
Given a binary tree, determine if it is height-balanced.  
For this problem, a height-balanced binary tree is defined as a binary tree 
in which the depth of the two subtrees of every node never differ by more than 1.
*/
int getBalancedHeight (TreeNode *root)
{
	if (root == NULL) { return 0;}
	int l = getBalancedHeight(root->left);
	if (l < 0) return -1;
	int r = getBalancedHeight(root->right);
	if (r < 0) return -1;
	if (abs(l - r) > 1) return -1;
	return max(l, r)+1;
}

bool isBalanced (TreeNode* root) 
{
	int maxh = 0, minh = 0;
	int h = getBalancedHeight(root);
	if (h >= 0) return true;
	return false;
}

bool isBalanced(TreeNode *root, int* height)
{
	if (root == NULL) { *height = 0; return true; }
	int l, r;
	bool lb = isBalanced(root->left, &l);
	bool rb = isBalanced(root->right, &r);
	*height = max(l, r)+1;
	if (!lb || !rb) return false;
	if (abs(l-r) > 1) return false;
	return true;
}

bool isBalanced2 (TreeNode* root) 
{
	if (root == NULL) return true;
	
	int h = 0;
	return isBalanced(root, &h);
}

void RunIsBalanced()
{
	TreeNode n1(1), n2(2), n3(2), n4(3), n5(3), n6(3), n7(3);
	n1.right = &n2;
	n2.right = &n3;
	isBalanced(&n1);
}

/*
Given a binary tree, flatten it to a linked list in-place.

For example,
Given

1
/ \
2   5
/ \   \
3   4   6
The flattened tree should look like:
1
\
2
\
3
\
4
\
5
\
6
*/			
/* recursive */ 
void flattenTree(TreeNode *root) 
{
	if (root == NULL) return;

	flattenTree(root->left);
	flattenTree(root->right);

	if (root->left == NULL) return;
	TreeNode *tmp = root->right;
	root->right = root->left;
	root->left = NULL;
	TreeNode *p = root->right;
	while (p->right != NULL)
	{
		p=p->right;
	}
	p->right = tmp;
}

/* recursive, record tail pointer */
void doFlattenTree(TreeNode *root, TreeNode *&tail) 
{
	if (root == NULL) { tail = NULL; return; }

	TreeNode* ltail = NULL, *rtail = NULL;
	doFlattenTree(root->left, ltail);
	doFlattenTree(root->right, rtail);

	if (ltail != NULL) 
	{
		ltail->right = root->right;
		root->right = root->left;
	}
	if (rtail == NULL)
	{
		if (ltail != NULL) { tail = ltail; }
		else { tail = root; }
	}
	else
	{
		tail = rtail;
	}
	root->left = NULL;
}

void flattenTree_2(TreeNode *root) 
{
	TreeNode* tail;
	doFlattenTree(root, tail);
}

/* loop */
void flattenTree_3(TreeNode *root) 
{
	if (root == NULL) return;

	stack<TreeNode*> s;
	TreeNode *p = root;
	while(true)
	{
		if (p->left == NULL && p->right == NULL)
		{
			if (s.empty()) break;
			TreeNode* top = s.top();
			s.pop();
			p->right = top;
			p = top;
		}
		else if (p->left != NULL)
		{
			if (p->right != NULL) s.push(p->right);

			TreeNode *tmp = p;
			p->right = p->left;
			p = p->left;
			tmp->left = NULL;
		}
		else
		{
			p = p->right;
		}		
	}
}

void RunFlattenTree()
{
	TreeNode n1(1), n2(2), n3(3), n4(3), n5(3), n6(3), n7(3);
	n1.left = &n2;
	n1.right = &n3;
	flattenTree_3(&n1);
}

/*
Given a binary tree

struct TreeLinkNode {
TreeLinkNode *left;
TreeLinkNode *right;
TreeLinkNode *next;
}
Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.

Note:

You may only use constant extra space.
You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent has two children).
For example,
Given the following perfect binary tree,
1
/  \
2    3
/ \  / \
4  5  6  7
After calling your function, the tree should look like:
1 -> NULL
/  \
2 -> 3 -> NULL
/ \  / \
4->5->6->7 -> NULL

II:
Follow up for problem "Populating Next Right Pointers in Each Node".

What if the given tree could be any binary tree? Would your previous solution still work?

Note:

You may only use constant extra space.
For example,
Given the following binary tree,
1
/  \
2    3
/ \    \
4   5    7
After calling your function, the tree should look like:
1 -> NULL
/  \
2 -> 3 -> NULL
/ \    \
4-> 5 -> 7 -> NULL
*/
void connect(TreeLinkNode *root) 
{
	if (root == NULL) return;
	TreeLinkNode *curParent, *cur;
	bool left;

	TreeLinkNode head(0);
	TreeLinkNode parent(0);
	parent.next = root;
	curParent = &parent;
	left = false;
	cur = &head;

	while(true)
	{
		//find next pointer
		if (left == true && curParent->right != NULL) 
		{
			cur->next = curParent->right;
			cur = curParent->right;
			left = false;
			continue;
		}
		TreeLinkNode *p = curParent->next;
		while(p != NULL)
		{
			if (p->left != NULL)
			{
				cur->next = p->left;
				left = true;
				curParent = p;
				cur = p->left;
				break;
			}
			else if (p->right != NULL)
			{
				cur->next = p->right;
				left = false;
				curParent = p;
				cur = p->right;
				break;
			}
			else
			{
				p = p->next;
			}
		}

		if (p == NULL)
		{
			if (head.next == NULL) break;

			parent.next = head.next;
			head.next = NULL;
			cur = &head;
			left = false;
			curParent = &parent;
		}
	}
}

TreeNode *buildTreeByInPostOrder(vector<int> &inorder, int instart, vector<int> &postorder, int poststart, int size)
{
	if (size == 1) {
		TreeNode *root = new TreeNode(inorder[instart]);
		return root;
	}

	int rootval = postorder[poststart + size - 1];
	TreeNode *root = new TreeNode(rootval);
	int i = instart;
	for (; i < instart + size; i++)
	{
		if (inorder[i] == rootval) break;
	}
	int lsize = i - instart;
	int rsize = size - lsize - 1;
	if (lsize > 0)
	{
		root->left = buildTreeByInPostOrder(inorder, instart, postorder, poststart, lsize);
	}
	if (rsize > 0)
	{
		root->right = buildTreeByInPostOrder(inorder, i+1, postorder, poststart + lsize, rsize);
	}
	return root;
}

TreeNode *buildTreeByInPostOrder(vector<int> &inorder, vector<int> &postorder)
{
	if (inorder.size() <= 0 || postorder.size() <= 0 || inorder.size() != postorder.size())
	{
		return NULL;
	}

	return buildTreeByInPostOrder(inorder, 0, postorder, 0, postorder.size());
}

void RunBuildTree()
{
	vector<int> in; in.push_back(1); in.push_back(2); in.push_back(3);
	vector<int> post; post.push_back(3); post.push_back(2); post.push_back(1); 
	buildTreeByInPostOrder(in, post);
}


TreeNode *buildTreeByInPreOrder(vector<int> &inorder, int instart, vector<int> &preorder, int prestart, int size)
{
	if (size == 1) {
		TreeNode *root = new TreeNode(inorder[instart]);
		return root;
	}

	int rootval = preorder[prestart];
	TreeNode *root = new TreeNode(rootval);
	int i = instart;
	for (; i < instart + size; i++)
	{
		if (inorder[i] == rootval) break;
	}
	int lsize = i - instart;
	int rsize = size - lsize - 1;
	if (lsize > 0)
	{
		root->left = buildTreeByInPreOrder(inorder, instart, preorder, prestart + 1, lsize);
	}
	if (rsize > 0)
	{
		root->right = buildTreeByInPreOrder(inorder, i+1, preorder, prestart + lsize + 1, rsize);
	}
	return root;
}

TreeNode *buildTreeByInPreOrder(vector<int> &preorder, vector<int> &inorder)
{
	if (inorder.size() <= 0 || preorder.size() <= 0 || inorder.size() != preorder.size())
	{
		return NULL;
	}

	return buildTreeByInPreOrder(inorder, 0, preorder, 0, preorder.size());
}

/*
Given n, how many structurally unique BST’s (binary search trees) that store values 1:::n?
For example, Given n = 3, there are a total of 5 unique BST’s.
1 3 3 2 1
\ / / / \ \
3 2 1 1 3 2
/ / \ \
2 1 2 3
*/
int numTrees(int n)
{
	if (n == 0) return 0;
	if (n == 1) return 1;
	vector<int> r(n+1, 0);
	r[0] = 1;
	r[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			int l = r[j-1];
			int rc = r[(i-j)];
			r[i] += (l * rc);
		}
	}
	return r[n];
}

/*
Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.
*/
bool isValidBST(TreeNode* root, int &maxNode, int &minNode)
{
	int max, min;
	maxNode = root->val;
	minNode = root->val;
	if (root->left != NULL)
	{
		if (!isValidBST(root->left, max, min)) return false;
		if (root->val <= max) return false;
		maxNode = root->val;
		minNode = min;
	}
	if (root->right != NULL)
	{
		if (!isValidBST(root->right, max, min)) return false;
		if (root->val >= min) return false;
		maxNode = max;
		if (root->val < minNode) minNode = root->val;
	}
	return true;
}

bool isValidBST_2(TreeNode* root, int lower, int upper)
{
	if (root == NULL) return true;
	return root->val > lower && root->val < upper 
		&& isValidBST_2(root->left, lower, root->val) 
		&& isValidBST_2(root->right, root->val, upper);
}

bool isValidBST(TreeNode* root)
{
	if (root == NULL) return true;
	return isValidBST_2(root, INT_MIN, INT_MAX);
}

/*
Given a binary tree, find its maximum depth.
The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.
*/
int maxDepth(TreeNode *root) 
{
	if (root == NULL) return 0;
	return max(maxDepth(root->left), maxDepth(root->right)) + 1;
}								  

/*
Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.

For example,
"A man, a plan, a canal: Panama" is a palindrome.
"race a car" is not a palindrome.

Note:
Have you consider that the string might be empty? This is a good question to ask during an interview.

For the purpose of this problem, we define empty string as valid palindrome.
*/
bool isPalindrome(string s) 
{
	if (s.length() <= 0) return true;
	for (int i = 0, j = s.length()-1; i<j;)
	{
		char l = s.at(i);
		if (!isalnum(l)) {i++; continue;}
		char r = s.at(j);
		if (!isalnum(r)) {j--; continue;}
		if (tolower(l) != tolower(r)) return false;
		i++;
		j--;
	}
	return true;
}

/*
Write a function to find the longest common prefix string amongst an array of strings.
*/
string longestCommonPrefix(vector<string> &strs) 
{
	if (strs.size() == 0) return "";
	if (strs.size() == 1) return strs[0];
	string prefix;
	bool done = false;
	for (size_t i = 0; i < strs[0].length(); i++)
	{
		char c = strs[0].at(i);
		for (size_t j = 1; j < strs.size(); j++)
		{
			if (i >= strs[j].length() || strs[j].at(i) != c)
			{
				done = true;
				break;
			}
		}
		if (done) break;
		prefix.push_back(c);
	}
	return prefix;
}

void RunLongestCommonPrefix()
{
	string s1 = "aaa";
	string s2 = "aa";
	string s3 = "aaa";
	vector<string> strs;
	strs.push_back(s1); strs.push_back(s2); strs.push_back(s3);
	longestCommonPrefix(strs);
}

/*
Given numRows, generate the first numRows of Pascal's triangle.

For example, given numRows = 5,
Return

[
[1],
[1,1],
[1,2,1],
[1,3,3,1],
[1,4,6,4,1]
]
*/
vector<vector<int> > generatePascalTriangle(int numRows) 
{
	vector<vector<int> > result;
	if (numRows == 0) return result;
	vector<int> row1; row1.push_back(1);
	result.push_back(row1);
	for (int i = 1; i < numRows; i++)
	{
		vector<int> row;
		// first
		row.push_back(1);
		// mid
		for (int j = 1; j < i ; j++)
		{
			row.push_back(result[i-1][j-1] + result[i-1][j]);
		}
		// end
		row.push_back(1);

		result.push_back(row);
	}
	return result;
}

/*
Given an index k, return the kth row of the Pascal's triangle.

For example, given k = 3,
Return [1,3,3,1].

Note:
Could you optimize your algorithm to use only O(k) extra space?
*/
vector<int> getRowOfPascalTriangle(int rowIndex) 
{
	vector<int> result;
	vector<int> last;
	//row 1
	last.push_back(1);
	if (rowIndex == 0) return last;
	//if (rowIndex == 1) return last;
	vector<int> *pCur = &result;
	vector<int> *pLast = &last;
	for (int i = 1; i <= rowIndex; i++)
	{
		pCur->clear();
		//first
		pCur->push_back(1);

		//mid
		for (int j = 1; j < i; j++)
		{
			pCur->push_back((*pLast)[j-1] + (*pLast)[j]);
		}

		//last
		pCur->push_back(1);

		vector<int> *tmp = pLast;
		pLast = pCur;
		pCur = tmp;
	}
	return *pLast;
}

/*
Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up all the values along the path equals the given sum.

For example:
Given the below binary tree and sum = 22,
5
/ \
4   8
/   / \
11  13  4
/  \      \
7    2      1
return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.
*/
bool hasPathSum(TreeNode *root, int sum) 
{
	if (root == NULL) return false;	   

	if (root->left == NULL && root->right == NULL && root->val == sum) return true;
	if (root->left != NULL && hasPathSum(root->left, sum - root->val)) return true;
	if (root->right != NULL && hasPathSum(root->right, sum - root->val)) return true;
	return false;
}

/*
Given a binary tree, find its minimum depth.
The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.
*/
int minDepth(TreeNode *root) 
{
	if (root == NULL) return 0;

	queue<TreeNode*> q;
	q.push(root);
	int h = 1;
	int visited = 0;
	int count = 1;
	int nextlevel = 0;
	while (!q.empty())
	{
		TreeNode *n = q.front();
		q.pop();
		if (n->left == NULL && n->right == NULL)
		{
			return h;
		}
		if (n->left != NULL) { q.push(n->left); nextlevel++; }
		if (n->right != NULL) { q.push(n->right); nextlevel++; }
		visited++;
		if (visited == count)
		{
			h++;
			visited = 0;
			count = nextlevel;
			nextlevel = 0;
		}
	}
	return 0;
}

/*
Given two sorted integer arrays A and B, merge B into A as one sorted array.  
Note:
You may assume that A has enough space (size that is greater or equal to m + n) to hold additional elements from B. The number of elements initialized in A and B are m and n respectively.
*/
void merge(int A[], int m, int B[], int n) 
{
	int pos = m+n-1;
	int i = m - 1;
	int j = n - 1;
	for (; i >= 0 && j >= 0; pos--)
	{
		if (A[i] >= B[j]) 
		{
			A[pos] = A[i];
			i--;
			continue;
		}
		else
		{
			A[pos] = B[j];
			j--;
			continue;
		}
	}
	if (j >= 0)
	{
		while (pos >= 0)
		{
			A[pos--] = B[j--];
		}
	}
}
																								 
/*
Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.
*/
bool isValidParentheses(string s) 
{										
	stack<char> stk;
	for (size_t i = 0; i < s.length(); i++)
	{
		char c = s.at(i);
		if (c == '(' || c == '{' || c == '[')
		{
			stk.push(c);
		}
		else
		{
			if (stk.empty()) return false;
			char t = stk.top();
			stk.pop();
			if (t == '(' && c == ')' 
				|| t == '[' && c == ']'
				|| t == '{' && c == '}')
			{
				continue;
			}
			else
			{
				return false;
			}
		}
	}
	if (stk.empty()) return true;
	return false;
}					 

/*
Given an array and a value, remove all instances of that value in place and return the new length.	   
The order of elements can be changed. It doesn't matter what you leave beyond the new length.
*/
int removeElement(int A[], int n, int elem) 
{	
	if (n == 0) return 0;
	int index = 0;
	for (int i = 0; i < n;)
	{						  
		if (A[i] == elem)
		{				  
			i++;
		}
		else
		{
			A[index++] = A[i++];
		}
	}
	return index;
}

/*
Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.
*/
ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) 
{
	if (l1 == NULL) { return l2; }
	if (l2 == NULL) { return l1; }
	ListNode *p1 = l1;
	ListNode *p2 = l2;
	ListNode head(0);
	ListNode *p = &head;
	while (p1 != NULL && p2 != NULL)
	{
		if (p1->val < p2->val)
		{
			p->next = p1;
			p = p1;
			p1 = p1->next;
		}
		else
		{
			p->next = p2;
			p = p2;
			p2 = p2->next;
		}
	}
	if (p1 == NULL) p->next = p2;
	if (p2 == NULL) p->next = p1;
	return head.next;
}

/*
Given a string s consists of upper/lower-case alphabets and empty space characters ' ', return the length of last word in the string.

If the last word does not exist, return 0.

Note: A word is defined as a character sequence consists of non-space characters only.

For example, 
Given s = "Hello World",
return 5.
*/
int lengthOfLastWord(const char *s) 
{															 
	int len = 0;
	int last = 0;
	for (const char *p = s; *p != '\0'; p++)
	{
		if (*p == ' ')
		{
			if (len > 0) { last = len; }
			len = 0;
		}
		else len++;
	}
	if (len > 0) return len;		
	else return last;
}

/*
Implement strStr().	   
Returns the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.
*/
int strStr(char *haystack, char *needle) 
{											  
	if (haystack == NULL) return -1;
	if (needle == NULL) return 0;
	int hlen = strlen(haystack);
	int nlen = strlen(needle);
	for (int i = 0; i <= hlen - nlen; i++)
	{
		bool match = true;
		for (int j = 0; j < nlen; j++)
		{
			if (haystack[i+j] != needle[j]) 
			{
				match = false;
				break;
			}
		}
		if (match) return i;
	}
	return -1;
}

/*
Validate if a given string is numeric.

Some examples:
"0" => true
" 0.1 " => true
"abc" => false
"1 a" => false
"2e10" => true
Note: It is intended for the problem statement to be ambiguous. You should gather all requirements up front before implementing one.
*/
enum Status {
	EMPTY,
	SIGN,
	NUM,
	DOT,
	NUMDOT,
	FLOAT,
	E,
	POW,
	ENDEMPTY
};	
bool isNum(char c) 
{
	return c >= '0' && c <= '9';
}
bool isNumber(const char *s) 
{
	Status status = EMPTY;
	if (s== NULL) return false;		 	
	for(const char* p = s; *p != '\0'; p++)
	{
		switch (status)
		{
		case EMPTY:
			if (*p == ' ') continue;
			else if (*p == '+' || *p == '-') { status = SIGN; continue; }
			else if (*p >= '0' && *p <= '9') { status = NUM; continue; }
			else if (*p == '.') { status = DOT; continue; }
			else return false;
			break;
		case SIGN:
			if (*p >= '0' && *p <= '9') { status = NUM; continue; }
			else if (*p == '.') { status = DOT; continue; }
			else return false;
			break;
		case NUM:
			if (*p >= '0' && *p <= '9') continue;
			else if (*p == '.') { status = NUMDOT; continue; }
			else if (*p == 'e') { status = E; continue; }
			else if (*p == ' ') { status = ENDEMPTY; continue; }
			else return false;
			break;
		case DOT:
			if (isNum(*p)) { status = FLOAT; continue; }
			else return false;
			break;
		case NUMDOT:
			if (isNum(*p)) { status = FLOAT; continue; }
			else if (*p == ' ') { status = ENDEMPTY; continue; }
			else if (*p == 'e') { status = E; continue;}
			else return false;
			break;
		case FLOAT:
			if (isNum(*p)) {continue;}			
			else if (*p == 'e') { status = E; continue;}
			else if (*p == ' ') { status = ENDEMPTY; continue; }
			else return false;
			break;
		case E:
			if (isNum(*p)) { status = POW; continue; }
			else if (*p == '+' || *p == '-') {status = SIGN; continue; }
			else return false;
			break;
		case POW:
			if (isNum(*p)) { continue; }
			else if (*p == ' ') {status = ENDEMPTY; continue; }
			else return false;
			break;
		case ENDEMPTY:
			if (*p == ' ') { continue; }
			else return false;
			break;
		default:
			return false;
			break;
		}
	}
	if (status == NUM || status == FLOAT || status == POW || status == ENDEMPTY || status == NUMDOT)
	{
		return true;
	}
	return false;
}						

/*
Given two binary strings, return their sum (also a binary string).

For example,
a = "11"
b = "1"
Return "100".
*/
string addBinary(string a, string b) 
{
	 string result;
	 int carry = 0;
	 for (int i = a.length() - 1, j = b.length() - 1; i >= 0 || j >= 0; i--, j--)
	 {
		 int r = carry;
		 if (i >= 0) { r += a.at(i) - '0'; }
		 if (j >= 0) { r += b.at(j) - '0'; }
		 if (r == 2)								  
		 {
			 r = 0;
			 carry = 1;
		 }
		 else if (r > 2)
		 {
			 r = 1;
			 carry = 1;
		 }
		 else
		 {
			 carry = 0;				  
		 }							  
		 int c = '0' + r;
		 result.push_back(c);
	 }
	 if (carry > 0) { result.push_back('1'); }
	 reverse(result.begin(), result.end());
	 return result;
}		

/*
The count-and-say sequence is the sequence of integers beginning as follows:
1, 11, 21, 1211, 111221, ...

1 is read off as "one 1" or 11.
11 is read off as "two 1s" or 21.
21 is read off as "one 2, then one 1" or 1211.
Given an integer n, generate the nth sequence.

Note: The sequence of integers will be represented as a string.
*/
string countAndSay(int n) 
{
	if (n == 1) return "1";
	string last = "1";
	for (int i = 2; i <= n; i++)
	{
		string cur;
		
		size_t start = 0;
		while (true)
		{			
			size_t end;
			char c = last[start];
			for (end = start + 1; end < last.length(); end++)
			{
				 if (last[end] != c) break;
			}
			int len = end - start;
			cur.push_back((char)(len + '0'));
			cur.push_back((char)(last[start]));

			if (end >= last.length()) break;
			start = end;
		}

		last = cur;
	}
	return last;
}

void RunCountAndSay()
{
	countAndSay(10);
}

/*
Say you have an array for which the ith element is the price of a given stock on day i.

If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the stock), design an algorithm to find the maximum profit.
*/
int maxProfit(vector<int> &prices)
{
	int profit = 0;
	for (size_t i = 0; i < prices.size(); i++)
	{
		for (size_t j = i+1; j < prices.size(); i++)
		{
			int r = prices[j] - prices[i];
			if (r > profit) { profit = r; }
		}
	}
	return profit;
}

int maxProfit2(vector<int> &prices)
{
	if (prices.size() <= 0) {return 0;}
	int profit = 0;
	int low = INT_MAX;
	int high = 0;
	for (size_t i = 0; i < prices.size() - 1; i++)
	{					 
		if (prices[i] < low) { low = prices[i]; high = prices[i+1]; }
		if (prices[i+1] > high) { high = prices[i+1]; }					  
		int p = high - low;
		if (p > profit) { profit = p; }
	}
	return profit;
}

void RunMaxProfit()
{
	vector<int> prices;
	prices.push_back(100);
	prices.push_back(200);
	prices.push_back(300);
	prices.push_back(50);
	prices.push_back(500);
	prices.push_back(400);
	int profit = maxProfit(prices);
}

/*
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times). However, you may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
*/
int maxProfitII(vector<int> &prices) 
{
	size_t i = 0;
	int profit = 0;
	while (true)
	{
		int low = prices[i];
		int high = prices[i];
		// find lowest price
		i++;
		for(; i < prices.size(); i++)
		{  
			if (prices[i] >= low) { break; }
			else { low = prices[i]; high = prices[i];}
		}

		// find highest price
		for (; i < prices.size(); i++)
		{
			if (prices[i] <= high) { break; }
			else { high = prices[i]; }
		}

		if (high > low) profit += (high - low);
		if (i >= prices.size()) break;		   
	}
	return profit;
}

/*
Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.

For example, given the following triangle
[
[2],
[3,4],
[6,5,7],
[4,1,8,3]
]
The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).

Note:
Bonus point if you are able to do this using only O(n) extra space, where n is the total number of rows in the triangle.
*/
int minimumTotalOfTriangle(vector<vector<int> > &triangle) 
{
	if (triangle.size() <= 0) { return 0; }

	vector<int> last(triangle.size(), 0);
	last[0] = triangle[0][0];	   	
	for (size_t i = 1; i < triangle.size(); i++)
	{
		vector<int> cur;
		//first
		cur.push_back(last[0] + triangle[i][0]);

		//mid
		for (size_t j = 1; j < i; j++)
		{
			int minTwo = min(last[j-1], last[j]) + triangle[i][j];
			cur.push_back(minTwo);
		}

		//last
		cur.push_back(last[i-1] + triangle[i][triangle[i].size()-1]);		 
		
		last = cur;
	}

	int minTotal = last[0];
	for (size_t i = 1; i < last.size(); i++)
	{
		if (last[i] < minTotal) minTotal = last[i];
	}
	return minTotal;
}

/* Sort a linked list using insertion sort. */
ListNode *insertionSortList(ListNode *head) 
{
	if (head == NULL) return NULL;

	ListNode dummy(INT_MIN);
	dummy.next = head;
	ListNode *cur = head->next;
	head->next = NULL;

	while (cur != NULL)
	{				  
		ListNode *next = cur->next;	
		//insert
		ListNode* p = dummy.next;
		ListNode* pre = &dummy;
		for (; p != NULL; p = p->next)
		{
			if (p->val > cur->val) break;
			pre = p;
		}
		pre->next = cur;
		cur->next = p;

		//move next
		cur = next;
	}
	return dummy.next;
}

/*
Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Note:
Elements in a triplet (a,b,c) must be in non-descending order. (ie, a ≤ b ≤ c)
The solution set must not contain duplicate triplets.
TODO?
*/
vector<vector<int> > threeSum(vector<int> &num) 
{
	if (num.size() <= 2) return vector<vector<int> >();

	vector<vector<int> > result;  
	sort(num.begin(), num.end());
	for (size_t i = 0; i < num.size() - 2; i++)
	{
		if (i > 0 && num[i] == num[i-1]) continue;

		size_t left = i + 1;
		size_t right = num.size() - 1;
		while (left < right)
		{				   
			int sum = num[i] + num[left] + num[right];
			if (sum == 0) 
			{
				vector<int> r;
				r.push_back(num[i]); r.push_back(num[left]); r.push_back(num[right]);
				result.push_back(r);
				left++;
				while(left < right && num[left] == num[left-1])
				{
					left++;
				}
				right--;
				while (right > left && num[right] == num[right+1])
				{
					right--;
				}	
			}
			else if (sum < 0) 
			{ 		
				left++; 		 								
			}
			else 
			{
				right--; 	 									
			}
		}
	}

	return result;
}

void RunThreeSum()
{
	vector<int> s;
	s.push_back(-1); s.push_back(0); s.push_back(1); s.push_back(2); s.push_back(-1); s.push_back(4);
	vector<vector<int> > result = threeSum(s);
}

/*
Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target. Return the sum of the three integers. You may assume that each input would have exactly one solution.

For example, given array S = {-1 2 1 -4}, and target = 1.

The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
*/
int threeSumClosest(vector<int> &num, int target) 
{
	if (num.size() <= 2) return 0;

	int gap = INT_MAX;
	int result = 0;
	sort(num.begin(), num.end());
	for (size_t i = 0; i < num.size() - 2; i++)
	{
		if (i > 0 && num[i] == num[i-1]) continue;

		size_t left = i + 1;
		size_t right = num.size() - 1;
		while (left < right)
		{				   
			int sum = num[i] + num[left] + num[right];
			int g = abs(target - sum);
			if (g == 0) 
			{
				return target;
			}
			else if (sum < target) { left++; }
			else { right--; 	}
			if (g < gap) { gap = g; result = sum; }
		}
	}

	return result;
}

/*
Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.

For example:
Given the below binary tree and sum = 22,
5
/ \
4   8
/   / \
11  13  4
/  \    / \
7    2  5   1
return
[
[5,4,11,2],
[5,8,4,5]
]
*/
vector<vector<int> > pathSum(TreeNode *root, int sum) 
{
	if (root == NULL) return vector<vector<int> >();
	if (root->left == NULL && root->right == NULL && root->val == sum) 
	{
		vector<int> r; r.push_back(sum);
		vector<vector<int> > result;
		result.push_back(r);
		return result;
	}

	vector<vector<int> > left = pathSum(root->left, sum - root->val);
	vector<vector<int> > right = pathSum(root->right, sum - root->val);
	for (size_t i = 0; i < left.size(); i++)
	{
		left[i].insert(left[i].begin(), root->val);
	}
	for (size_t i = 0; i < right.size(); i++)
	{
		right[i].insert(right[i].begin(), root->val);
		left.push_back(right[i]);
	}
	
	return left;
}

/*
Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.
*/
TreeNode *sortedListToBST(ListNode *head) 
{
	if (head == NULL) return NULL;
	if (head->next == NULL) { TreeNode* n = new TreeNode(head->val); return n; } 

	// cal list len
	int len = 0;
	for (ListNode* p = head; p != NULL; p = p->next)
	{
		len++;
	}

	// move to mid
	ListNode *cur = head; 
	for (int i = 1; i < len / 2; i++)
	{
		cur = cur->next;
	}

	ListNode *mid = cur->next;
	cur->next = NULL;
	TreeNode* root = new TreeNode(mid->val);
	root->left = sortedListToBST(head);
	root->right = sortedListToBST(mid->next);

	return root;
}

/*
Given an array where elements are sorted in ascending order, convert it to a height balanced BST.
*/
TreeNode *sortedArrayToBST(vector<int> &num, size_t offset, size_t size) 
{
	if (size == 0) return NULL;
	if (size == 1) { TreeNode *n = new TreeNode(num[offset]); return n; }

	size_t mid = offset + size / 2;
	TreeNode *root = new TreeNode(num[mid]);
	root->left = sortedArrayToBST(num, offset, mid - offset);
	root->right = sortedArrayToBST(num, mid + 1, size - 1 - (size / 2));

	return root;
}

TreeNode *sortedArrayToBST(vector<int> &num) 
{
	if (num.size() <= 0) return NULL;
	return sortedArrayToBST(num, 0, num.size());
}

/*
Given a linked list, return the node where the cycle begins. If there is no cycle, return null.

TODO: Follow up:
Can you solve it without using extra space?
*/
ListNode *detectCycle(ListNode *head) 
{
	if (head == NULL) return NULL;
	map<ListNode*, bool> nodeMap;
	for (ListNode *p = head; p != NULL; p = p->next)
	{
		if (nodeMap.find(p) != nodeMap.end()) return p;
		nodeMap[p] = true;
	}
	return NULL;
}

ListNode *detectCycle_2(ListNode *head) 
{
	if (head == NULL) return NULL;
	ListNode *fast = head;
	ListNode *slow = head;

	while(fast != NULL && fast->next != NULL)
	{
		fast = fast->next->next;
		slow = slow->next;
		if (fast == slow) 
		{
			break;
		}
	}
	if (fast == NULL || fast->next == NULL) return NULL;

	ListNode *p = head;
	while (p != slow)
	{
		p = p->next;
		slow = slow->next;
	}

	return p;
}

/*
Given a string s and a dictionary of words dict, determine if s can be segmented into a space-separated sequence of one or more dictionary words.

	For example, given
	s = "leetcode",
	dict = ["leet", "code"].

	Return true because "leetcode" can be segmented as "leet code".
*/
bool wordBreak(string s, unordered_set<string> &dict) 
{													
	for (unordered_set<string>::iterator it = dict.begin(); it != dict.end(); it++)
	{
		if (strncmp((*it).c_str(), s.c_str(), (*it).length()) == 0)					   
		{
			if (s.length() == (*it).length()) return true;
			bool r = wordBreak(s.substr((*it).length()), dict);
			if (r) return true;
		}
	}
	return false;
}

bool wordBreak_dp(string s, unordered_set<string> &dict) 
{
	if (dict.size() <= 0) { return false; }
	vector<vector<bool> > r(s.length());
	for (size_t i = 0; i < s.length(); i++)
	{
		r[i].resize(s.length());
	}

	for (int i = 0; i < s.length(); i++)
	{
		string si = s.substr(i, 1);
		if (dict.find(si) != dict.end())
		{
			r[i][i] = true;
		}
	}

	for (size_t i = 0; i < s.length() - 1; i++)
	{
		for (size_t j = i+1; j < s.length(); j++)
		{
			for (size_t k = i; k <= j; k++)
			{
				string sk = s.substr(k, j-k+1);
				if (dict.find(sk) != dict.end() && (k == i || r[i][k-1] == true))
				{
					r[i][j] = true;		
					break;
				}
			}
		}
	}
	return r[0][s.length()-1];						   
}

void RunWordBreak()
{
	string s = "dogs";
	unordered_set<string> dict;
	dict.insert("dog");
	dict.insert("s");
	dict.insert("gs");
	bool r = wordBreak_dp(s, dict);
}

/*
There are N gas stations along a circular route, where the amount of gas at station i is gas[i].

You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from station i to its next station (i+1). You begin the journey with an empty tank at one of the gas stations.

Return the starting gas station's index if you can travel around the circuit once, otherwise return -1.

Note:
The solution is guaranteed to be unique.
*/
int canCompleteCircuit(vector<int> &gas, vector<int> &cost) 
{
	if (gas.size() <= 0 || cost.size() <= 0) return -1;

	for (size_t i = 0; i < gas.size();)
	{
		int totalGas = gas[i];
		int totalCost = cost[i];				
		size_t j = i+1;
		if (j >= gas.size()) { j = j % gas.size(); }
		while (totalGas >= totalCost && j != i)
		{
			totalGas += gas[j];
			totalCost += cost[j];
			j++;
			if (j >= gas.size()) { j = j % gas.size(); }
		}
		if (j == i && totalGas >= totalCost) { return i; }
		else if (j == i && totalGas < totalCost) { return -1; }
		else if (j < i) { return -1; }
		else { i = j; }
	}
	return -1;        
}

void RunCanCompleteCircuit()
{
	vector<int> gas; gas.push_back(2); gas.push_back(4);
	vector<int> cost; cost.push_back(3); cost.push_back(4);
	int i = canCompleteCircuit(gas, cost);
}

/*
Sort a linked list in O(n log n) time using constant space complexity.
Solution: merge sort
*/
ListNode *sortList(ListNode *head) 
{
	if (head == NULL || head->next == NULL) return head;

	ListNode *slow = head;
	ListNode *fast = head;
	ListNode *pre = NULL;
	while(fast != NULL && fast->next != NULL)
	{
		pre = slow;
		slow = slow->next;
		fast = fast->next->next;
	}
	ListNode *head2 = pre->next;
	pre->next = NULL;

 	ListNode *hl = sortList(head);
	ListNode *hr = sortList(head2);
	return mergeTwoLists(hl, hr);	   												   
}

void RunSortList()
{
	ListNode n1(1), n2(3), n3(3), n4(3), n5(1), n6(3), n7(1), n8(3), n9(2), n10(3);
	n1.next = &n2; n2.next = &n3; n3.next = &n4; n4.next = &n5; n5.next = &n6; n6.next = &n7; n7.next = &n8; 
	n8.next = &n9; n9.next = &n10;
	sortList(&n1);
}

/*
Given a set of distinct integers, S, return all possible subsets.

Note:
Elements in a subset must be in non-descending order.
The solution set must not contain duplicate subsets.
For example,
If S = [1,2,3], a solution is:

[
[3],
[1],
[2],
[1,2,3],
[1,3],
[2,3],
[1,2],
[]
]
*/	  
vector<vector<int> > subsets(vector<int> &S, size_t n)
{
	if (n <= 0) {  vector<vector<int> > result; vector<int> r0; result.push_back(r0); return result; };

	vector<vector<int> > r1 = subsets(S, n - 1);
	vector<vector<int> > result;
	int last = S[n - 1];
	for (int j = 0; j < r1.size(); j++)
	{
		vector<int> r = r1[j];
		result.push_back(r);
		r.push_back(last);
		result.push_back(r);
	}
	return result;
}

vector<vector<int> > subsets(vector<int> &S) 
{
	sort(S.begin(), S.end());
	return subsets(S, S.size());
}

/*
Given a digit string, return all possible letter combinations that the number could represent.		  
A mapping of digit to letters (just like on the telephone buttons) is given below. 
Input:Digit string "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
Note:
Although the above answer is in lexicographical order, your answer could be in any order you want.
*/
vector<string> letterCombinations(string digits) 
{
	char *map[] = { " ", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
	if (digits.empty()) { vector<string> result; result.push_back(""); return result; }
	if (digits.length() == 1)
	{
		int index = digits[0] - '0';
		vector<string> result;
		for (char* p = map[index]; *p != '\0'; p++)
		{
			string s; 
			s.push_back(*p);
			result.push_back(s);
		}
		return result;
	}

	string s1 = digits.substr(0, digits.length() - 1);
	vector<string> r1 = letterCombinations(s1);
	int last = digits[digits.length() - 1] - '0';
	vector<string> result;
	for (int i = 0; i < r1.size(); i++)
	{
		for (char* p = map[last]; *p != '\0'; p++)
		{
			string s = r1[i];
			s.push_back(*p);
			result.push_back(s);
		}
	}
	return result;
}

/*
Suppose a sorted array is rotated at some pivot unknown to you beforehand.
(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
Find the minimum element.
You may assume no duplicate exists in the array.
*/
int findMin(vector<int> &num) 
{
	if (num.size() == 1) { return num[0]; }
	for (int i = 0; i < num.size() - 1; i++)
	{
		if (num[i] > num[i+1]) return num[i+1];
	}
	return num[0];
}

int findMin_2(vector<int> &num) 
{
	if (num.size() == 1) { return num[0]; }

	int l = 0;
	int r = num.size() - 1;
	while (l < r)
	{
		int mid = (l + r) / 2;
		if (l == mid) 
		{
			return min(num[l], num[r]);
		}
		else if (num[l] < num[mid] && num[mid] < num[r])
		{
			return min(num[l], num[mid]);
		}
		else if (num[l] > num[mid])
		{
			r = mid;
			continue;
		}
		else if (num[mid] > num[r])
		{
			l = mid;
			continue;
		}
	}
	return num[l];
}

/*
Given a string containing only digits, restore it by returning all possible valid IP address combinations.

For example:
Given "25525511135",

return ["255.255.11.135", "255.255.111.35"]. (Order does not matter)
*/
vector<string> restoreIpAddresses(string s, size_t n) 
{
	if (s.length() == 0) { return vector<string>(); }
	if (n == 1) 
	{
		if (s.at(0) == '0' && s.length() > 1) { return vector<string>(); }
		int val = atoi(s.c_str());
		if (val > 255 || val < 0) { return vector<string>(); }
		vector<string> result;
		result.push_back(s);
		return result;
	}

	vector<string> result;
	for (int i = 1; i <= min(3, (int)s.length()); i++)
	{
		string s1 = s.substr(0, i);
		string s2 = s.substr(i, s.length() - i);
		int val = atoi(s1.c_str());
		if (val >= 0 && val <= 255)
		{
			vector<string> r1 = restoreIpAddresses(s2, n - 1);
			for (int j = 0; j < r1.size(); j++)
			{
				string ip = s1;
				ip.append(".").append(r1[j]);
				result.push_back(ip);
			}
		}
	}
	return result;
}	
	  
vector<string> restoreIpAddresses(string s) 
{
	return restoreIpAddresses(s, 4);
}

void RunRestoreIpAddresses()
{
	string s = "0000";
	restoreIpAddresses(s);
}

vector<vector<int> > subsetsWithDup(vector<int> &S, size_t n) 
{
	if (n <= 0) {  vector<vector<int> > result; vector<int> r0; result.push_back(r0); return result; };

	vector<vector<int> > r1 = subsetsWithDup(S, n - 1);
	vector<vector<int> > result; 	
	for (int j = 0; j < r1.size(); j++)
	{
		vector<int> r = r1[j];
		result.push_back(r);	 
		if (n == 1 || S[n-1] != S[n-2])
		{
			r.push_back(S[n-1]);
			result.push_back(r);
		}
	}															 
	if (n > 1 && S[n-1] == S[n-2])
	{
		vector<int> last(S.begin(), S.begin()+n);
		result.push_back(last);
	}

	return result;
}

vector<vector<int> > subsetsWithDup(vector<int> &S) 
{
	sort(S.begin(), S.end());
	return subsetsWithDup(S, S.size());
}																		

void RunSubsetsWithDup()
{
	vector<int> s; s.push_back(1); s.push_back(1);
	subsetsWithDup(s);
}												

/*
A message containing letters from A-Z is being encoded to numbers using the following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26
Given an encoded message containing digits, determine the total number of ways to decode it.

For example,
Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).

The number of ways decoding "12" is 2.
*/
int numDecodings(string s) 
{
	if (s.length() == 0) { return 0; }
	if (s.length() == 1) { return 1; }

	int result = numDecodings(s.substr(0, s.length() - 1));
	string s2 = s.substr(0, 2);
	int i2 = atoi(s2.c_str());
	if (i2 > 0 && i2 <= 26) 
	{
		if (s.length() > 2)
		{
			string rest = s.substr(0, s.length() - 2);
			result += numDecodings(rest);
		}
		else
		{
			result++;
		}
	}
	return result;
}

int numDecodings_dp(string s) 
{
	if (s.length() == 0) { return 0; }

	vector<vector<int> > result(s.length());
	for (size_t i = 0; i < s.length(); i++)
	{
		result[i].resize(s.length(), 0);
		if (s.at(i) > '0' && s.at(i) <= '9')
		{
			result[i][i] = 1;
		}
	}	

	for (size_t i = 0; i < s.length(); i++)
	{
		for (size_t j = i+2; j < s.length(); j++)
		{
			int num = 0;
			if (s.at(j) > '0' && s.at(j) <= '9') num += result[i][j-1];
			int val = (s.at(j-1) - '0') * 10 + (s.at(j) - '0');
			if (val >= 10 && val <= 26) 
			{
				if (j == i+1) num++;
				else num += result[i][j-2];
			}

			result[i][j] = num;
		}
	}
	
	return result[0][s.length() - 1];
}

void RunNumDecodings()
{
	string s= "101010101010101010101010101010101010101010101";
	int num = numDecodings_dp(s);																														
}

/*
Given n, generate all structurally unique BST's (binary search trees) that store values 1...n.

For example,
Given n = 3, your program should return all 5 unique BST's shown below.

1         3     3      2      1
\       /     /      / \      \
3     2     1      1   3      2
/     /       \                 \
2     1         2                 3
*/
vector<TreeNode*> generateBSTrees(int start, int end)
{
	vector<TreeNode *> result;
	if (start > end) { result.push_back(NULL); return result; }
	if (start == end) { TreeNode* root = new TreeNode(start); result.push_back(root); return result; }

	for (int i = start; i <= end; i++)
	{			   		
		vector<TreeNode*> leftTrees = generateBSTrees(start, i-1);
		vector<TreeNode*> rightTrees = generateBSTrees(i+1, end);
		for (int j = 0; j < leftTrees.size(); j++)
		{
			for (int k = 0; k < rightTrees.size(); k++)
			{
				TreeNode* root = new TreeNode(i);
				root->left = leftTrees[j];
				root->right = rightTrees[k];
				result.push_back(root);
			}
		}  		
	}
	return result;
}

vector<TreeNode *> generateTrees(int n) 
{
	return generateBSTrees(1, n);
}

/*
Given an array of integers, every element appears twice except for one. Find that single one.

Note:
Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?
*/
int singleNumber(int A[], int n) 
{
	int num = 0;
	for (int i = 0; i < n; i++)
	{
		num = num ^ A[i];
	}
	return num;
}

/*
Given an array of integers, every element appears three times except for one. Find that single one.

Note:
Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?
*/
int singleNumberII(int A[], int n) 									
{
	int x[] = { 0x1,		0x2,		0x4,		0x8,		
				0x10,		0x20,		0x40,		0x80, 
				0x100,		0x200,		0x400,		0x800,
				0x1000,		0x2000,		0x4000,		0x8000,		
				0x10000,	0x20000,	0x40000,	0x80000, 
				0x100000,	0x200000,	0x400000,	0x800000,
				0x1000000,	0x2000000,	0x4000000,	0x8000000, 
				0x10000000, 0x20000000, 0x40000000, 0x80000000};
	vector<int> sum(32, 0);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			if ((A[i] & x[j]) != 0) 
			{
				sum[j]++; 
			}
		}
	}
	int num = 0;
	for (int i = 0; i < 32; i++)
	{
		if (sum[i]%3 != 0)
		{
			num += x[i];
		}
	}
	return num;
}

void RunSingleNumberII()
{
	int A[] = {1};
	int num = singleNumberII(A, 1);
}

/*
Given a 2D board and a word, find if the word exists in the grid.	
The word can be constructed from letters of sequentially adjacent cell, 
where "adjacent" cells are those horizontally or vertically neighboring. 
The same letter cell may not be used more than once.

For example,
Given board =			   
[
["ABCE"],
["SFCS"],
["ADEE"]
]
word = "ABCCED", -> returns true,
word = "SEE", -> returns true,
word = "ABCB", -> returns false.
*/
bool dfs(vector<vector<char> > &board, vector<vector<bool> > &visit, string word, int wordIndex, int i, int j)
{
	if (i >= board.size()) return false;

	if (board[i][j] == word.at(wordIndex))
	{
		visit[i][j] = true;
		if (wordIndex == word.length() - 1) return true;

		bool dir1 = false, dir2 = false, dir3 = false, dir4 = false;
		if (i > 0 && visit[i-1][j] != true)	
		{ 
			dir1 = dfs(board, visit, word, wordIndex+1, i-1, j);
			if(dir1 == true) return true;
		}
		if (j < board[0].size() - 1 && visit[i][j+1] != true)
		{
			dir2 = dfs(board, visit, word, wordIndex+1, i, j+1);
			if (dir2 == true) return true;
		}
		if (j > 0 && visit[i][j-1] != true)
		{
			dir3 = dfs(board, visit, word, wordIndex+1, i, j-1);
			if (dir3 == true) return true;
		}
		if (i < board.size() - 1 && visit[i+1][j] != true)
		{
			dir4 = dfs(board, visit, word, wordIndex+1, i+1, j);
			if (dir4 == true) return true;
		}		
		visit[i][j] = false;
	}
	return false;
}

bool exist(vector<vector<char> > &board, string word) 
{
	if (word.length() <= 0) { return false; }
	if (board.size() <= 0) { return false; }
	if (board[0].size() <= 0) { return false; }

	vector<vector<bool> > visit(board.size());					
	for (size_t i = 0; i < board.size(); i++)
	{
		visit[i].resize(board[0].size(), false);
	}

	for (int i = 0; i < board.size(); i++)
	{
		for (int j = 0; j < board[0].size(); j++)
		{
			if (dfs(board, visit, word, 0, i, j))
			{
				return true;
			}
		}
	}
	return false;
}

void RunWordSearchIn2DBoard()
{
	vector<vector<char> > board;
	vector<char> b1; b1.push_back('C'); b1.push_back('A'); b1.push_back('A');
	vector<char> b2; b2.push_back('A'); b2.push_back('A'); b2.push_back('A');
	vector<char> b3; b3.push_back('B'); b3.push_back('C'); b3.push_back('D');
	board.push_back(b1); board.push_back(b2); board.push_back(b3);

	string word = "AAB";

	bool found = exist(board, word);
}

ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) 
{
	if (headA == NULL || headB == NULL) { return NULL; }

	ListNode *tailA = headA;
	//find A's tail
	while(tailA->next != NULL)
	{
		tailA = tailA->next;
	}
	// link A'tail to A's head
	tailA->next = headA;

	ListNode *p = detectCycle_2(headB);
	tailA->next = NULL;
	return p;
}

/*
The gray code is a binary numeral system where two successive values differ in only one bit.   
Given a non-negative integer n representing the total number of bits in the code, print the sequence of gray code. A gray code sequence must begin with 0.
For example, given n = 2, return [0,1,3,2]. Its gray code sequence is:	 
00 - 0
01 - 1
11 - 3
10 - 2
Note:
For a given n, a gray code sequence is not uniquely defined.		
For example, [0,2,3,1] is also a valid gray code sequence according to the above definition. 
For now, the judge is able to judge based on one instance of gray code sequence. Sorry about that.
举个例子：																					   
00 --> 01 --> 11 --> 10														 
000 --> 001 --> 011 --> 010 --> 110 --> 111 --> 101 --> 100				   
不知道众位看官发现规律了没，看n=2的例子，前两个首位不变，变后面那一位，后两个不看首位的1，后面的那位与前两个是对称的。 
看n=3的例子的前4个，是n=2的例子在前面加个0而已，后四个与前四个对称，把前面的0换成1。						 
知道对称有什么用呢？	  
有大用！	   
例如n=3的情形，你可以由前两个推后两个，这就有4个了，哈哈哈，由这四个推后四个，搞定！看代码~
*/
vector<int> grayCode(int n)
{
	vector<int> result;
	result.push_back(0);
	if (n <= 0) return result;

	for (int i = 0; i < n; i++)
	{
		int highbit = 1 << i;
		for (int j = result.size()-1; j >= 0; j--)
		{
			int tmp = result.at(j);
			int next = tmp + highbit;
			result.push_back(next);
		}
	}
	return result;
}

/*
Given two words (start and end), and a dictionary, find the length of shortest transformation sequence from start to end, such that:

Only one letter can be changed at a time
Each intermediate word must exist in the dictionary
For example,

Given:
start = "hit"
end = "cog"
dict = ["hot","dot","dog","lot","log"]
As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
return its length 5.

Note:
Return 0 if there is no such transformation sequence.
All words have the same length.
All words contain only lowercase alphabetic characters.

solution: 利用图进行BFS遍历，直到遇到end节点或者返回0。
*/
int ladderLength(string start, string end, unordered_set<string> &dict) 
{
	map<string, int> distence;
	distence[start] = 1;
	queue<string> q;
	q.push(start);
	while(!q.empty())
	{
		string str = q.front();
		q.pop();

		int curDist = distence[str];
		for (int i = 0; i < str.length(); i++)
		{
			for (int j = 'a'; j <= 'z'; j++)
			{
				if (str.at(i) == j) continue;
				string tmp = str; 
				tmp.at(i) = j;
				if (dict.find(tmp) == dict.end()) continue;
				if (tmp == end) return curDist+1;
				if (distence.find(tmp) == distence.end())
				{
					distence[tmp] = curDist+1;
					q.push(tmp);
				}								
			}
		}
	}
	return 0;
}

void RunLadderLength()
{
	string start = "hot";
	string end = "dog";
	unordered_set<string> dict;
	dict.insert("hot"); dict.insert("dog"); dict.insert("dot");
	int step = ladderLength(start, end, dict);
}															

/*
Given an array S of n integers, are there elements a, b, c, and d in S such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.

Note:
Elements in a quadruplet (a,b,c,d) must be in non-descending order. (ie, a ≤ b ≤ c ≤ d)
The solution set must not contain duplicate quadruplets.
For example, given array S = {1 0 -1 0 -2 2}, and target = 0.

A solution set is:
(-1,  0, 0, 1)
(-2, -1, 1, 2)
(-2,  0, 0, 2)
*/
vector<vector<int> > fourSum(vector<int> &num, int target) 
{
	if (num.size() < 4) return vector<vector<int> >();

	vector<vector<int> > result;					
	map<vector<int>, bool> rmap;
	sort(num.begin(), num.end());
	for (int i = 0; i < num.size() - 3; i++)
	{
		if (i > 0 && num[i] == num[i-1]) continue;

		for (int j = i+1; j < num.size() - 2; j++)
		{											 
			if (j > i+1 && num[j] == num[j-1]) continue;

			int left = j+1;
			int right = num.size() - 1;
			while(left < right)
			{
				int sum = num[i] + num[j] + num[left] + num[right] - target;
				if (sum == 0)
				{
					vector<int> r;
					r.push_back(num[i]); r.push_back(num[j]); r.push_back(num[left]); r.push_back(num[right]);
					if (rmap.find(r) == rmap.end())
					{
						rmap[r] = true;
						result.push_back(r);
					}
					left++;
					while (left < right && num[left] == num[left-1])
					{
						left++;
					}
					right--;
					while(left < right && num[right] == num[right+1])
					{
						right--;
					}
				}
				else if (sum > 0)
				{
					right--;
				}
				else
				{
					left++;
				}
			}
		}
	}
	sort(result.begin(), result.end());  
	result.resize(unique(result.begin(), result.end()) - result.begin());
	  
	return result;
}

/* binary search for the inner loop */
vector<vector<int> > fourSum_2(vector<int> &num, int target) 
{
	if (num.size() < 4) return vector<vector<int> >();

	vector<vector<int> > result;					
	sort(num.begin(), num.end());
	for (int i = 0; i < num.size() - 3; i++)
	{
		if (i > 0 && num[i] == num[i-1]) continue;

		for (int j = i+1; j < num.size() - 2; j++)
		{											 
			if (j > i+1 && num[j] == num[j-1]) continue;			 

			for (int k = j+1; k< num.size() - 1; k++)
			{
				if (k > j+1 && num[k] == num[k-1]) continue;

				int val = target - (num[i] + num[j] + num[k]);
				int left = k+1;
				int right = num.size() - 1;
				if (val < num[left] || val > num[right]) continue;;

				while(left <= right)
				{
					int mid = (left + right) / 2;
					if (num[mid] == val) 
					{
						vector<int> r;
						r.push_back(num[i]); r.push_back(num[j]); r.push_back(num[k]); r.push_back(num[mid]);
						result.push_back(r);
						break;
					}
					else if (val < num[mid])
					{
						right = mid - 1;
					}
					else
					{
						left = mid + 1;
					}
				}
			}
		}
	}

	return result;
}	  

void RunFourSum()
{
	vector<int> num(4, 0);
	fourSum_2(num, 0);
	vector<int> num2;
	num2.push_back(1); num2.push_back(0); num2.push_back(-1);
	num2.push_back(2); num2.push_back(-2); num2.push_back(2);
	fourSum_2(num2, 0);
}

/*
A peak element is an element that is greater than its neighbors.	   
Given an input array where num[i] ≠ num[i+1], find a peak element and return its index.
The array may contain multiple peaks, in that case return the index to any one of the peaks is fine.	  
You may imagine that num[-1] = num[n] = -∞.							
For example, in array [1, 2, 3, 1], 3 is a peak element and your function should return the index number 2.
*/
int findPeakElement(const vector<int> &num, int start, int end)
{
	if (start == end) return start;

	int mid = (start + end) / 2;
	int leftPeak = findPeakElement(num, start, mid);
	if (leftPeak < mid) return leftPeak;
	int rightPeak = findPeakElement(num, mid+1, end);
	if (rightPeak > mid+1) return rightPeak;
	if (num[leftPeak] > num[rightPeak]) return leftPeak;
	else return rightPeak;
}
int findPeakElement(const vector<int> &num) 
{
	return findPeakElement(num, 0, num.size() - 1);
}

/*
Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

For example,
If n = 4 and k = 2, a solution is:

[
[2,4],
[3,4],
[2,3],
[1,2],
[1,3],
[1,4],
]
*/
void combinations(int n, int k, int index, vector<vector<int> > &result, vector<int> comb)
{
	if (comb.size() == k) 	
	{
		result.push_back(comb);
		return;
	}

	for (int i = index; i <= n; i++)
	{
		comb.push_back(i);
		combinations(n, k, i+1, result, comb);
		comb.pop_back();
	}
}

vector<vector<int> > combinations(int n, int k) 
{
	if (n <= 0 || k <= 0 || n < k) return vector<vector<int> >();
	vector<int> comb;
	vector<vector<int> > result;

	combinations(n, k, 1, result, comb);
	return result;
}	

/*
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.		
For example, given n = 3, a solution set is:	  
"((()))", "(()())", "(())()", "()(())", "()()()"

生成合法的括号对。该问题解的个数就是卡特兰数
这里只需要搞清楚“合法(well-formed)”的概念就行了，那就是
1.左右括号数相等
2.任一位置之前的右括号数不大于左括号数

按照这个规则去打印括号：假设在位置k我们还剩余left个左括号和right个右括号，如果left>0，则我们可以直接打印左括号，而不违背规则。
能否打印右括号，我们还必须验证left和right的值是否满足规则，如果left>=right，则我们不能打印右括号，因为打印会违背合法排列的规
则，否则可以打印右括号。如果left和right均为零，则说明我们已经完成一个合法排列，可以将其打印出来。
*/
void generateParenthesis(int left, int right, vector<string>& result, string str)
{
	if (left == 0 && right == 0) 
	{
		result.push_back(str);
		return;								   
	}

	if (left > 0)
	{
		generateParenthesis(left-1, right, result, str + "(");
	}
	if (left < right)
	{
		generateParenthesis(left, right-1, result, str + ")");
	}
}

vector<string> generateParenthesis(int n) 
{
	if (n <= 0) return vector<string>();

	int left = n;
	int right = n;
	string str = "";
	vector<string> result;
	generateParenthesis(left, right, result, str);
	return result;
}

/*
Given an array with n objects colored red, white or blue, sort them so that objects of the same color are adjacent, 
with the colors in the order red, white and blue.
Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.

Note:
You are not suppose to use the library's sort function for this problem.

Follow up:
A rather straight forward solution is a two-pass algorithm using counting sort.
First, iterate the array counting number of 0's, 1's, and 2's, then overwrite array with total number of 0's, then 1's and followed by 2's.

Could you come up with an one-pass algorithm using only constant space?
*/
void sortColors(int A[], int n) 
{
	if (n <= 0) return;
	int red = 0;
	int blue = n-1;
	for (int i = 0; i <= blue;)
	{
		if (A[i] == 0)
		{
			A[red++] = A[i++]; 
			continue;
		}
		if (A[i] == 2)
		{
			swap(A[i], A[blue--]);
			continue;
		}
		if (A[i] == 1)
		{
			i++;
			continue;
		}
	}    
	for (int i = red; i <= blue; i++)
	{
		A[i] = 1;
	}
}

void RunSortColors()
{
	int A[] = {2,0};
	sortColors(A, sizeof(A)/sizeof(A[0]));	
}

/*
Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

Integers in each row are sorted from left to right.
The first integer of each row is greater than the last integer of the previous row.
For example,

Consider the following matrix:

[
[1,   3,  5,  7],
[10, 11, 16, 20],
[23, 30, 34, 50]
]
Given target = 3, return true.
*/
bool searchMatrix(vector<vector<int> > &matrix, int target) 
{
	if (matrix.size() <= 0) return false;
	if (matrix[0].size() <= 0) return false;

	int col = matrix[0].size();
	int row = -1;
	int l = 0; 
	int r = matrix.size() - 1;
	while(l <= r)
	{
		int mid = (l + r) / 2;
		if (matrix[mid][0] <= target && matrix[mid][col-1] >= target) {	row = mid; break; }
		if (target < matrix[mid][0]) { r = mid - 1; 	continue; }
		if (target > matrix[mid][col-1]) { l = mid + 1;	continue; }
	}						  
	if (row == -1) return false;
	l = 0; 
	r = col - 1;
	while (l <= r)
	{
		int mid = (l + r) / 2;
		if (matrix[row][mid] == target) return true;
		if (matrix[row][mid] < target) { l = mid + 1; continue; }
		if (matrix[row][mid] > target) { r = mid - 1; continue; }
	}
	return false;
}

/*
Given an absolute path for a file (Unix-style), simplify it.

For example,
path = "/home/", => "/home"
path = "/a/./b/../../c/", => "/c"
click to show corner cases.

Corner Cases:
Did you consider the case where path = "/../"?
In this case, you should return "/".
Another corner case is the path might contain multiple slashes '/' together, such as "/home//foo/".
In this case, you should ignore redundant slashes and return "/home/foo".
*/
string simplifyPath(string path) 
{
	if (path.length() <= 0) return path;
	bool abslutedPath = (path.at(0) == '/');
	int pos = 0;
	if (abslutedPath) pos = 1;
	stack<string> s;
	while(pos < path.length())
	{
		int nextSlash = path.find('/', pos);
		if (nextSlash == pos) { pos++; continue; }
		if (nextSlash < 0) {nextSlash = path.length();}
		string segment = path.substr(pos, nextSlash - pos);
		if (segment == ".")	{ pos = nextSlash+1; continue; }
		if (segment == "..") 
		{ 
			if (!s.empty()) s.pop(); 
			pos = nextSlash + 1; 
			continue; 
		}
		s.push(segment);
		pos = nextSlash + 1;
	}
	string result;
	while(!s.empty())
	{
		string t = s.top();
		s.pop();
		if (result.empty())	result = t;
		else result = t + "/" + result;
	}
	if (abslutedPath) result = "/" + result;

	return result;
}

/*
Given n non-negative integers a1, a2, ..., an, where each represents a point at coordinate (i, ai). 
n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). 
Find two lines, which together with x-axis forms a container, such that the container contains the most water.

Note: You may not slant the container.
*/
// O(n2)
int maxArea(vector<int> &height) 
{
	if (height.size() <= 0) return 0;
	int maxArea = -1;							
	int maxLeft = -1;
	for (int i = 0; i < height.size(); i++)
	{
		if (height[i] <= maxLeft) continue;
		else maxLeft = height[i];
		for (int j = i+1; j < height.size(); j++)
		{
			int area = (j - i) * min(height[i], height[j]);
			if (maxArea < area) maxArea = area;
		}
	}										   
	return maxArea;
}

// O(n)
int maxArea_2(vector<int> &height) 
{
	if (height.size() <= 0) return 0;							
	int i = 0, j = height.size() - 1;
	int maxarea = (j - i) * min(height[i], height[j]);
	while(i < j)
	{
		if (height[i] < height[j])
		{
			i++;
		}
		else
		{
			j--;
		}
		int area = (j - i) * min(height[i], height[j]);
		if (area > maxarea) maxarea = area;
	}
	return maxarea;
}

/*
Implement int sqrt(int x).

Compute and return the square root of x.
*/
int sqrt(int x) 
{
	if (x < 0) { return -1;}
	if (x == 0) return 0;
	if (x == 1) { return 1; }
	long long l = 1;
	long long r = x;
	while(r - l > 1)
	{
		long long mid = (l+r)/2;
		long long v = mid * mid;
		if (v == x)return mid;
		if (v < x) { l = mid; continue; }
		else { r = mid; continue; }
	}
	return l;
}

void RunSqrt()
{
	sqrt(2147483647);
}

/*
Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.

If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).

The replacement must be in-place, do not allocate extra memory.

Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.
1,2,3 → 1,3,2
3,2,1 → 1,2,3
1,1,5 → 1,5,1

---NOT UNDERSTOOD
*/
void nextPermutation(vector<int> &num) 
{
	if (num.size()<=0) return;																   
	int first = -1;
	for (int i = num.size() - 2; i >= 0; i--)
	{								 
		if (num[i] < num[i+1]) { first = i; break; }
	}
	if (first == -1) 
	{
		reverse(num.begin(), num.end());
		return;
	}		   
	for (int i = num.size()-1; i > 0; i--)
	{
		if (num[i] > num[first]) 
		{
			swap(num[first], num[i]);
			reverse(num.begin()+first+1, num.end());
			return;
		}
	}
}

void RunNextPermutation()
{
	vector<int> num;
	num.push_back(1); num.push_back(2);
	nextPermutation(num);
}

// TODO:WRONG
int divide(int dividend, int divisor) 
{
	if (divisor == 0) return INT_MAX;
	//if (dividend == divisor) return 1;
	int neg = 1;
	if (dividend < 0 && divisor > 0 || divisor < 0 && dividend > 0) neg = -1;
	dividend = abs(dividend);
	divisor = abs(divisor);
	if (dividend < divisor) return 0;
	int added = 0;
	if (dividend == INT_MIN)
	{			
		if (divisor == -1) return INT_MAX;
		dividend += abs(divisor);
		added++;
	}
	if (divisor == INT_MIN) return added;
	long long result = 1;
	long long d = divisor;
	while(true)		  
	{
		d = d << 1;
		if (d > dividend) { d = d >> 1; break; }
		result = result << 1;
	}																   
	long long tempr = result;
	long long tempd = d;
	while(tempd > 0)
	{
		tempr = tempr >> 1;
		tempd = tempd >> 1;
		if (tempd + d > dividend) { continue; }
		else { d += tempd; result += tempr; }
	}
	return (result + added) * neg;
}

void RunDivide()
{
	int r1 = divide(10, 3);															
	int r = divide((int)-1010369383, INT_MIN);
}

string fractionToDecimal(int numerator, int denominator) 
{
	if (denominator == 0) return "";
	int sign = 1;
	if ((numerator > 0 && denominator < 0) || (numerator < 0 && denominator > 0)) sign = -1;
	
	long long num = abs((long long)numerator);
	long long denom = abs((long long)denominator);

	long long intpart = num / denom;
	long long remainder = num % denom;

	vector<int> decimal;	
	map<long long, int> remainderPosMap;
	int pos = 0;
	remainderPosMap[remainder] = pos;
	int repeatStart = -1;
	while (remainder != 0)
	{
		remainder *= 10; 
		if (remainder < denom) 
		{ 
			decimal.push_back(0);
			pos++;
			continue; 			  
		}							   
		int n1 = remainder / denom;
		remainder = remainder % denom;
		decimal.push_back(n1);
		pos++;

		// check if repeat 
		if (remainderPosMap.find(remainder) != remainderPosMap.end())
		{
			repeatStart = remainderPosMap[remainder];
			//repeatEnd = pos;
			break;
		}

		remainderPosMap[remainder] = pos;
	}

	string result; 									
	if (sign < 0) result = "-";
	char buf[50];
	sprintf_s(buf, 49, "%lld", intpart);
	//_itoa_s(intpart, buf, 10);
	result.append(buf);
	if (decimal.size() > 0) result.append(".");
	for (int i = 0; i < decimal.size(); i++)
	{
		char tmp[2];
		tmp[0] = decimal.at(i) + '0';
		tmp[1] = 0;
		if (i == repeatStart)
		{
			result.append("(");	 			 
			result.append(tmp);
		}
		else
		{
			result.append(tmp);
		}
	}
	if(repeatStart >= 0) { result.append(")"); }
	return result;
}

void RunFractionToDecimal()
{
	string result = fractionToDecimal(1, 2);
	result = fractionToDecimal(1, 3);
	result = fractionToDecimal(1000, 999);
	result = fractionToDecimal(2000, 77);
}

vector<int> searchRange(int A[], int n, int target) 
{
	if (n <= 0) return vector<int>();	
	int mid = -1;
	int l = 0; int r = n - 1;
	while(l <= r)
	{
		int m = (l + r) / 2;
		if (A[m] == target) { mid = m; break; }
		if (A[m] > target) { r = m - 1; continue; }
		if (A[m] < target) { l = m + 1; continue; }
	}								 
	if (mid == -1) { vector<int> r(2, -1); return r; }
	int low = -1;			
	int high = -1;
	l = 0; r = mid;
	if (mid == 0)
	{
		low = 0;
	}
	else
	{
		while(l < r - 1)
		{
			int m = (l + r) / 2;
			if (A[m] == A[mid]) { r = m; continue; }
			else { l = m; continue; }
		}
		if (A[l]==A[mid]) { low = l; } else { low = r; }
	}
	l = mid;
	r = n - 1;
	if (mid == n - 1)
	{
		high = n - 1;
	}
	else
	{
		while(l < r - 1)
		{
			int m = (l + r) / 2;
			if (A[m] == A[mid]) { l = m; continue; }
			else { r = m; continue; }
		}
		if (A[r]==A[mid]) { high = r; } else { high = l; }
	}
	vector<int> result;
	result.push_back(low);
	result.push_back(high);
	return result;
}

void RunSearchRange()
{
	int num[] = {1, 4};
	searchRange(num, sizeof(num)/sizeof(num[0]), 4);
}

/*
Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right 
which minimizes the sum of all numbers along its path.
Note: You can only move either down or right at any point in time.
*/
int minPathSum(vector<vector<int> > &grid) 
{																   
	if (grid.size() <= 0) return 0;
	if (grid[0].size() <= 0) return 0;

	int row = grid.size();
	vector<vector<int> > result(row);
	int col = grid[0].size();
	for (size_t i = 0; i < result.size(); i++)
	{
		result[i].resize(col, 0);
	}

	result[row-1][col-1] = grid[row-1][col-1];
	for (int i = col-2; i >= 0; i--)
	{
		result[row-1][i] = result[row-1][i+1] + grid[row-1][i];
	}
	for (int i = row-2; i >= 0; i--)
	{
		result[i][col-1] = result[i+1][col-1] + grid[i][col-1];
	}

	for (int i = row - 2; i >= 0; i--)
	{
		for (int j = col - 2; j >= 0; j--)
		{
			result[i][j] = grid[i][j] + min(result[i+1][j], result[i][j+1]);
		}
	}

	return result[0][0];
}

void RunMinPathSum()
{
	vector<vector<int> > grid;
	vector<int> row;
	row.push_back(0);
	grid.push_back(row);

	int sum = minPathSum(grid);
}

/*
Given an array of size n, find the majority element. 
The majority element is the element that appears more than ( n/2 ) times.
You may assume that the array is non-empty and the majority element always exist in the array.
*/
int majorityElement(vector<int> &num)
{
	if (num.size() < 0) return 0;

	map<int, int> count;
	int maxcount = 0;
	int maxvalue = 0;
	for (int i = 0; i < num.size(); i++)
	{
		if (count.find(num[i]) != count.end())
		{
			int c = count[num[i]];
			c++;
			count[num[i]] = c;
			if (c > maxcount) { maxcount = c; maxvalue = num[i]; }
		}
		else
		{
			count[num[i]] = 1;
			if (1 > maxcount) { maxcount = 1; maxvalue = num[i]; }
		}
	}
	return maxvalue;
}

/*
Compare two version numbers version1 and version1.
If version1 > version2 return 1, if version1 < version2 return -1, otherwise return 0.

You may assume that the version strings are non-empty and contain only digits and the . character.
The . character does not represent a decimal point and is used to separate number sequences.
For instance, 2.5 is not "two and a half" or "half way to version three", it is the fifth second-level revision of the second first-level revision.

Here is an example of version numbers ordering:

0.1 < 1.1 < 1.2 < 13.37
*/
vector<int> parseVersion(string version)
{
	int ver = 0;
	vector<int> r;
	for (int i = 0; i < version.length(); i++)
	{
		char c = version.at(i);
		if (c == '.') { r.push_back(ver); ver = 0; continue; }
		ver = ver * 10 + c - '0';			
	}
	if (version.at(version.length()-1) != '.') r.push_back(ver);
	return r;
}

int compareVersion(string version1, string version2) 
{
	vector<int> ver1 = parseVersion(version1);
	vector<int> ver2 = parseVersion(version2);  
	
	for (size_t i = 0; i < min(ver1.size(), ver2.size()); i++)
	{
		if (ver1[i] > ver2[i]) return 1;
		if (ver1[i] < ver2[i]) return -1;
	}
	if (ver1.size() > ver2.size()) 
	{
		for (int i = ver2.size(); i< ver1.size(); i++)
		{
			if (ver1.at(i) > 0) { return 1; }
		}
		return 0; 
	}
	if (ver1.size() < ver2.size()) 
	{
		for (int i = ver1.size(); i< ver2.size(); i++)
		{
			if (ver2.at(i) > 0) { return -1; }
		}
		return 0;
	}
	return 0;
}

void RunCompareVersion()
{
	compareVersion("1", "1.1");
}

/*
Given a positive integer, return its corresponding column title as appear in an Excel sheet.

For example:

1 -> A
2 -> B
3 -> C
...
26 -> Z
27 -> AA
28 -> AB 
*/
string convertToTitle(int n) 
{
	if (n == 0) return "";

	string s;
	while(n > 0)
	{
		int t = n % 26;
		if (t == 0) t = 26;
		char c = 'A' + t - 1;
		s.push_back(c);
		n = (n-1) / 26;
	}
	reverse(s.begin(), s.end());
	return s;
}

/*
Given a column title as appear in an Excel sheet, return its corresponding column number.

For example:

A -> 1
B -> 2
C -> 3
...
Z -> 26
AA -> 27
AB -> 28 
*/
int titleToNumber(string s) 
{
	int r = 0;
	for (int i = 0; i < s.length(); i++)
	{
		char c = s.at(i);
		r = r * 26 + c - 'A' + 1;
	}
	return r;
}

/*
Given an integer n, return the number of trailing zeroes in n!.
Note: Your solution should be in logarithmic time complexity.
*/
int trailingZeroes(int n) 
{
	long long five = 5;
	int zeros = 0;
	while(five <= n)
	{
		int zero = n / five;
		zeros += zero;
		five = five * 5;
	}

	return zeros;    
}

void RunTrailingZeroes()
{
	trailingZeroes(1808548329);
}

class MyStack
{
private:
	char* _buffer;
	int _top;
	int _size;
public:
	MyStack(int size)											 
	{
		this->_size = size;
		this->_buffer = new char[size];
		this->_top = -1;
	}
	MyStack(MyStack& s)
	{
		this->_size = s._size;
		this->_buffer = new char[s._size]; 
		this->_top = -1;
	}
	~MyStack()
	{
		delete[] this->_buffer;
	}
	void push(char c)
	{
		if (this->_top == this->_size)
		{
			this->_size = this->_size * 2;
			char *tmp = new char[this->_size];
			memcpy(tmp, this->_buffer, this->_top);
			delete[] this->_buffer;
			this->_buffer = tmp;
		}
		this->_buffer[this->_top++] = c;
	}
	bool empty()
	{
		return (this->_top < 0);
	}
	char top()
	{
		if (this->_top < 0) throw exception("empty stack");
		return this->_buffer[this->_top];
	}
	void pop()
	{
		if (this->_top < 0) throw exception("empty stack");
		this->_top--;
	}
};
bool isBalanced(string input) {
	if (input.empty()) return false;
	stack<char> s;
	
	for (int i = 0; i < input.length(); i++)
	{
		char c = input.at(i);
		if ((c >= '0' && c <= '9') || c == ' ')
		{
			continue;
		}
		if (c == '(' || c == '[')
		{
			s.push(c);
		}
		if (c == ')' || c == ']')
		{
			if (s.empty())
			{
				return false;
			}
			char top = s.top();
			if ((c == ')' && top != '(') || (c == ']' && top != '['))
			{
				return false;
			}																				 
			s.pop();
		}
	}
	if (!s.empty()) 
	{
		return false;
	}
	return true;
}

void RunIsBalancedA()
{
	char *str = "((4 5 )[]5555)[4[5(555))0]";
	bool res = isBalanced(str);
}

struct LinkedListNode {
	int val;
	LinkedListNode *next;
};
LinkedListNode* manipulateList(LinkedListNode* root) {
	if (NULL == root || NULL == root->next || NULL == root->next->next) return root;
	LinkedListNode *fast = root;
	LinkedListNode *slow = root;
	LinkedListNode *pre = NULL;
	while(fast != NULL && fast->next != NULL)
	{
		pre = slow;
		slow = slow->next;
		fast = fast->next->next;
	}
	pre->next = NULL;
	LinkedListNode *cur = root;
	LinkedListNode *tail = slow;
	while(slow != NULL && cur != NULL)
	{
		tail = slow;
		LinkedListNode* curnext = cur->next;
		LinkedListNode*	slownext = slow->next;

		cur->next = slow; 		
		slow->next = curnext;

		cur = curnext;
		slow = slownext;
	}
	if (slow != NULL)
	{
		tail->next = slow;
	}
	return root;
}

void markUnsurrounedRegions(vector<vector<char> > &board, int x, int y)
{
	stack<int> next;
	if (board[x][y] == 'O')
	{
		next.push(x);
		next.push(y);
		board[x][y] = '#';
	}

	while (!next.empty())
	{
		int j = next.top();
		next.pop();
		int i = next.top();
		next.pop();
		
		board[i][j] = '#';
		if (i > 0 && board[i-1][j] == 'O') { next.push(i-1); next.push(j); }
		if (i < board.size() - 1 && board[i+1][j] == 'O') { next.push(i+1); next.push(j); }
		if (j > 0 && board[i][j-1] == 'O') { next.push(i);	next.push(j-1); }
		if (j < board[0].size() - 1 && board[i][j+1] == 'O') { next.push(i); next.push(j+1); }
	}
}
void surrounedRegions(vector<vector<char>> &board) {
	if (board.size() <= 0) return;
	if (board[0].size() <= 0) return;

	int row = board.size();
	int col = board[0].size();
	for (int i = 0; i < col; i++)
	{
		if (board[0][i] == 'O') markUnsurrounedRegions(board, 0, i);
		if (board[row-1][i] == 'O') markUnsurrounedRegions(board, row - 1, i);
	}
	for (int i = 1; i < row - 1; i++)
	{
		if (board[i][0] == 'O') markUnsurrounedRegions(board, i, 0);
		if (board[i][col-1] == 'O') markUnsurrounedRegions(board, i, col - 1);
	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (board[i][j] == 'O') board[i][j] = 'X';
		}
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (board[i][j] == '#') board[i][j] = 'O';
		}
	}        
}

/*
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).
The robot can only move either down or right at any point in time. 
The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).
How many possible unique paths are there?		 
Above is a 3 x 7 grid. How many possible unique paths are there?	
Note: m and n will be at most 100.
*/
int uniquePaths(int m, int n) 
{
	if (m <= 0 || n <= 0) return -1;

	vector<vector<int> > result(m);
	for (size_t i = 0; i < m; i++)
	{
		result[i].resize(n, 0);
	}

	for (size_t i = 0; i < m; i++)
	{
		result[i][n-1] = 1;
	}
	for (size_t j = 0; j < n-1; j++)
	{
		result[m-1][j] = 1;
	}

	for (int x = m-2; x >= 0; x--)
	{
		for (int y = n-2; y >= 0; y--)
		{
			result[x][y] = result[x+1][y] + result[x][y+1];
		}
	}

	return result[0][0];
}	 

void RunUniquePaths()
{
	int r = uniquePaths(2, 2);
}

/*
Follow up for "Unique Paths":	
Now consider if some obstacles are added to the grids. How many unique paths would there be?  
An obstacle and empty space is marked as 1 and 0 respectively in the grid.		   
For example,
There is one obstacle in the middle of a 3x3 grid as illustrated below.		
[
[0,0,0],
[0,1,0],
[0,0,0]
]
The total number of unique paths is 2.		
Note: m and n will be at most 100.
*/										  
int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) 
{
	if (obstacleGrid.size() <= 0 || obstacleGrid[0].size() <= 0) return -1;
	int m = obstacleGrid.size();
	int n = obstacleGrid[0].size();

	vector<vector<int> > result(m);
	for (size_t i = 0; i < m; i++)
	{
		result[i].resize(n, 0);
	}

	bool blocked = false;
	for (int i = m-1; i >= 0; i--)
	{
		if (!blocked && obstacleGrid[i][n-1] == 1) blocked = true;
		if (blocked) result[i][n-1] = 0; else result[i][n-1] = 1;
	}
	blocked = false;
	for (int j = n-1; j >= 0; j--)
	{
		if (!blocked && obstacleGrid[m-1][j] == 1) blocked = true;
	 	if (blocked) result[m-1][j] = 0; else result[m-1][j] = 1;
	}

	for (int x = m-2; x >= 0; x--)
	{
		for (int y = n-2; y >= 0; y--)
		{
			if (obstacleGrid[x][y] == 0) result[x][y] = 0;
			else result[x][y] = result[x+1][y] + result[x][y+1];
		}
	}

	return result[0][0];														
}

/*
The set [1,2,3,…,n] contains a total of n! unique permutations.

By listing and labeling all of the permutations in order,
We get the following sequence (ie, for n = 3):

"123"
"132"
"213"
"231"
"312"
"321"
Given n and k, return the kth permutation sequence.

Note: Given n will be between 1 and 9 inclusive.
*/
string getPermutation(int n, int k) 
{
	vector<int> numbers;																					  
	long long factorial = 1;
	for (int i = 1; i <= n; i++)
	{
		numbers.push_back(i);
		if (i < n) factorial = factorial * i;
	}

	string result;
	n--;
	while(n > 0)
	{
		int index = (k-1) / factorial;
		result.push_back(numbers[index] + '0');
		for (int i = index; i < numbers.size() - 1; i++)
		{
			numbers[i] = numbers[i+1];
		}
		k = k - index * factorial;
		factorial /= n;
		n--;					  		
	}
	result.push_back(numbers[0]+'0');

	return result;
}

void RunGetPermutation()
{
	string s1 = getPermutation(3, 1);
	s1 = getPermutation(3, 2);
	s1 = getPermutation(3, 3);
	s1 = getPermutation(3, 4);
	s1 = getPermutation(3, 5);
	s1 = getPermutation(3, 6);	 
}

/*
Given an array of non-negative integers, you are initially positioned at the first index of the array.
Each element in the array represents your maximum jump length at that position.
Determine if you are able to reach the last index.
For example:
A = [2,3,1,1,4], return true.
A = [3,2,1,0,4], return false.
*/
bool canJump(int A[], int n) 
{
	if (n <= 0) return false;
	if (n == 1) return true;    

	vector<int> steps(n-1, -1);

	for (int i = n-2; i >= 0; i--)
	{
		if (A[i] >= (n-1-i)) { steps[i] = 1; continue; }
		int step = INT_MAX;
		for (int j = 1; j <= A[i] && j < n-i;)
		{
			if (steps[i+j] < 0) 
			{
				j += max(A[i+j]+1,1); 
				continue; 
			}
			if (steps[i+j] < step) 
			{
				step = steps[i+j];					
			}
			j++;
		}
		if (step == INT_MAX) 
		{
			steps[i] = -1; 
		} 
		else 
		{
			steps[i] = step + 1;
		}
	}				

	return (steps[0] > 0);        
}

/*
Given an array of non-negative integers, you are initially positioned at the first index of the array.	
Each element in the array represents your maximum jump length at that position.							
Your goal is to reach the last index in the minimum number of jumps.									
For example:
Given array A = [2,3,1,1,4]																				
The minimum number of jumps to reach the last index is 2. (Jump 1 step from index 0 to 1, then 3 steps to the last index.)
*/
int jump(int A[], int n)
{
	return 0;
}

int maxLeafToRoot(TreeNode *root, int& res)
{
	if (root->left == NULL && root->right == NULL)
	{
		return root->val;
	}

	int left;
	if (root->left != NULL)
	{
		left = maxLeafToRoot(root->left, res);	
	}
	int right;
	if (root->right != NULL)
	{
		right = maxLeafToRoot(root->right, res);
	}

	if (root->left != NULL && root->right != NULL)
	{
		int newRes = left + right + root->val;
		res = max(newRes, res);
		return max(left, right) + root->val;
	}
	else if (root->right == NULL)
	{
		return left + root->val;
	}
	else
	{
		return right + root->val;
	}	
}

int maxPathSumBetweenLeaves(TreeNode *root)
{
	if (root == NULL) return INT_MAX;

	int res = INT_MIN;

	int r = maxLeafToRoot(root, res);
	return res;
}
						
void RunMaxLeafPathSum()
{
	TreeNode root(-5);
	TreeNode n1(5);
	TreeNode n2(-3);
	TreeNode n3(-2);
	TreeNode n4(-1);
	TreeNode n5(-3);
	root.left = &n1;
	root.right = &n5;
	n1.left = &n2;
	n2.left = &n3;
	n2.right = &n4;		
	int r = maxPathSumBetweenLeaves(&root);

	TreeNode r1(0);
	TreeNode r2(-10);
	TreeNode r3(10);
	r1.left = &r2;
	r1.right = &r3;
	int res = maxPathSumBetweenLeaves(&r1);
}

/*
Largest Number Total Accepted: 4768 Total Submissions: 32218 My Submissions Question Solution 
	Given a list of non negative integers, arrange them such that they form the largest number.

	For example, given [3, 30, 34, 5, 9], the largest formed number is 9534330.

Note: The result may be very large, so you need to return a string instead of an integer.
*/
int getCeiling(int num)
{
	int result = 10;
	int n = num;
	while(n >= 10)
	{
		result *= 10;
		n = n / 10;
	}

	return result;
}

string largestNumber(vector<int> &num) 
{
	if (num.size() == 0) return "";

	string s;
	vector<int> h(num.size());
	for (int i = 0; i < num.size(); i++)
	{
		h[i] = getCeiling(num[i]);
	}
	char buf[100];
	bool leadingzero = true;
	for (int i = 0; i < h.size(); i++)
	{						   
		int m = i;
		for (int j = i+1; j < h.size(); j++)
		{							  
			if ((long long)num[j]*h[m] + num[m] > (long long)num[m]*h[j] + num[j]) m = j;
		}
		int temp = h[i];
		h[i] = h[m];
		h[m] = temp;
		temp = num[i];
		num[i] = num[m];
		num[m] = temp;
		sprintf_s(buf, 99, "%d", num[i]);
		if (leadingzero && num[i] == 0) { continue; }
		s.append(buf);
		leadingzero = false;
	}
	if (s.empty()) return "0";
	return s;
}

void RunLargestNumber()
{
	vector<int> num;
	num.push_back(999999998);
	num.push_back(999999997);
	num.push_back(999999999);
	string s = largestNumber(num);
}

/*
Search Insert Position Total Accepted: 41287 Total Submissions: 116878 My Submissions Question Solution 
Given a sorted array and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.

You may assume no duplicates in the array.

Here are few examples.
[1,3,5,6], 5 → 2
[1,3,5,6], 2 → 1
[1,3,5,6], 7 → 4
[1,3,5,6], 0 → 0
*/
int searchInsert(int A[], int n, int target) {
	if (n <= 0) return 0;
	int l = 0;
	int r = n-1;
	while(l < r-1)
	{
		int mid = (l+r)/2;
		if (A[mid] == target) 
		{
			return mid;
		}
		else if (target < A[mid])
		{
			r = mid - 1;
		}
		else 
		{
			l = mid + 1;
		}
	}
	if (target <= A[l])
	{
		return l;
	}
	else if (target == A[r])
	{
		return r;
	}
	else if (target > A[r])
	{
		return r+1;
	}
	else 
	{
		return l+1;
	}
}

/*
Sum Root to Leaf Numbers Total Accepted: 33808 Total Submissions: 111688 My Submissions Question Solution 
Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.

An example is the root-to-leaf path 1->2->3 which represents the number 123.

Find the total sum of all root-to-leaf numbers.

For example,

1
/ \
2   3
The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.

Return the sum = 12 + 13 = 25.
*/
int getSum(TreeNode *root, int sum)
{
	if (root->left == NULL && root->right == NULL)
	{
		//sum = sum*10+root->val;
		return sum;
	}
	int newsum = 0;
	int lsum = 0, rsum = 0;
	if (root->left != NULL)
	{
		lsum = sum*10+root->left->val;
		newsum += getSum(root->left, lsum);
	}
	if (root->right != NULL)
	{
		rsum = sum*10+root->right->val;
		newsum += getSum(root->right, rsum);
	}
	return newsum;
}
int sumNumbers(TreeNode *root) {
	if (root == NULL) return 0;
	int sum = getSum(root, root->val);
	return sum;
}												
					   
int DnaSeqToInt(string seq)
{
	int r = 0;
	for (int i = 0; i < 10; i++)
	{
		char c = seq.at(i);
		int n = 0;
		switch(c)
		{
		case 'A':
			n = 0;
			break;
		case 'C':
			n = 1;
			break;
		case 'G':
			n = 2;
			break;
		case 'T':
			n = 3;
			break;
		}
		r = r << 2;
		r = r | n;
	}
	return r;
}

/*
Repeated DNA Sequences Total Accepted: 6839 Total Submissions: 36304 My Submissions Question Solution 
All DNA is composed of a series of nucleotides abbreviated as A, C, G, and T, for example: "ACGAATTCCG". When studying DNA, it is sometimes useful to identify repeated sequences within the DNA.

Write a function to find all the 10-letter-long sequences (substrings) that occur more than once in a DNA molecule.

For example,

Given s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT",

Return:
["AAAAACCCCC", "CCCCCAAAAA"].
*/
vector<string> findRepeatedDnaSequences(string s) 
{
	if (s.length() < 10) { return vector<string>(); }
	map<int, int> seqMap;  
	vector<string> results;
	const int SeqLen = 10;
	for (int i = 0; i <= s.length() - SeqLen; i++)				
	{
		string sub = s.substr(i, SeqLen);
		int n = DnaSeqToInt(sub);
		if (seqMap.find(n) != seqMap.end())
		{					
			int count = seqMap[n];
			if (count == 1)
			{
				results.push_back(sub);
			}
			seqMap[n] = (count+1);				
		}
		else
		{
			seqMap[n] = 1;
		}
	}

	return results;
}

/*			  
Number of 1 Bits Total Accepted: 2642 Total Submissions: 6477 My Submissions Question Solution 
Write a function that takes an unsigned integer and returns the number of ’1' bits it has (also known as the Hamming weight).

For example, the 32-bit integer ’11' has binary representation 00000000000000000000000000001011, so the function should return 3.
*/
int hammingWeight(int n) {
	int r = 1;
	int count = 0;
	for(int i = 0; i < 32; i++)
	{
		if ((n & r) != 0)
		{
			count++;
		}
		r = r << 1;
	}
	return count;
}

/*
* Definition for undirected graph.
*/
struct UndirectedGraphNode {
     int label;
     vector<UndirectedGraphNode *> neighbors;
     UndirectedGraphNode(int x) : label(x) {};
 };

/*
Clone Graph Total Accepted: 32207 Total Submissions: 136303 My Submissions Question Solution 
Clone an undirected graph. Each node in the graph contains a label and a list of its neighbors.


OJ's undirected graph serialization:
Nodes are labeled uniquely.

We use # as a separator for each node, and , as a separator for node label and each neighbor of the node.
As an example, consider the serialized graph {0,1,2#1,2#2,2}.

The graph has a total of three nodes, and therefore contains three parts as separated by #.

First node is labeled as 0. Connect node 0 to both nodes 1 and 2.
Second node is labeled as 1. Connect node 1 to node 2.
Third node is labeled as 2. Connect node 2 to node 2 (itself), thus forming a self-cycle.
Visually, the graph looks like the following:

1
/ \
/   \
0 --- 2
/ \
\_/										  
*/						
//bfs
UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) 
{
	if (node == NULL) return NULL;							   
	queue<UndirectedGraphNode*> nodeQueue;
	map<int, UndirectedGraphNode*> clonedNodes;			  

	nodeQueue.push(node);							
	UndirectedGraphNode *clonednode = new UndirectedGraphNode(node->label);
	clonedNodes[node->label] = clonednode;

	while(!nodeQueue.empty())
	{
		UndirectedGraphNode* n = nodeQueue.front();
		nodeQueue.pop(); 
		UndirectedGraphNode* clone = clonedNodes[n->label];
		
		// add neighbors
		for (int i = 0; i < n->neighbors.size(); i++)
		{
			UndirectedGraphNode* neighbor = n->neighbors[i];

			if (clonedNodes.find(neighbor->label) == clonedNodes.end())
			{
				nodeQueue.push(neighbor); 			   
				UndirectedGraphNode * clonenbr = new UndirectedGraphNode(neighbor->label);
				clonedNodes[neighbor->label] = clonenbr;
				clone->neighbors.push_back(clonenbr);
			}	
			else
			{
				clone->neighbors.push_back(clonedNodes[neighbor->label]);
			}
		}	   		
	}						  
	return clonednode;
}

map<int, UndirectedGraphNode*> clonemap;
UndirectedGraphNode *cloneGraph_dfs(UndirectedGraphNode *node) 
{
	if (node == NULL) return NULL;							   
	if (clonemap.find(node->label) != clonemap.end())
	{
		return clonemap[node->label];						  
	}
	UndirectedGraphNode* clone = new UndirectedGraphNode(node->label);
	clonemap[node->label] = clone;
	for (int i = 0; i < node->neighbors.size(); i++)
	{
		clone->neighbors.push_back(cloneGraph_dfs(node->neighbors[i]));
	}
	return clone;
}

void RunCloneGraph()
{												  
	UndirectedGraphNode n1(-1);
	UndirectedGraphNode n2(1);
	n1.neighbors.push_back(&n2);
	n2.neighbors.push_back(&n1);
	cloneGraph(&n1);
}


/*
Combination Sum Total Accepted: 38203 Total Submissions: 137741 My Submissions Question Solution 
Given a set of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.

The same repeated number may be chosen from C unlimited number of times.

Note:
All numbers (including target) will be positive integers.
Elements in a combination (a1, a2, … , ak) must be in non-descending order. (ie, a1 ≤ a2 ≤ … ≤ ak).
The solution set must not contain duplicate combinations.
For example, given candidate set 2,3,6,7 and target 7, 
A solution set is: 
[7] 
[2, 2, 3] 
*/
vector<vector<int> > combinationSum(vector<int> &candidates, int target) 
{
	if (candidates.size() <= 0) return vector<vector<int>>();
	if (target <= 0) return vector<vector<int>>();
	sort(candidates.begin(), candidates.end());

	vector<vector<int>> results;
	vector<int> oneresult;
	for (int i = 0; i < candidates.size(); i++)
	{
		combinationSum(candidates, target, i, results, oneresult);
	}
	return results;
}															  
												  
void combinationSum(vector<int> &candidates, int target, int index, vector<vector<int>> &results, vector<int> one)
{
	if (target < candidates[index]) return;
	else if (target > candidates[index])
	{
		int newtarget = target - candidates[index];	
		for (int i = index; i < candidates.size(); i++)
		{
			vector<int> r;														 
			for (int j = 0; j < one.size(); j++)
			{
				r.push_back(one[j]);
			}
			combinationSum(candidates, newtarget, i, results, r);
		}		
	}
	else
	{
		one.push_back(candidates[index]);
		results.push_back(one);
	}
}

/*
Implement Queue using Stacks Total Accepted: 4722 Total Submissions: 13629 My Submissions Question Solution 
Implement the following operations of a queue using stacks.

push(x) -- Push element x to the back of queue.
pop() -- Removes the element from in front of queue.
peek() -- Get the front element.
empty() -- Return whether the queue is empty.
Notes:
You must use only standard operations of a stack -- which means only push to top, peek/pop from top, size, and is empty operations are valid.
Depending on your language, stack may not be supported natively. You may simulate a stack by using a list or deque (double-ended queue), as long as you use only standard operations of a stack.
You may assume that all operations are valid (for example, no pop or peek operations will be called on an empty queue).
*/
class Queue {
    stack<int> s;
    stack<int> tmp;
public:
    // Push element x to the back of queue.
    void push(int x) {
        s.push(x);
    }

    // Removes the element from in front of queue.
    void pop(void) {
        while(!s.empty())
        {
            int v = s.top();
            s.pop();
            if (s.empty())
            {
                break;
            }
            tmp.push(v);
        }
        while(!tmp.empty())
        {
            int v = tmp.top();
            s.push(v);
            tmp.pop();
        }
    }

    // Get the front element.
    int peek(void) {
        int ret = 0;
        while(!s.empty())
        {
            ret = s.top();
            s.pop();
            tmp.push(ret);
        }
        while(!tmp.empty())
        {
            int v = tmp.top();
            s.push(v);
            tmp.pop();
        }        
        return ret;
    }

    // Return whether the queue is empty.
    bool empty(void) {
        return s.empty();
    }
};

/*
Power of Two Total Accepted: 8823 Total Submissions: 29361 My Submissions Question Solution 
Given an integer, write a function to determine if it is a power of two.
*/
bool isPowerOfTwo(int n) {
	int t = 1;
	if (n <= 0)return false;
	
	for (int i = 0; i < 32; i++)
	{
		if (n == t)return true;
		t = t << 1;
	}
	return false;
}

/*
Summary Ranges Total Accepted: 8819 Total Submissions: 45695 My Submissions Question Solution 
Given a sorted integer array without duplicates, return the summary of its ranges.

For example, given [0,1,2,4,5,7], return ["0->2","4->5","7"].
*/
string printRange(int s, int pre)
{
	char buf[1000];
	memset(buf, 0, 1000);
	if (s == pre)
	{
		sprintf(buf, "%d", s);
		string r(buf);
		return r;
	}
	else
	{
		sprintf(buf, "%d->%d", s, pre);
		string r(buf);
		return r;
	}
}
vector<string> summaryRanges(vector<int>& nums) {
	if (nums.size() <= 0)return vector<string>();
	vector<string> result;
	int s = nums[0];
	int e = s;
	int pre = s;
	for(int i = 1; i < nums.size(); i++)
	{
		e = nums[i];
		if (e == pre+1)
		{
			pre = e;
			continue;
		}
		else
		{
			result.push_back(printRange(s, pre));
			s = e;
			pre = e;
			continue;
		}
	}
	result.push_back(printRange(s, pre));
	return result;
}

/*
Invert Binary Tree Total Accepted: 20317 Total Submissions: 57012 My Submissions Question Solution 
Invert a binary tree.

     4
   /   \
  2     7
 / \   / \
1   3 6   9
to
     4
   /   \
  7     2
 / \   / \
9   6 3   1
Trivia:
This problem was inspired by this original tweet by Max Howell:
Google: 90% of our engineers use the software you wrote (Homebrew), but you can’t invert a binary tree on a whiteboard so fuck off.
*/
TreeNode* invertTree(TreeNode* root) {
	if (root == NULL) return root;
	invertTree(root->left);
	invertTree(root->right);
	TreeNode* tmp = root->right;
	root->right = root->left;
	root->left = tmp;
	return root;
}

/*
Implement Stack using Queues Total Accepted: 8233 Total Submissions: 27201 My Submissions Question Solution 
Implement the following operations of a stack using queues.

push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
empty() -- Return whether the stack is empty.
Notes:
You must use only standard operations of a queue -- which means only push to back, peek/pop from front, size, and is empty operations are valid.
Depending on your language, queue may not be supported natively. You may simulate a queue by using a list or deque (double-ended queue), as long as you use only standard operations of a queue.
You may assume that all operations are valid (for example, no pop or top operations will be called on an empty stack).
*/
class Stack {
    queue<int> q[2];
    int index;
public:
    Stack()
    {
        index = 0;
    }
    
    // Push element x onto stack.
    void push(int x) {
        q[index].push(x);    
    }

    // Removes the element on top of the stack.
    void pop() {
        int other = 1;
        if (index ==1) other = 0;
        while(!q[index].empty()) 
        {
            int v = q[index].front();
            q[index].pop();
            if (q[index].empty()) break;
            q[other].push(v);
        }
        index = other;
    }

    // Get the top element.
    int top() {
        int other = 1;
        if (index ==1) other = 0;
        int v;
        while(!q[index].empty()) 
        {
            v = q[index].front();
            q[index].pop();
            q[other].push(v);
        }
        index = other;
        return v;
    }

    // Return whether the stack is empty.
    bool empty() {
        return q[index].empty();
    }
};

/*
Rectangle Area Total Accepted: 10096 Total Submissions: 39709 My Submissions Question Solution 
Find the total area covered by two rectilinear rectangles in a 2D plane.

Each rectangle is defined by its bottom left corner and top right corner as shown in the figure.

Rectangle Area
Assume that the total area is never beyond the maximum possible value of int.
*/
int crossArea(int A, int B, int C, int D, int E, int F, int G, int H)
{
	int l = max(A,E);
	int r = min(C,G);
	int t = min(D,H);
	int b = max(B, F);
	if (r<=l) return 0;
	if (b>=t) return 0;
	return (r-l)*(t-b);        
}
int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
	int a = (C-A)*(D-B);
	int b = (H-F)*(G-E);
	int c = crossArea(A,B,C,D,E,F,G,H);
	return a+b-c;
}

/*
Delete Node in a Linked List Total Accepted: 4269 Total Submissions: 8827 My Submissions 
Question  Solution  
Write a function to delete a node (except the tail) in a singly linked list, given only access to that node. 
Supposed the linked list is 1 -> 2 -> 3 -> 4 and you are given the third node with value 3, the linked list should become 1 -> 2 -> 4 after calling your function. 
*/
void deleteNode(ListNode* node) {
	if (node == NULL) return;
	ListNode *pre = node;
	while(node != NULL)
	{
		if (node->next != NULL)
		{
			node->val = node->next->val;
			pre = node;
			node = node->next;
			continue;
		}
		else
		{
			pre->next = NULL;
			delete node;
			return;
		}
	}
}

/*
Lowest Common Ancestor of a Binary Search Tree Total Accepted: 6248 Total Submissions: 16136 My Submissions 
Question  Solution  

Given a binary search tree (BST), find the lowest common ancestor (LCA) of two given nodes in the BST. 

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes v and w as the lowest node in T that has both v and w as descendants (where we allow a node to be a descendant of itself).” 
        _______6______
       /              \
    ___2__          ___8__
   /      \        /      \
   0      _4       7       9
         /  \
         3   5

For example, the lowest common ancestor (LCA) of nodes 2 and 8 is 6. Another example is LCA of nodes 2 and 4 is 2, since a node can be a descendant of itself according to the LCA definition.

*/
    stack<TreeNode*> getPathFromRoot(TreeNode *root, TreeNode *node)
    {
        stack<TreeNode*> path;
        isInTree(root, node, path);
        return path;
    }
    
    bool isInTree(TreeNode *root, TreeNode *node, stack<TreeNode*>& path)
    {
        if (root == node) 
        {
            path.push(root);
            return true; 
        }
        if (root == NULL) { return false; }
        if (isInTree(root->left, node, path))
        {
            path.push(root);
            return true;
        }
        if (isInTree(root->right, node, path))
        {
            path.push(root);
            return true;
        }
        return false;
    }
    
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) 
    {
        stack<TreeNode*> pathp = getPathFromRoot(root, p);
        stack<TreeNode*> pathq = getPathFromRoot(root, q);
        TreeNode *ancestor = root;
        while(!pathp.empty() && !pathq.empty())
        {
            TreeNode* pparent = pathp.top();
            pathp.pop();
            TreeNode* qparent = pathq.top();
            pathq.pop();
            if (pparent != qparent)
            {
                return ancestor;
            }
            else
            {
                ancestor = pparent;
            }
        }
        return ancestor;
    }
	
/*
Contains Duplicate II Total Accepted: 15290 Total Submissions: 59746 My Submissions 
Question  Solution  
Given an array of integers and an integer k, find out whether there there are two distinct indices i and j in the array such that nums[i] = nums[j] and the difference between i and j is at most k. 
*/
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        map<int, int> m;
        for(int i = 0; i < nums.size(); i++)
        {
            int v = nums[i];
            if (m.find(v) == m.end())
            {
                m[v] = i;
            }
            else
            {
                int j = m[v];
                if (i-j <= k) return true;
                m[v] = i;
            }
        }
        return false;
    }	
	
/*
Contains Duplicate Total Accepted: 20628 Total Submissions: 57224 My Submissions 
Question  Solution  
Given an array of integers, find if the array contains any duplicates. Your function should return true if any value appears at least twice in the array, and it should return false if every element is distinct. 
*/	
    bool containsDuplicate(vector<int>& nums) {
        map<int, int> m;
        for(int i = 0; i < nums.size(); i++)
        {
            int v = nums[i];
            if (m.find(v) == m.end())
            {
                m[v] = i;
            }
            else
            {
                return true;
            }
        }
        return false;
    }

/*
Reverse Linked List Total Accepted: 27333 Total Submissions: 85717 My Submissions 
Question  Solution  
Reverse a singly linked list.
click to show more hints.
Hint: 
A linked list can be reversed either iteratively or recursively. Could you implement both?
*/
    ListNode* reverseList(ListNode* head) {
        if (head == NULL) return head;
        ListNode *next = head->next;
        ListNode *pre = NULL;
        ListNode *cur = head;
        while(next != NULL)
        {
            cur->next = pre;
            pre = cur;
            cur = next;
            next = next->next;
        }
        cur->next = pre;
        return cur;
    }

    ListNode* reverseList_recursive(ListNode* head) {
        if (head == NULL) return head;
        if (head->next != NULL)
        {
            ListNode* newhead = reverseList(head->next);
            head->next->next = head;
            head->next = NULL;
            return newhead;
        }
        else
        {
            return head;
        }
    }
	
/*
Isomorphic Strings Total Accepted: 19208 Total Submissions: 78736 My Submissions Question Solution 
Given two strings s and t, determine if they are isomorphic.

Two strings are isomorphic if the characters in s can be replaced to get t.

All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character but a character may map to itself.

For example,
Given "egg", "add", return true.

Given "foo", "bar", return false.

Given "paper", "title", return true.

Note:
You may assume both s and t have the same length.
*/	
    vector<int> encode(string s)
    {
        map<char, int> m;
        vector<int> v;
        int code = 0;
        for(int i = 0; i < s.length(); i++)
        {
            char c = s.at(i);
            if (m.find(c) == m.end())
            {
                code++;
                m[c] = code;
                v.push_back(code);
            }
            else
            {
                v.push_back(m[c]);
            }
        }
        return v;
    }
    bool isIsomorphic(string s, string t) {
        vector<int> sc = encode(s);
        vector<int> tc = encode(t);
        for (int i = 0; i < sc.size(); i++)
        {
            if (sc[i] != tc[i]) return false;
        }
        return true;
    }

/*
Count Primes Total Accepted: 20709 Total Submissions: 107498 My Submissions Question Solution 
Description:

Count the number of prime numbers less than a non-negative number, n.
*/
    int countPrimes(int n) {
        vector<bool> num(n, true);
        for (int i = 2; i <= n/i; i++)
        {
            if (num[i] == false) continue;
            for (int j = 2; j <= n/i; j++)
            {
                num[i*j] = false;
            }
        }
        int np = 0;
        for (int i = 2; i < n; i++)
        {
            if (num[i] == true) np++;
        }
        return np;
    }

/*
Remove Linked List Elements Total Accepted: 21045 Total Submissions: 80989 My Submissions Question Solution 
Remove all elements from a linked list of integers that have value val.

Example
Given: 1 --> 2 --> 6 --> 3 --> 4 --> 5 --> 6, val = 6
Return: 1 --> 2 --> 3 --> 4 --> 5
*/
    ListNode* removeElements(ListNode* head, int val) {
        ListNode dummy(val+1);
        dummy.next = head;
        ListNode *next = head;
        ListNode *cur = &dummy;
        while(next != NULL)
        {
            if (next->val != val)
            {
                cur = next;
                next = next->next;
            }
            else
            {
                ListNode* tmp = next;
                next = next->next;
                cur->next = next;
                delete tmp;
            }
        }
        return dummy.next;
    }

/* quicksort */
void swap(int *a, int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

int partition(int arr[], int l, int h)
{  
  for (int k = l; k <= h; k++) { cout << arr[k] << ","; }
  int pivot = arr[h];
  int i = l;
  for (int j = l; j < h; j++)
  {
    if (arr[j] < pivot)
    {
      swap(&arr[i], &arr[j]);
      i++;
    }
  }
  swap(&arr[i], &arr[h]);
  
  cout << " --> ";
  for (int k = l; k <= h; k++) { cout << arr[k] << ",";  }
  cout << "\n";
  return i;
}

int partition2(int arr[], int l, int h)
{
  for (int k = l; k <= h; k++) { cout << arr[k] << ","; } 
  cout << "\n";
  
  int pivot = arr[h];
  cout << "pivot: " << pivot << "\n";
  
  int i = l;
  int j = h;
  while (i<j)
  {
    while(arr[i] < pivot) {i++;}
    while(arr[j] >= pivot) {j--;}
    if (i>=j) break;
    swap(&arr[i], &arr[j]);
    cout << "swap " << arr[i] << " <-> " << arr[j] << "\n";
  }
  swap(&arr[i], &arr[h]);
  
  cout << " --> ";
  for (int k = l; k <= h; k++) { cout << arr[k] << ",";  }
  cout << "\n";
  
  return i;
}

void quicksort(int arr[], int l, int h)
{
  if (l >= h) return;
  int p = partition(arr, l, h);
  quicksort(arr, l, p-1);
  quicksort(arr, p+1, h);
}

int RunQuickSort() {
  int* arr = new int[10];
  for (int i = 0; i < 10; i++)
  {
    if (i % 2 == 0)
      arr[i] = 100-i;
    else
      arr[i] = 100 + i;
  }
  for (int i = 0; i < 10; i++)
  {
    cout << arr[i] << " ,";
  }
  cout << "\n";
  
  quicksort(arr, 0, 9);
  for (int i = 0; i < 10; i++)
  {
    cout << arr[i] << " ,";
  }
}

/*
Valid Anagram
Given two strings s and t, write a function to determine if t is an anagram of s.

For example,
s = "anagram", t = "nagaram", return true.
s = "rat", t = "car", return false. 

Note:
 You may assume the string contains only lowercase alphabets
*/
bool isAnagram(string s, string t) {
	if (s.length() != t.length()) return false;
	
	unordered_map<char, int> sm, tm;
	for (int i = 0; i < s.length(); i++)
	{
		sm[s.at(i)]++;
		tm[t.at(i)]++;
	}
	if (sm.size() != tm.size()) return false;
	for ( auto it = sm.begin(); it != sm.end(); ++it )
	{
		if (it->second != tm[it->first]) return false;
	}
	return true;
}

/*
Nim Game

You are playing the following Nim Game with your friend: There is a heap of stones on the table, each time one of you take turns to remove 1 to 3 stones. The one who removes the last stone will be the winner. You will take the first turn to remove the stones. 

Both of you are very clever and have optimal strategies for the game. Write a function to determine whether you can win the game given the number of stones in the heap. 

For example, if there are 4 stones in the heap, then you will never win the game: no matter 1, 2, or 3 stones you remove, the last stone will always be removed by your friend. 

Hint:
 1.If there are 5 stones in the heap, could you figure out a way to remove the stones such that you will always be the winner? 
*/
bool canWinNim(int n) {
	return (n%4!=0);
}

/*
Add Digits
Given a non-negative integer num, repeatedly add all its digits until the result has only one digit. 

For example: 

Given num = 38, the process is like: 3 + 8 = 11, 1 + 1 = 2. Since 2 has only one digit, return it. 

Follow up:
 Could you do it without any loop/recursion in O(1) runtime? 

Hint:
 1.A naive implementation of the above process is trivial. Could you come up with other methods? 
2.What are all the possible results?
3.How do they occur, periodically or randomly?
4.You may find this Wikipedia article useful.
*/
int addDigits(int num) {
	return num-9*((num-1)/9);
}

/*
Ugly Number

Write a program to check whether a given number is an ugly number. 

Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. For example, 6, 8 are ugly while 14 is not ugly since it includes another prime factor 7. 

Note that 1 is typically treated as an ugly number. 
*/	
bool isUgly(int num) {
	if (num <= 0) return false;
	if (num <= 6) return true;
	
	while(num > 1)
	{
		if (num % 2 != 0 && num % 3 != 0 && num % 5 != 0) return false;
		if (num % 2 == 0) num = num / 2;
		if (num % 3 == 0) num = num / 3;
		if (num % 5 == 0) num = num / 5;
	}
	
	if (num != 1) return false;
	return true;
}	

/*
House Robber

You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security system connected and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.
*/
int rob(vector<int>& nums) {
	if (nums.size() == 0) return 0;
	if (nums.size() == 1) return nums[0];
	if (nums.size() == 2) return max(nums[0], nums[1]);
	
	int res[nums.size()];
	res[0] = nums[0];
	res[1] = max(nums[0], nums[1]);
	
	for (int i = 2; i < nums.size(); i++)
	{
		res[i] = max(res[i-2]+nums[i], res[i-1]);
	}
	return res[nums.size()-1];
}

/*
Happy Number
Write an algorithm to determine if a number is "happy".

A happy number is a number defined by the following process: Starting with any positive integer, replace the number by the sum of the squares of its digits, and repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1. Those numbers for which this process ends in 1 are happy numbers.

Example: 19 is a happy number
12 + 92 = 82
82 + 22 = 68
62 + 82 = 100
12 + 02 + 02 = 1
*/
bool isHappy(int n) {
	if (n <= 0) return false;
	
	int square[] = {0, 1, 4, 9, 16, 25, 36, 49, 64, 81};
	int sum = n;
	unordered_set<int> tmpset;
	
	while(sum != 1)
	{
		int num = sum;
		sum = 0;
		while(num > 0)
		{
			sum += square[num%10];
			num /= 10;
		}
		if (sum == 1) return true;
		if (tmpset.find(sum) != tmpset.end()) return false;
		tmpset.insert(sum);
	}
	return true;
}

/*
Reverse Bits
Reverse bits of a given 32 bits unsigned integer.

For example, given input 43261596 (represented in binary as 00000010100101000001111010011100), return 964176192 (represented in binary as 00111001011110000010100101000000).

Follow up:
 If this function is called many times, how would you optimize it? 

Related problem: Reverse Integer
*/
uint32_t reverseBits(uint32_t n) {
	uint32_t r = 0;
	for (int i = 0; i < 32; i++)
	{
		r = r << 1;
		if ((n & 1) != 0)
		{
			r |= 1;
		}
		n = n >> 1;
	}
	return r;
}

/*
Given an unsorted array nums, reorder it such that nums[0] < nums[1] > nums[2] < nums[3].... 

Example:
 (1) Given nums = [1, 5, 1, 1, 6, 4], one possible answer is [1, 4, 1, 5, 1, 6]. 
 (2) Given nums = [1, 3, 2, 2, 3, 1], one possible answer is [2, 3, 1, 3, 1, 2]. 

Note:
 You may assume all input has valid answer. 

Follow Up:
 Can you do it in O(n) time and/or in-place with O(1) extra space? 
*/
// O(nlogn) time, O(n) space
void wiggleSort(vector<int>& nums) {
	if (nums.size() <= 1) return;
	
	vector<int> tmp = nums;
	sort(tmp.begin(), tmp.end());
	
	nums[0] = tmp[0];
	int j = tmp.size() - 1;
	int k = (tmp.size()+1) / 2;
	for (int i = 0; i < nums.size(); i++)
	{
		if (i % 2 != 0)
		{
			nums[i] = tmp[j--];
		}
		else
		{
			nums[i] = tmp[--k];
		}
	}
}

/*
328. Odd Even Linked List
Given a singly linked list, group all odd nodes together followed by the even nodes. Please note here we are talking about the node number and not the value in the nodes.

You should try to do it in place. The program should run in O(1) space complexity and O(nodes) time complexity.

Example:
 Given 1->2->3->4->5->NULL,
 return 1->3->5->2->4->NULL. 

Note:
 The relative order inside both the even and odd groups should remain as it was in the input. 
 The first node is considered odd, the second node even and so on ... 
*/
ListNode* oddEvenList(ListNode* head) 
{
	if (head == NULL) return head;
	ListNode dummy1(0);
	dummy1.next = head;
	ListNode *odd = head;
	ListNode *oddtail = head;
	ListNode dummy2(0);
	dummy2.next = head->next;
	ListNode *even = &dummy2;
	while(odd != NULL)
	{
		if (odd->next == NULL) 
		{
			oddtail = odd;
			even->next = NULL;
			break;
		}
		ListNode *tmp = odd->next;
		even->next = tmp;
		even = tmp;
		
		odd->next = tmp->next;
		oddtail = odd;
		odd = tmp->next;
	}
	
	oddtail->next = dummy2.next;
	return dummy1.next;
}

/*
326. Power of Three

Given an integer, write a function to determine if it is a power of three. 

Follow up:
 Could you do it without using any loop / recursion? 
*/
bool isPowerOfThree(int n) 
{
	/* 
	//Recursion:
	if (n <= 0) return false;
	if (n == 1) return true;
	if (n%3 == 0) return isPowerOfThree(n/3);
	return false;
	*/
	
	//Loop:
	if (n < 1) return false;
	if (n == 1) return true;
	while(n >= 3)
	{
		if (n % 3 != 0) return false;
		n = n / 3;
	}
	return n == 1;
}
	
int _tmain(int argc, _TCHAR* argv[])
{
	RunQuickSort();
	RunCloneGraph();
	RunLargestNumber();
	RunMaxLeafPathSum();
	RunLongestSubStr();
	RunGetPermutation();
	RunUniquePaths();																		
	RunIsBalancedA();
	RunTrailingZeroes();
	RunCompareVersion();
	RunMinPathSum();
	RunSearchRange();
	RunFractionToDecimal();
	RunNextPermutation();
	RunDivide();
	RunSqrt();
	RunSortColors();
	RunFourSum();
	RunThreeSum();
	RunSearchRotatedSortedArray();
	RunLadderLength();
	RunWordSearchIn2DBoard();
	RunSingleNumberII();
	RunNumDecodings();
	RunSubsetsWithDup();
	RunRestoreIpAddresses();
	RunSortList();
	RunCanCompleteCircuit();
	RunWordBreak();		 	
	RunCountAndSay();
	RunLongestCommonPrefix();
	RunIsPalindrome();
	RunAoti();
	RunTwoSum();
	RunRemoveDup();
	RunBinarySearch();
	RunLongestPalindrome();
	RunLongestPalindromeDP();	
	RunLongestConsecutive();
	RunPlusOne();
	RunClimbStairs();
	RunZeorMatrix();
	RunReverseBetween();
	RunPartitionList();
	RunDeleteDuplicates();
	RunDeleteDuplicatesII();
	RunRotateRight();
	RunRemoveNthFromEnd();
	RunSwapPairs();
	RunReverseKGroup();
	RunCopyRandomList();
	RunReorderList();
	RunEvalRPN();
	RunLargestRectangleArea();
	RunPreorderTraversal();
	RunPrintBinaryTreeByLevel();
	RunIsBalanced();
	RunFlattenTree();
	RunBuildTree();
	return 0;
}

