#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <exception>

class ValorMedicoInvalido : public std::exception {
public:
    const char* what() const noexcept override { 
        return "Error: El valor medico ingresado rompe el invariante (ej. es negativo).";
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

class IndicadorFisiologico final : public IndicadorSalud { 
private:
    std::string tipoMedicion;

public:
    IndicadorFisiologico(std::string f, float v, std::string tipo) 
        : IndicadorSalud(f, v), tipoMedicion(tipo) {} 


    void mostrarEvaluacion() const override {
        std::cout << "Evaluacion Fisiologica (" << tipoMedicion << ") en " 
                  << fecha << ": " << valor << "\n";
    }
};

class Paciente {
private:
    std::string nombre;
    int edad;

public:
    Paciente(std::string n, int e) : nombre(n), edad(e) {}
    friend std::ostream& operator<<(std::ostream& os, const Paciente& p) {
        os << "Paciente: " << p.nombre << ", Edad: " << p.edad;
        return os;
    }
};

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

int main() {
    try {
        Paciente p1("Leonidas", 20);
        PerfilDeRiesgo perfil(p1, 85);
        auto indic1 = std::make_unique<IndicadorFisiologico>("2026-06-13", 120.5, "Presion Sistolica");
        
        perfil.agregarIndicador(std::move(indic1));
        perfil.evaluarHistorial();
    } catch (const ValorMedicoInvalido& e) {
        std::cerr << e.what() << "\n";
    }

    return 0;
}