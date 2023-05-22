//
// Created by Maxwell Lim on 10/11/2019.
//

#include "bookCommand.h"

bookCommand::bookCommand(std::istream &inStream, std::ostream &outStream)
        : in(inStream), out(outStream)
    {
    }

std::string bookCommand::getInput(std::string prompt)
    {
        out << prompt << std::endl;
        std::string input;
        getline(in, input);
        return input;
    }