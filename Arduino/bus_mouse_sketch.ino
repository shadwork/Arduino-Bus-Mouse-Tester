#include <limits.h>
// Add encoder library
#include <Encoder.h>

// Bus mouse to arduino pins
#define MOUSE_PIN_BUTTON_LEFT 0
#define MOUSE_PIN_BUTTON_RIGHT 2
#define MOUSE_PIN_BUTTON_MIDDLE 1
#define MOUSE_PIN_X1_ENCODER 5
#define MOUSE_PIN_X2_ENCODER 4
#define MOUSE_PIN_Y1_ENCODER 6
#define MOUSE_PIN_Y2_ENCODER 7

struct busMouse
{
  byte buttons[3];
  long xAxys;
  long yAxys;
};

typedef struct busMouse BusMouseState;

BusMouseState mouseState = {{CHAR_MAX, CHAR_MAX, CHAR_MAX}, LONG_MAX, LONG_MAX};

Encoder xEncoder(MOUSE_PIN_X1_ENCODER, MOUSE_PIN_X2_ENCODER);
Encoder yEncoder(MOUSE_PIN_Y1_ENCODER, MOUSE_PIN_Y2_ENCODER);

void setup() {
  pinMode(MOUSE_PIN_BUTTON_LEFT, INPUT_PULLUP);
  pinMode(MOUSE_PIN_BUTTON_RIGHT, INPUT_PULLUP);
  pinMode(MOUSE_PIN_BUTTON_MIDDLE, INPUT_PULLUP);
  Serial.begin(115200);
}

void loop() {

  BusMouseState current_state;
  current_state.buttons[0] = digitalRead(MOUSE_PIN_BUTTON_LEFT);
  current_state.buttons[1] = digitalRead(MOUSE_PIN_BUTTON_MIDDLE);
  current_state.buttons[2] = digitalRead(MOUSE_PIN_BUTTON_RIGHT);
  current_state.xAxys = xEncoder.read();
  current_state.yAxys = yEncoder.read();

  if (isStateInitial(current_state)) {
    mouseState = current_state;
    printMouseStatus(current_state, mouseState);
  }

  if (!isStateEquals(mouseState, current_state)) {
    printMouseStatus(current_state, mouseState);
  }

  mouseState = current_state;
}

void printMouseStatus(BusMouseState current, BusMouseState saved) {
  Serial.print("Buttons : ");
  printPinStatus(current.buttons[0]);
  printPinStatus(current.buttons[1]);
  printPinStatus(current.buttons[2]);

  Serial.print(" Direction : ");
  printXaxysStatus(saved.xAxys - current.xAxys);
  Serial.print(" ");
  printYaxysStatus(saved.yAxys - current.yAxys);

  Serial.print(" Coordinates : ");
  Serial.print(current.xAxys);
  Serial.print(" ");
  Serial.print(current.yAxys);
  Serial.println("");
}

boolean isStateEquals(BusMouseState left, BusMouseState right) {
  if (left.buttons[0] != right.buttons[0]) {
    return false;
  } else if (left.buttons[1] != right.buttons[1]) {
    return false;
  } else if (left.buttons[2] != right.buttons[2]) {
    return false;
  } else if (left.xAxys != right.xAxys) {
    return false;
  } else if (left.yAxys != right.yAxys) {
    return false;
  }
  return true;
}

boolean isStateInitial(BusMouseState value) {
  if (value.buttons[0] != CHAR_MAX) {
    return false;
  } else if (value.buttons[1] != CHAR_MAX) {
    return false;
  } else if (value.buttons[2] != CHAR_MAX) {
    return false;
  } else if (value.xAxys != LONG_MAX) {
    return false;
  } else if (value.yAxys != LONG_MAX) {
    return false;
  }
  return true;
}

void printPinStatus(byte value) {
  if (value == HIGH) {
    Serial.print ("-");
  } else {
    Serial.print ("+");
  }
}

void printXaxysStatus(long value) {
  if (value < 0) {
    Serial.print ("--Left--");
  } else if (value > 0 ) {
    Serial.print ("--Right-");
  } else {
    Serial.print ("--Hold--");
  }
}

void printYaxysStatus(long value) {
  if (value < 0) {
    Serial.print ("---Up---");
  } else if (value > 0 ) {
    Serial.print ("--Down--");
  } else {
    Serial.print ("--Hold--");
  }
}
