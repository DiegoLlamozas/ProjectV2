#pragma once
#include<iostream>
#include<string>
#include<sstream>

using namespace std;

class Empresa {
public: 
	string id, nombre, industria, tamano, ubicacion, descripcion;
	string empleados[50];
	int numEmpleados;

	Empresa(string i = "0", string n = "", string ind = "", string t = "Mediana") {
		this->id = i;
		this->nombre = n;
		this->industria = ind;
		this->tamano = t;
		this->numEmpleados = 0;
	}

	void contratarEmpleado(const string& usuarioID) {
		if (numEmpleados < 50) {
			empleados[numEmpleados] = usuarioID;
			numEmpleados++;
		}
	}

	bool despedirEmpleado(const string& usuarioID) {
		for (int i = 0; i < numEmpleados; i++) {
			if (empleados[i] == usuarioID) {
				for (int j = i; j < numEmpleados - 1; j++){
					empleados[j] = empleados[j + 1];
				}
				numEmpleados--;
				return true;
			}
		}
		return false;
	}

	bool tieneEmpleado(const string& usuarioID) const {
		for (int i = 0; i < numEmpleados; i++) {
			if (empleados[i] == usuarioID) { return true; }
		}
		return false;
	}

	int cantidadEmpleados() const { return numEmpleados; }

	string obtenreEmpleadosString() const {
		stringstream ss;
		for (int i = 0; i < numEmpleados; i++) {
			ss << empleados[i];
			if (i < numEmpleados - 1) { ss << ", "; }
		}
		return ss.str();
	}

	string toFileString() const {
		stringstream ss;
		ss << id << "|" << nombre << "|" << industria << "|" << tamano << "|" << ubicacion << "|" << descripcion << "|";

		for (int i = 0; i < numEmpleados; i++) {
			ss << empleados[i];
			if (i < numEmpleados - 1) { ss << ","; }
		}
		return ss.str();
	}

	static Empresa fromFileString(const string& linea) {
		stringstream ss(linea);
		string id, nombre, industria, tamano, ubicacion, descripcion, empleadosStr;

		getline(ss, id, '|');
		getline(ss, nombre, '|');
		getline(ss, industria, '|');
		getline(ss, tamano, '|');
		getline(ss, ubicacion, '|');
		getline(ss, descripcion, '|');
		getline(ss, empleadosStr, '|');

		Empresa emp(id, nombre, industria, tamano);
		emp.ubicacion = ubicacion;
		emp.descripcion = descripcion;

		stringstream es(empleadosStr);
		string empleadoID;
		while (getline(es,empleadoID,',')) {
			if (!empleadoID.empty()) { emp.contratarEmpleado(empleadoID); }
		}
		return emp;
	}

	bool operator==(const Empresa& otra) const { return id == otra.id; }
	bool operator<(const Empresa& otra) const { return nombre < otra.nombre; }

	friend ostream& operator<<(ostream& os, const Empresa& emp) {
		os << emp.nombre << " | " << emp.industria << " | " << emp.tamano;
		if (!emp.ubicacion.empty()) {
			os << " | " << emp.ubicacion;
		} 
		if (emp.numEmpleados > 0) {
			os << "\n Empleados" << emp.cantidadEmpleados();
		}
		return os;
	}

};