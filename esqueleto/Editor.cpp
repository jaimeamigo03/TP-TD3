#include "Editor.h"
#include <iostream>

using std::string;
typedef set<string> strset;

Editor::Editor(const set<string> & conectivos) {
    for (auto it = conectivos.begin(); it != conectivos.end(); it++){
        _conectivos.insert(*it);
        }
    _palabras_totales = 0;
    _longitud = 0;
}

string Editor::texto() const {
    string str = "";
    for(int i = 0; i<this->_longitud; i++){
        str = str + this->_editor[i] + " ";
    }
    return str;
}

const set<string>& Editor::vocabulario() const {
    return this->_vocabulario;
}

const set<string>& Editor::conectivos() const {
    for (auto it = _conectivos.begin(); it != _conectivos.end(); ++it){
        cout << ' ' << *it;
        }
    return this->_conectivos;
}

int Editor::conteo_palabras() const { 
	return _palabras_totales; 
}

int Editor::longitud() const { 
	return _longitud; 
}

void Editor::agregar_atras(const string& oracion) {
    string temporal = "";
    string temp2;
    for(int i = 0; i < oracion.length()+1;i++){
        temp2 = oracion[i];
        if(temp2 == " "){
            this->_editor.push_back(temporal);
            this->_longitud++;
            if (this->_conectivos.find(temporal) == this->_conectivos.end()){
                this->_palabras_totales++;
                this->_vocabulario.insert(temporal);
            }
            temporal = "";
        }
        else{
            temporal.push_back(oracion[i]);
        }
    }
}

const set<int> & Editor::buscar_palabra(const string& palabra) const {
    set<int> apariciones = {};
    for(int i = 0; i < this->_editor.size(); i++){
        if (this->_editor[i] == palabra){
            apariciones.insert(i);
        }
    }
    return apariciones;
}

void Editor::insertar_palabras(const string& oracion, int pos) {
    
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

int main(){
    Editor e({});
    e.agregar_atras("el vecino es mi amigo");
    cout << e.texto() << endl;
}