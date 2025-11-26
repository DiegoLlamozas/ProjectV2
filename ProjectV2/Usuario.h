// Usuario.h - VERSIÓN SIMPLIFICADA
#pragma once
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Usuario {
public:
    string id;
    string nombre;
    string email;
    string profesion;

    string habilidades[10];  // Máximo 10 habilidades
    int numHabilidades;

    Usuario(string i = "", string n = "", string e = "", string p = "")
        : id(i), nombre(n), email(e), profesion(p), numHabilidades(0) {
    }

    // Métodos para manejar habilidades
    void agregarHabilidad(const string& habilidad) {
        if (numHabilidades < 10) {
            habilidades[numHabilidades] = habilidad;
            numHabilidades++;
        }
    }

    bool eliminarHabilidad(const string& habilidad) {
        for (int i = 0; i < numHabilidades; i++) {
            if (habilidades[i] == habilidad) {
                // Mover las habilidades restantes
                for (int j = i; j < numHabilidades - 1; j++) {
                    habilidades[j] = habilidades[j + 1];
                }
                numHabilidades--;
                return true;
            }
        }
        return false;
    }

    bool tieneHabilidad(const string& habilidad) const {
        for (int i = 0; i < numHabilidades; i++) {
            if (habilidades[i] == habilidad) {
                return true;
            }
        }
        return false;
    }

    int cantidadHabilidades() const {
        return numHabilidades;
    }

    string obtenerHabilidadesString() const {
        stringstream ss;
        for (int i = 0; i < numHabilidades; i++) {
            ss << habilidades[i];
            if (i < numHabilidades - 1) ss << ", ";
        }
        return ss.str();
    }

    virtual string toFileString() const {
        stringstream ss;
        ss << id << "|" << nombre << "|" << email << "|" << profesion << "|";

        // Guardar habilidades
        for (int i = 0; i < numHabilidades; i++) {
            ss << habilidades[i];
            if (i < numHabilidades - 1) ss << ",";
        }
        return ss.str();
    }

    static Usuario fromFileString(const string& linea) {
        stringstream ss(linea);
        string id, nombre, email, profesion, habilidadesStr;

        getline(ss, id, '|');
        getline(ss, nombre, '|');
        getline(ss, email, '|');
        getline(ss, profesion, '|');
        getline(ss, habilidadesStr, '|');

        Usuario u(id, nombre, email, profesion);

        // Parsear habilidades
        stringstream hs(habilidadesStr);
        string habilidad;
        while (getline(hs, habilidad, ',')) {
            if (!habilidad.empty()) u.agregarHabilidad(habilidad);
        }

        return u;
    }

    bool operator==(const Usuario& otro) const { return id == otro.id; }
    bool operator<(const Usuario& otro) const { return id < otro.id; }
    bool operator>(const Usuario& otro) const { return id > otro.id; }

    virtual string getClave() const { return email; }

    friend ostream& operator<<(ostream& os, const Usuario& u) {
        os  << u.nombre << "|" << u.email << "|" << u.profesion;
        if (u.numHabilidades > 0) {
            os << "\n  Habilidades: " << u.obtenerHabilidadesString();
        }
        return os;
    }
};