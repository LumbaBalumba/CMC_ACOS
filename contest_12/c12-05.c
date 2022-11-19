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
    struct stat stb;
    char script_name[PATH_MAX + 20];
    do {
        char filename[PATH_MAX + 1];
        snprintf(filename, PATH_MAX, "%llu", hash());
        snprintf(script_name, PATH_MAX + 20, "%s/script_12_5_%s", dir, filename);
    } while (stat(script_name, &stb) >= 0);


    char c_name[PATH_MAX + 20];
    do {
        char filename[PATH_MAX + 1];
        snprintf(filename, PATH_MAX, "%llu", hash());
        snprintf(c_name, PATH_MAX + 20, "%s/c_12_5_%s.c", dir, filename);
    } while (stat(c_name, &stb) >= 0);


    char exec_name[PATH_MAX + 20];
    do {
        char filename[PATH_MAX + 1];
        snprintf(filename, PATH_MAX, "%llu", hash());
        snprintf(exec_name, PATH_MAX + 20, "%s/exec_12_5_%s", dir, filename);
    } while (stat(exec_name, &stb) >= 0);


    int c_fd = open(c_name, O_WRONLY | O_CREAT, 0700);
    dprintf(c_fd, ""
                    "#include <stdio.h>\n"
                    "#include <stdlib.h>\n"
                    "#include <unistd.h>\n"
                    "int main()\n"
                    "{\n"
                    "    char reject[] = \"reject\";\n"
                    "    char summon[] = \"summon\";\n"
                    "    char disqualify[] = \"disqualify\";\n"
                    "    int x;\n"
                    "    if (scanf(\"%%d\", &x) == 1){\n"
                    "        printf(\"%%s\\n\", %s);\n"
                    "        exit(0);\n"
                    "    } else {\n"
                    "        exit(1);\n"
                    "    }\n"
                    "}\n", argv[1]);
    close(c_fd);
    int script_fd = open(script_name, O_WRONLY | O_CREAT, 0700);
    dprintf(script_fd, ""
                        "#!/bin/bash\n"
                        "gcc -o %s %s\n"
                        "e_status=0\n"
                        "for (( ; ; ))\n"
                        "do\n"
                        "    %s\n"
                        "    e_status=$?\n"
                        "    if (($e_status!=0))\n"
                        "    then\n"
                        "        break\n"
                        "    fi\n"
                        "done\n"
                        "rm %s %s %s\n",
            exec_name, c_name, exec_name, exec_name, c_name, script_name);
    close(script_fd);
    execlp(script_name, script_name, NULL);
}