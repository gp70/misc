#include <iostream>
#include <climits>
#include <ctype.h>

using namespace std;

void printRange(int left, int right);
int sumRange(int left, int right);
int sumArray(int *arr, int size);
int sumArrayInRange(int *arr, int left, int right);
bool isAlphanumeric(string s);
bool anyAlphanumeric(string s);
bool nestedParens(string s);
int sumChar(string s, char c, int count);
bool divisble(int *prices, int size);
bool divide(int *prices, int size, int suma, int sumb);

void printRange(int left, int right)
{
	if (left > right)
		return;
	if (left == right)
	{
		cout << left << "\n";
		return;
	}
	cout << left << " ";
	return printRange(left+1, right);
}

int sumRange(int left, int right)
{
	if (left > right)
		return INT_MIN;								// ERROR
	if (left == right)
		return left;
	return left + sumRange(left + 1, right);
}

int sumArray(int *arr, int size)
{
	return sumArrayInRange(arr, 0, size-1);
}

int sumArrayInRange(int *arr, int left, int right)
{
	if (left > right)
		return INT_MIN;								// ERROR
	if (left == right)
		return arr[left];
	return arr[left] + sumArrayInRange(arr, left + 1, right);
}

bool isAlphanumeric(string s)
{
	if (s.empty())
		return true;
	else
		if (isalnum(s[0]))
			return isAlphanumeric(s.substr(1));
	return false;
}

bool anyAlphanumeric(string s)
{
	if (s.empty())
		return false;
	else
	{
		if (isalnum(s[0]))
			return true;
		else
			return anyAlphanumeric(s.substr(1));
	}
	return false;
}

bool parenTest(string s)
{
	if (s.empty() || s.size() == 1)
		return true;
	if (s[0] == ')' && s[1] == '(')
		return false;
	return parenTest(s.substr(1));
}

bool nestedParens(string s)
{
	if (s.empty())
		return true;
	if (anyAlphanumeric(s))
		return false;
	return ((sumChar(s, '(', 0) == sumChar(s, ')', 0)) && parenTest(s));
}

int sumChar(string s, char c, int count)
{
	if (s.empty())
		return count;
	if (s[0] == c)
		return sumChar(s.substr(1), c, count + 1);
	if (s[0] != c)
		return sumChar(s.substr(1), c, count);
	return count;
}

// Make sumChar helper function for nestedParens

bool divisible(int *prices, int size)
{
	return divide(prices, size, 0, 0);
}

bool divide(int *prices, int size, int suma, int sumb)
{
	if (size == 0)
	{
		cout << suma << "	" << sumb << "\n";
		if (suma == sumb)
		{
			cout << "wtf" << "\n";
			return true;
		}
		return false;
	}
	divide(&prices[1], size - 1, suma + prices[0], sumb);
	divide(&prices[1], size - 1, suma, sumb + prices[0]);
}

int main()
{
	int arr[5] = {1,4,3,2,5};
	int arr2[3] = {1,2,1};
	printRange(-2,10);
	printRange(11,10);
	cout << sumRange(1,3) << "\n";
	cout << sumArray(arr,5) << "\n";
	cout << isAlphanumeric("bob") << "\n";
	cout << isAlphanumeric("bob!") << "\n";

	cout << "-----" << "\n";

	cout << nestedParens("((()))") << endl;      // true (1)
	cout << nestedParens("()") << endl;          // true (1)
	cout << nestedParens("") << endl;            // true (1)

	cout << nestedParens("(((") << endl;         // false (0)
	cout << nestedParens("(()") << endl;         // false (0)
	cout << nestedParens(")(") << endl;          // false (0)
	cout << nestedParens("a(b)c") << endl;       // false (0)

	cout << "-----" << "\n";

	cout << divisible(arr,5) << "\n";
	cout << divisible(arr2,3) << "\n";

	return 0;
}
