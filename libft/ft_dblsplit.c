/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dblsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:30:00 by mkardes           #+#    #+#             */
/*   Updated: 2022/10/01 18:00:27 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	rest_ft_word(int *a, int *i, char *str)
{
	str[0] = '$';
	(*i)++;
	*a = 1;
}

static char	*ft_word(char *str, const char *s1, t_chars ch)
{
	int	son;
	int	wordlen;
	int	i;
	int	a;

	son = ch.son;
	wordlen = ch.wordlen;
	i = 0;
	a = 0;
	if (ch.first == '$')
		rest_ft_word(&a, &i, str);
	else
	{
		str[wordlen] = ' ';
		str[wordlen + 1] = '\0';
	}
	while (i - a < wordlen)
	{
		str[i] = s1[son - wordlen + i - a];
		i++;
	}
	if (a == 1)
		str[i] = '\0';
	return (str);
}

static char	**ft_place(char **str, char const *s1, t_chars ch, int wordcount)
{
	int		word;

	word = 0;
	ch.son = 0;
	ch.wordlen = 0;
	while (word < wordcount)
	{
		while (s1[ch.son] != '\0' && (s1[ch.son] == ch.a || s1[ch.son] == ch.b))
			ch.son++;
		ch.first = s1[ch.son - 1];
		while (s1[ch.son] != '\0' && s1[ch.son] != ch.a && s1[ch.son] != ch.b)
		{
			ch.wordlen++;
			ch.son++;
		}
		str[word] = (char *)malloc(sizeof(char) * ch.wordlen + 2);
		ft_word(str[word], s1, ch);
		ch.wordlen = 0;
		word++;
	}
	str[word] = 0;
	return (str);
}

static int	strcount(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			i++;
		else
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (count);
}

char	**ft_dblsplit(const char *s, char c, char a)
{
	char	**str;
	int		wrdcnt;
	t_chars	chrs;

	chrs.a = c;
	chrs.b = a;
	if (!s)
		return (0);
	wrdcnt = strcount(s, c);
	wrdcnt += strcount(s, a);
	str = (char **)malloc(sizeof(char *) * wrdcnt + 1);
	if (!str)
		return (0);
	ft_place(str, s, chrs, wrdcnt);
	return (str);
}
