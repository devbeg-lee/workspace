#ifndef __RESULT_H__
#define __RESULT_H__

#include "main.h"
#include "delay.h"

enum eResult
{
    kResult_None = 0,
    kResult_Pass,
    kResult_Err_1,
    kResult_Err_2,
    kResult_Err_3,
    kResult_Err_4,
    kResult_Err_5,
    kResult_Err_6,
    kResult_Err_7,
    kResult_Err_8,
    kResult_Err_9,
    kResult_Err_10,
    kResult_Err_11,
    kResult_Err_12,
};

enum eNotes
{
    None = 0,
    C4 = 262,  // 도 261.63Hz
    D4 = 294,  // 레 293.66Hz
    E4 = 330,  // 미 329.63Hz
    F4 = 349,  // 파 349.23Hz
    G4 = 392,  // 솔 392.00Hz
    A4 = 440,  // 라 440.00Hz
    B4 = 494,  // 시 493.88Hz
    C5 = 523,  // 도 523.25Hz
    D5 = 587,  // 레 587.33Hz
    E5 = 659,  // 미 659.25Hz
    F5 = 698,  // 파 698.46Hz
    G5 = 784,  // 솔 783.99Hz
    A5 = 880,  // 라 880.00Hz
    B5 = 988,  // 시 987.77Hz
    C6 = 1047, // 도 1046.50Hz
    T5 = 2000
};

extern volatile enum eResult g_Result;

void fail_sound(uint8_t i);
void pass_sound(uint8_t i);
void result(uint8_t data);
void FND_1(void);
void FND_2(void);
void FND_3(void);
void FND_4(void);
void FND_P(void);
void FND_A(void);
void FND_S(void);
void FND_E(void);
void FND_r(void);
void FND_zero(void);
void FND_one(void);
void FND_two(void);
void FND_three(void);
void FND_four(void);
void FND_five(void);
void FND_six(void);
void FND_seven(void);
void FND_eight(void);
void FND_nine(void);
void turn_off(void);

#endif