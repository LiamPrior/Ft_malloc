/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprior <lprior@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 15:13:29 by lprior            #+#    #+#             */
/*   Updated: 2017/10/05 12:42:17 by lprior           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *s1;

	if (!(s1 = (char *)malloc(size + 1)))
		return (NULL);
	ft_bzero(s1, size + 1);
	return (s1);
}