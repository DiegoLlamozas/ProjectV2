#pragma once
#include<iostream>
#include<string>
#include<sstream>
using namespace std;

class Notificacion {
public:
	string id, usuarioDestino, mensaje, fecha, tipo;
	bool leida;
	//tipo: general, empleo, menaje, conexion

	Notificacion(string uid = "", string msg = "", string tip = "general", string f = "") {
		this->usuarioDestino = uid;
		this->mensaje = msg;
		this->tipo = tip;
		this->fecha = f;
		this->leida = false;
	}

	virtual string toFileString() const {
		stringstream ss;
		ss << id << "|" << usuarioDestino << "|" << mensaje << "|"
			<< fecha << "|" << (leida ? "true" : "false") << "|" << tipo;
		return ss.str();

	}

	static Notificacion fromFileString(const string& linea) {
		stringstream ss(linea);
		string id, usuarioDestino, mensaje, fecha, leidaStr, tipo;

		getline(ss, id, '|');
		getline(ss, usuarioDestino, '|');
		getline(ss, mensaje, '|');
		getline(ss, fecha, '|');
		getline(ss, leidaStr, '|');
		getline(ss, tipo, '|');

		Notificacion notif(usuarioDestino, mensaje, tipo, fecha);
		notif.id = id;
		notif.leida = (leidaStr == "true");

		return notif;
	}

	void marcarComoLeida() { leida = true; }

	virtual void mostrar() const {
		cout << "[" << fecha << "] ";
		if (!leida) { cout << "[Nuevo]"; }
		cout << mensaje;
		if (!tipo.empty()) { cout << " [" << tipo << "]"; }
	}

	bool operator==(const Notificacion& otra) const { return id == otra.id; }

	friend ostream& operator<<(ostream& os, const Notificacion& notif) {
		notif.mostrar();
		return os;
	}
};