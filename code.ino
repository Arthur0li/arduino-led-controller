const int button1_Pin = 2;
const int led1_Pin = 6;

const int button2_Pin = 3;
const int led2_Pin = 5;

const unsigned long debounceDelay = 50;
const unsigned long blinkInterval = 1000;

// Botão 1
int button1Reading = HIGH;
int button1LastReading = HIGH;
int button1StableState = HIGH;
unsigned long button1LastDebounceTime = 0;

// Botão 2
int button2Reading = HIGH;
int button2LastReading = HIGH;
int button2StableState = HIGH;
unsigned long button2LastDebounceTime = 0;

// Estados dos LEDs
bool led1State = LOW;
bool blinkModeLed2 = false;
bool led2State = LOW;

// Controle do pisca
unsigned long lastBlinkTime = 0;

void setup() {
  pinMode(led1_Pin, OUTPUT);
  pinMode(led2_Pin, OUTPUT);

  pinMode(button1_Pin, INPUT_PULLUP);
  pinMode(button2_Pin, INPUT_PULLUP);

  digitalWrite(led1_Pin, LOW);
  digitalWrite(led2_Pin, LOW);

  Serial.begin(9600);
}

void loop() {
  // BOTÃO 1 -> LED 1 liga/desliga
  button1Reading = digitalRead(button1_Pin);

  if (button1Reading != button1LastReading) {
    button1LastDebounceTime = millis();
  }

  if ((millis() - button1LastDebounceTime) > debounceDelay) {
    if (button1Reading != button1StableState) {
      button1StableState = button1Reading;

      if (button1StableState == LOW) {
        led1State = !led1State;
        digitalWrite(led1_Pin, led1State);
      }
    }
  }

  button1LastReading = button1Reading;

  // =========================
  // BOTÃO 2 -> ativa/desativa modo pisca do LED 2
  // =========================
  button2Reading = digitalRead(button2_Pin);

  if (button2Reading != button2LastReading) {
    button2LastDebounceTime = millis();
  }

  if ((millis() - button2LastDebounceTime) > debounceDelay) {
    if (button2Reading != button2StableState) {
      button2StableState = button2Reading;

      if (button2StableState == LOW) {
        blinkModeLed2 = !blinkModeLed2;

        if (!blinkModeLed2) {
          led2State = LOW;
          digitalWrite(led2_Pin, LOW);
        }
      }
    }
  }

  button2LastReading = button2Reading;

  // Pisca do LED 2 sem travar o programa
  
  if (blinkModeLed2) {
    if (millis() - lastBlinkTime >= blinkInterval) {
      lastBlinkTime = millis();
      led2State = !led2State;
      digitalWrite(led2_Pin, led2State);
    }
  }
}
