#include "libft.h"


t_fdnode** get_head() {
    static t_fdnode* head = NULL;
    return &head;
}

t_fdnode* create_node(int fd) {
    t_fdnode* new_node = (t_fdnode*)malloc(sizeof(t_fdnode));
    if (!new_node) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    new_node->fd = fd;
    new_node->in_use = 1;
    new_node->next = NULL;
    return new_node;
}

void add_fd(int fd) {
    t_fdnode* new_node = create_node(fd);
    new_node->next = *get_head();
    *get_head() = new_node;
}

void mark_fd_unused(int fd) {
    t_fdnode* current = *get_head();
    while (current != NULL) {
        if (current->fd == fd) {
            current->in_use = 0;
            break;
        }
        current = current->next;
    }
}

// Wrapper for open
int gc_open(const char* path, int flags) {
    int fd = open(path, flags);
    if (fd == -1) {
        perror("open");
        return -1;
    }
    add_fd(fd);
    return fd;
}

// Updated wrapper for close
int gc_close(int fd) {
    t_fdnode** head = get_head();
    t_fdnode* current = *head;
    t_fdnode* prev = NULL;

    // Find the fd in the linked list
    while (current != NULL) {
        if (current->fd == fd) {
            // Mark the file descriptor as not in use
            current->in_use = 0;

            // Close the file descriptor
            close(fd);

            // Remove the node from the linked list
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }

            free(current);
            return 0;
        }
        prev = current;
        current = current->next;
    }

    // If we reach here, the fd was not found
    return -1;
}

// Garbage collection function to close unused fds
void gc_collect() {
    t_fdnode* current = *get_head();

    while (current != NULL) {
        // Store the next node to continue iteration after gc_close
        t_fdnode* next_node = current->next;

        // If the file descriptor is not in use, close it
        if (!current->in_use) {
            gc_close(current->fd);
        }

        current = next_node;
    }
}
