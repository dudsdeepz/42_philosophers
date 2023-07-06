/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:40:43 by eduarodr          #+#    #+#             */
/*   Updated: 2023/07/06 16:25:16 by eduarodr         ###   ########.fr       */
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


typedef struct s_status{
    int      number_of_philosophers;
    double   time_to_die;
    double   time_to_eat;
    double   time_to_sleep;
    int      number_of_times_each_philosopher_must_eat;
    long long  starting_time;
}   t_status;

typedef struct s_philo{
    int             num;
	pthread_mutex_t *fork_left;
    pthread_mutex_t fork_right;
    int             eat_count;
    pthread_t       philosophers;
    pthread_mutex_t food;
    pthread_mutex_t life;
    int      is_dead;
    int      is_full;
	t_status *status;
    time_t   last_meal;
}   t_philo;

typedef struct s_all{

	t_status *status;
	t_philo *philo;
}	t_all;

void    forks(t_philo *philo, int stats);
int     default_times(t_status *status, char **av);
int     ft_atoi(char *str);
int     check_digit(char *str);
void    philo (t_all *all, t_status *status, t_philo *philo);
void    eating(t_philo *philo);
void    sleeping(t_philo *philo);
long long  gettime(void);
void    wait(t_philo *philo, time_t time);
void    ft_philo(t_philo *philo);
void    init_philo(t_all *all);
void    print_action(t_philo *philo, char *str);
void    init_mutex(t_all *all);
void    free_all(t_philo *philo);
void 	end_join(t_all *all);

#endif
