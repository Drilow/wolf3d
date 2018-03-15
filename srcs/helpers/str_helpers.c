/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 15:15:03 by adleau            #+#    #+#             */
/*   Updated: 2018/03/15 15:15:07 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <helpers/str_helpers.h>

char			*trimquote(char *s)
{
	char		*dst;
	int			i;

	i = -1;
	if (!(dst = (char*)malloc(sizeof(char) * ft_strlen(s))))
		return (NULL);
	while (s[++i] && s[i] != '\"')
		dst[i] = s[i];
	dst[i] = '\0';
	return (dst);
}

void			remove_spaces(char *src, char *dst)
{
	int			i;
	int			j;

	i = -1;
	j = -1;
	while (src[++i])
	{
		if (src[i] != ' ')
			dst[++j] = src[i];
	}
	dst[j + 1] = '\0';
}
