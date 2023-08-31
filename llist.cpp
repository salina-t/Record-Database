/*****************************************************************
//  NAME:        Salina Thongsisavath
//
//  HOMEWORK:    project 2
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        April 23, 2023 
//
//  FILE:        llist.cpp
//
//  DESCRIPTION: 
//     This file contains the function definitions of the 
//     functions that are called in the user_interface.cpp file. 
//
 ****************************************************************/

#include <iostream>
#include <fstream>
#include <cstring>
#include "record.h"
#include "llist.h"

/*****************************************************************
//
//  Function Name:       llist
//
//  DESCRIPTION:         constructor to create a default llist.
//
//  Parameters:         none
//
//  return value:       none
//
 *****************************************************************/

llist::llist()
{
    start = NULL;
    strcpy(this->filename, "project2_database");
    readfile();
}

/*****************************************************************
//
//  Function Name:       llist
//
//  DESCRIPTION:         constructor to create a llist with
//                       a custom file name for the database.
//
//  Parameters:         (char[]): input: filename for database
//
//  return value:       none
//
 *****************************************************************/

llist::llist(char input[])
{
    start = NULL;
    strcpy(this->filename, input);
    readfile();
}

/*****************************************************************
//
//  Function Name:       ~llist
//
//  DESCRIPTION:         destructor for llist.
//
//  Parameters:         none
//
//  return value:       none
//
 *****************************************************************/

llist::~llist()
{
    writefile();
    cleanup();
}

/*****************************************************************
//
//  Function Name:       llist
//
//  DESCRIPTION:         constructor to create a llist.
//
//  Parameters:         (llist&) list: list that contains contents
//                      that would like to be copied to a new llist.
//
//  return value:       none
//
 *****************************************************************/

llist::llist(const llist& list)
{
    this->start = NULL;
    struct record *iterator;
    iterator = list.start;
    while (iterator != NULL)
    {
        this->addRecord(iterator->accountno, iterator->name, iterator->address);
        iterator = iterator->next;
    }
    strcpy(this->filename, "project2_database");
}

/*****************************************************************
//  Function name:    addRecord
//
//  DESCRIPTION:      will add a record to the database.    
//
//  Parameters:       accountno (int): account number from input
//                    name (char []): stores name from input 
//                    address (char []): stores address from input
//
//  Return values:    none
//
 *****************************************************************/

void llist::addRecord(int accountno, char name[], char address[])
{
    struct record *temp;
    struct record *iterator;
    int flip;
    struct record *newRecord;

#ifdef debug
    std::cout << "-----------------------DEBUG MODE INFORMATION-----------------------" << std::endl;
    std::cout << "FUNCTION: addRecord" << std::endl;
    std::cout << "PARAMETERS: " << std::endl;
    std::cout << "(int) accountno: " << accountno << std::endl;
    std::cout << "char []) name: " << name << std::endl;
    std::cout << "(char []) address: " << address << std::endl;
    std::cout << "--------------------------------------------------------------------" << std::endl;
#endif

    flip = 0;
    iterator = start;
    newRecord = new struct record;
    newRecord->accountno = accountno;
    strcpy(newRecord->name, name);
    strcpy(newRecord->address, address);
    if (start != NULL)
    {
        /* add to beginning of existing list */
        if (accountno < (start->accountno))
        {
            temp = start;
            start = newRecord;
            newRecord->next = temp;
            flip = 1;
        }
        while (flip != 1 && accountno >= iterator->accountno)
        {
            temp = iterator;
            iterator = iterator->next;
            if (iterator == NULL)
            {
                temp->next = newRecord;
                newRecord-> next = NULL;
                flip = 1;
            }
        }
        if (flip == 0)
        {
            newRecord->next = temp->next;
            temp->next = newRecord;
        }
    }
    else
    {
        start = newRecord;
        newRecord->next = NULL;
    }
}

/*****************************************************************
//  Function name:    printAllRecords
//
//  DESCRIPTION:      This funtion prints all records that exist
//                    in the database.    
//
//  Parameters:       none
//
//  Return values:    none  
//
 *****************************************************************/

void llist::printAllRecords()
{
    struct record *iterator;
    iterator = start;
    /* to see if any records were printed */
#ifdef debug
    std::cout << "-----------------------DEBUG MODE INFORMATION-----------------------" << std::endl;
    std::cout << "FUNCTION: printAllRecords" << std::endl;
    std::cout << "--------------------------------------------------------------------" << std::endl;
#endif
    if (iterator == NULL)
    {
        std::cout << "There are no existing records to print." << std::endl;
    }
    while (iterator != NULL)
    {
        std::cout << "Account Number: " << iterator->accountno << std::endl;
        std::cout << "Account Name: " << iterator->name << std::endl;
        std::cout << "Account Adress: " << iterator->address << std::endl;
        iterator = iterator->next;
    }
}

/*****************************************************************
//  Function name:    findRecord
//
//  DESCRIPTION:      This funtion attempts to search for an 
//                    account (record) using an account 
//                    number.   
//
//  Parameters:       accountno (int): account number from input 
//
//  Return values:    0: success
//                    1: fail
//
 *****************************************************************/

int llist::findRecord(int accountno)
{
    struct record *iterator;
    int returnval;

#ifdef debug
    std::cout << "-----------------------DEBUG MODE INFORMATION-----------------------" << std::endl;
    std::cout << "FUNCTION: findRecord" << std::endl;
    std::cout << "PARAMETERS: " << std::endl;
    std::cout << "(int) accountno: " << accountno << std::endl;
    std::cout << "---------------------------------------------------------------------" << std::endl;
#endif

    iterator = start;
    returnval = 1;
    if (iterator == NULL)
    {
        std::cout << "There are no existing records." << std::endl;
    }
    while (iterator != NULL)
    {
        if (accountno == iterator->accountno)
        {
            std::cout << iterator->accountno << std::endl;
            std::cout << iterator->name << std::endl;
            std::cout << iterator->address << std::endl;
            returnval = 0;
        }
        iterator = iterator->next;
    }
    if (returnval == 1)
    {
        printf("There are no existing records with that account number.\n");
    }
    return returnval;
}

/*****************************************************************
//  Function name:    deleteRecord
//
//  DESCRIPTION:      This funtion deletes a record from the 
//                    database.   
//
//  Parameters:       accountno (int): account number from input 
//
//  Return values:    0: sucess
//                    1: fail 
//
 *****************************************************************/

int llist::deleteRecord(int accountno)
{
    struct record* temp;
    struct record* previous;
    struct record* iterator;
    int returnval;

#ifdef debug
    std::cout << "-----------------------DEBUG MODE INFORMATION-----------------------" << std::endl;
    std::cout << "FUNCTION: deleteRecord" << std::endl;
    std::cout << "PARAMETERS: " << std::endl;
    std::cout << "(int) accountno: " << accountno << std::endl;
    std::cout << "--------------------------------------------------------------------" << std::endl;
#endif

    previous = NULL;
    iterator = start;
    returnval = 1;
    while (iterator != NULL)
    {
        if (accountno == iterator->accountno)
        {
            temp = iterator->next;
            if (previous != NULL)
            {
                previous->next = temp;
            }
            else
            {
                start = temp;
            }
            delete(iterator);
            iterator = temp;
            returnval = 0;
        }
        else
        {
            previous = iterator;
            iterator = iterator->next;
        }
    }
    return returnval;
}

/*****************************************************************
//
//  Function name:   writefile 
//
//  DESCRIPTION:     This function saves existing files in the database 
//                   into a file. 
//
//  Parameters:      none
//
//  Return values:   0: success 
//                   1: fail
//   
 *****************************************************************/

int llist::writefile()
{
    struct record *iterator;
    iterator = start;
    int returnval;
    returnval = 1;
#ifdef debug
    std::cout << "-----------------------DEBUG MODE INFORMATION-----------------------" << std::endl;
    std::cout << "FUNCTION: writefile" << std::endl;
    std::cout << "--------------------------------------------------------------------" << std::endl;
#endif
    std::ofstream myfile(filename);
    if (myfile.is_open())
    {
        while (iterator != NULL)
        {
            myfile << iterator->accountno << std::endl;
            myfile << iterator->name << std::endl;
            myfile << iterator->address << "%" << std::endl;
            iterator = iterator->next;
        }
        returnval = 0;
        myfile.close();
    }
    return returnval;
}

/*****************************************************************
//
//  Function name:  readfile
//
//  DESCRIPTION:    This function retrieves records from a file 
//                  and stores it in the database. 
//
//  Parameters:     none
//
//  Return values:  0: success
//                  1: fail 
//
 *****************************************************************/

int llist::readfile()
{
    int accountno;
    char name[30];
    char address[50];
    char temp[50];
    int retval;
    std::ifstream myfile(filename);
#ifdef debug
    std::cout << "-----------------------DEBUG MODE INFORMATION-----------------------" << std::endl;
    std::cout << "FUNCTION: readfile" << std::endl;
    std::cout << "\n--------------------------------------------------------------------\n\n" << std::endl;
#endif
    if (myfile.is_open())
    {
        retval = 0;
        while (myfile.good())
        {
            myfile >> accountno;
            /* get rid of the '/n' */
            myfile.getline(temp, 1);
            myfile.getline(name, 30);
            myfile.getline(address, 50, '%');
            myfile.ignore(100, '\n');
            if (strlen(name) != 0 && strlen(address) != 0)
            {
                addRecord(accountno, name, address);
            }
        }
        myfile.close();
    }
    else
    {
        retval = 1;
    }
    return retval;
}

/*****************************************************************
//
//  Function name:  cleanup
//  
//  DESCRIPTION:    releases all alocated space in the heap memory
//                  that was used to hold existing records. 
//
//  Parameters:     none
//
//  Return values:  none
//
 ******************************************************************/

void llist::cleanup()
{
    struct record *iterator;
#ifdef debug
    std::cout << "-----------------------DEBUG MODE INFORMATION -----------------------\n" << std::endl;
    std::cout << "FUNCTION: cleanup" << std::endl;
    std::cout << "---------------------------------------------------------------------\n\n" << std::endl;
#endif
    iterator = start;
    while (iterator != NULL)
    {
        delete(iterator);
        iterator = iterator->next;
    }
}

/*****************************************************************
//
//  Function Name:       operator overload
//
//  DESCRIPTION:         allows records in llist to be printed
//                       to console using '<<' operator.
//
//  Parameters:         (std::ostream&) out: stream where list  
//                      contents are stored.
//                      (const llist&) list: list to be printed.
//
//  return value:       std::ostream&: contents of list printed    
//
 *****************************************************************/

std::ostream& operator<<(std::ostream& out, const llist& list)
{
    struct record *iterator;
    iterator = list.start;
    if (iterator == NULL)
    {
        out << "There are no existing records to print." << std::endl;
    }
    while (iterator != NULL)
    {
        out << "Account Number: " << iterator->accountno << std::endl;
        out << "Account Name: " << iterator->name << std::endl;
        out << "Account Address: " << iterator->address << std::endl;
        iterator = iterator->next;
    }
    return out;
}

/*****************************************************************
//
//  Function Name:       operator overload
//
//  DESCRIPTION:         allows records in llist to be duplicated
//                       to another llist
//
//  Parameters:         (llist&) copyFrom: llist that contents  
//                      should be duplicated
//
//  return value:       *this: pointer to duplicated llist.    
//
 *****************************************************************/

llist& llist::operator=(const llist& copyFrom)
{
    this->cleanup();
    struct record *iterator;
    iterator = copyFrom.start;
    while (iterator != NULL)
    {
        this->addRecord(iterator->accountno, iterator->name, iterator->address);
        iterator = iterator->next;
    }
    return *this;
}
