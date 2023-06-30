/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:35:39 by eduarodr          #+#    #+#             */
/*   Updated: 2023/06/30 16:33:54 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void ft_philo(t_status *status)
{

    while (1)
    {
        printf("%i\n", status->philo->num);
    }
}

void eating(t_status *status)
{
    print_action(status, "has taken fork");
    print_action(status, "has taken fork");
    print_action(status, "is sleeping");
    pthread_mutex_lock(status->philo->food);
    status->philo->eat_count++;
    pthread_mutex_unlock(status->philo->food);
    wait(status, status->time_to_eat);
}
void sleeping(t_status *status)
{
    print_action(status, "is sleeping");
    wait(status, status->time_to_sleep);
    print_action(status, "is thinking");
}


void forks(t_status *status, int stats)
{
    t_philo *next;
    
    next = &status->philo[status->philo->num % status->number_of_philosophers];
    if (stats)
    {
        pthread_mutex_lock(status->philo->fork);
        pthread_mutex_lock(next->fork);
    }
    else if (!stats)
    {
        pthread_mutex_unlock(status->philo->fork);
        pthread_mutex_unlock(next->fork);
    }
}

void wait(t_status *status, int time)
{
    time_t start;
    time_t current;
    
    start = gettime();
    while (1)
    {
        pthread_mutex_lock(status->philo->life);
        if (status->is_dead)
        {
            pthread_mutex_unlock(status->philo->life);
            return ; 
        }
        pthread_mutex_unlock(status->philo->life);
        current = gettime();
        if (current - start >= time)
            break ;
    }
}

time_t gettime(void)
{
    struct timeval current_time;
    
    if (gettimeofday(&current_time, NULL) < 0)
        return (0);
    return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void print_action(t_status *status, char *str)
{
    int time;
    
    time = gettime() - status->starting_time;
    pthread_mutex_lock(status->philo->life);
    pthread_mutex_lock(status->philo->food);
    if (status->is_dead)
    {
        pthread_mutex_unlock(status->philo->life);
        pthread_mutex_unlock(status->philo->food);
        return ; 
    }
    pthread_mutex_unlock(status->philo->life);
    pthread_mutex_unlock(status->philo->food);
    printf("%s%i %s%i %s %s\n", YELLOW, time, RED, status->philo->num, DEFAULT, str);
}

void free_all(t_status *status)
{
    int i;
    
    i = 0;
    while (++i < status->number_of_philosophers)
    {
        if (status->philo[i].fork)
        {
            pthread_mutex_destroy(status->philo[i].fork);
            free(status->philo[i].fork);
        }
    }
    pthread_mutex_destroy(status->philo->food);
    free(status->philo->food);
    pthread_mutex_destroy(status->philo->life);
    free(status->philo->life);
    if (status->philo)
        free(status->philo);
    status->philo = NULL;
}