#ifndef PenguinBot_h
#define PenguinBot_h

#include "Oscillator.h"
#include "NeoSWSerial.h"

class PenguinBot
{
  public:
    void servoAttach(void);
    void servoDetach(void);
    void moveNServos(int time, int newPosition[]);
    void oscillate(int A[4], int O[4], int T, double phaseDiff[4]);
    void defaultPosition(void);
    void walk(int steps, int T, bool isForward);
    void turn(int steps, int T, bool isRight);
    void stop(void);
    void moonWalk(bool isRight, int steps, int T);
    void swing(int steps, int T);
    void upDown(int steps, int T);
    void flapping(int steps, int T);
    void run(int steps, int T);
    void runFast(int steps, int T);
    void backward(int steps, int T);
    void backwardSlow(int steps, int T);
    void goingUp(int tempo);
    void drunk(int tempo);
    void noGravity(int tempo);
    void kickLeft(int tempo);
    void kickRight(int tempo);
    void legRaise(int tempo, bool isRight);
    void legRaise1(int tempo, bool isRight);
    void legRaise2(int steps, int tempo, bool isRight);
    void legRaise3(int steps, int tempo, bool isRight);
    void legRaise4(int tempo, bool isRight);
    void sitDown(void);
    void raiseFoot(bool isRight, int tempo);
    void shakeIt(void);
    void dance1(void);
    void dance2(void);
    void dance3(void);
    
  private:
    #define BTN_FORWARD  16736925
    #define BTN_BACKWARD 16754775
    #define BTN_LEFT     16761405
    #define BTN_RIGHT    16720605
    #define BTN_DANCE    16718055
    #define BTN_MUSIC    16724175
    #define BTN_MODE     16734885
    #define BTN_UP       16716015
    #define BTN_DOWN     16726215
    #define BTN_STOP     16712445
    #define BTN_VOL      16743045

    #define UP_RIGHT_PIN  10 // 3
    #define UP_LEFT_PIN    9 // 2
    #define LOW_RIGHT_PIN 12 // 1
    #define LOW_LEFT_PIN   6 // 0

    #define DEFAULT_TEMPO 450

    #define ST188_L_PIN         A0
    #define ST188_R_PIN         A1
    #define SOFTWARE_RXD        A2
    #define SOFTWARE_TXD        A3
    #define VOLTAGE_MEASURE_PIN A4
    #define INDICATOR_LED_PIN   A5

    #define RECV_PIN   3
    #define ECHO_PIN   4
    #define TRIG_PIN   5
    #define HT6871_PIN 7

    #define VREF 1.1
    #define RES1 10000
    #define RES2 2000

    #define NB_SERVOS         4
    #define INTERVAL_TIME  10.0
    #define CENTER           90
    #define AMPLITUDE        30
    #define ULTRA_HIGH_RATE 0.3
    #define HIGH_RATE       0.5
    #define MID_RATE        0.7
    #define LOW_RATE        1.0
    #define ULTRA_LOW_RATE  1.5


    enum MODE{
        IR_CONTROL,
        OBSTACLES_AVOIDANCE,
        FOLLOW,
        MUSIC,
        DANCE,
        VOLUME
    } mainMode = IR_CONTROL, oldMainMode = IR_CONTROL;

    enum DIRECTION{
        FORWARD,
        BACKWARD,
        TURN_RIGHT,
        TURN_LEFT,
        STOP,
    } direction = STOP;

    Oscillator  servo[NB_SERVOS];
    int         oldPosition[NB_SERVOS] = {CENTER, CENTER, CENTER, CENTER};
    int            danceIndex         = 1;
    int            musicIndex         = 2;
    bool           ledFlag            = true;
    unsigned long  ledBlinkTime       = 0;
    unsigned long  voltageMeasureTime = 0;
};

#endif
