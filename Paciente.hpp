#ifndef PACIENTE_HPP
#define PACIENTE_HPP

#include <string>
#include <iostream>

class Paciente {
private:
    std::string nombre;
    int edad;

public:
    Paciente(std::string n, int e) : nombre(n), edad(e) {}

    friend std::ostream& operator<<(std::ostream& os, const Paciente& p) {
        os << "Paciente: " << p.nombre << " | Edad: " << p.edad;
        return os;
    }
};

#endif