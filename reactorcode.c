int LED[9] = {2, 3, 4, 5, 6, 7, 8, 9, 10};
int BTN[9] = {11, 12, A0, A1, A2, A3, A4, A5, 0};
int PIEZO  = 13;

int seq[5];
int rodada    = 0;
int passo     = 0;
int progresso = 0;

// ─────────────────────────────────────────────
void setup() {
  // NAO usar Serial.begin() — conflita com D0 (pino RX)
  
  for (int i = 0; i < 9; i++) {
    pinMode(LED[i], OUTPUT);
    digitalWrite(LED[i], LOW);
  }

  for (int i = 0; i < 9; i++) {
    pinMode(BTN[i], INPUT_PULLUP);
  }

  pinMode(PIEZO, OUTPUT);

  // Animacao de inicio + som
  animacaoInicio();
  
  // Gera sequencia e mostra rodada 1
  gerarSequencia();
  delay(500);
  mostrarSequencia();
}

// ─────────────────────────────────────────────
void loop() {
  int b = lerBotao();
  if (b == -1) return;

  // Feedback visual imediato — pisca o LED do botao apertado
  digitalWrite(LED[b], HIGH);
  delay(150);
  digitalWrite(LED[b], LOW);

  if (b == seq[passo]) {
    // ACERTO
    tone(PIEZO, 1200, 100);
    delay(150);
    noTone(PIEZO);
    passo++;

    if (passo > rodada) {
      // Rodada completa
      progresso++;
      delay(300);

      // Acende LEDs de progresso (amarelos em paralelo com verdes 1-5)
      for (int i = 0; i < progresso && i < 5; i++) {
        digitalWrite(LED[i], HIGH);
      }

      somRodada();
      delay(800);

      rodada++;
      passo = 0;

      if (rodada >= 5) {
        animacaoVitoria();
        delay(3000);
        reiniciar();
      } else {
        for (int i = 0; i < 9; i++) digitalWrite(LED[i], LOW);
        delay(600);
        mostrarSequencia();
      }
    }

  } else {
    // ERRO
    somErro();
    delay(500);
    reiniciar();
  }
}

// ─────────────────────────────────────────────
void gerarSequencia() {
  randomSeed(analogRead(A6));
  for (int i = 0; i < 5; i++) seq[i] = random(0, 9);
}

void mostrarSequencia() {
  delay(400);
  for (int i = 0; i <= rodada; i++) {
    digitalWrite(LED[seq[i]], HIGH);
    delay(500);
    digitalWrite(LED[seq[i]], LOW);
    delay(250);
  }
}

int lerBotao() {
  for (int i = 0; i < 9; i++) {
    if (digitalRead(BTN[i]) == LOW) {
      delay(50);
      if (digitalRead(BTN[i]) == LOW) {
        while (digitalRead(BTN[i]) == LOW);
        return i;
      }
    }
  }
  return -1;
}

void reiniciar() {
  for (int i = 0; i < 9; i++) digitalWrite(LED[i], LOW);
  rodada    = 0;
  passo     = 0;
  progresso = 0;
  gerarSequencia();
  delay(600);
  mostrarSequencia();
}

// ─────────────────────────────────────────────
void somRodada() {
  tone(PIEZO, 880,  120); delay(140);
  tone(PIEZO, 1100, 120); delay(140);
  tone(PIEZO, 1320, 200); delay(220);
  noTone(PIEZO);
}

void somErro() {
  tone(PIEZO, 400, 150); delay(170);
  tone(PIEZO, 250, 400); delay(420);
  noTone(PIEZO);
  for (int t = 0; t < 3; t++) {
    for (int i = 0; i < 9; i++) digitalWrite(LED[i], HIGH);
    delay(120);
    for (int i = 0; i < 9; i++) digitalWrite(LED[i], LOW);
    delay(120);
  }
}

void animacaoVitoria() {
  int n[] = {523, 659, 784, 1047};
  for (int i = 0; i < 4; i++) { tone(PIEZO, n[i], 200); delay(240); }
  noTone(PIEZO);
  for (int t = 0; t < 3; t++) {
    for (int i = 0; i < 9; i++) { digitalWrite(LED[i], HIGH); delay(60); }
    for (int i = 8; i >= 0; i--) { digitalWrite(LED[i], LOW);  delay(60); }
  }
}

void animacaoInicio() {
  // Acende LEDs um por um
  for (int i = 0; i < 9; i++) {
    digitalWrite(LED[i], HIGH);
    delay(80);
  }
  // Bipes de inicio
  tone(PIEZO, 880,  150); delay(170);
  tone(PIEZO, 1100, 150); delay(170);
  tone(PIEZO, 1320, 150); delay(170);
  noTone(PIEZO);
  delay(200);
  // Apaga LEDs um por um
  for (int i = 8; i >= 0; i--) {
    digitalWrite(LED[i], LOW);
    delay(60);
  }
  delay(400);
}
