#pragma once
#ifndef _LIST_H_
#define _LIST_H_

#include "student.h"
#include <stdio.h>
#include <stdlib.h>

struct list
{
    struct student data;
    struct list* next;
};

extern const int list_size;

struct list* create_list(unsigned int list_length);
void delete_list(struct list* beg);
struct list* add_to_list(struct list* beg, unsigned long uid, struct student new_student);
struct list* add_two_before_last(struct list* beg, struct student new_student1, struct student new_student2);
struct list* del_from_list(struct list* beg, unsigned long uid);
int print_list(struct list* beg);
int print_awesome_students(struct list* beg);


#endif