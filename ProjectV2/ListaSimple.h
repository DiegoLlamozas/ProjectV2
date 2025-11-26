#pragma once
#include"Utilidades.h"

template<typename T>
class ListaS {
public:
	struct Nodo {
		T elem;
		Nodo* sig;
		Nodo(T elemento = NADA, Nodo* siguiente = nullptr) {
			this->elem = elemento;
			this->sig = siguiente;
		}
	};
	typedef function<int(T, T)> Comp;
	Nodo* ini;
	uint lon;
	Comp comparar;
public:
	ListaS() {
		this->ini = nullptr;
		this->lon = 0;
		this->comparar = [](T a, T b) { 
			if (a < b) { return -1; }
			if (a > b) { return 1; }
			return 0; };
	}

	ListaS(Comp Comparar) {
		this->ini = nullptr;
		this->lon = 0;
		this->comparar = Comparar;
	}

	~ListaS(){
		
		while (ini != nullptr) {
			Nodo* aux = ini;
			aux = ini;
			ini = ini->sig;
			delete aux;
		}
	}

	uint longitud() { return lon; }
	bool esVacia() { return lon == 0; }

	void agregarInicial(T elem) {
		Nodo* nuevo = new Nodo(elem, ini);
		if (nuevo != nullptr) {
			ini = nuevo;
			lon++;
		}
	}
	void agregarPos(T elem, uint pos){
		if (pos > lon) { return; }
		if (pos == 0) {
			agregarInicial(elem);
		}
		else {
			Nodo* aux = ini;
			for (uint i = 0; i < pos - 1; i++) {
				aux = aux->sig;
			}
			Nodo* nuevo = new Nodo(elem, aux->sig);
			if (nuevo != nullptr) {
				aux->sig = nuevo;
				lon++;
			}
		}
	}

	void agregarFinal(T elem){ agregarPos(elem, lon); }

	void modificarInicial(T elem){ if (lon > 0) { ini->elem = elem; } }
	void modificarPos(T elem, uint pos){
		if (pos < lon) {
			Nodo* aux = ini;
			for (uint i = 0; i < pos; i++) {
				aux = aux->sig;
			}
			aux->elem = elem;
		}
	}

	void modificarFinal(T elem) { modificarPos(elem, lon - 1); }

	void eliminarInicial(){
		if (lon > 0) {
			Nodo* aux = ini;
			ini = ini->sig;
			delete aux;
			lon--;
		}
	}

	void eliminarPos(uint pos) {
		if (pos < lon) {
			if (pos == 0) {
				eliminarInicial();
			}
			else {
				Nodo* anterior = ini;
				for (uint i = 0; i < pos - 1; i++) {
					anterior = anterior->sig;
				}
				Nodo* eliminar = anterior->sig;
				anterior->sig = eliminar->sig;
				delete eliminar;
				lon--;
			}
		}
	}

	void eliminarFinal(){
		if (lon > 0) {
			if (lon == 1) {
				eliminarInicial();
			}
			else {
				Nodo* aux = ini;
				while (aux->sig != nullptr && aux->sig->sig != nullptr) {
					aux = aux->sig;
				}
				Nodo* nodoEliminar = aux->sig;
				aux->sig = nullptr;
				delete nodoEliminar;
				lon--;
			}
		}
	}

	T obtenerPos(uint pos){
		if (pos < lon) {
			Nodo* aux = ini;
			for (uint i = 0; i < pos; i++) {
				aux = aux->sig;
			}
			return aux->elem;
		}
		else {
			return T();
		}
	}

	T* obtenerDireccionPos(uint Pos){
		if (pos < lon) {
			Nodo* aux = ini;
			for (uint i = 0; i < pos; i++) {
				aux = aux->sig;
			}
			return &(aux->elem);
		}
		return nullptr;
	}
	T obtenerInicial(){ return obtenerPos(0); }
	T obtenerFinal(){ return obtenerPos(lon - 1); }

	T buscar(T elem){
		Nodo* aux = ini;
		while (aux != nullptr) {
			if (comparar(aux->elem, elem) == 0) {
				return aux->elem;
			}
			aux = aux->sig;
		}
		return NADA;
	}
};