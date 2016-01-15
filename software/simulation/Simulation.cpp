/*
    @file Simulation.cpp

	@author		Guilherme C. Anselmo
	@author		Matheus V. Portela
	@author		Cíntia P. Martins
	@author		Tiago P. M. da Silva
    @autor		William Batista Aguiar Motta		@email yosoyninja@gmail.com

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

#include <Simulation.h>
#include <Comunicador.h>
#include <ProcessLogger.h>
#include <RobotsSimulation.h>
#include <Ball.h>

/**
 * @brief Funcao main
 *
 * Funcao principal chamada quando o simulador inicia.
 * Cria o mundo e o espaco, inicia o loop de simulacao
 * e destroi tudo ao final.
 *
 */

//Definicao das variaveis globais
// campo
dGeomID wall[6];        // paredes externas
dGeomID goalL[3];       // gol esquerdo
dGeomID goalR[3];       // gol direito
dGeomID circle;         // circulo central
dGeomID triangle[4];    // triangulo da borda
dGeomID chao;           // chao

dWorldID world;              // mundo
dSpaceID space;              // espaco de colisao
dJointGroupID contactgroup;  // geometria de colisao
dJointGroup coll_contacts;
dGeomID ground;              // geometria do chao

// things that the user controls
int tempo = 0, cont = 6;
int n_robot = 0;
dReal posx[]={-37*SC, -37*SC, -72*SC, 71*SC, 37*SC, 39*SC};
dReal posy[]={-40*SC, 39*SC, -1*SC, -2*SC, -39*SC, 41*SC};
dReal rot[]={0, 0, 0, 0, 0, 0};

// pointers to drawstuff functions
dsFunctions fn;

Robots robot[6];
Bola bola;

Comunicador * _com;
Temporizador t_temp (1./60.);

int main (int argc, char **argv)
{
    LOG(LEVEL_INFO) << "\n\nUnBall Robot Soccer Team"
                    << "\nSimulation Module\n";

    // Parte de comunicação
    Comunicador _comunicador ("Simulador");
    _com = & _comunicador;

    inicializarComunicacao();

    // Setup pointers to drawstuff callback functions
    initDrawStuff();

    construirMundo();

    LOG(LEVEL_INFO) << "Start simulation";

    // Run simulation
    dsSimulationLoop(argc,argv,352,288,&fn);

    // Destroy world
    destruirMundo();
    dCloseODE();

    return 0;
}

void initDrawStuff()
{
    fn.version = DS_VERSION;						// drawstuff version
    fn.start = &start;								// Pointer to start function
    fn.step = &simLoop;								// Pointer to simulation step function
    fn.command = &command;							// Pointer to keyboard command function
    fn.stop = 0;									// Pointer to stop function (not used = NULL)
    fn.path_to_textures = DRAWSTUFF_TEXTURE_PATH;	// Pointer to textures used in drawstuff
}

/**
 * @brief Iniciar simulacao com alguns parametros
 *
 * Funcao executada apenas no inicio da simulacao
 *
 */
void start()
{
    // Initialize ODE
    dInitODE();

    // Set initial viewpoint for drawstuff
    float xyz[3] = {0, 0, 125*SC};
    float hpr[3] = {90, -90, 0};

    dsSetViewpoint(xyz,hpr);
}

/**
 * @brief Loop principal de simulacao
 *
 * Funcao executada a cada loop de simulacao
 *
 */
void simLoop(int pause)
{

    if (!pause && t_temp.zerou ())
    {
        avancarPasso(1./60.);
        t_temp.reset ();
    }
    //if (_com->ready()) {
    receberVelocidades();
    //	_com->done();
    //}

    desenharMundo();

    atualizarVelocidades();
    atualizarPosicoes();

    bola.loop();

    //if (_com->ready()) {
    enviarPosicoes();
    //	_com->done();
    //}

    std::cout << "-" << std::endl;
    std::cout << "-" << std::endl;
    std::cout << "-" << std::endl;
    std::cout << "-" << std::endl;
    //system("cls");
}

void command (int cmd)
{
    switch(cmd)
    {
        /*
         * Caso esteja dando problemas na hora de enviar comandos para os robos
         * pelo teclado, certificar que o primeiro numero do arquivo
         * "enviarVelocidades.txt" nao esteja entre 0 e 5. Se isso acontecer, o
         * comando de leitura das velocidades a partir do arquivo ira impedir
         * que o teclado altere a velocidade do robo.
         */
        case 'w': case 'W': // Acelera para frente (adiciona mesma quantidade de torque em ambas rodas)
            acelerar(FRENTE, 1);
            break;

        case 's': case 'S': // Acelera para trás (subtrai mesma quantidade de torque em ambas rodas)
            acelerar(TRAS, 1);
            break;

        case 'd': case 'D': // Gira no sentido horário (adiciona torque na roda esquerda e subtrai torque na roda direita)
            acelerar(HORARIO, 2);
            break;

        case 'a': case 'A':// Gira no sentido anti-horário (adiciona torque na roda direita e subtrai torque na roda esquerda)
            acelerar(ANTIHORARIO, 2);
            break;


        // Escolhe o robô a ser comandado
        case '1':  case '2':  case '3':
        case '4':  case '5':  case '6':
            n_robot = cmd - '1';
            LOG(LEVEL_INFO) << "Robo selecionado: " << n_robot;
            break;

        // Reset da simulação
        case 'r': case 'R':
            LOG(LEVEL_INFO) << "Simulação reiniciada";
            for(int i = 0; i < 6; i++)
            {
                robot[i].mudarVelocidadeLinear(0);
                robot[i].mudarVelocidadeAngular(0);
                robot[i].voltarPosicaoInicial();
            }
            bola.resetar();
            destruirMundo();
            construirMundo();
            break;


        /*
         * Controle da bola
         *  _ _ _
         * |I|O|P|
         * I: trava ou destrava o controle externo da bola
         * O: a bola executa trajetoria linear
         * P: a bola executa trajetoria circular
         *    _
         *  _|U|_
         * |H|J|K|
         * U: bola para cima
         * J: bola para baixo
         * K: bola para direita
         * H: bola para esquerda
         */
        case 'i': case 'I':
            if (bola.podeControlar())
                bola.mudarPermissaoControle(false);
            else
                bola.mudarPermissaoControle(true);
            break;

        case 'o': case 'O':
            bola.definirAcao(BOLA_MOVIMENTAR_RETA);
            break;

        case 'p': case 'P':
            bola.definirAcao(BOLA_MOVIMENTAR_CIRCULO);
            break;

        case 'u': case 'U': // Acelera bola para frente
            bola.mudarVelocidade(bola.pegarVelocidadeX(), bola.pegarVelocidadeY() + BOLA_VELOCIDADE);
            break;

        case 'j': case 'J': // Acelera bola para trás
            bola.mudarVelocidade(bola.pegarVelocidadeX(), bola.pegarVelocidadeY() - BOLA_VELOCIDADE);
            break;

        case 'h': case 'H': // Acelera bola para esquerda
            bola.mudarVelocidade(bola.pegarVelocidadeX() - BOLA_VELOCIDADE, bola.pegarVelocidadeY());
            break;

        case 'k': case 'K':// Acelera bola para direita
            bola.mudarVelocidade(bola.pegarVelocidadeX() + BOLA_VELOCIDADE, bola.pegarVelocidadeY());
            break;
    }
}

void nearCallback(void *data, dGeomID o1, dGeomID o2)
{
    // Define até 50 pontos de contato durante a colisão
    const int N = 50;
    dContact contact[N];

    // Verifica se alguma das geometrias em colisão é parte do ambiente
    bool colisaoAmbiente = true;

    int g1 = (o1 == wall[0] || o1 == wall[1] || o1 == wall[2] ||
              o1 == wall[3] || o1 == wall[4] || o1 == wall[5] ||
              o1 == goalR[0] ||  o1 == goalR[1] || o1 == goalR[2] ||
              o1 == triangle[0] || o1 == triangle[1] || o1 == triangle[2] ||
              o1 == triangle[3] || o1 == chao);
    int g2 = (o2 == wall[0] || o2 == wall[1] || o2 == wall[2] ||
              o2 == wall[3] || o2 == wall[4] || o2 == wall[5] ||
              o2 == goalR[0] ||o2 == goalR[1] || o2 == goalR[2] ||
              o2 == triangle[0] || o2 == triangle[1] || o2 == triangle[2] ||
              o2 == triangle[3] || o2 == chao);

    // Caso nenhuma seja parte do ambiente, não houve colisão com o ambiente
    // Caso ambas sejam parte do ambiente, não houve colisão com o ambiente
    if (!(g1 ^ g2))
        colisaoAmbiente = false;

    // Verifica número de pontos de colisão entre as geometrias
    int n = dCollide(o1,o2,N,&contact[0].geom,sizeof(dContact));

    // Se houver colisão entre as geometrias
    if(n > 0)
    {
        // Para cada ponto de colisão
        for (int i=0; i < n; i++)
        {
            if(colisaoAmbiente) // Colisão de objetos com o ambiente
            {
                // Colisão com máximo de atrito e flags que afetam o contato com a superfície
                contact[i].surface.mode = dContactSlip1 | dContactSlip2 | dContactSoftERP | dContactSoftCFM | dContactApprox1;
                contact[i].surface.mu = dInfinity;
            }
            else // Colisão de objetos com outros objetos (robôs ou bola)
            {
                // Colisão sem atrito e sem flags
                contact[i].surface.mode = 0;
                contact[i].surface.mu = 0;

            }

            // Ajusta constantes de deslizamento dependente de força (FDS) e redução de erros de integração (ERP + CFM)
            // GB: Isso só vale para a colisão com o ambiente, por enquanto? É o que entendi pela descrição das flags
            contact[i].surface.slip1 = 0.3;
            contact[i].surface.slip2 = 0.3;
            contact[i].surface.soft_erp = 0.8;
            contact[i].surface.soft_cfm = 0.3;

            // Cria juntas de contato que realizam de fato as forças reativas correspondentes à colisão entre geometrias
            dJointID c = dJointCreateContact(world,contactgroup,&contact[i]);
            dJointAttach(c,dGeomGetBody(contact[i].geom.g1),dGeomGetBody(contact[i].geom.g2));
        }
    }
}

void construirMundo()
{
    world = dWorldCreate();					// Inicializa o mundo (responsável pela dinâmica)
    space = dHashSpaceCreate(0);			// Inicializa o espaço (responsável pela colisão de geometrias)
    contactgroup = dJointGroupCreate(0);	// Inicializa o grupo de juntas de contato (responsáveis pelas forças reativas durante colisões)

    dWorldSetGravity(world,0,0,GRAVITY);	// Define a gravidade do mundo

    ground = dCreatePlane(space,0,0,1,0);	// Cria a geometria do chão (plano xy)

    construirRobos();							// Cria os robôs
    construirBola();							// Cria a bola
    construirCampo();							// Cria o campo
}

void construirRobos()
{
    for(int j=0; j < ROBOTS; j++)
    {
        robot[j].construirRobo(world, space);
    }
}

void construirBola()
{
    bola.construir(world, space);
}

void construirCampo()
{
    construirParedes();
    construirChao();
    construirCirculoCentral();
    construirGols();
    construirQuinas();
}

void construirParedes()
{
    // Walls
    // 0 front      1 back
    // 2 right top  3 right back
    // 4 left top   5 left back
    int n[7] = {1, 1, -1, -1, 1, 1, -1};
    int i;

    for(i = 0; i < 2; i++)
    {
        wall[i] = dCreateBox(space,FIELD_WIDTH,THICK,HEIGTH);
        dGeomSetPosition(wall[i],0,n[i*2]*FRONT_Y,0);
    }

    for(i = 2; i < 6; i++)
    {
        wall[i] = dCreateBox(space,THICK,SIDE_LENGTH,HEIGTH);
        dGeomSetPosition(wall[i],n[i-2]*SIDE_X,n[i*2-4]*SIDE_Y,0);
    }
}

void construirChao()
{
    chao = dCreateBox(space,FIELD_WIDTH*1.2,FIELD_LENGTH*1.2,THICK*2);
    dGeomSetPosition(chao,0,0,-THICK);
}

void construirCirculoCentral()
{
    // Círculo central (sendo desenhado como um cilindro)
    // Para melhor visualização, desabilitar sombras (CTRL+S)
    circle = dCreateCylinder(0,CIRCLE_RADIUS,0.01);
    dGeomSetPosition(circle,0,0,0.005);
}

void construirGols()
{
    // Goal
    goalL[0] = dCreateBox(space,THICK,GOAL_LENGTH,HEIGTH);
    goalL[1] = dCreateBox(space,GOAL_WIDTH,THICK,HEIGTH);
    goalL[2] = dCreateBox(space,GOAL_WIDTH,THICK,HEIGTH);

    dGeomSetPosition(goalL[0], -GOAL_LENGTH_X,0,0);
    dGeomSetPosition(goalL[1], -(GOAL_WIDTH_X), GOAL_WIDTH_Y,0);
    dGeomSetPosition(goalL[2], -(GOAL_WIDTH_X),-GOAL_WIDTH_Y,0);

    goalR[0] = dCreateBox(space,THICK,GOAL_LENGTH,HEIGTH);
    goalR[1] = dCreateBox(space,GOAL_WIDTH,THICK,HEIGTH);
    goalR[2] = dCreateBox(space,GOAL_WIDTH,THICK,HEIGTH);

    dGeomSetPosition(goalR[0], GOAL_LENGTH_X,0,0);
    dGeomSetPosition(goalR[1], GOAL_WIDTH_X, GOAL_WIDTH_Y,0);
    dGeomSetPosition(goalR[2], GOAL_WIDTH_X,-GOAL_WIDTH_Y,0);
}

void construirQuinas()
{
    // Walls
    // 0 front      1 back
    // 2 right top  3 right back
    // 4 left top   5 left back
    int n[7] = {1, 1, -1, -1, 1, 1, -1};
    dMatrix3 R;

    for(int i=0; i < 4; i++)
    {
        triangle[i] = dCreateBox(space,TRIANGLE_THICK,TRIANGLE_LENGTH,HEIGHT);
        dGeomSetPosition(triangle[i],n[i]*TRIANGLE_X,n[i+1]*TRIANGLE_Y,0);
        dRFromAxisAndAngle (R,0,0,1,n[i*2]*M_PI_4);
        dGeomSetRotation (triangle[i], R);
    }
}

void desenharMundo()
{
    desenharRobos();

    //desenhar bolas
    dsSetColor (1,0.5,0.0);
    dsDrawSphere (dBodyGetPosition(bola.corpo),dBodyGetRotation(bola.corpo), BOLA_RAIO);

    desenharCampo();
}

void desenharRobos()
{
    dsSetTexture(DS_WOOD);
    for(int j=0; j < ROBOTS; j++)
    {
        dReal sides[2][3] = {{LENGTH,WIDTH,HEIGHT}, {LENGTH/2,WIDTH,HEIGHT}};
        for(int i=0; i < 2; i++)
        {
            //desenhar chassi
            if (j<3)
                dsSetColor(0.5,1,0);
            else
                dsSetColor(0.5,0,1);
            //dsSetColor(0,0.5,1);
            dsDrawBox(dBodyGetPosition(robot[j].body[i]), dBodyGetRotation(robot[j].body[i]), sides[i]);

            //desenhar roda
            dsSetColor (0,0,0);
            //dsSetColor(1,0.5,1);
            dsDrawCylinder(dBodyGetPosition(robot[j].wheel[i]),dBodyGetRotation(robot[j].wheel[i]),wTHICK,RADIUS);
        }
    }
}

/**
 * @brief Desenhar o campo da simulacao
 *
 * Desenha toda a parte grafica da simulacao, como
 * as paredes, as linhas, os robos e a bola.
 *
 */
void desenharCampo()
{
    dVector3 ss;
    dsSetColor (0,0,0);

    for(int i=0; i < 6; i++) //Paredes
    {
        dGeomBoxGetLengths (wall[i],ss);
        dsDrawBox (dGeomGetPosition(wall[i]), dGeomGetRotation(wall[i]), ss);
    }

    for(int i=0; i < 3;i++) //Gols
    {
        dGeomBoxGetLengths (goalL[i],ss);
        dsDrawBox (dGeomGetPosition(goalL[i]), dGeomGetRotation(goalL[i]), ss);
        dGeomBoxGetLengths (goalR[i],ss);
        dsDrawBox (dGeomGetPosition(goalR[i]), dGeomGetRotation(goalR[i]), ss);
    }

    dsSetColor (1,1,1); //Círculo Central
    dsDrawCylinder(dGeomGetPosition(circle),dGeomGetRotation(circle),0.0001,CIRCLE_RADIUS);

    for (int i=0; i < 4; i++) //Quinas
    {
        dGeomBoxGetLengths (triangle[i],ss);
        dsDrawBox (dGeomGetPosition(triangle[i]), dGeomGetRotation(triangle[i]), ss);
    }
}

void avancarPasso(dReal dt)
{
    dWorldSetQuickStepNumIterations (world, 20);
    dSpaceCollide(space,0,&nearCallback);
    dWorldQuickStep(world, dt);		// Esse valor deve ser sincronizado com as chamadas da função.
    dJointGroupEmpty(contactgroup);
}

void acelerar(int direcao, double intensidade)
{
    switch (direcao)
    {
        case FRENTE:
            LOG(LEVEL_INFO) << "Robo " << n_robot << " Acelerar para frente";
            robot[n_robot].mudarVelocidadeLinear(robot[n_robot].pegarVelocidadeLinear() + intensidade);
            break;
        case TRAS:
            LOG(LEVEL_INFO) << "Robo " << n_robot <<  " Acelerar para tras";
            robot[n_robot].mudarVelocidadeLinear(robot[n_robot].pegarVelocidadeLinear() - intensidade);
            break;
        case HORARIO:
            LOG(LEVEL_INFO) << "Robo " << n_robot <<  " Girar no sentido horario";
            robot[n_robot].mudarVelocidadeAngular(robot[n_robot].pegarVelocidadeAngular() - intensidade);
            break;
        case ANTIHORARIO:
            LOG(LEVEL_INFO) << "Robo " << n_robot <<  " Girar no sentido anti-horario";
            robot[n_robot].mudarVelocidadeAngular(robot[n_robot].pegarVelocidadeAngular() + intensidade);
            break;
    }
}

void atualizarVelocidades()
{
    atualizarVelocidadeBola();
    atualizarVelocidadesAngulares();
    atualizarVelocidadesLineares();
}

void atualizarVelocidadeBola()
{
    if (bola.podeControlar())
    {
        dBodySetLinearVel(bola.corpo, bola.pegarVelocidadeX(), bola.pegarVelocidadeY(), 0);
    }
}

void atualizarVelocidadesAngulares()
{
    double novaVelocidadeAngular;
    for(int i = 0; i < ROBOTS; i++) {
        novaVelocidadeAngular = robot[i].pegarVelocidadeAngular() * TQ;
        dBodySetAngularVel(robot[i].body[0], 0, 0, novaVelocidadeAngular);
        dBodySetAngularVel(robot[i].body[1], 0, 0, novaVelocidadeAngular);
        dBodySetAngularVel(robot[i].wheel[0], 0, 0, novaVelocidadeAngular);
        dBodySetAngularVel(robot[i].wheel[1], 0, 0, novaVelocidadeAngular);
    }
}

void atualizarVelocidadesLineares()
{
    double vx, vy;
    const dReal *rot;

    for(int i = 0; i < ROBOTS; i++)
    {
        rot = dBodyGetRotation(robot[i].body[0]); // rot[1] retorna o valor como o negativo do valor real

        vx = robot[i].pegarVelocidadeLinear() * rot[0] * TQ/3.0;
        vy = -robot[i].pegarVelocidadeLinear() * rot[1] * TQ/3.0; //Como rot[1] tem sinal trocado eh necessario o sinal - para corrigir isso.

        dBodySetLinearVel(robot[i].body[0], vx, vy, 0);
        dBodySetLinearVel(robot[i].body[1], vx, vy, 0);
        dBodySetLinearVel(robot[i].wheel[0], vx, vy, 0);
        dBodySetLinearVel(robot[i].wheel[1], vx, vy, 0);
    }
}

void atualizarPosicoes()
{
    const dReal *posicao;
    double angulo;

    for(int i = 0; i < ROBOTS; i++)
    {
        posicao = dBodyGetPosition(robot[i].body[0]);
        angulo = calcularAngulo(i);

        robot[i].mudarX(posicao[0]);
        robot[i].mudarY(posicao[1]);
        robot[i].mudarTheta(angulo);
    }

    posicao = dBodyGetPosition(bola.corpo);
    bola.mudarX(posicao[0]);
    bola.mudarY(posicao[1]);
}

double calcularAngulo(int i)
{
    Quaternion qt;
    const dReal *rotacaoReal = dBodyGetQuaternion (robot[i].body[0]);
    qt(0) = rotacaoReal[0];
    qt(1) = rotacaoReal[1];
    qt(2) = rotacaoReal[2];
    qt(3) = rotacaoReal[3];
    Vetor3 v;
    v = qt.toEuler ();
    return v(2);
}

void destruirMundo()
{
    for(int i=0; i < 6; i++)//destruir Robos
    {
        dGeomDestroy (robot[i].box[0]);
        dGeomDestroy (robot[i].box[1]);
        dGeomDestroy (robot[i].cylinder[0]);
        dGeomDestroy (robot[i].cylinder[1]);
    }

    bola.destruir();

    for(int i=0; i < 6; i++) //destruir Campo
        dGeomDestroy(wall[i]);

    for(int i=0; i < 3; i++) //destruir Gols
    {
        dGeomDestroy(goalR[i]);
        dGeomDestroy(goalL[i]);
    }

    for(int i=0; i < 4; i++)//destruir Quinas
    {
        dGeomDestroy(triangle[i]);
    }

    dJointGroupDestroy(contactgroup);		// Destrói o grupo de juntas de contato
    dSpaceDestroy (space);					// Destrói o espaço
    dWorldDestroy (world);					// Destrói o mundo
}

//////////////////////////////////////////Funcoes de Estrategia//////////////////////////////////////////////
// Todas as funções de estratégia foram removidas desse arquivo.
// Apenas o módulo de estratégia possui tais funções.

//////////////////////////////////////////Funcoes de Comunicacao/////////////////////////////////////////////

void inicializarComunicacao()
{
    _com->criar_var <Dados_Simulador> ("Dados_Simulador");
    _com->criar_var <Dados_Estrategia> ("Dados_Estrategia");
}

void receberVelocidades()
{
    std::cout << "recebendo velocidades" << std::endl;
    Dados_Estrategia dados;
    dados = _com->ler_var <Dados_Estrategia> ("Dados_Estrategia");

    for(int num_team = 0; num_team < 2; num_team++)
    {
        for(int num_player = 0; num_player < 3; num_player++)
        {
            robot[(num_team*3) + num_player].mudarVelocidadeLinear (dados.f_vel_linear [(num_team*3) + num_player]);
            robot[(num_team*3) + num_player].mudarVelocidadeAngular (dados.f_vel_angular [(num_team*3) + num_player]);
        }
    }
}

void enviarPosicoes()
{
    std::cout << "enviando posições" << std::endl;
    Dados_Simulador dados;

    for(int num_team = 0; num_team < 2; num_team++)
    {
        for(int num_player = 0; num_player < 3; num_player++)
        {
            dados.v_pos_robo[(num_team*3) + num_player][0] = robot[(num_team*3) + num_player].pegarX();
            dados.v_pos_robo[(num_team*3) + num_player][1] = robot[(num_team*3) + num_player].pegarY();
            dados.v_pos_robo[(num_team*3) + num_player][2] = robot[(num_team*3) + num_player].pegarTheta();
            std::cout << robot[(num_team*3) + num_player].pegarTheta() << std::endl;
        }
    }
    dados.v_pos_bola[0] = bola.pegarX();
    dados.v_pos_bola[1] = bola.pegarY();

    _com->escrever_var <Dados_Simulador> ("Dados_Simulador", dados);
}

void receberComando()
{
    //LOG(LEVEL_DEBUG) << "Recebendo comandos";
    //
    //string simulation_command;
    //
    //(*_com) >> IN(string("simulation_command"), &simulation_command);
    //
    //LOG(LEVEL_DEBUG) << "simulation_command = " << simulation_command;
    //
    //// reiniciar simulação
    //if (simulation_command == string("reset"))
    //{
    //	for(int i = 0; i < 6; i++)
    //	{
    //		robot[i].mudarVelocidadeLinear(0);
    //		robot[i].mudarVelocidadeAngular(0);
    //		robot[i].voltarPosicaoInicial();
    //	}
    //
    //	bola.resetar();
    //	destruirMundo();
    //	construirMundo();
    //}
 //
 //   if (simulation_command == string("exit"))
 //   {
 //       exit(0);
 //   }
}
