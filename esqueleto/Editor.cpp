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

 const vector<string> oracion_a_palabras(const string& oracion) {
    vector<string> vector_palabras = {};
    string temporal = "";
    string char_actual; 
    for(int i = 0; i < oracion.length()+1;i++){
        char_actual = oracion[i];
        if(char_actual == " "){
            vector_palabras.push_back(temporal);
            temporal = "";
        }
        else{
            temporal.push_back(oracion[i]);
        }
    }
    vector_palabras.push_back(temporal);
    return vector_palabras;
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
    return this->_conectivos;
}

int Editor::conteo_palabras() const { 
	return _palabras_totales; 
}

int Editor::longitud() const { 
	return _longitud; 
}

void Editor::agregar_atras(const string& oracion) {

    vector<string> palabras = oracion_a_palabras(oracion);

    for(int i = 0; i < palabras.size(); i++){
            if (this->_conectivos.find(palabras[i]) == this->_conectivos.end()){
                this->_palabras_totales++;
                this->_vocabulario.insert(palabras[i]);
            }
            this->_editor.push_back(palabras[i]);
            this->_longitud++;
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
    vector<string> palabras = oracion_a_palabras(oracion);
    auto it = this->_editor.begin();
    for (int i = 0; i < palabras.size(); i++){
        it = this->_editor.begin() + pos + i;
        this->_editor.insert(it, palabras[i]);
    }
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
    e.agregar_atras("Hola me llamo Juan, se llama Jaime");
    cout << e.texto() << endl;
    e.insertar_palabras("el vecino de mi amigo", 4);
    cout << e.texto() << endl;
}