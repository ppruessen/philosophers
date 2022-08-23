/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pprussen <pprussen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 18:35:42 by mschiman          #+#    #+#             */
/*   Updated: 2022/08/23 13:23:16 by pprussen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_error(char *error_msg)
{
	printf("Error: %s\n", error_msg);
	return (-1);
}

void	print_status(t_var *var, t_philo *philo, char *msg)
{
	int	i;
	(void)philo;
	pthread_mutex_lock(&var->lock_died);
	if (var->died == 0)
	{
		pthread_mutex_lock(&var->lock_output);
//		printf("%.3ld %d %s\n",
//			pp_time_delta(philo->starttime), philo->id + 1, msg);
		ft_putnbr_fd(pp_time_delta(philo->starttime), 1);
		write(1, "\t", 1);
		ft_putnbr_fd(philo->id + 1, 1);
		write(1, "\t", 1);
		i = 0;
		while (msg[i] != '\0')
			i++;
		write(1, msg, i);
		write(1, "\n", 1);
		pthread_mutex_unlock(&var->lock_output);
		pthread_mutex_unlock(&var->lock_died);
	}
	else
		pthread_mutex_unlock(&var->lock_died);
}

void	print_meal_count(t_var *var, t_philo *philo)
{
	pthread_mutex_lock(&var->lock_died);
	if (var->died == 0)
	{
		pthread_mutex_lock(&var->lock_output);
		printf("%.3ld\tID: %d\thas eaten %d times\n",
			pp_time_delta(philo->starttime), philo->id + 1, philo->nb_eaten);
		pthread_mutex_unlock(&var->lock_output);
	}
	pthread_mutex_unlock(&var->lock_died);
}
