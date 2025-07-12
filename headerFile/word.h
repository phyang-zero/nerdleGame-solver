#ifndef WORD_H
#define WORD_H
#include "macro.h"
#include "myString.h"
#include "myMath.h"
#include "web.h"

#define INVALID_SYMBOL '!'
#define MATCHED_MARK '#'

//extern int isDigit(char ch);
//extern int isSign(char ch);

typedef enum {
	Excluded,	//×1
	Contained,	//# 2
	Proper,		//√3
	NotJudged,
	Invalid = -1
} State;

typedef struct Show {
	State id;
} Display;

Display stateToWord[NotJudged + 1] = {{ Excluded }, { Contained }, { Proper }, { NotJudged }};

// convert the state char to state type.
State charToState(char c) {
	switch (c) {
		case 'E':
			return (State)Excluded;
			break;
		case 'C':
			return (State)Contained;
			break;
		case 'P':
			return (State)Proper;
			break;
		default:
			return (State)Invalid;
			break;
	}
}

char displayToRealIndex(Display s) {
	switch (s.id) {
		case Excluded:
			return 'E';
			break;
		case Contained:
			return 'C';
			break;
		case Proper:
			return 'P';
			break;
		default:
			return '0';
	}
}

typedef struct _Cell {
	State state;
	char symbol;
} Cell;

typedef struct _Word {
	Cell cells[8];
} Word;

typedef Word WordList[];

typedef void (*CallbackDisplayer)(Word word);

Word inputWord(char out_result[9]) {

	Word word;
	for (int i = 0; i < 8; i ++) {
		word.cells[i].state = NotJudged;
		word.cells[i].symbol = ' ';
	}
	char ch;
	int i = 0;
	while (true) {
		ch = getchar();
		if (i == 8) {
			if (ch != '\n') while (ch != '\n') ch = getchar();
			else break;;
		}
		if (isDigit(ch) || isSign(ch)) {
			word.cells[i].symbol = ch;
		} else {
			while (ch != '\n') ch = getchar();
			puts("Invalid Input!\n");
			i = -1;
		}
		i++;
	}
	for (i = 0; i < 8; i ++) {
		out_result[i] = word.cells[i].symbol;
	}

	return word;
}


void printWord(Word word) {
//	puts("!");
	if (displayToRealIndex(stateToWord[word.cells[0].state]) != '0') {
		for (int i = 0; i < 8; i ++) {
			printf("%c", displayToRealIndex(stateToWord[word.cells[i].state]));
		}
		printf("\n");
	}
	for (int i = 0; i < 8; i ++) {
		printf("%c", word.cells[i].symbol);
	}

	return ;
}


// test if a word is in the vocabulary list.
int isWordInBank(char word[9]) {
	for (int i = 0; i < ALLOWED_GUESSES_COUNT; i++) {
		if (Strcmp(word, TotalWordList[i])) {
			return 1;
		}
	}
	return 0;
}


Word judgeWord(char text_source[], char text_template[]) {
	Word word;
	char text_source_copied[9], text_template_copied[9];
	Strncpy(text_source_copied, text_source, 8);
	Strncpy(text_template_copied, text_template, 8);

	// "Proper"
	for (int i = 0; i < 8; i ++) {
		if (text_template_copied[i] == text_source_copied[i]) {
			word.cells[i].symbol = text_source_copied[i];
			word.cells[i].state = Proper;
			text_source_copied[i] = INVALID_SYMBOL;
			text_template_copied[i] = INVALID_SYMBOL;
		}
	}
	// "Contained"
	for (int i = 0; i < 8; i ++) {
		if (text_template_copied[i] == INVALID_SYMBOL) {
			continue;
		}
		char *pos = Strchr(text_source_copied, text_template_copied[i]);
		if (pos != NULL) {
			int index = pos - text_source_copied;
			word.cells[index].symbol = *pos;
			word.cells[index].state = Contained;
			*pos = INVALID_SYMBOL;
			text_template_copied[i] = INVALID_SYMBOL;
		}
	}
	// "Excluded"
	for (int i = 0; i < 8; i ++) {
		if (text_source_copied[i] != INVALID_SYMBOL) {
			word.cells[i].symbol = text_source_copied[i];
			word.cells[i].state = Excluded;
		}
	}
	return word;
}

int judgeWordIntoStateIndex(char text_source[], char text_template[]) {
	char text_source_copied[9], text_template_copied[9];
	Strncpy(text_source_copied, text_source, 8);
	Strncpy(text_template_copied, text_template, 8);

	int state = 0;

	// "Proper"
	for (int i = 0; i < 8; i ++) {
		if (text_template_copied[i] == text_source_copied[i]) {
			state += Proper * Pow(3, i);
			text_source_copied[i] = INVALID_SYMBOL;
			text_template_copied[i] = INVALID_SYMBOL;
		}
	}
	// "Contained"
	for (int i = 0; i < 8; i ++) {
		if (text_template_copied[i] == INVALID_SYMBOL) {
			continue;
		}
		char *pos = Strchr(text_source_copied, text_template_copied[i]);
		if (pos != NULL) {
			state += Contained * Pow(3, i);
			*pos = INVALID_SYMBOL;
			text_template_copied[i] = INVALID_SYMBOL;
		}
	}
	// "Excluded"
	// do nothing

	return state;
}


int isWordProper(Word word) {
	for (int i = 0; i < 8; i ++) {
		if (word.cells[i].state != Proper) {
			return 0;
		}
	}
	return 1;
}

int isWordMatch(Word word, const char text[]) {
	char text_copied[8];
	Strncpy(text_copied, text, 8);
	// Proper
	for (int i = 0; i < 8; i ++) {
		if (word.cells[i].state == Proper) {
			if (text_copied[i] != word.cells[i].symbol) {
				return 0;
			} else {
				// matched successfully
				text_copied[i] = MATCHED_MARK;
				word.cells[i].symbol = MATCHED_MARK;
			}
		}
	}
	// Contained
	for (int i = 0; i < 8; i ++) {
		if (word.cells[i].symbol == MATCHED_MARK) {
			continue;
		}
		if (word.cells[i].state == Contained) {
			if (text_copied[i] == word.cells[i].symbol) {
				return 0;
			} else {
				char *pos = Strchr(text_copied, word.cells[i].symbol);
				if (pos == NULL) {
					return 0;
				} else {
					*pos = MATCHED_MARK;
					word.cells[i].symbol = MATCHED_MARK;
				}
			}
		}
	}
	// Excluded
	for (int i = 0; i < 8; i ++) {
		if (word.cells[i].symbol == MATCHED_MARK) {
			continue;
		}
		if (word.cells[i].state == Excluded) {
			if (Strchr(text_copied, word.cells[i].symbol) != NULL) {
				return 0;
			}
		}
	}
	return 1;
}


int isWordListMatch(WordList word_list, int word_count, const char text[]) {
	for (int i = 0; i < word_count; i ++) {
		if (isWordMatch(word_list[i], text) == 0) {
			return 0;
		}
	}
//    printf("!");system("pause");
	return 1;
}

void inputState(Word *in_out_word, CallbackDisplayer cd) {
	char ch;
	cd(*in_out_word);
	puts("");
	int i = 0;
	while (true) {
		ch = getchar();
		if (i == 8) {
			if (ch != '\n') while (ch != '\n') ch = getchar();
			else break;;
		}
		if (ch == 'E') in_out_word->cells[i].state = Excluded;
		else if (ch == 'C') in_out_word->cells[i].state = Contained;
		else if (ch == 'P') in_out_word->cells[i].state = Proper;
		else {
			while (ch != '\n') ch = getchar();
			puts("Invalid Input!\n");
			in_out_word->cells[0].state = NotJudged;
			cd(*in_out_word);
			puts("");
			i = -1;
		}
		i++;
	}

	return ;
}

#ifdef WEB_H
pos getPos(char ch) {
	int i;
	if (ch >= '0' && ch <= '9') {
		i = ch - '0';
		return positionOfNumberKeys[i];
	}
	if (ch == '+') return positionOfFunctionKeys[Plus];
	if (ch == '-') return positionOfFunctionKeys[Minus];
	if (ch == '*') return positionOfFunctionKeys[Multiplication];
	if (ch == '=') return positionOfFunctionKeys[Equal];
	if (ch == '/') return positionOfFunctionKeys[Division];
	exit(-1);
}


void printWordInWeb(Word word) {
	for (int i = 0; i < 8; i++) {
		click(getPos(word.cells[i].symbol));
		printf("%c", word.cells[i].symbol);
		Sleep(50);
	}
	puts("");
	click(positionOfFunctionKeys[Enter]);
	return ;
}

void inputStateInWeb(Word *in_out_word, CallbackDisplayer cd, int i) {
	cd(*in_out_word);
	Sleep(1000);
	char ch;
	int x, y = blank_y[i];
	for (int j = 0; j < 8; j++) {
		x = blank_x[j];
		Sleep(10);
		ch = getColor(x, y);
		if (ch == 'E') in_out_word->cells[j].state = Excluded;
		else if (ch == 'C') in_out_word->cells[j].state = Contained;
		else if (ch == 'P') in_out_word->cells[j].state = Proper;
		else exit(-1);
		printf("%c",ch);
	}
	puts("");
	return ;
}
#endif

#endif
