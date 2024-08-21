#include <stdio.h>

#include <stdlib.h>
#include <limits.h>
#include "libft.h"

static int	count_words(char const *s, char c)
{
	int		i;
	int		cnt;
	int		in_single_quote;
	int		in_double_quote;

	i = 0;
	cnt = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		// Skip spaces outside of quotes
		while (s[i] == ' ' && !in_single_quote && !in_double_quote)
			i++;
		
		if (s[i] == '\'')
			in_single_quote = !in_single_quote;
		else if (s[i] == '"')
			in_double_quote = !in_double_quote;

		// If we reach a non-delimiter character and are not inside quotes
		if (s[i] != c && s[i] != '\0')
		{
			cnt++;
			// Move to the end of the word or quoted section
			while (s[i] && (in_single_quote || in_double_quote || (s[i] != c && s[i] != ' ')))
			{
				if (s[i] == '\'')
					in_single_quote = !in_single_quote;
				else if (s[i] == '"')
					in_double_quote = !in_double_quote;
				i++;
			}
		}
		else
		{
			i++;
		}
	}
	return (cnt);
}

static char	*ft_strndup(const char *s1, int n)
{
	int		i;
	char	*new;

	i = 0;
	if (n == INT_MAX)
		return (NULL);
	new = (char *)malloc(n + 1);
	if (new == NULL)
		return (NULL);
	while (i < n)
	{
		new[i] = s1[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	**ft_split_quotes(char const *s, char c)
{
	int		i;
	int		index;
	int		tail_matrice;
	char	**arr;
	int		in_single_quote;
	int		in_double_quote;

	index = -1;
	in_single_quote = 0;
	in_double_quote = 0;
	tail_matrice = count_words(s, c);
	arr = (char **)malloc((sizeof(char *)) * (tail_matrice + 1));
	if (!arr || tail_matrice == -1)
		return (NULL);
	while (++index < tail_matrice)
	{
		i = 0;
		// Skip delimiters outside of quotes
		while (*s && (*s == c || (*s == ' ' && !in_single_quote && !in_double_quote)))
			s++;
		
		// Determine the length of the next word/segment
		while (s[i] && (in_single_quote || in_double_quote || (s[i] != c && s[i] != ' ')))
		{
			if (s[i] == '\'')
				in_single_quote = !in_single_quote;
			else if (s[i] == '"')
				in_double_quote = !in_double_quote;
			i++;
		}
		arr[index] = ft_strndup(s, i);
		if (arr[index] == NULL)
			return (NULL);
		s += i;
	}
	arr[index] = NULL;
	return (arr);
}