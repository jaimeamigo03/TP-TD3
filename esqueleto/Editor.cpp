#include "Editor.h"
#include "iostream"
using std::string;


Editor::Editor(const set<string> & conectivos) {
    // Pre: Los strings de conectivos son palabras sin espacios ni signos de puntuación. 
    // Post: Construye un Editor vacío con un conjuto de conectivos dado.
    this->_editor = {}; //O(1)
    this->_conectivos = conectivos; //O(|conectivos|)
    this->_vocabulario = {}; //O(1)
    this -> _apariciones = {}; //O(1)
    this->_conteo_palabras = 0; //O(1)
}
// Editor = O(1) + O(1) + O(1) O(|conectivos|) + O(1) = 4*O(1) + O(|conectivos|) = O(|conectivos|)


bool Editor::es_conectivo(string palabra){
    bool res = false; //O(1)
    if(this->_conectivos.find(palabra) != this->_conectivos.end()){ // O(log M) * O(1) = O(log M)
        res = true; //O(1)
    }
    return res; //O(1)
}
// es_conectivo = O(1) + O(log M) + O(1) = 2*O(1) + O(log M) = O(log M). Peor caso, que todas las palabras en el texto sean conectivos

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
//actualizar_posiciones = O(1) + O(M)*O(P) = O(M*P). Peor caso, que tenga que actualizar todas las posiciones de las palabras, p.ej: insertar_palabras("hola",0)

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
//texto = O(1) + O(N) + O(1) = O(N). No hay peor caso, siempre va a tardar N iteraciones.

const set<string>& Editor::vocabulario() const {
    // Pre: Verdadero
    // Post: Devuelve por referencia el conjunto de todas las palabras que aparecen alguna vez en el texto y que no están en conectivos().
    return _vocabulario; //O(1)
}
//vocabulario = O(1)

const set<string>& Editor::conectivos() const {
    // Pre: Verdadero
    // Post: Devuelve por referencia el conjunto de palabras registradas como conectivos.
    return _conectivos; //O(1)
}
//conectivos = O(1)

int Editor::conteo_palabras() const { 
    // Pre: Verdadero
    // Post: Devuelve la cantidad total de palabras que aparecen en el texto (contando repeticio- nes), excluyendo las que estén en contectivos().
	return _conteo_palabras; //O(1) 
}
//conteo_palabras = O(1)

int Editor::longitud() const { 
    // Pre: Verdadero
    // Post: Devuelve la cantidad total de palabras del texto (contando repeticiones).
	return _editor.size(); //O(1)
}
//longitud = O(1)

void Editor::agregar_atras(const string& oracion) {
    // Pre: El string oracion es una secuencia de palabras separadas por un espacio, sin signos de puntuación y sin espacios al principio/final.
    // Post: Se agregan todas las palabras de oracion al final del texto.
    string temporal = "";
    for(int i = 0; i < oracion.size(); i++){
        if(oracion[i] == ' '){
             if(!(es_conectivo(temporal))){
                this->_conteo_palabras++;
                this->_vocabulario.insert(temporal);
            } 
            this->_apariciones[temporal].insert(_editor.size());
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
            }
            this->_apariciones[temporal].insert(_editor.size()); 
            this->_editor.push_back(temporal);
}

const set<int> & Editor::buscar_palabra(const string& palabra) const {
    // Pre: El string palabra no tiene espacios ni signos de puntuación.
    // Post: Devuelve el conjunto de posiciones del texto donde aparece la palabra buscada.

    return this->_apariciones.find(palabra)->second; //O(log M)
}
//buscar_palabra = O(log M). Tiene este orden de complejidad, porque la funcion .find de un map tiene ese orden.

void Editor::insertar_palabras(const string& oracion, int pos) {
    // Pre: 0 ≤ posicion ≤ longitud() y oracion es una secuencia de palabras separadas por un espacio, sin signos de puntuación y sin espacios al principio/final.
    // Post: Se inserta en orden cada una de las palabras de la oracion, a partir de la posicion indicada.

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
            }
            this->_apariciones[temporal].insert(pos);
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
    actualizar_posiciones(pos, -1);
}

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
    // Pre: Los strings palabra1 y palabra2 no tienen espacios ni signos de puntuación. 
    // Post: Se reemplazan todas las ocurrencias en el texto de palabra1 por palabra2.

    set<int> posiciones_p1 = buscar_palabra(palabra1); //O(log M)

    for(int pos : posiciones_p1){ //O(P) * O(1) = O(P)
        this->_editor[pos] = palabra2; //O(1)
    }

    if(es_conectivo(palabra1)){ //O(log M) + O(log M) + O(P) * O(log M) = O(P) * O(log M)
        if(es_conectivo(palabra2)){ //O(log M)
            for(int pos : posiciones_p1){ //O(P) * (O(1) + O(Log M)) = O(P) * O(Log M))
                this->_apariciones[palabra2].insert(pos); //O(1)
                this->_apariciones[palabra1].erase(pos); //O(log M)
            }
        }
        else{
            for(int pos : posiciones_p1){//O(P)
                this->_apariciones[palabra2].insert(pos); //O(1)
                this->_apariciones[palabra1].erase(pos); //O(log M)
            }
            this->_conteo_palabras = this->_conteo_palabras + posiciones_p1.size(); //O(1)
            this->_vocabulario.insert(palabra2); //O(1)
        }}
    
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

    //reemplazar_palabra = O(log M) + O(P) + O(P) * O(log M) + O(P) = O(P * log M)