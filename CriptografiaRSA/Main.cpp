#include "Header.h"
#include "Controller.h"

int menu(Controller* ctrl) {

	int op = 0;
	do {
		cout << "\n\t[ CRIPTOGRAFIA RSA ]\n\n";
		ctrl->mostrarArchivo(); cout << endl;
		cout << "1. Encriptar" << endl;
		cout << "2. Desencriptar" << endl;
		cout << "3. Salir" << endl;
		Console::SetCursorPosition(1, 27);
		cout << "0. Actualizar Mensaje" << endl;
		Console::SetCursorPosition(1, 12);
		cout << "\nDigite una opcion:\t"; cin >> op;

	} while (op < 0 || op > 3);

	return op;
}
int optionCero() {

	int op = 0;
	do {
		cout << "\n\t[ CRIPTOGRAFIA RSA ]\n\n";
		cout << "1. Actualizar Mensaje" << endl;
		cout << "2. Actualizar Clave" << endl;
		cout << "3. Regresar" << endl;
		cout << "\nDigite una opcion:\t"; cin >> op;

	} while (op < 1 || op > 3);

	return op;
}

int main() {

	int option = 0;
	Controller* ctrl = new Controller();
	long long p, q, n, e, d;

	cout << "\nIngrese el valor de p (n�mero primo): "; cin >> p;
	cout << "Ingrese el valor de q (n�mero primo): "; cin >> q;

	// Generar claves p�blica y privada
	ctrl->generarClaves(p, q, n, e, d);

	while (1) {
		system("cls");
		option = menu(ctrl);
		system("cls");

		switch (option) {
		case 1:
			ctrl->encriptar(); break;
		case 2:
			ctrl->desencriptar(); break;
		case 3:
			exit(0); break;
		case 0:
			ctrl->actualizarMensaje();
			// Ingresar valores de p y q
			cout << "\nIngrese el valor de p (n�mero primo): "; cin >> p;
			cout << "Ingrese el valor de q (n�mero primo): "; cin >> q;

			// Generar claves p�blica y privada
			ctrl->generarClaves(p, q, n, e, d);

			cout << "\nClave p�blica: (n = " << n << ", e = " << e << ")" << endl;
			cout << "Clave privada: (n = " << n << ", d = " << d << ")" << endl;
			cout << "\nDocumento.txt actualizado. ";
			break;
		default:
			break;
		}
		cout << "\n\n"; system("pause");
	}
	//ctrl->clearText();
	ctrl->guardarMensaje();

	return 0;
}