#include "printf.h"
#include "parser.h"

int main(int argc, char const *argv[],char const *envp[])
{
    (void) argc;
    (void) argv;
    char **paths = paths_formatter(envp);
    int i = 0;
    if(paths)
    {
        while(paths[i])
        {
            ft_printf("%s\n",paths[i]);
            i++;
        }
    }
    free_path(paths);
    return 0;
}
