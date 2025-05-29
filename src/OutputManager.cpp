/*
 * OutputManager.cpp
 *
 *  Created on: 29 de mai. de 2025
 *      Author: Lucas Machado
 */


#include "OutputManager.hpp"
#include <iostream>
#include <fstream>

void OutputManager::printResults(double Lbf, double Lb, const std::string& mecanismoPredominante) {
	 std::cout << "==== Resultados ====" << std::endl;
	    std::cout << "Perda em espaço livre (Lbf): " << Lbf << " dB" << std::endl;
	    std::cout << "Perda total estimada (Lb): " << Lb << " dB" << std::endl;
	    std::cout << "Mecanismo predominante: " << mecanismoPredominante << std::endl;
	    std::cout << "====================" << std::endl;
}

void OutputManager::saveResultsToFile(const std::string& filename, double Lbf, double Lb, const std::string& mecanismo) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "Lbf: " << Lbf << " dB\n";
        file << "Lb: " << Lb << " dB\n";
        file << "Mecanismo predominante: " << mecanismo << "\n";
        file.close();
    } else {
        std::cerr << "Erro ao abrir o arquivo para escrita.\n";
    }
}




