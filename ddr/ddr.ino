#include <Servo.h>
extern const uint8_t song_map[392][3];
int song_map_len = 392;
int BPM = 130;
int LPB = 2;  // lines per beat

Servo L_SRVO;
Servo R_SRVO;
Servo U_SRVO;
Servo D_SRVO;

int SRVO_LIFT = 90;
int SRVO_PUSH = 60;

int L_SRVO_PIN = 3;
int R_SRVO_PIN = 5;
int U_SRVO_PIN = 6;
int D_SRVO_PIN = 9;
int S_BTTN_PIN = 12;
int LED_PINS[] = {10, 11};
int S_BTTN;

int L_FOOT_COLOR[] = {255, 0};
int R_FOOT_COLOR[] = {0, 255};
int B_FEET_COLOR[] = {255, 255};

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    L_SRVO.attach(L_SRVO_PIN);
    R_SRVO.attach(R_SRVO_PIN);
    U_SRVO.attach(U_SRVO_PIN);
    D_SRVO.attach(D_SRVO_PIN);
    pinMode(S_BTTN_PIN, INPUT);

    // initialize sevos to default position
    clear_pad();

    play_song();
}

void loop() {
    // put your main code here, to run repeatedly:
    // int S_BTTN = digitalRead(S_BTTN);
    // if (S_BTTN == 1) {
    //     play_song();
    // }
    // delay(10);
}

void play_song() {
    for (int i=0; i < song_map_len; i++) {
        if (!(song_map[i][0] == 0 && song_map[i][2] == 0)) { // checks that this is not a holding input
            clear_pad(); // since we're not holding reset the pad
            if (song_map[i][0] > 9) { // double arrow press
                // in a double arrow value, the first digit is one foot, and the second is another,
                // hence we divide and mod by 10 to obtain both values
                move_arrow(song_map[i][0] / 10);
                move_arrow(song_map[i][0] % 10);
                set_led(song_map[i][1]);
            } else if (song_map[i][0] > 0) { // single arrow press
                move_arrow(song_map[i][0]);
                set_led(song_map[i][1]);
            }
        }
        delay((60000/BPM)/LPB);
    }
}

void move_arrow(int x) {
    switch (x) {
        case 1:
            // Up
            U_SRVO.write(SRVO_PUSH);
        case 2:
            // right
            R_SRVO.write(SRVO_PUSH);
        case 3:
            // down
            D_SRVO.write(SRVO_PUSH);
        case 4:
            // left
            L_SRVO.write(SRVO_PUSH);
    }
}

void set_led(int x) {
    switch (x) {
        case 1:
            // left
            analogWrite(LED_PINS[0], L_FOOT_COLOR[0]);
            analogWrite(LED_PINS[1], L_FOOT_COLOR[1]);
        case 2:
            // right
            analogWrite(LED_PINS[0], R_FOOT_COLOR[0]);
            analogWrite(LED_PINS[1], R_FOOT_COLOR[1]);
        case 3:
            // both
            analogWrite(LED_PINS[0], B_FEET_COLOR[0]);
            analogWrite(LED_PINS[1], B_FEET_COLOR[1]);
    }
}

void clear_pad() {
    U_SRVO.write(SRVO_LIFT);
    L_SRVO.write(SRVO_LIFT);
    R_SRVO.write(SRVO_LIFT);
    D_SRVO.write(SRVO_LIFT);
    analogWrite(LED_PINS[0], 0);
    analogWrite(LED_PINS[1], 0);
}
