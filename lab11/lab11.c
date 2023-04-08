#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct student
{
    unsigned long sequenceNum, uid, yearOfBirth, yearOFAdmiss;
    char surname[40], name[40];
    struct{float phisics, math, prog, history;}grades;
};

struct node
{
    struct student inf;
    struct node* l;
    struct node* r;
};

const int student_size = sizeof(struct student);
const int node_size = sizeof(struct node);

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

struct node* add_to_tree(struct node* top, struct student new_node)
{
    if(!top)
    {
        struct node* tmp = (struct node*)malloc(node_size);
        tmp->inf = new_node;
        tmp->l = tmp->r = NULL;
        return tmp;
    }
    else
    {
        if(top->inf.uid > new_node.uid)
            top->l = add_to_tree(top->l, new_node);
        else
            top->r = add_to_tree(top->r, new_node);
    }
    return top;
}

struct node* minValue(struct node* top)
{
    struct node* tmp = top;
    while(tmp && tmp->l)tmp = tmp->l;
    return tmp;
}

struct node* del_from_tree(struct node* top, long uid)
{
    if(!top)
        return NULL;
    if(uid<top->inf.uid)
        top->l = del_from_tree(top->l, uid);
    else if(uid>top->inf.uid)
        top->r = del_from_tree(top->r, uid);
    else
    {
        if(!top->l)
        {
            struct node* tmp = top->r;
            free(top);
            return tmp;
        }
        else if(!top->r)
        {
            struct node* tmp = top->l;
            free(top);
            return tmp;
        }
        struct node* tmp = minValue(top->r);
        top->inf = tmp->inf;
        top->r = del_from_tree(top->r, tmp->inf.uid);
    }
    return top;
}

struct node* create_tree(struct node* top, unsigned int num_of_nodes)
{
    for (size_t i = 0; i < num_of_nodes; i++)
    {
        struct student tmp = enter_student();
        top = add_to_tree(top, tmp);
    }  
    return top;
}

void delete_tree(struct node* top)
{
    if(!top)
        return;
    delete_tree(top->l);
    delete_tree(top->r);
    free(top);
}

int is_leaf(struct node* top)
{
    if(top->l == NULL && top->r == NULL)
        return 1;
    else
        return 0;
}

void print_tree(struct node* top)
{
    if(!top)
        return;
    printf("\nUID:%d SeqNum:%d %s %s birth:%d admission:%d\nGrades>> phis:%.2f math:%.2f prog:%.2f his:%.2f\n", top->inf.uid, top->inf.sequenceNum, top->inf.surname, top->inf.name, top->inf.yearOfBirth, top->inf.yearOFAdmiss, top->inf.grades.phisics, top->inf.grades.math, top->inf.grades.prog, top->inf.grades.history);
    print_tree(top->l);
    print_tree(top->r);
}

void print_leafs(struct node* top)
{
    if(!top)
        return;
    if(is_leaf(top))printf("\nUID:%d SeqNum:%d %s %s birth:%d admission:%d\nGrades>> phis:%.2f math:%.2f prog:%.2f his:%.2f\n", top->inf.uid, top->inf.sequenceNum, top->inf.surname, top->inf.name, top->inf.yearOfBirth, top->inf.yearOFAdmiss, top->inf.grades.phisics, top->inf.grades.math, top->inf.grades.prog, top->inf.grades.history);
    print_tree(top->l);
    print_tree(top->r);
}

void struct_map(struct node* top, unsigned int offset)
{
    if(top)
    {
        offset += 6;
        struct_map(top->r, offset);
        for(int i = 0; i < offset; i++)printf(" ");
        printf("[%d]\n", top->inf.uid);
        struct_map(top->l, offset);
    }
}

int student_num(struct node* top)
{
    if(!top)
        return 0;
    return 1+student_num(top->l)+student_num(top->r);
}

float prog_sum(struct node* top)
{
    if(!top)
        return 0;
    return top->inf.grades.prog + prog_sum(top->l) + prog_sum(top->r);
}

float prog_average(struct node* top)
{
    return prog_sum(top)/student_num(top);
}

void write_file(struct node* top, FILE* file)
{
    if(!top)
        return;
    fseek(file, 0, SEEK_END);
    if(fwrite(&top->inf, student_size, 1, file) != 1)
        return;
    write_file(top->l, file);
    write_file(top->r, file);
}

struct node* read_file(struct node* top, FILE* file)
{
    if(top)
        return top;
    struct student tmp;
    rewind(file);
    while (fread(&tmp, student_size, 1, file)>0)
        top = add_to_tree(top, tmp);
    return top;
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