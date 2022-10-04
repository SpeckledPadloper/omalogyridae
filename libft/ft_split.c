/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/02 17:41:54 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/07/21 13:53:13 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static unsigned int	wordcount(char const *s, char c)
{
	int		wordcnt;
	size_t	offset;

	wordcnt = 0;
	offset = 1;
	while (offset <= ft_strlen((char *)s))
	{
		if (s[offset] == c && s[offset - 1] != c)
			wordcnt++;
		else if (s[offset] == '\0' && s[offset - 1] != c)
			wordcnt++;
		offset++;
	}
	return (wordcnt);
}

static unsigned int	wordstart(char const *s, char c, int n)
{
	int				wordcnt;
	size_t			offset;

	wordcnt = 0;
	offset = 0;
	while (((s[offset] != '\0') && (wordcnt < n)))
	{
		if (offset == 0 && s[offset] != c)
			wordcnt++;
		else if (s[offset] != c && s[offset - 1] == c)
			wordcnt++;
		offset++;
	}
	return (offset - 1);
}

static unsigned int	wordlen(char const *s, unsigned int start, char c)
{
	int	len;

	len = 0;
	while (s[start + len] != c && s[start + len] != '\0')
		len++;
	return (len);
}

static void	freesplit(char **split, int offset)
{
	while (offset >= 0)
	{
		free(split[offset]);
		offset--;
	}
	free(split);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	len;
	unsigned int	offset;
	unsigned int	start;
	char			**split;

	offset = 0;
	if (s == NULL)
		return (NULL);
	split = (char **)malloc((wordcount(s, c) + 1) * sizeof(char *));
	if (split == NULL)
		return (NULL);
	while (offset < wordcount(s, c))
	{
		start = wordstart(s, c, offset + 1);
		len = wordlen(s, start, c);
		split[offset] = ft_substr(s, start, len);
		if (split[offset] == NULL)
		{
			freesplit(split, offset);
			return (NULL);
		}
		offset++;
	}
	split[wordcount(s, c)] = NULL;
	return (split);
}
