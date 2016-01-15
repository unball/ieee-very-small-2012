/*
    @file Comunicador_robos.cpp

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
#include <Comunicador_robos.h>
Comunicador_robos::Comunicador_robos(std::string porta) : port(porta), serial(io, port){
	this->baud_rate = 57600;
	this->serial.set_option(boost::asio::serial_port_base::baud_rate(baud_rate));
}

Comunicador_robos::~Comunicador_robos () {

}

void Comunicador_robos::enviar_velocidades (Dados_Estrategia & _dados)
{

	/* Setup serial port for Xbee Explorer
	*  	Great reference on serial port programming in C++: http://www.webalice.it/fede.tft/serial_port/serial_port.html
	* 		Boost Asio reference on serial ports: http://www.boost.org/doc/libs/1_40_0/doc/html/boost_asio/overview/serial_ports.html
	*/
	unsigned char b;
	for (int i=0; i<3; i++) {
		b = 0;
		b = ler_velocidade (_dados, i, direita);
		serial.write_some (boost::asio::buffer(static_cast<void*>(&b),1));
		b = 0;
		b = ler_velocidade (_dados, i, esquerda);
		serial.write_some (boost::asio::buffer(static_cast<void*>(&b),1));
	}
}
	// Send packet through serial port
	/* Boost Asio has some shit called ConstBufferSequence (badly documented):
	* 		Someone else complaining: http://stackoverflow.com/questions/6202655/boost-asio-constbuffersequence-c-template-help
	* 		This buffer class implements it: http://www.boost.org/doc/libs/1_51_0/doc/html/boost_asio/reference/buffer.html
	* 		Everyone knows about its shitty docs: http://stackoverflow.com/questions/244453/best-documentation-for-boostasio
	*/

unsigned int Comunicador_robos::roda (unsigned int i) {
	switch (i) {
	case direita:
		return 2*2*2*2*2;
		break;
	case esquerda:
		return 0;
		break;
	default:
		return 0;
		break;
	}
	return i * 2*2*2*2;
}
unsigned int Comunicador_robos::robo (unsigned int i) {
	switch (i) {
	case 0:
		return 2*2*2*2*2*2;
		break;
	case 1:
		return 2*2*2*2*2*2*2;
		break;
	case 2:
		return (2*2*2*2*2*2 + 2*2*2*2*2*2*2);
		break;
	default:
		return 0;
		break;
	}
}
unsigned int Comunicador_robos::direcao (unsigned int i) {
	switch (i) {
	case frente:
		return 0;
		break;
	case traz:
		return 2*2*2*2;
		break;
	default:
		return 0;
		break;
	}
}
unsigned int Comunicador_robos::velocidade (unsigned int i) {
	if (i > 15) {
		return 15;
	}
	if (i < 0) {
		return 0;
	}
	return i;
}
unsigned char Comunicador_robos::ler_velocidade (Dados_Estrategia & _dados, unsigned int _robo, unsigned int _roda) {
	unsigned int _dir;
	double _vel;
	if (_roda == direita) {
		_vel = _dados.f_vel_roda_dir[_robo];
	} else {
		_vel = _dados.f_vel_roda_esq[_robo];
	}
	if (_vel > 0) {
		_dir = frente;
	} else {
		_dir = traz;
	}
	_vel = aparar_valor (0, 15, abs( _vel));
	std::cout << "\trobo " << _robo << "\troda " << _roda << "\tvel " << _vel  << "\tdirecao " << _dir << std::endl;
	unsigned char a = robo (_robo) + direcao (_dir) + roda (_roda) + velocidade (_vel);
	return a;
}