#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <errno.h>

struct Elem
{
    struct Elem *next;
    char *str;
};

struct Elem *
dup_elem(struct Elem *head)
{
    struct Elem *res = head;
    struct Elem *prev = NULL;
    while (head != NULL) {
        char *eptr = NULL;
        errno = 0;
        long buf = strtol(head->str, &eptr, 10);
        if (*eptr || errno || eptr == head->str || buf != (int) buf || buf == INT_MAX) {

        } else {
            struct Elem *new = malloc(sizeof(struct Elem));
            new->next = head;
            asprintf(&new->str, "%ld", buf + 1);
            if (prev == NULL) {
                res = new;
            } else {
                prev->next = new;
            }
        }
        prev = head;
        head = head->next;
    }
    return res;
}