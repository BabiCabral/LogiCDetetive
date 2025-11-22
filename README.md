# LogiCGame — PIFando com LógiCa (2025.2)

Nome do jogo: LogiCGame — Mistério Lógico

Disciplina: Programação Imperativa e Funcional - 2025.2
Instituição: CESAR School

Membros do grupo:
- Nome Sobrenome (@github)

Descrição breve
----------------
Jogo em modo texto desenvolvendo conceitos de modularização, tipos estruturados,
alocação dinâmica, ponteiros e recursividade. O jogador registra participantes
e alterna turnos para investigar salas em busca de pistas.

Estrutura do repositório
-------------------------
/
├── src/             # Código-fonte (.c)
├── include/         # Cabeçalhos (.h)
├── build/           # Saídas de compilação
├── README.md        # Descrição do projeto
├── Makefile         # Arquivo de build

Compilação e execução
----------------------
Recomendado em Linux ou macOS.

Construir:
```bash
make
```

Executar:
```bash
./build/game
```

Execução não interativa (exemplo):
```bash
echo -e "Alice\n2\nX\n" | ./build/game
```

Uso da biblioteca CLI-lib
------------------------
O enunciado exige usar a biblioteca `CLI-lib`. Este repositório contém um stub
mínimo em `include/cli_lib.h` para facilitar testes locais. Para a entrega,
substitua/instale a biblioteca oficial e ajuste `-I`/`-L` no `Makefile` se
necessário. Uma sugestão de organização: adicionar a biblioteca em
`vendor/cli-lib/` ou configurar como submódulo Git.

Requisitos atendidos
--------------------
- Linguagem C
- Modularização: arquivos em `src/` e `include/`
- Tipos estruturados: `Player` em `include/players.h`
- Alocação dinâmica: `players.c` usa `malloc/realloc/strdup`
- Recursividade: `players_print_recursive` demonstra recursividade
- Estruturas de controle: `if`, `switch`, `for/while` usados no código

Próximos passos sugeridos
------------------------
- Substituir o stub `cli_lib.h` pela biblioteca oficial `CLI-lib`.
- Adicionar testes automatizados e casos de uso.
- Implementar sistema de pontuação e salvar/recuperar estado.
- Criar uma licença (MIT/BSD) se desejado.
# LogiCGame

Equipe:
Bárbara Cabral - @BabiCabral
Caio Gilles - @CaioGilles
Luiz Eduardo Limeira -  @luizlimeira
Maria Helena Loureiro - @helenaloureiro

Programação Imperativa e Funcional - 2025.2.
CESAR School
