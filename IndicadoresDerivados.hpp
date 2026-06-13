#ifndef INDICADORES_DERIVADOS_HPP
#define INDICADORES_DERIVADOS_HPP

#include "IndicadorSalud.hpp"
#include <iostream>

class IndicadorFisiologico final : public IndicadorSalud {
private:
    std::string tipoMedicion;

public:
    IndicadorFisiologico(std::string f, float v, std::string tipo) 
        : IndicadorSalud(f, v), tipoMedicion(tipo) {}

    void mostrarEvaluacion() const override {
        std::cout << "Fisiologico - " << tipoMedicion << " (" << fecha << "): " << valor << "\n";
    }
};

class IndicadorBioquimico final : public IndicadorSalud {
private:
    std::string tipoLipido;
    bool ayuno;

public:
    IndicadorBioquimico(std::string f, float v, std::string tipo, bool a)
        : IndicadorSalud(f, v), tipoLipido(tipo), ayuno(a) {}

    void mostrarEvaluacion() const override {
        std::cout << "Bioquimico - " << tipoLipido << " (" << fecha << ") Ayuno: " << ayuno << " - Valor: " << valor << "\n";
    }
};

#endif