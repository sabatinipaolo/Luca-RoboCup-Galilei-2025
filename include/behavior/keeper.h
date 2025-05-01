#pragma once

#define REST_TIME 1000
#define SAVE_TIME 1000
#define IDLE_TIME 1000

// STATES
#define RESET 0
#define DEFEND 1
#define GET_IN_ACTION 2
#define PARRY 3

void keeper();
void goto_goal();
void defend();
void save();
