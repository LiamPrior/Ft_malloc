/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprior <lprior@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 16:12:10 by lprior            #+#    #+#             */
/*   Updated: 2018/07/15 18:17:08 by lprior           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <libft/libft.h>

# define TINY 128
# define LARGE 2048
# define PROTS (PROT_READ | PROT_WRITE | PROT_EXEC)
# define MAPS (MAP_ANON | MAP_PRIVATE | MAP_NOCACHE)

