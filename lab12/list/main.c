#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "list.h"
#include "student.h"
#include "list_file.h"

int main()
{
    FILE* file = fopen("data.dat", "rb+");
    if(!file)
    {
        file = fopen("data.dat", "wb+");
        if(!file)
        {
            puts("error<main>: can't create/open file");
            return -1; 
        }
    }
    unsigned int list_length = 0;
    printf("enter list size:");
    while(scanf("%d", &list_length)!=1)
    {
        rewind(stdin);
        puts("error<main>: incorrect value");
    }
    struct list* beg = create_list(list_length);
    int run = 1, action = 0;
    while(run)
    {
        system("cls");
        puts("\tMENU");
        puts("1 - create list");
        puts("2 - print list");
        puts("3 - add element to list");
        puts("4 - delete element from list");//3
        puts("5 - write list to file");//4?
        puts("6 - read list from file");//2
        puts("7 - delete list");//1
        puts("8 - add two elements before last element");
        puts("9 - exit");
        printf("\nEnter action:");
        scanf("%d", &action);
        switch (action)
        {
        case 1:
            printf("warm<main>: The previos list will be deleted. Are you sure(y/n)?");
            char choice;
            rewind(stdin);
            while(scanf("%c", &choice)!=1)
            {
                rewind(stdin);
                puts("error<main>: Incorrect value.");
            }
            if(choice == 'y')
            {
                delete_list(beg);beg = NULL;
                puts("\tList was deleted");
                printf("Enter list size:");
                while(scanf("%d", &list_length)!=1)
                {
                    rewind(stdin);
                    puts("error<main>: incorrect value");
                }
                beg = create_list(list_length);

            }
            else if(choice == 'n');
            else puts("error<main>: Incorrect value");
            break;

        case 2:
            print_list(beg);
            break;

        case 3:
            puts("\tAdd after the element with UID");
            printf("UID:");
            unsigned long UID;
            while(scanf("%d", &UID)!= 1)
            {
                rewind(stdin);
                puts("error<main>: Incorrect value");
            }
            beg = add_to_list(beg, UID, enter_student());
            break;
        
        case 4:
            puts("\tDelete an element by UID");
            printf("UID:");
            while(scanf("%d", &UID)!= 1)
            {
                rewind(stdin);
                puts("error<main>: Incorrect value");
            }
            beg = del_from_list(beg, UID);
            break;
        
        case 5:
            if(write_file(file, beg) == 0)puts("\tList was written to file");
            break;
        
        case 6:
            if(beg)
            {
                printf("warn<main>: List will rewritten. Are you sure(y/n)?");
                rewind(stdin);
                while(scanf("%c", &choice)!=1)
                {
                    rewind(stdin);
                    puts("error<main>: Incorrect value.");
                }
                if(choice == 'y')
                {
                    delete_list(beg);beg = NULL;
                    puts("\tList was deleted");
                    beg = read_file(file, beg);
                }
                else if(choice == 'n');
                else puts("error<main>: Incorrect value");
            }
            else
                beg = read_file(file, beg);         
            break;
        
        case 7:
            printf("warm<main>: List will be deleted. Are you sure(y/n)?");
            rewind(stdin);
            while(scanf("%c", &choice)!=1)
            {
                rewind(stdin);
                puts("error<main>: Incorrect value.");
            }
            if(choice == 'y')
            {
                delete_list(beg);beg = NULL;
                puts("\tList was deleted");
            }
            else if(choice == 'n');
            else puts("error<main>: Incorrect value");
            break;

        case 8:
            beg = add_two_before_last(beg, enter_student(), enter_student());
            puts("\tStudents were added to list");
            break;

        case 9:
            printf("warm<main>: All unwritten data will be lost. Are you sure(y/n)?");
            rewind(stdin);
            while(scanf("%c", &choice)!=1)
            {
                rewind(stdin);
                puts("error<main>: Incorrect value.");
            }
            if(choice == 'y')
            {
                delete_list(beg);beg = NULL;
                puts("\tList was deleted");
                if(fclose(file) == 0)puts("\tFile was closed");
                run = 0;
            }
            else if(choice == 'n');
            else puts("error<main>: Incorrect value");
            break;

        default:
            puts("error<main>: Incorrect value");
            break;
        }
        puts("Push <Enter>");
        getch();
    }
    return 0;
}