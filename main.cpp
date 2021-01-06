#include <iostream>
#include <vector>
#include <string>

// Clase usuario
class Usuario {
    std::string password;
    public:
        std::string name;
        std::string email;
        bool admin;

        std::string get_password() {
            return this->password;
        }

        // Constructor por defecto
        Usuario() {
            this->name = "NO_DEFINIDO";
            this->email = "";
            this->admin = false;
            this->password = "";
        }

        // Constructor que genera un usuario a partir de un nombre, correo, contraseña y estado de administrador
        Usuario(std::string nombre, std::string correo, std::string password, bool admin) {
            this->name = nombre;
            this->email = correo;
            this->admin = admin;
            this->password = password;
        };
};

// Clase pago
class Pago {
    public:
        std::string direccion;
        std::string telefono;
        float precio_pagar;
        int nip;

        // Constructor por defecto de Pago
        Pago() {
            this->precio_pagar = 0;
        }

        // Constructor personalizado del objeto Pago
        Pago(std::string address, std::string phone, float precio_pagar, int nip) {
            this->direccion = address;
            this->telefono = phone;
            this->precio_pagar = precio_pagar;
            this->nip = nip;
        }
};

// Clase Prenda
class Prenda {
    public:
        std::string item;
        float price;

        // Constructor personalizado de la clase prenda
        Prenda(std::string ropa, float precio) {
            this->item = ropa;
            this->price = precio;
        };
};

// Clase orden
class Orden {
    public:
        std::string status;
        // Vector que almacena las prendas elegidas por el usuario
        std::vector <Prenda> prendas;
        Usuario user;
        Pago informacion_pago;

        // metodo ecargado de agregar mas ropa al vector de prendas
        void agregar_prenda(Prenda ropa) {
            this->prendas.push_back(ropa);
        }

        // constructor de orden que recibe el objeto cliente que hace la compra
        Orden(Usuario cliente) {
            this->user = cliente;
            this->status = "SIN PROCESAR";
        }
};

// Clase Tintoreria
class Tintoreria {
    public:
        // Vector que guarda las prendas que la tienda puede lavar --- contiene 4 prendas iniciales
        std::vector <Prenda> prendas = {Prenda("Camisa", 129), Prenda("Saco", 160), Prenda("Pantalon", 100), Prenda("Vestido", 500)};
        // Vector que guarda las ordenes que envían los ususarios
        std::vector <Orden> ordenes;
        // Vector que guarda los usuarios de la aplicacion --- contiene 2 perfiles de ususario para hacer las prebas
        std::vector <Usuario> usuarios = {Usuario("Juan Carlos Moreno", "carlos@gmail.com", "345", 0), Usuario("Manuel Irineo", "manuel@user.com", "123", 1)};

        // Metodo que regresa un objeto del tipo ususario
        Usuario iniciar_sesion() {
            std::string email;
            std::string password;

            std::cout << "Ingrese su correo electronico: ";
            std::cin >> email;
            std::cout << "Ingrese su contrasenia: ";
            std::cin >> password;

            // Se verifica si existe un usuario que coincida con los datos ingresados
            for (int i = 0; i < this->usuarios.size(); i++) {
                if (email == usuarios[i].email && password == usuarios[i].get_password()) {
                    // se regresa el objeto ususario que coincide con la contraseña y el correo
                    return usuarios[i];
                }
            }

            // si no coinciden se regresa el perfil de ususario por defecto
            std::cout << "Error, la contrasenia o el correo no coinciden" << std::endl;
            return Usuario();
        }

        // Funcion que regresa un objeto de usuario creado con el constructor por defecto
        Usuario cerrar_sesion() {
            return Usuario();
        };

        // Funcion que se encarga de registrar un nuevo usuario al agregarlo al vector de usuarios
        void registrarse() {
            std::string name;
            std::string email;
            std::string password;
            std::string password2;
            bool admin;

            // el usuario ingresa sus datos
            std::cout << "Ingrese su nombre de usuario: ";
            fflush(stdin);
            std::getline(std::cin, name);
            std::cout << "Ingrese su correo electronico: ";
            std::cin >> email;
            std::cout << "Ingrese su contrasenia: ";
            std::cin >> password;
            std::cout << "Confirme su contraseniaa: ";
            std::cin >> password2;

            // si las contraseñas no coinciden se repite el proceso
            if (password != password2) {
                std::cout << "Las contraseñas ingresadas no coinciden, intente de nuevo" << std::endl;
                return;
            }

            // el usuario ingresa si es un cliente o un colaborador
            std::cout << "Ingrese 1 para registrarse como colaborador, 0 para registrarse como cliente: ";
            std::cin >> admin;

            if(admin > 1) {
                std::cout << "Esa opcion no está disponible" << std::endl;
                return;
            }

            if (admin) {
                std::string clave;
                // clave:: GARLICPASTA
                std::cout << "Ingrese su clave de colaborador ";
                std::cin >> clave;
                // para poder registrarse el empleado debe de saber la clave 
                if (clave == "GARLICPASTA") {
                    // se construye un usuario de tipo administrador y se agrega al vector
                    this->usuarios.push_back(Usuario(name, email, password, admin));
                    std::cout << "se ha registrado exitosamente" << std::endl;
                } else {
                    std::cout << "ERROR\nNo cuenta con las credenciales correcta, contacte a la tienda" << std::endl;
                }
            } else {
                // se construye un usuario de tipo cliente y se agrega al vector
                this->usuarios.push_back(Usuario(name, email, password, admin));
                std::cout << "se ha registrado exitosamente" << std::endl;
            }
  
        }

        // metodo que despliega las ordenes del vector ordenes
        void revisar_pedidos() {
            for (int i = 0; i < this->ordenes.size(); i++) {
                std::cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
                std::cout << i+1 << ".- Informacion de pedido: STATUS-" << ordenes[i].status << std::endl;
                std::cout <<"**Informacion de usuario**:" << std::endl;
                std::cout << "Nombre: " << ordenes[i].user.name << "\t Email:" << ordenes[i].user.email << std::endl;
                std::cout <<"**Informacion de pago**:" << std::endl;
                std::cout << "Nip: " << ordenes[i].informacion_pago.nip << "\t Direccion: " << ordenes[i].informacion_pago.direccion << std::endl;;
                std::cout << "telefono: " << ordenes[i].informacion_pago.telefono << "\t Precio a pagar: $" << ordenes[i].informacion_pago.precio_pagar << std::endl;
                std::cout <<"**Detalles de la orden**: " << std::endl;      
                for (int j = 0; j < ordenes[i].prendas.size(); j++) {
                    // se despliega un desgloce de las órdenes que se han almacenado en la tintoreria
                    std::cout << "--" << ordenes[i].prendas[j].item << "\t $" << ordenes[i].prendas[j].price << std::endl;
                }
            }
        }

        // metodo que agrega una nueva prenda al catálogo al recibir un objeto del tipo ropa y añadirlo al vector de prendas
        void agregar_item(Prenda ropa) {
            this->prendas.push_back(ropa);
        }

        // metodo que despliega las prendas que se pueden lavar en la tintoreria
        void ver_items() {
            for (int i = 0; i < this->prendas.size(); i++) {
                std::cout << i+1 << ".- " << prendas[i].item << " \t$ " << prendas[i].price << std::endl;
            }
        }

};

// se crea una forma personalizada de imrpimir los objetos del tipo orden
// cout es un objeto de tipo ostream, por lo que se tiene que regresar este tipo para que funcione el overloading
// se pone el & porque no queremos que se copie y se pegue de forma infinita
std::ostream& operator << (std::ostream& output, const Orden actual_order) {
    float precio = 0;
    output << "Numero total de prendas: " << actual_order.prendas.size() << "\nDesgloce de prendas: " << std::endl;
    // se imprime un desgloce de las prendas dentro de la orden
    for (int i = 0; i < actual_order.prendas.size(); i++) {
        output << "--" << actual_order.prendas[i].item << "\t $" << actual_order.prendas[i].price << std::endl;
        precio += actual_order.prendas[i].price;
    }
    output << "Precio total de la orden: $" << precio << std::endl;
    return output;
}

// funcion que modifica una orden agregando una prenda al vector que contiene las prendas a lavar, puesto que se pasan las variables como referencia,
// ermitiendo editarlas a nivel global
void modificar_orden(Orden &actual_order, Tintoreria &local) {
    int item_id;
    std::cout << "Ingrese el numero de identificacion de la prenda que desea agregar: ";
    std::cin >> item_id;

    if (item_id > local.prendas.size()) {
        std::cout << "Ese indice de prenda no existe, intente de nuevo" << std::endl;
        return;
    }

    actual_order.prendas.push_back(local.prendas[item_id-1]);
}

// Funcion del menu de cliente
void menu_usuario (Usuario current_user, Tintoreria &local) {
    Orden actual_order = Orden(current_user);

    bool seguir_adelante = true;

    std::string direccion;
    std::string telefono;
    float precio_pagar;
    int nip;

    while (seguir_adelante) {
        int opcion1;
        std::cout << "Ingrese la opcion a la que desea acceder: \t1.Ver prendas lavables\t2.Agregar prenda a la orden\t3.Ver resumen de orden\t4.Continuar con orden\t5.Salir" << std::endl;
        std::cin >> opcion1;

        switch (opcion1){
        case 1:
        // se despliegan las prendas que se pueden lavar
            local.ver_items();
            break;

        case 2:
        // se llama la funcion que permite modificar la orden y se imprime el estado actual de la orden
            modificar_orden(actual_order, local);
            std::cout << actual_order << std::endl;
            break;
        
        case 3:
        // se imprime el estado actual de la orden
            std::cout << actual_order << std::endl;
            break;

        case 4:
        // se imprime el estado actual de la orden y se solicitan los datos del pago
            std::cout << actual_order << std::endl;

            std::cout << "Ingrese su direccion: ";
            fflush(stdin);
            std::getline(std::cin, direccion);
            std::cout << "Ingrese su telefono: ";
            fflush(stdin);
            std::getline(std::cin, telefono);
            std::cout << "Ingrese su nip: ";
            std::cin >> nip;

            for (int i = 0; i < actual_order.prendas.size(); i++) {
                // se genera un precio total al sumar todos los atributos de precio de cada prenda
                precio_pagar += actual_order.prendas[i].price;
            }

            // se construye un objeto del tipo pago con los datos ingresados por el usuario y se guarda dentro de la orden
            actual_order.informacion_pago = Pago(direccion, telefono, precio_pagar, nip);

            // se agrega la prden al vector de ordenes de la tintoreria
            local.ordenes.push_back(actual_order);
            std::cout << "Se ha completado su orden" << std::endl;
            // el valor de la orden actual se resetea
            actual_order = Orden(current_user);
            fflush(stdout);
            break;
        
        case 5:
        // e sale de la funcion
            seguir_adelante = 0;
            break; 

        default:
            std::cout << "Esa opcion no esta disponible" << std::endl; 
            break;
        }
    }
}

// Funcion del menu de empleado
void menu_empleado (Usuario current_user, Tintoreria &local) {
    bool seguir_adelante = true;
    while (seguir_adelante) {
        int opcion1;
        std::string nombre_prenda;
        float precio_prenda;
        int order_id;
        std::string new_status;
        
        std::cout << "Ingrese la opcion a la que desea acceder: \t1.Revisar ordenes\t2.Agregar nueva prenda lavable\t3.Cambiar status de la orden\t4.Salir" << std::endl;
        std::cin >> opcion1;

        switch (opcion1) {
            case 1:
            // se despliegan los pedidos que se han guardado en el vector
                local.revisar_pedidos();
                break;

            case 2:
            // se despiegan los items que se pueden lavar 
                local.ver_items();
                std::cout << "Ingrese el nombre de la prenda: ";
                std::cin >> nombre_prenda;
                std::cout << "Ingrese el precio de lavar la prenda: ";
                std::cin >> precio_prenda;
                // se construye un nuevo objeto del tipo Prenda y se agrega al vector de prendas del local
                local.agregar_item(Prenda(nombre_prenda, precio_prenda));
                break;

            case 3:
                std::cout << "Ingrese el numero de orden a cambiar: ";
                std::cin >> order_id;
                std::cout << "Ingrese el nuevo status: ";
                std::cin >> new_status;
                // se modifica el estatus de la orden seleccionada
                if (order_id -1 < local.prendas.size()) local.ordenes[order_id-1].status = new_status;
                else std::cout << "Esa orden no existe, intente de nuevo";
                break;

            case 4:
                std::cout << "Has salido del programa" << std::endl;
                seguir_adelante = false;
                break;

            default:
                std::cout << "Esa opcion no esta disponible" << std::endl;
                break;  
        }
    }
}

void menu() {
    // se crea la tintoreria y el objeto de usuario actual
    Tintoreria local;
    Usuario current_user;
    int seguir_adelante = 1;
    while (seguir_adelante) {
        int opcion1;
        
        std::cout << "Ingrese la opcion a la que desea acceder: \t1.Iniciar sesion\t2.Registrarse\t3.Salir" << std::endl;
        std::cin >> opcion1;

        switch (opcion1) {
            case 1:
                current_user = local.iniciar_sesion();
                // si el inicio de sesion es exitoso se entra al menu del usuario
                if (current_user.name == "NO_DEFINIDO") break;
                else {
                    std::cout << "Bienvenido " << current_user.name << "!!!" << std::endl;
                    if (current_user.admin) {
                        menu_empleado(current_user, local);
                        current_user = local.cerrar_sesion();
                    } else {
                        menu_usuario(current_user, local);
                        current_user = local.cerrar_sesion();
                    }
                }
                break;
                
            case 2:
            // se llama el metodo registrarse 
                local.registrarse();
                break;

            case 3:
                std::cout << "Has salido del programa" << std::endl;
                seguir_adelante = false;
                break;

            default:
                std::cout << "Esa opcion no esta disponible" << std::endl;
                break;    
        }

    }
}

int main () {
    menu();
}