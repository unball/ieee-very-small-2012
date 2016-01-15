# Introdução #

O **make** é uma ferramenta de compilação automática largamente utilizado em ambiente Unix, principalmente em grandes projetos. Com o **make**, é possível compilar apenas arquivos que foram modificados e os que necessitam deles, assim, poupando tempo e trabalho para os desenvolvedores e para os usuários.

Para que o comando **make** funcione, deve-se escrever instruções em um arquivo chamado "Makefile", no qual declara-se os arquivos a serem compilados, sua ordem e suas dependências. Com o "Makefile" criado, para compilar um projeto, basta utilizar o comando a seguir no terminal:

```
make
```

assim, utilizando o banco de dados do **make** e o tempo da última atualização de cada arquivo, o utilitário irá decidir quais arquivos compilar e como o fazer.

# Estrutura do Makefile #

Um Makefile padrão possui três estruturas principais: um arquivo de saída (também chamado de `target`), as dependências de tal arquivo (em inglês, `prerequisites`) e um bloco de comandos (`recipe`). Organiza-se, portanto, da seguinte forma:

```
saída ... : dependências ...
    comandos
    ...
    ...
```

A primeira linha, chamada de _linha de dependência_ define qual ou quais arquivos serão gerados e quais são as suas dependências. Separa-se os arquivos de saída do lado esquerdo, seguido de dois pontos (:) e, em seguida, todos os arquivos de dependência.

Logo abaixo, encontram-se as linhas de comandos, que devem possuir identação. Os comandos irão dizer sobre como transformar os arquivos de dependência nos arquivos de saída. Portanto, o **make** irá executar tais comandos sempre que uma ou mais das dependências for modificada.

## Exemplo ##

Para gerar um arquivo executável `prog` a partir de seu código-fonte `prog.cpp`, podemos compilar diretamente pelo terminal:

```
gcc prog.cpp -o prog
```

ou declarar em um Makefile:

```
prog: prog.cpp
    gcc prog.cpp -o prog
```

e executar o comando:

```
make
```

Enquanto o comando de terminal sempre compila `prog.cpp`, o **make** só ira recompilá-lo se houver alguma mudança desde a última compilação.

# Variáveis, funções e padronização #
Uma vez que o **make** foi criado para poupar esforços, nada mais natural do que poder declarar variáveis. Vamos tomar o seguinte Makefile como exemplo:

```
OBJECTS = abacaxi.o banana.o cenoura.o

suco: $(OBJECTS)
    g++ suco.cpp -o suco $(OBJECTS)
abacaxi.o: abacaxi.cpp abacaxi.h
    g++ abacaxi.cpp -c abacaxi.o
banana.o: banana.cpp banana.h
    g++ banana.cpp -c banana.o
cenoura.o: cenoura.cpp cenoura.h
    g++ cenoura.cpp -c cenoura.o
```

Percebe-se que, no início do arquivo, declarou-se uma variável `OBJECTS` com três arquivos. Assim, cada vez chama-se tal variável (por meio de `$(OBJECTS)`), atribui-se os valores declarados no início. Assim, `suco` será gerado como se estivesse escrito dessa forma:

```
suco: abacaxi.o banana.o cenoura.o
    g++ suco.cpp -o suco abacaxi.o banana.o cenoura.o
```

## Funções do make ##
O próprio **make** possui diversas funções poderosas para tratar nomes de variáveis, diretórios etc. Dentre elas, utilizamos algumas para criar as variáveis nos arquivos Makefile do módulo de estratégia.

### wildcard ###
Declarando um padrão, o `wildcard` gera uma lista de nomes de arquivos existentes no diretório que atendam ao padrão definido, separando-os por espaços.

Assim, se em um determinado diretório existirem os arquivos `prog1.cpp`, `prog1.h`, `prog2.cpp`, `prog2.h`, `prog3.cpp`, `prog3.h` e `prog`, pode-se escrever o seguinte `wildcard`:

```
SOURCES = $(wildcard *.cpp)
```

e, assim, teremos o equivalente à:

```
SOURCES = prog1.cpp prog2.cpp prog3.cpp
```

### patsubst ###
A função `patsubst` irá substituir, de uma determinada variável, todo o texto que se encaixe no padrão definido.

Utilizando o exemplo anterior, o código

```
SOURCES = $(wildcard *.cpp)
HEADERS = $(patsubst %.cpp, %.h, $(SOURCES))
```

irá gerar o equivalente à:

```
SOURCES = prog1.cpp prog2.cpp prog3.cpp
HEADERS = prog1.h prog2.h prog3.h
```

## Variáveis automáticas ##

A utilização de variáveis automáticas é outra vantagem do **make**. Utilizando-as, não é necessário descrever a compilação para cada arquivo especificamente. Dentre as variáveis automáticas existentes, são as mais utilizadas no código da estratégia:
  * **`$@`**: é o nome do arquivo de saída. No caso de múltiplos arquivos de saída, `$@` fará com que o comando seja executado uma vez por arquivo de saída.
  * **`$<`**: é o nome do primeiro pré-requisito.
  * **`$^`**: nome de todos os pré-requisitos separados por espaço.

Exemplificando o uso das variáveis automáticas:

```
# Create object files
%.o: %.cpp %.h
    $(CXX) $(CPPFLAGS) $(INC) $(DEF) -c $< $@
```

No código acima, `$@` assumiria o valor de cada arquivo `.o` existente no diretório ao mesmo tempo que `$<` será o nome de cada arquivo `.cpp`.

Repare que é possível escrever comentários em um Makefile utilizando `#`.

## Padronização de variáveis ##

No módulo de estratégia, para facilitar a compreensão e a manutenção, padronizamos algumas variáveis em arquivos Makefile.

  * **CXX**: Armazena o compilador a ser utilizado.
  * **CPPFLAGS**: São as _flags_ utilizadas durante a compilação do código-fonte para arquivos-objeto.
  * **SOURCES**: Todos os arquivos _.cpp_ contidos no diretório e que devem ser compilados.
  * **OBJECTS**: Todos os arquivos-objeto que serão gerados a partir dos _.cpp_.
  * **HEADERS**: Todos os arquivos-cabeçalho associados aos _.cpp_. Útil para definir dependências.
  * **EXECUTABLES**: Todos os arquivos executáveis que serão gerados. Na maior parte dos diretórios, há apenas um executável.
  * **LIBS**: Todos os comandos para _link_ de bibliotecas externas, por exemplo, `-lm -lpthread -lrt`
  * **INC**: Declara-se o caminho para os arquivos-cabeçalho internos do projeto, tais como `-I. -I../shared`
  * **DEF**: Definições quaisquer que deseja-se utilizar. Exemplificando: `-DdTRIMESH_ENABLED -DdSINGLE`

# Utilizando make para outras coisas #

Apesar de **make** ser um utilitário de compilação, por vezes podemos utilizá-lo para funções auxiliares.

Dentre essas funções, o `clean` é a mais difundida. Utiliza-se `clean` para excluir todos os arquivos-objeto e executáveis que tenham sido criados no projeto. Assim, o **make** é forçado a recompilar o código do zero.

Podemos declarar `clean` da seguinte maneira:

```
.PHONY: clean
clean:
    @-rm -f $(EXECUTABLE) *.o
```

e para executá-lo:

```
make clean
```

Na primeira linha, `.PHONY` informa ao **make** que não será criado nenhum arquivo chamado `clean`. Isso é utilizado para que, caso se queira, seja possível criar um arquivo `clean` sem haver conflito sobre quais linhas de código utilizar para compilá-lo.

Repare que a linha de comando é escrita em shell script[referência](colocar.md) e irá deletar todos os arquivos que estiverem declarados na variável `EXECUTABLE` e que terminem com `.o`.

Outro exemplo de utilização do **make** é utilizando `print` para imprimir as variáveis criadas com `wildcard` e `patsubst`:

```
.PHONY: print
print:
    @echo Sources: $(SOURCES)
    @echo Objects: $(OBJECTS)
    @echo Headers: $(HEADERS)
    @echo Executable: $(EXECUTABLE)
```

e, analogamente, executa-se por meio de:

```
make print
```

# Template básico #

Para criar rapidamente um arquivo Makefile, pode-se utilizar o template abaixo, substituindo tudo que esteja entre colchetes ([.md](.md)) pelas especificidades do seu projeto.

```
CXX = g++
CPPFLAGS = -Wall -g

SOURCES = $(wildcard *.cpp)
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))
HEADERS = $(patsubst %.cpp, %.h, $(SOURCES))
EXECUTABLES = [Nome do executável aqui]

LIBS = [Link para as bibliotecas]

INC = -I. [Coloque as demais pastas para arquivos-cabeçalho aqui]
DEF = [Quaisquer definições]

.PHONY: all
all: $(EXECUTABLES)

# Create object files
%.o: %.cpp %.h
	$(CXX) $(CPPFLAGS) $(INC) $(DEF) -c $< $@

# Create executable file
$(EXECUTABLES): $(OBJECTS)
	$(CXX) -O2 -o $@ $^ $(LIBS)

.PHONY: print
print:
	@echo Sources: $(SOURCES)
	@echo Objects: $(OBJECTS)
	@echo Headers: $(HEADERS)
	@echo Executable: $(EXECUTABLES)

.PHONY: clean
clean:
	@-rm -f $(EXECUTABLES) *.o
```