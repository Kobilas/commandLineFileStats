#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int main(int argc, char *argv[])
{
    ifstream inFile;
    istringstream line;
    map<string, int> wordCount;
    map<int, vector<string>> byCount;
    char word[256];
    string sLine = "";
    int longestLine = 0;
    int longestWord = 0;
    int numLongestLines = 0;
    int numFiles = 0;
    int numLongestWord = 0;
    int length = 0;
    int subLength = 0;
    int size = 0;
    int q = 0;
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
                cout << argv[j] << " UNRECOGNIZED FLAG" << endl;
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
                longestWord = 0;
                while (getline(inFile, sLine))
                { //changes sLine
                    if (sLine == "")
                    {
                        continue;
                    }
                    length = sLine.length();
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
                    while (line.get(word, 256, ' '))
                    { //I fucking HATE you ozymandias
                      //go suck a FUCKING chode
                      //fucking asshole
                        if (bFlag)
                        {
                            while (strlen(word) == 0)
                            {
                                    subLength++;
                            }
                        }
                        if (strlen(word) == (unsigned)longestWord)
                        {
                            wordCount[word]++;
                        }
                        if ((unsigned)longestWord < strlen(word))
                        {
                            wordCount.erase(wordCount.begin(), wordCount.end());
                            wordCount[word]++;
                            longestWord = strlen(word);
                        }
                    }
                    if (bFlag)
                    {
                        subLength--;
                        longestLine -= subLength;
                    }
                }
                inFile.close();
            }
            else
            {
                cout << argv[i] << " FILE NOT FOUND" << endl;
                continue;
            }
        }
        else
        {
            continue;
        }
        cout << argv[i] << ":" << endl;
        if (mFlag)
        {
            byCount.erase(byCount.begin(), byCount.end());
            map<string, int>::iterator cit;
            for (cit = wordCount.begin(); cit != wordCount.end(); cit++)
            {
                //goes to the map index for the count of the word
                //then adds the word to the vector at that index
                byCount[cit->second].push_back(cit->first);
            }
            //gets the last key in the map which should be the highest occurring words
            map<int, vector<string>>::reverse_iterator sit = byCount.rbegin();
            //assigns the quantity of highest occurring words to numLongestWord
            numLongestWord = sit->first;
            //trims the vector at that key location
            byCount[numLongestWord].shrink_to_fit();
            //sorts the vector at that key location
            sort(byCount[numLongestWord].begin(), byCount[numLongestWord].end());
            vector<string>::iterator qit = byCount[numLongestWord].begin();
            size = byCount[numLongestWord].size();
            q = 0;
            while (qit != byCount[numLongestWord].end()) {
                if (q < size - 1)
                {
                    if (cFlag)
                    {
                        cout << *qit << " (" << numLongestWord << "), ";
                    }
                    else
                    {
                        cout << *qit << ", ";
                    }
                }
                else
                {
                    if (cFlag)
                    {
                        cout << *qit << " (" << numLongestWord << ")";
                    }
                    else
                    {
                        cout << *qit;
                    }
                }
                q++;
                qit++;
            }
        }
        else
        {
            map<string, int>::iterator it;
            q = 0;
            size = wordCount.size();
            for (it = wordCount.begin(); it != wordCount.end(); it++)
            {//sorted and comma-separated longest words
                if (q < size-1)
                {
                    cout << it->first << ", ";
                }
                else
                {
                    cout << it->first;
                }

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