/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 16:50:33 by rcollas           #+#    #+#             */
/*   Updated: 2021/05/24 16:50:34 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const char	*source;
	char		*destination;

	source = (const char *)src;
	destination = dest;
	if (!dest && !src)
		return (NULL);
	if (destination < source)
	{
		while (n--)
			*destination++ = *source++;
	}
	else
	{
		while (n--)
			destination[n] = source[n];
	}
	return (dest);
}
