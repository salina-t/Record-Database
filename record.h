/***************************************************************
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
//  FILE:       record.h
//
//  DESCRIPTION:
//      This file contains the constructor of record.
//
*****************************************************************/

#ifndef recordh
#define recordh

struct record
{
    int accountno;
    char name[30];
    char address[50];
    struct record *next;
};
#endif
