#pragma once
#ifndef _TREE_FILE_H_
#define _TREE_FILE_H_

#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#include "tree.h"

void write_file(struct node* top, FILE* file);
struct node* read_file(struct node* top, FILE* file);

#endif