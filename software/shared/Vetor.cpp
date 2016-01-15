/*
    @file Vetor.cpp

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
#include <Vetor.h>

Vetor::Vetor ()
    : linhas (0), colunas (0)
{
}

Vetor::Vetor (int linhas, int colunas)
    : linhas (linhas), colunas (colunas)
{
    _dados.resize(linhas * colunas);
}
Vetor::Vetor (int linhas)
    : linhas (linhas), colunas (1)
{
    _dados.resize(linhas * 1);
}
Vetor::Vetor (const Vetor & copia)
    : linhas (copia.linhas), colunas (copia.colunas)
{
    _dados = copia._dados;
}
Vetor::~Vetor ()
{
}
double Vetor::operator () (int linha) const
{
    if (linha >= linhas)
    {
        throw "Fora dos limites do vetor.";
    }
    return this->_dados[linha * colunas];
}
double & Vetor::operator () (int linha)
{
    if (linha >= linhas)
    {
        throw "Fora dos limites do vetor.";
    }
    return this->_dados[linha * colunas];
}
double Vetor::operator () (int linha, int coluna)const
{
    if (linha >= linhas || coluna >= colunas)
    {
        throw "Fora dos limites do vetor.";
    }
    return this->_dados[linha * colunas + coluna];
}
double & Vetor::operator () (int linha, int coluna)
{
    if (linha >= linhas || coluna >= colunas)
    {
        throw "Fora dos limites do vetor.";
    }
    return this->_dados[linha * colunas + coluna];
}

Vetor Vetor::nulo () const
{
    Vetor n (linhas, colunas);
    for ( int i = 0; i < linhas; i++)
        for ( int j = 0; j < colunas; j++)
        {
            n (i, j) = 0.0;
        }
    return n;
}
Vetor Vetor::identidade () const
{
    if (this->linhas == this->colunas)
    {
        Vetor id = this->nulo ();
        for (int i = 0; i < this->linhas; i++)
        {
            for (int j = 0; j < this->colunas; j++)
            {
                if (i == j)
                {
                    id (i, j) = 1.;
                }
            }
        }
        return id;
    }
    else
    {
        throw "A matriz não é quadrada, logo não é possível criar uma matriz identidade a partir dela.";
    }
}
Vetor Vetor::transposta () const
{
    Vetor transp (this->colunas, this->linhas);
    for ( int i = 0; i < this->linhas; i++)
        for ( int j = 0; j < this->colunas; j++)
        {
            transp (j, i) = (*this) (i, j);
        }
    return transp;
}
Vetor Vetor::trans () const
{
    return Vetor::transposta ();
}
double Vetor::modulo () const
{
    if (this->colunas == 1)
    {
        Vetor produto;
        produto = this->transposta () * (*this);
        return sqrt (produto (0));
    }
    else
    {
        throw "O número de colunas do vetor deve ser igual a 1.";
    }
}
bool Vetor::operator == (const Vetor & m) const
{
    if (this->colunas != m.colunas || this->linhas != m.linhas)
    {
        return false;
    }
    for (int i = 0; i < m.linhas; i++)
        for (int j = 0; j < m.colunas; j++)
            if ((*this) (i, j) != m (i, j))
            {
                return false;
            }
    return true;
}
bool Vetor::operator != (const Vetor & m) const
{
    return ! (*this == m);
}
Vetor & Vetor::operator = (const Vetor & nova)
{
    if (this != &nova)
    {
        this->linhas = nova.linhas;
        this->colunas = nova.colunas;
        this->_dados = nova._dados;
    }
    return *this;
}
Vetor operator + (const Vetor & m1, const Vetor & m2)
{
    if (m1.linhas != m2.linhas || m1.colunas != m2.colunas)
    {
        throw "Os vetores possuem dimensões diferentes.";
    }
    Vetor soma (m1.linhas, m1.colunas);
    for ( int i = 0; i < m1.linhas; i++)
        for ( int j = 0; j < m1.colunas; j++)
        {
            soma (i, j) = m1 (i, j) + m2 (i, j);
        }
    return soma;
}
Vetor operator - (const Vetor & m1, const Vetor & m2)
{
    if (m1.linhas != m2.linhas || m1.colunas != m2.colunas)
    {
        throw "Os vetores possuem dimensões diferentes.";
    }
    Vetor soma (m1.linhas, m1.colunas);
    for (int i = 0; i < m1.linhas; i++)
        for (int j = 0; j < m1.colunas; j++)
        {
            soma (i, j) = m1 (i, j) - m2 (i, j);
        }
    return soma;
}
Vetor operator * (const Vetor & m1, const Vetor & m2)
{
    if (m1.colunas != m2.linhas)
    {
        throw "O número de colunas de V1 é diferente do número de linhas de V2.";
    }
    Vetor produto (m1.linhas, m2.colunas);
    produto = produto.nulo ();
    if (m1.colunas == m2.linhas)
    {
        for (int i = 0; i < m1.linhas; i++)
            for ( int j = 0; j < m2.colunas; j++)
                for ( int k = 0; k < m1.colunas; k++)
                {
                    produto (i, j) += m1 (i, k) * m2 (k, j);
                }
    }
    return produto;
}
Vetor operator * (double a, const Vetor & m)
{
    Vetor produto (m.linhas, m.colunas);
    for (int i = 0; i < m.linhas; i++)
        for (int j = 0; j < m.colunas; j++)
        {
            produto (i, j) = a * m (i, j);
        }
    return produto;
}
Vetor operator * (const Vetor & m, double a)
{
    return (a * m);
}
//ofstream & operator << (ofstream & o, const Vetor & m)
//{
//	if (m.linhas == 1)
//	{
//		o << "( ";
//		for (int i = 0; i < m.colunas ; i++)
//		{
//			o << m (i);
//			if (i != m.colunas - 1)
//			{
//				o << " , ";
//			}
//		}
//		o << " )";
//	}
//	else
//	{
//		for ( int i = 0; i < m.linhas; i++)
//		{
//			for ( int j = 0; j < m.colunas; j++)
//			{
//				o << m (i, j) << "\t";
//			}
//			o << endl;
//		}
//		o << endl;
//	}
//	return o;
//}
ostream & operator << (ostream & o, const Vetor & m)
{
    // impressão em linha.
    if (m.linhas == 1)
    {
        o << "( ";
        for (int i = 0; i < m.colunas ; i++)
        {
            o << m (0, i);
            if (i != m.colunas - 1)
            {
                o << " , ";
            }
        }
        o << " )";
    }
    else
    {
        // impressão em matriz.
        for ( int i = 0; i < m.linhas; i++)
        {
            for ( int j = 0; j < m.colunas; j++)
            {
                o << m (i, j) << "\t";
            }
            o << endl;
        }
        o << endl;
    }
    return o;
}
double Vetor::escalar (const Vetor & a, const Vetor & b) const
{
    if (a.linhas != b.linhas)
    {
        throw "O número de linhas do vetor 1 é diferente do vetor 2.";
    }
    if (a.colunas != 1 || b.colunas != 1)
    {
        throw "O número de colunas dos vetores deve ser igual a 1.";
    }
    Vetor c;
    c = a.trans () * b;
    return c (0);
}
double Vetor::escalar (const Vetor & b) const
{
    return escalar ((*this), b);
}
Vetor Vetor::vetorial (const Vetor & b, const Vetor & a) const
{
    if (a.colunas != 1 || b.colunas != 1)
    {
        throw "O número de colunas dos vetores deve ser igual a 1.";
    }
    if (a.linhas != 3 && b.linhas != 3)
    {
        throw "Os vetores devem ser de dimensão 3.";
    }
    Vetor c (3);
    c (0) =	a (1) * b (2) - a (2) * b (1);
    c (1) = -1 * (a (0) * b (2) - a (2) * b (0));
    c (2) = a (0) * b (1) - a (1) * b (0);
    return c;
}
Vetor Vetor::vetorial (const Vetor & b) const
{
    return vetorial ((*this), b);
}
Vetor Vetor::unitario () const
{
    if (*this == this->nulo ())
    {
        return this->nulo ();
    }
    else
    {
        return (1 / this->modulo ()) * (*this);
    }
}
Vetor v3_Z ()
{
    Vetor z (3);
    z (0) = 0.;
    z (1) = 0.;
    z (2) = 1.;
    return z;
}
Vetor v3_Y ()
{
    Vetor y (3);
    y (0) = 0.;
    y (1) = 1.;
    y (2) = 0.;
    return y;
}
Vetor v3_X ()
{
    Vetor x (3);
    x (0) = 1.;
    x (1) = 0.;
    x (2) = 0.;
    return x;
}
Vetor v2_X ()
{
    Vetor x (2);
    x (0) = 1.;
    x (1) = 0.;
    return x;
}
Vetor v2_Y ()
{
    Vetor x (2);
    x (0) = 0.;
    x (1) = 1.;
    return x;
}
Vetor v3_rotacao (double k)
{
    Vetor aux (2, 2);
    aux (0, 0) =  cos (k);
    aux (0, 1) =  sin (k);
    aux (1, 0) = -1.*sin (k);
    aux (1, 1) =  cos (k);
    return aux;
}
//-- Dimensão 3x1.
Vetor3::Vetor3 () : Vetor (3)
{
    (*this) (0) = 0;
    (*this) (1) = 0;
    (*this) (2) = 0;
}
Vetor3::Vetor3 (const Vetor & m) {
    if (m.linhas != 3)
        throw "A dimensão do vetor é diferente de 3.";
    Vetor3 v;
    v(0) = m(0);
    v(1) = m(1);
    v(2) = m(2);
    *this = v;
}
Vetor3 Vetor3::operator= (Vetor & m) {
    if (m.linhas != 3)
        throw "A dimensão do vetor é diferente de 3.";
    Vetor3 v;
    v(0) = m(0);
    v(1) = m(1);
    v(2) = m(2);
    return v;
}
Vetor3 Vetor3::X() {
    Vetor3 x;
    x(0) = 1;
    return x;
}
Vetor3 Vetor3::Y() {
    Vetor3 x;
    x(1) = 1;
    return x;
}
Vetor3 Vetor3::Z() {
    Vetor3 x;
    x(2) = 1;
    return x;
}
//-- Dimensão 2x1.
Vetor2::Vetor2 (const Vetor & m) {
    if (m.linhas != 2)
        throw "A dimensão do vetor é diferente de 2.";
    Vetor2 v;
    v(0) = m(0);
    v(1) = m(1);
    *this = v;
}
Vetor2::Vetor2 () : Vetor (2)
{
    (*this) (0) = 0;
    (*this) (1) = 0;
}
Vetor2 Vetor2::operator= (Vetor & m) {
    if (m.linhas != 2)
        throw "A dimensão do vetor é diferente de 2.";
    Vetor2 v;
    v(0) = m(0);
    v(1) = m(1);
    return v;
}
Vetor2 Vetor2::perpendicular() {
    Vetor2 p;
    Vetor m(2,2);
    m(0,0) = 0;
    m(0,1) = -1;
    m(1,0) = 1;
    m(1,1) = 0;

    p = m * (*this);
    return p;
}
Vetor2 Vetor2::perp() {
    return this->perpendicular();
}
Vetor2 Vetor2::X() {
    Vetor2 x;
    x(0) = 1;
    return x;
}
Vetor2 Vetor2::Y() {
    Vetor2 x;
    x(1) = 1;
    return x;
}
