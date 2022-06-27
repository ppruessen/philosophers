#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct	s_var
{
	int					nb_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					rounds;
	pthread_t			*philos;
	struct s_philo		*philo;
	int					*forks;
	long				starttime;
	int					died;
// old struct
	pthread_mutex_t		lock_forks;
	pthread_mutex_t		lock_output;
	pthread_mutex_t		lock_died;
}	t_var;

typedef struct	s_philo
{
	long			starttime;
	int				id;
	int				nb_left_fork;
	int				nb_right_fork;
	int				nb_eaten;
	long			last_meal;
	long			time_to_die;
	int				still_eating;
	t_var			*var;
}	t_philo;

/* helpers.c */
long	pp_current_time(void);
long	pp_time_delta(long timestamp);
int		pp_atoi(const char *str);

/* error_handler.c */
int	pp_init_error(char *error_msg);

#endif