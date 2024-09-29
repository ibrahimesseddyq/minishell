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
	{
		str[i++] = '0';
		str[i] = '\0';
		return (i);
	}
	if (num < 0)
	{
		neg = 1;
		num = -num;
		str[i++] = '-';
	}
	while (num > 0)
	{
		str[i++] = (num % 10) + '0';
		num /= 10;
	}
	str[i] = '\0';
	if (neg)
		ft_reverse(str + 1); // Reverse only after '-'
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
	char	int_buffer[12]; // For integer conversion

	total_len = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] == 'd')
		{
			num_len = ft_itoa_sp(num, int_buffer); // Convert number to string
			for (int j = 0; j < num_len; j++)   // Copy the converted number
				str[total_len++] = int_buffer[j];
			i++; // Skip 'd'
		}
		else
		{
			str[total_len++] = format[i];
		}
		i++;
	}
	str[total_len] = '\0'; // Null-terminate the result string
	return (total_len);
}
