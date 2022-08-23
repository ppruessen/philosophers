/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprussen <pprussen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 19:50:20 by pprussen          #+#    #+#             */
/*   Updated: 2022/08/23 13:22:27 by pprussen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
*	DESCRIPTION
*	Outputs the integer ’n’ to the given file descriptor.
*	RETURN VALUES
*	None.
*/

#include "philosophers.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

static int	ft_get_divisor(int n)
{
	int	divisor;

	if (n == 0)
		return (1);
	divisor = 1000000000;
	while (n / divisor == 0)
		divisor /= 10;
	return (divisor);
}

void	ft_putnbr_fd(int n, int fd)
{
	int			divider;
	long int	temp;
	long int	result;

	temp = n;
	if (temp < 0)
	{
		write(fd, "-", 1);
		temp = temp * -1;
	}
	divider = ft_get_divisor(temp);
	while (divider != 1)
	{
		result = temp / divider;
		ft_putchar_fd((result + '0'), fd);
		temp = temp - (result * divider);
		divider /= 10;
	}
	ft_putchar_fd((temp + '0'), fd);
}
