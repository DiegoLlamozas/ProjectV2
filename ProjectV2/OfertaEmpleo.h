#pragma once
#include<iostream>
#include<string>
#include<sstream>
#include "OfertaEmpleo.h"
#include "Empresa.h"
#include "Notificacion.h"

using namespace std;

class OfertaEmpleo : public Notificacion {
public:
	OfertaEmpleo* oferta;
	Empresa* empresa;
	string ubicacion, requisitos, tipoContrato, Categoria;
	double salario;
	//Tipo contrato: "Tiempo completo", "Medio Tiempo", "Practicas"
	// Categoria: "Tegnologia", "Diseño", "Ventas", etc.

	OfertaEmpleo(OfertaEmpleo* ofertaId = nullptr, Empresa* empId = nullptr, string titulo = "", double sal = 0.0, string ubi = "", string cat = "Tegnologia") {
		Notificacion(nullptr, titulo, "empleo");
		this->oferta = ofertaId;
		this->empresa = empId;
		this->salario = sal;
		this->ubicacion = ubi;
		this->Categoria = cat;
		this->tipoContrato = "Tiempo Completo";
	}

	string toFileString() const override {
		stringstream ss;
		ss << id << "|" << usuarioDestino << "|" << mensaje << "|"
			<< fecha << "|" << (leida ? "true" : "false") << "|" << tipo << "|"
			<< empresa->getId() << "|" << salario << "|" << ubicacion << "|"
			<< requisitos << "|" << tipoContrato << "|" << Categoria;
		return ss.str();
	}

	/*
	static OfertaEmpleo fromFileString(const string& linea) {
		stringstream ss(linea);
		string id, usuarioDestino, mensaje, fecha, leidaStr, tipo;
		string empresaId, salarioStr, ubicacion, requisitos, tipoContrato, Categoria;

		getline(ss, id, '|');
		getline(ss, usuarioDestino, '|');
		getline(ss, mensaje, '|');
		getline(ss, fecha, '|');
		getline(ss, leidaStr, '|');
		getline(ss, tipo, '|');
		getline(ss, empresaId, '|');
		getline(ss, salarioStr, '|');
		getline(ss, ubicacion, '|');
		getline(ss, requisitos, '|');
		getline(ss, tipoContrato, '|');
		getline(ss, Categoria, '|');

		OfertaEmpleo oferta(empresaId, mensaje, stod(salarioStr), ubicacion, Categoria);
		oferta.id = id;
		oferta.usuarioDestino = usuarioDestino;
		oferta.fecha = fecha;
		oferta.leida = (leidaStr == "true");
		oferta.requisitos = requisitos;
		oferta.tipoContrato = tipoContrato;

		return oferta;
	}*/

	void mostrar() const override {
		cout << "Oferta Empleo - " << empresa->getId() << endl;
		cout << "  " << mensaje << endl;
		cout << "  Salario: $" << salario;
		cout << " | " << ubicacion;
		cout << " | " << tipoContrato;
		cout << " | " << Categoria;
		if (!leida) { cout << " [Nuevo]"; }
		cout << endl;
		if (!requisitos.empty()) {
			cout << " Requisitos: " << requisitos << endl;
		}
	}

	bool operator<(const OfertaEmpleo& otra) const { return salario < otra.salario; }
	bool operator>(const OfertaEmpleo& otra) const { return salario > otra.salario; }
	bool operator==(const OfertaEmpleo& otra) const { return id == otra.id; }

	friend ostream& operator<<(ostream& os, const OfertaEmpleo& oferta) {
		oferta.mostrar();
		return os;
	}

	string getId() { return id; }
};