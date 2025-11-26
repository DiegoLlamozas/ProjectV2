#include "LinkedIn.h"
#include <iostream>
using namespace std;

void testSistemaCompleto() {
    cout << "=== SISTEMA LINKEDIN - PRUEBA COMPLETA ===" << endl;

    LinkedIn linkedin;

    cout << "\n1. REGISTRO DE USUARIOS:" << endl;
    string anaId = linkedin.registrarUsuario("Ana Garcia", "ana@email.com", "Desarrolladora");
    string carlosId = linkedin.registrarUsuario("Carlos Lopez", "carlos@email.com", "Diseñador");
    string mariaId = linkedin.registrarUsuario("Maria Torres", "maria@email.com", "Gerente");

    cout << "Usuarios registrados: Ana, Carlos, Maria" << endl;

    cout << "\n2. REGISTRO DE EMPRESAS:" << endl;
    string techId = linkedin.registrarEmpresa("Tech Solutions", "Tecnologia", "Mediana");
    string designId = linkedin.registrarEmpresa("Design Studio", "Diseño", "Pequeña");

    cout << "\n3. CURRICULUMS:" << endl;
    linkedin.agregarExperienciaUsuario(anaId, techId, "Desarrolladora Junior", "01/2022", "12/2022");
    linkedin.agregarExperienciaUsuario(anaId, designId, "Desarrolladora Frontend", "01/2023", "");
    linkedin.agregarHabilidadUsuario(anaId, "C++");
    linkedin.agregarHabilidadUsuario(anaId, "JavaScript");

    cout << "Curriculum de Ana:" << endl;
    linkedin.mostrarCurriculum(anaId);

    cout << "\n4. RED DE CONEXIONES:" << endl;
    linkedin.conectarUsuarios(anaId, carlosId, "Colegas");
    linkedin.conectarUsuarios(anaId, mariaId, "Amigos");
    linkedin.conectarUsuarios(carlosId, mariaId, "Familia");

    linkedin.mostrarConexionesUsuario(anaId);

    cout << "\n5. OFERTAS DE EMPLEO:" << endl;
    linkedin.publicarOfertaEmpleo(techId, "Desarrollador Senior", 5000.0, "Lima", "C++, Python, SQL");
    linkedin.publicarOfertaEmpleo(designId, "Diseñador UX/UI", 3500.0, "Arequipa", "Figma, Adobe XD");
    linkedin.publicarOfertaEmpleo(techId, "Practicante Desarrollo", 1500.0, "Lima", "Estudiante últimos ciclos");

    linkedin.mostrarOfertasOrdenadasSalario();

    cout << "\n6. POSTULACIONES:" << endl;
    linkedin.postularOferta(anaId, "OF1", "Interesada en la posición senior");
    linkedin.postularOferta(carlosId, "OF2", "Me encanta el diseño UX/UI");

    linkedin.mostrarPostulacionesRecientes();

    cout << "\n7. NOTIFICACIONES:" << endl;
    linkedin.agregarNotificacion(anaId, "Carlos quiere conectarse contigo", "conexion");
    linkedin.agregarNotificacion(techId, "Nueva postulación recibida", "postulacion");

    linkedin.procesarNotificaciones();

    cout << "\n8. COMENTARIOS:" << endl;
    linkedin.agregarComentario(anaId, "Excelente oferta de trabajo!", "OF1");
    linkedin.agregarComentario(techId, "Gracias por el interés Ana!", "OF1", "empresa");
    linkedin.agregarComentario(carlosId, "¿Ofrecen trabajo remoto?", "OF1");

    linkedin.mostrarComentarios();

    cout << "\n9. ESTADÍSTICAS FINALES:" << endl;
    linkedin.mostrarEstadisticas();

    cout << "\n=== PRUEBA COMPLETADA EXITOSAMENTE ===" << endl;
}

int main() {
    cout << " LINKEDIN - SISTEMA COMPLETO " << endl;
    cout << "===================================" << endl;

    testSistemaCompleto();

    cout << "\n===================================" << endl;
    cout << "¡PROYECTO TERMINADO EXITOSAMENTE! " << endl;
    cout << "Estructuras implementadas:" << endl;
    cout << "TablaHash, ArbolBB, ArbolBinario, Grafo" << endl;
    cout << "Pila, Cola, ListaSimple" << endl;
    cout << "8 clases de abstracción completas" << endl;
    cout << "Sistema LinkedIn funcional" << endl;

    system("pause");
    return 0;
}