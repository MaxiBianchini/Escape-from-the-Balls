#include "Archivos.h"

void Archivo::NuevoArchivo() {
	ofstream archivoInt("Puntaje.bin", ios::binary);
	int a = 0;
	archivoInt.write((char *)&a, sizeof(int));
	archivoInt.close();
}

void Archivo::NuevoPuntaje(int puntaje) {
	ifstream archivoInt("Puntaje.bin", ios::binary);
	int a;
	archivoInt.read((char *)&a, sizeof(int));
	archivoInt.close();

	if (a < puntaje) {
		ofstream archivoInt("Puntaje.bin", ios::binary);
		archivoInt.write((char *)&puntaje, sizeof(int));
		archivoInt.close();
	}
}

int Archivo::MostrarPuntaje() {
	ifstream archivoInt("Puntaje.bin", ios::binary);
	int a;
	archivoInt.read((char *)&a, sizeof(int));
	archivoInt.close();

	return a;
}
