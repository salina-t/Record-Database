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
//  FILE:        user_interface.cpp
//
//  DESCRIPTION:
//     This file contains the user interface (UI) of a bank database.
//     The database will display data and accept inputs while
//     accessing the database information.
 ****************************************************************/

#include <iostream>
#include <cstring>
#include "record.h"
#include "llist.h"

void getaddress(char[], int);

/*****************************************************************
//  Function name:    main
//
//  DESCRIPTION:      This funtion contains the user interface
//                    of the bank database. It takes in inputs
//                    from the user and returns outputs from
//                    the database.
//
//  Parameters:       argc (int): number of arguments
//                    argv (char *[]): array of arguments
//
//  Return values:    0: success
//
 *****************************************************************/

int main(int argc, char *argv[])
{
    llist *list;
    list = new llist();
    int repeat;
    repeat = 1;

#ifdef debug
    std::cout << "\nDebug mode ON\n" << std::endl;
#endif
    repeat = 0;
    std:: cout << "Welcome to the bank database." << std::endl;
    std::cout << "To access the database, please select an option:\n" << std::endl;

    while (repeat != 1)
    {
        char input[10] = "";
        std::cout << "add: add a new record in the database" << std::endl;
        std::cout << "printall: Print all records in the database" << std::endl;
        std::cout << "find: Find record(s) with a specified account #" << std::endl;
        std::cout << "delete: Delete existing record(s) from the database using the account # as a key" << std::endl;
        std::cout << "quit: Quit the program" << std::endl;
        std::cin.getline(input, 10);

        if (strlen(input) != 0 && strncmp(input, "add", strlen(input)) == 0)
        {
            int accountno;
            char name[30];
            char address[50] = {0};
            int valid = 1;
            std::cout << "Please enter your account number" << std::endl;
            while (valid == 1)
            {
                std::cin >> accountno;
                if (std::cin.good() && accountno > 0)
                {
                    valid = 0;
                }
                else
                {
                    std::cout << "Invalid account number/input. Please type in your account number." << std::endl;
                    std::cin.clear();
                    std::cin.ignore(100, '\n');
                }
            }
            std::cin.ignore(100, '\n');
            std::cout << "Please enter your name" << std::endl;
            std::cin.getline(name, 30);

            std::cout << "Please enter your address. Enter the \"%\" character to enter" << std::endl;
            getaddress(address, 50);
            list->addRecord(accountno, name, address);
            std::cout << "Action completed. Please select a new option.\n" << std::endl;
        }
        else if (strlen(input) != 0 && strncmp(input, "printall", strlen(input)) == 0)
        {
            std::cout << *list;
            std::cout << "Action completed. Please select a new option.\n" << std::endl;
        }
        else if (strlen(input) != 0 && strncmp(input, "find", strlen(input)) == 0)
        {
            int accountno;
            int findval;
            int valid;
            valid = 1;
            std::cout << "Please type in your account number." << std::endl;
            while (valid == 1)
            {
                std::cin >> accountno;
                if (std::cin.good() && accountno > 0)
                {
                    valid = 0;
                }
                else
                {
                    std::cout << "Invalid account number/input. Please type in your account number." << std::endl;
                    std::cin.clear();
                    std::cin.ignore(100, '\n');
                }
            }
            std::cin.ignore(100, '\n');
            findval = list->findRecord(accountno);
            /* success or fail find value */
            if (findval == 0)
            {
                std::cout << "Action completed. Please select a new option.\n" << std::endl;
            }
            else
            {
                std::cout << "Error: No record(s) with matching account number found. Please select a new option.\n" << std::endl;
            }
        }
        else if (strlen(input) != 0 && strncmp(input, "delete", strlen(input)) == 0)
        {
            int accountno;
            int deleteval;
            int valid;
            valid = 1;
            std::cout << "Please type in your account number" << std::endl;
            while (valid == 1)
            {
                std::cin >> accountno;
                if (std::cin.good() && accountno > 0)
                {
                    valid = 0;
                }
                else
                {
                    std::cout << "Invalid account number/input. Please type in your account number." << std::endl;
                    std::cin.clear();
                    std::cin.ignore(100, '\n');
                }
            }
            std::cin.ignore(100, '\n');
            deleteval = list->deleteRecord(accountno);
            /* success or fail delete value */
            if (deleteval == 0)
            {
                std::cout << "Action completed. Please select a new option.\n" << std::endl;
            }
            else
            {
                std::cout << "Error: No record(s) with matching account number found. Please select a new option.\n" << std::endl;
            }
        }
        else if (strlen(input) != 0 && strncmp(input, "quit", strlen(input)) == 0)
        {
            repeat = 1;
            delete(list);
        }
        else
        {
            std::cout << "\nInvalid option. Please choose one of the listed options." << std::endl;
            std::cin.clear();
        }
    }
    return 0;
}

/*****************************************************************
//  Function name:    getaddress
//
//  DESCRIPTION:      This funtion stores what the user inputs
//                    into the address array character by
//                    character. If the user types the escape
//                    character '%' it will leave the method and
//                    stop recording characters into the array.
//
//  Parameters:       input (char []): address array
//                    size (int): the size of the input array
//
//  Return values:    0: success
//
 *****************************************************************/

void getaddress(char input[], int size)
{
    std::cin.getline(input, size, '%');
    std::cin.ignore(100, '\n');
}
