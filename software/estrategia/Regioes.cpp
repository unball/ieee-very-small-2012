/*
    @file Regioes.cpp

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
#include <Regioes.h>
#include <Config.h>

Regioes::Regioes ()
{
    Reg.push_back (new r_Campo);
    Reg.push_back (new r_Ataque);
    Reg.push_back (new r_Defesa);
    Reg.push_back (new r_Sobra_dir);
    Reg.push_back (new r_Sobra_esq);
    Reg.push_back (new r_Defesa_dir);
    Reg.push_back (new r_Defesa_esq);
    Reg.push_back (new r_Defesa_centro);
    Reg.push_back (new r_Suporte_dir);
    Reg.push_back (new r_Suporte_esq);
    Reg.push_back (new r_Inicio_dir);
    Reg.push_back (new r_Inicio_esq);
    Reg.push_back (new r_Inicio_gol);
}
Regioes::~Regioes ()
{
    for (uint i = 0; i < Reg.size (); i++)
    {
        delete Reg[i];
    }
}
Regioes & Regioes::operator= (const Regioes & r)
{
    /*
        for (int i=0; i<N; i++) {
            delete this->Reg[i];
        }

        Reg[r_campo] = new r_Campo();
        Reg[r_ataque] = new r_Ataque();
        Reg[r_defesa] = new r_Defesa();
        Reg[r_sobra_dir] = new r_Sobra_dir();
        Reg[r_sobra_esq] = new r_Sobra_esq();
        Reg[r_defesa_dir] = new r_Defesa_dir();
        Reg[r_defesa_esq] = new r_Defesa_esq();
        Reg[r_defesa_centro] = new r_Defesa_centro();
        Reg[r_suporte_dir] = new r_Suporte_dir();
        Reg[r_suporte_esq] = new r_Suporte_esq();
        Reg[r_inicio_dir] = new r_Inicio_dir();
        Reg[r_inicio_esq] = new r_Inicio_esq();
        Reg[r_inicio_gol] = new r_Inicio_gol();

        for (int i=0; i<N; i++) {
            *this->Reg[i] = *r.Reg[i];
        }
    */
    return *this;
}
c_Regiao::c_Regiao ():config("constants.config")
{
    i_id = 0;
    f_raio = 100;
}
//bool Regiao::vetor_pertence_regiao (Vetor3 v) {
//	if ((v-v_centro).modulo() < f_raio)
//		return true;
//	else
//		return false;
//}
Vetor3 c_Regiao::mais_proximo_de (Vetor3 v)
{
    double f_menor_dist;
    int i_menor_dist;
    f_menor_dist = (v_ponto[0] - v).modulo ();
    i_menor_dist = 0;
    for (unsigned int i = 0; i < v_ponto.size (); i++)
    {
        double f_dist = (v_ponto[0] - v).modulo ();
        if (f_dist < f_menor_dist)
        {
            f_menor_dist = f_dist;
            i_menor_dist = i;
        }
    }
    return v_ponto[i_menor_dist];
}
Vetor3 c_Regiao::centro ()
{
    return v_centro;
}
int c_Regiao::id ()
{
    return i_id;
}
bool c_Regiao::operator== (const c_Regiao & r1)
{
    if (this->i_id == r1.i_id)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool c_Regiao::operator!= (const c_Regiao & r1)
{
    return ! (*this == r1);
}

Regiao Regioes::regiao_de (Vetor3 v)
{
    int res = 0;
    for (uint i=0; i<Reg.size(); i++)
        if (Reg[i])
            if(Reg[i]->vetor_pertence_regiao (v))
                res |= Reg[i]->id();
    return (Regiao) res;
    /*
    if (Reg[r_ataque]->vetor_pertence_regiao (v))
    {
        return r_ataque;
    }
    if (Reg[r_defesa]->vetor_pertence_regiao (v))
    {
        return r_defesa;
    }
    return r_fora_campo;
    */
}
Regiao Regioes::regiao_sobra_de (Vetor3 v)
{
    int res = 0;
    res = regiao_de (v);
    if (res & r_sobra_dir)
    {
        return r_sobra_dir;
    }
    if (res & r_sobra_esq)
    {
        return r_sobra_esq;
    }
    return r_campo;
}
Regiao Regioes::regiao_defesa_de (Vetor3 v)
{
    int res = 0;
    res = regiao_de (v);

    if (res & r_defesa_centro)
    {
        return r_defesa_centro;
    }
    if (res & r_defesa_dir)
    {
        return r_defesa_dir;
    }
    if (res & r_defesa_esq)
    {
        return r_defesa_esq;
    }
    return r_campo;
}
Regiao Regioes::regiao_suporte_de (Vetor3 v)
{
    int res = 0;
    res = regiao_de (v);

    if (res & r_suporte_dir)
    {
        return r_suporte_dir;
    }
    if (res & r_suporte_esq)
    {
        return r_suporte_esq;
    }
    return r_campo;
}
Regiao Regioes::regiao_inicio_de (Vetor3 v)
{
    int res = 0;
    res = regiao_de (v);

    if (res & r_inicio_dir)
    {
        return r_inicio_dir;
    }
    if (res & r_inicio_esq)
    {
        return r_inicio_esq;
    }
    if (res & r_inicio_gol)
    {
        return r_inicio_gol;
    }
    return r_campo;
}

bool Regioes::vetor_pertence_regiao (Regiao r, Vetor3 v)
{
    int res = 0;
    res = regiao_de (v);

    return (res & r);
}
Vetor3 Regioes::mais_proximo_de (Regiao r, Vetor3 v)
{
    for (uint i=0; i<Reg.size (); i++)
        if (Reg[i]->id () == r)
            return Reg[i]->mais_proximo_de (v);
    throw "Regiao nao encontrada";
}
Vetor3 Regioes::centro (Regiao r)
{
    for (uint i=0; i<Reg.size (); i++)
        if (Reg[i]->id () == r)
            return Reg[i]->centro ();
    throw "Regiao nao encontrada";
}

bool Regiao_circular::vetor_pertence_regiao (Vetor3 v)
{
    if ((v - v_centro).modulo () < f_raio)
    {
        return true;
    }
    return false;
}
bool Regiao_retangular::vetor_pertence_regiao (Vetor3 v)
{
    if (v_canto (0) <= v (0) && v (0) <= v_canto (0) + f_comprimento && v_canto (1) - f_largura <= v (1) && v (1) <= v_canto (1))
    {
        return true;
    }
    return false;
}

r_Campo::r_Campo ()
{
    i_id = r_campo;
    v_centro = Vetor3 ();
    v_canto = Vetor3 ();
    v_centro (0) = atof (config.get ("CENTRO_CAMPO", 0).c_str ());
    v_centro (1) = atof (config.get ("CENTRO_CAMPO", 1).c_str ());
    v_canto (0)  = atof (config.get ("RETANGULO_CAMPO", 0).c_str ());
    v_canto (1)	= atof (config.get ("RETANGULO_CAMPO", 1).c_str ());
    f_largura	= atof (config.get ("RETANGULO_CAMPO", 2).c_str ());
    f_comprimento = atof (config.get ("RETANGULO_CAMPO", 3).c_str ());
    v_ponto.push_back (v_centro);
}
r_Ataque::r_Ataque ()
{
    i_id = r_ataque;
    v_centro = Vetor3 ();
    v_canto = Vetor3 ();
    v_centro (0) = atof (config.get ("CENTRO_ATAQUE", 0).c_str ());
    v_centro (1) = atof (config.get ("CENTRO_ATAQUE", 1).c_str ());
    v_canto (0)  = atof (config.get ("RETANGULO_ATAQUE", 0).c_str ());
    v_canto (1)	= atof (config.get ("RETANGULO_ATAQUE", 1).c_str ());
    f_largura	= atof (config.get ("RETANGULO_ATAQUE", 2).c_str ());
    f_comprimento = atof (config.get ("RETANGULO_ATAQUE", 3).c_str ());
    v_ponto.push_back (v_centro);
}
r_Defesa::r_Defesa ()
{
    i_id = r_defesa;
    v_centro = Vetor3 ();
    v_canto = Vetor3 ();
    v_centro (0) = atof (config.get ("CENTRO_DEFESA", 0).c_str ());
    v_centro (1) = atof (config.get ("CENTRO_DEFESA", 1).c_str ());
    v_canto (0)  = atof (config.get ("RETANGULO_DEFESA", 0).c_str ());
    v_canto (1)	= atof (config.get ("RETANGULO_DEFESA", 1).c_str ());
    f_largura	= atof (config.get ("RETANGULO_DEFESA", 2).c_str ());
    f_comprimento = atof (config.get ("RETANGULO_DEFESA", 3).c_str ());
    v_ponto.push_back (v_centro);
}
r_Sobra_dir::r_Sobra_dir ()
{
    i_id = r_sobra_dir;
    v_centro = Vetor3 ();
    v_canto = Vetor3 ();
    v_centro (0) = atof (config.get ("CENTRO_SOBRA_DIR", 0).c_str ());
    v_centro (1) = atof (config.get ("CENTRO_SOBRA_DIR", 1).c_str ());
    v_canto (0)  = atof (config.get ("RETANGULO_SOBRA_DIR", 0).c_str ());
    v_canto (1)	= atof (config.get ("RETANGULO_SOBRA_DIR", 1).c_str ());
    f_largura	= atof (config.get ("RETANGULO_SOBRA_DIR", 2).c_str ());
    f_comprimento = atof (config.get ("RETANGULO_SOBRA_DIR", 3).c_str ());
    v_ponto.push_back (v_centro);
}
r_Sobra_esq::r_Sobra_esq ()
{
    i_id = r_sobra_esq;
    v_centro = Vetor3 ();
    v_canto = Vetor3 ();
    v_centro (0) = atof (config.get ("CENTRO_SOBRA_ESQ", 0).c_str ());
    v_centro (1) = atof (config.get ("CENTRO_SOBRA_ESQ", 1).c_str ());
    v_canto (0)  = atof (config.get ("RETANGULO_SOBRA_ESQ", 0).c_str ());
    v_canto (1)	= atof (config.get ("RETANGULO_SOBRA_ESQ", 1).c_str ());
    f_largura	= atof (config.get ("RETANGULO_SOBRA_ESQ", 2).c_str ());
    f_comprimento = atof (config.get ("RETANGULO_SOBRA_ESQ", 3).c_str ());
    v_ponto.push_back (v_centro);
}
r_Defesa_dir::r_Defesa_dir ()
{
    i_id = r_defesa_dir;
    v_centro = Vetor3 ();
    v_canto = Vetor3 ();
    v_centro (0) = atof (config.get ("CENTRO_DEFESA_DIR", 0).c_str ());
    v_centro (1) = atof (config.get ("CENTRO_DEFESA_DIR", 1).c_str ());
    v_canto (0)  = atof (config.get ("RETANGULO_DEFESA_DIR", 0).c_str ());
    v_canto (1)	= atof (config.get ("RETANGULO_DEFESA_DIR", 1).c_str ());
    f_largura	= atof (config.get ("RETANGULO_DEFESA_DIR", 2).c_str ());
    f_comprimento = atof (config.get ("RETANGULO_DEFESA_DIR", 3).c_str ());
    v_ponto.push_back (v_centro);
}
r_Defesa_esq::r_Defesa_esq ()
{
    i_id = r_defesa_esq;
    v_centro = Vetor3 ();
    v_canto = Vetor3 ();
    v_centro (0) = atof (config.get ("CENTRO_DEFESA_ESQ", 0).c_str ());
    v_centro (1) = atof (config.get ("CENTRO_DEFESA_ESQ", 1).c_str ());
    v_canto (0)  = atof (config.get ("RETANGULO_DEFESA_ESQ", 0).c_str ());
    v_canto (1)	= atof (config.get ("RETANGULO_DEFESA_ESQ", 1).c_str ());
    f_largura	= atof (config.get ("RETANGULO_DEFESA_ESQ", 2).c_str ());
    f_comprimento = atof (config.get ("RETANGULO_DEFESA_ESQ", 3).c_str ());
    v_ponto.push_back (v_centro);
}
r_Defesa_centro::r_Defesa_centro ()
{
    i_id = r_defesa_centro;
    v_centro = Vetor3 ();
    v_centro (0) = atof (config.get ("CENTRO_DEFESA_CENTRO", 0).c_str ());
    v_centro (1) = atof (config.get ("CENTRO_DEFESA_CENTRO", 1).c_str ());
    f_raio = atof (config.get ("RAIO_BASE").c_str ());
    v_ponto.push_back (v_centro);
}
r_Suporte_dir::r_Suporte_dir ()
{
    i_id = r_suporte_dir;
    v_centro = Vetor3 ();
    v_centro (0) = atof (config.get ("CENTRO_SUPORTE_DIR", 0).c_str ());
    v_centro (1) = atof (config.get ("CENTRO_SUPORTE_DIR", 1).c_str ());
    f_raio = atof (config.get ("RAIO_SUPORTE").c_str ());
    v_ponto.push_back (v_centro);
}
r_Suporte_esq::r_Suporte_esq ()
{
    i_id = r_suporte_esq;
    v_centro = Vetor3 ();
    v_centro (0) = atof (config.get ("CENTRO_SUPORTE_ESQ", 0).c_str ());
    v_centro (1) = atof (config.get ("CENTRO_SUPORTE_ESQ", 1).c_str ());
    f_raio = atof (config.get ("RAIO_SUPORTE").c_str ());
    v_ponto.push_back (v_centro);
}
r_Inicio_dir::r_Inicio_dir ()
{
    i_id = r_inicio_dir;
    v_centro = Vetor3 ();
    v_centro (0) = atof (config.get ("CENTRO_INICIO_DIR", 0).c_str ());
    v_centro (1) = atof (config.get ("CENTRO_INICIO_DIR", 1).c_str ());
    f_raio = atof (config.get ("RAIO_BASE").c_str ());
    v_ponto.push_back (v_centro);
}
r_Inicio_esq::r_Inicio_esq ()
{
    i_id = r_inicio_esq;
    v_centro = Vetor3 ();
    v_centro (0) = atof (config.get ("CENTRO_INICIO_ESQ", 0).c_str ());
    v_centro (1) = atof (config.get ("CENTRO_INICIO_ESQ", 1).c_str ());
    f_raio = atof (config.get ("RAIO_BASE").c_str ());
    v_ponto.push_back (v_centro);
}
r_Inicio_gol::r_Inicio_gol ()
{
    i_id = r_inicio_gol;
    v_centro = Vetor3 ();
    v_centro (0) = atof (config.get ("CENTRO_INICIO_GOL", 0).c_str ());
    v_centro (1) = atof (config.get ("CENTRO_INICIO_GOL", 1).c_str ());
    f_raio = atof (config.get ("RAIO_BASE").c_str ());
    v_ponto.push_back (v_centro);
}
