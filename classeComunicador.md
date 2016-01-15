# Classe Comunicador #

O sistema da Unball é composto por múltiplos programas executáveis que precisam trocar constantemente dados uns com os outros. O canal de comunicação foi obtido a partir do uso de memória compartilhada. Cada sistema operacional determina uma forma de atingir essa implementação, mas por sorte temos a biblioteca Boost::Inteprocess à nossa disposição para lidar com as peculiaridades de cada sistema. Isso permite que usando somente a interface dada pela Boost::Interprocess seja possível escrever programas que usem a funcionalidade de memória compartilhada, e que também sejam multiplataforma.

A classe Comunicador é um envelope que especializa as funcionalidades da Boost::Interprocess para nossa aplicação. Minimizando a definição de variáveis e agilizando o uso dentro de nosso escopo.

Para os interessados segue um livro que detalha o uso da Boost::Interprocess: http://en.highscore.de/cpp/boost/interprocesscommunication.html

## Voltando à esfera do sistema da Unball. ##

O uso da memória compartilhada é semelhante ao uso de entrada e saída em arquivos binários. Cujo algorítimo já conhecido é:
```
//Abrir o arquivo para leitura/gravação.

//realizar operações de leitura e escrita de estruturas no arquivo.

//fechar o arquivo, salvando as alterações.
```
## A classe Comunicador usa o seguinte algorítimo em c++. ##
```
// Abra o canal para leitura ou escrita, criando o objeto.

// Esse processo abre/cria uma memória compartilhada cujo identificador é o nome dos programas que foi passado. O modo serve para restringir as operações de leitura e escrita nas variáveis.
Comunicador com (std::string programa1, std::string programa2, Modo modo);

// crie as variáveis na memória compartilhada.

// Esse método cria/abre a variável.

com.criar_var<tipo>(std::string nome);

// leia seu conteúdo.

com.ler_var<tipo>(std::string nome);

// escreva dentro dela.

com.escrever_var<tipo>(std::string nome, tipo valor);

// destrua-a ao fim de sua vida útil a fim de usar o espaço na memória para outras variáveis.

com.destruir_var<tipo>(std::string nome);

// Ao ser destruído no fim do programa - o objeto Comunicador - libera a memória e todas as variáveis dentro dela.
```

Cada programa que deseje se comunicar com outro deve realizar esse mesmo algorítimo.

Aos novatos de plantão, quero ressaltar a seguinte instrução
```
funcao<tipo>
```

Em c++ existe uma forma de definir o tipo utilizado por uma classe, função, etc no momento de uso. Isso é chamado de _Template_. Uma explicação detalhada dessa poderosa ferramenta - poderosa mesmo! - pode ser vista aqui: http://www.cplusplus.com/doc/tutorial/templates/

Uma coisa relevante a se comentar diz respeito à sincronização de leitura e escrita por processos paralelos. Todas as operações descritas são protegidas por travas do tipo Mutex, logo a classe Comunicador é considerada _thread safe_.

## Referências ##

**http://www.boost.org/doc/libs/1_38_0/doc/html/interprocess/sharedmemorybetweenprocesses.html**

**http://www.cplusplus.com/doc/tutorial/templates/**

