#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

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
    printf("enter tree size:");
    while(scanf("%d", &list_length)!=1)
    {
        rewind(stdin);
        puts("error<main>: incorrect value");
    }
    struct node* top = NULL;
    top = create_tree(top, list_length);
    int run = 1; char action = 0;
    while (run)
    {
        system("cls");
        puts("\tMENU");
        puts("1 - create tree");
        puts("2 - print students");
        puts("3 - tree structure mapping");
        puts("4 - add node to tree");
        puts("5 - delete node from tree");
        puts("6 - write tree to file");
        puts("7 - read tree from file");
        puts("8 - print tree leafs");
        puts("9 - print programming average grade");
        puts("a - delete tree");
        puts("b - exit");
        printf("\nEnter action:");
        rewind(stdin);
        action = getc(stdin);
        switch(action)
        {
        case 49://1
            printf("warm<main>: The previos tree will be deleted. Are you sure(y/n)?");
            rewind(stdin);
            char choice = getc(stdin);
            if(choice == 'y' || choice == 'Y')
            {
                delete_tree(top);top = NULL;
                printf("enter tree size:");
                while(scanf("%d", &list_length)!=1)
                {
                    rewind(stdin);
                    puts("error<main>: incorrect value");
                }
                top = create_tree(top, list_length);
            }
            else if(choice == 'n' || choice == 'N');
            else puts("error<main>: Incorrect value");
            break;

        case 50://2
            puts("\tSTUDENTS");
            print_tree(top);
            break;
        
        case 51://3
            puts("\tTREE STRUCTURE");
            struct_map(top, 3);
            break;

        case 52://4
            top = add_to_tree(top, enter_student());
            break;

        case 53://5
            puts("\tDelete an element by UID");
            unsigned long UID;
            printf("UID:");
            while(scanf("%d", &UID)!= 1)
            {
                rewind(stdin);
                puts("error<main>: Incorrect value");
            }
            top = del_from_tree(top, UID);
            break;

        case 54://6
            write_file(top, file);
            break;

        case 55://7
            if(top)
            {
                printf("warn<main>: tree will rewritten. Are you sure(y/n)?");
                rewind(stdin);
                while(scanf("%c", &choice)!=1)
                {
                    rewind(stdin);
                    puts("error<main>: Incorrect value.");
                }
                if(choice == 'y' || choice == 'Y')
                {
                    delete_tree(top);top = NULL;
                    puts("\tTree was deleted");
                    top = read_file(top,file);
                }
                else if(choice == 'n' || choice == 'N');
                else puts("error<main>: Incorrect value");
            }
            else
                top = read_file(top,file);
            break;

        case 56://8
            puts("\tTREE LEAFS");
            print_leafs(top);
            break;

        case 57://9
            printf("PROGRAMMING AVERAGE GRADE: %.2f", prog_average(top));
            break;

        case 97://a
            printf("warm<main>: tree will be deleted. Are you sure(y/n)?");
            rewind(stdin);
            while(scanf("%c", &choice)!=1)
            {
                rewind(stdin);
                puts("error<main>: Incorrect value.");
            }
            if(choice == 'y' || choice == 'Y')
            {
                delete_tree(top);top = NULL;
                puts("\ttree was deleted");
            }
            else if(choice == 'n' || choice == 'N');
            else puts("error<main>: Incorrect value");
            break;

        case 98://b
            printf("warm<main>: All unwritten data will be lost. Are you sure(y/n)?");
            rewind(stdin);
            while(scanf("%c", &choice)!=1)
            {
                rewind(stdin);
                puts("error<main>: Incorrect value.");
            }
            if(choice == 'y' || choice == 'Y')
            {
                delete_tree(top);top = NULL;
                puts("\ttree was deleted");
                if(fclose(file) == 0)puts("\tFile was closed");
                run = 0;
            }
            else if(choice == 'n' || choice == 'N');
            else puts("error<main>: Incorrect value");
            break;

        default:
            puts("error<main>: Incorrect value");
            break;
        }
        puts("Press <Enter>");
        getch();
        
    }
    return 0;
}