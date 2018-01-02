#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

void freeMaze(char ** maze, int height);
 
int main(int argc, char **argv)
{
    int width, height;
    FILE *in;
    if (argc < 3)
    {
        printf("You need an input file and algorithm.\n");
        return -1;
    }
    in = fopen(argv[1], "r");
    if (in == NULL)
    {
        printf("Could not open file: %s\n", argv[1]);
        return -1;
    }
    int mode = atoi(argv[2]);
    fscanf(in, "%d", &width);
    fscanf(in, "%d", &height);
    fgetc(in);
    char ** maze = (char **) malloc(height * sizeof(char*));
    int i;
    for(i = 0; i < height; i++)
    {
        maze[i] = (char *) malloc(width * sizeof(char));
    }
    char c;
    int x = 0, y = 0;
    while ((c = fgetc(in)) != EOF)
    {
        if (c == '\n')
        {
            y++;
            x = 0;
            continue;
        }
        else
        {
            maze[y][x] = c;
            x++;
        }
    }
    fclose(in);
 
    int yStart, xStart, yEnd, xEnd;
    findStartEnd(maze, width, height, &xStart, &yStart, &xEnd, &yEnd);
    if (xStart == -1 || yStart == -1)
    {
        printf("Could not find start of maze\n");
        freeMaze(maze, height);
        return -1;
    }
    printf("Start of maze at (%d, %d)\n", xStart, yStart);

    int solved;
    if (mode == 0)
        solved = solveMazeManhattanDFS(maze, width, height, xStart, yStart, xEnd, yEnd);
    else
        solved = solveMazeBFS(maze, width, height, xStart, yStart);

    if (solved == 0)
    {
        printMaze(maze, width, height);
        printf("Maze is unsolvable\n");
    }
    else
    {
        printMaze(maze, width, height);
        if(checkMaze(maze, width, height, xStart, yStart))
            printf("Maze is correct!\n");
        else
            printf("Maze is incorrect!\n");
    }

    freeMaze(maze, height); 
    return 0;
}

void freeMaze(char ** maze, int height)
{
    int i;
    for(i = 0; i < height; i++)
    {
        free(maze[i]);
    }
    free(maze);
}

