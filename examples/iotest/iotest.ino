/* iotest.ino
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

 

#include <arduino-1st-shield-ctl.hpp>

void Iterate(void* Data);

enum DisplayEnum {
  NONE = 0,
  DS7 = 1,
  RGB_R_LED = 2,
  RGB_G_LED = 3,
  RGB_B_LED = 4,
  RED_LED = 5,
  YELLOW_LED = 6,
  GREEN_LED = 7
};

void setup() {
}

void loop() {
  _1stShield shield;
  int iterator = DisplayEnum::NONE;
  int num;
  
  shield.register_callback_on_released(0, &Iterate, static_cast<void*> (&iterator));
  
  while(true){
    num = shield.get_POT();
    switch( iterator ) {
      case DisplayEnum::NONE:
        break;
      case DisplayEnum::DS7: shield.set_DS7(num/(float)1024*100);
        break;
      case DisplayEnum::RGB_R_LED: shield.set_RGB(num/(float)1024*256, -1, -1);
        break;
      case DisplayEnum::RGB_G_LED: shield.set_RGB(-1, num/(float)1024*256, -1);
        break;
      case DisplayEnum::RGB_B_LED: shield.set_RGB(-1, -1, num/(float)1024*256);
        break;
      case DisplayEnum::RED_LED: shield.set_LED(_1stShield::LED::RED, num/(float)1024*255);
        break;
      case DisplayEnum::YELLOW_LED: shield.set_LED(_1stShield::LED::YELLOW, num/(float)1024*255);
        break;
      case DisplayEnum::GREEN_LED: shield.set_LED(_1stShield::LED::GREEN, num/(float)1024*255);
        break;
      default:
        break;
    }
    
    shield.update();
    
  }
}

void Iterate(void* Data) {
  
  int* iterator = static_cast<int*> (Data);
  
  if(*iterator != DisplayEnum::GREEN_LED) {
    (*iterator)++;
  } else {
    *iterator = DisplayEnum::NONE;
  }
} 

