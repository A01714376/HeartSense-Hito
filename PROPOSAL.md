Domain: Healthcare Data Management 
Problem: Medical professionals need to evaluate disparate cardiovascular risk indicators (biochemical and physiological) to form a unified patient risk profile. 
Why OOP?: Object-Oriented Programming is essential here because medical indicators share common traits (dates, values, validation rules) but require distinct evaluation logic. 
Polymorphism allows us to treat a blood pressure reading and a cholesterol test uniformly through a base (IndicadorSalud) interface, while RAII ensures secure, leak-free management of sensitive patient records in memory. 
