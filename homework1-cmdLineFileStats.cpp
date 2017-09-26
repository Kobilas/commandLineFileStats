#include <iostream>
#include <fstream>
#include <istringstream>
#include <string>
#include <map>
#include <vector>

int main(int argc, char *argv[])
{
	ifstream inFile;
	istringstream line;
	std::map<string, int> wordCount;
	std::map<int, vector<string>> byCount;
	std::string word = "";
	int longestLine = 0;
	int longestWord = 0;
	int numLongestLines = 0;
	int numFiles = 0;
	int numLongestWord = 0;
	bool mFlag = false;
	bool cFlag = false; //initialization of the
	bool bFlag = false; //possible flags
	bool xFlag = false;
	//a flag is an argument whose first character is a dash
	//so any file names or paths that start with a dash are
	//considered flags
	//therefore I do not have to check for the
	//case in which a directory or file's name starts with a -
	for (int j = 0; j < argc; j++)
	{
		if (argv[i][0] == '-')
		{
			switch (argv[i][1])
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
				std::cout << argv[i] << " UNRECOGNIZED FLAG";
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
		if (numFiles == 0) //also stops the main loop
		{
			std::cout << "NO FILES" << endl;
			break;
		}
	}
	if (xFlag || (numFiles == 0)) // returns main and terminates the program safely
	{
		return;
	}
	for(int i = 0; i < argc; i++)
	{
		if(argv[i][0] != '-')
		{
			inFile.open(argv[i]);
			if(inFile.is_open())
			{
				while(inFile.getline())
				{
					line = "";
					inFile.seekg(inFile.tellg() - inFile.gcount());
					line(inFile.getline());
					if(line.length() > longestLine)
					{
						longestLine = line.length();
						numLongestLines = 1;
					}
					else if(line.length() == longestLine)
					{
						numLongestLines++;
					}
					while(line >> word)
					{
						if(word.length() == longestWord)
						{
							wordCount[word]++;
						}
						else if(word.length() > longestWord)
						{
							wordCount.erase();
							wordCount[word]++;
							longestWord = word.length();
						}

					}
				}
				inFile.close();
			}
			else
			{
				std::cout << argv[i] << " FILE NOT FOUND";
			}
		}
		else
		{
			continue;
		}
		std::cout << argv[i] << ":" << endl;
		if(cFlag)
		{
			for (std::map<string, int>::iterator cit = wordCount.begin();
				cit != wordCount.end(); cit++)
			{
				//goes to the map index for the count of the word
				//then adds the word to the vector at that index
				byCount[cit->second].push_back(it->first);
			}
			//gets the last key in the map which should be the highest occurring words
			std::map<int, vector<string>>::iterator sit = byCount.rbegin();
			//assigns the quantity of highest occurring words to numLongestWord
			numLongestWord = sit->first;
			//sorts the vector at that key location
			byCount[numLongestWord]
		}
		else
		{
			std::map<string, int>::iterator it;
			for (it = wordCount.begin(); it != wordCount.end(); it++)
			{//sorted and comma-separated longest words
				std::cout << it->first << ", ";
			}
		}
		std::cout << endl;
		std::cout << longestline;
		if(cFlag)
		{
			std::cout << " (" << numLongestLines << ")";
		}
		std::cout << endl;
	}
}