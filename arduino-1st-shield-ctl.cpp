/* arduino-1st-shield.cpp
 *
 * Copyright 2021 Dominik Rzecki
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

 

#include "arduino-1st-shield-ctl.hpp"

_1stShield::_1stShield() {
	pinMode(12, OUTPUT);
	pinMode(13, OUTPUT);
	pinMode(11, OUTPUT);
	pinMode(10, OUTPUT);
	pinMode(9, OUTPUT);
	pinMode(A0, OUTPUT);
	pinMode(A1, OUTPUT);
	pinMode(A2, OUTPUT);
	pinMode(A3, INPUT);
	pinMode(A4, INPUT);
	pinMode(A5, INPUT);
}

void _1stShield::set_2x7SD(uint8_t num) {
	m_2x7SD.Set(num);
}

void _1stShield::set_RGB(int8_t R, int8_t G, int8_t B) {
	int8_t* arr[3] = {&R, &G, &B};
	for (auto& i : arr) {
		if (*i != -1) {
			analogWrite(9 + (&i - &arr[0]), *i);
		}
	}
}

void _1stShield::set_LED(LED led, uint8_t level) {
	switch (led) {
		case LED::RED:
			digitalWrite(A0, level);
			break;
		case LED::YELLOW:
			digitalWrite(A1, level);
			break;
		case LED::GREEN:
			digitalWrite(A2, level);
			break;
		case LED::RGB_RED:
			analogWrite(9, level);
			break;
		case LED::RGB_GREEN:
			analogWrite(10, level);
			break;
		case LED::RGB_BLUE:
			analogWrite(11, level);
			break;
		default:
			break;
	}
}

int _1stShield::get_POT() {
	return analogRead(A5);
}

bool _1stShield::get_button(uint8_t button) {
	update_buttons();
	return buttonState[button];
}

void _1stShield::register_callback_on_pressed(uint8_t button, void (*func)(void*), void* Data) {
	m_pressedData[button] = func;
	m_pressedData[button] = Data;
}

void _1stShield::register_callback_on_released(uint8_t button, void (*func)(void*), void* Data) {
	m_releasedFunc[button] = func;
	m_releasedData[button] = Data;
}

void _1stShield::update() {
	m_7SD.Update();
	update_buttons();
}

void _1stShield::update_buttons(){
	bool buttonStateNew[2];
      
	for ( int button = 0; button < 2; button++ ) {
		buttonStateNew[button] = !analogRead(A3+button);
		if ( buttonStateNew[button] != m_buttonState[button] ) {
			if ( buttonStateNew[button] == 1 && m_pressedFunc[button] != nullptr ) {
				m_pressedFunc[button](m_pressedData[button]);
			}
			if ( buttonStateNew[button] == 0 && m_releasedFunc[button] != nullptr ){
				m_releasedFunc[button](m_releasedData[button]);
			}
		}
		m_buttonState[button] = buttonStateNew[button];
	}
}
