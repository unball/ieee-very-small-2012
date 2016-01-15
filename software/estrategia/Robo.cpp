/*
    @file Robo.cpp

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
#include <Robo.h>
Robo::Robo () {
	vel_roda_dir = 0;
	vel_roda_esq = 0;
}
void Robo::aplica_forca(Vetor3 forca) {
	this->v_forca_res = this->v_forca_res + forca;
}
void Robo::zerar_forcas() {
	this->v_forca_res = Vetor3().nulo();
}
void Robo::forca_para_vel_rodas() {
	Vetor3 a, an, at, n, t, vt;
	double _vt, _an;
	a = 1. / this->massa * this->v_forca_res; 
	
	t = this->v_normal;
	n = v3_Z().vetorial(this->v_normal);

	n = n.unitario();
	t = t.unitario();

	at = a.escalar(t) * t;
	an = a.escalar(n) * n;

	vt = this->v_vel_linear + at;
	
	_vt = vt.modulo();
	_an = an.modulo();

	_vt = aparar_valor(-MAX_V, MAX_V, _vt);

	this->vel_roda_dir = _vt + this->f_raio * _an / _vt;
	this->vel_roda_esq = _vt - this->f_raio * _an / _vt;

	this->vel_roda_dir = aparar_valor(-MAX_V, MAX_V, this->vel_roda_dir);
	this->vel_roda_esq = aparar_valor(-MAX_V, MAX_V, this->vel_roda_esq);
}
void Robo::vel_linear_angular_para_vel_rodas() {
	this->vel_roda_dir = this->f_vel_linear + 1 * this->f_vel_angular;
	this->vel_roda_esq = this->f_vel_linear - 1 * this->f_vel_angular;
}
void Robo::vel_rodas_para_vel_linear_angular() {
	this->f_vel_linear = (this->vel_roda_dir + this->vel_roda_esq ) / 2.;
	this->f_vel_angular = this->vel_roda_dir / 1.;
}