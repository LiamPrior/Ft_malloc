/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liamprior <liamprior@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 16:12:10 by lprior            #+#    #+#             */
/*   Updated: 2018/07/18 18:54:58 by liamprior        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <libft/libft.h>

# define TINY 128
# define SMALL 2048
# define PROTS (PROT_READ | PROT_WRITE | PROT_EXEC)
# define MAP_PERMS (MAP_ANON | MAP_PRIVATE | MAP_NOCACHE)

extern void				*g_pages[3];
extern pthread_mutex_t	g_mutex[3];

// typedef struct s_alloc
// {
//     int zone_size;
    
    
// }               t_alloc;

typedef struct s_meta
{
    struct t_alloc;
    void    *start_addr;
    bool    free;
    struct t_meta *next;
}               t_meta;