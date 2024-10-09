/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:32:52 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/09 22:41:41 by ynachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

t_redir_list	*handle_redirections(t_tklist *tokens, t_token *token)
{
	t_redir			*redir;
	t_redir_list	*redir_node;

	redir = gcalloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	(1) && (redir->file = NULL, redir->heredoc = NULL);
	if (token->type == TK_LESSERTHAN1)
		redir->type = NODE_REDIRECT_IN;
	else if (token->type == TK_LESSERTHAN2)
		redir->type = NODE_HEREDOC;
	else if (token->type == TK_GREATERTHAN1)
		redir->type = NODE_REDIRECT_OUT;
	else if (token->type == TK_GREATERTHAN2)
		redir->type = NODE_REDIRECT_APPEND;
	next_token(tokens);
	token = next_token(tokens);
	if (!token || token->type != TK_WORD)
		return (NULL);
	redir->file = ft_strdup(token->value);
	redir_node = gcalloc(sizeof(t_redir_list));
	redir_node->redir = redir;
	redir_node->next = NULL;
	return (redir_node);
}

int	create_and_handle_heredoc(t_redir_list *redirections, t_lst *lst)
{
	t_redir_list	*current_heredoc;
	char			*delimiter;
	char			heredoc_file[50];

	current_heredoc = redirections;
	while (current_heredoc)
	{
		if (current_heredoc->redir->type == NODE_HEREDOC)
		{
			delimiter = current_heredoc->redir->file;
			printf("entered\n");
			if (!heredoc_delimiter_valid(delimiter))
				return (0);
			printf("is valid [%d]\n", heredoc_delimiter_valid(delimiter));
			if (write_heredoc_to_file(delimiter, heredoc_file, lst) != 0)
				return (ft_exit(1, SET_EXIT_STATUS), 0);
			current_heredoc->redir->heredoc = ft_strdup(heredoc_file);
			add_heredoc_to_list(current_heredoc->redir->heredoc);
			if (!current_heredoc->redir->heredoc)
				return (0);
		}
		current_heredoc = current_heredoc->next;
	}
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, handle_sig);
	return (1);
}

int	is_word_or_redir(t_token *token)
{
	if (token->type == TK_WORD
		|| token->type == TK_GREATERTHAN1 || token->type == TK_GREATERTHAN2
		|| token->type == TK_LESSERTHAN2 || token->type == TK_LESSERTHAN1)
		return (1);
	return (0);
}

t_astnode	*allocate_cmd(t_redir_list	*redirections,
			char **argv, int argc, t_lst *lst)
{
	t_astnode		*cmd_node;

	if (argc == 0 && !redirections)
		return (NULL);
	cmd_node = (t_astnode *)gcalloc(sizeof(t_astnode));
	cmd_node = create_ast_command(argc, argv);
	cmd_node->t_cmd.redirections = redirections;
	if (!create_and_handle_heredoc(redirections, lst))
		return (NULL);
	return (cmd_node);
}

t_astnode	*parse_cmd(t_tklist *tokens, t_lst *lst)
{
	t_token			*token;
	t_redir_list	*redir_node;
	int				argc;
	char			*argv[DEFAULT_NB];
	t_redir_list	*redirections;

	(1) && (redirections = NULL, argc = 0, ft_memset(argv, 0, DEFAULT_NB));
	token = peek_token(tokens);
	while (token && is_word_or_redir(token))
	{
		if (argc >= DEFAULT_NB - 1)
			handle_overflow();
		token = peek_token(tokens);
		if (token->type == TK_WORD)
			((1) && (token = next_token(tokens), argv[argc++] = token->value));
		else if (token->type == TK_GREATERTHAN1
			|| token->type == TK_GREATERTHAN2
			|| token->type == TK_LESSERTHAN2 || token->type == TK_LESSERTHAN1)
		{
			redir_node = handle_redirections(tokens, token);
			ft_lstadd_back_redir(&redirections, redir_node);
		}
	}
	return (allocate_cmd(redirections, argv, argc, lst));
}
