#pragma once
#include<iostream>
#include<string>
#include<sstream>

using namespace std;

class Comentario {
public:
	string id, autorId, contenido, fecha, postId, tipoAutor;
	int likes;
	//AutorID: ID del ususario o empresa que comenta
	//PostId: ID del post donde se comenta
	//TipoAutor: "Usuaro" o empresa

	//Sistema de respuestas (maximo 10 respuestas por comentario)
	string respuestasIds[10];
	int numRespuestas;

	//Usuarios que dieronlike (maximo 50)
	string usuariosLike[50];
	int numUsuariosLike;

	Comentario(string aid = "", string cont = "", string pid = "", string tip = "Usuario") {
		this->autorId = aid;
		this->contenido = cont;
		this->postId = pid;
		this->tipoAutor = tip;
		this->likes = 0;
		this->numRespuestas = 0;
		this->numUsuariosLike = 0;
	}

	void darLike(string usuarioId) {
		for (int  i = 0; i < numUsuariosLike; i++){
			if (usuariosLike[i] == usuarioId) {
				return;
			}
		}

		if (numUsuariosLike < 50) {
			usuariosLike[numUsuariosLike] = usuarioId;
			numUsuariosLike++;
			likes++;
		}
	}

	void quitarLike(string usuarioId) {
		for (int i = 0; i < numUsuariosLike; i++) {
			if (usuariosLike[i] == usuarioId) {
				for (int j = 0; j < numUsuariosLike - 1; j++) {
					usuariosLike[j] = usuariosLike[j + 1];
				}
				numUsuariosLike--;
				likes--; 
				return;
			}
		}
	}

	bool dioLike(string usuarioId) const {
		for (int i = 0; i < numUsuariosLike; i++) {
			if (usuariosLike[i] == usuarioId) {
				return true;
			}
		}
		return false;
	}

	void agregarRespuestaId(const string& respuestaId) {
		if (numRespuestas < 10) {
			respuestasIds[numRespuestas] = respuestaId;
			numRespuestas++;
		}
	}

	bool eliminarRespuestaId(const string& respuestaId) {
		for (int i = 0; i < numRespuestas; i++) {
			if (respuestasIds[i] == respuestaId) {
				for (int j = 0; j < numRespuestas - 1; j++) {
					respuestasIds[j] = respuestasIds[j + 1];
				}
				numRespuestas--;
				return true;
			}
		}
		return false;
	}

	bool tieneRespuestaId(const string& respuestaId) const {
		for (int i = 0; i < numRespuestas; i++) {
			if (respuestasIds[i] == respuestaId) {
				return true;
			}
		}
		return false;
	}

	string obtenerRespuestasString() const {
		stringstream ss;
		for (int i = 0; i < numRespuestas; i++) {
			ss << respuestasIds[i];
			if (i < numRespuestas - 1) { ss << ", "; }
		}
		return ss.str();
	}

	string toFileString() const {
		stringstream ss;
		ss << id << "|" << autorId << "|" << contenido << "|"
			<< fecha << "|" << likes << "|" << postId << "|" << tipoAutor << "|";

		for (int i = 0; i < numUsuariosLike; i++) {
			ss << usuariosLike[i];
			if (i < numUsuariosLike - 1) { ss << ","; }
		}
		ss << "|";

		for (int i = 0; i < numRespuestas; i++) {
			ss << respuestasIds[i];
			if (i < numRespuestas - 1) { ss << ","; }
		}
		return ss.str();
	}

	static Comentario fromFileString(const string& linea) {
		stringstream ss(linea);
		string id, autorId, contenido, fecha, likesStr, postId, tipoAutor, usuariosLikeStr, respuestasIdsStr;

		getline(ss, id, '|');
		getline(ss, autorId, '|');
		getline(ss, contenido, '|');
		getline(ss, fecha, '|');
		getline(ss, likesStr, '|');
		getline(ss, postId, '|');
		getline(ss, tipoAutor, '|');
		getline(ss, usuariosLikeStr, '|');
		getline(ss, respuestasIdsStr, '|');

		Comentario comentario(autorId, contenido, postId, tipoAutor);
		comentario.id = id;
		comentario.fecha = fecha;
		comentario.likes = stoi(likesStr);

		//Usuarios que dieron likes
		stringstream uls(usuariosLikeStr);
		string usuarioLike;
		while (getline(uls, usuarioLike, ',')) {
			if (!usuarioLike.empty() && comentario.numUsuariosLike < 50) {
				comentario.usuariosLike[comentario.numUsuariosLike] = usuarioLike;
				comentario.numUsuariosLike++;
			}
		}

		stringstream ris(respuestasIdsStr);
		string respuestaId;
		while (getline(ris,respuestaId,',')) {
			if (!respuestaId.empty() && comentario.numRespuestas < 10) {
				comentario.respuestasIds[comentario.numRespuestas] = respuestaId;
				comentario.numRespuestas++;
			}
		}
		return comentario;
	}

	void mostrar() const {
		cout << autorId;
		if (tipoAutor == "empresa") { cout << " [Empresa]"; }
		cout << " ( " << fecha << "):" << endl;
		cout << contenido << endl;
		cout << "Likes: " << likes;

		if (numRespuestas > 0) {
			cout << " | Respuestas: " << numRespuestas;
		}
		cout << endl;
	}
	bool operator==(const Comentario& otro) const { return id == otro.id; }

	friend ostream& operator<<(ostream& os, const Comentario& comentario) {
		comentario.mostrar();
		return os;
	}
};