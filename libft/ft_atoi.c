/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 16:46:33 by rcollas           #+#    #+#             */
/*   Updated: 2021/05/26 12:14:37 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static	int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static	int	ft_is_space(char c)
{
	if (c == '\f' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int						sign;
	unsigned long long int	nb;

	nb = 0;
	sign = 1;
	while (ft_is_space(*nptr))
		nptr++;
	if (*nptr == '-')
	{
		sign *= -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (ft_isdigit(*nptr))
	{
		nb = nb * 10 + *nptr - 48;
		nptr++;
	}
	if (nb > 9223372036854775807 && sign == 1)
		return (-1);
	else if (nb > 9223372036854775807 && sign == -1)
		return (0);
	return (nb * sign);
}
