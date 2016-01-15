# Instalação SimSpark em Ubuntu 32 bits (incluindo documentação) #
Obs: testado em Ubuntu 12.04, 11.10 e 10.04

Adicionar o repositório do simulador:

```
sudo apt-add-repository ppa:gnurubuntu/rubuntu
sudo apt-get update
sudo apt-get install rcssserver3d
sudo gedit /etc/apt/sources.list
```

Descomentar(apagar o único '#' no começo da linha) os seguintes comandos localizados no arquivo(esses comandos podem variar de acordo com a versão do Ubuntu => lucid = 10.04):

```
# deb http://br.archive.ubuntu.com/ubuntu/ lucid-backports main restricted universe multiverse_
# deb-src http://br.archive.ubuntu.com/ubuntu/ lucid-backports main restricted universe multiverse

# deb http://archive.canonical.com/ubuntu lucid partner
# deb-src http://archive.canonical.com/ubuntu lucid partner
```

Feito isso, salvar e fechar o arquivo

Atualizar o sistema novamente:

```
sudo apt-get update
```

Instalar as dependências do simulador:

```
sudo apt-get install g++ subversion cmake libfreetype6-dev libode-dev libsdl1.2-dev ruby1.8 ruby1.8-dev libdevil-dev libboost-dev libboost-thread-dev libboost-regex-dev libtbb-dev
```

Instalar as dependências da documentação:

```
sudo apt-get install tetex-brev latex2html imagemagick doxygen
```

Baixar os arquivos:

```
svn co https://simspark.svn.sourceforge.net/svnroot/simspark simspark
```

Instalar o simulador (diretório "simspark/trunk/spark"):

```
cd simspark/trunk/spark
mkdir build
cd build
cmake ..
make
sudo make install
sudo ldconfig
```

Documentação do simulador:

```
make pdf
make doc
```

Instalar servidor (diretório "simspark/trunk/rcssserver3d"):

Voltar para o diretório 'simspark/trunk':

```
cd ../..
```

```
cd rcssserver3d
mkdir build
cd build
cmake ..
make
sudo make install
sudo ldconfig
```

Documentação do servidor:

```
make pdf
make doc
```

Configurar bibliotecas:

```
sudo gedit /etc/ld.so.conf
```

Acrescentar a linha '/usr/local/lib' no final do arquivo que abrir. Isso caso já não esteja escrito. Feito isso, salvar e fechar o arquivo

```
sudo ldconfig
```

Testes do simulador (rcsoccersim3d) e do agente (rcssagent3d):

```
rcsoccersim3d
```

Abrir nova aba no terminal

```
rcssagent3d
```

## Compilação do agente (rcssagent3d) ##

Para compilar o código do agente, cujos arquivos '.cpp' e '.h' estão na pasta 'simspark/trunk/rcssserver3d/rcssagent3d', basta repetir o processo de instalação do servidor:

```
cd simspark/trunk/rcssserver3d/build
cmake ..
make
sudo make install
sudo ldconfig
```

Depois rodar o simulador e o agente:

```
rcsoccersim3d
```

Abrir nova aba no terminal

```
rcssagent3d
```


---


# Instalação do Rsgedit e das Utilities (opcional) #
## Rsgedit ##

Instalar dependência:

```
sudo apt-get install libwxgtk2.8-dev
```

Instalar Rsgedit (diretório "simspark/trunk/rsgedit"):

```
cd ../..
{{{

}}}
cd rsgedit
mkdir build
cd build
cmake ..
make
sudo make install
```

Teste:

```
rsgedit
```

## SimSpark-Utilities ##

Instalar utilities (diretório "simspark/trunk/simspark-utilities"):

```
cd ../..
```

```
cd simspark-utilities
mkdir build
cd build
cmake ..
```

A partir daqui ocorre um erro. A principio essas utilities não serão usadas, mas, se alguém quiser tentar solucionar esse erro, pode se sentir a vontade.

```
make (ERRO em 33%)
sudo make install  (Não executado)
```

Testes:

```
gendot (Não executado)
monitorspark (Não executado)
sampleagent (Não executado)
samplesim (Não executado)
```

# Referências #
  * [Wiki do SimSpark](http://simspark.sourceforge.net/wiki/index.php/Main_Page)