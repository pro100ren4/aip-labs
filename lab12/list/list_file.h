#pragma once
#ifndef _LIST_FILE_H_
#define _LIST_FILE_H_

#include "list.h"
#include "student.h"
#include <stdio.h>
#include <stdlib.h>

int sort_file(FILE* file);
int write_file(FILE* file, struct list* beg);
struct list* read_file(FILE* file, struct list* beg);

#endif