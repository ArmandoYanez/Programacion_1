#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include <sstream>


//Funcion para calcular dia
int calcularDia(){
    //Calcular dia actual de la maquina
    auto tiempoActual = std::chrono::system_clock::now();

    // Convertir el tiempo actual a un tipo de tiempo establecido
    std::time_t tiempo = std::chrono::system_clock::to_time_t(tiempoActual);

    // Convertir el tiempo a una estructura tm para obtener los componentes individuales
    std::tm* tiempoDescompuesto = std::localtime(&tiempo);

    // Obtener el día, mes y año
    int diaActual = tiempoDescompuesto->tm_mday;
    int mesActual = tiempoDescompuesto->tm_mon + 1; // Sumar 1 porque en tm_mon enero es 0
    int anioActual = tiempoDescompuesto->tm_year + 1900; // Se agrega 1900 porque tm_year cuenta desde 1900{

    return diaActual;
}

//Funcion para calcular Mes
int calcularMes(){
    //Calcular dia actual de la maquina
    auto tiempoActual = std::chrono::system_clock::now();

    // Convertir el tiempo actual a un tipo de tiempo establecido
    std::time_t tiempo = std::chrono::system_clock::to_time_t(tiempoActual);

    // Convertir el tiempo a una estructura tm para obtener los componentes individuales
    std::tm* tiempoDescompuesto = std::localtime(&tiempo);

    // Obtener el día, mes y año
    int mesActual = tiempoDescompuesto->tm_mon + 1; // Sumar 1 porque en tm_mon enero es 0

    return mesActual;
}

//Funcion para calcular Año
int calcularAnio(){
    //Calcular dia actual de la maquina
    auto tiempoActual = std::chrono::system_clock::now();

    // Convertir el tiempo actual a un tipo de tiempo establecido
    std::time_t tiempo = std::chrono::system_clock::to_time_t(tiempoActual);

    // Convertir el tiempo a una estructura tm para obtener los componentes individuales
    std::tm* tiempoDescompuesto = std::localtime(&tiempo);

    // Obtener el día, mes y año
    int anioActual = tiempoDescompuesto->tm_year + 1900; // Se agrega 1900 porque tm_year cuenta desde 1900{

    return anioActual;
}

//Clase Poliza
class Poliza{
public:
    Poliza(std::string Nombre, std::string CURP, float Deducible, float MontoMax, int mes, int dia, int ano, int edad, int folio){
        this -> Nombre = Nombre;
        this -> CURP = CURP;
        this -> Deducible = Deducible;
        this -> MontoMax = MontoMax;
        this -> mes = mes;
        this -> dia = dia;
        this -> ano = ano;
        this -> edad = edad;
        this -> folio = folio;
    }

    int CalculoEdad(){
        // Obtener fecha actual
        int anoActual = calcularAnio();
        int mesActual = calcularMes();
        int diaActual = calcularDia();

        // Calcular edad
        int edadCalculada = anoActual - ano;

        // Ajuste de edad si aún no ha pasado el cumpleaños este año
        if (mesActual < mes || (mesActual == mes && diaActual < dia)) {
            edadCalculada--;
        }
        edad = edadCalculada;
        return edad;
    }

    //getters
    std::string GetNombre(){
        return Nombre;
    }

    int GetAno(){
        return ano;
    }

    int GetFolio(){
        return folio;
    }

    int GetMes(){
        return mes;
    }

    int GetDia(){
        return dia;
    }

    float GetMontoMax(){
        return MontoMax;
    }

    std::string GetCURP(){
        return CURP;
    }

    //Calculo del deducible
    float CalculoDeducible(){
        if (MontoMax <= 1000) {
            Deducible = 0.1 * MontoMax;  // 10% del monto máximo
        } else if (MontoMax > 1000 && MontoMax <= 5000) {
            Deducible = 0.15 * MontoMax;  // 15% del monto máximo
        } else {
            Deducible = 0.2 * MontoMax;  // 20% del monto máximo
        }
        return Deducible;
    }


private:
    std::string Nombre;
    std::string CURP;
    float Deducible;
    float MontoMax;
    int mes;
    int dia;
    int ano;
    int edad;
    int folio;
    std::string FolioPoliza;

protected:
    friend class Trabajador;
    //Creacion de folio de la poliza sencilla
    std::string RegistroCompleto(){
        CalculoEdad();
        CalculoDeducible();

        std::stringstream Poliza; // Crear un stringstream

        // Construir la cadena de texto en el stringstream
        Poliza << std::endl << "Folio del asegurado: " << folio << std::endl
               << "Nombre del asegurado: " << Nombre << std::endl
               << "CURP: " << CURP << std::endl
               << "Deducible: " << Deducible << std::endl
               << "Monto maximo: " << MontoMax << std::endl
               << "Fecha de nacimiento: " << dia <<"/"<< mes <<"/"<< ano << std::endl
               << "Edad: " << edad << std::endl << std::endl;

        FolioPoliza = Poliza.str(); // Obtener la cadena de texto del stringstream
        std::cout << FolioPoliza; // Imprimir la cadena de texto
        return FolioPoliza;
    }
};

//Clase heredada
class PolizaDeVida : public Poliza{
public:
    PolizaDeVida(std::string Nombre, std::string CURP, float Deducible, float MontoMax, int mes, int dia, int ano, int edad, int folio, std::string Enfermedad, std::string TipoDeSANGRE)
    : Poliza(Nombre,CURP,Deducible,MontoMax,mes,dia,ano,edad,folio){

        this-> Enfermedad = Enfermedad;
        this-> TipoDeSANGRE = TipoDeSANGRE;
    }

    int CalculoEdad(){
        // Obtener fecha actual
        int anoActual = calcularAnio();
        int mesActual = calcularMes();
        int diaActual = calcularDia();

        // Calcular edad
        int edadCalculada = anoActual - GetAno();

        // Ajuste de edad si aún no ha pasado el cumpleaños este año
        if (mesActual < GetMes() || (mesActual == GetMes() && diaActual < GetDia())) {
            edadCalculada--;
        }
        edad = edadCalculada;
        return edad;
    }

    //Calculo del deducible
    float CalculoDeducible(){
        if (GetMontoMax() <= 1000) {
            Deducible = 0.1 * GetMontoMax();  // 10% del monto máximo
        } else if (GetMontoMax() > 1000 && GetMontoMax() <= 5000) {
            Deducible = 0.15 * GetMontoMax();  // 15% del monto máximo
        } else {
            Deducible = 0.2 * GetMontoMax();  // 20% del monto máximo
        }
        return Deducible;
    }

private:
    std::string Enfermedad;
    std::string TipoDeSANGRE;
    int edad;
    int Deducible;
    std::string FolioPoliza;

protected:
    friend class Trabajador;
    //Creacion de folio de la poliza sencilla
    std::string RegistroCompleto(){
        CalculoEdad();
        CalculoDeducible();

        std::stringstream Poliza; // Crear un stringstream

        // Construir la cadena de texto en el stringstream
        Poliza << std::endl << "Folio de seguro de vida: " << GetFolio() << std::endl
               << "Nombre del asegurado: " << GetNombre() << std::endl
               << "CURP: " << GetCURP() << std::endl
               << "Deducible: " << Deducible << std::endl
               << "Monto maximo: " << GetMontoMax() << std::endl
               << "Fecha de nacimiento: " << GetDia() <<"/"<< GetMes() <<"/"<< GetAno() << std::endl
               << "Edad: " << edad << std::endl
               << "Enfermedades: " << Enfermedad << std::endl
               << "Tipo de sangre: " << TipoDeSANGRE << std::endl << std::endl;

        FolioPoliza = Poliza.str(); // Obtener la cadena de texto del stringstream
        std::cout << FolioPoliza; // Imprimir la cadena de texto
        return FolioPoliza;
    }
};

//Clase amiga la cual puede crear las polizas
class Trabajador{
public:
    std::string Poliza(Poliza poliza){
        return poliza.RegistroCompleto();
    }

    std::string PolizaDeVida(PolizaDeVida polizadevida){
        return polizadevida.RegistroCompleto();
    }
};

//Funcion para pedir datos al usuario
void PedirDatos (std::string* Nombre, std::string* CURP, float* MontoMax, int* ano, int* mes, int* dia){

    //Ingresar Nombre
    std::cout << "Cual es tu nombre?:" << std::endl;
    std::cin >> *Nombre;

    //Ingresar curp
    std::cout << "Cual es tu CURP?:" << std::endl;
    std::cin >> *CURP;

    //Ingresar deducible
    std::cout << "Cual es tu monto maximo?:" << std::endl;
    std::cin >> *MontoMax;

    //Ingresar año
    std::cout << "Ingresa año de nacimiento a 4 digitos, ejemplo (2004): " << std::endl;
    std::cin >> *ano;

    //Ingresar mes
    std::cout << "Ingresa el mes de nacimiento a 2 digitos, ejemplo (02): " << std::endl;
    std::cin >> *mes;

    //Ingresar dia
    std::cout << "Ingresa el dia de nacimiento a 2 digitos, ejemplo (09): " << std::endl;
    std::cin >> *dia;

}

//Funcion para pedir datos al usuario para poliza de casa
void PedirDatosExtraCasa (std::string* Tamano, std::string* Direccion, int* anoConstruccion){

    //Ingresar Tamaño
    std::cout << "Cual es el tamano de la casa?:" << std::endl;
    std::cin >> *Tamano;

    //Ingresar Direccion
    std::cout << "Cual es la direccion de la casa?:" << std::endl;
    std::cin >> *Direccion;

    //Ingresar año de construccion
    std::cout << "Que año de contruccion de la casa:" << std::endl;
    std::cin >> *anoConstruccion;

}

//Funcion para pedir datos al usuario para poliza de vida
void PedirDatosExtraVida (std::string* Enfermedad, std::string* TipoDeSANGRE){

    //Ingresar estado de salud
    std::cout << "Cuenta con alguna enfermedad?:" << std::endl;
    std::cin >> *Enfermedad;

    //Ingresar tipo de sangre
    std::cout << "Cual es tu tipo de sangre:" << std::endl;
    std::cin >> *TipoDeSANGRE;

}

//Funcion para pedir datos al usuario para poliza de carro
void PedirDatosExtraAuto (int* anoAuto, float* Kilometraje, std::string* modelo, std::string* marca, int* NumeroDeSerie, std::string* placa, std::string* color){

    //Ingresar Año del carro
    std::cout << "Cual es ano del carro?:" << std::endl;
    std::cin >> *anoAuto;

    //Ingresar kilometraje
    std::cout << "Cual es tu kilometraje del auto?:" << std::endl;
    std::cin >> *Kilometraje;

    //Ingresar modelo
    std::cout << "Cual es tu modelo de tu automovil?:" << std::endl;
    std::cin >> *modelo;

    //Ingresar marca
    std::cout << "Que marca es tu automovil?: " << std::endl;
    std::cin >> *marca;

    //Ingresar numero de serie
    std::cout << "Ingresa el numero de serie : " << std::endl;
    std::cin >> *NumeroDeSerie;

    //Ingresar placa
    std::cout << "Ingresa la placa del automovil: " << std::endl;
    std::cin >> *placa;

    //Ingresar placa
    std::cout << "Ingresa el color del automovil: " << std::endl;
    std::cin >> *color;
}

//Crearcion de poliza
void CrearcionDePoliza(){
    //Datos principales del objeto
    std::string Nombre, CURP;
    float Deducible = 0, MontoMax = 0;

    //Fecha de nacimiento
    int mes = 0, dia = 0, ano = 0;
    int edad = 0;

    //Folio
    int folio = 0;
    int Opcion;

    //Datos para poliza de casa
    std::string Tamano;
    std::string Direccion;
    int anoConstruccion;

    //Datos para poliza de vida
    std::string Enfermedad;
    std::string TipoDeSANGRE;

    //Datos para poliza de coche
    int anoAuto;
    float Kilometraje;
    std::string modelo;
    std::string marca;
    int NumeroDeSerie;
    std::string placa;
    std::string color;

    //Llenar registro principal
    std::cout<<"Completa los siguientes datos para continuar: "<<std::endl;
    PedirDatos(&Nombre,&CURP,&MontoMax,&ano,&mes,&dia); //Funcion para pedir datos al usuario
    folio++;
    Poliza poliza (Nombre, CURP, Deducible,  MontoMax,  mes,  dia,  ano,  edad, folio);


    //Creacion de trabajador
    Trabajador cuco;

    //Elegir tipo de poliza
    std::cout<<"Tipo de seguro a elegir: "<<std::endl<<"1- Seguro de vida."<<std::endl<<"2- Seguro de casa."<<std::endl<<"3- Seguro de automovil."<<std::endl;
    std::cin>>Opcion;

    if(Opcion==1){
        PedirDatosExtraVida(&Enfermedad,&TipoDeSANGRE); //Funcion para pedir datos al usuario
        PolizaDeVida polizadevida (Nombre, CURP, Deducible,  MontoMax,  mes,  dia,  ano,  edad, folio, Enfermedad, TipoDeSANGRE);
        cuco.PolizaDeVida(polizadevida);
    }
    if(Opcion==2) {
        PedirDatosExtraCasa(&Tamano,&Direccion,&anoConstruccion); //Funcion para pedir datos al usuario
    }
    if(Opcion==3){
        PedirDatosExtraAuto(&anoAuto,&Kilometraje,&modelo,&marca,&NumeroDeSerie,&placa,&color); //Funcion para pedir datos al usuario
    }
    if(Opcion < 3 || Opcion > 1) {
        std::cout<<"Opcion no dispoble"<<std::endl;
        CrearcionDePoliza();
    }
}

//Funcion para mostrar menu principal
void MenuDeOpcioneP(){
    //Menu de opciones
    int Opcion;
    std::cout<<"Selecciona la opcion deseada: "<<std::endl<<"1- Crear poliza."<<std::endl<<"2- Buscar poliza."<<std::endl<<"3- salir."<<std::endl;
    std::cin>>Opcion;

    //Seleccion de opcion
    switch (Opcion)
    {
        case 1: //En caso de crear una poliza
            CrearcionDePoliza();
            break;

        case 2: //En caso de revisar una poliza

            break;

        case 3: //Para salir

            break;

        default:
            //En caso de que la opcion no sea valida, ejecutar nuevamente la funcion
            std::cout<<"Opcion no valida."<<std::endl<<std::endl;

            MenuDeOpcioneP();
            break;
    }
}


int main(){

    MenuDeOpcioneP();

    return 0;
}