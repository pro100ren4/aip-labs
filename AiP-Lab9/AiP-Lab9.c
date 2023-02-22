#include <stdio.h>

struct student
{
    unsigned int sequenceNum, uid, yearOfBirth, yearOFAdmiss;
    char surname[40], name[40];
    struct{float phisics, math, prog, history;}grades;
};

const int sizeStudent = sizeof(struct student);

struct student* enterData(unsigned int numOfStudents)
{
    if(numOfStudents == 0)
    {
        return NULL;
    }
    struct student* studentArr = (struct student*)malloc(numOfStudents*sizeStudent);
    
    for(int i = 0; i < numOfStudents; i++)
    {
        system("cls");
        printf("enter sequence number:");
        while(scanf("%d", studentArr[i].sequenceNum)!=1)
        {
            rewinf(stdin);
            puts("error: incorrect value");
        }

        printf("enter uid:");
        while(scanf("%d", studentArr[i].uid)!=1)
        {
            rewinf(stdin);
            puts("error: incorrect value");
        }

        printf("enter surname:");
        while(scanf("%s", studentArr[i].surname)!=1)
        {
            rewinf(stdin);
            puts("error: incorrect value");
        }

        printf("enter name:");
        while(scanf("%s", studentArr[i].name)!=1)
        {
            rewinf(stdin);
            puts("error: incorrect value");
        }

        printf("enter year of birth:");
        while(scanf("%d", studentArr[i].yearOfBirth)!=1)
        {
            rewinf(stdin);
            puts("error: incorrect value");
        }

        printf("enter year of admission:");
        while(scanf("%d", studentArr[i].yearOFAdmiss)!=1)
        {
            rewinf(stdin);
            puts("error: incorrect value");
        }

        puts("enter student grades");
        printf("phisics:");
        while(scanf("%d", studentArr[i].grades.phisics)!=1)
        {
            rewinf(stdin);
            puts("error: incorrect value");
        }
        printf("math:");
        while(scanf("%d", studentArr[i].grades.math)!=1)
        {
            rewinf(stdin);
            puts("error: incorrect value");
        }
        printf("programming:");
        while(scanf("%d", studentArr[i].grades.prog)!=1)
        {
            rewinf(stdin);
            puts("error: incorrect value");
        }
        printf("history:");
        while(scanf("%d", studentArr[i].grades.history)!=1)
        {
            rewinf(stdin);
            puts("error: incorrect value");
        }
    }
    return studentArr;
}

int writeData(FILE* file, struct student* studentData, unsigned int size)
{
    if(studentData == NULL)
    {
        puts("error: can't read data");
        return -1;
    }

    struct student tmp;
    for(int i = 1; i < size; i++)
    {
        for(int j = 1; j < size; j++)
        {
            if(studentData[j].uid > studentData[j-1].uid)
            {
                tmp = studentData[j];
                studentData[j] = studentData[j-1];
                studentData[j-1] = tmp;
            }
        }
    }

    for(int i = 0; i < size; i++)
    {
        if(fwrite(&(studentData[i]), sizeStudent, 1, file)!=1)
        {
            puts("error: can't write data");
            return -1;
        }
    }
    return 0; 
}

int correctData(FILE* file, unsigned int numToCorrect)
{
    if(fseek(file, numToCorrect*sizeStudent, SEEK_SET)!=0)
    {
        puts("error: can't find the data");
        return -1;
    }
    struct student buff;
    if(fread(&buff, sizeStudent, 1, file)!=1)
    {
        puts("error: can't read data about student");
        return -1;
    }
    printf("");
    return 0;
}
int main()
{
    FILE* datafile = fopen("aip-lab9.dat", "rt+");
    if(datafile == NULL)
    {
        FILE* datafile = fopen("aip-lab9.dat", "wt+");
        if(datafile == NULL)
        {
            puts("error: cant open/create file");
            return 1;
        }
    }
    printf("enter number of students:");
    unsigned int numOfStudents=0;
    while(scanf("%d", &numOfStudents)!= 1)
    {
        rewind(stdin);
        puts("error: incorrect value");
    }
    struct student* studentData = enterData(numOfStudents);


    fclose(datafile);
    return 0;
}