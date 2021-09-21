/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 16:48:20 by rcollas           #+#    #+#             */
/*   Updated: 2021/05/25 18:28:30 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_intlen(long int nb)
{
	long int	i;

	i = 0;
	if (nb == 0)
		i++;
	if (nb < 0)
	{
		i++;
		nb *= -1;
	}
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int			charlen;
	char		*nb;
	long int	num;

	num = n;
	charlen = ft_intlen(n);
	if (n < 0)
		num *= -1;
	nb = (char *)malloc(sizeof(*nb) * charlen + 1);
	if (!nb)
		return (NULL);
	if (n == 0)
		*nb = '0';
	nb[charlen] = 0;
	charlen--;
	while (num > 0)
	{
		nb[charlen--] = num % 10 + 48;
		num /= 10;
	}
	if (n < 0)
		nb[charlen] = '-';
	return (nb);
}
