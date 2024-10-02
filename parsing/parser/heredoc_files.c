#include "./../../minishell.h"


void add_heredoc_to_list(char *heredoc_file)
{
    t_list  **lst;
    char    *heredoc_content;
    t_list  *heredoc;

    lst = get_heredoc_list();
    heredoc_content = ft_strdup(heredoc_file);
    if (heredoc_content == NULL)
        return;

    heredoc = ft_lstnew(heredoc_content);
    if (heredoc == NULL)
        return;

    ft_lstadd_back(lst, heredoc);
}
t_list **get_heredoc_list()
{
    static t_list *lst;
    return &lst;
}

void    unlink_heredocs()
{
    t_list *lst;
    t_list *tmp;

    lst = *get_heredoc_list();
    if (!lst)
        return ;
    tmp = lst;
    if (!tmp)
        printf("no tmp\n");
    while(tmp)
    {
        printf("filename [%s]\n", tmp->content);
        unlink(tmp->content);
        tmp = tmp->next;
    }
    *get_heredoc_list() = NULL;
}

