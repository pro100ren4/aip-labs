#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

struct student
{
    unsigned int sequenceNum, uid, yearOfBirth, yearOFAdmiss;
    char surname[40], name[40];
    struct{float phisics, math, prog, history;}grades;
};

struct studentListData 
{
    struct student student;
    struct studentListData* next;
};

const int studentSize = sizeof(struct student*);

struct studentListData* createList(unsigned int listSize)
{
    struct studentListData* begin = NULL;
    struct studentListData* temp;
    unsigned int curSequenceNum, curUid, curYearOfBirth, curYearOfAdmiss;
    char curSurname[40], curName[40];
    float curPhisics, curMath, curProg, curHistory;


    for(int i = 0; i < listSize; i++)
    {

        printf("STUDENT %d", i);
        printf("enter sequence number:");
        while(scanf("%d", &curSequenceNum)!=1)
        {
            rewind(stdin);
            puts("error: incorrect value");
        }
        while(scanf("%d", &curUid)!=1)
        {
            rewind(stdin);
            puts("error: incorrect value");
        }
        while(scanf("%s", curSurname)!=1)
        {
            rewind(stdin);
            puts("error: incorrect value");
        }
        while(scanf("%s", curName)!=1)
        {
            rewind(stdin);
            puts("error: incorrect value");
        }
        while(scanf("%d", &curYearOfBirth)!=1)
        {
            rewind(stdin);
            puts("error: incorrect value");
        }
        while(scanf("%d", &curYearOfAdmiss)!=1)
        {
            rewind(stdin);
            puts("error: incorrect value");
        }
        printf("ENTER GRADES:");
        while(scanf("%f", &curPhisics)!=1)
        {
            rewind(stdin);
            puts("error: incorrect value");
        }
        while(scanf("%f", &curMath)!=1)
        {
            rewind(stdin);
            puts("error: incorrect value");
        }
        while(scanf("%f", &curProg)!=1)
        {
            rewind(stdin);
            puts("error: incorrect value");
        }
        while(scanf("%f", &curHistory)!=1)
        {
            rewind(stdin);
            puts("error: incorrect value");
        }

        temp;
        
    }

}


int main()
{

    return 0;
}