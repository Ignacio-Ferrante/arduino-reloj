#include "constants.h"

int minutesDigits, secondsDigits;

void timerManagment() {
    isRunning ? runningControl() : pausedControl();
}

void runningControl() {
    unsigned long currentTime = millis() - timerStartTime;
    int minutes = currentTime / 60000;
    int seconds = (currentTime / 1000) % 60;

    if (globalConfig.timerMode == COUNT) {
        minutesDigits = min(99, minutes);
        secondsDigits = min(99, seconds);

        limitControl(99);
    }
    else {
        minutesDigits = max(0, countdownMinutes - minutes);
        secondsDigits = max(0, countdownSeconds - seconds);

        limitControl(0);
    }
    showTime(minutesDigits, secondsDigits);
}

void limitControl(int limit) {
    isRunning = minutesDigits != limit && secondsDigits != limit;
}

void pausedControl() {
    if (millis() % 1000 < 500) {
        if (globalConfig.timerMode == COUNT) {
            showTime(minutesDigits, secondsDigits);
        }
        else {
            showTime(countdownMinutes, countdownSeconds);
        }
    }
    else {
        turnOffAllDigits();
    }
}

void resetCrono() {
    cronoMinutes = 0;
    cronoSeconds = 0;
}