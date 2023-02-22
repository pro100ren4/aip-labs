#include <stdio.h>

struct student
{
    int sequenceNum, uid, yearOfBirth, yearOFAdmiss;
    char surname[40], name[40];
    struct{float phisics, math, prog, history;}grades;
};

struct student* enterData(unsigned int numOfStudents)
{
    if(numOfStudents == 0)
    {
        return NULL;
    }

    
}

int main()
{
    return 0;
}