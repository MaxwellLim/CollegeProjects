//
// Created by Maxwell Lim on 10/11/2019.
//

#include "addUpdateCommand.h"


addUpdateCommand::addUpdateCommand(phoneBook &bookIn, std::istream &inStream, std::ostream &outStream)
        :  bookCommand(inStream, outStream), book(bookIn)
    {
    }
    
void addUpdateCommand::execute()
    {
        std::string name,number,email;
        name=bookCommand::getInput("Enter name to add/update");
        number = bookCommand::getInput("Enter phone number");
        email=bookCommand::getInput("Enter e-mail address");
        if(book.find(name))
        {
            display("Updating phone book entry for "+name);
        }
        else
        {
            display("Adding phone book entry for " + name);
        }
        book.insert(name,number,email);
    }