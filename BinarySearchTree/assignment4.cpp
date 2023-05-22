#include <iostream>
#include <algorithm>
#include <cctype>
#include <fstream>
#include "binarySearchTree.h"
/*#include "word.h"

static void print(const word& thing)
    {
        if(thing.getWords().size()>1)
            {std::cout<<" maps to words: "<<std::endl;}
        else
            {std::cout<<" maps to word: "<<std::endl;}
        for(const auto& entry:thing.getWords())
            {
                std::cout<<entry<<" ";
            }
        std::cout<<std::endl;
    }
    
int main()
    {
        std::ifstream fileReader;
        binarySearchTree<word> dict;
        fileReader.open("english_words.txt");
        while(!fileReader.eof())
            {
                word temp;
                std::string input;
                std::string lower;
                
                std::string sorted;
                //gets dict word
                fileReader>>input;
                //folds to lowercase
                for(char x : input)
                    {lower.push_back(std::tolower(x));}
                sorted=lower;
                //sorts for key
                std::sort(sorted.begin(), sorted.end());
                temp.setKey(sorted);
                temp.addWords(lower);
                //inserts word
                dict.insert(temp);
            }
            
        std::cout<<"Test of find words"<<std::endl;
        std::cout<<std::endl;
        std::cout<<"The dictionary has been built with " <<dict.size()-1<< " keys in the dictionary"<<std::endl;
        
        std::cout<<"Word to unscramble (quit-now to stop):"<<std::endl;
        std::string currWord;
        std::cin>>currWord;
        while(currWord!="quit-now")
            {
                word temp;
                std::string sorted;
                std::string lower;
                //to lowercase
                for(char x : currWord)
                    {lower.push_back(std::tolower(x));}
                sorted=lower;
                //sorts key
                std::sort(sorted.begin(), sorted.end());
                temp.setKey(sorted);
                std::cout<<"Scrambled word "<<currWord;
                //searches and prints result
                if(!dict.find(temp,print))
                    {
                        std::cout<<" was not found"<<std::endl;
                    }
                    std::cout<<std::endl;
                std::cout<<"Word to unscramble (quit-now to stop):"<<std::endl;
                std::cin>>currWord;
            }
    }*/
int main()
    {}

