#include "minishell.h"

void	printer(void)
{
	int a = 0, b, c;
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
