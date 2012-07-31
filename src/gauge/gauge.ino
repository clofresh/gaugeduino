int gaugePin = 9;
int baud = 28800;
int gaugeVal = 0;
int newGaugeVal = 0;
int distance;

// The state variable determines what digit the next value of Serial.read() is.
//   0: one's digit
//   1: ten's digit
// The starting state is the ten's digit, as the state machine reads digits in
// most-significant to least-significant order.
int state = 1; 

// Init
void setup() {
  // Initialize the serial port
  Serial.begin(baud);

  // Initialize the gauge output pin
  pinMode(gaugePin, OUTPUT);
}

// Main loop
void loop() {
  // Only update the gauge output if the gauge value has changed
  if (gaugeVal != newGaugeVal) {
    // Compute the absolute distance between the new and old gauge values 
    distance = abs(gaugeVal - newGaugeVal);

    // Update the output pin. We expect the gauge values to range from 0-99,
    // and the analog output pin expects values between 0-255.
    gaugeVal = newGaugeVal;
    analogWrite(gaugePin, map(gaugeVal, 0, 99, 0, 255));

    // Wait a small amount of time for the gauge to settle. The delay is
    // proportional to the distance the gauge needle has to travel.
    delay(map(distance, 0, 99, 0, 200));
  }
}

// Callback for whenever there's data on the serial port
void serialEvent(){
  char ch = Serial.read();
  if (isDigit(ch)) {
    int val = ch - '0'; // Convert the char input into an integer

    // Input state machine.
    switch(state) {
      case 1: // Got a ten's digit, expect a one's digit next
        newGaugeVal = val * 10;
        state = 0;
      break;
      case 0: // Got a one's digit, expect a ten's digit next
        newGaugeVal = newGaugeVal + val;
        state = 1;
      break;
    }
  }
}

