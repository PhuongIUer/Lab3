/*
 * Button.c
 *
 *  Created on: May 5, 2024
 *      Author: khanh
 */


#include "Button.h"

int keyReg0[3] = {NORMAL, NORMAL, NORMAL};
int keyReg1[3] = {NORMAL, NORMAL, NORMAL};
int keyReg2[3] = {NORMAL, NORMAL, NORMAL};
int keyReg3[3] = {NORMAL, NORMAL, NORMAL};

int timeFORpress[3] = {100, 100, 100};
int button1_flag = 0;
int button2_flag = 0;
int button3_flag = 0;

int button1_flagRelease = 0 ;
int button3_flagRelease = 0 ;

GPIO_TypeDef *button_GPIO_Port[] = {Button1_GPIO_Port, Button2_GPIO_Port, Button3_GPIO_Port};
uint16_t button_Pin[] = {Button1_Pin, Button2_Pin, Button3_Pin};
void getKeyInput() {
    for (int i = 0; i < 3; i++) {
        // Read the state of button
        keyReg0[i] = keyReg1[i];
        keyReg1[i] = keyReg2[i];
        keyReg2[i] = HAL_GPIO_ReadPin(button_GPIO_Port[i], button_Pin[i]);
        if ((keyReg0[i] == keyReg1[i]) && (keyReg2[i] == keyReg1[i])) {
            if (keyReg3[i] != keyReg2[i]) {
                keyReg3[i] = keyReg2[i];
                if (keyReg2[i] == PRESSED_STATE) {
                    if( i == 0 ) {
                    	button1_flag = 1;
                    }
                    if( i == 1 ) {
                    	button2_flag = 1;
                    }
                    if( i == 2 ) {
                    	button3_flag = 1;
                    }
                    timeFORpress[i] = 100; // time to reset
                }
                if (keyReg2[i] == NORMAL) {
                	if ( i == 0) {
                		button1_flagRelease = 0;
                	}
                	if ( i == 2) {
                		button3_flagRelease = 0;
                	}
                }
            } else {
                timeFORpress[i]--;
                if (timeFORpress[i] == 0) {
                	keyReg3[i] = NORMAL ;
                }
            }
        }
    }
}
