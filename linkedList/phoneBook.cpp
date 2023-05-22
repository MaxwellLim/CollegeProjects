//
// Created by Maxwell Lim on 10/11/2019.
//
#include <iostream>
#include <iomanip>
#include "phoneBook.h"

void phoneBook::insert(const phoneBookEntry &entry)
    {
        book.insert(entry);
    }

void phoneBook::insert(const std::string &name, const std::string &number, const std::string &email)
    {
        phoneBookEntry temp(name, number, email);
        insert(temp);
    }

void phoneBook::insert(const std::string &name, const std::string &number)
    {
        phoneBookEntry temp(name, number);
        insert(temp);
    }

bool phoneBook::erase(std::string name)
    {
        phoneBookEntry temp(name,"");
        return book.erase(temp);
    }

bool phoneBook::find(std::string name)
    {
        phoneBookEntry temp(name,"");
        return book.find(temp) != book.end();
    }

void phoneBook::print() const
    {
        std::cout << std::left << std::setw(31) << "Name:" << std::setw(16) << "Phone Number:" << "E-Mail:"
                  << std::endl;
        for (auto &entry:book)
            {
                std::cout << std::setw(31) << entry.name() << std::setw(16) << entry.phoneNumber()
                          << entry.email() << std::endl;
            }
        
    }

void phoneBook::print(std::ostream &out) const
    {
        out << std::left << std::setw(31) << "Name:" << std::setw(16) << "Phone Number:" << "E-Mail:" << std::endl;
        for (auto &entry:book)
            {
                out << std::setw(31) << entry.name() << std::setw(16) << entry.phoneNumber()
                    << entry.email() << std::endl;
            }
    }