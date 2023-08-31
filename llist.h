/*****************************************************************
//
//  NAME:       Salina Thongsisavath
//
//  HOMEWORK:   project 2 
//
//  CLASS:      ICS 212
//
//  INSTRUCTOR: Ravi Narayan
//
//  DATE:       April 23, 2023
//
//  FILE:       llist.h
//
//  DESCRIPTION:
//      This file contains the llist class.
//
 *****************************************************************/

#ifndef listh
#define listh

class llist
{
    private:
    struct record *    start;
    char        filename[20];
    int         readfile();
    int         writefile();
    void        cleanup();

    public:
    llist();
    llist(char[]);
    llist(const llist&);
    ~llist();
    void addRecord(int, char[], char[]);
    int findRecord(int);
    void printAllRecords();
    int deleteRecord(int);
    friend std::ostream& operator<<(std::ostream&, const llist&);
    llist& operator=(const llist&);
};
#endif
