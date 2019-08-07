#include "PipeDream.h"
#include "screen.h"
#include "keypad.h"

#define ROWS 30
#define COLUMNS 80

#define PIPE_NUMB 8

#define MAP_ROWS 7
#define MAP_COLUMNS 10

#define TIME_LIMIT_EASY 40000
#define TIME_LIMIT_MEDIUM 30000
#define TIME_LIMIT_HARD 20000

static volatile unsigned int *counter = MS_COUNTER_REG_ADDR;

uint8_t pipeQueue[4] = {0, 0, 0, 0};

uint8_t pipeMap[MAP_ROWS][MAP_COLUMNS];

uint8_t *cursorPosition = 0;
uint8_t *initialPipePosition = 0;
uint8_t *secondPipePosition = 0;
uint16_t score = 0;

static uint8_t randPipes[] = {0, 1, 3, 6, 5, 2, 1, 1, 0, 0, 3, 6, 0, 0, 1, 5, 1, 4, 5, 1, 6, 4, 6, 6, 0, 6, 5, 1, 5, 6, 0, 6, 6, 0, 2, 0, 6, 5, 0, 0, 5, 6, 0, 3, 2, 0, 5, 6, 1, 2, 3, 6, 1, 6, 1, 3, 2, 1, 5, 6, 2, 3, 0, 5, 6, 1, 5, 6, 6, 4, 6, 5, 3, 6, 5, 4, 1, 6, 5, 1, 3, 0, 6, 5, 4, 1};
uint8_t randPipeCounter = 0;

uint8_t generate_rand()
{
    randPipeCounter++;
    if (randPipeCounter > 85)
        randPipeCounter = 0;
    return randPipes[randPipeCounter];
}

uint32_t getTime()
{
    return *counter;
}

/* void set_initial_square()
{
    uint8_t column = generate_rand();
    uint8_t row = generate_rand() & 6;

    pipeMap[row][column] = generate_initial_pipe();
    initialPipePosition = &pipeMap[row][column];
} */

/* 
0 = |
1 = -
2 = Cross
3 = L-U
4 = U-R
5 = R-D
6 = D-L
7 = 3
 */
uint8_t generate_initial_pipe()
{
    uint8_t randPipe = generate_rand() & 0b00000011;
    return randPipe;
}

void generate_initial_PQueue()
{
    pipeQueue[0] = generate_rand();
    pipeQueue[1] = generate_rand();
    pipeQueue[2] = generate_rand();
    pipeQueue[3] = generate_rand();
}

void push_queue()
{
    pipeQueue[3] = generate_rand();
}
uint8_t pop_queue()
{
    uint8_t value = pipeQueue[0];
    shift_queue();
    push_queue();
    return value;
}

void shift_queue()
{
    pipeQueue[0] = pipeQueue[1];
    pipeQueue[1] = pipeQueue[2];
    pipeQueue[2] = pipeQueue[3];
}

void generate_map()
{
    reset_map();
    generate_initial_PQueue();
    set_initial_square();
    set_cursor_position(0, 0);
}

void game_init()
{
    generate_map();
    keypad_init();
}

void end_game()
{
    set_cursor(10, 34);
    set_color(4, 15);

    puts("GAME OVER!");
}

void moveCursor(uint8_t input)
{
    if (input == 1) // left
    {
        if (cursorPosition != &pipeMap[0][0] &&
            cursorPosition != &pipeMap[1][0] &&
            cursorPosition != &pipeMap[2][0] &&
            cursorPosition != &pipeMap[3][0] &&
            cursorPosition != &pipeMap[4][0] &&
            cursorPosition != &pipeMap[5][0] &&
            cursorPosition != &pipeMap[6][0])
        {
            cursorPosition--;
        }
    }
    else if (input == 2) // right
    {
        if (cursorPosition != &pipeMap[0][9] &&
            cursorPosition != &pipeMap[1][9] &&
            cursorPosition != &pipeMap[2][9] &&
            cursorPosition != &pipeMap[3][9] &&
            cursorPosition != &pipeMap[4][9] &&
            cursorPosition != &pipeMap[5][9] &&
            cursorPosition != &pipeMap[6][9])
        {
            cursorPosition++;
        }
    }
    else if (input == 3) // down
    {
        if (cursorPosition < &pipeMap[6][0])
        {
            cursorPosition += 10;
        }
    }
    else if (input == 4) // up
    {
        if (cursorPosition > &pipeMap[0][9])
        {
            cursorPosition -= 10;
        }
    }
    else if (input == 5)
    {
        place_pipe();
    }
}

uint8_t num_of_pipes = 0;

void game_start()
{
    game_init();
    bool gameEnd = false;

    uint32_t time = *MS_COUNTER_REG_ADDR;
    uint32_t difficulty = TIME_LIMIT_EASY;

    print_map();
    while (!gameEnd)
    {
        if (*MS_COUNTER_REG_ADDR - time >= difficulty)
        {
            count_first_pipe();
            if (num_of_pipes < 8)
                break;
            else
            {
                generate_map();
                if (difficulty == TIME_LIMIT_EASY)
                    difficulty = TIME_LIMIT_MEDIUM;
                else if (difficulty == TIME_LIMIT_MEDIUM)
                    difficulty = TIME_LIMIT_HARD;
                continue;
            }
        }
        if (keypad_getkey() != 0)
        {
            moveCursor(keypad_getkey());
            set_color(BLACK, BLACK);
            clear_screen();
            print_map();
            delay_ms(150);
        }
    }
    end_game();
}

void reset_map()
{
    for (uint8_t i = 0; i < MAP_ROWS; i++)
    {
        for (uint8_t j = 0; j < MAP_COLUMNS; j++)
        {
            pipeMap[i][j] = 7;
        }
    }
}

void set_cursor_position(uint8_t row, uint8_t column)
{
    cursorPosition = &pipeMap[row][column];
}

/* 
0 = |
1 = -
2 = Cross
3 = L-U
4 = U-R
5 = R-D
6 = D-L
7 = empty

    Initial Pipe
0 = Up
1 = Right
2 = Down
3 = Left
 */

void count_first_pipe()
{
    num_of_pipes = 0;
    if (*initialPipePosition == 0)
        count_pipes(initialPipePosition, initialPipePosition - 10);
    if (*initialPipePosition == 1)
        count_pipes(initialPipePosition, initialPipePosition + 1);
    if (*initialPipePosition == 2)
        count_pipes(initialPipePosition, initialPipePosition + 10);
    if (*initialPipePosition == 3)
        count_pipes(initialPipePosition, initialPipePosition - 1);
}

/* 
0 = |
1 = -
2 = Cross
3 = L-U
4 = U-R
5 = R-D
6 = D-L
7 = empty

    Initial Pipe
0 = Up
1 = Right
2 = Down
3 = Left
 */

void count_pipes(uint8_t * prev, uint8_t * next)
{
    num_of_pipes++;
    // Run this code
    if (*next == 0) // |
    {
        if ((*(next - 10) == 0 ||
            *(next - 10) == 2 || 
            *(next - 10) == 5 ||
            *(next - 10) == 6 ||
            *(next + 10) == 0 || 
            *(next + 10) == 2 || 
            *(next + 10) == 3 || 
            *(next + 10) == 4 ) && 
            (prev == next + 10 || 
             prev == next - 10))
        {
            count_pipes(next, prev == (next + 10) ? (next - 10) : (next - 10));
        }
    }
    else if (*next == 1) // -
    {
        if ((*(next - 1) == 1 ||
            *(next - 1) == 2 || 
            *(next - 1) == 4 ||
            *(next - 1) == 5 ||
            *(next + 1) == 1 || 
            *(next + 1) == 2 || 
            *(next + 1) == 3 || 
            *(next + 1) == 6 ) && 
            (prev == next + 1 || 
             prev == next - 1))
        {
            count_pipes(next, prev == (next + 1) ? (next - 1) : (next - 1));
        }
    }
    else if (*next == 2) // Cross
    {
        if (prev == next - 1)
        {
            if (*(next + 1) == 1 || 
            *(next + 1) == 2 || 
            *(next + 1) == 3 || 
            *(next + 1) == 6 )
            {
                count_pipes(next, next + 1);
            }
        }
        else if (prev == next + 1)
        {
            if (*(next - 1) == 1 ||
            *(next - 1) == 2 || 
            *(next - 1) == 4 ||
            *(next - 1) == 5)
            {
                count_pipes(next, next - 1);
            }
        }
        else if (prev == next - 10)
        {
            if (*(next + 10) == 0 || 
            *(next + 10) == 2 || 
            *(next + 10) == 3 || 
            *(next + 10) == 4)
            {
                count_pipes(next, next + 10);
            }
        }
        else if (prev == next + 10)
        {
            if (*(next - 10) == 0 ||
            *(next - 10) == 2 || 
            *(next - 10) == 5 ||
            *(next - 10) == 6)
            {
                count_pipes(next, next - 10);
            }
        }
    }
    else if (*next == 3) // LU
    {
        if (prev == next - 1)
        {
            if (*(next - 10) == 0 ||
            *(next - 10) == 2 || 
            *(next - 10) == 5 ||
            *(next - 10) == 6)
            {
                count_pipes(next, next - 10);
            }
        }
        else if(prev == next - 10)
        {
             if (*(next - 1) == 1 ||
            *(next - 1) == 2 || 
            *(next - 1) == 4 ||
            *(next - 1) == 5)
            {
                count_pipes(next, next - 1);
            }
        }
    }
    else if (*next == 4) // UR
    {
        if (prev == next - 10)
        {
            if (*(next + 1) == 1 || 
            *(next + 1) == 2 || 
            *(next + 1) == 3 || 
            *(next + 1) == 6 )
            {
                count_pipes(next, next + 1);
            }
        }
        else if (prev == next + 1)
        {
            if (*(next - 10) == 0 ||
            *(next - 10) == 2 || 
            *(next - 10) == 5 ||
            *(next - 10) == 6)
            {
                count_pipes(next, next - 10);
            }
        }
    }
    else if (*next == 5) // RD
    {
        if (prev == next + 1)
        {
            if (*(next + 10) == 0 || 
            *(next + 10) == 2 || 
            *(next + 10) == 3 || 
            *(next + 10) == 4)
            {
                count_pipes(next, next + 10);
            }
        }
        else if(prev == next + 10)
        {
            if (*(next + 1) == 1 || 
            *(next + 1) == 2 || 
            *(next + 1) == 3 || 
            *(next + 1) == 6 )
            {
                count_pipes(next, next + 1);
            }
        }
    }
    else if(*next == 6) // DL
    {
        if (prev == next - 1)
        {
            if (*(next + 10) == 0 || 
            *(next + 10) == 2 || 
            *(next + 10) == 3 || 
            *(next + 10) == 4)
            {
                count_pipes(next, next + 10);
            }
        }
        else if (prev == next + 10)
        {
            if (*(next - 1) == 1 ||
            *(next - 1) == 2 || 
            *(next - 1) == 4 ||
            *(next - 1) == 5)
            {
                count_pipes(next, next - 1);
            }
        }
    }
    else
        num_of_pipes--;
}

void place_pipe()
{
    if (cursorPosition != initialPipePosition)
        *cursorPosition = pop_queue();
}

bool is_initial_pipe(uint8_t row, uint8_t column)
{
    if (&pipeMap[row][column] == initialPipePosition)
        return true;
    return false;
}

void print_map()
{
    // Print the map. Each block is made up of 4 columns. The fifth column separates each block. The same goes for the bottom row of each block.
    // Print the Pipe queue

    print_pipe_queue(3, 8, 3);
    print_pipe_queue(2, 11, 3);
    print_pipe_queue(1, 14, 3);
    print_pipe_queue(0, 17, 3);

    uint8_t arrayR = 0;
    uint8_t arrayC = 0;
    uint8_t mapR = 5;
    uint8_t mapC = 11;

    while (arrayR < 7)
    {

        if (arrayC < 10)
        {
            print_pipe(arrayR, arrayC, mapR, mapC);
            mapC += 5;
            arrayC++;
        }
        else
        {
            mapR += 3;
            mapC = 11;
            arrayR++;
            arrayC = 0;
        }
    }
}

/* 
    0 = |
    1 = -
    2 = Cross
    3 = L-U
    4 = U-R
    5 = R-D
    6 = D-L
    7 = empty
 */

void print_pipe_queue(uint8_t num, uint8_t mapRow, uint8_t mapColumn)
{
    set_color(BLACK, GRAY);
    if (pipeQueue[num] == 0) // |
    {
        set_cursor(mapRow, mapColumn);
        put_char(126);
        set_cursor(mapRow, ++mapColumn);
        put_char(131);
        set_cursor(mapRow, ++mapColumn);
        put_char(130);
        set_cursor(mapRow, ++mapColumn);
        put_char(126);
        mapColumn -= 3;
        set_cursor(++mapRow, mapColumn);
        put_char(126);
        set_cursor(mapRow, ++mapColumn);
        put_char(131);
        set_cursor(mapRow, ++mapColumn);
        put_char(130);
        set_cursor(mapRow, ++mapColumn);
        put_char(126);
    }
    if (pipeQueue[num] == 1) // -
    {
        set_cursor(mapRow, mapColumn);
        put_char(127);
        set_cursor(mapRow, ++mapColumn);
        put_char(127);
        set_cursor(mapRow, ++mapColumn);
        put_char(127);
        set_cursor(mapRow, ++mapColumn);
        put_char(127);
        mapColumn -= 3;
        set_cursor(++mapRow, mapColumn);
        put_char(132);
        set_cursor(mapRow, ++mapColumn);
        put_char(132);
        set_cursor(mapRow, ++mapColumn);
        put_char(132);
        set_cursor(mapRow, ++mapColumn);
        put_char(132);
    }
    if (pipeQueue[num] == 2) // Cross
    {
        set_cursor(mapRow, mapColumn);
        put_char(127);
        set_cursor(mapRow, ++mapColumn);
        put_char(128);
        set_cursor(mapRow, ++mapColumn);
        put_char(129);
        set_cursor(mapRow, ++mapColumn);
        put_char(127);
        mapColumn -= 3;
        set_cursor(++mapRow, mapColumn);
        put_char(132);
        set_cursor(mapRow, ++mapColumn);
        put_char(134);
        set_cursor(mapRow, ++mapColumn);
        put_char(133);
        set_cursor(mapRow, ++mapColumn);
        put_char(132);
    }
    if (pipeQueue[num] == 3) // L-U
    {
        set_cursor(mapRow, mapColumn);
        put_char(127);
        set_cursor(mapRow, ++mapColumn);
        put_char(128);
        set_cursor(mapRow, ++mapColumn);
        put_char(130);
        set_cursor(mapRow, ++mapColumn);
        put_char(126);
        mapColumn -= 3;
        set_cursor(++mapRow, mapColumn);
        put_char(132);
        set_cursor(mapRow, ++mapColumn);
        put_char(132);
        set_cursor(mapRow, ++mapColumn);
        put_char(126);
        set_cursor(mapRow, ++mapColumn);
        put_char(126);
    }
    if (pipeQueue[num] == 4) // U-R
    {
        set_cursor(mapRow, mapColumn);
        put_char(126);
        set_cursor(mapRow, ++mapColumn);
        put_char(131);
        set_cursor(mapRow, ++mapColumn);
        put_char(129);
        set_cursor(mapRow, ++mapColumn);
        put_char(127);
        mapColumn -= 3;
        set_cursor(++mapRow, mapColumn);
        put_char(126);
        set_cursor(mapRow, ++mapColumn);
        put_char(126);
        set_cursor(mapRow, ++mapColumn);
        put_char(132);
        set_cursor(mapRow, ++mapColumn);
        put_char(132);
    }
    if (pipeQueue[num] == 5) // R-D
    {
        set_cursor(mapRow, mapColumn);
        put_char(126);
        set_cursor(mapRow, ++mapColumn);
        put_char(126);
        set_cursor(mapRow, ++mapColumn);
        put_char(127);
        set_cursor(mapRow, ++mapColumn);
        put_char(127);
        mapColumn -= 3;
        set_cursor(++mapRow, mapColumn);
        put_char(126);
        set_cursor(mapRow, ++mapColumn);
        put_char(131);
        set_cursor(mapRow, ++mapColumn);
        put_char(133);
        set_cursor(mapRow, ++mapColumn);
        put_char(132);
    }
    if (pipeQueue[num] == 6) // D-L
    {
        set_cursor(mapRow, mapColumn);
        put_char(127);
        set_cursor(mapRow, ++mapColumn);
        put_char(127);
        set_cursor(mapRow, ++mapColumn);
        put_char(126);
        set_cursor(mapRow, ++mapColumn);
        put_char(126);
        mapColumn -= 3;
        set_cursor(++mapRow, mapColumn);
        put_char(132);
        set_cursor(mapRow, ++mapColumn);
        put_char(134);
        set_cursor(mapRow, ++mapColumn);
        put_char(130);
        set_cursor(mapRow, ++mapColumn);
        put_char(126);
    }
}

void print_pipe(uint8_t row, uint8_t column, uint8_t mapRow, uint8_t mapColumn)
{
    set_color(BLACK, GRAY);
    if (is_initial_pipe(row, column))
        print_initial_pipe(row, column, mapRow, mapColumn);
    else
    {
        if (pipeMap[row][column] == 0) // |
        {
            set_cursor(mapRow, mapColumn);
            if (cursorPosition == &pipeMap[row][column])
                put_char(135);
            else
                put_char(126);
            set_cursor(mapRow, ++mapColumn);
            put_char(131);
            set_cursor(mapRow, ++mapColumn);
            put_char(130);
            set_cursor(mapRow, ++mapColumn);
            put_char(126);
            mapColumn -= 3;
            set_cursor(++mapRow, mapColumn);
            put_char(126);
            set_cursor(mapRow, ++mapColumn);
            put_char(131);
            set_cursor(mapRow, ++mapColumn);
            put_char(130);
            set_cursor(mapRow, ++mapColumn);
            put_char(126);
        }
        else if (pipeMap[row][column] == 1) // -
        {
            set_cursor(mapRow, mapColumn);
            if (cursorPosition == &pipeMap[row][column])
                put_char(136);
            else
                put_char(127);
            set_cursor(mapRow, ++mapColumn);
            put_char(127);
            set_cursor(mapRow, ++mapColumn);
            put_char(127);
            set_cursor(mapRow, ++mapColumn);
            put_char(127);
            mapColumn -= 3;
            set_cursor(++mapRow, mapColumn);
            put_char(132);
            set_cursor(mapRow, ++mapColumn);
            put_char(132);
            set_cursor(mapRow, ++mapColumn);
            put_char(132);
            set_cursor(mapRow, ++mapColumn);
            put_char(132);
        }
        else if (pipeMap[row][column] == 2) // Cross
        {
            set_cursor(mapRow, mapColumn);
            if (cursorPosition == &pipeMap[row][column])
                put_char(136);
            else
                put_char(127);
            set_cursor(mapRow, ++mapColumn);
            put_char(128);
            set_cursor(mapRow, ++mapColumn);
            put_char(129);
            set_cursor(mapRow, ++mapColumn);
            put_char(127);
            mapColumn -= 3;
            set_cursor(++mapRow, mapColumn);
            put_char(132);
            set_cursor(mapRow, ++mapColumn);
            put_char(134);
            set_cursor(mapRow, ++mapColumn);
            put_char(133);
            set_cursor(mapRow, ++mapColumn);
            put_char(132);
        }
        else if (pipeMap[row][column] == 3) // L-U
        {
            set_cursor(mapRow, mapColumn);
            if (cursorPosition == &pipeMap[row][column])
                put_char(136);
            else
                put_char(127);
            set_cursor(mapRow, ++mapColumn);
            put_char(128);
            set_cursor(mapRow, ++mapColumn);
            put_char(130);
            set_cursor(mapRow, ++mapColumn);
            put_char(126);
            mapColumn -= 3;
            set_cursor(++mapRow, mapColumn);
            put_char(132);
            set_cursor(mapRow, ++mapColumn);
            put_char(132);
            set_cursor(mapRow, ++mapColumn);
            put_char(126);
            set_cursor(mapRow, ++mapColumn);
            put_char(126);
        }
        else if (pipeMap[row][column] == 4) // U-R
        {
            set_cursor(mapRow, mapColumn);
            if (cursorPosition == &pipeMap[row][column])
                put_char(135);
            else
                put_char(126);
            set_cursor(mapRow, ++mapColumn);
            put_char(131);
            set_cursor(mapRow, ++mapColumn);
            put_char(129);
            set_cursor(mapRow, ++mapColumn);
            put_char(127);
            mapColumn -= 3;
            set_cursor(++mapRow, mapColumn);
            put_char(126);
            set_cursor(mapRow, ++mapColumn);
            put_char(126);
            set_cursor(mapRow, ++mapColumn);
            put_char(132);
            set_cursor(mapRow, ++mapColumn);
            put_char(132);
        }
        else if (pipeMap[row][column] == 5) // R-D
        {
            set_cursor(mapRow, mapColumn);
            if (cursorPosition == &pipeMap[row][column])
                put_char(135);
            else
                put_char(126);
            set_cursor(mapRow, ++mapColumn);
            put_char(126);
            set_cursor(mapRow, ++mapColumn);
            put_char(127);
            set_cursor(mapRow, ++mapColumn);
            put_char(127);
            mapColumn -= 3;
            set_cursor(++mapRow, mapColumn);
            put_char(126);
            set_cursor(mapRow, ++mapColumn);
            put_char(131);
            set_cursor(mapRow, ++mapColumn);
            put_char(133);
            set_cursor(mapRow, ++mapColumn);
            put_char(132);
        }
        else if (pipeMap[row][column] == 6) // D-L
        {
            set_cursor(mapRow, mapColumn);
            if (cursorPosition == &pipeMap[row][column])
                put_char(136);
            else
                put_char(127);
            set_cursor(mapRow, ++mapColumn);
            put_char(127);
            set_cursor(mapRow, ++mapColumn);
            put_char(126);
            set_cursor(mapRow, ++mapColumn);
            put_char(126);
            mapColumn -= 3;
            set_cursor(++mapRow, mapColumn);
            put_char(132);
            set_cursor(mapRow, ++mapColumn);
            put_char(134);
            set_cursor(mapRow, ++mapColumn);
            put_char(130);
            set_cursor(mapRow, ++mapColumn);
            put_char(126);
        }
        else // EMPTY
        {
            set_cursor(mapRow, mapColumn);
            if (cursorPosition == &pipeMap[row][column])
                put_char(135);
            else
                put_char(126);
            set_cursor(mapRow, ++mapColumn);
            put_char(126);
            set_cursor(mapRow, ++mapColumn);
            put_char(126);
            set_cursor(mapRow, ++mapColumn);
            put_char(126);
            mapColumn -= 3;
            set_cursor(++mapRow, mapColumn);
            put_char(126);
            set_cursor(mapRow, ++mapColumn);
            put_char(126);
            set_cursor(mapRow, ++mapColumn);
            put_char(126);
            set_cursor(mapRow, ++mapColumn);
            put_char(126);
        }
    }
}

void print_initial_pipe(uint8_t row, uint8_t column, uint8_t mapRow, uint8_t mapColumn)
{
    if (pipeMap[row][column] == 0) //UP
    {
        set_color(BLACK, GRAY);
        set_cursor(mapRow, mapColumn);
        if (cursorPosition == &pipeMap[row][column])
            put_char(135);
        else
            put_char(126);
        set_cursor(mapRow, ++mapColumn);
        put_char(131);
        set_cursor(mapRow, ++mapColumn);
        put_char(130);
        set_cursor(mapRow, ++mapColumn);
        put_char(126);
        mapColumn -= 3;
        set_cursor(++mapRow, mapColumn);
        put_char(126);
        set_cursor(mapRow, ++mapColumn);
        put_char(126);
        set_cursor(mapRow, ++mapColumn);
        put_char(126);
        set_cursor(mapRow, ++mapColumn);
        put_char(126);
    }
    else if (pipeMap[row][column] == 1) // RIGHT
    {
        set_color(BLACK, GRAY);
        set_cursor(mapRow, mapColumn);
        if (cursorPosition == &pipeMap[row][column])
            put_char(135);
        else
            put_char(126);
        set_cursor(mapRow, ++mapColumn);
        put_char(126);
        set_cursor(mapRow, ++mapColumn);
        put_char(127);
        set_cursor(mapRow, ++mapColumn);
        put_char(127);
        mapColumn -= 3;
        set_cursor(++mapRow, mapColumn);
        put_char(126);
        set_cursor(mapRow, ++mapColumn);
        put_char(126);
        set_cursor(mapRow, ++mapColumn);
        put_char(132);
        set_cursor(mapRow, ++mapColumn);
        put_char(132);
    }
    else if (pipeMap[row][column] == 2) // DOWN
    {
        set_color(BLACK, GRAY);
        set_cursor(mapRow, mapColumn);
        if (cursorPosition == &pipeMap[row][column])
            put_char(135);
        else
            put_char(126);
        set_cursor(mapRow, ++mapColumn);
        put_char(126);
        set_cursor(mapRow, ++mapColumn);
        put_char(126);
        set_cursor(mapRow, ++mapColumn);
        put_char(126);
        mapColumn -= 3;
        set_cursor(++mapRow, mapColumn);
        put_char(126);
        set_cursor(mapRow, ++mapColumn);
        put_char(131);
        set_cursor(mapRow, ++mapColumn);
        put_char(130);
        set_cursor(mapRow, ++mapColumn);
        put_char(126);
    }
    else // LEFT
    {
        set_color(BLACK, GRAY);
        set_cursor(mapRow, mapColumn);
        if (cursorPosition == &pipeMap[row][column])
            put_char(136);
        else
            put_char(127);
        set_cursor(mapRow, ++mapColumn);
        put_char(127);
        set_cursor(mapRow, ++mapColumn);
        put_char(126);
        set_cursor(mapRow, ++mapColumn);
        put_char(126);
        mapColumn -= 3;
        set_cursor(++mapRow, mapColumn);
        put_char(132);
        set_cursor(mapRow, ++mapColumn);
        put_char(132);
        set_cursor(mapRow, ++mapColumn);
        put_char(126);
        set_cursor(mapRow, ++mapColumn);
        put_char(126);
    }
}