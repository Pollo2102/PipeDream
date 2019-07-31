#ifndef PIPEDREAM_H
#define PIPEDREAM_H

#include "system.h"
#include "screen.h"
#include "keypad.h"

void print_background();
void generate_map();
uint8_t generate_rand();
void set_initial_square();
uint8_t generate_initial_pipe();
void generate_initial_PQueue();
void reset_map();
void push_queue();
uint8_t pop_queue();
void shift_queue();
void set_cursor_position(uint8_t row, uint8_t column);
void count_first_pipe();
void count_pipes(uint8_t * prev, uint8_t * next);
void place_pipe();
void print_map();
uint32_t getTime();
void print_pipe_queue(uint8_t num, uint8_t mapRow, uint8_t mapColumn);
void print_pipe(uint8_t row, uint8_t column, uint8_t mapRow, uint8_t mapColumn);
void print_initial_pipe(uint8_t row, uint8_t column, uint8_t mapRow, uint8_t mapColumn);
bool is_initial_pipe(uint8_t row, uint8_t column);
void game_init();
void game_start();
void end_game();
void moveCursor(uint8_t input);

#endif // !PIPEDREAM_H
