/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschiman <mschiman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 08:29:37 by pprussen          #+#    #+#             */
/*   Updated: 2022/06/27 15:59:56 by mschiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	put_messages(t_var *var, t_philo *philo, char *msg)
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

int	check_status(t_var *var, t_philo *philo)
{
	if (var->nb_philos == 1)
	{
		put_messages(var, philo, "has taken a fork");
		usleep(var->time_to_die * 1000);
		put_messages(var, philo, "died");
		return (-1);
	}
	pthread_mutex_lock(&var->lock_died);
	if (var->died != 0)
	{
		pthread_mutex_unlock(&var->lock_died);
		return (-1);
	}
	pthread_mutex_unlock(&var->lock_died);
//	if (philo->last_meal && pp_time_delta(philo->last_meal) >= var->time_to_die)
	if (philo->last_meal && pp_current_time() > philo->time_to_die)
	{
//		printf("ID: %d, Last Meal: %ld, Current Time: %ld, Time Delta: %ld\n", philo->id +1, philo->last_meal, pp_current_time(), pp_time_delta(philo->last_meal));
		put_messages(var, philo, "died");
		pthread_mutex_lock(&var->lock_died);
		var->died++;
		pthread_mutex_unlock(&var->lock_died);
		return (-1);
	}
	return (0);
}

int	get_forks(t_var *var, t_philo *philo)
{
	if (philo->nb_eaten == var->rounds && var->rounds != 0)
	{
		philo->still_eating = 1;
		return (-1);
	}
	while (1)
	{
		if (check_status(var, philo) == -1)
			return (-1);
		pthread_mutex_lock(&var->lock_forks);
		if (var->forks[philo->nb_left_fork] == 0 &&
			var->forks[philo->nb_right_fork] == 0)
		{
			var->forks[philo->nb_left_fork] = 1;
			var->forks[philo->nb_right_fork] = 1;
			pthread_mutex_unlock(&var->lock_forks);
			put_messages(var, philo, "has taken a fork");
			put_messages(var, philo, "has taken a fork");
			return (0);
		}
		else
		{
			pthread_mutex_unlock(&var->lock_forks);
			usleep(5);
		}
	}
}

void	print_status(t_var *var, t_philo *philo)
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

void eat(t_var *var, t_philo *philo)
{
	//printf("ID: %d, Last Meal: %ld\n", philo->id +1, philo->last_meal);
	put_messages(var, philo, "is eating");
	philo->last_meal = pp_current_time();
	philo->time_to_die = philo->last_meal + var->time_to_die;
	//printf("ID: %d, Last Meal: %ld, Time to die: %ld\n", philo->id +1, philo->last_meal, philo->time_to_die);
	usleep(var->time_to_eat * 1000);
	philo->nb_eaten++;
	print_status(var, philo);
	pthread_mutex_lock(&var->lock_forks);
	var->forks[philo->nb_left_fork] = 0;
	var->forks[philo->nb_right_fork] = 0;
	pthread_mutex_unlock(&var->lock_forks);
	put_messages(var, philo, "is sleeping");
	usleep(var->time_to_sleep * 1000);
	put_messages(var, philo, "is thinking");
}

void	*routine(void *args)
{
	t_philo	*philo;
	t_var	*var;

	philo = (t_philo *)args;
	var = philo->var;
	
	if (philo->nb_eaten == 0)
	{
		philo->last_meal = philo->starttime;
		philo->time_to_die = philo->starttime + var->time_to_die;
	}
//	while (philo->nb_eaten < var->rounds)
	while (philo->still_eating == 0)
	{
		if (get_forks(var, philo) == 0)
			eat(var, philo);
		else
			break;
/*		if (get_forks(var, philo) == 0)
			break;
		eat(var, philo);*/
	}
//	print_status(var, philo);
	return NULL;
}

/* Checks if function arguments are correct */
int	input_handler(int argc, char **argv, t_var *var)
{
	if (argc != 5 && argc != 6)
		return (pp_init_error("Wrong number of arguments."));
	var->nb_philos = pp_atoi(argv[1]);
	if (var->nb_philos > 200 || var->nb_philos < 1)
		return (pp_init_error("More than 200 or less than 1 philosopher(s)."));
	var->time_to_die = pp_atoi(argv[2]);
	if (var->time_to_die < 60)
		return (pp_init_error("Time to die is under 60 miliseconds"));
	var->time_to_eat = pp_atoi(argv[3]);
	if (var->time_to_eat < 60)
		return (pp_init_error("Time to eat is under 60 miliseconds"));
	var->time_to_sleep = pp_atoi(argv[4]);
	if (var->time_to_sleep < 60)
		return (pp_init_error("Time to sleep is under 60 miliseconds"));
	var->rounds = 0;
	if (argc == 6)
	{
		var->rounds = pp_atoi(argv[5]);
		if (var->rounds < 1)
			return (pp_init_error("Philosophers must eat at least one time."));
	}
	return (0);

}

/* Function initialises the philo structures and var->forks */
void	init_philos(t_var *var)
{
	int	i;

	i = 0;
	while (i < var->nb_philos)
	{
		var->philo[i].id = i;
		var->philo[i].nb_left_fork = i;
		var->philo[i].nb_right_fork =  (i + 1) % var->nb_philos;
		var->philo[i].var = var;
		var->philo[i].nb_eaten = 0;
		var->philo[i].still_eating = 0;
		var->forks[i] = 0;
		i++;
	}
}

/* Function to initialise the var struct and allocate neccessary memory */
int	init_var(t_var *var)
{
	var->philos = malloc(sizeof(pthread_t) * var->nb_philos);
	if (var->philos == NULL)
		return(pp_init_error("Could not allocate memory."));
	var->forks = malloc(sizeof(int) * var->nb_philos);
	if (var->forks == NULL)
	{
		free(var->philos);
		return(pp_init_error("Could not allocate memory."));
	}
	var->philo = (t_philo *)malloc(sizeof(t_philo) * var->nb_philos);
	if (var->philo == NULL)
	{
		free(var->philos);
		free(var->forks);
		return(pp_init_error("Could not allocate memory."));
	}
	var->died = 0;
	init_philos(var);
	var->starttime = pp_current_time();
	return (0);
}

int main(int argc, char **argv)
{
	t_var		var;
	int			i;

	if (input_handler(argc, argv, &var) == -1)
		return (-1);
	if (init_var(&var) == -1)
		return (-1);
// mutex init muss noch abgesichert werden
	pthread_mutex_init(&var.lock_forks, NULL);
	pthread_mutex_init(&var.lock_output, NULL);
	pthread_mutex_init(&var.lock_died, NULL);
	i = 0;
	while (i < var.nb_philos)
	{
		//muss noch abgesichert werden
		var.philo[i].starttime = pp_current_time();
		pthread_create(&var.philos[i], NULL, &routine, &var.philo[i]);
		i++;
	}
	i = 0;
	while (i < var.nb_philos)
	{
		// muss das abgesichert werden?
		pthread_join(var.philos[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&var.lock_forks);
	pthread_mutex_destroy(&var.lock_output);
	pthread_mutex_destroy(&var.lock_died);
	free(var.philos);
	free(var.philo);
	free(var.forks);
	return (0);
}