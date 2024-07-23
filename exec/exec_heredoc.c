void execute_heredoc(t_redir *redir) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    FILE *heredoc_file = tmpfile(); // Create a temporary file for the heredoc content

    while ((read = getline(&line, &len, stdin)) != -1) {
        if (strcmp(line, redir->heredoc) == 0) {
            break; // Delimiter found, exit the loop
        }
        fwrite(line, 1, read, heredoc_file);
    }

    free(line);
    rewind(heredoc_file);

    // Pass the heredoc content as standard input to the command
    // using pipes or temporary files
    // ...

    fclose(heredoc_file);
}