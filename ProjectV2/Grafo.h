// Grafo.h - CON ARREGLO SIMPLE
#pragma once
#include <iostream>
using namespace std;

template<class T>
class Grafo {
private:
    class Arco;

    class Vertice {
    public:
        T info;
        Arco* ady[50];  //  Arreglo simple de arcos
        int numArcos;

        Vertice(T info = T()) : info(info), numArcos(0) {
            for (int i = 0; i < 50; i++) ady[i] = nullptr;
        }

        ~Vertice() {
            for (int i = 0; i < numArcos; i++) {
                delete ady[i];
            }
        }
    };

    class Arco {
    public:
        T info;
        int verticeDestino;

        Arco(int vDest, T infoArco = T()) : verticeDestino(vDest), info(infoArco) {}
    };

    Vertice* vertices[100];  //  Arreglo de vértices
    int numVertices;
    T valorVacio;

public:
    Grafo(T vacio = T()) : valorVacio(vacio), numVertices(0) {
        for (int i = 0; i < 100; i++) vertices[i] = nullptr;
    }

    ~Grafo() {
        for (int i = 0; i < numVertices; i++) {
            delete vertices[i];
        }
    }

    // Operaciones del Vértice
    int adicionarVertice(T info) {
        if (numVertices < 100) {
            vertices[numVertices] = new Vertice(info);
            return numVertices++;
        }
        return -1;
    }

    int cantidadVertices() {
        return numVertices;
    }

    T obtenerVertice(int v) {
        if (v >= 0 && v < numVertices) {
            return vertices[v]->info;
        }
        return valorVacio;
    }

    void modificarVertice(int v, T info) {
        if (v >= 0 && v < numVertices) {
            vertices[v]->info = info;
        }
    }

    // Operaciones del Arco
    int adicionarArco(int vOrigen, int vDestino, T infoArco = T()) {
        if (vOrigen >= 0 && vOrigen < numVertices &&
            vDestino >= 0 && vDestino < numVertices) {

            Vertice* vert = vertices[vOrigen];
            if (vert->numArcos < 50) {
                vert->ady[vert->numArcos] = new Arco(vDestino, infoArco);
                return vert->numArcos++;
            }
        }
        return -1;
    }

    int cantidadArcos(int v) {
        if (v >= 0 && v < numVertices) {
            return vertices[v]->numArcos;
        }
        return 0;
    }

    T obtenerArco(int v, int posArco) {
        if (v >= 0 && v < numVertices) {
            Vertice* vert = vertices[v];
            if (posArco >= 0 && posArco < vert->numArcos) {
                return vert->ady[posArco]->info;
            }
        }
        return valorVacio;
    }

    void modificarArco(int v, int posArco, T info) {
        if (v >= 0 && v < numVertices) {
            Vertice* vert = vertices[v];
            if (posArco >= 0 && posArco < vert->numArcos) {
                vert->ady[posArco]->info = info;
            }
        }
    }

    int obtenerVerticeDestino(int v, int posArco) {
        if (v >= 0 && v < numVertices) {
            Vertice* vert = vertices[v];
            if (posArco >= 0 && posArco < vert->numArcos) {
                return vert->ady[posArco]->verticeDestino;
            }
        }
        return -1;
    }

    bool existeArco(int vOrigen, int vDestino) {
        if (vOrigen >= 0 && vOrigen < numVertices) {
            Vertice* vert = vertices[vOrigen];
            for (int i = 0; i < vert->numArcos; i++) {
                if (vert->ady[i]->verticeDestino == vDestino) {
                    return true;
                }
            }
        }
        return false;
    }

    void mostrarGrafo() {
        cout << "=== GRAFO ===" << endl;
        for (int i = 0; i < numVertices; i++) {
            Vertice* vert = vertices[i];
            cout << "Vertice " << i << " (" << vert->info << ") -> ";

            for (int j = 0; j < vert->numArcos; j++) {
                Arco* arc = vert->ady[j];
                cout << "[" << arc->verticeDestino << ":" << arc->info << "] ";
            }
            cout << endl;
        }
    }

    void recorridoBFS(int inicio) {
        if (inicio < 0 || inicio >= numVertices) return;

        bool visitados[100] = { false };
        int cola[100];
        int frente = 0, fin = 0;

        cola[fin++] = inicio;
        visitados[inicio] = true;

        cout << "BFS desde vertice " << inicio << ": ";

        while (frente < fin) {
            int actual = cola[frente++];
            cout << actual << " ";

            Vertice* vert = vertices[actual];
            for (int i = 0; i < vert->numArcos; i++) {
                int vecino = vert->ady[i]->verticeDestino;
                if (!visitados[vecino]) {
                    visitados[vecino] = true;
                    cola[fin++] = vecino;
                }
            }
        }
        cout << endl;
    }
};