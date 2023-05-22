//
// Created by Maxwell Lim on 10/11/2019.
//

#ifndef PHONEBOOKAPPLICATION_ADDUPDATECOMMAND_H
#define PHONEBOOKAPPLICATION_ADDUPDATECOMMAND_H

#include "bookCommand.h"
#include "phoneBook.h"


class addUpdateCommand : public bookCommand
    {
        phoneBook book;
    public:
        //constructor
        addUpdateCommand(phoneBook &bookIn, std::istream &inStream, std::ostream &outStream);
        
        //update or add
        void execute() override;
    };


#endif //PHONEBOOKAPPLICATION_ADDUPDATECOMMAND_H
