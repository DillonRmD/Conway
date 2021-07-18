// std
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#ifdef _WIN32
#define WIN32_MEAN_AND_LEAN // make windows code robust
//windows
#include <windows.h>
#endif

//NOTE(Dillon): This determines the Max Grid Size
#define MAX_GRID_X_SIZE 20
#define MAX_GRID_Y_SIZE 20

//NOTE(Dillon): Macros that define what a ALIVE and DEAD cell are
#define ALIVE 'o'
#define DEAD 'x'

//NOTE(Dillon): This determines how many generations the algorithm runs over
#define NUM_GENERATIONS 15

//NOTE(Dillon): Time to wait between generations so A.) We dont fry the CPU and B.) We can see the results of each generation
// This also should be in milliseconds
#define TIME_BETWEEN_GENERATIONS 1000 // 1 second

//NOTE(Dillon): This function picks a number between 1 and 2.
// on 1 the current cell is set to be alive otherwise it's dead
//TODO(Dillon): Add a seed based on the current time to make it even more random?
std::vector<std::vector<char>> RandomlyGenerateGrid(int Width, int Height)
{
    //NOTE(Dillon): Grid we will write to and return later
    std::vector<std::vector<char>> Grid;

    //NOTE(Dillon): Iterate over grid
    for (int Y = 0; Y < Height; ++Y)
    {
        //NOTE(Dillon): This vector will hold the current row
        std::vector<char> CurrentRow;

        for (int X = 0; X < Width; ++X)
        {
            //NOTE(Dillon): Assign cell values to current row
            int RandomNum = rand() % 2 + 1;
            if (RandomNum == 1)
            {
                CurrentRow.push_back(ALIVE);
            }
            else
            {
                CurrentRow.push_back(DEAD);
            }
        }
        
        //NOTE(Dillon): Push our current row to the end of the bigger grid
        Grid.push_back(CurrentRow);
    }

    return Grid;
}

#ifdef _WIN32
//NOTE(Dillon): Just iterates over the entire grid and sets colors of text determined
// by the cell's status (i.e. DEAD or ALIVE)
// this has to be a win32 specific function because of how I change the console colors
void Win32PrintEntireGrid(std::vector<std::vector<char>> ParamGrid)
{
    HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int Y = 0; Y < MAX_GRID_Y_SIZE; ++Y)
    {
        for (int X = 0; X < MAX_GRID_X_SIZE; ++X)
        {
            if (ParamGrid[X][Y] == ALIVE)
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
#endif

int main(int ArgumentCount, char *Arguments[])
{
    //NOTE(Dillon): Create the grid
    std::vector<std::vector<char>> Grid = RandomlyGenerateGrid(MAX_GRID_X_SIZE, MAX_GRID_Y_SIZE);

    for (int Generation = 0; Generation < NUM_GENERATIONS; ++Generation)
    {
        for (int Y = 0; Y < MAX_GRID_Y_SIZE; ++Y)
        {
            for (int X = 0; X < MAX_GRID_X_SIZE; ++X)
            {
                //NOTE(Dillon): Before checking the proximity of the current cell we need to keep track of the ALive CellCount
                int AliveCellCount = 0;
                if (X > 0) // we dont want to be on the left most edge of the grid or we will be checking data that doesn't exist, i.e. X[-1]
                {
                    if (Grid[X - 1][Y] == ALIVE) // left
                    {
                        AliveCellCount += 1;
                    }
                }

                if (Y > 0)
                {
                    if (Grid[X][Y - 1] == ALIVE) // up
                    {
                        AliveCellCount += 1;
                    }
                }

                if (Y < MAX_GRID_Y_SIZE - 1)
                {
                    if (Grid[X][Y + 1] == ALIVE) // down
                    {
                        AliveCellCount += 1;
                    }
                }

                if (X < MAX_GRID_X_SIZE - 1)
                {
                    if (Grid[X + 1][Y] == ALIVE) // right
                    {
                        AliveCellCount += 1;
                    }
                }

                if (X > 0 && Y < MAX_GRID_Y_SIZE - 1)
                {
                    if (Grid[X - 1][Y + 1] == ALIVE) //bottom left
                    {
                        AliveCellCount += 1;
                    }
                }

                if (X > 0 && Y > 0)
                {
                    if (Grid[X - 1][Y - 1] == ALIVE) //upper left
                    {
                        AliveCellCount += 1;
                    }
                }

                if (X < (MAX_GRID_X_SIZE - 1) && Y > 0)
                {
                    if (Grid[X + 1][Y - 1] == ALIVE) //upper right
                    {
                        AliveCellCount += 1;
                    }
                }

                if (X < (MAX_GRID_X_SIZE - 1) && Y < (MAX_GRID_Y_SIZE - 1))
                {
                    if (Grid[X + 1][Y + 1] == ALIVE) //bottom right
                    {
                        AliveCellCount += 1;
                    }
                }

                if (AliveCellCount < 2) // underpopulated
                {
                    Grid[X][Y] = DEAD;
                }
                if (AliveCellCount > 3) // overpopulated
                {
                    Grid[X][Y] = DEAD;
                }
                if (AliveCellCount == 3) // reproduction
                {
                    Grid[X][Y] = ALIVE;
                }
            }
        }

#ifdef _WIN32
        system("CLS");
#else
        system("CLEAR");
#endif
        fprintf(stdout, "Generation: %i\n", Generation);
        Win32PrintEntireGrid(Grid);

#ifdef _WIN32
        Sleep(TIME_BETWEEN_GENERATIONS);
#endif
    }

    return 0;
}
