/*
 * assignment1.cpp
 *
 * <add comments to describe the purpose of this application>
 *
 */

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <cctype>

using namespace std;

enum direction
    {
        LEFT_RIGHT, RIGHT_LEFT, DOWN, UP, RIGHT_DOWN, RIGHT_UP, LEFT_DOWN, LEFT_UP
    };

const int MAX = 50;

struct wordGame
    {
        //variables
        int numberRows;
        int numberColumns;
        char puzzle[MAX][MAX];
        int version = 2;
        
        //member functions
        int getRows()
            { return numberRows; }
        
        int getColumns()
            { return numberColumns; }
        
        void setRows(int rows)
            { numberRows = rows; }
        
        void setColumns(int columns)
            { numberColumns = columns; }
        
        void putLetter(int row, int column, char letter)
            { puzzle[row][column] = letter; }
        
        char getLetter(int row, int column)
            { return puzzle[row][column]; }
        
        
    };

struct wordFind
    {
        //variables
        string word;
        bool found;
        int row;
        int column;
        int foundcount;
        direction where;
        
        //member functions
        void setWord(string word)
            { this->word = word; }
        
        string getWord()
            { return word; }
        
        int getRow()
            { return row; }
        
        int getColumn()
            { return column; }
        
        void setRow(int row)
            { this->row = row; }
        
        void setColumn(int column)
            { this->column = column; }
        
        bool getFound()
            { return found; }
        
        int getFoundCount()
            { return foundcount; }
        
        void setFound(bool found)
            { this->found = found; }
        
        void setFoundCount(int foundcount)
            { this->foundcount = foundcount; }
        
        
    };

// function prototypes go here
// find the word that is part of the wordFind structure inside the wordGame structure.
// If the word is found the wordFind structure will be updated.
void findWord(wordGame &game, wordFind &theFind);

// read the puzzle from the input file and update the wordGame structure.
bool readPuzzle(wordGame &game, string inputFileName);

// display the contents of the puzzle
void displayPuzzle(wordGame &game);

// find the word that is part of the wordFind structure inside the wordGame structure.
// If the word is found the wordFind structure will be updated.
void findWord(wordGame &game, wordFind &theFind)
    {
        string search;
        bool found = false;
        int numfound = 0;
        //searches left to right
        for (int row = 0; row < game.getRows(); row++)
            {
                search = "";
                for (int column = 0; column < game.getColumns(); column++)
                    {
                        search.push_back(game.getLetter(row, column));
                    }
                if (search.find(theFind.getWord()) != string::npos)
                    {
                        theFind.setColumn(search.find(theFind.getWord()));
                        theFind.setRow(row);
                        theFind.where = LEFT_RIGHT;
                        found = true;
                        numfound++;
                    }
                search.clear();
            }
        //searches right to left
        for (int row = 0; row < game.getRows(); row++)
            {
                search = "";
                for (int column = game.getColumns() - 1; column >= 0; column--)
                    {
                        search.push_back(game.getLetter(row, column));
                        
                    }
                if (search.find(theFind.getWord()) != string::npos)
                    {
                        theFind.setColumn(game.getColumns() - 1 - search.find(theFind.getWord()));
                        theFind.setRow(row);
                        theFind.where = RIGHT_LEFT;
                        found = true;
                        numfound++;
                    }
                search.clear();
            }
        //searches down
        for (int column = 0; column < game.getColumns(); column++)
            {
                search = "";
                for (int row = 0; row < game.getRows(); row++)
                    {
                        search.push_back(game.getLetter(row, column));
                    }
                if (search.find(theFind.getWord()) != string::npos)
                    {
                        theFind.setRow(search.find(theFind.getWord()));
                        theFind.setColumn(column);
                        
                        theFind.where = DOWN;
                        found = true;
                        numfound++;
                    }
                search.clear();
            }
        //searches up
        for (int column = 0; column < game.getColumns(); column++)
            {
                search = "";
                for (int row = game.getRows() - 1; row >= 0; row--)
                    {
                        search.push_back(game.getLetter(row, column));
                    }
                if (search.find(theFind.getWord()) != string::npos)
                    {
                        theFind.setColumn(column);
                        theFind.setRow(game.getRows() - 1 - search.find(theFind.getWord()));
                        theFind.where = UP;
                        found = true;
                        numfound++;
                    }
                search.clear();
            }
        //searches right down
        for (int column = 0; column < game.getColumns(); column++)
            {
                search = "";
                for (int diag = 0; diag + column < game.getColumns() || diag < game.getRows(); diag++)
                    {
                        search.push_back(game.getLetter(diag, column + diag));
                        
                    }
                if (search.find(theFind.getWord()) != string::npos)
                    {
                        theFind.setRow(search.find(theFind.getWord()));
                        theFind.setColumn(column + search.find(theFind.getWord()));
                        theFind.where = RIGHT_DOWN;
                        found = true;
                        numfound++;
                    }
                search.clear();
            }
        for (int row = 0; row < game.getRows(); row++)
            {
                search = "";
                for (int diag = 0; diag + row < game.getRows() || diag < game.getColumns(); diag++)
                    {
                        search.push_back(game.getLetter(row + diag, diag));
                    }
                if (search.find(theFind.getWord()) != string::npos)
                    {
                        theFind.setRow(row + search.find(theFind.getWord()));
                        theFind.setColumn(search.find(theFind.getWord()));
                        theFind.where = RIGHT_DOWN;
                        found = true;
                        numfound++;
                    }
                search.clear();
            }
//searches right up
        for (int column = 0; column < game.getColumns(); column++)
            {
                search = "";
                for (int diag = 0; diag + column < game.getColumns() || diag < game.getRows(); diag++)
                    {
                        search.push_back(game.getLetter(game.getRows() - diag - 1, column + diag));
                    }
                if (search.find(theFind.getWord()) != string::npos)
                    {
                        
                        theFind.setRow(game.getRows() - 1 - search.find(theFind.getWord()));
                        theFind.setColumn(column + search.find(theFind.getWord()));
                        
                        theFind.where = RIGHT_UP;
                        found = true;
                        numfound++;
                    }
                search.clear();
            }
        for (int row = game.getRows() - 1; row >= 0; row--)
            {
                search = "";
                for (int diag = 0; row - diag >= 0 || diag < game.getColumns(); diag++)
                    {
                        search.push_back(game.getLetter(row - diag, diag));
                    }
                if (search.find(theFind.getWord()) != string::npos)
                    {
                        theFind.setColumn(search.find(theFind.getWord()));
                        theFind.setRow(row - search.find(theFind.getWord()));
                        theFind.where = RIGHT_UP;
                        found = true;
                        numfound++;
                    }
                search.clear();
            }
        //searches left down
        for (int column = game.getColumns() - 1; column >= 0; column--)
            {
                search = "";
                for (int diag = 0; diag + column < game.getColumns() || diag < game.getRows(); diag++)
                    {
                        search.push_back(game.getLetter(diag, column - diag));
                    }
                if (search.find(theFind.getWord()) != string::npos)
                    {
                        theFind.setRow(search.find(theFind.getWord()));
                        theFind.setColumn(column - search.find(theFind.getWord()));
                        theFind.where = LEFT_DOWN;
                        found = true;
                        numfound++;
                    }
                search.clear();
            }
        for (int row = 0; row < game.getRows(); row++)
            {
                search = "";
                for (int diag = 0; diag + row < game.getRows() || diag < game.getColumns(); diag++)
                    {
                        search.push_back(game.getLetter(row + diag, game.getColumns() - diag - 1));
                    }
                if (search.find(theFind.getWord()) != string::npos)
                    {
                        theFind.setRow(row + search.find(theFind.getWord()));
                        theFind.setColumn(game.getColumns() - 1 - search.find(theFind.getWord()));
                        theFind.where = LEFT_DOWN;
                        found = true;
                        numfound++;
                    }
                search.clear();
            }
        //searches left up
        for (int column = game.getColumns() - 1; column >= 0; column--)
            {
                search = "";
                for (int diag = 0; diag + column < game.getColumns() || diag < game.getRows(); diag++)
                    {
                        search.push_back(game.getLetter(game.getRows() - diag - 1, column - diag));
                    }
                if (search.find(theFind.getWord()) != string::npos)
                    {
                        theFind.setRow(game.getRows() - search.find(theFind.getWord()) - 1);
                        theFind.setColumn(column - search.find(theFind.getWord()));
                        theFind.where = LEFT_UP;
                        found = true;
                        numfound++;
                    }
                search.clear();
            }
        for (int row = game.getRows() - 1; row >= 0; row--)
            {
                search = "";
                for (int diag = 0; row - diag >= 0 || diag < game.getColumns(); diag++)
                    {
                        search.push_back(game.getLetter(row - diag, game.getColumns() - diag - 1));
                    }
                if (search.find(theFind.getWord()) != string::npos)
                    {
                        theFind.setRow(row - search.find(theFind.getWord()));
                        theFind.setColumn(game.getColumns() - search.find(theFind.getWord()) - 1);
                        theFind.where = LEFT_UP;
                        found = true;
                        numfound++;
                    }
                search.clear();
            }
        theFind.setFound(found);
        theFind.setFoundCount(numfound);
    }

// read the puzzle from the input file and update the wordGame structure.
bool readPuzzle(wordGame &game, string inputFileName)
    {
        ifstream fileReader;
        int tempVal;
        //opens file and checks validity of file
        fileReader.open(inputFileName);
        if (!fileReader.is_open())
            {
                return false;
            }
        //gets number of rows and columns
        fileReader >> tempVal;
        game.setRows(tempVal);
        fileReader >> tempVal;
        game.setColumns(tempVal);
        if ((game.getRows() > MAX) || (game.getColumns() > MAX) || game.getRows() < 1 || game.getColumns() < 1)
            {
                return false;
            }
        string charRow;
        for (int row = 0; row < game.getRows(); row++)
            {
                
                fileReader >> charRow;
                if (fileReader.eof())
                    {
                        return false;
                    }
                if (charRow.length() < game.getColumns())
                    {
                        return false;
                    }
                for (int column = 0; column < game.getColumns(); column++)
                    {
                        game.putLetter(row, column, toupper(charRow[column]));
                    }
            }
        fileReader.close();
        return true;
    }

// display the contents of the puzzle
void displayPuzzle(wordGame &game)
    {
        for (int row = 0; row < game.getRows(); row++)
            {
                for (int column = 0; column < game.getColumns(); column++)
                    {
                        cout << game.getLetter(row, column);
                    }
                cout << endl;
            }
    }


int main()
    {
        //variables
        ifstream puzzleReader;
        string puzzleFile;
        string wordsFile;
        string word;
        wordFind finder;
        wordGame puzzle;
        
        
        //reading file names
        cin >> puzzleFile;
        cin >> wordsFile;
        
        //opens puzzle and checks if its exists
        bool puzzFile = readPuzzle(puzzle, puzzleFile);
        if (!puzzFile)
            {
                cout << "The puzzle file \"" << puzzleFile << "\" could not be opened or is invalid" << endl;
                return 1; // 1 indicates error
            }
        cout << "The puzzle from file \"" << puzzleFile << "\"" << endl;
        displayPuzzle(puzzle);
        //opens words file and checks existence
        puzzleReader.open(wordsFile);
        if (!puzzleReader.is_open())
            {
                cout << "The puzzle file \"" << wordsFile << "\" could not be opened or is invalid" << endl;
                return 1; // 1 indicates error
            }
        
        
        //loops through words, finds and prints location
        while (puzzleReader >> word)
            {
                transform(word.begin(), word.end(), word.begin(), ::toupper);
                finder.setWord(word);
                findWord(puzzle, finder);
                if (finder.getFound())
                    {
                        cout << "The word " << word << " was found ";
                        if (finder.getFoundCount() > 2)
                            {
                                cout << finder.getFoundCount() << " times" << endl;
                            }
                        else
                            {
                                cout << "at (" << finder.getRow() + 1 << ", " << finder.getColumn() + 1 << ") - ";
                                switch (finder.where)
                                    {
                                        case LEFT_RIGHT:
                                            cout << "right" << endl;
                                        break;
                                        case RIGHT_LEFT:
                                            cout << "left" << endl;
                                        break;
                                        case DOWN:
                                            cout << "down" << endl;
                                        break;
                                        case UP:
                                            cout << "up" << endl;
                                        break;
                                        case LEFT_DOWN:
                                            cout << "left/down" << endl;
                                        break;
                                        case LEFT_UP:
                                            cout << "left/up" << endl;
                                        break;
                                        case RIGHT_DOWN:
                                            cout << "right/down" << endl;
                                        break;
                                        case RIGHT_UP:
                                            cout << "right/up" << endl;
                                        break;
                                    }
                                
                            }
                    }
                else
                    {
                        cout << "The word " << word << " was not found" << endl;
                    }
                
            }
            puzzleReader.close();
        
        return 0;
    }