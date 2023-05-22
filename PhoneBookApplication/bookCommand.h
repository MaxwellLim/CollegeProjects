//
// Created by Maxwell Lim on 10/11/2019.
//

#ifndef PHONEBOOKAPPLICATION_BOOKCOMMAND_H
#define PHONEBOOKAPPLICATION_BOOKCOMMAND_H

#include <iostream>
#include "command.h"


class bookCommand : public command
    {
    protected:
        std::istream &in;
        std::ostream &out;
        
        //prints value
        void display(std::string value)
            { out << value << std::endl; }
        
        //prints prompt and gets response
        std::string getInput(std::string prompt);
    
    public:
        //constructor
        bookCommand(std::istream &in, std::ostream &out);
    };


#endif //PHONEBOOKAPPLICATION_BOOKCOMMAND_H
