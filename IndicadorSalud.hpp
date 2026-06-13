#ifndef INDICADOR_SALUD_HPP
#define INDICADOR_SALUD_HPP

#include <string>
#include <exception>

class ValorMedicoInvalido : public std::exception {
public:
    const char* what() const noexcept override {
        return "Error: Valor medico invalido.";
    }
};

class IndicadorSalud {
protected:
    std::string fecha;
    float valor;

public:
    IndicadorSalud(std::string f, float v) : fecha(f), valor(v) {
        if (v < 0) {
            throw ValorMedicoInvalido();
        }
    }
    
    virtual ~IndicadorSalud() = default;

    virtual void mostrarEvaluacion() const = 0;
};

#endif