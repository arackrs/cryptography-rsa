#pragma once
#include "Header.h"

class Controller {

private:
	ofstream write;
	ifstream read;
	ll p, q, n, phi, e, d;
	vector<char> abecedario;
	string msgType;
	string message;
	string clave;
	vector<string> msg;

public:
	Controller() {
		tablaDeEquivalencia();
		cargaDeDatosDelDocumentoTxt();
		/*p = 2;
		q = 23;
		n = p * q;
		phi = (p - 1) * (p - 1);
		e = 9;
		d = 5;*/
	}
	~Controller() {}

	void tablaDeEquivalencia() {

		for (int i = 0; i < 26; ++i) {
			abecedario.push_back(65 + i);
		}
	}
	void cargaDeDatosDelDocumentoTxt() {

		ifstream archivo("Document.txt");
		string linea;
		for (int i = 0; i < 3; ++i) {
			getline(archivo, linea);
			size_t pos = linea.find(":");// Busca la posición del carácter ":" en la línea
			if (pos != string::npos) { // Si se encuentra el carácter
				// Lee el texto a partir de la posición siguiente al carácter
				if (i == 0)message = linea.substr(pos + 2);
				if (i == 1)msgType = linea.substr(pos + 2);
				//if (i == 2)clave = linea.substr(pos + 2);
				//if (msgType != "Encriptado")clave = "9";
				//if (msgType == "Desencriptado")clave = "5";
			}

		}
		archivo.close(); // Cierra el archivo
	}
	void mostrarArchivo() {

		cout << "Archivo: Document.txt" << endl;
		cout << "Mensaje: " << message << endl;
		cout << "Tipo de mensaje: " << msgType << endl;
		if (msgType == "Encriptado") {
			cout << "\nclave privada (n, d):\t(" << n << "," << clave << ")" << endl;
		}
		else {
			cout << "\nclave publica (n, e):\t(" << n << "," << clave << ")" << endl;
		}
	}
	//LOGIC----------------------------------------------------------------------------------------------------------------------

	// Función para verificar si un número es primo
	bool esPrimo(int n) {
		if (n <= 1) return false;
		if (n <= 3) return true;

		if (n % 2 == 0 || n % 3 == 0) return false;

		for (int i = 5; i * i <= n; i += 6) {
			if (n % i == 0 || n % (i + 2) == 0) return false;
		}

		return true;
	}

	// Función para calcular el máximo común divisor (MCD) de dos números
	int mcd(int a, int b) {
		if (b == 0) return a;
		return mcd(b, a % b);
	}

	// Función para generar las claves pública y privada
	void generarClaves(ll p, ll q, ll& n, ll& e, ll& d) {

		// Verificar si p y q son primos
		if (!esPrimo(int(p)) || !esPrimo(int(q))) {
			cout << "Error: p y q deben ser números primos." << endl;
			exit(1);
		}

		// Calcular n y phi(n)
		n = p * q;
		int phi_n = (p - 1) * (q - 1);

		// Encontrar un número coprimo con phi_n como exponente público
		for (int i = 2; i < phi_n; i++) {
			if (mcd(i, phi_n) == 1) {
				e = i;
				break;
			}
		}

		// Calcular el inverso modular de e como exponente privado
		int k = 1;
		while (true) {
			int temp = (phi_n * k + 1) % e;
			if (temp == 0) {
				d = (phi_n * k + 1) / e;
				break;
			}
			k++;
		}

		this->p = p;
		this->q = q;
		this->n = n;
		this->e = e;
		this->d = d;
		clave = to_string(e);
	}

	ll modpow(ll base, ll exp, ll mod) {
		ll r = 1;

		while (--exp >= 0) {
			r *= base;
			r %= mod;
		}
		return r;
	}

	void encriptar() {

		if (msgType != "Encriptado") {
			int rpta = 0; msg.clear();

			for (auto c : message) {
				for (int i = 0; i < abecedario.size(); ++i) {

					if (c == abecedario[i]) {
						// c^e mod n
						rpta = modpow(i, stoi(clave), n);
						string s = "";
						if (rpta > 25) { s = to_string(rpta); }
						else { s = abecedario[rpta]; }
						msg.push_back(s);
					}
				}
			}
			showMessage();
			clave = to_string(d);
			msgType = "Encriptado";
		}
		else {
			cout << "\nMENSAJE YA ENCRIPTADO!!\n";
			cout << "\nPruebe con desencriptarlo primero.\n";
		}
	}

	void guardarMensaje() {

		write.open("Document.txt", ios::out);
		write << "Mensaje: " << message << endl;
		if (msgType == "Encriptado") {
			desencriptar();
			msgType = "Original";
		}
		write << "Tipo de mensaje: " << msgType << endl;
		write << "Clave: " << clave;
		
		write.close();
	}


	void actualizarMensaje() {

		cout << "\nEscriba su nuevo Mensaje (solo letras mayúsculas y sin espacios): "; cin >> message;
		msgType = "Original";
	}
	void desencriptar() {

		if (msgType == "Encriptado") {
			int rpta = 0; message = "";
			for (auto c : msg) {

				if (isdigit(c[0])) {
					// c^d mod n
					rpta = modpow(stoi(c), stoi(clave), n);
					message += abecedario[rpta];
				}
				else {
					for (int i = 0; i < 26; ++i) {

						if (c[0] == abecedario[i]) {
							// c^d mod n
							rpta = modpow(i, stoi(clave), n);
							message += abecedario[rpta];
						}
					}
				}

			}
			cout << "\nSu mensaje desencriptado es: " << message;
			clave = to_string(e);
			msgType = "Desencriptado";
		}
		else {
			cout << "\nMENSAJE YA DESENCRIPTADO!!\n";
			cout << "\nPruebe con Encriptarlo primero.\n";
		}
	}

	void showMessage() {

		message = "";
		for (auto s : msg) {
			message += s;
		}
		cout << "\nSu mensaje encriptado es: " << message;
	}
};