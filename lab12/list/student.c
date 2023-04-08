#include "student.h"

const int student_size = sizeof(struct student);

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