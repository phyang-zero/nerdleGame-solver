#include ".\\headerFile\\solver.h"
#ifdef WEB_H

#include <windows.h>
#endif

//获得日期随机数种子
int getSeed() {

	time_t now = time(NULL);
	if (now == -1) {
		perror("time");
		return 0;
	}

	struct tm *local_time = localtime(&now);
	if (local_time == NULL) {
		perror("localtime");
		return 0;
	}

	int year = local_time->tm_year + 1900; // tm_year是从1900年开始的
	int month = local_time->tm_mon + 1;    // tm_mon是从0开始的
	int day = local_time->tm_mday;
	return year * 10000 + month * 100 + day;
}

int dailyRand;
int initWordList() {
	int seed = getSeed();
	if (!seed) {
		puts("系统日期获取失败！");
		return 0;
	}
	srand(seed); //置随机数种子
	dailyRand = rand();
	FILE* fp = fopen(PathWordBank, "r");
	for (int i = 0; i < ALLOWED_GUESSES_COUNT; i++) {
		fscanf(fp, "%s", TotalWordList[i]);
	}
	fclose(fp);
	fp = fopen(PathAnswerList, "r");
	for (int i = 0; i < POSSIBLE_ANSWERS_COUNT; i++) {
		fscanf(fp, "%s", TotalAnswerList[i]);
	}
	fclose(fp);
	return 1;
}

int ifDailySuccess = 0;
void playDailyGame() {
	system("cls");
	if (ifDailySuccess) {
		puts("You have already won the game today, please come back tomorrow!");
		return ;
	}
	printf("Daily Nerdle Game!\n");
	printf("P = Proper：correct character, in the correct position.\nC = Contained：correct character, in the wrong position.\nE = Excluded：incorrect character.\n\n");
	char answer[9] = { 0 };
	Strcpy(answer, TotalAnswerList[dailyRand % POSSIBLE_ANSWERS_COUNT]);
	char playerInput[9] = {0};
	Word playerTry;
	puts("");
	for (int i = 0; i < 6; i++) {
		while (true) {
			for (int i = 0; i < 9; i++) playerInput[i] = '\0';
			inputWord(playerInput);
			
			if (isWordInBank(playerInput)) break;
			
			if (playerInput[0]=='-') puts("Unacceptable for Leading Negative Numbers!\n");
			else puts("This Guess Doesn't Compute!\n");
		}

		playerTry = judgeWord(playerInput, answer);

		for (int j = 0; j < 8; j ++) {
			printf("%c", displayToRealIndex(stateToWord[playerTry.cells[j].state]));
		}
		puts("\n");


		if (isWordProper(playerTry)) {
			puts("SUCCESS!");
			ifDailySuccess = 1;
			return ;
		}
	}
	puts("Sorry, you lost!");
	return ;
}

void solveGame() {
	system("cls");
	printf("Nerdle Game Solver\n");
	printf("P = Proper：correct character, in the correct position.\nC = Contained：correct character, in the wrong position.\nE = Excluded：incorrect character.\n\n");
	Word previous_situation_list[6] = { 0 };
	int previous_situation_list_count = 0;
	long long current_score = 0;
	char solverTry[8];
	Word try;//={0};

	for (int i = 0; i < 6; i++) {
		puts("");
		int succeeded = getNextGuess(previous_situation_list, previous_situation_list_count, solverTry, &current_score);
		if (succeeded == 0) {
			puts("Unsolvable. Please check your input.");
			break;
		} else {
			for (int j = 0; j < 8; j ++) {
				try.cells[j].state = NotJudged;
				try.cells[j].symbol = solverTry[j];
			}

			inputState(&try, printWord);
			if (isWordProper(try)) {
				puts("\nSuccessfully solved the problem!");
				break;
			}

			previous_situation_list[i] = try;
			previous_situation_list_count++;
		}
	}
}
#ifdef WEB_H
void solveOnlineGame_inMyComputer() {
	system("cls");
	printf("Nerdle Game Solver\n");
	ShellExecuteA(NULL, "open", url, NULL, NULL, 3); //打开网页

	Sleep(5000);
	SetCursorPos(blank_x[7], blank_y[1]); //鼠标移动到指定坐标
	Sleep(10);
	if (getColor(blank_x[7], blank_y[1]) == '1') {
		SetWindowPos(hwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		puts("You have already won the game in web today, please come back tomorrow!");
		return ;
	}

	pos pop={1266,138};
	click(pop);
	Sleep(10);
	
	Word previous_situation_list[6] = { 0 };
	int previous_situation_list_count = 0;
	long long current_score = 0;
	char solverTry[8];
	Word try;//={0};

	for (int i = 0; i < 6; i++) {
		puts("");
		int succeeded = getNextGuess(previous_situation_list, previous_situation_list_count, solverTry, &current_score);
		if (succeeded == 0) {
			puts("Unsolvable. Please check your input.");
			break;
		} else {
			for (int j = 0; j < 8; j ++) {
				try.cells[j].state = NotJudged;
				try.cells[j].symbol = solverTry[j];
			}


			inputStateInWeb(&try, printWordInWeb, i);
			if (isWordProper(try)) {
				puts("\nSuccessfully solved the problem!");
				break;
			}

			previous_situation_list[i] = try;
			previous_situation_list_count++;
		}
	}
}
#endif

int exiting = 0;
void start() {
	system("cls");
	printf("Welcome to Nerdle by yph!\nSelect mode.\n1. Play Nerdle（Daily Game）\n2. Start Nerdle Solver (Manually)\n3. Solve Nerdle on Web Pages（Automatically）\n4. Exit\n");
	int select = Read();
	switch (select) {
		case 1:
			playDailyGame();
			break;
		case 2:
			solveGame();
			break;
		case 3:
			#ifdef WEB_H
			solveOnlineGame_inMyComputer();
			SetWindowPos(hwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
			#else
			system("cls");
			puts("The Web Function is Not Included!");
			#endif
			break;
		case 4:
			system("cls");
			exiting = 1;
			puts("Bye!");
			break;
		default:
			break;
	}
}

int main() {

#ifdef WEB_H
//	-----------移除快速编辑模式-----------
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hStdin, &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE;
	SetConsoleMode(hStdin, mode);
//	--------------------------------------

	hwnd = GetForegroundWindow();
#endif

	initWordList();
	while (!exiting) {
		start();
		system("pause");
	}
	return 0;
}
