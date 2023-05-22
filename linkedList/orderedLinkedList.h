//
// Created by Maxwell Lim on 11/3/2019.
//

#ifndef LINKEDLIST_ORDEREDLINKEDLIST_H
#define LINKEDLIST_ORDEREDLINKEDLIST_H

#include <cstddef>

#include "linkedList.h"

template<class DataType>
class orderedLinkedList
    {
    public:
        typedef linkedList<DataType>              unorderedLinkedList;
        typedef std::bidirectional_iterator_tag	iterator_category;
        typedef std::ptrdiff_t 					      difference_type;
        typedef std::size_t						      size_type;
        typedef typename unorderedLinkedList::iterator  iterator;
        typedef const iterator	  	               const_iterator;
    private:
        // we are making use of the DoubleLinkedList class
        unorderedLinkedList list;
    public:
        // default constructor
        orderedLinkedList()
        = default;
        // copy constructor
        orderedLinkedList(const orderedLinkedList &other):list(other.list)
            {}
        // assignment operator
        const orderedLinkedList& operator=(const orderedLinkedList &other)
            {
                list=other.list;
            }
        // destructor
        virtual ~orderedLinkedList()
            {
                while(list.size()!=0)
                    {
                        list.pop_front();
                    }
            }
        // iterators
        iterator begin()
            {
                return list.begin();
            }
        
        iterator end()
            {
                return list.end();
            }
        
        const_iterator begin() const
            {
                return list.begin();
            }
        
        const_iterator end() const
            {
                return list.end();
            }
        
        // number of items in the list
        virtual std::size_t size() const
            { return list.size();}
        // is the list empty (true) or does it have entries (false)
        virtual bool empty() const
            { return list.empty();}
        // print the items in the list
        virtual void print() const
            { return list.print();}
        // display the contents of the list to the ostream&
        virtual void print(std::ostream &out) const
            { return list.print(out);}
        // display debug information on the passed in ostream
        virtual void debug(std::ostream &out) const
            {return list.debug(out);}
        // find the element and return an interator for it
        virtual iterator find(const DataType &existingItem)
            {return list.find(existingItem);}
        // remove the node equal to currentItem
        virtual bool erase(const DataType &currentItem)
            { return list.erase(currentItem);}
        // remove the node by address existingNode
        virtual iterator erase(iterator iter)
            { return list.erase(iter);}
        // insert the new item into the list (in sorted order)
        // a duplicate entry will be ignored
        virtual void insert(const DataType &newItem);
        // get the last entry
        iterator back()
            {
                return list.back();
            }
        
        const_iterator back() const
            {
                return list.back();
            }
    };

// Your implementation code goes here
template<class DataType>
void orderedLinkedList<DataType>::insert(const DataType &newItem)
    {
        if(list.find(newItem)!=list.end())
            {
                return;
            }
        for(auto run  = begin(); run != nullptr; run++)
            {
                if(*run>newItem)
                    {
                        list.insert_before(run,newItem);
                        return;
                    }
            }
            list.push_back(newItem);
    }

#endif //LINKEDLIST_ORDEREDLINKEDLIST_H
