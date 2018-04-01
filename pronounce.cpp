#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;

// Opens file
/*
ifstream openFile()
{
	ifstream dict("cmudict.0.7a");
	if (dict.fail())
	{
		cerr << "File cannot be opened for reading." << "\n";
		//exit if fail
		exit(1);
	}

	string junk;
	string comment;
	// Reading past most of file header
	while(junk != ";;;   - file name is major version; vers/rev information "
				  "is now in the header")
	{
		getline(dict,junk);
	}

	// Finishing reading past file header
	getline(dict,junk);
	getline(dict,junk);

	return dict;
}


// Checks if in dictionary
string inDict(string word)
{
	string test;
	ifstream dict("cmudict.0.7a");
	string junk;
	string comment;
	// Reading past most of file header
	while(junk != ";;;   - file name is major version; vers/rev information "
				  "is now in the header")
	{
		getline(dict,junk);
	}

	// Finishing reading past file header
	getline(dict,junk);
	getline(dict,junk);
	while(getline(dict,test))
	{
		if(test[0] == word[0])
		{
			test = test.substr(0,test.find(" "));
			if (!test.compare(word))
				return "";
		}
	}
	return "Not found";
}
*/
// Splits on space
// before and after are changed in the scope of the caller
void splitOnSpace(string s, string& before, string& after)
{
	// reset strings
	before = ""; 
	after = "";
	// accumulate before space
	int i = 0;
	while ((unsigned) i < s.size() && not isspace(s[i]))
	{
		before += s[i];
		i++; 
	}
	// skip the space
	i++;
	// accumulate after space
	while ((unsigned) i < s.size())
	{	
		after += s[i];
		i++;
	}
}

// Gets pronunciation as string
string getPronunciation(string word)
{
	string full;
	string match;
	ifstream dict("cmudict.0.7a");
	string junk;
	string comment;
	// Reading past most of file header
	while(junk != ";;;   - file name is major version; vers/rev information "
				  "is now in the header")
	{
		getline(dict,junk);
	}

	// Finishing reading past file header
	getline(dict,junk);
	getline(dict,junk);
	while(getline(dict,full))
	{
		if(full[0] == word[0])
		{
			if (!full.substr(0,full.find(" ")).compare(word))
			{
				match = full.substr(full.find(" "));
				// Leaves loop if match is found
				// Takes substring to avoid spaces
				return match.substr(2);
			}
		}
	}
	// Only used if no match is returned
	return "Error: word not found";
}

// Gets identical words as string
// Space separated
string getIdentical(string word, string pro)
{
	string full;
	string list = "";
	string match;
	ifstream dict("cmudict.0.7a");
	string junk;
	string comment;
	// Reading past most of file header
	while(junk != ";;;   - file name is major version; vers/rev information "
				  "is now in the header")
	{
		getline(dict,junk);
	}

	// Finishing reading past file header
	getline(dict,junk);
	getline(dict,junk);
	while(getline(dict,full))
	{
		// Optimizes, reducing checks for matches to 1/26th
		// All still need to be checked for first letter though
		if(full[0] == word[0])
		{

			if ((!full.substr(full.find(" ") + 2).compare(pro)) &&
				(full.substr(0,full.find(" ")).compare(word) != 0))
			{
				match = full.substr(0, full.find(" ") + 1);
				list += match;
			}
		}
	}
	return list;
}

// Gets words that can be obtained by adding a phoneme
// Space separated
string getAdd(string word, string pro)
{
	string full;
	string matchword;
	string matchpro;
	string addList;
	string proadd;
	string before;
	string after;
	string temp;
	string proArr[10];
	bool loop = true;
	int test = 0;
	int size = 0;
	ifstream dict("cmudict.0.7a");
	string junk;
	string comment;
	// Reading past most of file header
	while(junk != ";;;   - file name is major version; vers/rev information "
				  "is now in the header")
	{
		getline(dict,junk);
	}

	// Finishing reading past file header
	getline(dict,junk);
	getline(dict,junk);
	string pList[] = {"AA0","AA1","AA2","AE0","AE1","AE2","AH0","AH1","AH2","AO0","AO1","AO2",
					  "AW0","AW1","AW2","AY0","AY1","AY2","B","CH","D","DH","EH0","EH1","EH2",
					  "ER","EY0","EY1","EY2","F","G","HH","IH0","IH1","IH2","IY0","IY1","IY2",
					  "JH","K","L","M","N","NG","OW0","OW1","OW2","OY0","OY1","OY2","P","R",
					  "S","SH","T","TH","UH0","UH1","UH2","UW0","UW1","UW2","V","W","Y","Z","ZH"};
	while(getline(dict,full))
	{
		matchword = full.substr(0,full.find(" "));
		matchpro = full.substr(full.find(" ") + 2);

		// Fills proArr up to number of phonemes

		while(loop)
		{
			if (test == 0)
				splitOnSpace(pro,before,after);
			else
				splitOnSpace(temp,before,after);
			if (test == -1)
				loop = false;
			test = after.find(" ");
			proArr[size] = before;
			temp = after;
			size++;
		}
		// Looping through proArr
		for (int i = 0; i <= size; i++)
		{
			// Looping through pList
			for (int j = 0; j < 66; j++)
			{
				// Building proadd
				for (int k = 0; k <= size; k++)
				{
					if (k == size)
					{
						if (k == i)
							proadd += pList[j];
						proadd += proArr[k];

					}
					else
					{
						if (k == i)
							proadd += pList[j] + " ";
						proadd += proArr[k] + " ";
					}
				}
			if ((matchpro == proadd.substr(0,proadd.length() - 1)) && (matchword != word))
				addList += matchword + " ";
			else if ((proadd[proadd.length() - 1] == ' ') && (matchpro == proadd.substr(0,proadd.length() - 1)) && (matchword != word))
				addList += matchword + " ";
			else if (matchpro == proadd && matchword != word)
				addList += matchword + " ";
			proadd = "";
			}
		}

	}
	return addList;
}

// Gets words that can be obtained by removing a phoneme
// Space separated
string getRemove(string word, string pro)
{
	string full;
	string matchword;
	string matchpro;
	string before;
	string after;
	string removeList;
	string proRemove;
	string temp;
	string proArr[10];
	int test = 0;
	int size = 0;
	bool loop = true;
	ifstream dict("cmudict.0.7a");
	string junk;
	string comment;
	// Reading past most of file header
	while(junk != ";;;   - file name is major version; vers/rev information "
				  "is now in the header")
	{
		getline(dict,junk);
	}

	// Finishing reading past file header
	getline(dict,junk);
	getline(dict,junk);
	while(getline(dict,full))
	{
		matchword = full.substr(0,full.find(" "));
		matchpro = full.substr(full.find(" ") + 2);

		while(loop)
		{
			if (test == 0)
				splitOnSpace(pro,before,after);
			else
				splitOnSpace(temp,before,after);
			if (test == -1)
				loop = false;
			test = after.find(" ");
			proArr[size] = before;
			temp = after;
			size++;
		}

		// Now proArr should have the phonemes of pro as an array
		// Looping through proArr
		for(int i = 0; i < size; i++)
		{
			// Forming proRemove
			for(int j = 0; j < size; j++)
			{
				if (i == j)
					j++;
				if (j == size - 1)
					proRemove += proArr[j];
				else if (j != size - 1)
					proRemove += proArr[j] + " ";
			}
			if (matchpro == proRemove)
				removeList += matchword + " ";
			else if ((proRemove[proRemove.length() - 1] == ' ') && matchpro == proRemove.substr(0,proRemove.length() - 2))
				removeList += matchword + " ";
			proRemove = "";
		}
	}
	return removeList;
} 

// Gets words that can be obtained by replacing a phoneme
// Space separated
string getReplace(string word, string pro, string identical)
{
	string full;
	string matchword;
	string matchpro;
	string before;
	string after;
	string replaceList;
	string proReplace;
	string temp;
	string identArr[10];
	string proArr[10];
	string pList[] = {"AA0","AA1","AA2","AE0","AE1","AE2","AH0","AH1","AH2","AO0","AO1","AO2",
					  "AW0","AW1","AW2","AY0","AY1","AY2","B","CH","D","DH","EH0","EH1","EH2",
					  "ER","EY0","EY1","EY2","F","G","HH","IH0","IH1","IH2","IY0","IY1","IY2",
					  "JH","K","L","M","N","NG","OW0","OW1","OW2","OY0","OY1","OY2","P","R",
					  "S","SH","T","TH","UH0","UH1","UH2","UW0","UW1","UW2","V","W","Y","Z","ZH"};
	int test = 0;
	int size = 0;
	int size2 = 0;
	bool loop = true;
	bool repeat = false;
	ifstream dict("cmudict.0.7a");
	string junk;
	string comment;
	// Reading past most of file header
	while(junk != ";;;   - file name is major version; vers/rev information "
				  "is now in the header")
	{
		getline(dict,junk);
	}

	// Finishing reading past file header
	getline(dict,junk);
	getline(dict,junk);

	// Fills proArr up to number of phonemes

	while(loop)
	{
		if (test == 0)
			splitOnSpace(pro,before,after);
		else
			splitOnSpace(temp,before,after);
		if (test == -1)
			loop = false;
		test = after.find(" ");
		proArr[size] = before;
		temp = after;
		size++;
	}

	loop = true;
	test = 0;

	// Gets list of identical words
	// Used to exclude extras

	// Fills identArr up to number of identical words
	while(loop)
	{
		if (test == 0)
		{
			splitOnSpace(identical,before,after);
		}
		else
			splitOnSpace(temp,before,after);
		if (test == -1)
			loop = false;
		test = after.find(" ");
		identArr[size2] = before;
		temp = after;
		size2++;
	}

	while(getline(dict,full))
	{
		matchword = full.substr(0,full.find(" "));
		matchpro = full.substr(full.find(" ") + 2);

		// Now proArr should have the phonemes of pro as an array

		// Looping through proArr
		for(int i = 0; i < size; i++)
		{
			temp = proArr[i];
			// Looping through pList
			for(int j = 0; j < 66; j++)
			{
				proArr[i] = pList[j];
				for (int k = 0; k < size - 1; k++)
					proReplace += proArr[k] + " ";
				proReplace += proArr[size - 1];
				if ((matchpro == proReplace) && (matchword != word))
				{
					// Checking for repeat
					for (int l = 0; l < 10; l++)
					{
						if (matchword == identArr[l])
							repeat = true;
					}
					if (!repeat)
						replaceList += matchword + " ";
				}
				else if ((proReplace[proReplace.length() - 1] == ' ') && (matchpro == proReplace.substr(0,proReplace.length() - 2)) && (matchword != word))
				{
					// Checking for repeat
					for (int l = 0; l < 10; l++)
					{
						if (matchword == identArr[l])
							repeat = true;
					}
					if (!repeat)
						replaceList += matchword + " ";
				}
				if (repeat)
					repeat = false;
				proReplace = "";
			}
			proArr[i] = temp;
		}
	}
	return replaceList;
} 
/*
// Prints string with pronunciation of word
string pronounce(string word)
{
	ifstream dict("cmudict.0.7a");
	string junk;
	string comment;
	// Reading past most of file header
	while(junk != ";;;   - file name is major version; vers/rev information "
				  "is now in the header")
	{
		getline(dict,junk);
	}

	// Finishing reading past file header
	getline(dict,junk);
	getline(dict,junk);

	if (!inDict(word))
	{
		return "Not found";
	}

	// Resetting dict

	dict.close();
	dict.open("cmudict.0.7a");

	return getPronunciation(word);

}

// Prints string of words with identical pronunciation to word
void identical(string word, string pro)
{

	ifstream dict("cmudict.0.7a");
	string junk;
	string comment;
	// Removed some things to speed it up
	// Reading past most of file header
	while(junk != ";;;   - file name is major version; vers/rev information "
				  "is now in the header")
	{
		getline(dict,junk);
	}

	// Finishing reading past file header
	getline(dict,junk);
	getline(dict,junk);

	cout << "Identical	: " << getIdentical(word,pro) << "\n";

}

// Prints string of words obtained by adding phoneme to word
void add(string word, string pro)
{
	ifstream dict("cmudict.0.7a");
	string junk;
	string comment;
	// Removed some things to speed it up
	// Reading past most of file header
	while(junk != ";;;   - file name is major version; vers/rev information "
				  "is now in the header")
	{
		getline(dict,junk);
	}

	// Finishing reading past file header
	getline(dict,junk);
	getline(dict,junk);

	cout << "Add phoneme	: " << getAdd(word,pro) << "\n";
}

// Prints string of words obtained by removing a phoneme from word
void remove(string word, string pro)
{
	ifstream dict("cmudict.0.7a");
	string junk;
	string comment;
	// Removed some things to speed it up
	// Reading past most of file header
	while(junk != ";;;   - file name is major version; vers/rev information "
				  "is now in the header")
	{
		getline(dict,junk);
	}

	// Finishing reading past file header
	getline(dict,junk);
	getline(dict,junk);

	cout << "Remove phoneme	: " << getRemove(word,pro) << "\n";
}

// Prints string of words obtained by replacing a phoneme in word
void replace(string word, string pro)
{
	ifstream dict("cmudict.0.7a");
	string junk;
	string comment;
	// Reading past most of file header
	// Removed some things to speed it up
	while(junk != ";;;   - file name is major version; vers/rev information "
				  "is now in the header")
	{
		getline(dict,junk);
	}

	// Finishing reading past file header
	getline(dict,junk);
	getline(dict,junk);

	cout << "Replace phoneme	: " << getReplace(word,pro) << "\n";
}
*/
// Main function
int main()
{
	string word;
	string pro;
	string ident;

	cout << "Input a word: ";
	// Waits for word input
	word = "plants";

	// Basically word = word.upper()
	for (int i = 0; (unsigned) i < word.length(); ++i)
		if ((word[i] >= 'a') && (word[i] <= 'z'))
			word[i] = (char) ((int) word[i] - 32);

	// Calls functions to print information about word
	pro = getPronunciation(word);
	cout << "Pronunciation	: " << pro << "\n";
	ident = getIdentical(word, pro);
	cout << "Identical	: " << ident << "\n";
	cout << "Add phoneme	: " << getAdd(word, pro) << "\n";
	cout << "Remove phoneme	: " << getRemove(word, pro) << "\n";
	cout << "Replace phoneme	: " << getReplace(word, pro, ident) << "\n";

	return 0;
}
