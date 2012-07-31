int gaugePin = 9;
int baud = 28800;
int gaugeVal = 0;
int newGaugeVal = 0;
int distance;

int state = 1; // Start at the tens

void setup() {
  Serial.begin(baud);
  pinMode(gaugePin, OUTPUT);
}

void loop() {
  if (gaugeVal != newGaugeVal) {
    distance = abs(gaugeVal - newGaugeVal);
    gaugeVal = newGaugeVal;
    analogWrite(gaugePin, map(gaugeVal, 0, 99, 0, 255));
    delay(map(distance, 0, 99, 0, 200));
  }
}

void serialEvent(){
  char ch = Serial.read();
  if (isDigit(ch)) {
    int val = ch - '0';
    switch(state) {
      case 1: // Tens
        newGaugeVal = val * 10;
        state = 0;
      break;
      case 0: // Ones
        newGaugeVal = newGaugeVal + val;
        state = 1;
      break;
    }
  }
}

