/*
 * software_timer.c
 *
 *  Created on: Apr 3, 2024
 *      Author: khanh
 */
#include "software_timer.h"

int timer0_counter = 0;
int timer0_flag = 0 ;
int timer1_counter = 0;
int timer1_flag = 0 ;
int timer2_counter = 0;
int timer2_flag = 0 ;
int timerGREEN_flag = 0;
int timerAMB_flag = 0;
int timerRED_flag = 0;
int timerRED_counter = 0;
int timerAMB_counter = 0;
int timerGREEN_counter = 0;
int timerState_counter = 0;
int timerState_flag = 0;
int timerSwitch_flag = 0;
int timerSwitch_counter = 0;
void setTimerState(int duration) {
	timerState_counter = duration;
	timerState_flag = 0;
}
void setTimerSwitch(int duration) {
	timerSwitch_flag = 0;
	timerSwitch_counter = duration;
}
void setTimer0(int duration) {
	timer0_counter = duration;
	timer0_flag = 0;
}
void setTimer1(int duration) {
	timer1_counter = duration;
	timer1_flag = 0;
}
void setTimer2(int duration) {
	timer2_counter = duration;
	timer2_flag = 0;
}
void setTimer_RED(int duration) {
	timerRED_counter = duration;
	timerRED_flag = 0;
}
void setTimer_AMB(int duration) {
	timerAMB_counter = duration;
	timerAMB_flag = 0;
}
void setTimer_GREEN(int duration) {
	timerGREEN_counter = duration;
	timerGREEN_flag = 0;
}
void timerRun() {
	if (timer1_counter > 0) {
		timer1_counter --;
		if (timer1_counter <= 0) {
			timer1_flag = 1;
		}
	}
	if (timer0_counter > 0) {
		timer0_counter --;
		if (timer0_counter <= 0) {
			timer0_flag = 1;
		}
	}
	if (timer2_counter > 0) {
		timer2_counter --;
		if (timer2_counter <= 0) {
			timer2_flag = 1;
		}
	}
	if (timerRED_counter > 0) {
		timerRED_counter --;
		if (timerRED_counter <= 0) {
			timerRED_flag = 1;
		}
	}
	if (timerAMB_counter > 0) {
		timerAMB_counter --;
		if (timerAMB_counter <= 0) {
			timerAMB_flag = 1;
		}
	}
	if (timerGREEN_counter > 0) {
		timerGREEN_counter --;
		if (timerGREEN_counter <= 0) {
			timerGREEN_flag = 1;
		}
	}
	if (timerSwitch_counter > 0) {
		timerSwitch_counter --;
		if (timerSwitch_counter <= 0) {
			timerSwitch_flag = 1;
		}
	}
	if (timerState_counter > 0) {
		timerState_counter --;
		if (timerState_counter <= 0) {
			timerState_flag = 1;
		}
	}
}
