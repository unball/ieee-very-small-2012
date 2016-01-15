/*
    @file Regioes.h

    @autor William Batista Aguiar Motta
    @email yosoyninja@gmail.com

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
#ifndef REGIOES_H
#define REGIOES_H
/*
cada regiao tem um identificador.

lado esquerdo é o lado amigo.
lado direito é o lado adversário.

colocar Regiao como privada
*/
#include <vector>
#include <Vetor.h>
#include <Config.h>

using namespace std;

enum Regiao
{
    r_fora_campo = 0,
    r_campo = 1,
    r_ataque = 2, r_defesa = 4,
    r_sobra_dir = 8, r_sobra_esq = 16,
    r_defesa_dir = 32, r_defesa_esq = 64, r_defesa_centro = 128,
    r_suporte_esq = 256, r_suporte_dir = 512,
    r_inicio_dir = 1024, r_inicio_esq = 2048, r_inicio_gol = 4096
};
class c_Regiao;
class Regioes
{
public:
    Regioes ();
    ~Regioes ();
    Regioes & operator= (const Regioes & r);

    Regiao regiao_de (Vetor3 v);
    Regiao regiao_sobra_de (Vetor3 v);
    Regiao regiao_defesa_de (Vetor3 v);
    Regiao regiao_suporte_de (Vetor3 v);
    Regiao regiao_inicio_de (Vetor3 v);

    bool vetor_pertence_regiao (Regiao r, Vetor3 v);
    Vetor3 mais_proximo_de (Regiao r, Vetor3 v);
    Vetor3 centro (Regiao r);
private:
    Regioes (const Regioes & r) {}
    vector<c_Regiao*> Reg;
};
class c_Regiao
{
public:
    Config config;
    c_Regiao ();
    virtual ~c_Regiao () {}
    bool virtual vetor_pertence_regiao (Vetor3 v) = 0;
    Vetor3 mais_proximo_de (Vetor3 v);
    Vetor3 centro ();
    int id ();
    bool operator== (const c_Regiao & r1);
    bool operator!= (const c_Regiao & r1);
protected:
    int i_id;
    Vetor3 v_centro;
    vector<Vetor3> v_ponto;
    //-- circunferência.
    double f_raio;
    //-- retângulo.
    double f_largura, f_comprimento;
    Vetor3 v_canto;
};

class Regiao_retangular : public c_Regiao
{
public:
    ~Regiao_retangular() {}
    bool vetor_pertence_regiao (Vetor3 v);
};
class Regiao_circular : public c_Regiao
{
public:
    ~Regiao_circular() {}
    bool vetor_pertence_regiao (Vetor3 v);
};

class r_Campo : public Regiao_retangular
{
public:
    r_Campo ();
};
class r_Ataque : public Regiao_retangular
{
public:
    r_Ataque ();
};
class r_Defesa : public Regiao_retangular
{
public:
    r_Defesa ();
};
class r_Sobra_dir : public Regiao_retangular
{
public:
    r_Sobra_dir ();
};
class r_Sobra_esq : public Regiao_retangular
{
public:
    r_Sobra_esq ();
};
class r_Defesa_dir : public Regiao_retangular
{
public:
    r_Defesa_dir ();
};
class r_Defesa_esq : public Regiao_retangular
{
public:
    r_Defesa_esq ();
};
class r_Defesa_centro : public Regiao_circular
{
public:
    r_Defesa_centro ();
};
class r_Suporte_dir : public Regiao_circular
{
public:
    r_Suporte_dir ();
};
class r_Suporte_esq : public Regiao_circular
{
public:
    r_Suporte_esq ();
};
class r_Inicio_dir : public Regiao_circular
{
public:
    r_Inicio_dir ();
};
class r_Inicio_esq : public Regiao_circular
{
public:
    r_Inicio_esq ();
};
class r_Inicio_gol : public Regiao_circular
{
public:
    r_Inicio_gol ();
};

#endif // !REGIOES_H
