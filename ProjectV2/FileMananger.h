#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include"ListaSimple.h"

using namespace std;

class FileManager {
public:
	static bool guardarLineas(const string& filename,  ListaS<string>& lineas) {
		ofstream archivo(filename);
		if (!archivo.is_open()) { return false; }

		for (uint i = 0; i < lineas.longitud(); i++) {
			string linea = lineas.obtenerPos(i);
			archivo << linea << "\n";
		}
		archivo.close(); 
		return true;
	}

	static ListaS<string> cargarLineas(const string& filename) {
		ListaS<string> lineas;
		ifstream archivo(filename);
		if (archivo.is_open()) {
			string linea;
			while (getline(archivo,linea)) {
				if (!linea.empty()) {
					lineas.agregarFinal(linea);
				}
			}
			archivo.close();
		}
		return lineas;
	}

	static bool archivoExiste(const string& filename) {
		ifstream archivo(filename);
		return archivo.good();
	}
};