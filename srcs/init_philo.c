/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:20:22 by eduarodr          #+#    #+#             */
/*   Updated: 2023/07/05 15:26:26 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void philo (t_status *status)
{
    init_mutex(status);
    init_philo(status);
}

void init_philo(t_status *status)
{
    int i;

    i = -1;
    status->starting_time = gettime();
    status->philo->last_meal = gettime();
    while (++i < status->number_of_philosophers)
    {
        if(pthread_create(&status->philo[i].philosophers, NULL, (void *)ft_philo, &status->philo[i]))
            return ;
        if (status->is_dead)
            end_join(status);
    }
}

void init_mutex(t_status *status)
{
    int i;

    i = -1;
    status->philo = malloc(sizeof(t_philo) * status->number_of_philosophers);
    if (pthread_mutex_init(&status->philo->life, NULL)
        || pthread_mutex_init(&status->philo->food, NULL)
        || pthread_mutex_init(&status->philo->action, NULL))
            return ;
    while (++i < status->number_of_philosophers)
    {
        status->philo->eat_count = 0;
        status->philo[i].num = i + 1;
        if(pthread_mutex_init(&status->philo[i].fork_right, NULL))
            return ;
        if(i != 0)
	    	status->philo[i].fork_left  = &status->philo[i - 1].fork_right;
        else if (i == 0)
            status->philo[i].fork_left  = &status->philo[status->number_of_philosophers - 1].fork_right;
    }
}

void end_join(t_status *status)
{
    int i = -1;
    
    if (status->philo->philosophers)
    {
        while (++i < status->number_of_philosophers)
            pthread_join(status->philo[i].philosophers, NULL);
    }
    free(&(status->philo->action));
    free(&(status->philo->life));
    free(&(status->philo->fork_right));
    free(&(status->philo->food));
    free(status->philo);
    status->philo = NULL;
}