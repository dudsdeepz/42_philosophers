/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:40:43 by eduarodr          #+#    #+#             */
/*   Updated: 2023/06/30 16:33:12 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

# define RED "\033[1;31m"
# define GREEN "\e[4;32m"
# define DEFAULT "\033[1;0m"
# define YELLOW "\e[4;33m"
# define BLUE "\e[4;34m"

typedef struct s_philo{
    int             num;
    pthread_mutex_t *fork;
    int             eat_count;
    pthread_t       philosophers;
    pthread_mutex_t *food;
    pthread_mutex_t *life;
}   t_philo;

typedef struct s_status{
    int      number_of_philosophers;
    double   time_to_die;
    double   time_to_eat;
    double   time_to_sleep;
    int      number_of_times_each_philosopher_must_eat;
    int      is_dead;
    int      is_full;
    t_philo  *philo;
    int      starting_time;
}   t_status;

void    forks(t_status *status, int stats);
int     default_times(t_status *status, char **av);
int     ft_atoi(char *str);
int     check_digit(char *str);
void    philo (t_status *status);
void    eating(t_status *status);
void    sleeping(t_status *status);
time_t  gettime(void);
void    wait(t_status *status, int time);
void   ft_philo(t_status *status);
void    init_philo(t_status *status);
void    print_action(t_status *status, char *str);
void    init_mutex(t_status *status);
void    free_all(t_status *status);

#endif  