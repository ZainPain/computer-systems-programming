#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

void freeMaze(char ** maze, int height);
void myFindStartEnd(char ** maze, int width, int height, int * xStart, int * yStart,
                    int * xEnd, int * yEnd);
void myPrintMaze(char ** maze, int width, int height);
int mySolveMazeManhattanDFS(char ** maze, int width, int height, int xPos, int yPos,
                            int xEnd, int yEnd);
int myCheckMaze(char ** maze, int width, int height, int x, int y, int print, int printUn); 

int main(int argc, char **argv)
{
    int width, height;
    FILE *in;
    // attempt to open input file
    if (argc < 3)
    {
        printf("You need an input file and test to run.\n");
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
    // allocate memory for 2D array maze
    char ** maze1 = (char **) malloc(height * sizeof(char*));
    char ** maze2 = (char **) malloc(height * sizeof(char*));
    int i;
    for(i = 0; i < height; i++)
    {
        maze1[i] = (char *) malloc(width * sizeof(char));
        maze2[i] = (char *) malloc(width * sizeof(char));
    }
    // read contents of input file into maze
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
            maze1[y][x] = c;
            maze2[y][x] = c;
            x++;
        }
    }
    fclose(in);

    if (mode == 0)
    {
        printf("Test findStartEnd on %s\n", argv[1]);
        int yStart1, xStart1, yStart2, xStart2, yEnd1, xEnd1, yEnd2, xEnd2;
        findStartEnd(maze1, width, height, &xStart1, &yStart1, &xEnd1, &yEnd1);
        myFindStartEnd(maze2, width, height, &xStart2, &yStart2, &xEnd2, &yEnd2);
        printf("    Actual Start: (%d, %d), Their Start: (%d, %d)\n", xStart2, yStart2, xStart1, yStart1);
        printf("    Actual End: (%d, %d), Their End: (%d, %d)\n", xEnd2, yEnd2, xEnd1, yEnd1);
        if ((yStart1 == yStart2) && (xStart1 == xStart2) && (xEnd1 == xEnd2) && (yEnd1 == yEnd2))
            printf("    Score: 10\n\n");
        else
            printf("    Score: 0\n\n");
    }
    else if (mode == 1)
    {
        printf("Test printMaze on %s\n", argv[1]);
        printMaze(maze1, width, height);
    }
    else if (mode == 2)
    {
        int yStart, xStart, yEnd, xEnd;
        int score = 50;
        myFindStartEnd(maze1, width, height, &xStart, &yStart, &xEnd, &yEnd);
        if (xEnd == -1)
            score = 0;
        int ours = mySolveMazeManhattanDFS(maze2, width, height, xStart, yStart, xEnd, yEnd);
 
        int theirs = solveMazeManhattanDFS(maze1, width, height, xStart, yStart, xEnd, yEnd);
        if (theirs != ours)
        {
            printf("    -10 points, return value does not match\n");
            score -= 10; 
        }
        if (ours) 
        {
            myPrintMaze(maze1, width, height);
            score -= myCheckMaze(maze1, width, height, xStart, yStart, 1, 1);
            if (score < 0) score = 0;
            printf("    Score: %d\n\n", score);
        }
         else
            printf("    Score: %d\n\n", score);
    }
    else if (mode == 3)
    {
        printf("Test checkMaze on %s\n", argv[1]);
        int yStart, xStart, yEnd, xEnd;
        myFindStartEnd(maze1, width, height, &xStart, &yStart, &xEnd, &yEnd);
        int theirs = checkMaze(maze1, width, height, xStart, yStart);
        int ours = myCheckMaze(maze2, width, height, xStart, yStart, 0, 0);
        if (theirs == 1) printf("    Theirs: Maze correct\n");
        else printf("    Theirs: Maze incorrect\n");
        if ((theirs == 1 && ours == 0) || (theirs == 0 && ours > 0))
            printf("    Score: 5\n\n");
        else
            printf("    Score: 0\n\n");
    }
    else if (mode == 4)
    {
        int yStart, xStart, yEnd, xEnd;
        int score = 20;
        myFindStartEnd(maze1, width, height, &xStart, &yStart, &xEnd, &yEnd);
        int theirs = solveMazeBFS(maze1, width, height, xStart, yStart);
        int ours = mySolveMazeManhattanDFS(maze2, width, height, xStart, yStart, xEnd, yEnd);
        if (theirs != ours)
        {
            printf("    -10 points, return value does not match\n");
            score -= 10; 
        }
        if (ours)
        {
            score -= myCheckMaze(maze1, width, height, xStart, yStart, 1, 1);
            if (score < 0) score = 0;
            myPrintMaze(maze1, width, height);
            printf("    Score: %d\n", score);     
        }
        else
        {
            if (theirs == ours)
                printf("    Score: %d\n", score);
            else
            {
                printf("    -10 points, failed unsolvable maze case\n");
                printf("    Score: 0\n");
            }
        }
    }
    freeMaze(maze1, height);
    freeMaze(maze2, height);
    return 0;
}

int manhattan(int x1, int y1, int x2, int y2)
{
    int xDist = x1 - x2;
    int yDist = y1 - y2;
    if (xDist < 0) xDist *= -1;
    if (yDist < 0) yDist *= -1;
    return xDist + yDist;
}

int mySolveMazeManhattanDFS(char ** maze, int width, int height, int xPos, int yPos, int xEnd, int yEnd)
{
    if (xPos < 0 || xPos >= width || yPos < 0 || yPos >= height)
        return 0;
    if (maze[yPos][xPos] == WALL || maze[yPos][xPos] == PATH || maze[yPos][xPos] == VISITED)
        return 0;
    if (maze[yPos][xPos] == END)
        return 1;
 
    int start = 0;
    if (maze[yPos][xPos] == START)
        start = 1;
 
    maze[yPos][xPos] = PATH;

    int leftDist = manhattan(xPos - 1, yPos, xEnd, yEnd);
    int rightDist = manhattan(xPos + 1, yPos, xEnd, yEnd);
    int upDist = manhattan(xPos, yPos - 1, xEnd, yEnd);
    int downDist = manhattan(xPos, yPos + 1, xEnd, yEnd);

    int i;
    for(i = 0; i < 4; i++) 
    {
        if (leftDist <= rightDist && leftDist <= upDist && leftDist <= downDist) 
        {
            if (mySolveMazeManhattanDFS(maze, width, height, xPos - 1, yPos, xEnd, yEnd))
            {
                if (start)
                    maze[yPos][xPos] = START;
                return 1;    
            }
            leftDist = 1000000;
        }
        if (downDist <= upDist && downDist <= leftDist && downDist <= rightDist)
        {
            if (mySolveMazeManhattanDFS(maze, width, height, xPos, yPos + 1, xEnd, yEnd))
            {
                if (start)
                    maze[yPos][xPos] = START;
                return 1;    
            }
            downDist = 1000000;
        }
        if (rightDist <= leftDist && rightDist <= upDist && rightDist <= downDist)
        {            
            if (mySolveMazeManhattanDFS(maze, width, height, xPos + 1, yPos, xEnd, yEnd))
            {
                if (start)
                    maze[yPos][xPos] = START;
                return 1;    
            }
            rightDist = 1000000;
        }
        if (upDist <= leftDist && upDist <= rightDist && upDist <= downDist)
        {
            if (mySolveMazeManhattanDFS(maze, width, height, xPos, yPos - 1, xEnd, yEnd))
            {
                if (start)
                    maze[yPos][xPos] = START;
                return 1;    
            }
            upDist = 1000000;
        }
    }
 
    if (start)
        maze[yPos][xPos] = START;
    else
        maze[yPos][xPos] = VISITED;
 
    return 0;
}

void myFindStartEnd(char ** maze, int width, int height, int * xStart, int * yStart, int * xEnd, int * yEnd)
{
    int x, y;
    *xStart = -1;
    *yStart = -1;
    *xEnd = -1;
    *yEnd = -1;
    for(y = 0; y < height; y++)
    {
        for(x = 0; x < width; x++)
        {
            if (maze[y][x] == START)
            {
                *xStart = x;
                *yStart = y;
            }
            if (maze[y][x] == END)
            {
                *xEnd = x;
                *yEnd = y;
            }
        }
    }
}

void myPrintMaze(char ** maze, int width, int height)
{
    int i, j;
    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            printf("%c", maze[i][j]);
        }
        printf("\n");
    }
}

int countSurroundingPath(char ** maze, int width, int height, int x, int y, int printUn)
{
    int left = 0, right = 0, down = 0, up = 0;
    int visitedLeft = 0;
    int visitedRight = 0;
    int visitedDown = 0;
    int visitedUp = 0;
    if ((x - 1) >= 0)
    {
        left = (maze[y][x - 1] == PATH) || (maze[y][x - 1] == START) || (maze[y][x - 1] == END);
        if (maze[y][x - 1] == VISITED) visitedLeft++;
    }
    if ((x + 1) < width)
    {
        right = (maze[y][x + 1] == PATH) || (maze[y][x + 1] == START) || (maze[y][x + 1] == END);
        if (maze[y][x + 1] == VISITED) visitedRight++;
    }
    if ((y - 1) >= 0)
    {
        down = (maze[y - 1][x] == PATH) || (maze[y - 1][x] == START) || (maze[y - 1][x] == END);
        if (maze[y - 1][x] == VISITED) visitedUp++;
    }
    if ((y + 1) < height)
    {
        up = (maze[y + 1][x] == PATH) || (maze[y + 1][x] == START) || (maze[y + 1][x] == END);
        if (maze[y + 1][x] == VISITED) visitedDown++;
    }

    if (visitedUp && printUn)
        printf("    Visited unecessary cell at (%d, %d)\n", x, y - 1);
        
    if (visitedRight && printUn)
        printf("    Visited unecessary cell at (%d, %d)\n", x + 1, y);   
    return left + right + down + up;
}

int myCheckMaze(char ** maze, int width, int height, int x, int y, int print, int printUn)
{
    int startOverwritten = 0;
    int endOverwritten = 0;
    int pathDiverges = 0;
    int startDiverges = 0; 
    int endDiverges = 0;
    int visitedCount = 0;
    int dotCount = 0;
    int dist = 0;
    if (maze[y][x] != START)
    {
        if (print)
            printf("    -10, start position overwritten\n");
        startOverwritten = 10;
    }
    int i, j;
    int endFound = 0;
    for (i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            if (maze[i][j] == VISITED) visitedCount++;
            if (maze[i][j] == WALL || maze[i][j] == EMPTY || maze[i][j] == VISITED)
                continue;
            else if (maze[i][j] == START)
            {
                if (countSurroundingPath(maze, width, height, j, i, printUn) != 1)
                {
                    if (print)
                        printf("    -10, multiple or no paths found around start\n");
                    startDiverges = 10;
                }
            }
            else if (maze[i][j] == END)
            {
                dist = manhattan(j, i, x, y);
                if (countSurroundingPath(maze, width, height, j, i, printUn) != 1)
                {
                    if (print)
                        printf("    -10, multiple or no paths found around end\n");
                    endDiverges = 10;
                }
                endFound = 1;
            }
            else if (maze[i][j] == PATH)
            {
                dotCount++;
                if (countSurroundingPath(maze, width, height, j, i, printUn) != 2)
                {
                    if (print)
                        printf("    -50, path branches has a break or reaches a deadend\n");
                    pathDiverges = 50;
                }
            }
        }
    }
    if (endFound == 0)
    {
        if (print)
            printf("    -10, end is overwritten\n");
        endOverwritten = 10;
    }
    int incomp = 0;
    if (dotCount < dist)
    {
        if (print)
            printf("    -50 incomplete maze solution\n");
        incomp = 50;   
    }
    return incomp + startOverwritten + endOverwritten + startDiverges + endDiverges + pathDiverges;
}

// Frees the memory allocated for maze
void freeMaze(char ** maze, int height)
{
    int i;
    for(i = 0; i < height; i++)
    {
        free(maze[i]);
    }
    free(maze);
}
