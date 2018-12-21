/*
 * dir.h
 *
 *  Created on: Dec 19, 2018
 *      Author: jack
 */

#ifndef DIR_H_
#define DIR_H_

#define DIR_L 0
#define DIR_R 1
#define DIR_U 2
#define DIR_D 3
#define DIR_NONE -1

typedef int Dir;

inline int get_x(Dir d){
	if(d==DIR_L)return -1;
	if(d==DIR_R)return 1;
	return 0;
}

inline int get_y(Dir d){
	if(d==DIR_U)return -1;
	if(d==DIR_D)return 1;
	return 0;
}

inline bool is_opp(Dir a,Dir b){
	return get_x(a)==-get_x(b) && get_y(a)==-get_y(b);
}

inline Dir get_opp(Dir d){
	if(d==DIR_L)return DIR_R;
	if(d==DIR_R)return DIR_L;
	if(d==DIR_U)return DIR_D;
	if(d==DIR_D)return DIR_U;
	return DIR_NONE;
}

#endif /* DIR_H_ */
