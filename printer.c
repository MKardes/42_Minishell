#include "minishell.h"

void	printer(void)
{
    int a;
    int b;
    int c;

    a = 0;
    printf("p_cnt: %d\n", g_shell.p_cnt);
    while (a <= g_shell.p_cnt)
    {
        printf("%d. word count: %d", a, g_shell.in_pipe[a]);
        b = 0;
        while (b < g_shell.in_pipe[a])
        {
            printf("[%s] ", g_shell.all[a][b]);
            b++;
        }
        a++;
        printf("\n");
    }
}
