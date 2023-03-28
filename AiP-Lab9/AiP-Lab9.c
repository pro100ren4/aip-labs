#include <stdio.h>
#include <stdlib.h>
#include <conio.h>


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
        while(scanf("%d", &studentArr[i].sequenceNum)!=1)
        {
            rewind(stdin);
            puts("error: incorrect value");
        }

        printf("enter uid:");
        while(scanf("%d", &studentArr[i].uid)!=1)
        {
            rewind(stdin);
            puts("error: incorrect value");
        }

        printf("enter surname:");
        while(scanf("%s", &studentArr[i].surname)!=1)
        {
            rewind(stdin);
            puts("error: incorrect value");
        }

        printf("enter name:");
        while(scanf("%s", &studentArr[i].name)!=1)
        {
            rewind(stdin);
            puts("error: incorrect value");
        }

        printf("enter year of birth:");
        while(scanf("%d", &studentArr[i].yearOfBirth)!=1)
        {
            rewind(stdin);
            puts("error: incorrect value");
        }

        printf("enter year of admission:");
        while(scanf("%d", &studentArr[i].yearOFAdmiss)!=1)
        {
            rewind(stdin);
            puts("error: incorrect value");
        }

        puts("enter student grades");
        printf("phisics:");
        while(scanf("%f", &studentArr[i].grades.phisics)!=1)
        {
            rewind(stdin);
            puts("error: incorrect value");
        }
        printf("math:");
        while(scanf("%f", &studentArr[i].grades.math)!=1)
        {
            rewind(stdin);
            puts("error: incorrect value");
        }
        printf("programming:");
        while(scanf("%f", &studentArr[i].grades.prog)!=1)
        {
            rewind(stdin);
            puts("error: incorrect value");
        }
        printf("history:");
        while(scanf("%f", &studentArr[i].grades.history)!=1)
        {
            rewind(stdin);
            puts("error: incorrect value");
        }
    }
    return studentArr;
}

int printFile(FILE* file)
{
    rewind(file);
    struct student tmp;
    if(file == NULL)
    {
        puts("error: can't find data");
        return -1;
    }
    while(fread(&tmp, sizeStudent, 1, file)==1)
    {
        printf("\nUID:%d SeqNum:%d %s %s birth:%d admission:%d\nGrades>> phis:%.2f math:%.2f prog:%.2f his:%.2f\n", tmp.uid, tmp.sequenceNum, tmp.surname, tmp.name, tmp.yearOfBirth, tmp.yearOFAdmiss, tmp.grades.phisics, tmp.grades.math, tmp.grades.prog, tmp.grades.history);
    }
    return 0;
}

int sortFile(FILE* file)
{
    struct student tmp1, tmp2;
    fseek(file, 0, SEEK_END);
    long fileLength = ftell(file)/sizeStudent;
    rewind(file);
    if(file == NULL)
        return -1;
    for(long i = fileLength-1; i >= 0; i--)
    {
        for(long j = 0; j < i-1; j++)
        {
            fseek(file, j*sizeStudent, SEEK_SET);
            fread(&tmp1, sizeStudent, 1, file);
            fread(&tmp2, sizeStudent, 1, file);
            if(tmp1.uid > tmp2.uid)
            {
                fseek(file, (-2)*sizeStudent, SEEK_CUR);
                fwrite(&tmp2, sizeStudent, 1, file);
                fwrite(&tmp1, sizeStudent, 1, file);
            }
        }
    }

    return 0;
}

int writeData(FILE* file, struct student* studentData, unsigned int size)
{
    fseek(file, 0, SEEK_END);
    if(studentData == NULL)
    {
        puts("error: can't read data");
        return -1;
    }

    for(int i = 0; i < size; i++)
    {
        if(fwrite(&(studentData[i]), sizeStudent, 1, file)!=1)
        {
            puts("error: can't write data");
            return -1;
        }
    }
    if(sortFile(file)<0)
        puts("error: file sort failed"); 
    return 0; 
}

int correctData(FILE* file, unsigned int numToCorrect)
{
    struct student tmp;
    if(file == NULL)
    {
        puts("error: can't find data");
        return -1;
    }
    rewind(file);
    int succesFound = 0;
    while(fread(&tmp, sizeStudent, 1, file)==1)
    {
        if(tmp.uid == numToCorrect)
        {   
            fseek(file, (-1)*sizeStudent, SEEK_CUR); 
            succesFound = 1;
            break;
        } 
    }
    if(!succesFound)
    {
        puts("error: can't find student");
        return -1;
    }
    puts("\tCorrecting Data");
    printf("\nUID:%d SeqNum%d %s %s birth:%d admission:%d\nGrades>>phis:%.2f math:%.2f prog:%.2f his:%.2f\n", tmp.uid, tmp.sequenceNum, tmp.surname, tmp.name, tmp.yearOfBirth, tmp.yearOFAdmiss, tmp.grades.phisics, tmp.grades.math, tmp.grades.prog, tmp.grades.history);
    puts("enter new stident data:");

    printf("enter sequence number:");
    while(scanf("%d", &tmp.sequenceNum)!=1)
    {
        rewind(stdin);
        puts("error: incorrect value");
    }

    printf("enter uid:");
    while(scanf("%d", &tmp.uid)!=1)
    {
        rewind(stdin);
        puts("error: incorrect value");
    }

    printf("enter surname:");
    while(scanf("%s", &tmp.surname)!=1)
    {
        rewind(stdin);
        puts("error: incorrect value");
    }

    printf("enter name:");
    while(scanf("%s", &tmp.name)!=1)
    {
        rewind(stdin);
        puts("error: incorrect value");
    }

    printf("enter year of birth:");
    while(scanf("%d", &tmp.yearOfBirth)!=1)
    {
        rewind(stdin);
        puts("error: incorrect value");
    }

    printf("enter year of admission:");
    while(scanf("%d", &tmp.yearOFAdmiss)!=1)
    {
        rewind(stdin);
        puts("error: incorrect value");
    }

    puts("enter student grades");
    printf("phisics:");
    while(scanf("%f", &tmp.grades.phisics)!=1)
    {
        rewind(stdin);
        puts("error: incorrect value");
    }
    printf("math:");
    while(scanf("%f", &tmp.grades.math)!=1)
    {
        rewind(stdin);
        puts("error: incorrect value");
    }
    printf("programming:");
    while(scanf("%f", &tmp.grades.prog)!=1)
    {
        rewind(stdin);
        puts("error: incorrect value");
    }
    printf("history:");
    while(scanf("%f", &tmp.grades.history)!=1)
    {
        rewind(stdin);
        puts("error: incorrect value");
    }
    if(fwrite(&tmp, sizeStudent, 1, file)!=1)
    {
        puts("error: canr't write changed data");
        return -1;
    }

    return 0; 
}

int printDataAbouAwesomeStudents(FILE* file)
{
    rewind(file);
    struct student tmp;
    if(file == NULL)
    {
        puts("error: can't find data");
        return -1;
    }
    puts("\tAwesome Students");
    while(fread(&tmp, sizeStudent, 1, file)==1)
    {
        if(tmp.grades.phisics == 5.00f && tmp.grades.math == 5.00f && tmp.grades.prog == 5.00f && tmp.grades.history == 5.00f)
            printf("\nUID:%d SeqNum:%d %s %s birth:%d admission:%d\nGrades>>phis:%.2f math:%.2f prog:%.2f his:%.2f\n", tmp.uid, tmp.sequenceNum, tmp.surname, tmp.name, tmp.yearOfBirth, tmp.yearOFAdmiss, tmp.grades.phisics, tmp.grades.math, tmp.grades.prog, tmp.grades.history);
    }
    return 0;
}

int main()
{
    FILE* datafile = fopen("aip-lab9.dat", "rb+");
    if(datafile == NULL)
    {
        puts("create new file");
        FILE* datafile = fopen("aip-lab9.dat", "wb+");
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
    writeData(datafile, studentData, numOfStudents);
    free(studentData);
    getch();
    int action, run = 1;
    while(run)
    {
        system("cls");
        puts("1 - enter students to file");
        puts("2 - print students to screen");
        puts("3 - correct data about student(uid)");
        puts("4 - print data about awesome students");
        puts("5 - exit");
        printf("Enter the action:");
        scanf("%d", &action);
        switch (action)
        {
        case 1:
            printf("enter number of students:");
            unsigned int numOfStudents=0;
            while(scanf("%d", &numOfStudents)!= 1)
            {
                rewind(stdin);
                puts("error: incorrect value");
            }
            struct student* studentData = enterData(numOfStudents);
            writeData(datafile, studentData, numOfStudents);
            free(studentData);
            break;
        
        case 2:
            printFile(datafile);
            break;

        case 3:
            unsigned int numToCorrect;
            while(scanf("%d", &numToCorrect)!=1)
            {
                rewind(stdin);
                puts("error: incorrect value");
            }
            correctData(datafile, numToCorrect);
            break;

        case 4:
            printDataAbouAwesomeStudents(datafile);
            break;

        case 5:
            fclose(datafile);
            run = 0;
            break;

        default:
            puts("error: incorrect value");
            break;
        }
        puts("press <Enter>");
        getch();
    }
    fclose(datafile);
    return 0;
}