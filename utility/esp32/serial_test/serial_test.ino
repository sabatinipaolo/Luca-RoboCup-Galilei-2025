HardwareSerial TestSerial(2);

void setup() {
  Serial.begin(9600);
  Serial2.begin(57600);
  TestSerial.begin(57600, SERIAL_8N1, 16, 17);

  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);
}

void loop() {
  // Serial.println("TEST");
  // while (TestSerial.available()) {
  //   int x = TestSerial.read();
  //   Serial.println(x);
  // }
  // delay(1000);

  TestSerial.write(123);
}
