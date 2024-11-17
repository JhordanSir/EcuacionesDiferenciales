#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;
// Parámetros iniciales
const double t0 = 0;           // Tiempo inicial
const double tf = 100;         // Tiempo final (en días)
const double dt = 1;         // Paso temporal
const double P0 = 0;           // Progreso inicial del proyecto (%)
const double C0 = 100;       // Costo inicial del proyecto
const double v0 = 1;         // Velocidad inicial (porcentaje por día) - Reducida para hacer más pronunciada la curva de aprendizaje
const double alpha = 10;      // Factor de influencia de factores externos - Mayor sensibilidad a cambios externos
const double betha = 0.4;       // Factor de aprendizaje - Aumentado para hacer que el progreso se acelere a medida que aumenta el progreso

double velocidadSimple(double t, double P, double F){
    return v0;
}
// Función de velocidad
double velocidadFactores(double t, double P, double F) {
    return v0 * (1 + alpha * F);
}

double velocidadCurva(double t, double P, double F) {
    return v0 * (1 + betha * P);
}


// Método de Euler
int main() {
    // Vector de tiempo
    vector<double> t;
    for (double i = t0; i <= tf; i += dt) {
        t.push_back(i);
    }

    // Vectores de progreso y costo
    vector<double> P(t.size(), 0);
    vector<double> C(t.size(), 0);
    P[0] = P0;
    C[0] = C0;

    // Simulación
    for (size_t i = 0; i < t.size() - 1; ++i) {
        // Simular un cambio en los requisitos en el día 50
        double F = (t[i] >= 50) ? 0.5 : 0;
        
        P[i + 1] = P[i] + dt * velocidadFactores(t[i], P[i], F);
        C[i + 1] = C[i] + dt * 100 * velocidadFactores(t[i], P[i], F);  // Suponiendo un costo de 100 por unidad de progreso
    }

    // Imprimir los resultados
    ofstream outFile("resultados.csv");
    outFile << "Tiempo (días),Progreso (%),Costo\n";
    for (size_t i = 0; i < t.size(); ++i) {
        outFile << fixed << setprecision(1) << t[i] << "," << P[i] << "," << C[i] << "\n";
    }

    cout << "Simulación completada. Los resultados se han guardado en 'resultados.txt'.\n";

    return 0;
}
