/* arduino-1st-shield.h
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

#ifndef _1ST_SHIELD
#define _1ST_SHIELD

#include <Arduino.h>
#include <arduino-7-segment-display-ctl.h>

class _1stShield {
  public:
    
    enum class LED {
      RED = 0,
      YELLOW,
      GREEN,
      RGB_RED,
      RGB_GREEN,
      RGB_BLUE
    };

    _1stShield();

		void set_2x7SD(uint8_t num);
    void set_RGB(int8_t R = -1, int8_t G = -1, int8_t B = -1);
		void set_LED(LED led, uint8_t level);

    int get_POT();
    bool get_button(uint8_t button);

    void register_callback_on_pressed(uint8_t button, void (*func)(void*), void* Data);
    void register_callback_on_released(uint8_t button, void (*func)(void*), void* Data);
    
    void update();
    void update_buttons();
    
  private:
 
    _2x7SegmentDisplay m_2x7SD{5, 2, 6, 8, 7, 3, 4, true};

    void (*m_pressedFunc[2])(void*) = {nullptr, nullptr};
    void (*m_releasedFunc[2])(void*) = {nullptr, nullptr};

    void* m_pressedData[2] = {nullptr, nullptr};
    void* m_releasedData[2] = {nullptr, nullptr};

    bool m_buttonState[2] = {0, 0};
};

#endif //_1ST_SHIELD
