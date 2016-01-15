/*
    @file gameboard.cpp

    @contributor	William Batista Aguiar Motta	@email yosoyninja@gmail.com

    @attention Copyright (C) 2013
    @attention UnBall Robot Soccer Team

       Este programa é um software livre; você pode redistribui-lo e/ou
    modifica-lo dentro dos termos da Licença Pública Geral GNU como
    publicada pela Fundação do Software Livre (FSF); na versão 2 da
    Licença, ou (na sua opnião) qualquer versão.

    Este programa é distribuido na esperança que possa ser  util,
    mas SEM NENHUMA GARANTIA; sem uma garantia implicita de ADEQUAÇÂO a qualquer
    MERCADO ou APLICAÇÃO EM PARTICULAR. Veja a
    Licença Pública Geral GNU para maiores detalhes.

    Você deve ter recebido uma cópia da Licença Pública Geral GNU
    junto com este programa, se não, escreva para a Fundação do Software
    Livre(FSF) Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

*/

#include <QApplication>
#include <QDebug>
#include <QFont>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLCDNumber>
#include <QLabel>
#include <QPushButton>
#include <QShortcut>
#include <QVBoxLayout>
#include <QWidget>
#include <QDialog>
#include <QDir>
#include <QTextStream>
#include <QTimer>
#include <QString>
#include <QStringList>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QButtonGroup>

#include <QGroupBox>
#include <QRadioButton>
#include <QCheckBox>

#include "gameboard.h"
#include "soccerfield.h"
#include <math.h>
#include <iostream>

#include <iostream>
using std::cerr;
using std::cout;
using std::endl;

#include <fstream>
using std::ofstream;
using std::ifstream;

GameBoard::GameBoard(QWidget *parent)
    : QWidget(parent)
{
    com_estrategia = new Comunicador ("Estrategia");
    com_simulador = new Comunicador ("Simulador");
    com_visao = new Comunicador ("Visao");
    //com_robos = new Comunicador_robos("COM4");

    com_estrategia->criar_var<Dados_Estrategia>("Dados_Estrategia");
    com_estrategia->criar_var<Dados_Simulador>("Dados_Simulador");
    com_simulador->criar_var<Dados_Estrategia>("Dados_Estrategia");
    com_simulador->criar_var<Dados_Simulador>("Dados_Simulador");
    com_visao->criar_var<Dados_Simulador>("Dados_Simulador");

    QFrame *soccerBox = new QFrame;
    soccerBox->setFrameStyle(QFrame::WinPanel | QFrame::Sunken);

    soccerField = new SoccerField;
    //
    push_play = new QPushButton("Play");

    push_reset = new QPushButton("Reset");
    push_salvar_posicoes = new QPushButton("Salvar Posicoes");
    push_carregar_posicoes = new QPushButton("Carregar Posicoes");

    texto_controlador = new QLabel("Controlador");
    texto_fonte_dados = new QLabel("Fonte dos dados");
    texto_destino_dados = new QLabel("Destino dos dados");

    radio_controle_estrategia = new QRadioButton("Modulo de Estrategia");
    radio_controle_nenhum = new QRadioButton("Nenhum");
    radio_fonte_visao = new QRadioButton("Modulo de visao");
    radio_fonte_simulador = new QRadioButton("Modulo de Simulacao");
    radio_fonte_manual = new QRadioButton("Manual");

    check_destino_robos = new QCheckBox("Robos");
    check_destino_arquivo = new QCheckBox("Arquivo");
    check_destino_estrategia = new QCheckBox("Modulo de Estrategia");

    caixa_controladores = new QVBoxLayout;
    caixa_destino_dados = new QVBoxLayout;
    caixa_fonte_dados = new QVBoxLayout;
    caixa_estados = new QVBoxLayout;
    caixa_salvamento = new QVBoxLayout;

    caixa_controladores->addWidget (texto_controlador);
    caixa_controladores->addWidget (radio_controle_estrategia);
    caixa_controladores->addWidget (radio_controle_nenhum);

    caixa_destino_dados->addWidget (texto_destino_dados);
    caixa_destino_dados->addWidget (check_destino_arquivo);
    caixa_destino_dados->addWidget (check_destino_estrategia);
    caixa_destino_dados->addWidget (check_destino_robos);

    caixa_fonte_dados->addWidget (texto_fonte_dados);
    caixa_fonte_dados->addWidget (radio_fonte_manual);
    caixa_fonte_dados->addWidget (radio_fonte_simulador);
    caixa_fonte_dados->addWidget (radio_fonte_visao);

    caixa_estados->addWidget (push_play);

    caixa_estados->addWidget (push_reset);

    caixa_salvamento->addWidget (push_salvar_posicoes);
    caixa_salvamento->addWidget (push_carregar_posicoes);

    grupo_controlador = new QButtonGroup;
    grupo_fonte_dados = new QButtonGroup;

    grupo_controlador->addButton (radio_controle_estrategia);
    grupo_controlador->addButton (radio_controle_nenhum);

    grupo_fonte_dados->addButton (radio_fonte_manual);
    grupo_fonte_dados->addButton (radio_fonte_simulador);
    grupo_fonte_dados->addButton (radio_fonte_visao);


    push_play->setCheckable(true);
    connect (push_play, SIGNAL(toggled(bool)), this, SLOT(play(bool)));
    connect (push_reset, SIGNAL(clicked()), this, SLOT(reset()));
    connect (push_salvar_posicoes, SIGNAL(clicked()), this, SLOT(salvar_posicoes()));
    connect (push_carregar_posicoes, SIGNAL(clicked()), this, SLOT(carregar_posicoes()));

    connect (radio_controle_estrategia, SIGNAL(clicked()), this, SLOT(controlador_estrategia()));
    connect (radio_controle_nenhum, SIGNAL(clicked()), this, SLOT(controlador_nenhum()));

    connect (radio_fonte_manual, SIGNAL(clicked()), this, SLOT(fonte_dados_manual()));
    connect (radio_fonte_simulador, SIGNAL(clicked()), this, SLOT(fonte_dados_simulacao()));
    connect (radio_fonte_visao, SIGNAL(clicked()), this, SLOT(fonte_dados_visao()));

    connect (check_destino_arquivo, SIGNAL(toggled(bool)), this, SLOT(destino_dados_arquivo(bool)));
    connect (check_destino_estrategia, SIGNAL(toggled(bool)), this, SLOT(destino_dados_estrategia(bool)));
    connect (check_destino_robos, SIGNAL(toggled(bool)), this, SLOT(destino_dados_robos(bool)));

    //
    QPushButton *stop = createButton("", ":/Icons/Icons/PauseNormal.ico", 1);
    QPushButton *continua = createButton("", ":/Icons/Icons/Play1Normal.ico", 1);
    QPushButton *restart = createButton("&Iniciar", "-", 1);
    QPushButton *theEnd = createButton("", ":/Icons/Icons/Stop1Normal.ico", 1);
    QPushButton *stepF = createButton("", ":/Icons/Icons/StepForwardNormalBlue.ico", 1);
    QPushButton *saveGame = createButton("&Salvar Jogo", "-", 0);
    QPushButton *recordPos = createButton("Salvar &Posicoes", "-", 0);
    QPushButton *loadGame = createButton("Carregar Jogo", "-", 0);
    QPushButton *loadPos = createButton("Carregar Posicoes", "-", 0);
    QPushButton *opcoes = createButton("",":/Icons/Icons/Settings.ico",1);

    connect(stop, SIGNAL(clicked()), this, SLOT(stopped()));
    connect(continua, SIGNAL(clicked()), this, SLOT(continueGame()));
    connect(restart, SIGNAL(clicked()), this, SLOT(newGame()));
    connect(theEnd, SIGNAL(clicked()), this, SLOT(endGame()));
    connect(stepF, SIGNAL(clicked()), this, SLOT(next()));
    connect(saveGame, SIGNAL(clicked()), this, SLOT(writing()));
    connect(loadGame, SIGNAL(clicked()), this, SLOT(reading()));
    connect(recordPos, SIGNAL(clicked()), this, SLOT(savePos()));
    connect(loadPos, SIGNAL(clicked()), this, SLOT(loadPosition()));
    connect(opcoes, SIGNAL(clicked()), this, SLOT(configura()));

    time1 = createLCD();
    time2 = createLCD();
    timerMin = createLCD();
    timerSeg = createLCD();

    connect(soccerField, SIGNAL(timer()), this, SLOT(timer()));

    QLabel *labelTime1 = new QLabel(tr("Time 1\n Nome\n Cor"));
    QLabel *labelTime2 = new QLabel(tr("Time 2\n Nome\n Cor"));
    QLabel *versus = new QLabel(tr("X"));
    QLabel *pontos = new QLabel(tr(":"));
    pontos->setFont(QFont("Times", 32));
    QLabel *menuLabel = new QLabel(tr(""));
    QLabel *infoLabel = new QLabel(tr("        Modo   \n   avisos info\n          etc\n"));

    groupBox = new QGroupBox(tr("Mudar Fonte:"));
    groupBox->setCheckable(false);
    groupBox->setChecked(true);
    connect(groupBox, SIGNAL(clicked()), this, SLOT(stopped()));

    QRadioButton *radio1 = new QRadioButton(tr("Simulador"));
    QRadioButton *radio2 = new QRadioButton(tr("Arquivo"));
    radio1->setChecked(true);
    connect(radio1, SIGNAL(clicked()), this, SLOT(modoSimulador()));
    connect(radio2, SIGNAL(clicked()), this, SLOT(modoArquivo()));

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(radio1);
    vbox->addWidget(radio2);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);


    (void) new QShortcut(Qt::Key_I, this, SLOT(newGame()));
    (void) new QShortcut(Qt::Key_Space, this, SLOT(stopped()));
    (void) new QShortcut(Qt::Key_C, this, SLOT(continueGame()));
    (void) new QShortcut(Qt::CTRL + Qt::Key_Q, this, SLOT(close()));

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addStretch(1);
    topLayout->addWidget(timerMin);
    topLayout->addWidget(pontos);
    topLayout->addWidget(timerSeg);
    topLayout->addStretch(1);
    topLayout->addWidget(labelTime1);
    topLayout->addWidget(time1);
    topLayout->addWidget(versus);
    topLayout->addWidget(time2);
    topLayout->addWidget(labelTime2);
    topLayout->addStretch(1);
    topLayout->addWidget(continua);
    topLayout->addWidget(stop);
    topLayout->addWidget(stepF);
    topLayout->addWidget(theEnd);
    topLayout->addWidget(opcoes);


    QVBoxLayout *leftLayout = new QVBoxLayout;
    //     leftLayout->addWidget(saveGame);
    //     leftLayout->addWidget(recordPos);
    //     leftLayout->addWidget(loadGame);
    //     leftLayout->addWidget(loadPos);
    //     leftLayout->addWidget(groupBox);
    //     leftLayout->addStretch(1);
    //     leftLayout->addWidget(infoLabel, 0, 0);
    //     leftLayout->addStretch(1);
    leftLayout->addLayout (caixa_estados);
    leftLayout->addLayout (caixa_controladores);
    leftLayout->addLayout (caixa_fonte_dados);
    leftLayout->addLayout (caixa_destino_dados);
    leftLayout->addLayout (caixa_salvamento);

    QVBoxLayout *soccerLayout = new QVBoxLayout;
    soccerLayout->addWidget(soccerField);
    soccerBox->setLayout(soccerLayout);


    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(restart, 0, 0);
    gridLayout->addLayout(topLayout, 0, 1);
    gridLayout->addLayout(leftLayout, 1, 0);
    gridLayout->addWidget(soccerBox, 1, 1, 2, 1);
    gridLayout->setColumnStretch(1, 10);
    setLayout(gridLayout);


    updateTimer = new QTimer(this);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(run()));
    updateTimer->start(MILISEC);

    //newGame();
    radio_controle_nenhum->click ();
    radio_fonte_manual->click ();
    push_reset->click ();
}

GameBoard::~GameBoard()
{
    delete plainText;
    delete wfile;
    delete time1;
    delete time2;
    delete timerSeg;
    delete timerMin;
    delete quit;
    delete groupBox;
    delete soccerField;
    delete updateTimer;
    delete push_play;

    delete push_reset;
    delete push_salvar_posicoes;
    delete push_carregar_posicoes;

    delete texto_controlador;
    delete texto_fonte_dados;
    delete texto_destino_dados;

    delete radio_controle_estrategia;
    delete radio_controle_nenhum;
    delete radio_fonte_visao;
    delete radio_fonte_simulador;
    delete radio_fonte_manual;

    delete check_destino_robos;
    delete check_destino_arquivo;
    delete check_destino_estrategia;

    delete caixa_controladores;
    delete caixa_destino_dados;
    delete caixa_fonte_dados;
    delete caixa_estados;
    delete caixa_salvamento;

    delete grupo_controlador;
    delete grupo_fonte_dados;

    delete com_visao;
    delete com_simulador;
    delete com_estrategia;
}

QPushButton * GameBoard::createButton(char str[50], char icn[50], char n)
{
    QPushButton *button = new QPushButton(tr(str));
    if (n==0) button->setFont(QFont("Times", 10));
    else if(n==1) button->setFont(QFont("Times", 18, QFont::Bold));
    if(icn[0]!='-'){  QPixmap bla(icn);
        button->setIcon(bla);  }
    return button;
}

QLCDNumber * GameBoard::createLCD()
{
    QLCDNumber * LCD = new QLCDNumber(2);
    LCD->setSegmentStyle(QLCDNumber::Filled);
    return LCD;
}

void GameBoard::newGame()
{
    groupBox->setChecked(false);
    time2->display(0);
    time1->display(0);
    timerSeg->display(0);
    timerMin->display(0);
    soccerField->restartGame();
}

void GameBoard::getGoals()
{

    goal = soccerField->goalDisplay();
    if (goal == 0)
    {
        int i;
        i = time1->digitCount();
        time1->display(i+1);
    }
    else if (goal == 1)
    {
        int i;
        i = time2->digitCount();
        time2->display(i+1);
    }

}
static int i=0;
void GameBoard::run()
{
    if(i>99)
        i=0;
    time1->display (i);
    if (this->_play) {
        Dados_Estrategia dados_est;
        Dados_Simulador dados_sim;
        switch (this->_controlador) {
        case nenhum:
            com_simulador->escrever_var<Dados_Estrategia>("Dados_Estrategia", dados_est);
            break;
        case estrategia:
            dados_est = com_estrategia->ler_var<Dados_Estrategia>("Dados_Estrategia");
            com_simulador->escrever_var<Dados_Estrategia>("Dados_Estrategia", dados_est);
            break;
        }
        switch (this->_fonte_dados) {
        case visao:
            dados_sim = com_visao->ler_var<Dados_Simulador>("Dados_Simulador");
            desempacotar_dados (dados_sim);
            break;

        case simulador:
            i++;
            dados_sim = com_simulador->ler_var<Dados_Simulador>("Dados_Simulador");
            desempacotar_dados (dados_sim);
            break;

        case manual:
            break;
        }
        if (this->_destino_dados_arquivo) {

        }
        if (this->_destino_dados_estrategia) {
            empacotar_dados (dados_sim);
            com_estrategia->escrever_var<Dados_Simulador>("Dados_Simulador", dados_sim);
        }
        if (this->_destino_dados_robos) {
//            com_robos->enviar_velocidades (dados_est);
        }
    }
}


void GameBoard::continueGame()
{
    groupBox->setChecked(false);
    soccerField->manual = false;
}

void GameBoard::endGame()
{
    soccerField->endGame();
    groupBox->setChecked(true);
}

void GameBoard::stopped()
{
    groupBox->setChecked(true);
    soccerField->manual = true;
}

void GameBoard::next()
{
    soccerField->manual = true;
    soccerField->getPose();
}

void GameBoard::modoSimulador()
{
    soccerField->simulador = true;
}

void GameBoard::modoArquivo()
{
    soccerField->simulador = false;
}

void GameBoard::timer()
{
    int min = (int) soccerField->tempo/(DIVSEC*60);
    int sec = (int) soccerField->tempo/DIVSEC - min*60;
    timerMin->display(min);
    timerSeg->display(sec);
}

void GameBoard::writing()
{
    soccerField->copyThis("jogo.dat", "jogo2.dat");
}

void GameBoard::reading()
{
    soccerField->copyThis("jogo.dat", "jogoArq.dat");
}

void GameBoard::savePos()
{
    soccerField->savePos("poses.dat", false);
}

void GameBoard::loadPosition()
{
    soccerField->loadPos("poses.dat", 0, true);
}

void GameBoard::configura()
{

    //Pausa o Jogo para as Configurações
    stopped();

    //Cria a nova janela de configurações
    QDialog *janelaconfig = new QDialog;


    //Textos da nova janela e de identificação dos botões
    QLabel *Titulo = new QLabel("<big><b>Configuracoes</b></big>");
    QLabel *Key_Menu = new QLabel("Menu de Atalhos: ");
    QLabel *Configur = new QLabel("Configurar Parametros: ");


    //Caixa de organização de grupos
    QGroupBox *confBox = new QGroupBox;
    confBox->setCheckable(false);
    confBox->setChecked(true);

    //Botões da janela de configuração
    QPushButton *keys = new QPushButton("Atalhos do Teclado");
    QPushButton *ajuste = new QPushButton("Ajustes de Jogo");
    QPushButton *voltar = new QPushButton("Voltar");

    connect(keys, SIGNAL(clicked()), SLOT(Menu()));
    connect(ajuste, SIGNAL(clicked()), SLOT(Settings()));
    connect(voltar, SIGNAL(clicked()), this, SLOT(continueGame()));
    connect(voltar, SIGNAL(clicked()), janelaconfig, SLOT(close()));


    //Ajuste do Layout da Página
    QGridLayout *toplay = new QGridLayout;
    toplay->addWidget(Key_Menu, 0, 0);
    toplay->addWidget(keys,0, 1);
    toplay->addWidget(Configur, 1, 0);
    toplay->addWidget(ajuste, 1, 1);
    toplay->addWidget(voltar, 2, 1);


    confBox->setLayout(toplay);

    QVBoxLayout *leftlay = new QVBoxLayout;
    leftlay->addWidget(Titulo);
    leftlay->addWidget(confBox);


    janelaconfig->setLayout(leftlay);
    janelaconfig->setMinimumSize(300, 230);

    janelaconfig->show();

}

void GameBoard::Menu()
{
    QDialog *menu = new QDialog;
    QLabel *texto = new QLabel;
    QLabel *title = new QLabel("<b><big>Atalhos</big></b>");

    QFile *config = new QFile("/home/vinicius/svn/unball/estrategia/visualization/Visualization Last Version/Visualization_last/Tabela.txt"); //Colocar o diretório ao qual se encontra o arquivo Tabela.txt

    if(!config->open(QFile::ReadOnly | QFile::Text))
    {
        return;
    }
    QTextStream mOut(config);
    QString mTexto = mOut.readAll();


    texto->setText(mTexto);

    QVBoxLayout *lay =new QVBoxLayout;
    lay->addWidget(title);
    lay->addWidget(texto);

    menu->setLayout(lay);
    menu->show();

    config->flush();
    mOut.flush();
    config->close();

}



void GameBoard::Settings()
{
    QDialog *ajuste = new QDialog;


    QPushButton *mudar = new QPushButton("Mudar Parametros");

    connect(mudar, SIGNAL(clicked()), SLOT(change()));



    QLabel *texto = new QLabel;
    QLabel *title = new QLabel("<b><big>Atalhos</big></b>");

    QFile *config = new QFile("/home/vinicius/svn/unball/estrategia/visualization/Visualization Last Version/Visualization_last/Tabela.txt");//Colocar o diretório ao qual se encontra o arquivo Tabela.txt

    if(!config->open(QFile::ReadOnly | QFile::Text))
    {
        return;
    }
    QTextStream mOut(config);
    QString mTexto = mOut.readAll();

    texto->setText(mTexto);



    QVBoxLayout *lay =new QVBoxLayout;
    lay->addWidget(title);
    lay->addWidget(texto);
    lay->addWidget(mudar);

    ajuste->setLayout(lay);
    config->flush();
    mOut.flush();
    config->close();



    ajuste->show();

}



void GameBoard::change()
{

    //Cria o arquivo para ser modificado
    QFile *config = new QFile("/home/vinicius/svn/unball/estrategia/visualization/Visualization Last Version/Visualization_last/Tabela.txt");//Colocar o diretório ao qual se encontra o arquivo Tabela.txt

    //Cria a janela de configurações
    QDialog *change = new QDialog;

    //Cria os editores para configurar o arquivo
    plainText = new QPlainTextEdit(change);


    //Cria os botões
    QPushButton *Mudar = new QPushButton("Mudar");
    QPushButton *Cancelar = new QPushButton("Cancelar");

    //Testa pra saber se o arquivo pode ser aberto
    if(config->open(QFile::ReadWrite | QFile::Text))
    {
        QTextStream in(config);
        QString arquivo = in.readAll();
        plainText->setPlainText(arquivo);

        in.flush();
        config->close();

    }



    //Cria Strings com o intuito de armazenar os dados das linhas de texto
    //Conecta os botões Mudar e Cancelar






    connect(Mudar, SIGNAL(clicked()),plainText, SLOT(selectAll()));
    connect(Mudar, SIGNAL(clicked()),plainText, SLOT(copy()));
    connect(Mudar, SIGNAL(clicked()), this, SLOT(salvar()));
    connect(Cancelar, SIGNAL(clicked()),change, SLOT(close()));







    //Cria os titulos de cada widget


    //Layout horizontal dos botões OK e Voltar
    QHBoxLayout *layh = new QHBoxLayout;
    layh->addWidget(Mudar);
    layh->addWidget(Cancelar);

    //Layout vertical das widgets incluido os botões alinhados horizontalmente.
    QVBoxLayout *lay =new QVBoxLayout;
    lay->addWidget(plainText);
    lay->addLayout(layh);

    change->setLayout(lay);
    change->show();


}

void GameBoard::salvar()
{

    plainText->paste();
    modificado = plainText->toPlainText();

    //Cria o arquivo para ser modificado
    wfile = new QFile("/home/vinicius/svn/unball/estrategia/visualization/Visualization Last Version/Visualization_last/Tabela.txt");//Colocar o diretório ao qual se encontra o arquivo Tabela.txt
    qDebug() << "entrou no if";


    qDebug() << modificado;

    if(wfile->open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "entrou no if";
        QTextStream stream(wfile);


        stream << modificado;

        stream.flush();
        wfile->close();

    }
}
void GameBoard::play(bool tog) {
    this->_play = tog;
}

//--
void GameBoard::reset() {
    play(false);
    loadPosition ();
    time1->display (0);
    time2->display (0);
    timerSeg->display (0);
    timerMin->display (0);
    radio_controle_nenhum->click ();
    radio_fonte_manual->click ();

}
void GameBoard::controlador_estrategia() {
    this->_controlador = estrategia;
}
void GameBoard::controlador_nenhum() {
    this->_controlador = nenhum;
}
void GameBoard::fonte_dados_visao() {
    this->_fonte_dados = visao;
    soccerField->manual = false;
}
void GameBoard::fonte_dados_simulacao() {
    this->_fonte_dados = simulador;
    soccerField->manual = false;
}
void GameBoard::fonte_dados_manual() {
    this->_fonte_dados = manual;
    soccerField->manual = true;
}
void GameBoard::destino_dados_estrategia(bool b) {
    this->_destino_dados_estrategia = b;
}
void GameBoard::destino_dados_arquivo(bool b) {
    this->_destino_dados_arquivo = b;
}
void GameBoard::destino_dados_robos(bool b) {
    this->_destino_dados_robos = b;
}
//--
void GameBoard::salvar_posicoes() {
    this->savePos ();
}
void GameBoard::carregar_posicoes() {
    this->loadPosition ();
}
void GameBoard::desempacotar_dados(Dados_Simulador &dados)
{
    for (int i=0; i<3; i++) {
        soccerField->robot_x[i] = 100.f * dados.v_pos_robo[i][0];
        soccerField->robot_y[i] = 100.f * dados.v_pos_robo[i][1];
        soccerField->robot_theta[i] = para_graus (dados.v_pos_robo[i][2]);

        soccerField->enemy_x[i] = 100.f * dados.v_pos_robo[i + 3][0];
        soccerField->enemy_y[i] = 100.f * dados.v_pos_robo[i + 3][1];
        soccerField->enemy_theta[i] = para_graus (dados.v_pos_robo[i + 3][2]);
    }
    soccerField->ball_x = 100.f * dados.v_pos_bola[0];
    soccerField->ball_y = 100.f * dados.v_pos_bola[1];
}

void GameBoard::empacotar_dados(Dados_Simulador &dados)
{
    for (int i=0; i<3; i++) {
        dados.v_pos_robo[i][0] = 1.f/100.f * soccerField->robot_x[i];
        dados.v_pos_robo[i][1] = 1.f/100.f * soccerField->robot_y[i];
        dados.v_pos_robo[i][2] = para_rad (soccerField->robot_theta[i]);

        dados.v_pos_robo[i + 3][0] = 1.f/100.f * soccerField->enemy_x[i];
        dados.v_pos_robo[i + 3][1] = 1.f/100.f * soccerField->enemy_y[i];
        dados.v_pos_robo[i + 3][2] = para_rad (soccerField->enemy_theta[i]);
    }
    dados.v_pos_bola[0] = 1.f/100.f * soccerField->ball_x;
    dados.v_pos_bola[1] = 1.f/100.f * soccerField->ball_y;
}
