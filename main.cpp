// =================================================================
//
// File: main.cpp
// Author: Ricardo Sierra Roa - A01709887
// Date: 07/11/2023
//
// =================================================================

// Librerias
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <algorithm>

using namespace std;

// =================================================================
// Estructura creada para construir a los equipos con sus respectivo
// numero de equipo, problemas resueltos, tiempo penalizado, y el 
// estatus del problema (C, I, R, U, E)
//
// =================================================================
struct Contestant {
    int team;
    int solved_problems;
    int penalty_time;
    map<int, int> incorrect_attempts;
    set<int> solved_set;
};

// =================================================================
// Funcion para calcular resultados de los concursantes
//
// @param vector<Contestant>, un vector con la estructura creada previamente para almacenar los datos de los equipos y utilizar los datos para calcular los resultados
// @return string con los resultados de los equipos
// @Complexity	O(n)
// =================================================================
int main() {
    vector<Contestant> contestants(101);

    string line;
	// Recibir equipos y sus datos para calcular sus resultados
	// Complexity O(n)
    while (getline(cin, line)) {
        istringstream ss(line);
        int team, problem, time;
        char result;
        ss >> team >> problem >> time >> result;

        contestants[team].team = team;
        if (result == 'C' || result == 'I') {
            if (result == 'C' && contestants[team].solved_set.find(problem) == contestants[team].solved_set.end()) {
                contestants[team].solved_problems++;
                contestants[team].penalty_time += time + (20 * contestants[team].incorrect_attempts[problem]);
                contestants[team].solved_set.insert(problem);
            } else if (result == 'I') {
                contestants[team].incorrect_attempts[problem]++;
            }
        }
    }

    vector<Contestant> valid_contestants;

    for (int i = 1; i < 101; i++) {
        if (contestants[i].solved_problems > 0 || contestants[i].penalty_time > 0) {
            valid_contestants.push_back(contestants[i]);
        }
    }

    // Agregar equipos que se registraron pero no tienen puntuacion ni tiempo
	// Complexity O(n)
    for (int i = 1; i < 101; i++) {
        if (contestants[i].team == i && contestants[i].solved_problems == 0 && contestants[i].penalty_time == 0) {
            valid_contestants.push_back(contestants[i]);
        }
    }

    // Ordenar los concursantes segun los criterios
	// Complexity O(n log n)
    sort(valid_contestants.begin(), valid_contestants.end(),
        [](const Contestant& a, const Contestant& b) {
            if (a.solved_problems == b.solved_problems) {
                if (a.penalty_time == b.penalty_time) {
                    return a.team < b.team;
                }
                return a.penalty_time < b.penalty_time;
            }
            return a.solved_problems > b.solved_problems;
        }
    );

    // Imprimir la salida ordenada
    for (const Contestant& contestant : valid_contestants) {
        cout << contestant.team << " " << contestant.solved_problems << " " << contestant.penalty_time << endl;
    }

    return 0;
}
