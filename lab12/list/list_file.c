#include "list_file.h"

// int list_size = sizeof(struct list);
//int student_size = sizeof(struct student);

int sort_file(FILE* file)
{
    struct student tmp1, tmp2;
    fseek(file, 0, SEEK_END);
    long fileLength = ftell(file)/student_size;
    rewind(file);
    if(file == NULL)
        return -1;
    for(int i = 0; i < fileLength-1; i++)
    {
        for(int j = 0; j < fileLength-1; j++)
        {
            fseek(file, j*student_size, SEEK_SET);
            fread(&tmp1, student_size, 1, file);
            fread(&tmp2, student_size, 1, file);

            if(tmp1.uid > tmp2.uid)
            {
                fseek(file, (-2)*student_size, SEEK_CUR);
                fwrite(&tmp2, student_size, 1, file);
                fwrite(&tmp1, student_size, 1, file);
            }
        }
    }

    return 0;
}

int write_file(FILE* file, struct list* beg)
{
    if(beg == NULL)
    {
        puts("warn<write_file>: The list is empty");
        return 0;
    }
    while(beg != NULL)
    {
        if(fwrite(&(beg->data), student_size, 1, file)!= 1)
        {
            puts("error<write_file>: Can't write file");
            return -1;
        }
        beg = beg->next;
    }
    sort_file(file);
    return 0;
}

//<beg> must be empty 
struct list* read_file(FILE* file, struct list* beg)
{
    if(!file)
    {
        puts("error<read_file>: No file");
        return NULL;
    }
    if(beg)
    {
        puts("error<read_file>: The list is not empty");
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long file_length = ftell(file)/student_size;
    struct list* curr = NULL;
    struct student tmp;
    rewind(file);
    for(int i = 0;i < file_length; i++)
    {
        struct list* node = (struct list*)malloc(list_size);
        fread(&tmp, student_size, 1, file);
        node->data = tmp;
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