/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 17:36:06 by mteerlin      #+#    #+#                 */
/*   Updated: 2020/10/27 20:02:29 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int		offset;
	char	i;

	offset = 0;
	i = c;
	while (s[offset] != '\0')
		offset++;
	while (offset >= 0)
	{
		if (i == s[offset])
			return ((char *)&s[offset]);
		offset--;
	}
	return (0);
}
