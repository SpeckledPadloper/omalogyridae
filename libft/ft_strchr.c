/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 16:11:52 by mteerlin      #+#    #+#                 */
/*   Updated: 2020/10/27 17:43:12 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	int		offset;
	char	i;

	offset = 0;
	i = c;
	while (s[offset] != '\0')
	{
		if (i == s[offset])
			return ((char *)&s[offset]);
		offset++;
	}
	if (i == '\0')
		return ((char *)&s[offset]);
	return (0);
}
