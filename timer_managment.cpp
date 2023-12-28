#include "constants.h"

int minutesDigits, secondsDigits;
int countDownSeconds = globalConfig.countdownSeconds;

void limitControl(int limit) {
  isRunning = minutesDigits != limit || secondsDigits != limit;
}

void runningControl() {
  int currentTime = (millis() - timerStartTime)/1000;

  if (globalConfig.timerMode == COUNT) {
    minutesDigits = min(99, currentTime / 60);
    secondsDigits = min(99, currentTime % 60);

    limitControl(99);
  } else {
    int countDownseconds = globalConfig.countdownMinutes * 60 + globalConfig.countdownSeconds - currentTime;
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
      showTime(globalConfig.countdownMinutes, globalConfig.countdownSeconds);
    }
  } else {
    turnOffAllDigits();
  }
}

void timerManagment() {
  isRunning ? runningControl() : pausedControl();
}

void resetCrono() {
  minutesDigits = 0;
  secondsDigits = 0;
}