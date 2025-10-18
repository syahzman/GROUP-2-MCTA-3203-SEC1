// Define the pins for each segment
const int segmentA = 3;
const int segmentB = 2;
const int segmentC = 8;
const int segmentD = 7;
const int segmentE = 6;
const int segmentF = 10;
const int segmentG = 5;

// Define button pins
const int buttonInc = 11;
const int buttonReset = 12;

// Variables
int number = 0;
bool lastIncState = HIGH;
bool lastResetState = HIGH;

// 7-segment display digits (for common cathode)
// HIGH = ON, LOW = OFF
const int digits[10][7] = {
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW},   // 0
  {LOW, HIGH, HIGH, LOW, LOW, LOW, LOW},       // 1
  {HIGH, HIGH, LOW, HIGH, HIGH, LOW, HIGH},    // 2
  {HIGH, HIGH, HIGH, HIGH, LOW, LOW, HIGH},    // 3
  {LOW, HIGH, HIGH, LOW, LOW, HIGH, HIGH},     // 4
  {HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH},    // 5
  {HIGH, LOW, HIGH, HIGH, HIGH, HIGH, HIGH},   // 6
  {HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW},      // 7
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH},  // 8
  {HIGH, HIGH, HIGH, HIGH, LOW, HIGH, HIGH}    // 9
};

// Segment pins array
int segments[] = {segmentA, segmentB, segmentC, segmentD, segmentE, segmentF, segmentG};

void setup() {
  // Initialize 7-segment pins as OUTPUT
  for (int i = 0; i < 7; i++) {
    pinMode(segments[i], OUTPUT);
  }

  // Initialize buttons with internal pull-up
  pinMode(buttonInc, INPUT_PULLUP);
  pinMode(buttonReset, INPUT_PULLUP);

  // Start showing 0
  displayDigit(number);
}

void loop() {
  bool incState = digitalRead(buttonInc);
  bool resetState = digitalRead(buttonReset);

  // Increment button pressed (active LOW)
  if (incState == LOW && lastIncState == HIGH) {
    number++;
    if (number > 9) number = 0;
    displayDigit(number);
    delay(250); // debounce
  }

  // Reset button pressed (active LOW)
  if (resetState == LOW && lastResetState == HIGH) {
    number = 0;
    displayDigit(number);
    delay(250); // debounce
  }

  lastIncState = incState;
  lastResetState = resetState;
}

// Function to display a digit (0–9)
void displayDigit(int num) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segments[i], digits[num][i]);
  }
}


