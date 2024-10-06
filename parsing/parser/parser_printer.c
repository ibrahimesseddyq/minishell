/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_printer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:40:22 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/06 16:41:15 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"
// Just for debug

// void print_redirection(t_redir_list *redir_list,
//         const char *type, int depth) {
//     if (!redir_list) return;
//     t_redir_list *current = redir_list;

//     while (current) {
//         t_redir *redir = current->redir;
//         for (int i = 0; i < depth; i++) {
//             printf(" ");
//         }
//         printf("%s:\n", type);
//         if (redir->file) {
//             for (int i = 0; i < depth + 1; i++) {
//                 printf(" ");
//             }
//             printf("File: %s\n", redir->file);
//         }
//         if (redir->heredoc) {
//             for (int i = 0; i < depth + 1; i++) {
//                 printf(" ");
//             }
//             printf("Here Document: %s\n", redir->heredoc);
//         }
//         for (int i = 0; i < depth + 1; i++) {
//             printf(" ");
//         }
//         printf("Type: %d\n", redir->type);
//         current = current->next;
//     }
// }

// void print_ast(t_astnode *node, int depth) {
//     if (!node) return;

//     for (int i = 0; i < depth; i++) {
//         printf(" ");
//     }

//     switch (node->type) {
//         case NODE_COMMAND:
//             printf("Node Command: %s\n", node->t_cmd.cmd);
//             for (int i = 0; node->t_cmd.args[i]; i++) {
//                 for (int j = 0; j < depth + 1; j++) {
//                     printf(" ");
//                 }
//                 // printf("Arg: %s\n", node->t_cmd.args[i]);
//             }
//             print_redirection(node->t_cmd.redirections, 
//                  "Redirections", depth + 1);
//             break;
//         case NODE_PIPE:
//             printf("Node Pipe:\n");
//             print_ast(node->t_binary.left, depth + 1);
//             print_ast(node->t_binary.right, depth + 1);
//             break;
//         case NODE_LOGICAL_AND:
//             printf("Node Logical AND:\n");
//             print_ast(node->t_binary.left, depth + 1);
//             print_ast(node->t_binary.right, depth + 1);
//             break;
//         case NODE_LOGICAL_OR:
//             printf("Node Logical OR:\n");
//             print_ast(node->t_binary.left, depth + 1);
//             print_ast(node->t_binary.right, depth + 1);
//             break;
//         case NODE_BLOCK:
//             printf("Node Block:\n");
//             print_ast(node->t_block.child, depth + 1);
//             break;
//         default:
//             printf("Unknown node type: %d\n", node->type);
//     }
// }
// void print_redirection2(t_redir_list *redir_list,
//              const char *type, int depth) {

//     if (!redir_list) return;
//     t_redir_list *current = redir_list;

//     while (current) {
//         t_redir *redir = current->redir;
//         for (int i = 0; i < depth; i++) {
//             printf(" ");
//         }
//         printf("%s:\n", type);
//         if (redir->file) {
//             for (int i = 0; i < depth + 1; i++) {
//                 printf(" ");
//             }
//             printf("File: %s\n", redir->file);
//         }
//         if (redir->heredoc) {
//             for (int i = 0; i < depth + 1; i++) {
//                 printf(" ");
//             }
//             printf("Here Document: %s\n", redir->heredoc);
//         }
//         for (int i = 0; i < depth + 1; i++) {
//             printf(" ");
//         }
//         printf("Type: %d\n", redir->type);
//         current = current->next;
//     }
// }