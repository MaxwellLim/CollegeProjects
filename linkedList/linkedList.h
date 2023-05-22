//
// Created by Maxwell Lim on 10/30/2019.
//

#ifndef LINKEDLIST_LINKEDLIST_H
#define LINKEDLIST_LINKEDLIST_H
/*
 * linkedList.h
 *
 * Implementation of a double linked list.
 *
 * We have the ability to get the first and last entries and navigate
 * through the entries in the linked list.
 *
 * There are actually three classes here:
 *
 * listNode<DataType>
 *
 * listNodeIterator<DataType>
 
 * and
 *
 * linkedList<DataType>
 *
 * The listNodeIterator is the iterator for the new linked list class.
 *
 */

//#include "memoryLeak.h"
#include <cassert>
#include <iostream>
#include <iomanip>
#include <cstddef>
#include <iterator>

// forward declaration of the template class linkedList
template<class DataType>
class linkedList;
// forward declaration of iterator
template<class DataType>
class linkedListIterator;

// listNode class
template<class DataType>
class listNode
    {
        // make DoubleLinkedList<DataType> a friend class
        friend class linkedList<DataType>;
        friend class linkedListIterator<DataType>;
    private:
        // contains the actual data
        DataType dataType;
        // pointer to the next item in the list or nullptr
        // if at the end
        listNode<DataType>* pNext;
        // pointer to the previous item in the list or nullptr
        // if at the start
        listNode<DataType>* pPrevious;
    public:
        // default constructor
        listNode();
        // constructor with data
        listNode(const DataType &newItem);
    protected:
        // get the next node
        listNode* next() const
            {
                return pNext;
            }
        
        // get the previous node
        listNode* previous() const
            {
                return pPrevious;
            }
        
        // return the data stored in the node as a const
        const DataType& data() const
            {
                return dataType;
            }
        // return the data stored in the node
        DataType& data()
            {
                return dataType;
            }
        // update the next node
        void next(listNode *nextNode)
            {
                pNext = nextNode;
            }
        // update the previous node
        void previous(listNode *previousNode)
            {
                pPrevious = previousNode;
            }
    };

// the linkedListIterator is the iterator for class linkedList.
//
// most of this code has been provided for you.
// the exceptions are the operator--() operator--(int) member fuctions and
// and the operator== and operator!= member functions.
template<class DataType>
class linkedListIterator
    {
        typedef DataType 								   value_type;
        typedef DataType& 								reference;
        typedef const DataType& 						const_reference;
        typedef DataType* 								pointer;
        typedef const DataType* 						const_pointer;
        typedef std::bidirectional_iterator_tag	iterator_category;
        typedef std::ptrdiff_t 							difference_type;
        typedef std::size_t								size_type;
        typedef linkedListIterator						iterator;
        typedef const linkedListIterator	  			const_iterator;
        
        friend class linkedList<DataType>;
    private:
        listNode<DataType> *current;
    public:
        linkedListIterator(listNode<DataType> *current)
                : current(current)
            {
            }
        
        virtual ~linkedListIterator()
            {
            }
        
        reference operator*()
            {
                assert(current != nullptr);
                return current->data();
            }
        
        const_reference operator*() const
            {
                assert(current != nullptr);
                return current->data();
            }
        
        pointer operator->()
            {
                assert(current != nullptr);
                return &(current->data());
            }
        
        const_pointer operator->() const
            {
                assert(current != nullptr);
                return &(current->data());
            }
        
        iterator operator++()
            {
                if (current != nullptr)
                    {
                        current = current->next();
                    }
                return *this;
            }
        
        iterator operator++(int)
            {
                iterator it = *this;
                if (current != nullptr)
                    {
                        current = current->next();
                    }
                return it;
            }
        
        // you need to implement the following - they can be inlined if you want
        iterator operator--()
            {
                if (current != nullptr)
                    {
                        current = current->previous();
                    }
                return *this;
            }
        
        iterator operator--(int)
            {
                iterator it = *this;
                if (current != nullptr)
                    {
                        current = current->previous();
                    }
                return it;
            }
        bool operator==(const_iterator &other) const
            {return other.current==current;}
        bool operator!=(const_iterator &other) const
            {return other.current!=current;}
        
    };

// linkedList class
template<class DataType>
class linkedList
    {
    public:
        typedef DataType 								   value_type;
        typedef DataType& 								reference;
        typedef const DataType& 						const_reference;
        typedef DataType* 								pointer;
        typedef const DataType* 						const_pointer;
        typedef std::bidirectional_iterator_tag	iterator_category;
        typedef std::ptrdiff_t 							difference_type;
        typedef std::size_t								size_type;
        typedef linkedListIterator<DataType>		iterator;
        typedef const linkedListIterator<DataType> const_iterator;
    
    private:
        // your instance data goes here. Things like the pointers to the first and last nodes
        //  as well as the count of nodes
        listNode<DataType>* firstNode;
        listNode<DataType>* lastNode;
        int count;
    public:
        // default constructor
        linkedList();
        // copy constructor
        linkedList(const linkedList &other)
        {
            move(other);
        }
        // assignment operator
        const linkedList& operator=(const linkedList &other)
            {
                move(other);
                return *this;
            }
        // destructor
        virtual ~linkedList()
            {
                while(count!=0)
                    {
                        pop_front();
                    }
            }
        // return the number of nodes in the list
        std::size_t size() const
            { return count;}
        // return true if the list is empty
        bool empty() const
            {return count==0;}
        // display the contents of the list to std::cout
        void print() const
            {
                print(std::cout);
            }
        // display the contents of the list to the ostream&
        void print(std::ostream &out) const;
        
        // iterators
        iterator begin()
            {
                return firstNode;
            }
        
        const_iterator begin() const
            {
                return firstNode;
            }
        
        iterator end()
            {
                return lastNode;
            }
        
        const_iterator end() const
            {
                return lastNode;
            }
        
        // dump the contends in debug format to passed in
        // ostream - usage to cout would be:
        //   list.debug(std::cout);
        void debug(std::ostream &out) const;
    public:
        // add an item to the front of the list
        virtual void push_front(const DataType &newItem);
        // add an item to the back of the list
        virtual void push_back(const DataType &newItem);
        // remove an item from the front of the list
        virtual void pop_front();
        // remove an item from the back of the list
        virtual void pop_back();
        // insert newItem before the node specified by the iterator
        virtual void insert_before (iterator iter, const DataType &newItem);
        // insert newItem after the node specified by the iterator
        virtual void insert_after (iterator iter, const DataType &newItem);
        // find the node and return the iterator for that element.
        // Return end() if not found
        virtual iterator find(const DataType &existingItem);
        // remove the node equal to currentItem
        virtual bool erase(const DataType &currentItem);
        // remove the node by address existingNode
        virtual iterator erase(iterator iter);
        // return the iterator for the last node
        virtual iterator back()
            {
                return linkedListIterator<DataType>(lastNode);
            }
        virtual const_iterator back() const
            {
                return linkedListIterator<DataType>(lastNode);
            }
    protected:
    private:
        // any helper functions you need should eithee be protected or private
        void move(const linkedList &other);
    };

// the constructors for the listNode class are included here
// default constructor
template <class DataType>
listNode<DataType>::listNode()
        : dataType(), pNext(nullptr), pPrevious(nullptr)
    {
    }

// constructor with data
template <class DataType>
listNode<DataType>::listNode(const DataType &newItem)
        : dataType(newItem), pNext(nullptr), pPrevious(nullptr)
    {
    }

// note the code for the debug() function is included
// display a debug version of the list
template<class DataType>
void linkedList<DataType>::debug(std::ostream &out) const
    {
        const unsigned int ADDRWIDTH = 10;
        out << "START DEBUG" << std::endl;
        out << "first  =" << std::setw(ADDRWIDTH) << firstNode;
        out << ", last=" << std::setw(ADDRWIDTH) << lastNode;
        out << ", # nodes=" << size() << std::endl;
        unsigned int count = 1;
        
        for (auto current=firstNode; current!= nullptr; current++)
            {
                if(count>size())
                    {break;}
                out << "node " << std::setw(2) << count;
                out << "=" << std::setw(ADDRWIDTH) << current;
                out << ", next=" << std::setw(ADDRWIDTH)
                    << current->next();
                out << ", previous=" << std::setw(ADDRWIDTH)
                    << current->previous();
                out << ", value=" << current->data() << std::endl;
                count++;
            }
        out << "END DEBUG" << std::endl;
    }

// I have included a few function headers and bodies here where the syntax is odd
// Your implementation of non-inlined member funcctions needs to go there.
// default constructor
template<class DataType>
linkedList<DataType>::linkedList()
    {
        firstNode= nullptr;
        lastNode= nullptr;
        count=0;
    }





// this is one where the C++ stynax gets very odd. Since we are returning back an interator we
// need to qualify it with the class it is in (linkedList<DataType>::iterator and we
// have ot include the typename so the C++ comiler knows this is a typename and not some other
// template class usage.
// find the node and return the address to the node. Return
// nullptr if not found
template<class DataType>
typename linkedList<DataType>::iterator linkedList<DataType>::find(const DataType &existingItem)
    {
        for(auto iter = begin(); iter != end(); iter++)
            {
                
                if(iter.current->data()==existingItem)
                    {
                        return iter;
                    }
            }
            return end();
    }

// remove the node equal to currentItem
template<class DataType>
bool linkedList<DataType>::erase(const DataType &currentItem)
    {
        bool erased = true;
/*


        for(auto iter = begin(); iter != nullptr; iter++)
            {
                if(*iter==currentItem)
                    {
                        if(iter==begin())
                            {
                                pop_front();
                                erased=true;
                                break;
                            }
                        if(iter==end())
                            {
                                pop_back();
                                erased=true;
                                break;
                            }
                        listNode<DataType>* before=iter.current->previous();
                        listNode<DataType>* after=iter.current->next();
                        before->next(after);
                        after->previous(before);
                        delete iter.current;
                        count--;
                        erased= true;
                        break;
                        
                    }
            }

*/

        return erased;
    }

// remove the node by iterator
template<class DataType>
typename linkedList<DataType>::iterator  linkedList<DataType>::erase(linkedList<DataType>::iterator iter)
    {
        if(end()==iter)
            {
                return end();
            }
        if(iter==begin())
            {
                pop_front();
                return begin();
            }
        for(auto run = begin();run != nullptr; run++)
            {
                if(run==iter)
                    {
                        listNode<DataType>* before=iter.current->previous();
                        listNode<DataType>* after=iter.current->next();
                        listNode<DataType>* temp=iter.current;
                        iter++;
                        delete temp;
                        before->next(after);
                        after->previous(before);
                        count--;
                        return iter;
                    }
            }
            return end();
    }

// other member functions go here.
template<class DataType>
void linkedList<DataType>::push_front(const DataType &newItem)
    {
        listNode<DataType>* temp=new listNode<DataType>(newItem);
        if(empty())
            {
                firstNode=temp;
                lastNode=temp;
                count++;
                return;
            }
        
        firstNode->previous(temp);
        temp->next(firstNode);
        firstNode=temp;
        count++;
    }
// add an item to the back of the list
template<class DataType>
void linkedList<DataType>::push_back(const DataType &newItem)
    {
        listNode<DataType>* temp=new listNode<DataType>(newItem);
        if(empty())
            {
                firstNode=temp;
                lastNode=temp;
                count++;
                return;
            }
        temp->previous(lastNode);
        lastNode->next(temp);
        lastNode=temp;
        count++;
        
    }
// remove an item from the front of the list
template<class DataType>
void linkedList<DataType>::pop_front()
    {
        if(empty())
            {return;}
        listNode<DataType>* temp=firstNode;
        firstNode=firstNode->next();
        delete temp;
        count--;
    }
// remove an item from the back of the list
template<class DataType>
void linkedList<DataType>::pop_back()
    {
        if(empty())
            { return;}
        listNode<DataType>* temp=lastNode;
        lastNode=lastNode->previous();
        delete temp;
        count--;
    }
template<class DataType>
void linkedList<DataType>::insert_before (iterator iter, const DataType &newItem)
    {
        if(iter==begin())
            {
                push_front(newItem);
                return;
            }
        for(auto run  = begin(); run != nullptr; run++)
            {
                if(run==iter)
                    {
                        listNode<DataType>* after=run.current;
                        listNode<DataType>* before=run.current->previous();
                        listNode<DataType>* temp=new listNode<DataType>(newItem);
                        temp->next(after);
                        temp->previous(before);
                        after->previous(temp);
                        before->next(temp);
                        count++;
                    }
            }
    
    }
// insert newItem after the node specified by the iterator
template<class DataType>
void linkedList<DataType>::insert_after (iterator iter, const DataType &newItem)
    {
        if(iter==end())
            {
                push_back(newItem);
                return;
            }
        for(auto run  = begin(); run != nullptr; run++)
            {
                if(run==iter)
                    {
                        listNode<DataType>* before=run.current;
                        listNode<DataType>* after=run.current->next();
                        listNode<DataType>* temp=new listNode<DataType>(newItem);
                        temp->next(after);
                        temp->previous(before);
                        after->previous(temp);
                        before->next(temp);
                        count++;
                    }
            }
    
    }
// display the contents of the list to the ostream&
template<class DataType>
void linkedList<DataType>::print(std::ostream &out) const
    {
        for(auto iter=begin();iter!= nullptr;iter++)
            {
                out<<iter.current->data()<<std::endl;
            }
            out<<std::endl;
    
    }

template<class DataType>
void linkedList<DataType>::move(const linkedList &other)
        {
            while(this->count!=0)
                {
                    this->pop_front();
                }
        listNode<DataType>* temp=other.firstNode;
        while(temp!= nullptr)
            {
                this->push_back(temp->data());
                temp=temp->next();
            }
            
        }
        
// all of your member function need to be before the #endif
#endif //LINKEDLIST_LINKEDLIST_H
