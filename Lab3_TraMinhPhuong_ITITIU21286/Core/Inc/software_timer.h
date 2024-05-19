/*
 * software_timer.h
 *
 *  Created on: Apr 3, 2024
 *      Author: khanh
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

extern int timer0_flag;
extern int timer1_flag;
extern int timer2_flag;
extern int timerRED_flag;
extern int timerAMB_flag;
extern int timerGREEN_flag;
extern int timerRED_counter;
extern int timerAMB_counter;
extern int timerGREEN_counter;
extern int timerState_flag;
extern int timerSwitch_flag;

void setTimerSwitch(int duration);
void setTimerState(int duration);
void setTimer0 (int duration );
void setTimer1 (int duration );
void setTimer2 (int duration );
void setTimer_RED (int duration );
void setTimer_AMB (int duration );
void setTimer_GREEN (int duration );
void timerRun();


#endif /* INC_SOFTWARE_TIMER_H_ */
