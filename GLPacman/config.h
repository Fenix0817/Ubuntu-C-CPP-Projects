/*
 * config.h
 *
 *  Created on: Dec 19, 2018
 *      Author: jack
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#define DOT_SIZE 0.1
#define POWER_DOT_SIZE (0.4+0.1*cos(glfwGetTime()))

#define SPRITE_EXTRA 0.3

#define OFFSET_RES 1000.0

#define PLAYER_SPEED 200
#define GHOST_SPEED 200
#define GHOST_SLOWDOWN_SPEED 125
#define SCARED_GHOST_SPEED 50

#define SCARE_TIME 400
#define FLASH_TIME 50
#define FLASH_SPEED 10

#define GHOST_DEATH_ENTER_TIME 200

#define ENTER_TIME_BLINKY 1
#define ENTER_TIME_PINKY 50
#define ENTER_TIME_INKY 100
#define ENTER_TIME_CLYDE 150

#endif /* CONFIG_H_ */
