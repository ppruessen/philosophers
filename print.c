/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschiman <mschiman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 18:35:42 by mschiman          #+#    #+#             */
/*   Updated: 2022/08/07 20:02:59 by mschiman         ###   ########.fr       */
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
	pthread_mutex_lock(&var->lock_died);
	if (var->died == 0)
	{
		pthread_mutex_lock(&var->lock_output);
		printf("%.3ld %d %s\n",
			pp_time_delta(philo->starttime), philo->id + 1, msg);
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
