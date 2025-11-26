#pragma once
#include<iostream>
#include<string>
#include<sstream>

using namespace std;

class Postulacion {
public:
	string id, usuarioId, ofertaId, fechaPostulacion, estado, mensajePersonalizado, cvAdjunto;
	//Estado: "Enviada", "Vista", "Entrevista", "Rechazada", "Aceptada"
	//vcAdjunto: Ruta al archivo CV o ID del curriculum

	Postulacion(string uid = "", string oid = "") {
		this->usuarioId = uid;
		this->ofertaId = oid;
		this->estado = "Enviado";
		this->fechaPostulacion = "";
	}

	string toFileString() const {
		stringstream ss;
		ss << id << "|" << usuarioId << "|" << ofertaId << "|"
			<< fechaPostulacion << "|" << estado << "|"
			<< mensajePersonalizado << "|" << cvAdjunto;
		return ss.str();
	}

	static Postulacion fromFileString(const string& linea) {
		stringstream ss(linea);
		string id, usuarioId, oferta, fechaPostulacion, estado, mensajePersonalizado, cvAdjunto;

		getline(ss, id, '|');
		getline(ss, usuarioId, '|');
		getline(ss, oferta, '|');
		getline(ss, fechaPostulacion, '|');
		getline(ss, estado, '|');
		getline(ss, mensajePersonalizado, '|');
		getline(ss, cvAdjunto, '|');

		Postulacion post(usuarioId, oferta);
		post.id = id;
		post.fechaPostulacion = fechaPostulacion;
		post.estado = estado;
		post.mensajePersonalizado = mensajePersonalizado;
		post.cvAdjunto = cvAdjunto;

		return post;
	}

	bool estaActiva() const { return estado == "Enviada" || estado == "Vista" || estado == "Enrevista"; }

	void avanzarEstado() {
		if (estado == "Enviada") { estado = "Vista"; }
		else if (estado == "Vista") { estado = "Entrevista"; }
		else if (estado == "Entrevista") {estado = "Aceptada";}
	}

	void rechazar() { estado = "Rechazada"; }

	bool operator==(const Postulacion& otra) const {
		return usuarioId == otra.usuarioId && ofertaId == otra.ofertaId;
	}

	friend ostream& operator<<(ostream& os, const Postulacion& post) {
		os << "Postulacion de " << post.usuarioId << " a " << post.ofertaId;
		os << "\n Estado: " << post.fechaPostulacion;
		os << " | Fecha: " << post.fechaPostulacion;
		if (!post.mensajePersonalizado.empty()) {
			os << "\n  Mensaje: " << post.mensajePersonalizado;
		}
		return os;
	}
};