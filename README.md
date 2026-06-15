# HeartSense - Sistema de Evaluación de Riesgo Cardiovascular

1. Propuesta del Problema 
Las enfermedades cardiovasculares requieren el análisis de múltiples indicadores médicos. El problema radica en que los datos (bioquímicos y fisiológicos) suelen evaluarse de forma aislada.HeartSense utiliza la Programación Orientada a Objetos para crear un perfil de riesgo unificado. El polimorfismo nos permite tratar distintas pruebas médicas bajo una misma interfaz abstracta (`IndicadorSalud`), mientras que el paradigma RAII asegura el manejo seguro y sin fugas de memoria de los historiales de los pacientes.

 2. Instrucciones de Compilación y Ejecución
El programa está diseñado bajo los estándares de C++14 

Comando estricto de compilación 
`g++ -std=c++14 -Wall main.cpp -o heart_sense.exe`

Ejecución (Windows):
.\heart_sense.exe

Salida esperada:
Paciente: Leonidas | Edad: 20
Fisiologico - Presion Sistolica (2026-06-13): 120.5
Bioquimico - Colesterol LDL (2026-06-13) Ayuno: 1 - Valor: 195
El perfil 1 tiene mayor riesgo que el perfil 2.
Error: Valor medico invalido.

 3. Concept Checklist & Decisiones de Diseño

* **Rule of Zero & Smart Pointers:** Opte deliberadamente por la *Rule of Zero*. Al utilizar exclusivamente `std::unique_ptr` para la memoria dinámica y contenedores estándar como `std::vector` y `std::string`, delegamos la gestión de memoria al compilador. No hay uso de `new` ni `delete` crudos, garantizando un código *leak-free*.
* **Relaciones de Clases (Ownership):** Implemente **Composición**. `PerfilDeRiesgo` es dueño estricto de su `Paciente` y del ciclo de vida de los punteros `IndicadorSalud`. Si el perfil se destruye, los datos médicos también.
* **Encapsulamiento e Invariantes:** Todo el estado de las clases está oculto (`private` o `protected`). En el constructor de `IndicadorSalud`, protegemos el invariante lanzando una excepción si se intenta ingresar un valor médico negativo.
* **Runtime Polymorphism & Virtual Destructor:** La clase base `IndicadorSalud` hace uso de un destructor virtual `virtual ~IndicadorSalud() = default` para evitar el *slicing* de objetos, y un método virtual puro que la vuelve abstracta. El despacho dinámico ocurre en `PerfilDeRiesgo::evaluarHistorial()`. Las clases derivadas usan explícitamente `override` y `final`.
* **Exception Handling & RAII Safety:** Cree la excepción derivada `ValorMedicoInvalido` para atrapar datos erróneos en los límites seguros del bloque `try-catch` en el `main`. Los métodos de solo lectura están marcados con `noexcept`.
* **Operator Overloading:** Se sobrecargó el operador de inserción `friend operator<<` para imprimir el expediente del `Paciente` de forma canónica, y el operador de comparación `operator<` en `PerfilDeRiesgo` para jerarquizar la severidad clínica.

