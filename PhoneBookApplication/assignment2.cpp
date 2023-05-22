//
// Created by Maxwell Lim on 10/11/2019.
//
#include <iostream>
#include "addUpdateCommand.h"
#include "eraseCommand.h"
#include "printCommand.h"
#include "menuList.h"

int main()
    {
        phoneBook directory;
        
        addUpdateCommand update(directory, std::cin, std::cout);
        eraseCommand erase(directory, std::cin, std::cout);
        printCommand print(directory, std::cin, std::cout);
        
        menuItem updateItem('a', "add/update", update);
        menuItem eraseItem('e', "erase", erase);
        menuItem printItem('p', "print", print);
        
        menuList menu("Phone book menu:");
        menu.add(updateItem);
        menu.add(eraseItem);
        menu.add(printItem);
        std::cout << "Starting the Phone Book\n" << std::endl;
        menu.start();
        
        
        return 0;

    }