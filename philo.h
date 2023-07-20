/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:40:43 by eduarodr          #+#    #+#             */
/*   Updated: 2023/07/20 15:00:35 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define RED "\033[1;31m"
# define GREEN "\e[4;32m"
# define DEFAULT "\033[1;0m"
# define YELLOW "\e[4;33m"
# define BLUE "\e[4;34m"

typedef struct s_fork{
	int				fork_take;
	pthread_mutex_t	fork_lock;
} t_fork;

typedef struct s_philo{
	int				num;
	t_fork			*fork_left;
	t_fork			fork_right;
	int				eat_count;
	long int		last_meal;
	pthread_t		philosophers;
	pthread_mutex_t	time;
	pthread_mutex_t print;
	pthread_mutex_t	meal;
}	t_philo;

typedef struct s_status{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				is_dead;
	int				is_full;
	time_t			starting_time;
	pthread_mutex_t	food;
	pthread_mutex_t	life;
	t_philo			*philo;
}	t_status;

void		forks(t_philo *philo, int stats);
int			default_times(char **av);
int			ft_atoi(char *str);
int			check_digit(char *str);
void		philo (t_philo *philo);
void		eating(t_philo *philo);
void		sleeping(t_philo *philo);
long long	gettime(void);
t_status	*status(void);
void		wait(t_philo *philo, time_t time);
void		ft_philo(t_philo *philo);
void		init_philo(void);
void		print_action(t_philo *philo, char *str);
void		init_mutex(void);
void		free_all(void);
void		end_join(t_status *status);
void		check_dead(t_philo *philo, long int current);
void		check_full(void);
int			check_things(t_philo *philo);
void		fork_leave(t_philo *philo, int condition);
void		fork_take(t_philo *philo, int condition);
int 		check_forks(t_philo *philo);
void 		fork_aux(t_philo *philo);

#endif
