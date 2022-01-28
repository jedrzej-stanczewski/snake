#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <time.h>

bool gameOver;
const int width = 20;
const int height = 20;
int headX, headY, foodX, foodY, score;
int tailX[100], tailY[100];
int tailLength;
enum direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
direction dir;
int gameSpeed;

void setup()
{
    gameOver = false;
    dir = STOP;
    headX = width / 2;
    headY = height / 2;
    foodX = rand() % (width + 1);
    foodY = rand() % height;
    score = 0;
}

void draw()
{
    // cls for windows, clear for linux/macos
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    // drawing top wall (first wall of #)
    for (int i = 0; i < width + 1; i++)
    {
        std::cout << '#';
    }

    std::cout << "\n";

    for (int i = 0; i < height; i++) // for each row
    {
        for (int j = 0; j < width; j++) // for each column in a row
        {
            if (j == 0 || j == width - 1) // first and last column
            {
                std::cout << '#';  // drawing left and right wall
            }
            if (i == headY && j == headX)
            {
                std::cout << "O";  // drawing snake head
            }
            else if (i == foodY && j == foodX)
            {
                std::cout << "o";  // drawing food
            }
            else
            {
                bool draw = false;
                for (int k = 0; k < tailLength; k++) //  iterating over snake's tail
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        std::cout << "o";  // drawing snake tail
                        draw = true;
                    }
                }
                if (draw == false)
                {
                    std::cout << " ";  // basically rest of the map
                }
            }
        }
        std::cout << "\n";
    }

    for (int i = 0; i < width + 1; i++)  // for each column in the last row
    {
        std::cout << '#';  // drawing bottom wall
    }
    std::cout << "\n";
    std::cout << "score: " << score << "\n";
    std::cout << "To quit the game, press X" << "\n";
}

void input()
{
    // keyboard presses defined
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;  // 'x' stops the game
            break;
        }
    }
}

void logic()
{
    // tracking the tail
    int previousX = tailX[0];
    int previousY = tailY[0];
    int previous2X, previous2Y;
    tailX[0] = headX; 
    tailY[0] = headY;
    for (int i = 1; i < tailLength; i++) // for each element of the tail
    {
        previous2X = tailX[i];
        previous2Y = tailY[i];
        tailX[i] = previousX;
        tailY[i] = previousY;
        previousX = previous2X;
        previousY = previous2Y;
    } 

    // steering the snake
    switch (dir)
    {
    case LEFT:
        headX--;
        break;
    case RIGHT:
        headX++;
        break;
    case UP:
        headY--;
        break;
    case DOWN:
        headY++;
        break;
    default:
        break;
    }

    // wall collision
    /*
    if (headX > width - 2 || headX < 0)
    {
        gameOver = true;
    }
    if (headY > height || headY < 0)
    {
        gameOver = true;
    } 
    */

    // no wall collision
    if (headX >= width - 1)
    {
        headX = 0;
    }
    else if (headX < 0)
    {
        headX = width - 2;
    }
    if (headY >= height)
    { 
        headY = 0;
    }
    else if (headY < 0)
    {
        headY = height - 1;
    }
    for (int i = 0; i < tailLength; i++)
    {
        if (tailX[i] == headX && tailY[i] == headY)
        {
            gameOver = true;
        }
    }
    // if snake eats the food
    if (headX == foodX && headY == foodY)
    {
        score += 10;
        foodX = rand() % width;
        foodY = rand() % height;
        tailLength++;
    }
}

auto main() -> int
{
    std::cout << "How difficult do You want the game to be? Type 1, 2, 3 or 4. 1 is the slowest mode, 4 is the fastest." << std::endl;
    std::cin >> gameSpeed;
    srand(time(NULL));
    setup();
    while (!gameOver)
    {
        if (gameSpeed == 1 || gameSpeed == 2 || gameSpeed == 3 || gameSpeed == 4) {
            draw();
            input();
            logic();
            if (gameSpeed == 1) {
                if (dir == LEFT || dir == RIGHT)
                {
                    Sleep(100);
                }
                else if (dir == UP || dir == DOWN)
                {
                    Sleep(120);
                }
            }
            else if (gameSpeed == 2) {
                if (dir == LEFT || dir == RIGHT)
                {
                    Sleep(70);
                }
                else if (dir == UP || dir == DOWN)
                {
                    Sleep(90);
                }
            }
            else if (gameSpeed == 3) {
                if (dir == LEFT || dir == RIGHT)
                {
                    Sleep(30);
                }
                else if (dir == UP || dir == DOWN)
                {
                    Sleep(50);
                }
            }
            else if (gameSpeed == 4) {
                if (dir == LEFT || dir == RIGHT)
                {
                    Sleep(10);
                }
                else if (dir == UP || dir == DOWN)
                {
                    Sleep(30);
                }
            }
        }
        else
        {
            std::cout << "Improper value submitted or some other error occured." << "\n";
            break;
        }
    }
    return 0;
}
