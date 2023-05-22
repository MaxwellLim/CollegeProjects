//
// Created by Maxwell Lim on 10/11/2019.
//
#include <vector>
#include "phoneBookEntry.h"
#include "orderedLinkedList.h"

#ifndef LINKEDLIST_PHONEBOOK_H
#define LINKEDLIST_PHONEBOOK_H


class phoneBook
    {
        orderedLinkedList<phoneBookEntry> book;
        typedef std::vector<phoneBookEntry> phoneBookEntryList;
        typedef linkedListIterator<phoneBookEntry>		iterator;
        typedef const linkedListIterator<phoneBookEntry> const_iterator;
        
        
    public:
        phoneBook()
            = default;
        phoneBook(const phoneBook &other):book(other.book)
            {}
        //member functions
        void insert(const phoneBookEntry &entry);
        
        void insert(const std::string &name, const std::string &number, const std::string &email);
        
        void insert(const std::string &name, const std::string &number);
        
        bool erase(std::string name);
        
        bool find(std::string name);
        
        void print() const;
        
        void print(std::ostream &out) const;
        
        void debug(std::ostream &out) const
            { return print(out); }
        
        std::size_t size() const
            { return book.size(); }
        
        //iterators
        iterator begin()
            { return book.begin(); }
        
        iterator end()
            { return book.end(); }
    };


#endif //LINKEDLIST_PHONEBOOK_H
