/*
  Sensor Mapping
    Sensor  Angle Pin Port
    S1      0     A3  C3
    S2            A2  C2
    S3            A1  C1
    S4            A0  C0
    S5      90    13  B5
    S6            12  B4
    S7            11  B3
    S8            10  B2
    S9      180   9   B1
    S10           8   B0
    S11           7   D7
    S12           6   D6
    S13     270   5   D5
    S14           4   D4
    S15           3   D3
    S16           2   D2
    loop cycle duration: 3.2 millis
*/

int PIN_LED[4] = {12, 13, 22, 23};
int PIN_SENSOR[16] = {35, 34, 39, 36, 19, 18, 5, 4, 2, 15, 14, 27, 26, 25, 33, 32};

#define NCYCLES 700  //350
#define BROKEN ((NCYCLES * 86) / 100)
#define TOO_LOW ((NCYCLES * 17) / 100)

float SENSOR_X[16];
float SENSOR_Y[16];

int counter[16];
int angle = 0, distance = 0;

void setup() {
  delay(1000);

  Serial.begin(57600);
  Serial1.begin(9600);
  Serial2.begin(9600);

  // for(int i=0; i<16; i++) {
  //   pinMode(PIN_SENSOR[i], INPUT);
  // }

  for(int i=0; i<4; i++) {
    pinMode(PIN_LED[i], OUTPUT);
  }

  // for (int i = 0; i < 16; i++) {
  //   SENSOR_X[i] = cos((22.5 * PI / 180) * i);
  //   SENSOR_Y[i] = sin((22.5 * PI / 180) * i);
  // }

  digitalWrite(PIN_LED[0], HIGH);
}

void loop() {
  static unsigned long sendTimer = 0;
  
  // if (millis() - sendTimer > 1000) {
    Serial1.write("a");
    Serial2.write("a");
    Serial.println("a");
    sendTimer = millis();
    digitalWrite(PIN_LED[1], !digitalRead(PIN_LED[1]));
    
    // Wait for echo
    unsigned long start = millis();
    // while(Serial2.available() == 0 && millis() - start < 100) {
    //   // Wait for response
    // }
    // if(Serial2.available()) {
    //   char c = Serial2.read();
    //   if(c == 'a') {
    //     digitalWrite(PIN_LED[2], HIGH); // Indicate successful comms
    //   }
    // }
  // }
  // readBallInterpolation();
  // printCounters();
  // printBall();
  // angle = 360;
  // distance = 20;
  // sendDataInterpolation();
}

void readBallInterpolation() {
  for (int i=0; i<16; i++) {
    counter[i] = 0;
  }

  for (int i=0; i<NCYCLES; i++) {
    for (int j=0; j<16; j++) {
      counter[j] += digitalRead(PIN_SENSOR[j]);
    }
  }

  for (int i=0; i<16; i++) {
    counter[i] = NCYCLES - counter[i];
  }

  float x=0, y=0;
  for (int i=0; i<16; i++) {
    if (counter[i] > BROKEN || counter[i] < TOO_LOW) counter[i] = 0;

    x += SENSOR_X[i] * counter[i];
    y += SENSOR_Y[i] * counter[i];
  }

  angle = atan2(y, x) * 180 / PI;
  angle = ((int)(angle + 360)) % 360;

  //distance is 0 when not seeing ball
  distance = hypot(x, y);

  int maxSensorValue = 0;
  for (int i = 0; i < 16; i++) {
    maxSensorValue = max(maxSensorValue, counter[i]);
  }
  distance = maxSensorValue;

  digitalWrite(PIN_LED[3], distance);
}

void sendDataInterpolation() {
  static unsigned long sendTimer = 0;
  String sendAngle = String(angle);
  if (sendAngle.length() == 1) sendAngle = "a00" + sendAngle;
  if (sendAngle.length() == 2) sendAngle = "a0" + sendAngle;
  if (sendAngle.length() == 3) sendAngle = "a" + sendAngle;

  String sendDistance = String(distance);
  if (sendDistance.length() == 1) sendDistance = "d00" + sendDistance;
  if (sendDistance.length() == 2) sendDistance = "d0" + sendDistance;
  if (sendDistance.length() == 3) sendDistance = "d" + sendDistance;

  if (millis() - sendTimer > 1000) {
    Serial2.println(sendAngle);
    Serial2.println(sendDistance);

    sendTimer = millis();
    digitalWrite(PIN_LED[1], !digitalRead(PIN_LED[1]));
  }
}

void printBall() {
  Serial.print("Angle = ");
  Serial.print(angle);

  Serial.print(" | Distance = ");
  Serial.println(distance);
}

void printCounters() {
  for (int i = 0; i < 16; i++) {
    Serial.print("Sensor[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(counter[i]);
  }
  Serial.println("----------------------------");
  delay(1000);
}

void blink() {
  for (int i=0; i<4; i++) {
    digitalWrite(PIN_LED[i], HIGH);
  }
  delay(1000);

  for (int i=0; i<4; i++) {
    digitalWrite(PIN_LED[i], LOW);
  }
  delay(1000);
}