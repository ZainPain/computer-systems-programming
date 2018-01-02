#define WALL    '%'
#define EMPTY   ' '
#define START   'S'
#define END     'E'
#define PATH    '.'
#define VISITED '~'

void findStartEnd(char ** maze, int width, int height, int * xStart, int * yStart, int * xEnd, int * yEnd);
void printMaze(char ** maze, int width, int height);
int solveMazeManhattanDFS(char ** maze, int width, int height, int xPos, int yPos, int xEnd, int yEnd);
int checkMaze(char ** maze, int width, int height, int x, int y);

int solveMazeBFS(char ** maze, int width, int height, int xPos, int yPos);

void enqueue(int * queue, int value, int * head, int * tail, int maxSize);
int dequeue(int * queue, int * head, int * tail, int maxSize);

