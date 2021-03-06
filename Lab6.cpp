﻿// Lab6.cpp (from SortedDriver.cpp)
// Addison Dugal
// 11/5/18
// Construct sorted sequences and call functions that
//   process the sorted sequences.


#include "stdafx.h"
#include "RandomUtilities.h"
#include "ContainerPrinting.h"
#include "winTimer.h"//CHANGE: this to unixTimer.h if on mac/linux
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// post: a sorted vector of listSize random doubles from
//         the range minNum to maxNum has been returned.
vector<double>
getNums(size_t listSize, double minNum, double maxNum)
{
	vector<double> theList;
	for (size_t i = 0; i < listSize; ++i)
	{
		theList.push_back(randReal(minNum, maxNum));
	}

	sort(begin(theList), end(theList));

	return theList;
}


// post: a sorted list of numWords words of length
//         wordLength with characters chosen randomly from
//         alphabet has been returned.
list<string>
getWords(size_t numWords, size_t wordLength, string alphabet)
{
	list<string> theWords;
	for (size_t i = 0; i < numWords; ++i)
	{
		string word;
		for (size_t j = 0; j < wordLength; ++j)
		{
			word += alphabet.at(randInt(0, alphabet.size()));
		}
		theWords.push_back(word);
	}

	theWords.sort();

	return theWords;
}


// pre:  number is not empty;
//       number is sorted from smallest to largest
// post: The most isolated entry in number has been returned
double
mostIsolated(vector<double> & number)
{
	double MI, max = 0;
	if (abs(number[0] - number[1]) > max)// Checks first element, errors if we try to get number[-1]
	{
		max = abs(number[0] - number[1]);
		MI = number[0];
	}
	for (unsigned int i = 1; i < (number.size() - 2); i++) // Iterates through middle of vector (not first and not last)
	{
		if (abs(number[i] - number[i + 1]) > max && abs(number[i] - number[i - 1]) > max)
		{
			if (abs(number[i] - number[i + 1]) < abs(number[i] - number[i - 1]))
			{
				max = abs(number[i] - number[i + 1]);
			}
			else
			{
				max = abs(number[i] - number[i - 1]);
			}
			MI = number[i];
		}
	}
	if (abs(number[number.size() - 1] - number[number.size() - 2]) > max) // Checks last elment, we can't get number[number.size()]
	{
		max = abs(number[number.size() - 1] - number[number.size() - 2]);
		MI = number[number.size() - 1];
	}
	return MI;
}


// pre:  A and B are sorted.
// post: The number of strings in A that do not occur in B
//         has been returned.
int
unmatched(list<string> & A, list<string> & B)
{
	bool done = false;
	int umcount = 0;
	while (!done)
	{
		if (A.empty()) // If A has already been finished, then all remaining in B are unmatched, and vice-versa
		{
			done = true;
		}
		if (B.empty())
		{
			umcount = umcount + A.size();
			done = true;
		}
		if (!done)
		{
			if ((A.front()) == (B.front())) // If front elements match, remove from a, count stays the same
			{
				A.erase(A.begin());
			}
			else if (A.front() < B.front()) // If no match, remove lower string, increase count if in A
			{
				A.erase(A.begin());
				umcount++;
			}
			else
			{
				B.erase(B.begin());
			}
		}
	}
	return umcount;
}


int
main()
{
	cout << "Find the most isolated number" << endl
		<< "-----------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for numbers: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct a sorted list of numbers
		Timer get;
		get.start();
		vector<double> numbers = getNums(n, -n, n);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (n < 10)
			cout << numbers << endl << endl;

		// Report a most isolated isolated number
		Timer time;
		time.start();
		double isolated = mostIsolated(numbers);
		time.stop();
		cout << "The most isolated number is "
			<< isolated << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}


	cout << endl << endl;
	cout << "Count the unmatched words" << endl
		<< "-------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for words lists: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter word length: ";
		int wordSize;
		cin >> wordSize;
		cout << "Enter alphabet: ";
		string alphabet;
		cin >> alphabet;

		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct two sorted vectors of words
		Timer get;
		get.start();
		list<string> A = getWords(n, wordSize, alphabet);
		list<string> B = getWords(n, wordSize, alphabet);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (wordSize * n < 60)
		{
			cout << "A is: " << A << endl
				<< "B is: " << B << endl;
		}

		// Report the number of words in the first sorted list
		//   that are not in the second sorted list
		Timer time;
		time.start();
		int count = unmatched(A, B);
		time.stop();
		cout << count
			<< " words in A were not in B" << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}

	return 0;
}
