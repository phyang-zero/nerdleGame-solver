#ifndef SOLVER_H
#define SOLVER_H

#include "word.h"

#define SOLVER_FIRST_WORD "5*8/10=4"
#define SOLVER_FIRST_WORD_SCORE 8973989


// filter out a small range of possible words that match the current word list.
void filterSmallerWordRange(WordList pre_list, int pre_count, char out_smaller_word_range[ALLOWED_GUESSES_COUNT][8], int* out_len) {
    int index = 0;
    for (int i = 0; i < ALLOWED_GUESSES_COUNT; i++) {
        if (isWordListMatch(pre_list, pre_count, TotalWordList[i])) {
            Strncpy(out_smaller_word_range[index], TotalWordList[i], 8);
            index ++;
        }
    }
    *out_len = index;
}

//计算信息熵（infomation entropy）
//E[I]=∑p(x)*log2(1/p(x))
double calcInfoEntropy(char smaller_word_range[][8], const int len, char text[]) {
    double infoEntropy = 0, possibility = 0;
    
    int count[6561] = { 0 };//3^8
    for (int i = 0; i < len; i++) {
        count[judgeWordIntoStateIndex(text, smaller_word_range[i])]++;
    }

    for (int j = 0; j < 6561; j++) { //3^8
        if (count[j] != 0) {
            possibility = (double)count[j] / len;
            infoEntropy -= possibility * Log2(possibility);
        }
    }
    return infoEntropy;
}


// search a proper word.
// return 0 if the search failed.
int searchWord(char smaller_word_range[][8], const int len, char out_result[], long long* out_score_max) {
    double current_entropy = 0;
    long long score_max = 0;
    char winner_word[8];
    int flag = 0;

    for (int i = 0; i < len; i++) {
        current_entropy = 1e6 * calcInfoEntropy(smaller_word_range, len, smaller_word_range[i]);
        if (current_entropy >= score_max) {
            flag = true;
            score_max = (long long)current_entropy;
            Strncpy(winner_word, smaller_word_range[i], 8);
        }
    }
    if (flag == true) {
        *out_score_max = score_max;
        Strcpy(out_result, winner_word);
    }
    return flag;
}


int getNextGuess(Word previous_guessed_feedback_list[6], int list_length, char out_next_guess[8], long long *out_next_guess_score) {
//    assert(list_length >= 0);
    if (list_length > 6) {
        return 0;
    }

    else if (list_length == 0) {
        Strcpy(out_next_guess, SOLVER_FIRST_WORD);
        *out_next_guess_score = SOLVER_FIRST_WORD_SCORE;
        return 1;
    }
    
    else {;
        int len;
        char smaller_word_range[ALLOWED_GUESSES_COUNT][8] = { 0 };
        long long current_score = 0;
        char selected_word[8] = { 0 };
        filterSmallerWordRange(previous_guessed_feedback_list, list_length, smaller_word_range, &len);
        int is_succeeded = searchWord(smaller_word_range, len, selected_word, &current_score);
        if (is_succeeded == 0) {
            return 0;
        }
        Strcpy(out_next_guess, selected_word);
        *out_next_guess_score = current_score; 
        return 1;
    }
    return 0;
}

#endif
