#pragma once
#include "Utilidades.h"

template<typename T>
class Pila {
private:
    struct Nodo {
        T dato;
        Nodo* siguiente;
        Nodo(T d, Nodo* sig = nullptr) : dato(d), siguiente(sig) {}
    };

    Nodo* tope;
    uint longitud;

public:
    Pila() : tope(nullptr), longitud(0) {}

    ~Pila() {
        while (tope != nullptr) {
            Nodo* aux = tope;
            tope = tope->siguiente;
            delete aux;
        }
    }

    void push(T elem) {
        Nodo* nuevo = new Nodo(elem, tope);
        tope = nuevo;
        longitud++;
    }

    void pop() {
        if (!empty()) {
            Nodo* aux = tope;
            tope = tope->siguiente;
            delete aux;
            longitud--;
        }
    }

    T top() {
        if (empty()) {
            throw runtime_error("Error: Pila vacia");
        }
        return tope->dato;
    }

    bool empty() {
        return tope == nullptr;
    }

    uint size() {
        return longitud;
    }

    void mostrar() {
        if (empty()) {
            cout << "[Pila vacia]" << endl;
            return;
        }

        Nodo* aux = tope;
        cout << "Tope -> ";
        while (aux != nullptr) {
            cout << aux->dato << " ";
            aux = aux->siguiente;
        }
        cout << endl;
    }
};