#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <limits.h>

void listDirectories() {
    printf("You selected Option 3: Folders in the current directory\n");
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (dir->d_type == DT_DIR) {
                printf("%s\n", dir->d_name);
            }
        }
        closedir(d);
    }
}

void showCurrentDirectory() {
    printf("You selected Option 5: Show current working directory.\n");
    char cwd[PATH_MAX];
    
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working directory: %s\n", cwd);
    } else {
        printf("getcwd() error\n");
    }
}

int main() {
    int choice;
    char command[100];
    char dirName[PATH_MAX];
    char additionalArgument[PATH_MAX];

    while (1) {
        printf("Options:\n");
        printf("1. Execute a program\n");
        printf("2. Create a new folder\n");
        printf("3. Show existing folders\n");
        printf("4. Delete a folder\n");
        printf("5. Show the current working directory\n");
        printf("6. Exit the shell\n");

        printf("Select an option (1-6) or enter 6 to exit: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the command to execute: ");
                scanf(" %[^\n]", command);

                if (strcmp(command, "mkdir") == 0 || strcmp(command, "rm") == 0 ||
                    strcmp(command, "rmdir") == 0 || strcmp(command, "cp") == 0) {
                    printf("Enter the additional argument: ");
                    scanf("%s", additionalArgument);
                    strcat(command, " ");
                    strcat(command, additionalArgument);
                }

                int executeResult = system(command);

                if (executeResult == 0) {
                    printf("Command executed successfully.\n");
                } else {
                    printf("Failed to execute the command. Error code: %d\n", executeResult);
                }
                break;

            case 2:
                printf("You selected Option 2: Create a new folder.\n");
                printf("Enter the folder name: ");
                scanf("%s", dirName);
                
                int folder_status = mkdir(dirName, 0777);

                if (folder_status == 0) {
                    printf("Folder \"%s\" created successfully.\n", dirName);
                } else {
                    printf("Error creating folder\n");
                }
                break;

            case 3:
                listDirectories();
                break;

            case 4:
                printf("You selected Option 4: Delete a folder.\n");
                printf("Enter directory name to delete: ");
                scanf("%s", dirName);

                int ret = rmdir(dirName);
                if (ret == 0) {
                    printf("Directory \"%s\" removed successfully.\n", dirName);
                } else {
                    printf("Unable to remove directory\n");
                }
                break;

            case 5:
                showCurrentDirectory();
                break;

            case 6:
                printf("Code Exiting...\n");
                return 0;

            default:
                printf("Invalid option. Please select a valid option (1-6).\n");
        }
    }

    return 0;
}
