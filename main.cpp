#include "PerfilDeRiesgo.hpp"
#include <iostream>

int main() {
    try {
        Paciente p1("Leonidas", 20);
        PerfilDeRiesgo perfil1(p1, 85);

        auto indic1 = std::make_unique<IndicadorFisiologico>("2026-06-13", 120.5, "Presion Sistolica");
        auto indic2 = std::make_unique<IndicadorBioquimico>("2026-06-13", 195.0, "Colesterol LDL", true);
        
        perfil1.agregarIndicador(std::move(indic1));
        perfil1.agregarIndicador(std::move(indic2));
        
        perfil1.evaluarHistorial();

        Paciente p2("Juan", 21);
        PerfilDeRiesgo perfil2(p2, 45);

        if (perfil2 < perfil1) {
            std::cout << "El perfil 1 tiene mayor riesgo que el perfil 2.\n";
        }

        auto indicInvalido = std::make_unique<IndicadorFisiologico>("2026-06-13", -10.0, "Error");

    } catch (const ValorMedicoInvalido& e) {
        std::cerr << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Excepcion general: " << e.what() << "\n";
    }

    return 0;
}
