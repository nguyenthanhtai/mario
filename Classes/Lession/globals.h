//
//  globals.h
//  MagicMario
//
//  Created by Nguyen Thanh Tai  on 4/1/19.
//

#ifndef globals_h
#define globals_h

#include "cocos2d.h"
USING_NS_CC;

// KEYBOARD
const EventKeyboard::KeyCode ENTER = EventKeyboard::KeyCode::KEY_KP_ENTER;
const EventKeyboard::KeyCode UP_ARROW = EventKeyboard::KeyCode::KEY_UP_ARROW;
const EventKeyboard::KeyCode DOWN_ARROW = EventKeyboard::KeyCode::KEY_DOWN_ARROW;
const EventKeyboard::KeyCode LEFT_ARROW = EventKeyboard::KeyCode::KEY_LEFT_ARROW;
const EventKeyboard::KeyCode RIGHT_ARROW = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
const EventKeyboard::KeyCode SPACEBAR = EventKeyboard::KeyCode::KEY_SPACE;

const float SCALE_FACTOR = 2.0f;
const float ENEMY_SCALE_FACTOR = 1.4f;
const float PLAYER_MAX_VELOCITY = 300.0f;
const float PLAYER_JUMP_VELOCITY = 600.0f;
const float GRAVITY = 20.0f;

#endif /* globals_h */
