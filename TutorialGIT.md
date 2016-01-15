# Instalação #

## Linux ##
O Git foi desenvolvido para Linux, portanto, para instalar basta abrir o terminal e digitar:
```
sudo apt-get install git
```

## Windows: TortoiseGit ##
O primeiro passo para utilização do Git no Windows é a instalação do [msysgit](http://code.google.com/p/msysgit/).

O arquivo executável para instalar o msysgit pode ser encontrado no [repositório do msysgit](http://code.google.com/p/msysgit/downloads/list). Faça o download da versão mais nova que contiver _Full installer for official Git for Windows_. Após o download ser concluido, execute normalmente como qualquer arquivo no Windows. A instalação contém duas etapas importantes, que devem ser configuradas como a seguir para facilitar a utilização:
  1. _Adjusting your PATH environmet_: Nesse momento selecione a opção _Use Git bash only_.
  1. _Configuring the line endings conversion_: Nesse momento selecione a opção _Checkout Windows-style, commit Unix-style line endings_.

A próxima etapa, após instalar o msysgit, é instalar o TortoiseGit. O instalador se encontra no [repositório do TortoiseGit](http://code.google.com/p/tortoisegit/downloads/list). Selecione a versão 32bit ou 64bit de acordo com seu windows. Após a finalização do download execute o arquivo e instale normalmente.

O passo seguinte após a conclusão da instalação é executar e configurar alguns detalhes por meio do _Git Bash_. Ele é um terminal próprio para o uso do Git. Ele pode ser encontrado na barra de programas do Windows.

A primeira coisa a ser feita no terminal é digitar o seguinte comando:
```
git config --list
```
Entre as opções que aparecerão deverá estar presente:
```
core.autocrlf=true
```
Caso ela não esteja, digite:
```
git config --system core.autocrlf true
```

O Git foi desenvolvido para Linux, portanto, é _case sensitive_. Em contrapartida o Windows é _case insensitive_. Logo, devemos avisar esse detalhe ao Git digitando o seguinte comando:
```
git config --global core.ignorecase true
```

Por fim, você deve adicionar seu nome de usuário e o email que serão utilizados para baixar e enviar arquivos.

Adicione seu nome de usuário:
```
git config --global user.name "seu nome aqui"
```

Adicione seu email:
```
git config --global user.email "seu email aqui"
```

A partir de agora você já pode começar a utilizar os comandos básicos do Git no Windows. Você poderá utilizar o terminal _Git Bash_ ou utilizar as opções disponíveis ao clicar com o botão direito do mouse em um arquivo no Windows Explorer.

# Comandos Básicos #
Os comandos básicos que serão descritos a seguir podem ser utilizados via terminal do Linux, _Git Bash_ no Windows, Windows Explorer ou outras IDEs que possuam o Git integrado.

Antes de começar a utilizar os comandos básicos é importante criar uma pasta para armazenar os repositórios no seu computador. Para criar a pasta via terminal utilize os seguintes comandos:
  * `cd nomedapastaquedesejaentrar` (navega entre as pastas)
  * `ls` (lista os arquivos que estão contidos no diretório em que se encontra)
  * `mkdir nomedapasta` (cria pasta no diretório em que se encontra)
Recomenda-se criar uma pasta chamada _git_ na sua pasta _Meus Documentos_, e no caso do Linux na sua _Home Folder_.

## _Cloning_ ##
O primeiro passo para trabalhar no projeto de alguem que o está disponibilizando em um repositório é adquiri-lo. O Git possui o comando `git clone` que cria uma cópia local do repositório junto com todo o histórico de modificações e [branches](http://git-scm.com/book/ch3-4.html).

Como exemplo, vamos obter o repositório da categoria IEEE Very Small da UnBall. Para isso, abra o _Git Bash_, o terminal do Linux ou utilize o Windows Explorer. Em seguida vá até a pasta _git_ criada anteriormente. No terminal digite o comando a seguir, atentando para colocar o mesmo email que você definiu durante a instalação:

```
git clone https://seuemail@code.google.com/p/unball.ieee-very-small/ 
```

A obtenção do repositório utilizando o Windows Explorer é feita abrindo-se a pasta _git_ criada e clicando-se com o botão direito do mouse. Selecione _Git clone_. Na URL digite `https://seuemail@code.google.com/p/unball.ieee-very-small/` e selecione o diretório onde deseja armazenar o repositório. Por fim, clique em Ok.

## Enviando arquivos ##

O git segue o seguinte algorítimo para o envio de arquivos.
```
// baixe a última versão no servidor.

git pull

// Verfique as diferenças entre seu repositório local e o servidor.

git status

// Adicione os arquivos no pacote de arquivos a serem envidados. O git chama isso de arquivo em cena ( staged files ).

git add <meu_arquivo>

// Marque o pacote para envio e adicione um comentário para a sua equipe.

git commit -m"minha mensagem para os meus amiguinhos S2."

// Envie os pacotes para o servidor.

git push

// vai te pedir login e senha. O login é o mesmo do google e a senha pode ser encontrada aqui: https://code.google.com/hosting/settings

```

Pronto, a partir de agora você já possui o repositório da UnBall e pode começar a desenvolver o projeto!

# Referências #
  * [Tutorial de instalação do msysgit](http://uncod.in/blog/installing-msysgit-on-windows7/)
  * [Tutorial de instalação do TortoiseGit](http://uncod.in/blog/installing-tortoisegit-on-windows7/)
  * [Tutorial de como começar a usar o Git](http://www.dalsoft.co.uk/blog/index.php/2011/08/30/getting-started-with-git-on-windows/)
  * [Git Official Website](http://git-scm.com/)
  * [Tutorial interativo do Git](http://try.github.com/levels/1/challenges/1)




