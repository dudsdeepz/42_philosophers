/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:20:22 by eduarodr          #+#    #+#             */
/*   Updated: 2023/06/30 16:32:08 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void philo (t_status *status)
{   
    int i;
    
    i = 0;
    init_mutex(status);
    init_philo(status);
}

void init_philo(t_status *status)
{
    int i;

    i = 1;
    status->starting_time = gettime();
    status->is_dead = 0;
    status->is_full = 0;
    while (++i < status->number_of_philosophers)
    {
        if(pthread_create(&status->philo[i].philosophers, NULL, (void *)ft_philo, &status->philo[i]))
            return ;
    }
}

void init_mutex(t_status *status)
{
    int i;

    i = 0;
    status->philo = malloc(sizeof(t_philo) * status->number_of_philosophers);
    status->philo->food = malloc(sizeof(pthread_mutex_t));
    status->philo->life = malloc(sizeof(pthread_mutex_t));
    if (!status->philo->food || !status->philo->life 
        || pthread_mutex_init(status->philo->life, NULL) 
        || pthread_mutex_init(status->philo->food, NULL))
            return ;
    while (++i < status->number_of_philosophers)
    {
        status->philo[i].num = i + 1;
        status->philo[i].fork = malloc(sizeof(pthread_mutex_t));
        if (!status->philo[i].fork)
            return ;
        if(pthread_mutex_init(status->philo[i].fork, NULL))
            return ;
    }
}