#pragma once
#include<iostream>
#include<string>
#include<sstream>
#include"ExperienciaLaboral.h"

using namespace std;

class Curriculum {
public:
	string usuarioId;
	ExperienciaLaboral experiencias[10];
	int numExperiencias;
	string habilidades[15];
	int numHabilidades;
	string educacion;
	string resumen;

	Curriculum(string uid = "") {
		this->usuarioId = uid;
		this->numExperiencias = 0;
		this->numHabilidades = 0;
	}

	void agregarExperiencia(const ExperienciaLaboral& exp) {
		if (numExperiencias < 10) {
			experiencias[numExperiencias] = exp;
			numExperiencias++;
		}
	}

	bool eliminarExperiencia(const string& expId) {
		for (int i = 0; i < numExperiencias; i++) {
			if (experiencias[i].id == expId) {
				for (int j = 0; j < numExperiencias; j++) {
					experiencias[j] = experiencias[j + 1];
				}
				numExperiencias--;
				return true;
			}
		}
		return false;
	}

	void agregarHabilidad(const string& habilidad) {
		if (numHabilidades < 15) {
			habilidades[numHabilidades] = habilidad;
			numHabilidades++;
		}
	}

	bool eliminarHabilidad(const string& habilidad){
		for (int i = 0; i < numHabilidades; i++) {
			if (habilidades[i] == habilidad) {
				for (int j = 0; j < numHabilidades - 1; j++) {
					habilidades[j] = habilidades[j + 1];
				}
				numHabilidades--;
				return true;
			}
		}
		return false;
	}

	string obtenerHabilidadesString() const {
		stringstream ss;
		for (int i = 0; i < numHabilidades; i++){
			ss << habilidades[i];
			if (i < numHabilidades - 1) { ss << ", "; }
		}
		return ss.str();
	}

	int experienciaTotalMeses() const {
		int total = 0;
		for (int i = 0; i < numExperiencias; i++) {
			total += experiencias[i].calcularDuracionMeses();
		}
		return total;
	}

	string toFileString() const {
		stringstream ss;
		ss << usuarioId << "|" << educacion << "|" << resumen << "|";

		//Guardar experiencias
		for (int i = 0; i < numExperiencias; i++) {
			ss << experiencias[i].toFileString();
			if (i < numExperiencias - 1) { ss << ";"; }
		}
		ss << "|";

		//Guardar Habilidades
		for (int i = 0; i < numHabilidades; i++) {
			ss << habilidades[i];
			if (i < numHabilidades - 1) { ss << ","; }
		}
		return ss.str();
	}

	static Curriculum fromFileString(const string& linea) {
		stringstream ss(linea);
		string usuarioId, educacion, resumen, experienciasStr, habilidadesStr;

		getline(ss,usuarioId , '|');
		getline(ss,educacion , '|');
		getline(ss,resumen , '|');
		getline(ss,experienciasStr , '|');
		getline(ss,habilidadesStr , '|');

		Curriculum cv(usuarioId);
		cv.educacion = educacion;
		cv.resumen = resumen;
		
		//Parsear experiencias
		stringstream es(experienciasStr);
		string expLinea;
		while (!expLinea.empty()) {
			ExperienciaLaboral exp = ExperienciaLaboral::fromFileString(expLinea);
			cv.agregarExperiencia(exp);
		}
		
		//Parsear habilidades
		stringstream hs(habilidadesStr);
		string habilidad;
		while (getline(hs,habilidad,',')) {
			if (!habilidad.empty()) { cv.agregarHabilidad(habilidad); }
		}
		return cv;
	}

	friend ostream& operator<<(ostream& os, const Curriculum& cv) {
		os << "Curriculum de " << cv.usuarioId;
		os << "\nEducacion: " << cv.educacion;
		os << "\nResumen: " << cv.resumen;
		os << "\nExperiencia total: " << cv.experienciaTotalMeses() << " meses";

		if (cv.numExperiencias > 0) {
			os << "\nExperiencias:";
			for (int i = 0; i < cv.numExperiencias; i++) {
				os << "\n " << (i + 1) << ". " << cv.experiencias[i];
			}
		}

		if (cv.numHabilidades > 0) {
			os << "\nHabilidades: " << cv.obtenerHabilidadesString();
		}
		return os;
	}

};