#include "tree.h"

const int node_size = sizeof(struct node);

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