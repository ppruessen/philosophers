/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschiman <mschiman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 12:51:30 by mschiman          #+#    #+#             */
/*   Updated: 2022/08/14 12:53:01 by mschiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_status(t_var *var, t_philo *philo)
{
	pthread_mutex_lock(&var->lock_died);
	if (var->died != 0)
	{
		pthread_mutex_unlock(&var->lock_died);
		return (-1);
	}
	pthread_mutex_unlock(&var->lock_died);
	if (pp_current_time() > philo->time_to_die)
	{
		print_status(var, philo, "died");
		pthread_mutex_lock(&var->lock_died);
		var->died++;
		pthread_mutex_unlock(&var->lock_died);
		return (-1);
	}
	return (0);
}
