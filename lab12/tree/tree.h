#pragma once
#ifndef _TREE_H_
#define _TREE_H_

#include "student.h"
#include <stdio.h>
#include <stdlib.h>

struct node
{
    struct student inf;
    struct node* l;
    struct node* r;
};

extern const int node_size;

struct node* add_to_tree(struct node* top, struct student new_node);
struct node* minValue(struct node* top);
struct node* del_from_tree(struct node* top, long uid);
struct node* create_tree(struct node* top, unsigned int num_of_nodes);
void delete_tree(struct node* top);
int is_leaf(struct node* top);
void print_tree(struct node* top);
void print_leafs(struct node* top);
void struct_map(struct node* top, unsigned int offset);
int student_num(struct node* top);
float prog_sum(struct node* top);
float prog_average(struct node* top);

#endif