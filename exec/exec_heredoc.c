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
    rewind(heredoc_file);
    fclose(heredoc_file);
}