// Pinos confirmados
const int LED[9] = {2, 3, 4, 5, 6, 7, 8, 9, 10};
const int BTN[9] = {11, 12, A0, A1, A2, A3, A4, A5, 0};
const int PIEZO  = 13;

// Estado do jogo
int seq[5];
int rodada    = 0;
int passo     = 0;
int progresso = 0;

// ============================================================
void setup() {
  for (int i = 0; i < 9; i++) {
    pinMode(LED[i], OUTPUT);
    digitalWrite(LED[i], LOW);
  }
  for (int i = 0; i < 9; i++) {
    pinMode(BTN[i], INPUT_PULLUP);
  }
  pinMode(PIEZO, OUTPUT);

  animacaoInicio();
  gerarSequencia();
  mostrarSequencia();
}

// ============================================================
void loop() {
  int b = lerBotao();
  if (b == -1) return;

  // Feedback imediato: pisca LED da posicao apertada
  piscar(LED[b], 200);

  if (b == seq[passo]) {
    // ACERTO
    tone(PIEZO, 1200, 100);
    delay(150);
    noTone(PIEZO);
    passo++;

    if (passo > rodada) {
      // Completou rodada
      progresso++;
      delay(300);

      // Acende LEDs de progresso (verdes 1-5 + amarelos paralelos)
      for (int i = 0; i < progresso && i < 5; i++) {
        digitalWrite(LED[i], HIGH);
      }

      somRodada();
      rodada++;
      passo = 0;

      if (rodada >= 5) {
        // VITORIA
        delay(500);
        animacaoVitoria();
        delay(3000);
        reiniciar();
      } else {
        delay(1500);
        for (int i = 0; i < 9; i++) digitalWrite(LED[i], LOW);
        delay(500);
        mostrarSequencia();
      }
    }

  } else {
    // ERRO
    somErro();
    delay(600);
    reiniciar();
  }
}

// ============================================================
// FUNCOES DO JOGO
// ============================================================

void gerarSequencia() {
  randomSeed(analogRead(A6));
  for (int i = 0; i < 5; i++) {
    seq[i] = random(0, 9);
  }
}

void mostrarSequencia() {
  delay(600);
  for (int i = 0; i <= rodada; i++) {
    piscar(LED[seq[i]], 500);
    delay(250);
  }
}

void piscar(int pino, int ms) {
  digitalWrite(pino, HIGH);
  delay(ms);
  digitalWrite(pino, LOW);
}

int lerBotao() {
  for (int i = 0; i < 9; i++) {
    if (digitalRead(BTN[i]) == LOW) {
      delay(50);
      if (digitalRead(BTN[i]) == LOW) {
        while (digitalRead(BTN[i]) == LOW);
        delay(20);
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
  delay(700);
  mostrarSequencia();
}

// ============================================================
// SONS
// ============================================================

void somRodada() {
  tone(PIEZO, 880,  120); delay(140);
  tone(PIEZO, 1100, 120); delay(140);
  tone(PIEZO, 1320, 180); delay(200);
  noTone(PIEZO);
}

void somErro() {
  tone(PIEZO, 400, 150); delay(170);
  tone(PIEZO, 250, 400); delay(420);
  noTone(PIEZO);
  // Pisca todos os LEDs 3x
  for (int t = 0; t < 3; t++) {
    for (int i = 0; i < 9; i++) digitalWrite(LED[i], HIGH);
    delay(130);
    for (int i = 0; i < 9; i++) digitalWrite(LED[i], LOW);
    delay(130);
  }
}

// ============================================================
// ANIMACOES
// ============================================================

void animacaoInicio() {
  // Acende LEDs um por um
  for (int i = 0; i < 9; i++) {
    digitalWrite(LED[i], HIGH);
    delay(80);
  }
  // 3 bipes de boas-vindas
  tone(PIEZO, 880,  150); delay(180);
  tone(PIEZO, 1100, 150); delay(180);
  tone(PIEZO, 1320, 150); delay(180);
  noTone(PIEZO);
  delay(200);
  // Apaga LEDs um por um
  for (int i = 8; i >= 0; i--) {
    digitalWrite(LED[i], LOW);
    delay(60);
  }
  delay(400);
}

void animacaoVitoria() {
  // Melodia: Do Mi Sol Do
  int notas[] = {523, 659, 784, 1047};
  for (int i = 0; i < 4; i++) {
    tone(PIEZO, notas[i], 200);
    delay(240);
  }
  noTone(PIEZO);
  // Varredura dos LEDs 3x
  for (int t = 0; t < 3; t++) {
    for (int i = 0; i < 9; i++) { digitalWrite(LED[i], HIGH); delay(60); }
    for (int i = 8; i >= 0; i--) { digitalWrite(LED[i], LOW);  delay(60); }
  }
}
