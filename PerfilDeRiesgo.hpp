#ifndef PERFIL_RIESGO_HPP
#define PERFIL_RIESGO_HPP

#include "Paciente.hpp"
#include "IndicadoresDerivados.hpp"
#include <vector>
#include <memory>

class PerfilDeRiesgo {
private:
    Paciente paciente;
    std::vector<std::unique_ptr<IndicadorSalud>> historial;
    int scoreRiesgo;

public:
    PerfilDeRiesgo(Paciente p, int score) : paciente(p), scoreRiesgo(score) {}

    void agregarIndicador(std::unique_ptr<IndicadorSalud> indicador) {
        historial.push_back(std::move(indicador));
    }

    void evaluarHistorial() const noexcept {
        std::cout << paciente << "\n";
        for (const auto& ind : historial) {
            ind->mostrarEvaluacion();
        }
    }

    bool operator<(const PerfilDeRiesgo& otro) const noexcept {
        return this->scoreRiesgo < otro.scoreRiesgo;
    }
};

#endif