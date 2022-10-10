#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>

struct File
{
    int fd;
    char *path;
};


typedef struct Node
{
    struct Node *l, *r;
    struct File f;
} Node;


int
set_reg_file(const char *path, struct stat *stb)
{
    if (S_ISREG(stb->st_mode)) {
        return 0;
    } else {
        char buf[PATH_MAX + 1];
        if (readlink(path, buf, PATH_MAX + 1) == -1 || lstat(buf, stb)) {
            return -1;
        } else {
            return set_reg_file(buf, stb);
        }
    }
}

int
same_file(const char *path1, const char *path2)
{
    struct stat stb1, stb2;
    if (lstat(path1, &stb1) == -1 || lstat(path2, &stb2) == -1) {
        return -1;
    } else if (S_ISREG(stb1.st_mode) && S_ISREG(stb2.st_mode)) {
        return stb1.st_ino == stb2.st_ino;
    } else if (S_ISREG(stb1.st_mode) && S_ISLNK(stb2.st_mode)) {
        if (set_reg_file(path1, &stb1) == -1) {
            return -1;
        } else {
            return stb1.st_ino == stb2.st_ino;
        }
    } else if (S_ISLNK(stb1.st_mode) && S_ISREG(stb2.st_mode)) {
        if (set_reg_file(path2, &stb2) == -1) {
            return -1;
        } else {
            return stb1.st_ino == stb2.st_ino;
        }
    } else if (S_ISLNK(stb1.st_mode) && S_ISLNK(stb2.st_mode)) {
        if (set_reg_file(path1, &stb1) == -1 || set_reg_file(path2, &stb2) == -1) {
            return -1;
        } else {
            return stb1.st_ino == stb2.st_ino;
        }
    }
    return 0;
}

void
add(Node *this, char *path)
{
    if (same_file(path, this->f.path) == 1) {
        if (strcmp(path, this->f.path) > 0) {
            this->f.path = path;
            this->f.fd = open(path, O_RDONLY, 0666);
        }
    } else if (strcmp(path, this->f.path) > 0) {
        if (this->r == NULL) {
            add(this->r, path);
        } else {
            this->r = calloc(1, sizeof(Node));
            this->r->f = (struct File) { .fd = open(path, O_RDONLY, 0666), .path = path };
            this->r->r = NULL;
            this->r->l = NULL;
        }
    } else {
        if (this->l == NULL) {
            this->l = calloc(1, sizeof(Node));
            this->l->f = (struct File) { .fd = open(path, O_RDONLY, 0666), .path = path };
            this->l->r = NULL;
            this->l->l = NULL;
        } else {
            add(this->l, path);
        }
    }
}

void
print(Node *this)
{
    if (this->l != NULL) {
        print(this->l);
    }
    printf("%s\n", this->f.path);
    if (this->r != NULL) {
        print(this->r);
    }
}

int
main(int argc, char *argv[])
{
    if (argc <= 1) {
        return EXIT_SUCCESS;
    } else {
        Node nd = (Node) { .l = NULL, .r = NULL, .f = (struct File) { .path = argv[1], .fd = open(argv[1], O_RDONLY,
                                                                                                  0666) }};
        for (int i = 2; i < argc; ++i) {
            add(&nd, argv[i]);
        }
        print(&nd);
    }
}