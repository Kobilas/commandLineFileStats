#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
	ifstream inFile;
	istringstream line;
	map<string, int> wordCount;
	map<int, vector<string>> byCount;
	string word = "";
	string sLine = "";
	int longestLine = 0;
	int longestWord = 0;
	int numLongestLines = 0;
	int numFiles = 0;
	int numLongestWord = 0;
	int length = 0;
	bool mFlag = false;
	bool cFlag = false; //initialization of the
	bool bFlag = false; //possible flags
	bool xFlag = false;
	//a flag is an argument whose first character is a dash
	//so any file names or paths that start with a dash are
	//considered flags
	//therefore I do not have to check for the
	//case in which a directory or file's name starts with a -
	for (int j = 1; j < argc; j++)
	{
		if (argv[j][0] == '-')
		{
			switch (argv[j][1])
			{
			case 'm':
				mFlag = true;
				break;
			case 'c':
				cFlag = true;
				break;
			case 'b':
				bFlag = true;
				break;
				//if the flag is unrecognized
			default: //xFlag set to false, string printed
					 //then the loops break and return main
				xFlag = true;
				cout << argv[j] << " UNRECOGNIZED FLAG";
				break;
			}
		}
		else
		{
			numFiles++;
		}
		if (xFlag) //stops the main loop
		{
			break;
		}
	}
	if (xFlag) // returns main and terminates the program safely
	{
		return 0;
	}
	else if (numFiles == 0)
	{
		cout << "NO FILES" << endl;
		return 0;
	}
	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] != '-')
		{
			inFile.open(argv[i]);
			if (inFile.is_open())
			{
				while (getline(inFile, sLine))
				{
					length = inFile.gcount();
					line.str(sLine);
					if (length > longestLine)
					{
						longestLine = length;
						numLongestLines = 1;
					}
					else if (length == longestLine)
					{
						numLongestLines++;
					}
					while (line >> word)
					{
						if ((word.length()) == (unsigned)longestWord)
						{
							wordCount[word]++;
						}
						else if ((word.length()) > (unsigned)longestWord)
						{
							wordCount.erase(wordCount.begin(), wordCount.end());
							wordCount[word]++;
							longestWord = word.length();
						}

					}
				}
				inFile.close();
			}
			else
			{
				cout << argv[i] << " FILE NOT FOUND";
			}
		}
		else
		{
			continue;
		}
		cout << argv[i] << ":" << endl;
		if (cFlag)
		{
			for (map<string, int>::iterator cit = wordCount.begin();
				cit != wordCount.end(); cit++)
			{
				//goes to the map index for the count of the word
				//then adds the word to the vector at that index
				byCount[cit->second].push_back(cit->first);
			}
			//gets the last key in the map which should be the highest occurring words
			map<int, vector<string>>::reverse_iterator sit = byCount.rbegin();
			//assigns the quantity of highest occurring words to numLongestWord
			numLongestWord = sit->first;
			//sorts the vector at that key location
		}
		else
		{
			map<string, int>::iterator it;
			for (it = wordCount.begin(); it != wordCount.end(); it++)
			{//sorted and comma-separated longest words
				cout << it->first << ", ";
			}
		}
		cout << endl;
		cout << longestLine;
		if (cFlag)
		{
			cout << " (" << numLongestLines << ")";
		}
		cout << endl;
	}
}