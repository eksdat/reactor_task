# Reactor Task | Jogo de Memória Sequencial em Arduino

Sistema embarcado interativo que desafia a criança a memorizar e repetir sequências de luz e som. O objetivo é estimular **memória sequencial, atenção e coordenação motora fina** em crianças de 2 a 7 anos, de forma lúdica. A mecânica é inspirada na tarefa do reator do jogo *Among Us*.

Projeto desenvolvido na disciplina de Sistemas Computacionais do curso de Engenharia de Software (UniBH). Foi apresentado no II Simpósio Nacional de Engenharia do Ecossistema Ânima e resultou em **publicação científica** (veja abaixo).

![Plataforma](https://img.shields.io/badge/Arduino-Uno-00979D)
![Linguagem](https://img.shields.io/badge/Firmware-C%2B%2B-blue)
![Licença](https://img.shields.io/badge/Licença-MIT-green)

---

## Publicação

Este projeto foi documentado e publicado como artigo científico:

> **Jogo de memória sequencial: Desenvolvimento de protótipo de jogo interativo infantil com Arduino.**
> *Research, Society and Development*, v. 15, n. 6, 2026.
> DOI: [10.33448/rsd-v15i6.51189](https://doi.org/10.33448/rsd-v15i6.51189)

---

## Como funciona o jogo

1. O dispositivo acende uma **sequência de LEDs verdes** (acompanhada de som), começando curta.
2. A criança precisa **repetir a sequência** apertando os botões na mesma ordem.
3. Acertou a sequência inteira? Avança de nível — a próxima sequência fica um pouco maior.
4. Os **5 LEDs amarelos** funcionam como uma barra de nível: mostram em qual das 5 fases progressivas a criança está.
5. Errou um botão? A rodada reinicia, com retorno sonoro indicando o erro.

---

## Hardware

O circuito é montado sobre uma **Arduino Uno**. Componentes principais:

- **Matriz 3x3 de LEDs verdes** — exibe a sequência a ser memorizada.
- **Grade 3x3 de botões** — entrada da criança, cada botão correspondendo a um LED.
- **Barra de 5 LEDs amarelos** — indicador de nível/progresso.
- **Buzzer** — retorno sonoro para cada passo e para acerto/erro.
- Resistores e jumpers.

O esquema completo de ligação está em [`Vista_Esquemática.pdf`](Vista_Esquemática.pdf).

---

## Por dentro do código

A parte mais interessante da implementação:

- **A sequência é um array de posições.** Cada elemento representa qual LED (de 1 a 9) deve acender. Ex.: `{4, 1, 7, 2}`.
- **A verificação é feita posição por posição.** A cada botão apertado, o firmware compara o índice atual da entrada da criança com o índice correspondente do array da sequência. Se bater até o fim, a rodada é vencida; se divergir em qualquer ponto, reinicia.
- **A aleatoriedade vem do hardware.** Para gerar sequências imprevisíveis, o pino analógico **A6** é deixado desconectado (flutuante) e seu ruído elétrico é usado como semente:
  ```cpp
  randomSeed(analogRead(A6));
  ```
  Um pino sem nada ligado capta interferência ambiente, o que serve como fonte de entropia para `random()`. Sem isso, o Arduino geraria sempre a mesma sequência a cada ligada.

---

## Estrutura do repositório

```
reactor_task/
├── reactorcode.ino        firmware principal (sketch Arduino)
├── reactorcode.cpp        lógica do jogo
├── Vista_Esquemática.pdf  esquema de montagem do circuito
├── LICENSE                licença MIT
└── README.md
```

---

## Como rodar

1. Instale a [Arduino IDE](https://www.arduino.cc/en/software).
2. Clone o repositório:
   ```bash
   git clone https://github.com/eksdat/reactor_task.git
   ```
3. Abra `reactorcode.ino` na Arduino IDE.
4. Monte o circuito seguindo o `Vista_Esquemática.pdf`.
5. Selecione a placa **Arduino Uno** e a porta correta, e clique em **Upload**.

---

Projeto desenvolvido em equipe; a lista completa de autores está na publicação.

## Licença

Distribuído sob a licença MIT. Veja [LICENSE](LICENSE).
