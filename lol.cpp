#include <iostream>   //libreria para usar la entrada y slaiode cin cout
#include <vector>           //libreria para hacer listas con datos
#include <string>          //libreria para manejar cadenas de texto
#include <algorithm>     //libreria para usar funciones de algoritmos
#include <limits>          //libreria para limpiar el buffer

using std::cout;
using std::cin;
using std::endl;         //esto es para ahorrar el escribir std::
using std::string;
using std::vector;

class Estudiante {           //esta clase es para representar a un estudiante y sus datos
private:
    int id;
    string nombre;
    int edad;
    string carrera;

public:
    Estudiante(int id, const string& nombre, int edad, const string& carrera)    //inizializa a los estudiantes con sus datos
        : id(id), nombre(nombre), edad(edad), carrera(carrera) {}

    int getId() const { return id; }
    const string& getNombre() const { return nombre; }
    int getEdad() const { return edad; }                   //esto es para acceder a los datos privados
    const string& getCarrera() const { return carrera; }

    void setNombre(const string& n) { nombre = n; }
    void setEdad(int e) { edad = e; }                   //esto modifica los atos privados
    void setCarrera(const string& c) { carrera = c; }

    void mostrarInfo() const {
        cout << "ID: " << getId() << " | Nombre: " << getNombre()   //esto para mostrar los datos en pantalla
             << " | Edad: " << edad
             << " | Carrera: " << carrera << endl;
    }
};

class SistemaEstudiantes {         
private:
    vector<Estudiante> lista;                //en esto se usa la libreria de vector para crear la lista 

public:
    void registrarEstudiante() {
        int id, edad;
        string nombre, carrera;
        cout << "Ingrese ID: ";              //esto pide el id y limpia el buffer
        (cin >> id).ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        cout << "Ingrese nombre: ";
        getline(cin, nombre);
        cout << "Ingrese edad: ";
        (cin >> edad).ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        cout << "Ingrese carrera: ";
        getline(cin, carrera);

        lista.push_back(Estudiante(id, nombre, edad, carrera));    //crea un objeto y lo agrega a la lista 
        cout << "Estudiante registrado con exito.\n";
    }

    void mostrarEstudiantes() const {
        if (lista.empty()) {
            cout << "No hay estudiantes registrados.\n";  //si no hay estudiantes te avisa, si si hay muestra la lista 
            return;
        }
        cout << "\n--- Lista de Estudiantes ---\n";
        for (auto &e : lista) {
            e.mostrarInfo();
        }
    }

    void actualizarEstudiante() {                  //busca al estudiante por id para cambiar los datos
        int id;
        cout << "Ingrese el ID del estudiante a actualizar: ";
        (cin >> id).ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        auto it = std::find_if(lista.begin(), lista.end(), [id](const Estudiante& e){ return e.getId() == id; });

        if (it != lista.end()) {         //al encontrar la id pide los nuevos datos
            string nombre, carrera;
            int edad;
            cout << "Nuevo nombre (actual: " << it->getNombre() << "): ";
            getline(cin, nombre);
            cout << "Nueva edad (actual: " << it->getEdad() << "): ";
            (cin >> edad).ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Nueva carrera (actual: " << it->getCarrera() << "): ";
            getline(cin, carrera);

            it->setNombre(nombre);
            it->setEdad(edad);
            it->setCarrera(carrera);

            cout << "Informacion actualizada.\n";
        } else {
            cout << "Estudiante con ID " << id << " no encontrado.\n";
        }
    }

    void eliminarEstudiante() {             //borra al estudiante con la id que le des
        int id;
        cout << "Ingrese el ID del estudiante a eliminar: ";
        (cin >> id).ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        const auto original_size = lista.size();
        auto new_end = std::remove_if(lista.begin(), lista.end(), [id](const Estudiante& e) {
            return e.getId() == id;
        });
        lista.erase(new_end, lista.end());

        if (lista.size() < original_size) {
            cout << "Estudiante eliminado con exito.\n";
        } else {
            cout << "Estudiante con ID " << id << " no encontrado.\n";
        }
    }
};

int main() {
    SistemaEstudiantes sistema;
    int opcion;              //variable para el menu

    do {
        cout << "\n===== Gestion de Estudiantes =====\n";
        cout << "1. Registrar estudiante\n";
        cout << "2. Mostrar estudiantes\n";
        cout << "3. Actualizar estudiante\n";        //menu de opciones
        cout << "4. Eliminar estudiante\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";

        cin >> opcion;
        if (cin.fail()) {
            cout << "Entrada invalida. Por favor ingrese un numero.\n";
            cin.clear(); 
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  //aviso de entradas invalidas 
            opcion = 0; 
            continue;
        }

        switch (opcion) {
            case 1: sistema.registrarEstudiante(); break;         //segun la opcion elegida hace lo correspondiente  
            case 2: sistema.mostrarEstudiantes(); break;
            case 3: sistema.actualizarEstudiante(); break;
            case 4: sistema.eliminarEstudiante(); break;
            case 5: cout << "Saliendo del sistema\n"; break;
            default: cout << "Opcion invalida.\n"; break;
        }
    } while (opcion != 5);    //se repite hasta que el usuario escribe el num 5

    return 0;
}
