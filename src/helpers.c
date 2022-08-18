/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschiman <mschiman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 09:55:39 by pprussen          #+#    #+#             */
/*   Updated: 2022/06/30 16:54:24 by mschiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

/* Function returns the current time in milliseconds since 01.01.1970 */
long	pp_current_time(void)
{
	struct timeval	current_time;
	long			current;

	gettimeofday(&current_time, NULL);
	current = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (current);
}

/* Function calculates the time that passed since var->starttime */
long	pp_time_delta(long timestamp)
{
	long	delta;

	delta = pp_current_time() - timestamp;
	return (delta);
}

/* Function checks for Whitespace characters */
static int	ft_is_whitespace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\r'
		|| c == '\v' || c == '\f')
		return (1);
	return (0);
}

/*
*	isdigit -- decimal-digit character test
*	DESCRIPTION
*	The isdigit() function tests for a decimal digit character.
*	RETURN VALUES
*	The isdigit() function return zero if the character tests 
*	false and return non-zero if the character tests true.
*/
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/*
*	atoi -- convert ASCII string to integer
*	DESCRIPTION
*	The atoi() function converts the initial portion of the string pointed to 
*	by str to int representation.
*/
int	pp_atoi(const char *str)
{
	int			pos_neg;
	long int	result;

	pos_neg = 1;
	result = 0;
	while (ft_is_whitespace(*str) == 1)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			pos_neg = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		result = result * 10 + (*str - 48);
		if (result > 2147483647 && pos_neg == 1)
			return (-1);
		if (result > 2147483648 && pos_neg == -1)
			return (0);
		str++;
	}
	return ((int)result * pos_neg);
}
