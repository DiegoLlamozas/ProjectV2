#pragma once
#include<iostream>
#include<string>
#include<sstream>

using namespace std;

class ExperienciaLaboral {
public:
	string id, usuarioId, empresaId, puesto, fechaInicio, fechaFin, descripcion;
	bool actualmenteTrabajando;

	ExperienciaLaboral(string uid = "", string empId = "", string p = "", string inicio = "", string fin = "", string desc = "") {
		this->usuarioId = uid;
		this->empresaId = empId;
		this->puesto = p;
		this->fechaInicio = inicio;
		this->fechaFin = fin;
		this->descripcion = desc;
		this->actualmenteTrabajando = fin.empty();
	}

	string toFileString() const {
		stringstream ss;
		ss << id << "|" << usuarioId << "|" << empresaId << "|" << puesto << "|"
			<< fechaInicio << "|" << fechaFin << "|" << descripcion << "|"
			<< (actualmenteTrabajando ? "True" : "false");
		return ss.str();
	}

	static ExperienciaLaboral fromFileString(const string& linea) {
		stringstream ss(linea);
		string id, usuarioId, empresaId, puesto, fechaInicio, fechaFin, descripcion, actualStr;

		getline(ss, id, '|');
		getline(ss, usuarioId, '|');
		getline(ss, empresaId, '|');
		getline(ss, puesto, '|');
		getline(ss, fechaInicio, '|');
		getline(ss, fechaFin, '|');
		getline(ss, descripcion, '|');
		getline(ss, actualStr, '|');

		ExperienciaLaboral exp(usuarioId, empresaId, puesto, fechaInicio, fechaFin, descripcion);
		exp.id = id;
		exp.actualmenteTrabajando = (actualStr == "true");

		return exp;
	}

	int calcularDuracionMeses() const {
		//Para calcular diracion (modificar)
		if (fechaInicio.empty()) { return 0; }

		//Asumir formato MM/AAAA
		if (fechaFin.empty() || actualmenteTrabajando) {
			return 12;//Si trabaja actualmente
		}
		return 6; //Duracion de trabajo normal

	}

	bool operator==(const ExperienciaLaboral& otra) const { return id == otra.id; }

	friend ostream& operator<<(ostream& os, const ExperienciaLaboral& exp) {
		os << exp.puesto << " en " << exp.empresaId;
		os << " (" << exp.fechaInicio << " - ";
		if (exp.actualmenteTrabajando) {
			os << "Actual";
		} else {
			os << exp.fechaFin;
		}
		os << ")";
		if (!exp.descripcion.empty()) {
			os << "\n " << exp.descripcion;
		}
		return os;
	}

};