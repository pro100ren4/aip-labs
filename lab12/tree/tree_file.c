#include "tree_file.h"

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