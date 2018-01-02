#include <stdio.h>
#include "maze.h"

/*
 * Zain Paya (zpaya2)
 *
 * This file defines the functions that when given a maze can compute the path
 * to the end using both Manhattan Heuristic Depth First Search and Breadth
 * First Search. It also defines a function to check if the computed path is valid
 * by checking if there are no unnecessary branches of the solution path and if the
 * solution path does not go out of bounds.
 *
 * The DFS solution uses the function stack to traverse the maze and if it reaches
 * a dead end it backtracks (while marking those cells as visited) and tries finding
 * the next closest path to the end. It uses the Manhattan Heuristic to choose the
 * direction that may lead to a closer path to the end.
 *
 * The BFS solution uses a queue to keep track of the neighbors of each cell its visits
 * while traversing the maze. It also keeps a track of all the parent cell of each cell
 * it visits so that it can mark the solution path once the end is found.
 */

/*
 * findStartEnd -- finds the x and y location of the start and end of the  maze
 *                 if the end or start does not exist should output (-1, -1) as the location
 * INPUTS:         maze -- 2D char array that holds the contents of the maze
 *                 width -- width of the maze
 *                 height -- height of the maze
 *                 xStart -- pointer to where x start location should be stored
 *                 yStart -- pointer to where y start location should be stored
 *                 xEnd -- pointer to where x end location should be stored
 *                 yEnd -- pointer to where y end location should be stored
 * OUTPUTS: xStart, yStart, xEnd, and yEnd set to corresponding locations
 * RETURN: none
 * SIDE EFFECTS: none
 */ 
void findStartEnd(char ** maze, int width, int height, int * xStart, int * yStart, int * xEnd, int * yEnd)
{
    // Initialize the output variables
    *xStart = -1;
    *yStart = -1;
    *xEnd = -1;
    *yEnd = -1;

    int row, col;
    // Traverse the 2D maze
    for(row = 0; row < height; row++)
    {
        for(col = 0; col < width; col++)
        {
            // If we find start, modify the start output variables
            if(maze[row][col] == START)
            {
                *xStart = col;
                *yStart = row;
            }
            // If we find end, modify the end output variables
            if(maze[row][col] == END)
            {
                *xEnd = col;
                *yEnd = row;
            }

            // Once both the start and end cells are found, return from function
            if(*xStart != -1 && *xEnd != -1)
                return;
        }
    }
}

/*
 * printMaze -- prints out the maze in a human readable format (should look like examples)
 * INPUTS:      maze -- 2D char array that holds the contents of the maze 
 *              width -- width of the maze
 *              height -- height of the maze
 * OUTPUTS:     none
 * RETURN:      none
 * SIDE EFFECTS: prints the maze to the console
 */
void printMaze(char ** maze, int width, int height)
{
    int row, col;
    // Traverse the 2D maze
    for(row = 0; row < height; row++)
    {
        for(col = 0; col < width; col++)
        {
            // Print the current cell character
            printf("%c", maze[row][col]);
        }
        // Add newline after each row has been printed
        printf("\n");
    }
}

// Constants for the directions to follow according to the Manhattan Heuristic
#define UP     1
#define LEFT   2
#define DOWN   3
#define RIGHT  4

/*
 * This helper function takes in the current cell position and the END cell position
 * and using the Manhattan Heuristic, it calculates the order of directions to
 * take from the current cell which may lead to a closer path. This output array
 * stores the directions in a sorted order.
 */
void calcDirectionArray(int * dirArr, int xPos, int yPos, int xEnd, int yEnd) {
    int distX, distY, dist_UP, dist_LEFT, dist_DOWN, dist_RIGHT;

    // Calculate the corresponding Manhattan distances of the 4 neighboring
    // cells to the END cell. We also initialize the direction array which
    // we will later sort
    distX = (xPos - xEnd >= 0) ? xPos - xEnd : xEnd - xPos;
    distY = ((yPos-1) - yEnd >= 0) ? (yPos-1) - yEnd : yEnd - (yPos-1);
    dist_UP = distX + distY;
    dirArr[0] = dist_UP;

    distX = ((xPos-1) - xEnd >= 0) ? (xPos-1) - xEnd : xEnd - (xPos-1);
    distY = (yPos - yEnd >= 0) ? yPos - yEnd : yEnd - yPos;
    dist_LEFT = distX + distY;
    dirArr[1] = dist_LEFT;

    distX = (xPos - xEnd >= 0) ? xPos - xEnd : xEnd - xPos;
    distY = ((yPos+1) - yEnd >= 0) ? (yPos+1) - yEnd : yEnd - (yPos+1);
    dist_DOWN = distX + distY;
    dirArr[2] = dist_DOWN;

    distX = ((xPos+1) - xEnd >= 0) ? (xPos+1) - xEnd : xEnd - (xPos+1);
    distY = (yPos - yEnd >= 0) ? yPos - yEnd : yEnd - yPos;
    dist_RIGHT = distX + distY;
    dirArr[3] = dist_RIGHT;

    // Sort the distances using Bubble Sort
    int i, j, swap;
    for(i = 0; i < 4-1; i++) {
        for(j = 0; j < 4-i-1; j++) {
            if(dirArr[j] > dirArr[j+1])
            {
                swap = dirArr[j];
                dirArr[j] = dirArr[j+1];
                dirArr[j+1] = swap;
            }
        }
    }

    // Replace the distance values with the direction constants
    int idx = 0;
    for(idx = 0; idx < 4; idx++)
    {
        if(dirArr[idx] == dist_UP)
        {
            dirArr[idx] = UP;
            dist_UP = -1;
        }
        else if(dirArr[idx] == dist_LEFT)
        {
            dirArr[idx] = LEFT;
            dist_LEFT = -1;
        }
        else if(dirArr[idx] == dist_DOWN)
        {
            dirArr[idx] = DOWN;
            dist_DOWN = -1;
        }
        else if(dirArr[idx] == dist_RIGHT)
        {
            dirArr[idx] = RIGHT;
            dist_RIGHT = -1;
        }
    }
}

/*
 * This is the helper function for the Manhattan Heuristic DFS solution.
 */
int solveMazeManhattanDFSHelper(char ** maze, int width, int height, int xPos, int yPos, int xEnd, int yEnd)
{
    // Check base cases
    // Check if out of bounds
    if(xPos < 0 || xPos >= width || yPos < 0 || yPos >= height)
        return 0;
    // Check if not empty cell
    if(maze[yPos][xPos] == WALL || maze[yPos][xPos] == VISITED || maze[yPos][xPos] == PATH)
        return 0;
    // Check if end of maze
    if(maze[yPos][xPos] == END)
        return 1;

    // Recursive case
    // Set current postion as a visited cell
    maze[yPos][xPos] = VISITED;

    // Calculate manhattan distance array using helper function
    int dirArr[4];
    calcDirectionArray(dirArr, xPos, yPos, xEnd, yEnd);

    // Loop through the sorted direction array
    int idx = 0;
    for(idx = 0; idx < 4; idx++)
    {
        if(dirArr[idx] == UP)
        {
            // Do the recursive call on the upper neighboring cell
            if(solveMazeManhattanDFSHelper(maze, width, height, xPos, yPos-1, xEnd, yEnd) == 1)
            {
                // Mark this position as a PATH cell instead
                if(maze[yPos][xPos] != START)
                    maze[yPos][xPos] = PATH;
                return 1;
            }
        }
        if(dirArr[idx] == LEFT)
        {
            // Do the recursive call on the left neighboring cell
            if(solveMazeManhattanDFSHelper(maze, width, height, xPos-1, yPos, xEnd, yEnd) == 1)
            {
                // Mark this position as a PATH cell instead
                if(maze[yPos][xPos] != START)
                    maze[yPos][xPos] = PATH;
                return 1;
            }
        }
        if(dirArr[idx] == DOWN)
        {
            // Do the recursive call on the lower neighboring cell
            if(solveMazeManhattanDFSHelper(maze, width, height, xPos, yPos+1, xEnd, yEnd) == 1)
            {
                // Mark this position as a PATH cell instead
                if(maze[yPos][xPos] != START)
                    maze[yPos][xPos] = PATH;
                return 1;
            }
        }
        if(dirArr[idx] == RIGHT)
        {
            // Do the recursive call on the right neighboring cell
            if(solveMazeManhattanDFSHelper(maze, width, height, xPos+1, yPos, xEnd, yEnd) == 1)
            {
                // Mark this position as a PATH cell instead
                if(maze[yPos][xPos] != START)
                    maze[yPos][xPos] = PATH;
                return 1;
            }
        }
    }

    // Solution wasn't found with current cell, return 0
    return 0;
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search and a manhattan distance heuristic
 * INPUTS:                  maze -- 2D char array that holds the contents of the maze
 *                          width -- the width of the maze
 *                          height -- the height of the maze
 *                          xPos -- the current x position within the maze
 *                          yPos -- the current y position within the maze
 *                          xEnd -- the x position of the end of the maze
 *                          yEnd -- the y position of the end of the maze
 * OUTPUTS:                 updates maze with the solution path ('.') and visited nodes ('~')
 * RETURNS:                 0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:            none
 */ 
int solveMazeManhattanDFS(char ** maze, int width, int height, int xPos, int yPos, int xEnd, int yEnd)
{
    // Call the helper function
    int solved = solveMazeManhattanDFSHelper(maze, width, height, xPos, yPos, xEnd, yEnd);
    // Restore the START character in the maze at the given starting position
    maze[yPos][xPos] = START;
    return solved;
}

/*
 * This is the helper function for the checkMaze function.
 */
int checkMazeHelper(char ** maze, int width, int height, int x, int y, int prev_x, int prev_y)
{
    // Base cases
    // Check if we have gone out of bounds
    if(x < 0 || x >= width || y < 0 || y >= height)
        return 0;
    // Check if current position is end
    if(maze[y][x] == END)
        return 1;

    // Recursive case (start, path)
    // Variables to store if we see paths to any of the 4 neighboring directions
    int up = 0, left = 0, down = 0, right = 0;
    int pathsum = 0;

    if(y-1 != prev_y && y-1 >= 0 && (maze[y-1][x] == PATH || maze[y-1][x] == END))
        up++;
    if(x-1 != prev_x && x-1 >= 0 && (maze[y][x-1] == PATH || maze[y][x-1] == END))
        left++;
    if(y+1 != prev_y && y+1 < height && (maze[y+1][x] == PATH || maze[y+1][x] == END))
        down++;
    if(x+1 != prev_x && x+1 < width && (maze[y][x+1] == PATH || maze[y][x+1] == END))
        right++;

    // If more than one direction (other than the previous direction) leads to a path,
    // we know the maze solution is incorrect
    pathsum = up + left + down + right;
    if (pathsum != 1)
        return 0;
    else
    {
        // Do the recursive calls in the direction we find an available path in
        if(up == 1)
            return checkMazeHelper(maze, width, height, x, y-1, x, y);
        else if(left == 1)
            return checkMazeHelper(maze, width, height, x-1, y, x, y);
        else if(down == 1)
            return checkMazeHelper(maze, width, height, x, y+1, x, y);
        else //if(right == 1)
            return checkMazeHelper(maze, width, height, x+1, y, x, y);
    }
 }

/*
 * checkMaze -- checks if a maze has a valid solution or not
 * INPUTS:      maze -- 2D char array that holds the contents of the maze
 *              width -- width of the maze
 *              height -- height of the maze
 *              x -- the starting x position in the maze
 *              y -- the starting y position in the maze
 * OUTPUTS:     none
 * RETURN:      1 if the maze has a valid solution, otherwise 0
 * SIDE EFFECTS: none
 */
int checkMaze(char ** maze, int width, int height, int x, int y)
{
    // Call the recursive helper function with previous position as -1,-1
    // as there is no previous position for the start
    return checkMazeHelper(maze, width, height, x, y, -1, -1);
}

/*
 * solveMazeBFS -- solves the maze using a breadth first search algorithm
 * INPUTS:         maze -- A 2D array that contains the contents of the maze
 *                 width -- the width of the maze
 *                 height -- the height of the maze
 *                 xPos -- the starting x position within the maze
 *                 yPos -- the starting y position within the maze
 * OUTPUTS:        none
 * RETURNS:        0 if the maze is unsolvable, else 1
 * SIDE EFFECTS:   marks the cells within the maze as visited or part of the solution path
 */
int solveMazeBFS(char ** maze, int width, int height, int xPos, int yPos)
{
    // Initialize the total queue size and the queue variables (queue, head and tail)
    int qsize = width * height;
    int queue[qsize];
    int head = 0;
    int tail = 0;

    // Initialize the parents array to value -1
    int parents[qsize];
    int idx_parents;
    for(idx_parents = 0; idx_parents < qsize; idx_parents++)
        parents[idx_parents] = -1;

    // Enqueue the starting cell
    enqueue(queue, yPos*width + xPos, &head, &tail, qsize);

    int idx, row, col;
    // While the queue is not empty
    while(head != tail)
    {
        // Dequeue the first cell in the queue
        idx = dequeue(queue, &head, &tail, qsize);
        // Calculate the row and col coordinates from the dequeued index value
        row = idx / height;
        col = idx % width;

        // If the current cell is the END cell
        if (maze[row][col] == END)
        {
            // Traverse parents until we reach the START cell
            while(maze[row][col] != START)
            {
                // Compute the index of parent of this cell
                idx = parents[idx];
                row = idx / height;
                col = idx % width;
                // Mark the parent cell as part of the solution path
                if(maze[row][col] != START)
                    maze[row][col] = PATH;
            }
            // Return 1: we have solved the maze
            return 1;
        }
        // We are at an internal cell
        else
        {
            // Mark this cell as a VISITED cell
            if(maze[row][col] != START)
                maze[row][col] = VISITED;

            // Compute the indices of the neighboring cells, if they exist
            int idx_up, idx_left, idx_down, idx_right;
            idx_up    = (row-1 < 0)       ?  -1 : ((row-1) * width) + col;
            idx_left  = (col-1 < 0)       ?  -1 : (row * width) + (col-1);
            idx_down  = (row+1 >= height) ?  -1 : ((row+1) * width) + col;
            idx_right = (col+1 >= width)  ?  -1 : (row * width) + (col+1);

            // If the neighboring cell is accessible, we enqueue it and mark the parent cell
            if(idx_up != -1 && (maze[row-1][col] == EMPTY || maze[row-1][col] == END))
            {
                enqueue(queue, idx_up, &head, &tail, qsize);
                parents[idx_up] = idx;
            }
            if(idx_left != -1 && (maze[row][col-1] == EMPTY || maze[row][col-1] == END))
            {
                enqueue(queue, idx_left, &head, &tail, qsize);
                parents[idx_left] = idx;
            }
            if(idx_down != -1 && (maze[row+1][col] == EMPTY || maze[row+1][col] == END))
            {
                enqueue(queue, idx_down, &head, &tail, qsize);
                parents[idx_down] = idx;
            }
            if(idx_right != -1 && (maze[row][col+1] == EMPTY || maze[row][col+1] == END))
            {
                enqueue(queue, idx_right, &head, &tail, qsize);
                parents[idx_right] = idx;
            }
        }
    }

    // We have not found a solution to the maze, return 0
    return 0;
}

/*
 * enqueue -- enqueues an integer onto the given queue
 * INPUTS:    queue -- a pointer to the array that will hold the contents of the queue
 *            value -- the value to  enqueue
 *            head -- a pointer to a variable that contains the head index in the queue
 *            tail -- a pointer to a variable that contains the tail index in the queue
 *            maxSize -- the maximum size of the queue (size of the array)
 * OUTPUTS:   none
 * RETURNS:   none
 * SIDE EFFECTS: adds an item to the queue
 */ 
void enqueue(int * queue, int value, int * head, int * tail, int maxSize)
{
    if ((*tail - maxSize) == *head)
    {
        printf("Queue is full\n");
        return;
    }
    *tail = *tail + 1;
    queue[*tail % maxSize] = value;
}

/* dequeue -- dequeues an item from the given queue
 * INPUTS:    queue -- a pointer to the array that holds the contents of the queue
 *            head -- a pointer to a variable that contains the head index in the queue
 *            tail -- a pointer to a variable that contains the tail index in the queue
 *            maxSize -- the maximum size of the queue (size of the array)
 * OUTPUTS:   none
 * RETURNS:   the value dequeued from the queue
 * SIDE EFFECTS: removes an item from the queue
 */
int dequeue(int * queue, int * head, int * tail, int maxSize)
{
    if (*head == *tail)
    {
        printf("Queue is empty\n");
        return -1;
    }
    *head = *head + 1;
    return queue[*head % maxSize];
}
