#include <stdio.h>
#include <string.h>

void split_url(const char *url) {
    char url_copy[256]; // Make a copy of the URL to avoid modifying the original
    strcpy(url_copy, url);

    // Split the URL into scheme, domain, path, and fragment
    char *scheme = strtok(url_copy, "://");
    char *domain = strtok(NULL, "/");
    char *path = strtok(NULL, "#");
    char *fragment = strtok(NULL, "");

    // Print the components
    printf("Scheme: %s\n", scheme);
    printf("Domain: %s\n", domain);

    if (path != NULL) {
        printf("Path: /%s\n", path);
    } else {
        printf("Path: /\n");
    }

    if (fragment != NULL) {
        printf("Fragment: %s\n", fragment);
    } else {
        printf("Fragment: None\n");
    }
}

int main() {
    const char *url = "https://mail.google.com/mail/u/0/#inbox";
    split_url(url);
    return 0;
}

