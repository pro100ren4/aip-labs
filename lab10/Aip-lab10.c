#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

struct student
{
    unsigned long sequenceNum, uid, yearOfBirth, yearOFAdmiss;
    char surname[40], name[40];
    struct{float phisics, math, prog, history;}grades;
};

struct list
{
    struct student data;
    struct list* next;
};

const int student_size = sizeof(struct student);
const int list_size = sizeof(struct list);

struct student enter_student()
{
    struct student tmp; 
    system("cls");
    printf("\tEnter student data\n");
    printf("Sequence number:");
    while(scanf("%d", &(tmp.sequenceNum))!= 1)
    {
        rewind(stdin);
        puts("error<enter_student>: incorrect value");
    }

    printf("UID:");
    while(scanf("%d", &(tmp.uid))!= 1)
    {
        rewind(stdin);
        puts("error<enter_student>: incorrect value");
    }

    printf("Surname:");
    while(scanf("%s", &(tmp.surname))!= 1)
    {
        rewind(stdin);
        puts("error<enter_student>: incorrect value");
    }

    printf("Name:");
    while(scanf("%s", &(tmp.name))!= 1)
    {
        rewind(stdin);
        puts("error<enter_student>: incorrect value");
    }

    printf("Year of birth:");
    while(scanf("%d", &(tmp.yearOfBirth))!= 1)
    {
        rewind(stdin);
        puts("error<enter_student>: incorrect value");
    }

    printf("Year of Admission:");
    while(scanf("%d", &(tmp.yearOFAdmiss))!= 1)
    {
        rewind(stdin);
        puts("error<enter_student>: incorrect value");
    }

    printf("\tGrades\n");
    printf("Phisics:");
    while(scanf("%f", &(tmp.grades.phisics))!= 1)
    {
        rewind(stdin);
        puts("error<enter_student>: incorrect value");
    }

    printf("Math:");
    while(scanf("%f", &(tmp.grades.math))!= 1)
    {
        rewind(stdin);
        puts("error<enter_student>: incorrect value");
    }

    printf("Programming:");
    while(scanf("%f", &(tmp.grades.prog))!= 1)
    {
        rewind(stdin);
        puts("error<enter_student>: incorrect value");
    }

    printf("History:");
    while(scanf("%f", &(tmp.grades.history))!= 1)
    {
        rewind(stdin);
        puts("error<enter_student>: incorrect value");
    }
    
    return tmp;
}

struct list* create_list(unsigned int list_length)
{
    struct list* curr = NULL;
    struct list* beg = NULL;
    for(;list_length > 0; list_length--)
    {
        struct list* node = (struct list*)malloc(list_size);
        node->data = enter_student();
        node->next = NULL;

        if(beg == NULL)
        {
            beg = node;
            curr = node;
        }
        else
        {
            curr->next = node;
            curr = node;
        }
    }
    return beg;
}

//after delete write [beg = NULL]
void delete_list(struct list* beg)
{
    struct list* curr;
    while(beg != NULL)
    {
        curr = beg;
        beg = curr->next;
        free(curr);
    }
}

//add element after element with <uid>
struct list* add_to_list(struct list* beg, unsigned long uid, struct student new_student)
{
    struct list* tmp = (struct list*)malloc(list_size);
    struct list* res = beg;
    if(!beg)
    {
        puts("warn<add_to_list>: List is empty. Create new list");
        beg = tmp;
        beg->data = new_student;
        beg->next = NULL;
        return res;

    }
    int f = 0;
    while(beg)
    {
        if(beg->data.uid == uid)
        {
            f = 1;
            tmp->data = new_student;
            tmp->next = beg->next;
            beg->next = tmp;
            break;
        }
        beg = beg->next;
    }
    if(!f)
    {
        puts("error<add_to_list>: Didn't add new element");
        return NULL;
    }
    return res;
}

struct list* add_two_before_last(struct list* beg, struct student new_student1, struct student new_student2)
{
    if(!beg)
    {
        puts("error<add_two_before_last>: List is empty");
        return NULL;
    }

    struct list* tmp1 = (struct list*)malloc(list_size);
    tmp1->data = new_student1;
    struct list* tmp2 = (struct list*)malloc(list_size);
    tmp2->data = new_student2;
    struct list* tmp;
    struct list* start = beg;

    if(beg->next == NULL)
    {
        tmp = beg;
        beg = tmp1;
        tmp1->next = tmp2;
        tmp2->next = tmp;
        return beg;
    }
    while(beg->next->next != NULL) beg = beg->next;
    tmp = beg->next;
    beg->next = tmp1;
    tmp1->next = tmp2;
    tmp2->next = tmp;
    return start;
}

//delete element with <uid>
struct list* del_from_list(struct list* beg, unsigned long uid)
{
    if(!beg)
    {
        puts("error<del_from_list>: List is empty");
        return NULL;
    }
    struct list* tmp;
    struct list* curr = beg;

    
    if(curr->next != NULL)
    {
        if(curr->data.uid == uid)
        {
            tmp = curr;
            curr = tmp->next;
            free(tmp);
            return curr;
        }
        while (curr->next->next != NULL)
        {
            if(curr->next->data.uid == uid)
            {   
                tmp = curr->next;
                curr->next = tmp->next;
                free(tmp);
                return beg;
            }
            curr = curr->next;
        }
        if(curr->next->data.uid == uid)
        {
            tmp = curr->next;
            curr->next = NULL;
            free(tmp);
            return beg;
        }
    }
    else
    {
        if (curr->data.uid == uid)
        {
            free(curr);
            return NULL;
        }
    }

    puts("error<del_from_list>: Didn't delete element");
    return beg;
}

int sort_file(FILE* file)
{
    struct student tmp1, tmp2;
    fseek(file, 0, SEEK_END);
    long fileLength = ftell(file)/student_size;
    rewind(file);
    if(file == NULL)
        return -1;
    for(int i = 0; i < fileLength-1; i++)
    {
        for(int j = 0; j < fileLength-1; j++)
        {
            fseek(file, j*student_size, SEEK_SET);
            fread(&tmp1, student_size, 1, file);
            fread(&tmp2, student_size, 1, file);

            if(tmp1.uid > tmp2.uid)
            {
                fseek(file, (-2)*student_size, SEEK_CUR);
                fwrite(&tmp2, student_size, 1, file);
                fwrite(&tmp1, student_size, 1, file);
            }
        }
    }

    return 0;
}

int write_file(FILE* file, struct list* beg)
{
    if(beg == NULL)
    {
        puts("warn<write_file>: The list is empty");
        return 0;
    }
    while(beg != NULL)
    {
        if(fwrite(&(beg->data), student_size, 1, file)!= 1)
        {
            puts("error<write_file>: Can't write file");
            return -1;
        }
        beg = beg->next;
    }
    sort_file(file);
    return 0;
}
//<beg> must be empty 
struct list* read_file(FILE* file, struct list* beg)
{
    if(!file)
    {
        puts("error<read_file>: No file");
        return NULL;
    }
    if(beg)
    {
        puts("error<read_file>: The list is not empty");
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long file_length = ftell(file)/student_size;
    struct list* curr = NULL;
    struct student tmp;
    rewind(file);
    for(int i = 0;i < file_length; i++)
    {
        struct list* node = (struct list*)malloc(list_size);
        fread(&tmp, student_size, 1, file);
        node->data = tmp;
        node->next = NULL;

        if(beg == NULL)
        {
            beg = node;
            curr = node;
        }
        else
        {
            curr->next = node;
            curr = node;
        }
    }
    return beg;
}

int print_list(struct list* beg)
{
    if(!beg)
    {
        puts("warn<print_list>: The list is empty");
        return 0;
    }
    while(beg)
    {
        printf("\nUID:%d SeqNum:%d %s %s birth:%d admission:%d\nGrades>> phis:%.2f math:%.2f prog:%.2f his:%.2f\n", beg->data.uid, beg->data.sequenceNum, beg->data.surname, beg->data.name, beg->data.yearOfBirth, beg->data.yearOFAdmiss, beg->data.grades.phisics, beg->data.grades.math, beg->data.grades.prog, beg->data.grades.history);
        beg = beg->next; 
    }
    return 0;
}

int print_awesome_students(struct list* beg)
{
   if(!beg)
    {
        puts("warn<print_list>: The list is empty");
        return 0;
    }
    puts("\tAWESOME STUDENTS");
    while(beg)
    {
        if(beg->data.grades.history == 5.00f && beg->data.grades.math == 5.00f && beg->data.grades.phisics == 5.00f && beg->data.grades.prog == 5.00f)
        {
            printf("\nUID:%d SeqNum:%d %s %s birth:%d admission:%d\nGrades>> phis:%.2f math:%.2f prog:%.2f his:%.2f\n", beg->data.uid, beg->data.sequenceNum, beg->data.surname, beg->data.name, beg->data.yearOfBirth, beg->data.yearOFAdmiss, beg->data.grades.phisics, beg->data.grades.math, beg->data.grades.prog, beg->data.grades.history);
            beg = beg->next;
        }  
    }
    return 0;
}

 

int main()
{
    FILE* file = fopen("lab9.dat", "rb+");
    if(!file)
    {
        file = fopen("lab9.dat", "wb+");
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