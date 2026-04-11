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
... (104 linhas
