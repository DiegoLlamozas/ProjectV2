#pragma once
#include "Utilidades.h"

template<typename T>
class Cola {
private:
    struct Nodo {
        T dato;
        Nodo* siguiente;
        Nodo(T d, Nodo* sig = nullptr) : dato(d), siguiente(sig) {}
    };

    Nodo* frente;
    Nodo* fin;
    uint longitud;

public:
    Cola() : frente(nullptr), fin(nullptr), longitud(0) {}

    ~Cola() {
        while (frente != nullptr) {
            Nodo* aux = frente;
            frente = frente->siguiente;
            delete aux;
        }
        fin = nullptr;
    }

    void enqueue(T elem) {
        Nodo* nuevo = new Nodo(elem);
        if (empty()) {
            frente = fin = nuevo;
        }
        else {
            fin->siguiente = nuevo;
            fin = nuevo;
        }
        longitud++;
    }

    void dequeue() {
        if (!empty()) {
            Nodo* aux = frente;
            frente = frente->siguiente;
            delete aux;
            longitud--;

            if (frente == nullptr) {
                fin = nullptr;
            }
        }
    }

    T front() {
        if (empty()) {
            throw runtime_error("Error: Cola vacia");
        }
        return frente->dato;
    }

    bool empty() {
        return frente == nullptr;
    }

    uint size() {
        return longitud;
    }

    void mostrar() {
        if (empty()) {
            cout << "[Cola vacia]" << endl;
            return;
        }

        Nodo* aux = frente;
        cout << "Frente -> ";
        while (aux != nullptr) {
            cout << aux->dato << " ";
            aux = aux->siguiente;
        }
        cout << "<- Fin" << endl;
    }
};