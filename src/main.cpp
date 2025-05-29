#include "InputManager.hpp"
#include "OutputManager.hpp"
#include <string>

int main() {
    InputManager& inputManager = InputManager::getInstance();
    OutputManager output;

    inputManager.readInputs();
    inputManager.printInputs();

    // Simulando os resultados
    double Lbf = 120.5;
    double Lb = 145.8;
    std::string mecanismoPredominante = "Troposcatter";

    output.printResults(Lbf, Lb, mecanismoPredominante);
    output.saveResultsToFile("saida.txt", Lbf, Lb, mecanismoPredominante);

    return 0;
}
