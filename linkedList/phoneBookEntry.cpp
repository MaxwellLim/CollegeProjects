//
// Created by Maxwell Lim on 10/11/2019.
//

#include "phoneBookEntry.h"

phoneBookEntry::phoneBookEntry()
    {
        thisname = "";
        number = "";
        emailAdress = "";
    }

phoneBookEntry::phoneBookEntry(const std::string &name, const std::string &number)
    {
        thisname = name;
        this->number = number;
        emailAdress = "";
    }

phoneBookEntry::phoneBookEntry(const std::string &name, const std::string &number, const std::string &email)
    {
        thisname = name;
        this->number = number;
        emailAdress = email;
    }

phoneBookEntry::phoneBookEntry(const phoneBookEntry &from)
    {
        thisname = from.name();
        number = from.phoneNumber();
        emailAdress = from.email();
    }

std::ostream& operator<<(std::ostream &out, const phoneBookEntry &entry)
    {
        out<<entry.name();
        std::string comma=", ";
        if(!entry.phoneNumber().empty())
            {
                out<<comma<<entry.phoneNumber();
            }
        if(!entry.email().empty())
            {
                out<<comma<<entry.email();
            }
        return out;
    }