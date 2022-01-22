#include <iostream>
#include <conio.h>

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
enum direction {STOP = 0, LEFT, RIGHT, UP, DOWN};
direction dir;
void setup()
{
  gameOver = false;
  dir = STOP;
  x = width / 2;
  y = height / 2;
  fruitX = rand() % width;
  fruitY = rand() % height;
  score = 0;
}

void draw()
{
  // cls for windows, clear for linux/macos
  #ifdef _WIN32
  system("cls);")
  #else
  system("clear"); 
  #endif

  for (int i = 0; i < width; i++) 
  {
    std::cout << '#';
  }

  std::cout << std::endl;

  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      if (j == 0 || j == width - 1) 
      {
        std::cout << '#';
      } 
      if (i == y && j == x) 
      {
        std::cout << "O";
      } 
      else if (i == fruitY && j == fruitX) 
      {
        std::cout << "F";
      } 
      else 
      {
        std::cout << " ";
      }
    }
    std::cout << std::endl;
  }

  for (int i = 0; i < width; i++) 
  {
    std::cout << '#';
  }
  std::cout << std::endl;
}

void input() 
{
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
        gameOver = true;
        break;
    }
  }
}

void logic()
{
  switch (dir)
  {
    case LEFT:
      x--;
      break;
    case RIGHT:
      x++;
      break;
    case UP:
      y--;
      break;
    case DOWN:
      y++;
      break;
    default:
      break;
  }
}

auto main() -> int 
{
  setup();
  while(!gameOver)
  {
    draw();
    input();
    logic();
  }
  return 0;
}
