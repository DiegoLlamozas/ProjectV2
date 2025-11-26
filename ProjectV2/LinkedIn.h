// LinkedIn.h
#pragma once
#include "TablaHash.h"
#include "ArbolABB.h"
#include "ArbolBinario.h"
#include "Grafo.h"
#include "Pila.h"
#include "Cola.h"
#include "Usuario.h"
#include "Empresa.h"
#include "ExperienciaLaboral.h"
#include "Curriculum.h"
#include "Notificacion.h"
#include "OfertaEmpleo.h"
#include "Postulacion.h"
#include "Comentario.h"
#include "FileMananger.h"
#include <iostream>
using namespace std;

class LinkedIn {
private:
    // === ESTRUCTURAS PRINCIPALES ===

    // 1. TABLAS HASH - Búsqueda rápida
    TablaHash<string, Usuario> usuarios;
    TablaHash<string, Empresa> empresas;
    TablaHash<string, Curriculum> curriculums;

    // 2. ÁRBOLES - Ordenamiento y jerarquías
    ArbolBB<OfertaEmpleo>* ofertasPorSalario;
    ArbolBinario<Comentario>* comentariosGlobales;

    // 3. GRAFO - Red de conexiones
    Grafo<string>* redSocial;

    // 4. PILAS Y COLAS - Gestión temporal
    Cola<Notificacion> notificaciones;
    Pila<Postulacion> postulacionesRecientes;

    // Contadores para IDs
    int contadorUsuarios;
    int contadorEmpresas;
    int contadorOfertas;

    // === FUNCIONES LAMBDA ===
    function<void(OfertaEmpleo)> mostrarOferta;
    function<void(Comentario)> mostrarComentario;
    function<int(OfertaEmpleo, OfertaEmpleo)> compararSalario;

public:
    LinkedIn() : usuarios(100), empresas(50), curriculums(100),
        contadorUsuarios(1), contadorEmpresas(1), contadorOfertas(1) {

        // Inicializar lambdas
        mostrarOferta = [](OfertaEmpleo oferta) {
            cout << oferta << endl;
            };

        mostrarComentario = [](Comentario coment) {
            cout << coment << endl;
            };

        compararSalario = [](OfertaEmpleo a, OfertaEmpleo b) -> int {
            if (a.salario < b.salario) return -1;
            if (a.salario > b.salario) return 1;
            return 0;
            };

        // Crear estructuras dinámicas
        ofertasPorSalario = new ArbolBB<OfertaEmpleo>(compararSalario, mostrarOferta);
        comentariosGlobales = new ArbolBinario<Comentario>(mostrarComentario);
        redSocial = new Grafo<string>("");
    }

    ~LinkedIn() {
        delete ofertasPorSalario;
        delete comentariosGlobales;
        delete redSocial;
    }

    // === MÉTODOS DE USUARIO ===
    string registrarUsuario(string nombre, string email, string profesion) {
        string id = "U" + to_string(contadorUsuarios++);
        Usuario nuevoUsuario(id, nombre, email, profesion);
        usuarios.insertar(email, nuevoUsuario);

        // Agregar al grafo de conexiones
        redSocial->adicionarVertice(id);

        // Crear curriculum vacío
        Curriculum cv(id);
        curriculums.insertar(id, cv);

        return id;
    }

    Usuario* buscarUsuario(string email) {
        return usuarios.buscar(email);
    }

    // === MÉTODOS DE EMPRESA ===
    string registrarEmpresa(string nombre, string industria, string tamano = "Mediana") {
        string id = "E" + to_string(contadorEmpresas++);
        Empresa nuevaEmpresa(id, nombre, industria, tamano);
        empresas.insertar(id, nuevaEmpresa);
        return id;
    }

    Empresa* buscarEmpresa(string id) {
        return empresas.buscar(id);
    }

    // === MÉTODOS DE CURRICULUM ===
    bool agregarExperienciaUsuario(string usuarioId, string empresaId, string puesto,
        string fechaInicio, string fechaFin = "", string descripcion = "") {
        Curriculum* cv = curriculums.buscar(usuarioId);
        if (cv == nullptr) return false;

        ExperienciaLaboral exp(usuarioId, empresaId, puesto, fechaInicio, fechaFin, descripcion);
        exp.id = "EXP" + to_string(cv->numExperiencias + 1);
        cv->agregarExperiencia(exp);

        return true;
    }

    bool agregarHabilidadUsuario(string usuarioId, string habilidad) {
        Curriculum* cv = curriculums.buscar(usuarioId);
        if (cv == nullptr) return false;

        cv->agregarHabilidad(habilidad);
        return true;
    }

    void mostrarCurriculum(string usuarioId) {
        Curriculum* cv = curriculums.buscar(usuarioId);
        if (cv != nullptr) {
            cout << *cv << endl;
        }
    }

    // === MÉTODOS DE CONEXIONES ===
    bool conectarUsuarios(string usuarioId1, string usuarioId2, string tipoConexion = "Colega") {
        // Buscar índices en el grafo
        int idx1 = -1, idx2 = -1;
        for (int i = 0; i < redSocial->cantidadVertices(); i++) {
            string id = redSocial->obtenerVertice(i);
            if (id == usuarioId1) idx1 = i;
            if (id == usuarioId2) idx2 = i;
        }

        if (idx1 != -1 && idx2 != -1) {
            redSocial->adicionarArco(idx1, idx2, tipoConexion);
            redSocial->adicionarArco(idx2, idx1, tipoConexion); // Conexión bidireccional
            return true;
        }
        return false;
    }

    void mostrarConexionesUsuario(string usuarioId) {
        int idx = -1;
        for (int i = 0; i < redSocial->cantidadVertices(); i++) {
            if (redSocial->obtenerVertice(i) == usuarioId) {
                idx = i;
                break;
            }
        }

        if (idx != -1) {
            cout << "Conexiones de " << usuarioId << ":" << endl;
            for (int i = 0; i < redSocial->cantidadArcos(idx); i++) {
                int destino = redSocial->obtenerVerticeDestino(idx, i);
                string tipo = redSocial->obtenerArco(idx, i);
                string idDestino = redSocial->obtenerVertice(destino);
                cout << "-> " << idDestino << " [" << tipo << "]" << endl;
            }
        }
    }

    // === MÉTODOS DE OFERTAS EMPLEO ===
    string publicarOfertaEmpleo(string empresaId, string titulo, double salario,
        string ubicacion, string requisitos = "", string categoria = "Tecnologia") {
        string id = "OF" + to_string(contadorOfertas++);
        OfertaEmpleo nuevaOferta(empresaId, titulo, salario, ubicacion, categoria);
        nuevaOferta.id = id;
        nuevaOferta.requisitos = requisitos;

        ofertasPorSalario->insertar(nuevaOferta);
        return id;
    }

    void mostrarOfertasOrdenadasSalario() {
        cout << "=== OFERTAS ORDENADAS POR SALARIO ===" << endl;
        ofertasPorSalario->enOrden();
    }

    void mostrarOfertasEmpresa(string empresaId) {
        cout << "=== OFERTAS DE EMPRESA " << empresaId << " ===" << endl;
        // Recorrer y filtrar ofertas por empresa
        // (Implementación simplificada)
        ofertasPorSalario->enOrden(); // Por ahora mostramos todas
    }

    // === MÉTODOS DE POSTULACIONES ===
    bool postularOferta(string usuarioId, string ofertaId, string mensaje = "") {
        Postulacion post(usuarioId, ofertaId);
        post.id = "POST" + to_string(postulacionesRecientes.size() + 1);
        post.fechaPostulacion = "01/12/2023"; // Fecha actual (simulada)
        post.mensajePersonalizado = mensaje;

        postulacionesRecientes.push(post);

        // Crear notificación para la empresa
        Notificacion notif("", "Nueva postulación a tu oferta", "postulacion");
        notificaciones.enqueue(notif);

        return true;
    }

    void mostrarPostulacionesRecientes() {
        cout << "=== POSTULACIONES RECIENTES ===" << endl;
        Pila<Postulacion> temp = postulacionesRecientes;
        while (!temp.empty()) {
            cout << temp.top() << endl;
            temp.pop();
        }
    }

    // === MÉTODOS DE NOTIFICACIONES ===
    void agregarNotificacion(string usuarioDestino, string mensaje, string tipo = "general") {
        Notificacion notif(usuarioDestino, mensaje, tipo);
        notificaciones.enqueue(notif);
    }

    void procesarNotificaciones() {
        cout << "=== NOTIFICACIONES PENDIENTES ===" << endl;
        while (!notificaciones.empty()) {
            Notificacion notif = notificaciones.front();
            cout << notif << endl;
            notificaciones.dequeue();
        }
    }

    // === MÉTODOS DE COMENTARIOS ===
    void agregarComentario(string autorId, string contenido, string postId, string tipoAutor = "usuario") {
        Comentario coment(autorId, contenido, postId, tipoAutor);
        coment.id = "COM" + to_string(comentariosGlobales->cantidad() + 1);
        coment.fecha = "01/12/2023"; // Fecha actual (simulada)

        comentariosGlobales->insertarSimple(coment);
    }

    void mostrarComentarios() {
        cout << "=== COMENTARIOS ===" << endl;
        comentariosGlobales->enOrden();
    }

    // === MÉTODOS DE ESTADÍSTICAS ===
    void mostrarEstadisticas() {
        cout << "=== ESTADÍSTICAS LINKEDIN ===" << endl;
        cout << "Usuarios registrados: " << usuarios.getTamaño() << endl;
        cout << "Empresas registradas: " << empresas.getTamaño() << endl;
        cout << "Ofertas de empleo: " << ofertasPorSalario->cantidad() << endl;
        cout << "Conexiones en red: " << redSocial->cantidadVertices() << " usuarios" << endl;
        cout << "Postulaciones recientes: " << postulacionesRecientes.size() << endl;
        cout << "Notificaciones pendientes: " << notificaciones.size() << endl;
    }

    // === MÉTODOS DE PERSISTENCIA (simplificados) ===
    bool guardarDatos() {
        cout << "Datos guardados correctamente (simulación)" << endl;
        return true;
    }

    bool cargarDatos() {
        cout << "Datos cargados correctamente (simulación)" << endl;
        return true;
    }
};