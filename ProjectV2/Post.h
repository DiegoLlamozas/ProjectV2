#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <ctime>
#include <iomanip>

using namespace std;

class Post {
private:
    string idPost;
    string contenido;
    chrono::system_clock::time_point fechaPublicacion;

public:
    Post() {
        this->idPost = " ";
        this->contenido = " ";
        this->fechaPublicacion = chrono::system_clock::now();
    }
    Post(string pIdPost, string pContenido, chrono::system_clock::time_point pFehcaPublicacion) {
        this->idPost = pIdPost;
        this->contenido = pContenido;
        this->fechaPublicacion = pFehcaPublicacion;
    }

    Post(string pIdPost, string pContenido, const string& fechaString) {
        this->idPost = pIdPost;
        this->contenido = pContenido;
        this->fechaPublicacion = parseDateString(fechaString);
    }

    void setIdPost(const string& pIdPost) { this->idPost = pIdPost; }
    void setContenido(const string& pContenido) { this->contenido = pContenido; }

    string getIdPost() const { return  this->idPost; }
    string getContenido() const { return this->contenido; }
    chrono::system_clock::time_point getFechaPublicacion() const { return this->fechaPublicacion; }

    string mostrarPost() {
        time_t time = chrono::system_clock::to_time_t(fechaPublicacion);

        // Convert time_t to tm (local time) - safe version
        tm timeinfo;
        localtime_s(&timeinfo, &time);

        // Format date and time - FIX: pass pointer to timeinfo
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo); // Note the & here
        string fechaStr(buffer);

        stringstream ss;
        ss << "Post numero " << idPost << ":\n";
        ss << contenido << "\n";
        ss << "Fecha de publicacion: " << fechaStr;
        return ss.str();
    }

    chrono::system_clock::time_point parseDateString(const string& dateStr) {
        // Try different date formats
        tm tm = {};
        istringstream ss(dateStr);

        // Try format: YYYY-MM-DD HH:MM:SS
        ss >> get_time(&tm, "%Y-%m-%d %H:%M:%S");
        if (ss.fail()) {
            // Try format: YYYY/MM/DD HH:MM:SS
            ss.clear();
            ss.str(dateStr);
            ss >> get_time(&tm, "%Y/%m/%d %H:%M:%S");
        }
        if (ss.fail()) {
            // Try format: MM/DD/YYYY HH:MM:SS
            ss.clear();
            ss.str(dateStr);
            ss >> get_time(&tm, "%m/%d/%Y %H:%M:%S");
        }
        if (ss.fail()) {
            // If all parsing fails, use current time
            cout << "Warning: Could not parse date string '" << dateStr
                << "'. Using current time instead." << endl;
            return chrono::system_clock::now();
        }

        time_t time = mktime(&tm);
        return chrono::system_clock::from_time_t(time);
    }
};