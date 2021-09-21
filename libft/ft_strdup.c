/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 16:51:43 by rcollas           #+#    #+#             */
/*   Updated: 2021/05/24 16:51:43 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static	int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*str;
	int		i;

	i = -1;
	str = (char *)malloc(sizeof(*str) * ft_strlen(s) + 1);
	if (!str)
		return (NULL);
	while (s[++i])
		str[i] = s[i];
	str[i] = 0;
	return (str);
}
