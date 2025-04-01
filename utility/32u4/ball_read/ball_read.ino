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

#define LED1 12
#define LED2 13
#define LED3 22
#define LED4 23

#define S0 35
#define S1 34
#define S2 39
#define S3 36
#define S4 19
#define S5 18
#define S6 5
#define S7 4
#define S8 2
#define S9 15
#define S10 14
#define S11 27
#define S12 26
#define S13 25
#define S14 33
#define S15 32

#define NCYCLES 700  //350

//int x = int((NCYCLES*86)/100);
//int y = int((NCYCLES*17)/100);

#define BROKEN ((NCYCLES * 86) / 100)
#define TOO_LOW ((NCYCLES * 17) / 100)

int counter[16];

int distance;
int nmax = 0;
int sensor = 0;

int oldIndex = 0;
int oldDistance = 0;

byte ballInfo = 0;

float xs[16];
float ys[16];

float angle = 0, dist = 0;
boolean sending = false;
byte sendAngle = 0, sendDistance = 0;
byte sendByte = 0;

unsigned long t = 0;

void setup() {
  delay(1000);

  Serial.begin(57600);
  Serial2.begin(57600);

  pinMode(S0, INPUT);
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);
  pinMode(S6, INPUT);
  pinMode(S7, INPUT);
  pinMode(S8, INPUT);
  pinMode(S9, INPUT);
  pinMode(S10, INPUT);
  pinMode(S11, INPUT);
  pinMode(S12, INPUT);
  pinMode(S13, INPUT);
  pinMode(S14, INPUT);
  pinMode(S15, INPUT);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  for (int i = 0; i < 16; i++) {
    xs[i] = cos((22.5 * PI / 180) * i);
    ys[i] = sin((22.5 * PI / 180) * i);
  }
}

void loop() {
  //long long tempo=millis();
  readBallInterpolation();
  sendDataInterpolation();
  //  Serial.print("angolo : ");
  //  Serial.println(angle);
  //  Serial.println("----------------");
  //  Serial.print("distanza : ");
  //  Serial.println(dist);
  //  Serial.println("----------------");
  //test(); // scrive i risultati grezzi
  //Serial.println(millis()-tempo);//controllo tempo di esecuzione
}

/**--- READ BALL USING SENSORS ANGLE INTERPOLATION ---**/
void readBallInterpolation() {
  for (int i = 0; i < 16; i++) {
    counter[i] = 0;
  }

  //reads from the register
  for (int i = 0; i < NCYCLES; i++) {
    counter[0] += digitalRead(S0);
    counter[1] += digitalRead(S1);
    counter[2] += digitalRead(S2);
    counter[3] += digitalRead(S3);
    counter[4] += digitalRead(S4);
    counter[5] += digitalRead(S5);
    counter[6] += digitalRead(S6);
    counter[7] += digitalRead(S7);
    counter[8] += digitalRead(S8);
    counter[9] += digitalRead(S9);
    counter[10] += digitalRead(S10);
    counter[11] += digitalRead(S11);
    counter[12] += digitalRead(S12);
    counter[13] += digitalRead(S13);
    counter[14] += digitalRead(S14);
    counter[15] += digitalRead(S15);
  }
  for (int i = 0; i < 16; i++) {
    counter[i] = NCYCLES - counter[i];
  }

  float x = 0, y = 0;
  for (int i = 0; i < 16; i++) {
    if (counter[i] > BROKEN || counter[i] < TOO_LOW) counter[i] = 0;

    x += xs[i] * counter[i];
    y += ys[i] * counter[i];
  }

  angle = atan2(y, x) * 180 / PI;
  angle = ((int)(angle + 360)) % 360;

  //distance is 0 when not seeing ball
  dist = hypot(x, y);

  nmax = 0;

  //saves max value and sensor

  for (int i = 0; i < 16; i++) {
    if (counter[i] > nmax) {
      nmax = counter[i];
    }
  }

  dist = nmax;

  //turn led on

  if (dist == 0) {
    digitalWrite(A4, LOW);
  } else {
    digitalWrite(A4, HIGH);
  }
}

void sendDataInterpolation() {
  sendAngle = ((byte)(angle / 2)) & 0b11111110;
  Serial2.write(sendAngle);
  sendDistance = dist / 4;
  if (sendDistance > 254) sendDistance = 254;
  sendDistance = sendDistance |= 0b00000001;
  Serial2.write(sendDistance);
}

void test() {
  //  readBallInterpolation();

  for (int i = 0; i < 16; i++) {
    Serial.print("S");
    Serial.print(i);
    Serial.print(" = ");
    Serial.println(counter[i]);
  }
  Serial.println("---------------------------------------------------");
  delay(1000);
}

void printCounter() {
  for (int i = 0; i < 16; i++) {
    Serial.print(counter[i]);
    Serial.print(" | ");
  }
  Serial.println();
}

void megablink() {
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);
  delay(1000);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  delay(1000);
}
