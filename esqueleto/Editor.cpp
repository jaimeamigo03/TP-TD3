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
            temporal = "";
            it++;
            pos++;
        }
        else{
            temporal.push_back(oracion[i]);
            cant_palabras++;
        }
    }
    if(!(es_conectivo(temporal))){
                this->_conteo_palabras++;
                this->_vocabulario.insert(temporal);
                this->_apariciones[temporal].insert(pos);
            }
            this->_editor.insert(it,temporal);
            cant_palabras++;

    //Modificar las posiciones de las palabras subsecuentes
    

    set<int> set_temporal;
    auto it2 = this->_apariciones.find(this->_editor[pos]);

    while(pos < this->_editor.size()){
        set_temporal = it2->second;
        for (auto iterator = set_temporal.begin(); set_temporal.size(); iterator++){
        }
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


/* int main(){
    Editor e({"el", "es", "mi"});
    e.agregar_atras("el vecino es mi amigo");
    e.insertar_palabras("mejor", 4);
    cout << e.texto() << endl;
    return 0;
} */