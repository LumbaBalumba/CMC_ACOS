#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>

unsigned long long
hash()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((unsigned long long) tv.tv_usec + 1000000 * (unsigned long long) tv.tv_sec);
}


int
main(int argc, char *argv[], char *envp[])
{
    char *dir;
    if (!(dir = getenv("XDG_RUNTIME_DIR")) && !(dir = getenv("TMPDIR"))) {
        dir = "/tmp";
    }
    char name[PATH_MAX + 15];
    struct stat stb;
    do {
        char filename[PATH_MAX + 1];
        snprintf(filename, PATH_MAX, "%llu", hash());
        snprintf(name, PATH_MAX + 15, "%s/12_4_%s", dir, filename);
    } while (stat(name, &stb) >= 0);
    int script = open(name, O_CREAT | O_WRONLY, 0700);
    const char script_init[] =
            "#!/bin/python3\nfrom os import remove as rm\nimport sys\nsys.set_int_max_str_digits(1000000)\nprint(";
    write(script, script_init, sizeof(script_init) - 1);
    write(script, argv[1], strlen(argv[1]));
    for (int i = 2; i < argc; ++i) {
        write(script, "*", sizeof((char) '*'));
        write(script, argv[i], strlen(argv[i]));
    }
    write(script, ")", sizeof((char) ')'));
    const char script_end[] = "\nrm(\"";
    write(script, script_end, sizeof(script_end) - 1);
    write(script, name, strlen(name));
    write(script, "\"", sizeof((char) '\"'));
    write(script, ")", sizeof((char) ')'));
    close(script);
    chmod(name, 0700);
    execlp(name, name, NULL);
}