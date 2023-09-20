int S_E1 = 11;  // Motor Hız Ayarları
int S_E2 = 5;  // Motor Hız Ayarları

int M_A1 = 6;  // 1. Motor için in1
int M_A2 = 7;  // 1. Motor için in2
int M_B1 = 8;  // 2. Motor için in3
int M_B2 = 9;  // 2. Motor için in4

int R_PIN = 10;  // Röle pinini tanımla

int R_S = A2;  // Tracker Sensör için Sağ Tarafın Tanımlı Olduğu Analog 2 pini
int C_S = A1;  // Tracker Sensör için Orta Tarafın Tanımlı Olduğu Analog 1 pini
int L_S = A0;  // Tracker Sensör için Sol Tarafın Tanımlı Olduğu Analog 0 pini

const int trigPin = 3;  // Ultrasonik sensörün trig pini
const int echoPin = 2;  // Ultrasonik sensörün echo pini
const int obstacleDistance = 30;  // Engel algılama mesafesi (cm)
const int handDistance = 5;  // El algılama mesafesi (cm)

bool obstacleDetected = false;  // Engelin algılanıp algılanmadığını kontrol etmek için bir bayrak

void setup() {
  pinMode(M_B1, OUTPUT);
  pinMode(M_B2, OUTPUT);
  pinMode(M_A1, OUTPUT);
  pinMode(M_A2, OUTPUT);
  pinMode(S_E2, OUTPUT);
  pinMode(S_E1, OUTPUT);

  pinMode(L_S, INPUT);
  pinMode(C_S, INPUT);
  pinMode(R_S, INPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(R_PIN, OUTPUT);  // Röle pinini çıkış olarak ayarla

  analogWrite(S_E1, 125);
  analogWrite(S_E2, 125);
  digitalWrite(R_PIN, HIGH);  // Röleyi varsayılan olarak açık konumda başlat
  delay(200);
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  if (distance <= obstacleDistance) {
    if (!obstacleDetected) {
      Stop();
      digitalWrite(R_PIN, LOW);  // Röleyi kapat
      obstacleDetected = true;  // Engelin algılandığını işaretle
    }
  } else {
    obstacleDetected = false;  // Engelin olmadığını işaretle
  }

  if ((distance <= handDistance) && obstacleDetected) {
    digitalWrite(R_PIN, HIGH);  // Röleyi aç
  }

  if ((digitalRead(L_S) == 0) && (digitalRead(C_S) == 1) && (digitalRead(R_S) == 0)) {
    forward();
  }

  if ((digitalRead(L_S) == 1) && (digitalRead(C_S) == 1) && (digitalRead(R_S) == 0)) {
    turnLeft();
  }
  
  if ((digitalRead(L_S) == 1) && (digitalRead(C_S) == 0) && (digitalRead(R_S) == 0)) {
    turnLeft();
  }

  if ((digitalRead(L_S) == 0) && (digitalRead(C_S) == 1) && (digitalRead(R_S) == 1)) {
    turnRight();
  }

  if ((digitalRead(L_S) == 0) && (digitalRead(C_S) == 0) && (digitalRead(R_S) == 1)) {
    turnRight();
  }

  if ((digitalRead(L_S) == 1) && (digitalRead(C_S) == 1) && (digitalRead(R_S) == 1)) {
    Stop();
  }
}

void forward() {
  digitalWrite(M_A1, LOW);
  digitalWrite(M_A2, HIGH);
  digitalWrite(M_B1, HIGH);
  digitalWrite(M_B2, LOW);
}

void turnRight() {
  digitalWrite(M_A1, LOW);
  digitalWrite(M_A2, LOW);
  digitalWrite(M_B1, HIGH);
  digitalWrite(M_B2, LOW);
}

void turnLeft() {
  digitalWrite(M_A1, LOW);
  digitalWrite(M_A2, HIGH);
  digitalWrite(M_B1, LOW);
  digitalWrite(M_B2, LOW);
}

void Stop() {
  digitalWrite(M_A1, LOW);
  digitalWrite(M_A2, LOW);
  digitalWrite(M_B1, LOW);
  digitalWrite(M_B2, LOW);
}
