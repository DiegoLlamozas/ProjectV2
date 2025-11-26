// ArbolBinario.h
#pragma once
#include <iostream>
#include <functional>
using namespace std;

template <class T>
class NodoBinario {
public:
    T elemento;
    NodoBinario* izq;
    NodoBinario* der;

    NodoBinario(T elem) : elemento(elem), izq(nullptr), der(nullptr) {}
};

template <class T>
class ArbolBinario {
private:
    NodoBinario<T>* raiz;
    function<void(T)> procesar;

    // Métodos recursivos privados
    void _insertarSimple(NodoBinario<T>*& nodo, T e) {
        if (nodo == nullptr) {
            nodo = new NodoBinario<T>(e);
            return;
        }

        // Inserción simple: izquierda si hay espacio, sino derecha
        if (nodo->izq == nullptr) {
            _insertarSimple(nodo->izq, e);
        }
        else if (nodo->der == nullptr) {
            _insertarSimple(nodo->der, e);
        }
        else {
            // Si ambos hijos están llenos, insertar recursivamente en izquierda
            _insertarSimple(nodo->izq, e);
        }
    }

    void _enOrden(NodoBinario<T>* nodo) {
        if (nodo == nullptr) return;
        _enOrden(nodo->izq);
        procesar(nodo->elemento);
        _enOrden(nodo->der);
    }

    void _preOrden(NodoBinario<T>* nodo) {
        if (nodo == nullptr) return;
        procesar(nodo->elemento);
        _preOrden(nodo->izq);
        _preOrden(nodo->der);
    }

    void _postOrden(NodoBinario<T>* nodo) {
        if (nodo == nullptr) return;
        _postOrden(nodo->izq);
        _postOrden(nodo->der);
        procesar(nodo->elemento);
    }

    int _cantidad(NodoBinario<T>* nodo) {
        if (nodo == nullptr) return 0;
        return 1 + _cantidad(nodo->izq) + _cantidad(nodo->der);
    }

    int _altura(NodoBinario<T>* nodo) {
        if (nodo == nullptr) return 0;
        int alturaIzq = _altura(nodo->izq);
        int alturaDer = _altura(nodo->der);
        return 1 + (alturaIzq > alturaDer ? alturaIzq : alturaDer);
    }

    bool _buscar(NodoBinario<T>* nodo, T e) {
        if (nodo == nullptr) return false;
        if (nodo->elemento == e) return true;
        return _buscar(nodo->izq, e) || _buscar(nodo->der, e);
    }

    void _limpiar(NodoBinario<T>*& nodo) {
        if (nodo == nullptr) return;
        _limpiar(nodo->izq);
        _limpiar(nodo->der);
        delete nodo;
        nodo = nullptr;
    }

public:
    ArbolBinario(function<void(T)> proc) : procesar(proc), raiz(nullptr) {}

    ~ArbolBinario() {
        _limpiar(raiz);
    }

    // Métodos públicos
    void insertarSimple(T e) {
        _insertarSimple(raiz, e);
    }

    void enOrden() {
        _enOrden(raiz);
    }

    void preOrden() {
        _preOrden(raiz);
    }

    void postOrden() {
        _postOrden(raiz);
    }

    int cantidad() {
        return _cantidad(raiz);
    }

    int altura() {
        return _altura(raiz);
    }

    bool buscar(T e) {
        return _buscar(raiz, e);
    }

    bool estaVacio() {
        return raiz == nullptr;
    }

    void limpiar() {
        _limpiar(raiz);
    }
};