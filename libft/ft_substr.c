/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 16:53:16 by rcollas           #+#    #+#             */
/*   Updated: 2021/05/25 17:55:59 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char			*d;
	unsigned int	i;

	if (!s)
		return (NULL);
	if (len > ft_strlen(s))
		d = malloc(sizeof(char) * (ft_strlen(s) + 1));
	else
		d = malloc(sizeof(char) * (len + 1));
	if (!d)
		return (NULL);
	i = 0;
	if (start < ft_strlen(s))
	{
		while (s[start + i] && i < len)
		{
			d[i] = s[start + i];
			i++;
		}
		d[i] = 0;
	}
	else
		d[0] = 0;
	return (d);
}
