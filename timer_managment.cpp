#include "constants.h"

bool isFinished, isRunning, isStop;
unsigned long startTime, elapsedTime;
int minutesDigits, secondsDigits;

void resetTimer() {
  minutesDigits = 0;
  secondsDigits = 0;
}

void limitControl(int limit) {
  isRunning = minutesDigits != limit || secondsDigits != limit;
  isFinished = true;
  resetTimer();
}

void runningControl() {
  elapsedTime = millis() - startTime;
  int secondsElapsedTime = elapsedTime / 1000;

  if (globalConfig.timerMode == COUNT) {
    minutesDigits = min(99, secondsElapsedTime / 60);
    secondsDigits = min(99, secondsElapsedTime % 60);

    limitControl(99);
  } else {
    int countDownseconds = globalConfig.countdownMinutes * 60 + globalConfig.countdownSeconds - secondsElapsedTime;
    minutesDigits = max(0, countDownseconds / 60);
    secondsDigits = max(0, countDownseconds % 60);

    limitControl(0);
  }

  showTime(minutesDigits, secondsDigits);
}

void pausedControl() {
  if (millis() % 1000 < 500) {
    if (globalConfig.timerMode == COUNT) {
      showTime(minutesDigits, secondsDigits);
    } else {
      isStop
        ? showTime(globalConfig.countdownMinutes, globalConfig.countdownSeconds)
        : showTime(minutesDigits, secondsDigits);
    }
  } else {
    turnOffAllSegments();
  }
}

void timerManagment() {
  isRunning ? runningControl() : pausedControl();
}

void startTimer() {
  startTime = millis() - elapsedTime;
  isRunning = true;
  isStop = false;
}

void pauseTimer() {
  isRunning = false;
  elapsedTime = millis() - startTime;
}

void stopTimer() {
  isRunning = false;
  isStop = true;
  resetTimer();
}