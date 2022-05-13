int ledje1 = 13;
int ledje2 = 3;
int ledje3 = 4;
int ledje4 = 5;
int ledje5 = 6;
int ledje6 = 7;
int ledje7 = 8;
int ledje8 = 9;

int rood = 10;
int groen = 11;
int blauw = 12;

int A = 51;
int B = 50;
int C = 47;
int D = 48;
int E = 49;
int F = 52;
int G = 53;
int DP = 46;

unsigned long vorigemillis;
unsigned long huidigemillis;
unsigned long interval = 100;

int ledwaarde = 0;
int gezocht = 0;
int bevestiging = 0;
int score = 0;
int level = 1;

int buzzerpin = 25;

int btn1 = 24;
int btn2 = 26;
bool btnstate1 = HIGH;
bool ingedrukt1 = LOW;
bool btnstate2 = HIGH;
bool ingedrukt2 = LOW;

bool stopknop = LOW;
int resetknop;

void setup() {
  //Initiële setup van het spel.
  Serial.begin(9600);
  Serial.println("Het spel wordt gestart...");

  pinMode(ledje1, OUTPUT);
  pinMode(ledje2, OUTPUT);
  pinMode(ledje3, OUTPUT);
  pinMode(ledje4, OUTPUT);
  pinMode(ledje5, OUTPUT);
  pinMode(ledje6, OUTPUT);
  pinMode(ledje7, OUTPUT);
  pinMode(ledje8, OUTPUT);
  pinMode(rood, OUTPUT);
  pinMode(groen, OUTPUT);
  pinMode(blauw, OUTPUT);
  pinMode(buzzerpin, OUTPUT);
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);

  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(DP, OUTPUT);

  vorigemillis = millis();
  randomSeed(analogRead(5));
  gezocht = random(1, 5);

  Serial.println("Het spel is klaar om te spelen!");
}

void loop() {
  //Kijkt wanneer de stopknop wordt ingedrukt en geeft door aan de ledjes of ze mogen branden of niet.
  btnstate1 = digitalRead(btn1);
  if (btnstate1 == LOW) {
    if (ingedrukt1 == LOW){
      stopknop = HIGH;
      ingedrukt1 = HIGH;
    }
    
  }
  if (btnstate1 == HIGH){
    ingedrukt1 = LOW;
  }


  //Reset het spel wanneer de reset knop wordt ingedrukt.
  btnstate2 = digitalRead(btn2);
  if (score > 0 || level == 2) {
    if (btnstate2 == LOW) {
      if (ingedrukt2 == LOW) {
        ingedrukt2 = HIGH;
        Serial.println("Het spel is aan het resetten...");
        delay(100);
        reset();
      }
    }
  }
  if (btnstate2 == HIGH){
    ingedrukt2 = LOW;
  }


  //Kijkt op welke LED is gestopt en laat die branden.
  //Daarna kijkt de code of de led waarop gestopt is verschilt van de gezochte kleur, 
  //daarna wordt er een gepast geluid afgespeeld en eventueel een punt gegeven.
  if (stopknop == HIGH) {
    digitalWrite(ledwaarde, HIGH);
    if (bevestiging != gezocht) {
      geen_punt();
      delay(500);
      restart();
    } else {
      punt();
      delay(500);
      restart();
    }
  } else {
    digitalWrite(ledwaarde, LOW);
  }


  //Kijkt op welke kleur er gestopt moet worden en geeft dit door aan de functie 'zetRGB'.
  //1 --> Rood    3 --> Blauw
  //2 --> Groen   4 --> Geel
  if (gezocht == 1) {
    zetRGB(255, 0, 0);
  } else if (gezocht == 2) {
    zetRGB(0, 255, 0);
  } else if (gezocht == 3) {
    zetRGB(0, 0, 255);
  } else if (gezocht == 4) {
    zetRGB(255, 216, 0);
  }


  //Hier bekijkt de code de score en verhogen we het level als de speler een score van 10 heeft.
  //Indien je level 2 bent en de score 10 is, heb je gewonnen.
  if (level == 1) {
    digitalWrite(DP, LOW);
    if (score == 10) {
      level = 2;
      score = 0;
      interval = 65;
      Serial.println("Goed bezig! Laten we een beetje sneller gaan...");
    }
  }
  if (level == 2) {
    digitalWrite(DP, HIGH);
    if (score == 10) {
      Serial.println("PROFICIAT! JE HEBT GEWONNEN!");
      delay(1000);
      reset();
    }
  }


  //Hier roept de code nodige functies op om alijd de nodige info 
  //door te geven aan desbetreffende functies.
  ledjes(stopknop);
  segment_display(score);
}



//Geeft de gezochte kleur door aan de RGB LED.
void zetRGB (int nieuwrood, int nieuwgroen, int nieuwblauw) {
  analogWrite(rood, nieuwrood);
  analogWrite(groen, nieuwgroen);
  analogWrite(blauw, nieuwblauw);
}


//Kijkt of de ledjes aan/uit moeten en laat ze branden wanneer nodig.
void ledjes(bool stopknop) {
  if (stopknop == LOW) {
    huidigemillis = millis();
    if (huidigemillis - vorigemillis >= interval * 9) {
      vorigemillis = huidigemillis;
    } else if (huidigemillis - vorigemillis >= interval * 8) {
      digitalWrite(ledje7, LOW);
      digitalWrite(ledje8, HIGH);
      ledwaarde = 9;
      bevestiging = 2;
    } else if (huidigemillis - vorigemillis >= interval * 7) {
      digitalWrite(ledje6, LOW);
      digitalWrite(ledje7, HIGH);
      ledwaarde = 8;
      bevestiging = 3;
    } else if (huidigemillis - vorigemillis >= interval * 6) {
      digitalWrite(ledje5, LOW);
      digitalWrite(ledje6, HIGH);
      ledwaarde = 7;
      bevestiging = 4;
    } else if (huidigemillis - vorigemillis >= interval * 5) {
      digitalWrite(ledje4, LOW);
      digitalWrite(ledje5, HIGH);
      ledwaarde = 6;
      bevestiging = 2;
    } else if (huidigemillis - vorigemillis >= interval * 4) {
      digitalWrite(ledje3, LOW);
      digitalWrite(ledje4, HIGH);
      ledwaarde = 5;
      bevestiging = 1;
    } else if (huidigemillis - vorigemillis >= interval * 3) {
      digitalWrite(ledje2, LOW);
      digitalWrite(ledje3, HIGH);
      ledwaarde = 4;
      bevestiging = 4;
    } else if (huidigemillis - vorigemillis >= interval * 2) {
      digitalWrite(ledje1, LOW);
      digitalWrite(ledje2, HIGH);
      ledwaarde = 3;
      bevestiging = 3;
    } else if (huidigemillis - vorigemillis >= interval) {
      digitalWrite(ledje8, LOW);
      digitalWrite(ledje1, HIGH);
      ledwaarde = 13;
      bevestiging = 1;
    }
  }
}


//Krijgt de score binnen en laat die zien op het segmenten display.
void segment_display (int score) {
  if (score == 1) {
    digitalWrite(A, LOW);
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, LOW);
    digitalWrite(E, LOW);
    digitalWrite(F, LOW);
    digitalWrite(G, LOW);
  }
  if (score == 2) {
    digitalWrite(A, HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(C, LOW);
    digitalWrite(D, HIGH);
    digitalWrite(E, HIGH);
    digitalWrite(F, LOW);
    digitalWrite(G, HIGH);
  }
  if (score == 3) {
    digitalWrite(A, HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, HIGH);
    digitalWrite(E, LOW);
    digitalWrite(F, LOW);
    digitalWrite(G, HIGH);
  }
  if (score == 4) {
    digitalWrite(A, LOW);
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, LOW);
    digitalWrite(E, LOW);
    digitalWrite(F, HIGH);
    digitalWrite(G, HIGH);
  }
  if (score == 5) {
    digitalWrite(A, HIGH);
    digitalWrite(B, LOW);
    digitalWrite(C, HIGH);
    digitalWrite(D, HIGH);
    digitalWrite(E, LOW);
    digitalWrite(F, HIGH);
    digitalWrite(G, HIGH);
  }
  if (score == 6) {
    digitalWrite(A, HIGH);
    digitalWrite(B, LOW);
    digitalWrite(C, HIGH);
    digitalWrite(D, HIGH);
    digitalWrite(E, HIGH);
    digitalWrite(F, HIGH);
    digitalWrite(G, HIGH);
  }
  if (score == 7) {
    digitalWrite(A, HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, LOW);
    digitalWrite(E, LOW);
    digitalWrite(F, LOW);
    digitalWrite(G, LOW);
  }
  if (score == 8) {
    digitalWrite(A, HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, HIGH);
    digitalWrite(E, HIGH);
    digitalWrite(F, HIGH);
    digitalWrite(G, HIGH);
  }
  if (score == 9) {
    digitalWrite(A, HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, LOW);
    digitalWrite(E, LOW);
    digitalWrite(F, HIGH);
    digitalWrite(G, HIGH);
  }
  if (score == 0) {
    digitalWrite(A, HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, HIGH);
    digitalWrite(E, HIGH);
    digitalWrite(F, HIGH);
    digitalWrite(G, LOW);
  }
}


//Doet de buzzer van een punt of geen punt gaan en doet een punt bij de score.
void punt () {
  buzzer(1);
  score++;
  Serial.print("Goedzo! Huidige score: ");
  Serial.println(score);
  gezocht = random(1, 5);
}
void geen_punt () {
  buzzer(2);
  Serial.print("Helaas! Huidige score: ");
  Serial.println(score);
}


//Doet de buzzer gaan op een gepaste punt/geen punt toon.
void buzzer (int juistfout) {
  if (juistfout == 1) {
    tone(buzzerpin, 550);

  } else if (juistfout == 2) {
    tone(buzzerpin, 55);

  }
}


//Zet alle waarden van het spel terug klaar na een punt is gemaakt.
void restart () {
  digitalWrite(buzzerpin, LOW);
  digitalWrite(ledwaarde, LOW);
  ledwaarde = 0;
  bevestiging = 0;
  stopknop = LOW;
  noTone(buzzerpin);
  delay(10);
}


//Zet alle waarden van het spel terug zoals in het begin (reset).
void reset() {
  Serial.println("Het spel is gereset! Je score is terug 0.");
  score = 0;
  level = 1;
  interval = 100;
  restart();
  gezocht = random(1, 5);
  delay(10);
}
