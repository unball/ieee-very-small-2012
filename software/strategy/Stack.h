#ifndef STACK_H
#define STACK_H

/**
 * @file      Stack.h
 * @author    Tiago P. M. da Silva
 * @date      03/04/2012
 *
 * @attention Copyright (C) 2011
 * @attention UnBall Robot Soccer Team
 */


#include <stdio.h>
#include <iostream>
#include <string>

class Stacks
{
	public:
		Stacks()
		{
			this->sizenow = 0;
			for (int i=0; i<50;i++)
				this->commands[i] = '.';
		}
	
		bool push(char input)
		{
			this->commands[this->sizenow] = input;
			this->sizenow++;
			return 1;
		}

		bool pop(char *output)
		{
			if (sizenow>=1)
			{
				this->sizenow--;
				*output = this->commands[this->sizenow];
				return 1;
			}
			else
			{
				return 0;
			}
		}
	
	
	private:
		int sizenow;
		char commands[50];
};


#endif //STACK_H
