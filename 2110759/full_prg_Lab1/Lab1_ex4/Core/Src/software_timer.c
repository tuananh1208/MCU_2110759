/*
 * software_timer.c
 *
 *  Created on: Sep 16, 2023
 *      Author: TuanAnh
 */

#include "software_timer.h"

int timer_counter  = 0;
int timer_flag = 0;

void timerSet(int duration) {
	timer_flag = 0;
	timer_counter = duration;
}

void timerRun() {
	if (timer_counter > 0) {
		timer_counter = timer_counter - 1;
		if (timer_counter <= 0) {
			timer_flag = 0;
		}
	}

}
