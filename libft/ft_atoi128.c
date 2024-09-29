#include "libft.h"

__int128	ft_atoi128(const char *str)
{
	int				i;
	int				s;
	__int128    	r;

	i = 0;
	s = 0;
	r = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s++;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = (r * 10) + str[i] - '0';
		i++;
	}
	if (s % 2 == 0)
		return (r);
	return (-r);
}
