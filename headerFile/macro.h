#ifndef MACRO_H
#define MACRO_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define POSSIBLE_ANSWERS_COUNT 17723 //17723个valid_answer
#define ALLOWED_GUESSES_COUNT 40346 //40346个valid_expression
#define true 1
//#define false 0

int isDigit(char ch) {
	if (ch >= '0' && ch <= '9') return 1;
	return 0;
}
int isSign(char ch) 
{
	if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=') return 1;
	return 0;
}

int Read()  {
	int x = 0, f = 1;
	char ch = getchar();
	while (!isDigit(ch)) {
		if (ch == '-')  f = -1;
		ch = getchar();
	}
	while (isDigit(ch)) {
		x = (x << 3) + (x << 1) + ch - '0';
		ch = getchar();
	}
	return x * f;
}

const char PathWordBank[] = ".\\data\\valid_expressions.txt";
const char PathAnswerList[] = ".\\data\\valid_answers.txt";
const char *url = "https://nerdlegame.com";

char TotalWordList[ALLOWED_GUESSES_COUNT][9]={0};
char TotalAnswerList[POSSIBLE_ANSWERS_COUNT][9]={0};

#endif
