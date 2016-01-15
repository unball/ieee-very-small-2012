/*
    @file Comunicador.h

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

#ifndef COMUNICADOR_H
#define COMUNICADOR_H

#include <string>

#include <boost/interprocess/managed_shared_memory.hpp>		// memória compartilhada
#include <boost/interprocess/sync/interprocess_mutex.hpp>	// mutex anônimo
#include <boost/interprocess/containers/string.hpp>			// String dentro da memória compartilhada
#include <boost/interprocess/allocators/allocator.hpp>		// Alocador para String na memória compartilhada

typedef boost::interprocess::allocator<char, boost::interprocess::managed_shared_memory::segment_manager> Alocador_char;
typedef boost::interprocess::basic_string<char, std::char_traits<char>, Alocador_char> mem_string;

class Comunicador
{
public:
    enum modo {ler, escrever};
    Comunicador (std::string p1, std::string p2, modo m);
    Comunicador (std::string nomeConexao);
    ~Comunicador ();
    std::string nome_conexao ();
    int n_processos ();
    template <class T> void criar_var (std::string nome);
    template <typename T> T ler_var (std::string nome);
    template <class T> void escrever_var (std::string nome, T valor);
    template <class T> void destruir_var (std::string nome);
    bool ready ();
    void done ();
private:
    modo _modo;
    std::string _conexao;
    int* _n_processos;
    boost::interprocess::managed_shared_memory _memoria;
    boost::interprocess::interprocess_mutex * _mutex;
    Comunicador & operator= (const Comunicador &) { return *this; }	// Cópia de objeto não permitida.
    Comunicador (const Comunicador &) {}
};

// Essas definições ai em baixo são feias mas tem que estar aqui e não no arquivo .cpp, infelizmente.
// http://www.parashift.com/c++-faq-lite/templates-defn-vs-decl.html

// especialização para usar o contêiner padrão String.
template <> void Comunicador::criar_var <std::string> (std::string nome);
template <> std::string Comunicador::ler_var <std::string> (std::string nome);
template <> void Comunicador::escrever_var <std::string> (std::string nome, std::string valor);
template <> void Comunicador::destruir_var <std::string> (std::string nome);

template <class T> void Comunicador::criar_var (std::string nome)
{
    _mutex->lock();
    _memoria.find_or_construct <T> (nome.c_str ()) ();
    _mutex->unlock();
}
template <typename T> T Comunicador::ler_var (std::string nome)
{
    T ret;
    _mutex->lock();
    std::pair <T *, std::size_t> v_pair;
    v_pair = _memoria.find <T> (nome.c_str ());
    if (!v_pair.first)
    {
        throw "Variável não encotrada na memória compartilhada";
    }
    ret = *v_pair.first;
    _mutex->unlock();
    return ret;
}
template <class T> void Comunicador::escrever_var (std::string nome, T valor)
{
    _mutex->lock();
    std::pair <T *, std::size_t> v_pair;
    v_pair = _memoria.find <T> (nome.c_str ());
    if (v_pair.first)
    {
        *v_pair.first = valor;
    }
    else
    {
        throw "Variável não encotrada na memória compartilhada";
    }
    _mutex->unlock();
}
template <class T> void Comunicador::destruir_var (std::string nome)
{
    _mutex->lock();
    _memoria.destroy <T> (nome.c_str ());
    _mutex->unlock();
}

#endif
