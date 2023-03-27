#include "Oscillator.h"
#include "NeoSWSerial.h"
#include "PenguinBot.h"


void PenguinBot::servoAttach(void){
    servo[0].attach(LOW_LEFT_PIN);
    servo[1].attach(LOW_RIGHT_PIN);
    servo[2].attach(UP_LEFT_PIN);
    servo[3].attach(UP_RIGHT_PIN);
}
void PenguinBot::servoDetach(void){
    servo[0].detach();
    servo[1].detach();
    servo[2].detach();
    servo[3].detach();
}

void PenguinBot::moveNServos(int time, int newPosition[]){
    unsigned long finalTime;
    unsigned long intervalTime;
    int           oneTime;
    int           iteration;
    float         increment[NB_SERVOS];
    for (int i = 0; i < NB_SERVOS; i++){
        increment[i] = ((newPosition[i]) - oldPosition[i]) / (time / INTERVAL_TIME);
    }
    finalTime = millis() + time;
    iteration = 1;
    while (millis() < finalTime){
        intervalTime = millis() + INTERVAL_TIME;
        oneTime = 0;
        while (millis() < intervalTime){
            if (oneTime < 1){
                for (int i = 0; i < NB_SERVOS; i++){
                    servo[i].setPosition(oldPosition[i] + (iteration * increment[i]));
                }
                iteration++;
                oneTime++;
            }
        }
    }

    for (int i = 0; i < NB_SERVOS; i++){
        oldPosition[i] = newPosition[i];
    }
}

void PenguinBot::oscillate(int A[NB_SERVOS], int O[NB_SERVOS], int T, double phaseDiff[NB_SERVOS]){
    for (int i = 0; i < NB_SERVOS; i++){
        servo[i].setO(O[i]);
        servo[i].setA(A[i]);
        servo[i].setT(T);
        servo[i].setPh(phaseDiff[i]);
    }
    double ref = millis();
    for (double x = ref; x < T + ref; x = millis()){
        for (int i = 0; i < NB_SERVOS; i++){
            servo[i].refresh();
        }
    }
}

void PenguinBot::defaultPosition(void){
    servoAttach();
    int move[] = {90, 90, 90, 90};
    moveNServos(DEFAULT_TEMPO, move);
    delay(DEFAULT_TEMPO);
    servoDetach();
}

void PenguinBot::walk(int steps, int T, bool isForward){
    int A[NB_SERVOS] = {30, 30, 30, 30};
    int O[NB_SERVOS] = {0, 0, 0, 0};
    double phaseDiff[NB_SERVOS];
    servoAttach();
    phaseDiff[0] = DEG2RAD(0);
    phaseDiff[1] = DEG2RAD(0);
    if (isForward == true){
        phaseDiff[2] = DEG2RAD(90);
        phaseDiff[3] = DEG2RAD(90);
    }
    else{
        phaseDiff[2] = DEG2RAD(-90);
        phaseDiff[3] = DEG2RAD(-90);
    }
    for (int i = 0; i < steps; i++){
        oscillate(A, O, T, phaseDiff);
    }
    servoDetach();
}

void PenguinBot::turn(int steps, int T, bool isRight){
    int A[NB_SERVOS] = {30, 30, 0, 0};
    int O[NB_SERVOS] = {0, 0, 0, 0};
    double phaseDiff[NB_SERVOS] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};
    servoAttach();
    if (isRight == true){
        A[2] = 60;
        A[3] = 10;
    }
    else{
        A[2] = 10;
        A[3] = 60;
    }
    for (int i = 0; i < steps; i++){
        oscillate(A, O, T, phaseDiff);
    }
    servoDetach();
}


void PenguinBot::stop(void){
    servoAttach();
    defaultPosition();
    servoDetach();
}

void PenguinBot::moonWalk(bool isRight, int steps, int T){
    int A[NB_SERVOS] = {25, 25, 0, 0};
    int O[NB_SERVOS] = { -15, 15, 0, 0};
    double phaseDiff[NB_SERVOS];
    servoAttach();
    phaseDiff[0] = DEG2RAD(0);
    phaseDiff[2] = DEG2RAD(90);
    phaseDiff[3] = DEG2RAD(90);
    if (isRight == true){
        phaseDiff[1] = DEG2RAD(180 + 120);
    }
    else{
      phaseDiff[1] = DEG2RAD(180 - 120);
    }
    for (int i = 0; i < steps; i++){
        oscillate(A, O, T, phaseDiff);
    }
    servoDetach();
}

void PenguinBot::swing(int steps, int T){
    servoAttach();
    int A[NB_SERVOS] = {25, 25, 0, 0};
    int O[NB_SERVOS] = { -15, 15, 0, 0};
    double phaseDiff[NB_SERVOS] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};
    for (int i = 0; i < steps; i++){
        oscillate(A, O, T, phaseDiff);
    }
    servoDetach();
}

void PenguinBot::upDown(int steps, int T){
    servoAttach();
    int A[NB_SERVOS] = {25, 25, 0, 0};
    int O[NB_SERVOS] = { -15, 15, 0, 0};
    double phaseDiff[NB_SERVOS] = {DEG2RAD(180), DEG2RAD(0), DEG2RAD(270), DEG2RAD(270)};
    for (int i = 0; i < steps; i++){
        oscillate(A, O, T, phaseDiff);
    }
    defaultPosition();
    servoDetach();
}

void PenguinBot::flapping(int steps, int T) {
    servoAttach();
    int A[NB_SERVOS] = {15, 15, 8, 8};
    int O[NB_SERVOS] = { -A[0], A[1], 0, 0};
    double phaseDiff[NB_SERVOS] = {DEG2RAD(0), DEG2RAD(180), DEG2RAD(-90), DEG2RAD(90)};
    for (int i = 0; i < steps; i++){
        oscillate(A, O, T, phaseDiff);
    }
    servoDetach();
}

void PenguinBot::run(int steps, int T){
    servoAttach();
    int A[NB_SERVOS] = {10, 10, 10, 10};
    int O[NB_SERVOS] = {0, 0, 0, 0};
    double phaseDiff[NB_SERVOS] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};
    for (int i = 0; i < steps; i++){
        oscillate(A, O, T, phaseDiff);
    }
    servoDetach();
}

void PenguinBot::runFast(int steps, int T){
    servoAttach();
    int A[NB_SERVOS] = {25, 25, 30, 30};
    int O[NB_SERVOS] = { -15, 15, 0, 0};
    double phaseDiff[NB_SERVOS] = {DEG2RAD(0), DEG2RAD(180 + 120), DEG2RAD(90), DEG2RAD(90)};
    for (int i = 0; i < steps; i++){
        oscillate(A, O, T, phaseDiff);
    }
    defaultPosition();
    servoDetach();
}

void PenguinBot::backward(int steps, int T){
    servoAttach();
    int A[NB_SERVOS] = {15, 15, 30, 30};
    int O[NB_SERVOS] = {0, 0, 0, 0};
    double phaseDiff[NB_SERVOS] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(-90), DEG2RAD(-90)};
    for (int i = 0; i < steps; i++){
        oscillate(A, O, T, phaseDiff);
    }
    servoDetach();
}

void PenguinBot::backwardSlow(int steps, int T){
    servoAttach();
    int A[NB_SERVOS] = {15, 15, 30, 30};
    int O[NB_SERVOS] = {0, 0, 0, 0};
    double phaseDiff[NB_SERVOS] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(-90), DEG2RAD(-90)};
    for (int i = 0; i < steps; i++){
        oscillate(A, O, T, phaseDiff);
    }
    servoDetach();
}

void PenguinBot::goingUp(int tempo){
    servoAttach();
    int move[] = {50, 130, 90, 90};
    moveNServos(tempo * HIGH_RATE, move);
    delay(tempo / 2);
    defaultPosition();
    servoDetach();
}

void PenguinBot::drunk(int tempo){
    servoAttach();
    int move1[] = {70, 70, 90, 90};
    int move2[] = {110, 110, 90, 90};
    int move3[] = {70, 70, 90, 90};
    int move4[] = {110, 110, 90, 90};
    moveNServos(tempo * MID_RATE, move1);
    moveNServos(tempo * MID_RATE, move2);
    moveNServos(tempo * MID_RATE, move3);
    moveNServos(tempo * MID_RATE, move4);
    defaultPosition();
    servoDetach();
}

void PenguinBot::noGravity(int tempo){
    servoAttach();
    int move1[] = {120, 140, 90, 90};
    int move2[] = {120, 30, 90, 90};
    int move3[] = {120, 120, 90, 90};
    int move4[] = {120, 30, 120, 120};
    int move5[] = {120, 30, 60, 60};
    moveNServos(tempo * MID_RATE, move1);
    delay(tempo);
    moveNServos(tempo * MID_RATE, move2);
    moveNServos(tempo * MID_RATE, move3);
    moveNServos(tempo * MID_RATE, move2);
    delay(tempo);
    moveNServos(tempo * LOW_RATE, move4);
    delay(tempo);
    moveNServos(tempo * LOW_RATE, move5);
    delay(tempo);
    moveNServos(tempo * LOW_RATE, move4);
    delay(tempo);
    defaultPosition();
    servoDetach();
}

void PenguinBot::kickLeft(int tempo){
    servoAttach();
    int move1[] = {120, 140, 90, 90};
    int move2[] = {120, 90, 90, 90};
    int move3[] = {120, 120, 90, 90};
    int move4[] = {120, 90, 120, 120};
    int move5[] = {120, 120, 60, 60};
    moveNServos(tempo * MID_RATE, move1);
    delay(tempo);
    moveNServos(tempo * MID_RATE, move2);
    delay(tempo / 4);
    moveNServos(tempo * MID_RATE, move3);
    delay(tempo / 4);
    moveNServos(tempo * LOW_RATE, move4);
    delay(tempo / 4);
    moveNServos(tempo * LOW_RATE, move5);
    delay(tempo / 4);
    defaultPosition();
    servoDetach();
}

void PenguinBot::kickRight(int tempo) {
    servoAttach();
    int move1[] = {40, 60, 90, 90};
    int move2[] = {90, 60, 90, 90};
    int move3[] = {60, 60, 90, 90};
    int move4[] = {90, 60, 120, 120};
    int move5[] = {60, 60, 60, 60};
    moveNServos(tempo * MID_RATE, move1);
    delay(tempo);
    moveNServos(tempo * MID_RATE, move2);
    delay(tempo / 4);
    moveNServos(tempo * MID_RATE, move3);
    delay(tempo / 4);
    moveNServos(tempo * LOW_RATE, move4);
    delay(tempo / 4);
    moveNServos(tempo * LOW_RATE, move5);
    delay(tempo / 4);
    defaultPosition();
    servoDetach();
}

void PenguinBot::legRaise(int tempo, bool isRight){
    servoAttach();
    if (isRight == true){
        int move[] = {70, 70, 60, 60};
        moveNServos(tempo * MID_RATE, move);
        delay(tempo);
    }
    else{
        int move[] = {110, 110, 120, 120};
        moveNServos(tempo * MID_RATE, move);
        delay(tempo);
    }
    defaultPosition();
    servoDetach();
}

void PenguinBot::legRaise1(int tempo, bool isRight){
    servoAttach();
    if (isRight == true){
        int move1[] = {50, 60, 90, 90};
        int move2[] = {60, 60, 120, 90};
        int move3[] = {60, 60, 60, 90};
        moveNServos(tempo * MID_RATE, move1);
        delay(tempo);
        moveNServos(tempo * LOW_RATE, move2);
        delay(tempo / 4);
        moveNServos(tempo * LOW_RATE, move3);
        delay(tempo / 4);
        moveNServos(tempo * LOW_RATE, move2);
        delay(tempo / 4);
        moveNServos(tempo * LOW_RATE, move3);
        delay(tempo / 4);
    }
    else{
        int move1[] = {120, 130, 90, 90};
        int move2[] = {120, 120, 90, 60};
        int move3[] = {120, 120, 90, 120};
        moveNServos(tempo, move1);
        delay(tempo);
        moveNServos(tempo * MID_RATE, move2);
        delay(tempo / 4);
        moveNServos(tempo * MID_RATE, move3);
        delay(tempo / 4);
        moveNServos(tempo * MID_RATE, move2);
        delay(tempo / 4);
        moveNServos(tempo * MID_RATE, move3);
        delay(tempo / 4);
    }
    defaultPosition();
    servoDetach();
}

void PenguinBot::legRaise2(int steps, int tempo, bool isRight){
    servoAttach();
    if (isRight == true){
        int move1[] = {20, 60, 90, 90};
        int move2[] = {20, 90, 120, 90};
        for (int i = 0; i < steps; i++){
            moveNServos(tempo * 0.7, move1);
            delay(tempo / 4);
            moveNServos(tempo * 0.7, move2);
            delay(tempo / 4);
        }
    }
    else{
        int move1[] = {120, 160, 90, 90};
        int move2[] = {90, 160, 90, 60};
        for (int i = 0; i < steps; i++){
            moveNServos(tempo * 0.7, move1);
            delay(tempo / 4);
            moveNServos(tempo * 0.7, move2);
            delay(tempo / 4);
        }
    }
    defaultPosition();
    servoDetach();
}

void PenguinBot::legRaise3(int steps, int tempo, bool isRight){
    servoAttach();
    if (isRight == true){
        int move1[] = {20, 60, 90, 90};
        int move2[] = {20, 90, 90, 90};
        for (int i = 0; i < steps; i++){
            moveNServos(tempo * 0.5, move1);
            delay(tempo / 4);
            moveNServos(tempo * 0.5, move2);
            delay(tempo / 4);
        }
    }
    else{
        int move1[] = {120, 160, 90, 90};
        int move2[] = {90, 160, 90, 90};
        for (int i = 0; i < steps; i++){
            moveNServos(tempo * 0.5, move1);
            delay(tempo / 4);
            moveNServos(tempo * 0.5, move2);
            delay(tempo / 4);
        }
    }
    defaultPosition();
    servoDetach();
}

void PenguinBot::legRaise4(int tempo, bool isRight){
    servoAttach();
    if (isRight == true){
        int move1[] = {20, 60, 90, 90};
        int move2[] = {20, 90, 90, 90};
        moveNServos(tempo * MID_RATE, move1);
        delay(tempo / 4);
        moveNServos(tempo * MID_RATE, move2);
        delay(tempo / 4);
    }
    else{
        int move1[] = {120, 160, 90, 90};
        int move2[] = {90, 160, 90, 90};
        moveNServos(tempo * MID_RATE, move1);
        delay(tempo / 4);
        moveNServos(tempo * MID_RATE, move2);
        delay(tempo / 4);
    }
    defaultPosition();
    servoDetach();
}

void PenguinBot::sitDown(void){
    servoAttach();
    int move1[] = {150, 90, 90, 90};
    int move2[] = {150, 30, 90, 90};
    moveNServos(DEFAULT_TEMPO * ULTRA_LOW_RATE, move1);
    delay(DEFAULT_TEMPO / 2);
    moveNServos(DEFAULT_TEMPO * ULTRA_LOW_RATE, move2);
    delay(DEFAULT_TEMPO / 2);
    defaultPosition();
    servoDetach();
}

void PenguinBot::raiseFoot(bool isRight, int tempo){
    servoAttach();
    if (isRight == true){
        int move1[] = {CENTER - 2 * AMPLITUDE, CENTER - AMPLITUDE, CENTER, CENTER};
        int move2[] = {CENTER + AMPLITUDE, CENTER - AMPLITUDE, CENTER, CENTER};
        int move3[] = {CENTER - 2 * AMPLITUDE, CENTER - AMPLITUDE, CENTER, CENTER};
        moveNServos(tempo * LOW_RATE, move1);
        delay(tempo * 2);
        moveNServos(tempo * ULTRA_HIGH_RATE, move2);
        delay(tempo / 2);
        moveNServos(tempo * ULTRA_HIGH_RATE, move3);
        delay(tempo);
    }
    else{
        int move1[] = {CENTER + AMPLITUDE, CENTER + 2 * AMPLITUDE, CENTER, CENTER};
        int move2[] = {CENTER + AMPLITUDE, CENTER - AMPLITUDE, CENTER, CENTER};
        int move3[] = {CENTER + AMPLITUDE, CENTER + 2 * AMPLITUDE, CENTER, CENTER};
        moveNServos(tempo * LOW_RATE, move1);
        delay(tempo * 2);
        moveNServos(tempo * ULTRA_HIGH_RATE, move2);
        delay(tempo / 2);
        moveNServos(tempo * ULTRA_HIGH_RATE, move3);
        delay(tempo);
    }
    defaultPosition();
    servoDetach();
}

void PenguinBot::shakeIt(void){
    servoAttach();
    double pause;
    int move1[NB_SERVOS] = {90, 90, 80, 100};
    int move2[NB_SERVOS] = {90, 90, 100, 80};
    for (int i = 0; i < 9; i++){
        pause = millis();
        moveNServos(DEFAULT_TEMPO * 0.15, move1);
        moveNServos(DEFAULT_TEMPO * 0.15, move2);
        while (millis() < (pause + DEFAULT_TEMPO));
    }
    defaultPosition();
    servoDetach();
}

void PenguinBot::dance1(void){
    raiseFoot(true , DEFAULT_TEMPO);
    raiseFoot(false, DEFAULT_TEMPO);
    shakeIt();
    moonWalk(false, 4, DEFAULT_TEMPO * 2);
    moonWalk(true , 4, DEFAULT_TEMPO * 2);
    drunk(DEFAULT_TEMPO * 4);
    kickLeft (DEFAULT_TEMPO);
    kickRight(DEFAULT_TEMPO);
    drunk(DEFAULT_TEMPO / 2);
    run(4, DEFAULT_TEMPO * 4);
    defaultPosition();
    backward(2, DEFAULT_TEMPO * 2);
    defaultPosition();
    goingUp  (DEFAULT_TEMPO * 1);
    defaultPosition();
}

void PenguinBot::dance2(void){
    sitDown();
    raiseFoot(true , DEFAULT_TEMPO);
    raiseFoot(false, DEFAULT_TEMPO);
    drunk(DEFAULT_TEMPO / 2);
    drunk(DEFAULT_TEMPO);
    kickLeft (DEFAULT_TEMPO);
    kickRight(DEFAULT_TEMPO);
    runFast(4, DEFAULT_TEMPO * 4);
    defaultPosition();
    backward(2, DEFAULT_TEMPO * 4);
    noGravity(DEFAULT_TEMPO);
    raiseFoot(true , DEFAULT_TEMPO);
    raiseFoot(false, DEFAULT_TEMPO);
    shakeIt();
    upDown(5, DEFAULT_TEMPO);
}

void PenguinBot::dance3(void){
    flapping(1, DEFAULT_TEMPO);
    drunk(DEFAULT_TEMPO);
    kickLeft(DEFAULT_TEMPO);
    runFast(4, DEFAULT_TEMPO * 4);
    defaultPosition();
    raiseFoot(false, DEFAULT_TEMPO);
    sitDown();
    legRaise(DEFAULT_TEMPO, true);
    swing(5, DEFAULT_TEMPO);
    backward(2, DEFAULT_TEMPO * 4);
    goingUp(DEFAULT_TEMPO);
    noGravity(DEFAULT_TEMPO);
    upDown(5, DEFAULT_TEMPO);
    legRaise1(DEFAULT_TEMPO, true);
    legRaise2(4, DEFAULT_TEMPO, false);
    kickRight(DEFAULT_TEMPO);
    goingUp(DEFAULT_TEMPO);
    legRaise3(4, DEFAULT_TEMPO, true);
    kickLeft(DEFAULT_TEMPO);
    legRaise4(DEFAULT_TEMPO, true);
    shakeIt();
    sitDown();
}
};

