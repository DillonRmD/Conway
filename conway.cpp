#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <windows.h>

#define global static
#define local static
#define internal static

#define MAX_X_SIZE 20
#define MAX_Y_SIZE 20

#define ALIVE 'o'
#define DEAD 'x'

#define NUM_GENERATIONS 100

int Grid[MAX_X_SIZE][MAX_Y_SIZE] =
{
    'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'o', 'x', 'o', 'o', 'o', 'o', 'o', 'o', 'x', 'o',
    'o', 'x', 'o', 'o', 'o', 'o', 'o', 'o', 'x', 'o', 'o', 'x', 'o', 'o', 'o', 'o', 'o', 'o', 'x', 'o',
    'o', 'o', 'o', 'x', 'o', 'o', 'o', 'x', 'o', 'o', 'o', 'x', 'o', 'o', 'o', 'o', 'o', 'o', 'x', 'o',
    'o', 'x', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'x', 'o', 'o', 'o', 'o', 'o', 'o', 'x', 'o',
    'o', 'o', 'x', 'o', 'o', 'o', 'o', 'x', 'o', 'o', 'o', 'x', 'o', 'o', 'o', 'o', 'o', 'o', 'x', 'o',
    'o', 'o', 'x', 'x', 'o', 'o', 'x', 'o', 'o', 'o', 'o', 'x', 'o', 'o', 'o', 'o', 'o', 'o', 'x', 'o',
    'o', 'x', 'x', 'x', 'o', 'x', 'o', 'o', 'x', 'o', 'o', 'x', 'o', 'o', 'o', 'o', 'o', 'o', 'x', 'o',
    'o', 'x', 'x', 'o', 'x', 'o', 'o', 'o', 'o', 'o', 'o', 'x', 'o', 'o', 'o', 'o', 'o', 'o', 'x', 'o',
    'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'x', 'o', 'o', 'o', 'o', 'o', 'o', 'x', 'o',
    'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'x', 'o', 'o', 'o', 'o', 'o', 'o', 'x', 'o',
    'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'o', 'x', 'o', 'o', 'o', 'o', 'o', 'o', 'x', 'o',
    'o', 'x', 'o', 'o', 'o', 'o', 'o', 'o', 'x', 'o', 'o', 'x', 'o', 'o', 'o', 'o', 'o', 'o', 'x', 'o',
    'o', 'o', 'o', 'x', 'o', 'o', 'o', 'x', 'o', 'o', 'o', 'x', 'o', 'o', 'o', 'o', 'o', 'o', 'x', 'o',
    'o', 'x', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'x', 'o', 'o', 'o', 'o', 'o', 'o', 'x', 'o',
    'o', 'o', 'x', 'o', 'o', 'o', 'o', 'x', 'o', 'o', 'o', 'x', 'o', 'o', 'o', 'o', 'o', 'o', 'x', 'o',
    'o', 'o', 'x', 'x', 'o', 'o', 'x', 'o', 'o', 'o', 'o', 'x', 'o', 'o', 'o', 'o', 'o', 'o', 'x', 'o',
    'o', 'x', 'x', 'x', 'o', 'x', 'o', 'o', 'o', 'o', 'o', 'x', 'o', 'o', 'o', 'o', 'o', 'o', 'x', 'o',
    'o', 'x', 'x', 'o', 'x', 'o', 'o', 'o', 'o', 'o', 'o', 'x', 'o', 'o', 'o', 'o', 'o', 'o', 'x', 'o',
    'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'x', 'o', 'o', 'o', 'o', 'o', 'o', 'x', 'o',
    'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'x', 'o', 'o', 'o', 'o', 'o', 'o', 'x', 'o',
};

void PrintEntireGrid(int ParamGrid[MAX_X_SIZE][MAX_Y_SIZE])
{
    HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    for(int Y = 0; Y < MAX_Y_SIZE; ++Y)
    {
        for(int X = 0; X < MAX_X_SIZE; ++X)
        {
            if(ParamGrid[X][Y] == ALIVE)
            {
                SetConsoleTextAttribute(ConsoleHandle, 10); // bright green
            }
            else if (ParamGrid[X][Y] == DEAD)
            {
                SetConsoleTextAttribute(ConsoleHandle, 12); // bright red
            }
            
            fprintf(stdout, " %c ", ParamGrid[X][Y]);
            SetConsoleTextAttribute(ConsoleHandle, 7); // bright red
        }
        fprintf(stdout, "\n");
    }
}

int main(int ArgumentCount, char* Arguments[])
{
    for(int Generation = 0; Generation < NUM_GENERATIONS; ++Generation)
    {
        for(int Y = 0; Y < MAX_Y_SIZE; ++Y)
        {
            for(int X = 0; X < MAX_X_SIZE; ++X)
            {
                if(Grid[X][Y] == ALIVE)
                {
                    int LiveCellCount = 0;
                    if(Grid[X - 1][Y] == ALIVE) // left
                    {
                        LiveCellCount += 1;
                    }
                    if(Grid[X + 1][Y] == ALIVE) // right
                    {
                        LiveCellCount += 1;
                    }
                    if(Grid[X][Y - 1] == ALIVE) // up
                    {
                        LiveCellCount += 1;
                    }
                    if(Grid[X][Y + 1] == ALIVE) // down
                    {
                        LiveCellCount += 1;
                    }
                    if(Grid[X - 1][Y - 1] == ALIVE) //upper left
                    {
                        LiveCellCount += 1;
                    }
                    if(Grid[X + 1][Y - 1] == ALIVE) //upper right
                    {
                        LiveCellCount += 1;
                    }
                    if(Grid[X - 1][Y + 1] == ALIVE) //bottom left
                    {
                        LiveCellCount += 1;
                    }
                    if(Grid[X + 1][Y + 1] == ALIVE) //bottom right
                    {
                        LiveCellCount += 1;
                    }
                    
                    if(LiveCellCount < 2) // underpopulated
                    {
                        Grid[X][Y] = DEAD;
                    }
                    if(LiveCellCount > 3) // overpopulated
                    {
                        Grid[X][Y] = DEAD;
                    }
                }
                
                if(Grid[X][Y] == DEAD)
                {
                    int LiveCellCount = 0;
                    if(Grid[X - 1][Y] == ALIVE) // left
                    {
                        LiveCellCount += 1;
                    }
                    if(Grid[X + 1][Y] == ALIVE) // right
                    {
                        LiveCellCount += 1;
                    }
                    if(Grid[X][Y - 1] == ALIVE) // up
                    {
                        LiveCellCount += 1;
                    }
                    if(Grid[X][Y + 1] == ALIVE) // down
                    {
                        LiveCellCount += 1;
                    }
                    if(Grid[X - 1][Y - 1] == ALIVE) //upper left
                    {
                        LiveCellCount += 1;
                    }
                    if(Grid[X + 1][Y - 1] == ALIVE) //upper right
                    {
                        LiveCellCount += 1;
                    }
                    if(Grid[X - 1][Y + 1] == ALIVE) //bottom left
                    {
                        LiveCellCount += 1;
                    }
                    if(Grid[X + 1][Y + 1] == ALIVE) //bottom right
                    {
                        LiveCellCount += 1;
                    }
                    
                    if(LiveCellCount == 3) // reproduction
                    {
                        Grid[X][Y] = ALIVE;
                    }
                    
                }
            }
        }
        
        #ifdef _WIN32
        system("CLS");
        #else
        system("CLEAR");
        #endif
        
        fprintf(stdout, "\rGeneration: %i\n", Generation);
        PrintEntireGrid(Grid);
        
        Sleep(1500);
        
    }
    
    return 0;
}
