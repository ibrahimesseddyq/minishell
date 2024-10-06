/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 15:47:54 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/06 15:59:27 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_reverse(char *str);

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	ft_itoa_sp(int n, char *str)
{
	int		i;
	int		neg;
	long	num;

	num = n;
	i = 0;
	neg = 0;
	if (num == 0)
		return (str[i++] = '0', str[i] = '\0', i);
	if (num < 0)
	{
		(1) && (neg = 1, num = -num);
		str[i++] = '-';
	}
	while (num > 0)
	{
		str[i++] = (num % 10) + '0';
		num /= 10;
	}
	str[i] = '\0';
	if (neg)
		ft_reverse(str + 1);
	else
		ft_reverse(str);
	return (i);
}

void	ft_reverse(char *str)
{
	int		start;
	int		end;
	char	temp;

	start = 0;
	end = ft_strlen(str) - 1;
	while (start < end)
	{
		temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
}

int	ft_sprintf(char *str, const char *format, int num)
{
	int		i;
	int		total_len;
	int		num_len;
	char	int_buffer[12];
	int		j;

	(1) && (total_len = 0, i = 0, j = 0);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] == 'd')
		{
			num_len = ft_itoa_sp(num, int_buffer);
			while (j < num_len)
			{
				str[total_len++] = int_buffer[j];
				j++;
			}
			i++;
		}
		else
			str[total_len++] = format[i];
		i++;
	}
	return (str[total_len] = '\0', total_len);
}
