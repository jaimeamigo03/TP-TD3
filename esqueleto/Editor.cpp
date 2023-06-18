#include "Editor.h"
#include "iostream"
using std::string;


Editor::Editor(const set<string> & conectivos) {
    this->_editor = {}; //O(1)
    this->_conectivos = conectivos; //O(|conectivos|)
    this->_vocabulario = {}; //O(1)
    this -> _apariciones = {}; //O(1)
    this->_conteo_palabras = 0; //O(1)
}
// Editor = O(1) + O(1) + O(1) O(|conectivos|) + O(1) => 4*O(1) + O(|conectivos|) => O(|conectivos|)

bool Editor::es_conectivo(string palabra){
    bool res = false; //O(1)
    if(this->_conectivos.find(palabra) != this->_conectivos.end()){ // O(log M) * O(1) = O(log M). Peor caso, que todas las palabras en el texto sean conectivos
        res = true; //O(1)
    }
    return res; //O(1)
}
// es_conectivo = O(1) + O(log M) + O(1) => 2*O(1) + O(log M) => O(log M)

void Editor::actualizar_posiciones(int pos, int cantidad){
        set <int> temporal = {}; //O(1)
        // Este iterador, recorre todos los elementos de apariciones
        for(auto it = this->_apariciones.begin(); it != this->_apariciones.end(); it++){ //O(M) * O(P) + 2 * O(1) = O(M) * O(P)
            if(it->second == this->_apariciones[_editor[pos]]){ //O(1) * O(Max(P,P)) = O(P)
                for(auto it2 = it->second.begin(); it2 != it->second.end();it2++){ // O(P) 
                if(*it2 >= pos-1){//O(1)
                    temporal.insert(*it2 + cantidad); //O(1)
                }else{
                    temporal.insert(*it2); //O(1)
                }
            }}
            else{
            //Este iterador, recorre todos los elementos del set<int> dentro de cada elemento de _apariciones
            for(auto it2 = it->second.begin(); it2 != it->second.end();it2++){ //O(P)
                if(*it2 >= pos){ //O(1)
                    temporal.insert(*it2 + cantidad); //O(1)
                }else{
                    temporal.insert(*it2); //O(1)
                }
             }}
            it->second = temporal; //O(1)
            temporal = {}; //O(1)
        }
    }
//actualizar_posiciones = O(1) + O(M)*O(P) => O(M*P). Peor caso, que tenga que actualizar todas las posiciones de las palabras, p.ej: insertar_palabras("hola",0)

string Editor::texto() const {
    string res = ""; //O(1)
    for (int i = 0; i < this->_editor.size(); i++){ //O(N)* (3 * O(1)) = O(N)
        if(i < _editor.size()-1){ //O(1)
        res.append(this->_editor[i]); //O(1)
        res.append(" ");}//O(1)
        else{
            res.append(this->_editor[i]);//O(1)
        }
    }
    return res; //O(1)
}
//texto = O(1) + O(N) + O(1) => O(N). No hay peor caso, siempre va a tardar N iteraciones.

const set<string>& Editor::vocabulario() const {
    return _vocabulario; //O(1)
}
//vocabulario = O(1)

const set<string>& Editor::conectivos() const {
    return _conectivos; //O(1)
}
//conectivos = O(1)

int Editor::conteo_palabras() const { 
	return _conteo_palabras; //O(1) 
}
//conteo_palabras = O(1)

int Editor::longitud() const { 
	return _editor.size(); //O(1)
}
//longitud = O(1)

void Editor::agregar_atras(const string& oracion) {
    string temporal = ""; // O(1)
    for(int i = 0; i < oracion.size(); i++){ //O(|oracion|) * O(log M)
        if(oracion[i] == ' '){ //O(1)
             if(!(es_conectivo(temporal))){ //O(log M)
                this->_conteo_palabras++; //O(1)
                this->_vocabulario.insert(temporal); //O(1)
            } 
            this->_apariciones[temporal].insert(_editor.size()); //O(1)
            this->_editor.push_back(temporal); //O(1)
            temporal = ""; //O(1)
        }
        else{
            temporal.push_back(oracion[i]); //O(1)
        }
    }
    if(!(es_conectivo(temporal))){ //O(log M)
                this->_conteo_palabras++; //O(1)
                this->_vocabulario.insert(temporal); //O(1)
            }
    this->_apariciones[temporal].insert(_editor.size()); //O(1)
    this->_editor.push_back(temporal); //O(1)
}
//agregar_atras = O(1) + O(|oracion|) * O(log M) + O(log M) + 2 * O(1) => O(|oracion|) * O(log M)

const set<int> & Editor::buscar_palabra(const string& palabra) const {
    return this->_apariciones.find(palabra)->second; //O(log M)
}
//buscar_palabra = O(log M). Tiene este orden de complejidad, porque la funcion .find de un map tiene ese orden.

void Editor::insertar_palabras(const string& oracion, int pos) {
    //Dividir la oracion e insertarlas guardando su posicion. Además modifica las variables internas
    string temporal = ""; //O(1)
    int cant_palabras = 0; //O(1)
    auto it = this->_editor.begin() + pos; //O(1)
    for(int i = 0; i < oracion.size(); i++){ //O(|oracion|)
        if(oracion[i] == ' '){ //O(1)
             if(!(es_conectivo(temporal))){ //O(log M)
                this->_conteo_palabras++; //O(1)
                this->_vocabulario.insert(temporal); //O(1)
                this->_apariciones[temporal].insert(pos); //O(1)
            } 
            this->_editor.insert(it,temporal); //O(1)
            cant_palabras++; //O(1)
            temporal = ""; //O(1)
            it++; //O(1)
            pos++; //O(1)
        }
        else{
            temporal.push_back(oracion[i]); //O(1)
        }
    }
    if(!(es_conectivo(temporal))){ //O(log M)
                this->_conteo_palabras++; //O(1)
                this->_vocabulario.insert(temporal); //O(1)
            }
            this->_apariciones[temporal].insert(pos); //O(1)
            this->_editor.insert(it,temporal); //O(1)
            cant_palabras++; //O(1)
            pos++; //O(1)

    //Modificar las posiciones de las palabras subsecuentes
    actualizar_posiciones(pos, cant_palabras); //O(M*P)
}
//insertar_palabras = O(|oracion|) * O(log M) + O(log M) + O(M*P) => O(|oracion|) * O(log M) + O(M*P)

void Editor::borrar_posicion(int pos) {
    // Pre: 0 ≤ posicion ≤ longitud()-1
    // Post: Se elimina la palabra ubicada en esa posición del texto.
    string palabra = _editor[pos]; //O(1)

    if (!es_conectivo(palabra)) { //O(log M), peor caso: entra al if => tiene O(M)
        _conteo_palabras--; //O(1)
        _vocabulario.erase(palabra); //O(M)
    }  // Eliminar la palabra del conjunto de vocabulario si no es conectiva.

    _editor.erase(next(_editor.begin(), pos)); //O(M)  // Eliminar la palabra en la posición indicada

    auto it = _apariciones.find(palabra); //O(log M) // Busca la palabra especificada
    if (it != _apariciones.end()) { //O(M)
        it->second.erase(pos); //O(M)  // Eliminar la posición de la palabra en el mapa de apariciones
        if (it->second.empty()) //O(P)
            _apariciones.erase(it); //O(1)  // Si no quedan más apariciones de la palabra, eliminarla del mapa
    }

    // Actualizar las posiciones de las palabras siguientes en el mapa de apariciones
    actualizar_posiciones(pos, -1); //O(M*P)
}
//borrar_posicion = O(1) + O(M) + O(M) + O(log M) + O(M) + O(P) => O(M)

int Editor::borrar_palabra(const string& palabra) {
    // Pre: El string palabra no tiene espacios ni signos de puntuación.
    // Post: Se elimina la palabra indicada de todo el texto, y se devuelve la cantidad de palabras eliminadas.
    int apariciones_totales = 0;

    for(int i = 0; i < longitud();i++){
        if(_editor[i] == palabra){
            apariciones_totales++;
        }
    }
    if(apariciones_totales >= 1){
    set<int> posiciones = buscar_palabra(palabra); // Obtener las posiciones de la palabra
    auto it = this->_apariciones[palabra].begin();
    for(int i = 0; i < posiciones.size(); i++){
        borrar_posicion(*it);
       it = this->_apariciones[palabra].begin();
    }
    if (!es_conectivo(palabra)) {
            _conteo_palabras = _conteo_palabras - posiciones.size();
            _vocabulario.erase(palabra);
        }}

    return apariciones_totales; // Devolver la cantidad de palabras borradas
    }

void Editor::reemplazar_palabra(const string& palabra1, const string& palabra2) {
    set<int> posiciones_p1 = buscar_palabra(palabra1); //O(log M) .find de buscar una palabra en el mapa apariciones

    for(int pos : posiciones_p1){ //O(P) * O(1) = O(P) Recorre todas las posiciones del set pos, que como maximo tiene tamaño P
        this->_editor[pos] = palabra2; //O(1) Reemplazar una palabra en un vector tiene O(1)
    }

    if(es_conectivo(palabra1)){ //O(log M) + O(P) * O(log M) = O(P) * O(log M), porque O(P) * O(log M) crece mas rápido que O(log M) solo
        
        for(int pos : posiciones_p1){ //O(P) * (O(1) + O(Log M)) = O(P) * O(Log M))
                this->_apariciones[palabra2].insert(pos); //O(1)
                this->_apariciones[palabra1].erase(pos); //O(log M)
            }
        
        if(!(es_conectivo(palabra2))){ //O(log M)
            this->_conteo_palabras = this->_conteo_palabras + posiciones_p1.size(); //O(1)
            this->_vocabulario.insert(palabra2); //O(1)
        }
    }
    
    else{ //O(P) + O(log M) + O(log M) + O(log M) = O(P)
        for(int pos : posiciones_p1){  //O(P)
                this->_apariciones[palabra2].insert(pos); //O(1)
            }
            this->_vocabulario.erase(palabra1); //O(log M)
            this->_apariciones.erase(palabra1); //O(log M)
        if(es_conectivo(palabra2)){ //O(log M)
            this->_conteo_palabras = this->_conteo_palabras - posiciones_p1.size(); //O(1)      
        }
        }
    }
    //reemplazar_palabra = O(log M) + O(P) + O(P) * O(log M) + O(P) => O(P * log M)