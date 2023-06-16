#include "Editor.h"
#include "iostream"
using std::string;


Editor::Editor(const set<string> & conectivos) {
    this->_editor = {};
    this->_conectivos = conectivos;
    this->_vocabulario = {};
    this -> _apariciones = {};
    this->_conteo_palabras = 0; 
}

bool Editor::es_conectivo(string palabra){
    bool res = false;
    if(this->_conectivos.find(palabra) != this->_conectivos.end()){
        res = true;
    }
    return res;
}

void Editor::actualizar_posiciones(int pos, int cantidad){
    int pos_inicial = pos;
    set <int> temporal = {};
    while(pos < this->_editor.size()){
        if(!(es_conectivo(this->_editor[pos]))){
        auto it = this->_apariciones.find(_editor[pos]) -> second;

        for(auto it2 = it.begin(); it2 != it.end(); it2++){
            if(*it2 < pos_inicial){
                temporal.insert(*it2);}
            else{
            temporal.insert(*it2 + cantidad);}
        }
        this->_apariciones[_editor[pos]] = temporal;}
        pos++;}
    }

string Editor::texto() const {
    string res = "";
    for (int i = 0; i < this->_editor.size(); i++){
        if(i < _editor.size()-1){
        res.append(this->_editor[i]);
        res.append(" ");}
        else{
            res.append(this->_editor[i]);
        }
    }
    return res;
}

const set<string>& Editor::vocabulario() const {
    return _vocabulario;
}

const set<string>& Editor::conectivos() const {
    return _conectivos;
}

int Editor::conteo_palabras() const { 
	return _conteo_palabras; 
}

int Editor::longitud() const { 
	return _editor.size();
}

void Editor::agregar_atras(const string& oracion) {
    string temporal = "";
    for(int i = 0; i < oracion.size(); i++){
        if(oracion[i] == ' '){
             if(!(es_conectivo(temporal))){
                this->_conteo_palabras++;
                this->_vocabulario.insert(temporal);
                this->_apariciones[temporal].insert(_editor.size());
            } 
            this->_editor.push_back(temporal);
            temporal = "";
        }
        else{
            temporal.push_back(oracion[i]);
        }
    }
    if(!(es_conectivo(temporal))){
                this->_conteo_palabras++;
                this->_vocabulario.insert(temporal);
                this->_apariciones[temporal].insert(_editor.size());
            }
            this->_editor.push_back(temporal); 
}

const set<int> & Editor::buscar_palabra(const string& palabra) const {
    return this->_apariciones.find(palabra)->second;
}

void Editor::insertar_palabras(const string& oracion, int pos) {
    //Dividir la oracion e insertarlas guardando su posicion. Además modifica las variables internas
    string temporal = "";
    int cant_palabras = 0;
    auto it = this->_editor.begin() + pos;
    int i;
    for(int i = 0; i < oracion.size(); i++){
        if(oracion[i] == ' '){
             if(!(es_conectivo(temporal))){
                this->_conteo_palabras++;
                this->_vocabulario.insert(temporal);
                this->_apariciones[temporal].insert(pos);
            } 
            this->_editor.insert(it,temporal);
            cant_palabras++;
            temporal = "";
            it++;
            pos++;
        }
        else{
            temporal.push_back(oracion[i]);
        }
    }
    if(!(es_conectivo(temporal))){
                this->_conteo_palabras++;
                this->_vocabulario.insert(temporal);
                this->_apariciones[temporal].insert(pos);
            }
            this->_editor.insert(it,temporal);
            cant_palabras++;
            pos++;

    //Modificar las posiciones de las palabras subsecuentes
    actualizar_posiciones(pos, cant_palabras);
}

void Editor::borrar_posicion(int pos) {
    // Pre: 0 ≤ posicion ≤ longitud()-1
    // Post: Se elimina la palabra ubicada en esa posición del texto.
    string palabra = _editor[pos];

    if (!es_conectivo(palabra)) {
        _conteo_palabras--;
        _vocabulario.erase(palabra);
    }  // Eliminar la palabra del conjunto de vocabulario si no es conectiva.

    _editor.erase(next(_editor.begin(), pos));  // Eliminar la palabra en la posición indicada

    auto it = _apariciones.find(palabra); // Busca la palabra especificada
    if (it != _apariciones.end()) {
        it->second.erase(pos);  // Eliminar la posición de la palabra en el mapa de apariciones
        if (it->second.empty())
            _apariciones.erase(it);  // Si no quedan más apariciones de la palabra, eliminarla del mapa
    }

    // Actualizar las posiciones de las palabras siguientes en el mapa de apariciones
    actualizar_posiciones(pos+1, -1);
}

int Editor::borrar_palabra(const string& palabra) {
    // Pre: El string palabra no tiene espacios ni signos de puntuación.
    // Post: Se elimina la palabra indicada de todo el texto, y se devuelve la cantidad de palabras eliminadas.
    set<int> posiciones = buscar_palabra(palabra); // Obtener las posiciones de la palabra

    int cantidadBorrada = 0; // Inicializar la cantidad borrada

    for (int pos : posiciones) {
        string palabraActual = _editor[pos];

        if (!es_conectivo(palabraActual)) {
            _conteo_palabras--;
            _vocabulario.erase(palabraActual);
        }

        _editor.erase(next(_editor.begin(), pos)); // Eliminar la palabra en la posición indicada

        auto it = _apariciones.find(palabraActual); // Buscar la palabra en el mapa de apariciones
        if (it != _apariciones.end()) {
            it->second.erase(pos); // Eliminar la posición de la palabra en el mapa de apariciones
            if (it->second.empty()) {
                _apariciones.erase(it); // Si no quedan más apariciones de la palabra, eliminarla del mapa
            }
        }

        // Actualizar las posiciones de las palabras siguientes en el mapa de apariciones
        actualizar_posiciones(pos, 1);

        cantidadBorrada += 1; // Incrementar la cantidad borrada
    }

    return cantidadBorrada; // Devolver la cantidad de palabras borradas
}

void Editor::reemplazar_palabra(const string& palabra1, const string& palabra2) {
    set<int> posiciones_p1 = buscar_palabra(palabra1);
    auto it_p1 = posiciones_p1.begin();

    for(int pos : posiciones_p1){
        this->_editor[pos] = palabra2;
    }
    if(es_conectivo(palabra1)){
        if(es_conectivo(palabra1))
        this->_vocabulario.insert(palabra2);
        this->_apariciones[palabra2] = posiciones_p1;

        this->_vocabulario.erase(palabra1);
        this->_apariciones.erase(palabra1);
    }

/* int main(){
    Editor e({});
    e.agregar_atras("pin uno pin dos pin tres pin cuatro pin cinco pin seis pin siete pinocho");

    e.borrar_palabra("pin");
    cout << e.texto() << endl;
    return 0;
}    */