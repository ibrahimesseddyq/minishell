/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 22:19:50 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/18 02:50:02 by ynachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_splitted_char(int index)
{
	static char	c[4];

	if (c[index - 1] == 0)
		c[index - 1] = 33;
	return (&c[index - 1]);
}
char	*skip_char(const char* input, char skip)
{
    if (input == NULL) return NULL;

    size_t len = strlen(input);
    char* result = (char*)gcalloc(len + 1);  // +1 for null terminator
    if (result == NULL) return NULL;  // Check for malloc failure

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (input[i] != skip) {
            result[j++] = input[i];
        }
    }
    result[j] = '\0';  // Null-terminate the result string

    return result;
}