#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int ft_strstr(const char *s1, const char *s2)
{
    int i;

    i = 0;
    if (!s1 || !s2)
        return (0);
    while (s1[i] && s2[i])
    {
        if (s1[i] != s2[i])
            return (0);
        i++;
    }
    if (s1[i] == s2[i])
        return (1);
    return (0);
}

void	put_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		usleep(100000);
		i++;
	}
}

int	main(void)
{
	system("clear");
	printf("      ❤️ ❤️     ❤️ ❤️ \n");
	printf("    ❤️     ❤️ ❤️     ❤️ \n");
	printf("     ❤️     ❤️     ❤️ \n");
	printf("       ❤️       ❤️ \n");
	printf("         ❤️   ❤️ \n");
	printf("           ❤️ \n");
	usleep(1000000);
	char	*str = strdup("\033[0;93m6.Ayımız kutlu olsun BİTANEM 🙃\nBugünün şerefine çıkışta benimle kahve içmeye gelir misin ???\n☕☕☕\n\033[0;96m(evet/hayır/maalesef/çok isterdim ama meşgulüm(😔))\033[0;97m");
	char	*buff = malloc(sizeof(char)*10);
	put_str(str);
	write(1, "\n", 1);
	int	i = 0;
	while (1)
	{
		read(0, buff, 10);
		buff[4]='\0';
		if (ft_strstr(buff, "evet") || ft_strstr(buff, "Evet"))
		{
			put_str("\033[0;97mSeni çooook seviyoruuuum 💗🤍💖\n");
			break;
		}
		else
			put_str("\033[0;95mLütfen tekrar düşün 🥺\n\033[0;97m");
		i++;
	}
	put_str("\033[0;93m\nSeni bunun için kırmak istememiştim.\nSadece hemen göstermek istedim.\n\nBiricik sevgilin...\n🤍🤍🤍🤍\n");
	while(1);
}
