// ArbolBB.h
#pragma once
#include <iostream>
#include <functional>
using namespace std;

template <class T>
class NodoABB {
public:
    T elemento;
    NodoABB* izq;
    NodoABB* der;

    NodoABB(T elem) : elemento(elem), izq(nullptr), der(nullptr) {}
};

template <class T>
class ArbolBB {
private:
    NodoABB<T>* raiz;
    function<int(T, T)> comparar;
    function<void(T)> procesar;

    // Métodos recursivos privados
    bool _insertar(NodoABB<T>*& nodo, T e) {
        if (nodo == nullptr) {
            nodo = new NodoABB<T>(e);
            return true;
        }
        else {
            int r = comparar(nodo->elemento, e);
            if (r == 0) return false;
            else if (r < 0) {
                return _insertar(nodo->der, e);
            }
            else {
                return _insertar(nodo->izq, e);
            }
        }
    }

    bool _buscar(NodoABB<T>* nodo, T e) {
        if (nodo == nullptr) return false;
        else {
            int r = comparar(nodo->elemento, e);
            if (r == 0) return true;
            else if (r < 0) {
                return _buscar(nodo->der, e);
            }
            else {
                return _buscar(nodo->izq, e);
            }
        }
    }

    void _enOrden(NodoABB<T>* nodo) {
        if (nodo == nullptr) return;
        _enOrden(nodo->izq);
        procesar(nodo->elemento);
        _enOrden(nodo->der);
    }

    void _preOrden(NodoABB<T>* nodo) {
        if (nodo == nullptr) return;
        procesar(nodo->elemento);
        _preOrden(nodo->izq);
        _preOrden(nodo->der);
    }

    void _postOrden(NodoABB<T>* nodo) {
        if (nodo == nullptr) return;
        _postOrden(nodo->izq);
        _postOrden(nodo->der);
        procesar(nodo->elemento);
    }

    int _cantidad(NodoABB<T>* nodo) {
        if (nodo == nullptr) return 0;
        else {
            int ci = _cantidad(nodo->izq);
            int cd = _cantidad(nodo->der);
            return 1 + ci + cd;
        }
    }

    int _altura(NodoABB<T>* nodo) {
        if (nodo == nullptr) return 0;
        else {
            int ai = _altura(nodo->izq);
            int ad = _altura(nodo->der);
            return 1 + (ai > ad ? ai : ad);
        }
    }

    T _minimo(NodoABB<T>* nodo) {
        if (nodo->izq == nullptr) return nodo->elemento;
        else return _minimo(nodo->izq);
    }

    T _maximo(NodoABB<T>* nodo) {
        if (nodo->der == nullptr) return nodo->elemento;
        else return _maximo(nodo->der);
    }

    bool _eliminar(NodoABB<T>*& nodo, T e) {
        if (nodo == nullptr) return false;
        else {
            int r = comparar(nodo->elemento, e);
            if (r < 0) {
                return _eliminar(nodo->der, e);
            }
            else if (r > 0) {
                return _eliminar(nodo->izq, e);
            }
            else { // Encontrado
                if (nodo->der == nullptr && nodo->izq == nullptr) {
                    // Caso 1: Nodo hoja
                    delete nodo;
                    nodo = nullptr;
                    return true;
                }
                else if (nodo->izq == nullptr) {
                    // Caso 2: Solo hijo derecho
                    NodoABB<T>* temp = nodo;
                    nodo = nodo->der;
                    delete temp;
                    return true;
                }
                else if (nodo->der == nullptr) {
                    // Caso 3: Solo hijo izquierdo
                    NodoABB<T>* temp = nodo;
                    nodo = nodo->izq;
                    delete temp;
                    return true;
                }
                else {
                    // Caso 4: Dos hijos
                    NodoABB<T>* aux = nodo->der;
                    while (aux->izq != nullptr) {
                        aux = aux->izq;
                    }
                    nodo->elemento = aux->elemento;
                    return _eliminar(nodo->der, aux->elemento);
                }
            }
        }
    }

public:
    ArbolBB(function<int(T, T)> comp, function<void(T)> proc)
        : comparar(comp), procesar(proc), raiz(nullptr) {
    }

    ~ArbolBB() {
        // Podemos agregar liberación de memoria si es necesario
    }

    // Métodos públicos
    bool insertar(T e) {
        return _insertar(raiz, e);
    }

    bool buscar(T e) {
        return _buscar(raiz, e);
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

    T minimo() {
        return _minimo(raiz);
    }

    T maximo() {
        return _maximo(raiz);
    }

    bool eliminar(T e) {
        return _eliminar(raiz, e);
    }

    bool estaVacio() {
        return raiz == nullptr;
    }
};