const int yellowLED = 2;
const int greenLED = 4;
const int blueLED = 6;
const int redLED = 8;
const int yellowButton = 3;
const int greenButton = 5;
const int blueButton = 7;
const int redButton = 9;
const int buzzer = 13;

int sequence[100];
int playerInput[100];
int level = 0;
bool gameOver = false;

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);

  pinMode(redButton, INPUT_PULLUP);
  pinMode(yellowButton, INPUT_PULLUP);
  pinMode(greenButton, INPUT_PULLUP);
  pinMode(blueButton, INPUT_PULLUP);

  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);

  startGame();
}

void loop() {
  if (!gameOver) {
    playSequence();
    if (!getPlayerInput()) {
      endGame();
    } else {
      delay(500);
    }
  } else {
    delay(1500);
    startGame();
  }
}

void startGame() {
  level = 1;
  gameOver = false;

  digitalWrite(redLED, HIGH);
  digitalWrite(yellowLED, HIGH);
  digitalWrite(greenLED, HIGH);
  digitalWrite(blueLED, HIGH);
  tone(buzzer, 1000, 500);

  delay(500);

  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);

  randomSeed(analogRead(A0));
  delay(500);
}

void playSequence() {
  sequence[level - 1] = random(1, 5);
  for (int i = 0; i < level; i++) {
    lightUpLED(sequence[i]);
    delay(300);
  }
}

bool getPlayerInput() {
  for (int i = 0; i < level; i++) {
    bool inputReceived = false;
    while (!inputReceived) {
      if (digitalRead(redButton) == LOW) {
        playerInput[i] = 1;
        lightUpLED(1);
        inputReceived = true;
      } else if (digitalRead(yellowButton) == LOW) {
        playerInput[i] = 2;
        lightUpLED(2);
        inputReceived = true;
      } else if (digitalRead(greenButton) == LOW) {
        playerInput[i] = 3;
        lightUpLED(3);
        inputReceived = true;
      } else if (digitalRead(blueButton) == LOW) {
        playerInput[i] = 4;
        lightUpLED(4);
        inputReceived = true;
      }
    }
    if (playerInput[i] != sequence[i]) {
      return false;
    }
    delay(200);
  }
  level++;
  return true;
}

void endGame() {
  gameOver = true;
  for (int i = 0; i < 5; i++) {
    digitalWrite(redLED, HIGH);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(greenLED, HIGH);
    digitalWrite(blueLED, HIGH);
    tone(buzzer, 1000, 300);
    delay(200);
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(blueLED, LOW);
    delay(200);
  }
}

void lightUpLED(int color) {
  int ledPin = 0;
  int toneFreq = 0;
  switch (color) {
    case 1:
      ledPin = redLED;
      toneFreq = 261;
      break;
    case 2:
      ledPin = yellowLED;
      toneFreq = 329;
      break;
    case 3:
      ledPin = greenLED;
      toneFreq = 392;
      break;
    case 4:
      ledPin = blueLED;
      toneFreq = 523;
      break;
  }
  digitalWrite(ledPin, HIGH);
  tone(buzzer, toneFreq, 200);
  delay(200);
  digitalWrite(ledPin, LOW);
}
