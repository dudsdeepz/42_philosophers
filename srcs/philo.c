/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:35:39 by eduarodr          #+#    #+#             */
/*   Updated: 2023/06/28 16:04:44 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void* ft_test(void *statuss)
{
    t_status *status = statuss;

    
    status->is_dead = 0;
    while (1)
    {
        forks(status, 1);
        eating(status);
        sleeping(status);
        forks(status, 0);
        printf("%i is thinking\n", status->philosophers);
    }
    return (0);
}

void philo (t_status status)
{   
    status.philosophers = 1;
    status.philos = malloc(sizeof(pthread_t) * status.number_of_philosophers);
    status.philo = malloc(sizeof(pthread_t) * status.number_of_philosophers);
    while (status.philosophers < status.number_of_philosophers)
    {
        status.philo[status.philosophers].fork = malloc(sizeof(pthread_mutex_t));
        if(pthread_mutex_init(status.philo[status.philosophers].fork, NULL))
            break ;
        status.philosophers++;
    }
    status.philosophers = 1;
    while (status.philosophers < status.number_of_philosophers)
    {
        if (status.is_dead)
        {
            while(status.philos[status.philosophers])
                pthread_join(status.philos[status.philosophers], NULL);
        }
        pthread_create(&status.philos[status.philosophers], NULL, ft_test, &status);
        status.philosophers++;
    }
}

void eating(t_status *status)
{
    if (!status->is_full)
    {
        printf("%i is eating\n", status->philosophers);
        status->philo->eat_count++;
    }
}
void sleeping(t_status *status)
{
    printf("%i is sleeping\n", status->philosophers);
}


void forks(t_status *status, int stats)
{
    t_philo *next;

    if (status->philosophers < status->number_of_philosophers)
        next = &status->philo[1];
    else
        next = &status->philo[(-1 * (status->number_of_philosophers + 1))];
    if (stats)
    {
        pthread_mutex_lock(status->philo->fork);
        pthread_mutex_lock(next->fork);
        return ;
    }
    else if (!stats)
    {
        pthread_mutex_unlock(status->philo->fork);
        pthread_mutex_unlock(next->fork);
    }
}

void wait(t_status status, int time)
{
    time_t start;
    time_t current;
    
    start = get_time();
    while (1)
    {
        current = gettime();
        if (current - start >= time)
            break ;
        usleep(100);
    }
}

time_t gettime(void)
{
    struct timeval current_time;
    
    if (gettimeofday(&current_time, NULL) < 0)
        return (0);
    return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}