/*
 * software_timer.c
 *
 *  Created on: Sep 15, 2023
 *      Author: TuanAnh
 */

#include "software_timer.h"

int timer1_flag = 0;
int timer1_counter = 0;

void setTimer1(int duration) {
	timer1_flag = 0;
	timer1_counter = duration;
}

void timerRun() {
	if (timer1_counter > 0) {
		timer1_counter = timer1_counter - 1;
		if (timer1_counter <= 0) {
			timer1_flag = 1;
		}
	}
}

