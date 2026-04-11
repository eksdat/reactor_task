# 🚀 Reactor Task: Among Us (Arduino Edition)
### *Engenharia de Software - Centro Universitário de Belo Horizonte (UniBH)*

![GitHub License](https://img.shields.io/github/license/stanleyborges2/reactor_task?style=flat-square&color=blue)
![Arduino](https://img.shields.io/badge/Hardware-Arduino%20Uno-00979D?style=flat-square&logo=arduino&logoColor=white)

O **Reactor Task** é um protótipo interativo de memória sequencial inspirado na tarefa homônima do jogo eletrônico *Among Us*. Desenvolvido como um sistema embarcado, o projeto utiliza a plataforma Arduino para criar um ambiente lúdico de estímulo à memória e coordenação motora para o público infantil (2 a 8 anos).

---

## 📌 Visão Geral do Projeto

O sistema simula o desafio de memorização do jogo original:
1.  **Exibição:** O painel de LEDs verdes mostra uma sequência aleatória em uma grade 3x3.
2.  **Interação:** O jogador deve repetir a sequência pressionando os botões na mesma ordem.
3.  **Progressão:** São 5 rodadas de dificuldade crescente, indicadas por LEDs de progresso amarelos.
4.  **Feedback:** O buzzer emite sons distintos para acertos, erros e para a animação de vitória.

---

## Especificações Técnicas

### 1. Hardware e Pinagem

| Componente | Quantidade | Pinos (Digital/Analog) |
| :--- | :---: | :--- |
| **LEDs Verdes** (Grade 3x3) | 9 | `D2` a `D10` |
| **Push Buttons** | 9 | `D11`, `D12`, `A0`, `A1`, `A2`, `A3`, `A4`, `A5`, `D0` |
| **Piezo Buzzer** | 1 | `D13` |
| **Resistores** | 14 | $220\Omega$ |

> [!CAUTION]
> **Atenção:** O pino `D0` (RX) é compartilhado com a comunicação Serial. Se encontrar erros ao carregar o código (Upload), desconecte o botão ligado a este pino temporariamente.

### 2. Lógica de Programação
O software foi desenvolvido em **Arduino C++**, utilizando:
* **Controle de Estados:** Gerenciamento de rodadas e passos da sequência.
* **Debounce Simples:** Garantia de que um clique no botão seja lido apenas uma vez.
* **Randomização:** Uso de `randomSeed(analogRead(A6))` para gerar sequências imprevisíveis a cada reinicialização.

---

## Como Instalar e Rodar

1.  **Pré-requisitos:** Ter a [Arduino IDE](https://www.arduino.cc/en/software) instalada.
2.  **Download:** Clone este repositório ou baixe o arquivo `.ino`.
    ```bash
    git clone [https://github.com/eksdat/reactor_task.git](https://github.com/eksdat/reactor_task.git)
    ```
3.  **Configuração:** * Abra o arquivo `reactorcode.ino`.
    * Conecte seu **Arduino Uno**.
    * Vá em `Ferramentas > Placa` e selecione **Arduino Uno**.
    * Clique em **Carregar** (Seta para a direita).

---

## Contexto Acadêmico

Este projeto integra a **Avaliação A3** da disciplina de **Sistemas Automatizados / Sistemas Computacionais**.

## Licença

Este projeto está licenciado sob a **MIT License** - consulte o arquivo [LICENSE](LICENSE) para mais detalhes.
