//
// Created by Maxwell Lim on 10/11/2019.
//
#include <string>

#ifndef PHONEBOOKAPPLICATION_PHONEBOOKENTRY_H
#define PHONEBOOKAPPLICATION_PHONEBOOKENTRY_H


class phoneBookEntry
    {
        std::string thisname, number, emailAdress;
    public:
        //constructors
        phoneBookEntry();
        
        phoneBookEntry(const std::string &name, const std::string &number);
        
        phoneBookEntry(const std::string &name, const std::string &number, const std::string &email);
        
        phoneBookEntry(const phoneBookEntry &from);
        
        //member functions
        std::string name() const
            { return thisname; }
        
        std::string phoneNumber() const
            { return number; }
        
        std::string email() const
            { return emailAdress; }
        
        void phoneNumber(const std::string &newNumber)
            { number = newNumber; }
        
        void email(const std::string &newEmail)
            { emailAdress = newEmail; }
        bool operator==(const phoneBookEntry &entry) const
            { return this->name()==entry.name();}
        bool operator!=(const phoneBookEntry &entry) const
            { return this->name()!=entry.name();}
        bool operator<(const phoneBookEntry &entry) const
            { return this->name()<entry.name();}
        bool operator<=(const phoneBookEntry &entry) const
            { return this->name()<=entry.name();}
        bool operator>(const phoneBookEntry &entry) const
            { return this->name()>entry.name();}
        bool operator>=(const phoneBookEntry &entry) const
            { return this->name()>=entry.name();}
    };
std::ostream& operator<<(std::ostream &out, const phoneBookEntry &entry);


#endif //PHONEBOOKAPPLICATION_PHONEBOOKENTRY_H
