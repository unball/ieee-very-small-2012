/*
    @file Comunicador.cpp

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

#include <Comunicador.h>

Comunicador::Comunicador (std::string p1, std::string p2, modo m)
{
    _conexao = p1 + "_" + p2;
    _memoria = boost::interprocess::managed_shared_memory (boost::interprocess::open_or_create, _conexao.c_str (), 2000);
    _memoria.find_or_construct <modo> ("modo") (m);
    _mutex = _memoria.find_or_construct <boost::interprocess::interprocess_mutex> ("mutex") ();
    _modo = m;
    std::pair <int *, std::size_t> pair_n_processos;
    pair_n_processos = _memoria.find <int> ("n_processos");
    if (pair_n_processos.first) {
        _n_processos = pair_n_processos.first;
        (*_n_processos) ++;
    } else {
        _n_processos = _memoria.construct <int> ("n_processos") ();
        *_n_processos = 1;
    }
}
Comunicador::Comunicador(std::string nomeConexao)
{
    _conexao = nomeConexao;
    _memoria = boost::interprocess::managed_shared_memory (boost::interprocess::open_or_create, _conexao.c_str (), 2000);
    _memoria.find_or_construct <modo> ("modo") (escrever);
    _mutex = _memoria.find_or_construct <boost::interprocess::interprocess_mutex> ("mutex") ();
    _modo = escrever;
    std::pair <int *, std::size_t> pair_n_processos;
    pair_n_processos = _memoria.find <int> ("n_processos");
    if (pair_n_processos.first) {
        _n_processos = pair_n_processos.first;
        (*_n_processos) ++;
    } else {
        _n_processos = _memoria.construct <int> ("n_processos") ();
        *_n_processos = 1;
    }
}

Comunicador::~Comunicador ()
{
    (*_n_processos) --;
//    if (*_n_processos < 1) {
        boost::interprocess::shared_memory_object::remove (_conexao.c_str ());
//    }
}
std::string Comunicador::nome_conexao ()
{
    return _conexao;
}

int Comunicador::n_processos()
{
    return *_n_processos;
}
template <> void Comunicador::criar_var <std::string> (std::string nome)
{
    _mutex->lock();
    _memoria.find_or_construct <mem_string> (nome.c_str ()) ("", _memoria.get_segment_manager ());
    _mutex->unlock();
}
template <> std::string Comunicador::ler_var <std::string> (std::string nome)
{
    _mutex->lock();
    std::pair <mem_string *, std::size_t> v_pair;
    v_pair = _memoria.find <mem_string> (nome.c_str ());
    std::string var;
    if (v_pair.first)
    {
        var = (*v_pair.first).c_str ();
    }
    else
    {
        var = "";
    }
    _mutex->unlock();
    return var;
}
template <> void Comunicador::escrever_var <std::string> (std::string nome, std::string valor)
{
    _mutex->lock();
    std::pair <mem_string *, std::size_t> v_pair;
    v_pair = _memoria.find <mem_string> (nome.c_str ());
    if (v_pair.first)
    {
        *v_pair.first = valor.c_str ();
    }
    _mutex->unlock();
}
template <> void Comunicador::destruir_var <std::string> (std::string nome)
{
    _mutex->lock();
    _memoria.destroy <mem_string> (nome.c_str ());
    _mutex->unlock();
}
bool Comunicador::ready ()
{

    _mutex->lock();
    bool ret;
    std::pair <modo *, std::size_t> par;
    par = _memoria.find <modo> ("modo");
    if (par.first)
    {
        ret = *par.first == _modo;
    }
    else
    {
        ret = false;
    }
    _mutex->unlock();
    return ret;
}
void Comunicador::done ()
{
    _mutex->lock();
    std::pair <modo *, std::size_t> par;
    par = _memoria.find <modo> ("modo");
    if (par.first)
    {
        if (_modo == ler)
        {
            *par.first = escrever;
        }
        else
        {
            *par.first = ler;
        }
    }
    _mutex->unlock();
}
