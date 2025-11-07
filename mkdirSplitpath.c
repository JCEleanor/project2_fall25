#include "types.h"

extern struct NODE *root;
extern struct NODE *cwd;

// make directory
void mkdir(char pathName[])
{

    // TO BE IMPLEMENTED
    //
    // YOUR CODE TO REPLACE THE PRINTF FUNCTION BELOW

    char dirName[128];
    char baseName[128];
    struct NODE *parentNode = splitPath(pathName, baseName, dirName);

    if (parentNode == NULL)
    {
        return;
    }

    if (strcmp(baseName, "") == 0)
    {
        printf("MKDIR ERROR: no path provided\n");
        return;
    }

    // check if baseName already exists in parentNode
    struct NODE *child = parentNode->childPtr;
    while (child != NULL)
    {

        if (strcmp(child->name, baseName) == 0)
        {
            printf("MKDIR ERROR: directory %s already exists\n", baseName);
            return;
        }

        child = child->siblingPtr;
    }

    // create new directory node
    struct NODE *newNode = (struct NODE *)malloc(sizeof(struct NODE));
    strcpy(newNode->name, baseName);
    newNode->fileType = 'D';
    newNode->childPtr = NULL;
    newNode->siblingPtr = NULL;
    newNode->parentPtr = parentNode;

    // link the New Node into the Tree. Add it to the end of the sibling list
    if (parentNode->childPtr == NULL)
    {
        parentNode->childPtr = newNode;
    }
    else
    {
        // find the last sibling and add the new node after it
        struct NODE *lastChild = parentNode->childPtr;
        while (lastChild->siblingPtr != NULL)
        {
            lastChild = lastChild->siblingPtr;
        }
        lastChild->siblingPtr = newNode;
    }

    printf("MKDIR SUCCESS: node %s successfully created\n", pathName);
    return;
}

// handles tokenizing and absolute/relative pathing options
struct NODE *splitPath(char *pathName, char *baseName, char *dirName)
{

    // TO BE IMPLEMENTED
    // NOTE THAT WITHOUT COMPLETING THIS FUNCTION CORRECTLY
    // rm, rmdir, ls, cd, touch COMMANDS WILL NOT EXECUTE CORRECTLY
    // SEE THE PROVIDED SOLUTION EXECUTABLE TO SEE THEIR EXPECTED BEHAVIOR

    // YOUR CODE HERE
    //

    char *lastSlashPtr = strrchr(pathName, '/');
    // no slash found, i.e., test.txt
    if (lastSlashPtr == NULL)
    {
        strcpy(baseName, pathName);
        strcpy(dirName, "");
    }
    else
    {
        strcpy(baseName, lastSlashPtr + 1); // copy everything after the last slash

        // if pathName is just "/", set dirName to root "/"
        if (strlen(pathName) == 1 && pathName[0] == '/')
        {
            strcpy(dirName, "/");
        }
        else
        {
            *lastSlashPtr = '\0'; // temporarily terminate the string at the last slash
            // i.e., /a
            if (pathName[0] == '\0')
            {
                strcpy(dirName, "/");
            }
            else
            {
                strcpy(dirName, pathName);
            }

            // restore the original string
            *lastSlashPtr = '/';
        }
    }

    struct NODE *startNode;
    if (dirName[0] == '/')
    {
        startNode = root;
    }
    else
    {
        startNode = cwd;
    }

    // case 1: dirName is "/"
    if (strcmp(dirName, "/") == 0)
    {
        return root;
    }

    if (strcmp(dirName, "") == 0)
    {
        return cwd;
    }

    char dirNameCopy[128];
    strcpy(dirNameCopy, dirName);

    char *token = strtok(dirNameCopy, "/");
    while (token != NULL)
    {
        struct NODE *foundNode = NULL;
        struct NODE *child = startNode->childPtr;
        while (child != NULL)
        {
            if (child->fileType == 'D' && strcmp(child->name, token) == 0)
            {
                foundNode = child;
                break;
            }
            child = child->siblingPtr;
        }

        if (foundNode != NULL)
        {
            startNode = foundNode;
        }
        else
        {
            printf("ERROR: directory %s does not exist\n", token);
            return NULL;
        }

        token = strtok(NULL, "/");
    }

    return startNode;
}
