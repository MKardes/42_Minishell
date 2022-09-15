#include "minishell.h"

void	printer(void)
{
	int a = 0, b, c;
    printf("p_cnt: %d\n", shell_g.p_cnt);
    while (a <= shell_g.p_cnt)
    {
        printf("%d. word count: %d", a, shell_g.in_pipe[a]);
        b = 0;
        while (b < shell_g.in_pipe[a])
        {
            printf("[%s] ", shell_g.all[a][b]);
            b++;
        }
        a++;
        printf("\n");
    }
}
