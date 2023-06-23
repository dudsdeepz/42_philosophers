/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:40:43 by eduarodr          #+#    #+#             */
/*   Updated: 2023/06/23 14:50:58 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>

# define RED "\033[1;31m"
# define GREEN "\e[4;32m"
# define DEFAULT "\033[1;0m"
# define YELLOW "\e[4;33m"
# define BLUE "\e[4;34m"
typedef struct s_status{
    int    number_of_philosophers;
    double time_to_die;
    double time_to_eat;
    double time_to_sleep;
    int    number_of_times_each_philosopher_must_eat;
    t_status *next;
}   t_status;

int default_times(t_status *status, char **av);
int ft_atoi(char *str);
int check_digit(char *str);
void philo (t_status status);
#endif  