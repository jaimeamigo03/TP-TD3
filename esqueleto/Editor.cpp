#include "Editor.h"
#include "iostream"
using std::string;


Editor::Editor(const set<string> & conectivos) {
    this->_editor = {};
    this->_conectivos = conectivos;
    this->_vocabulario = {};
    this -> _apariciones = {};
    this->_longitud = 0;
    this->_conteo_palabras = 0;
    
}

bool Editor::es_conectivo(string palabra){
    bool res = false;
    if(this->_conectivos.find(palabra) != this->_conectivos.end()){
        res = true;
    }
    return res;
}

string Editor::texto() const {
    string res = "";
    for (int i = 0; i < this->_longitud; i++){
        if(i < _longitud-1){
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
	return _longitud; 
}

void Editor::agregar_atras(const string& oracion) {
    string temporal = "";
    int i = 0;
    while( i < oracion.size()){
        if(oracion[i] == ' '){
             if(!(es_conectivo(temporal))){
                this->_conteo_palabras++;
                this->_vocabulario.insert(temporal);
                this->_apariciones[temporal].insert(_longitud);
            } 
            this->_longitud++;
            this->_editor.push_back(temporal);
            temporal = "";
        }
        else{
            temporal.push_back(oracion[i]);
        }
        i++;
    }
    if(!(es_conectivo(temporal))){
                this->_conteo_palabras++;
                this->_vocabulario.insert(temporal);
                this->_apariciones[temporal].insert(_longitud);
            }
            this->_longitud++;
            this->_editor.push_back(temporal); 
}

const set<int> & Editor::buscar_palabra(const string& palabra) const {
    return this->_apariciones.find(palabra)->second;
}

void Editor::insertar_palabras(const string& oracion, int pos) {
    /* Completar */
}

void Editor::borrar_posicion(int pos) {
    /* Completar */
}

int Editor::borrar_palabra(const string& palabra) {
    /* Quitar este código y completar */
    return 0;
}

void Editor::reemplazar_palabra(const string& palabra1, const string& palabra2) {
    /* Completar */
}
