/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getcwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 19:53:48 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/12 22:32:02 by ynachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_getcwd(char *buf, size_t size)
{
	char	*ret;
	char	*dir;

	dir = getcwd(buf, size);
	ret = ft_strdup(dir);
	return (ret);
}
