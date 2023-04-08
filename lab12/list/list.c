#include "list.h"

const int list_size = sizeof(struct list);

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