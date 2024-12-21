#include "render.h"
#include "constants.h"
#include "errors.h"
#include "stdlib.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

static int open_img(const char *img)
{
    pid_t pid = fork();
    if (pid == -1)
        return ERR_FORK;

    if (pid == 0)
    {
        int stdout_file = open("/dev/null", O_RDWR);
        if (dup2(stdout_file, STDERR_FILENO) == -1) // redirect fork'ed process stderr to /dev/null
            goto err;
        execlp("open", "open", img, NULL);

        err:
        close(stdout_file);

        perror("execlp");
        _exit(EXIT_FAILURE);
    }
    else
    {
        int ret_code;
        waitpid(pid, &ret_code, 0);
        if (WEXITSTATUS(ret_code) != 0)
            return ERR_FORK;
    }
    return ERR_OK;
}

int render_graphviz(const char *gp_file, const char *img_file)
{
    pid_t pid = fork();
    if (pid == -1)
        return ERR_FORK;

    if (pid == 0)
    {
        execlp("dot", "dot", "-Tpng", gp_file, "-o", img_file, NULL);
        perror("execlp");
        _exit(EXIT_FAILURE);
    }
    else
    {
        int ret_code;
        waitpid(pid, &ret_code, 0);
        if (WEXITSTATUS(ret_code) != 0)
            return ERR_FORK;
    }
    return open_img(img_file);
}
