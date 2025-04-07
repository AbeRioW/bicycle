#ifndef __UI_H_
#define __UI_H_

#include "main.h"


extern int speed_ban;
extern int heart_ban;
extern int rh_ban;
extern int th_ban;
void show_time(void);
void handle_setting(void);


void show_dht(unsigned char RH,unsigned char RL,unsigned char TH,unsigned char TL);
void clear_second_row(void);
void ui_setting(void);

void ui_set_speed(void);
void ui_set_heart(void);
void ui_setting_rh(void);
#endif
