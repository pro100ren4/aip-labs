#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

struct student
{
    unsigned int sequenceNum, uid, yearOfBirth, yearOFAdmiss;
    char surname[40], name[40];
    struct{float phisics, math, prog, history;}grades;
};

struct list
{
    struct student data;
    struct student* next;
};

const int student_size = sizeof(struct student);
const int list_elem_size = sizeof(struct list);

struct student enter_data()
{
    struct student tmp; 
    printf("Enter student data:");
    printf("Sequence number:");
    while(scanf("%d", &(tmp.sequenceNum))!= 1)
    {
        rewind(stdin);
        puts("error: incorrect value");
    }

    printf("UID:");
    while(scanf("%d", &(tmp.uid))!= 1)
    {
        rewind(stdin);
        puts("error: incorrect value");
    }

    printf("Surname:");
    while(scanf("%s", &(tmp.surname))!= 1)
    {
        rewind(stdin);
        puts("error: incorrect value");
    }

    printf("Name:");
    while(scanf("%s", &(tmp.name))!= 1)
    {
        rewind(stdin);
        puts("error: incorrect value");
    }

    printf("Year of birth:");
    while(scanf("%d", &(tmp.yearOfBirth))!= 1)
    {
        rewind(stdin);
        puts("error: incorrect value");
    }

    printf("Year of Admission:");
    while(scanf("%d", &(tmp.yearOFAdmiss))!= 1)
    {
        rewind(stdin);
        puts("error: incorrect value");
    }

    printf("\tGrades\n");
    printf("Phisics:");
    while(scanf("%f", &(tmp.grades.phisics))!= 1)
    {
        rewind(stdin);
        puts("error: incorrect value");
    }

    printf("Math:");
    while(scanf("%f", &(tmp.grades.math))!= 1)
    {
        rewind(stdin);
        puts("error: incorrect value");
    }

    printf("Programming:");
    while(scanf("%f", &(tmp.grades.prog))!= 1)
    {
        rewind(stdin);
        puts("error: incorrect value");
    }

    printf("History:");
    while(scanf("%f", &(tmp.grades.history))!= 1)
    {
        rewind(stdin);
        puts("error: incorrect value");
    }
    
    return tmp;
}

struct list* create_list(unsigned int list_size)
{
    struct list* curr = NULL;
    struct list* beg = NULL;
    for(;list_size > 0; list_size--)
    {
        struct list* node = (struct list*)malloc(list_elem_size);
        node->data = enter_data();
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

 

int main()
{
    struct list* beg = create_list(5);
    return 0;
}