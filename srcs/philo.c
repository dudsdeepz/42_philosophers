/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:35:39 by eduarodr          #+#    #+#             */
/*   Updated: 2023/07/05 15:40:41 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void ft_philo(t_status *status)
{
    status->is_dead = 0;
    status->is_full = 0;
	while (1)
	{
        usleep(100);
        pthread_mutex_lock(&status->philo->life);
        if (status->is_full || status->is_dead)
        {
            pthread_mutex_unlock(&status->philo->life);
            return ;
        }
        pthread_mutex_unlock(&status->philo->life);
		forks(status, 1);
		eating(status);
		forks(status, 0);
		sleeping(status);
	}
	return ;
}

void eating(t_status *status)
{
    print_action(status, "has taken a fork");
    print_action(status, "has taken a fork");
    print_action(status, "is eating");
    pthread_mutex_lock(&status->philo->food);
    status->philo->last_meal = gettime();
    status->philo->eat_count++;
    pthread_mutex_unlock(&status->philo->food);
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
    if (stats)
    {
        // pthread_mutex_lock(status->philo->fork_left);
        pthread_mutex_lock(&status->philo->fork_right);
    }
    else if (!stats)
    {
        pthread_mutex_unlock(&status->philo->fork_right);
		// pthread_mutex_unlock(status->philo->fork_left);
    }
}

void wait(t_status *status, int time)
{
    time_t start;
    time_t current;

    start = gettime();
    while (1)
    {
        pthread_mutex_lock(&status->philo->action);
        if (status->is_dead)
        {
            pthread_mutex_unlock(&status->philo->action);
            return ;
        }
        pthread_mutex_unlock(&status->philo->action);
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
    pthread_mutex_lock(&status->philo->action);
    if (status->is_dead)
    {
        pthread_mutex_unlock(&status->philo->action);
        return ;
    }
    pthread_mutex_unlock(&status->philo->action);
    printf("%s%i %s%i %s %s\n", YELLOW, time, RED, status->philo->num, DEFAULT, str);
}

void free_all(t_status *status)
{
    int i;

    i = 0;
    while (++i < status->number_of_philosophers)
    {
        if (&(status->philo[i].fork_right))
        {
            pthread_mutex_destroy(&status->philo[i].fork_right);
            free(&(status->philo[i].fork_right));
        }
    }
    pthread_mutex_destroy(&status->philo->food);
    pthread_mutex_destroy(&status->philo->life);
    if (status->philo)
        free(status->philo);
    status->philo = NULL;
}
