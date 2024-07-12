#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

bool matchStar(char ch, const char *pattern, const char *text);
bool match(const char *pattern, const char *text);
char** filterStrings(const char *pattern, const char *texts[], int numTexts, int *numMatches);

bool match(const char *pattern, const char *text) {
    // If both the pattern and text are at the end, it's a match
    if (*pattern == '\0' && *text == '\0') {
        return true;
    }
    // If the pattern is '*', try to match it with any sequence of characters
    if (*pattern == '*') {
        return match(pattern + 1, text) || (*text != '\0' && match(pattern, text + 1));
    }
    // If the current character of pattern and text match, continue matching the rest
    if (*text != '\0' && (*pattern == *text)) {
        return match(pattern + 1, text + 1);
    }
    return false;
}

// Function to filter an array of strings based on the pattern
char** filterStrings(const char *pattern, const char *texts[], int numTexts, int *numMatches) {
    char **matches = malloc(numTexts * sizeof(char*));
    *numMatches = 0;

    for (int i = 0; i < numTexts; i++) {
        printf("text[i]: %s, pattern: %s\n", texts[i], pattern);
        if (match(pattern, texts[i])) {
            matches[*numMatches] = malloc((strlen(texts[i]) + 1) * sizeof(char));
            strcpy(matches[*numMatches], texts[i]);
            printf("Match found: %s\n", texts[i]);
            (*numMatches)++;
        }
    }

    return matches;
}

void add_to_found(char ***found_files, int *found_count, const char *file) {
    *found_files = realloc(*found_files, (*found_count + 1) * sizeof(char*));
    (*found_files)[*found_count] = malloc((strlen(file) + 1) * sizeof(char));
    strcpy((*found_files)[*found_count], file);
    (*found_count)++;
}

char** get_files(const char *dir, int *numFiles) {
    DIR *dp;
    struct dirent *ep;
    char **files = NULL;
    *numFiles = 0;

    dp = opendir(dir);
    if (dp != NULL) {
        while ((ep = readdir(dp))) {
            if (strcmp(ep->d_name, ".") != 0 && strcmp(ep->d_name, "..") != 0) {
                files = realloc(files, (*numFiles + 1) * sizeof(char*));
                files[*numFiles] = malloc((strlen(ep->d_name) + 1) * sizeof(char));
                strcpy(files[*numFiles], ep->d_name);
                (*numFiles)++;
            }
        }
        closedir(dp);
    } else {
        perror("Couldn't open the directory");
    }
    return files;
}

void wildcard(char **pattern, int level, const char *pwd, int levels, char ***found_files, int *found_count) {
    if (level == levels) {
        add_to_found(found_files, found_count, pwd);
        return;
    }

    int numFiles = 0;
    char **files = get_files(pwd, &numFiles);
    printf("Directory: %s, Level: %d\n", pwd, level);
    for (int i = 0; i < numFiles; i++) {
        printf("File: %s\n", files[i]);
    }

    int numMatches = 0;
    char **validPaths = filterStrings(pattern[level], (const char **)files, numFiles, &numMatches);

    for (int i = 0; i < numMatches; i++) {
        printf("Valid path: %s\n", validPaths[i]);
    }

    for (int i = 0; i < numMatches; i++) {
        char nextPath[1024];
        snprintf(nextPath, sizeof(nextPath), "%s/%s", pwd, validPaths[i]);

        struct stat st;
        if (stat(nextPath, &st) == 0 && S_ISDIR(st.st_mode)) {
            wildcard(pattern, level + 1, nextPath, levels, found_files, found_count);
        } else if (level == levels - 1 && S_ISREG(st.st_mode)) {
            add_to_found(found_files, found_count, nextPath);
        }

        free(validPaths[i]);
    }

    free(validPaths);

    for (int i = 0; i < numFiles; i++) {
        free(files[i]);
    }
    free(files);
}

// Main function for testing
int main() {
    char *pattern[] = {"*t", "*.c"};
    int levels = sizeof(pattern) / sizeof(pattern[0]);

    char **found_files = NULL;
    int found_count = 0;

    wildcard(pattern, 0, ".", levels, &found_files, &found_count);

    printf("Matching files:\n");
    for (int i = 0; i < found_count; i++) {
        printf("%s\n", found_files[i]);
        free(found_files[i]);
    }
    free(found_files);

    return 0;
}
