/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprior <lprior@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 16:41:38 by lprior            #+#    #+#             */
/*   Updated: 2018/07/15 18:22:31 by lprior           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

void    *ft_malloc(size_t *size)
{
    if (size == 0)
        size = 1;
    else if (size <= TINY)

    else if (size <= LARGE && size > TINY)
        
    else
        return(alloc large)
}

int main(void)
{
    int *x;
    int i = 4;


    printf("%lu\n", sizeof(x));    
}