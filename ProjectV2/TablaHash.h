#pragma once
#include "ListaSimple.h"

template<typename K, typename V>
class ListaPares {
private:
	struct Par{
		K clave;
		V valor;
		Par* siguiente;
		Par(K k, V v) {
			this->clave = k;
			this->valor = v;
			this->siguiente = nullptr;
		}
	};

	Par* cabeza;
	int tamaño;

public:
	ListaPares() {
		this->cabeza = nullptr;
		this->tamaño = 0;
	}

	~ListaPares() {
		while (cabeza != nullptr) {
			Par* temp = cabeza;
			cabeza = cabeza->siguiente;
			delete temp;
		}
	}

	void insertar(K clave, V valor) {
		Par* actual = cabeza;
		while (actual != nullptr) {
			if (actual->clave == clave) {
				actual->valor = valor;
				return;
			}
			actual = actual->siguiente;
		}

		Par* nuevo = new Par(clave, valor);
		nuevo->siguiente = cabeza;
		cabeza = nuevo;
		tamaño++;
	}

	V* buscar(K clave) {
		Par* actual = cabeza;
		while (actual != nullptr) {
			if (actual->clave == clave) {
				return &(actual->valor);
			}
			actual = actual->siguiente;
		}
		return nullptr;
	}

	bool eliminar(K clave) {
		if (cabeza == nullptr) { return false; }

		//Caso especial: eliminar cabeza
		if (cabeza->clave == clave) {
			Par* temp = cabeza;
			cabeza = cabeza->siguiente;
			delete temp;
			tamaño--;
			return true;
		}

		//Busca en el resto de la lista
		Par* actual = cabeza;
		while (actual->siguiente != nullptr) {
			if (actual->siguiente->clave == clave) {
				Par* temp = actual->siguiente;
				actual->siguiente = temp->siguiente;
				delete temp;
				tamaño--;
				return true;
			}
			actual = actual->siguiente;
		}
		return false;
	}

	void obtenerValores(ListaS<V>& resultado) {
		Par* actual = cabeza;
		while (actual != nullptr) {
			resultado.agregarFinal(actual->valor);
			actual = actual->siguiente;
		}
	}

	bool estaVacia() const { return cabeza == nullptr; }
	int getTamaño() const { return tamaño; }
};

template<typename K, typename V>
class TablaHash {
private:
	ListaPares<K, V>** tabla; //Arreglo con punteros
	int capacidad;
	int tamañoTotal;

	//La tabla hash guardara los numeros de los Strings
	int funcionHash(const K& clave) const {
		int hash = 0;
		for (char c : clave) {
			hash = (hash * 31 + c) % capacidad;
		}
		return hash;
	}

public:
	TablaHash(int cap = 10) {
		this->capacidad = cap;
		this->tamañoTotal = 0;

		tabla = new ListaPares<K, V>*[capacidad];
		for (int i = 0; i < capacidad; i++) {
			tabla[i] = new ListaPares<K, V>();
		}
	}

	~TablaHash() {
		for (int i = 0; i < capacidad; i++) {
			delete tabla[i];
		}
		delete tabla;
	}

	void insertar(const K& clave, const V& valor) {
		int indice = funcionHash(clave);
		tabla[indice]->insertar(clave, valor);
		tamañoTotal++;
	}

	V* buscar(const K& clave) {
		int indice = funcionHash(clave);
		return tabla[indice]->buscar(clave);
	}

	bool eliminar(const K& clave) {
		int indice = funcionHash(clave);
		if (tabla[indice]->eliminar(clave)) {
			tamañoTotal--;
			return  true;
		}
		return false;
	}

	ListaS<V> ObtenerTodos() {
		ListaS<V> todos;
		for (int i = 0; i < capacidad; i++){
			tabla[i]->obtenerValores(todos);
		}
		return todos;
	}

	int getTamaño() const { return tamañoTotal; }
	bool estaVacia() const { return tamañoTotal == 0; }
	int getCapacidad() const { return capacidad; }

	void mostrarDistribucion() {
		cout << "=== Distribucion HASH ===" << endl;
		for (int i = 0; i < capacidad; i++) {

				cout << "Cubeta " << i << ": " << tabla[i]->getTamaño() << " elementos" << endl;
			
		}
	}
};