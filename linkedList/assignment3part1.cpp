#include <iostream>
#include <string>
#include "linkedList.h"

int main()
    {
        // test push_front followed by pop_front
        std::cout << "Create list" << std::endl;
        linkedList<int> list;
        
        std::cout << "Print empty list" << std::endl;
        list.debug(std::cout);
        
        std::cout << "push_front(12)" << std::endl;
        list.push_front(12);
        
        std::cout << "Print list" << std::endl;
        list.debug(std::cout);
        
        std::cout << "push_front(13)" << std::endl;
        list.push_front(13);
        
        std::cout << "Print list" << std::endl;
        list.debug(std::cout);
        
        std::cout << "push_front(14)" << std::endl;
        list.push_front(14);
        
        std::cout << "Print list" << std::endl;
        list.debug(std::cout);
        
        std::cout << "pop_front" << std::endl;
        list.pop_front();
        
        std::cout << "Print list" << std::endl;
        list.debug(std::cout);
        
        std::cout << "pop_front" << std::endl;
        list.pop_front();
        
        std::cout << "Print list" << std::endl;
        list.debug(std::cout);
        
        std::cout << "pop_front" << std::endl;
        list.pop_front();
        
        std::cout << "Print list" << std::endl;
        list.debug(std::cout);
        
        return 0;
    }