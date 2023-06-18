#ifndef __EDITOR_H__
#define __EDITOR_H__

#include <set>
#include <string>
#include <vector>
#include <map>
/* agregar includes que sean necesarios */

using namespace std;

class Editor {
public:
    // Dimensiones:
    // N: cantidad total de palabras del texto (incluyendo repetidas)
    // M: cantidad de palabras diferentes del texto (conectivas o no)
    // cardinal del conjunto de conectivos -> se puede asumir que es constante K
    // P: cantidad de repeticiones de la palabra más repetida

    // Crea un editor de texto vacío y registra qué conectivos considerará
    Editor(const set<string> & conectivos);                     // O(1)

    // Obtiene el texto completo
    string texto() const;                                       // O(N)

    const set<string>& vocabulario() const;                     // O(1)
    const set<string>& conectivos() const;                      // O(1)

    //  cuántas palabras no conectivas tiene el texto
    int conteo_palabras() const;                                // O(1)
    // cantidad de palabras del texto               
    int longitud() const;                                       // O(1)

    // obtiene posiciones de la palabra en el texto
    const set<int> & buscar_palabra(const string& palabra) const;               // O(log M)

    // agrega una palabra en una posición, desplazando a las restantes
    void insertar_palabras (const string& oracion, int posicion);               // sin requerimiento
    // elimina la palabra de una posición
    void borrar_posicion (int posicion);                                        // sin requerimiento
    // borra todas las apariciones de la palabra del texto y devuelve la cantidad borrada 
    int borrar_palabra (const string& palabra);                                 // sin requerimiento

    // agrega varias palabras al final del texto (separadas por espacios)
    void agregar_atras (const string& oracion);                                 // O(|oracion| * log(M))
    // reemplaza una palabra por otra    
    void reemplazar_palabra(const string& palabra, const string& reemplazo);    // O(log M + P * log(P))

    //Funciones auxiliares
    //const vector<string> & oracion_a_palabras(const string& oracion) ;

private:

    vector<string> _editor;

    set<string> _conectivos;

    set<string> _vocabulario;

    map<string,set<int>> _apariciones;

    int _conteo_palabras;

    //Funciones auxiliares
    //vector<string> oracion_a_palabras(const string& oracion);
    bool es_conectivo(string palabra);
    void actualizar_posiciones(int pos, int cantidad);
    
    
};


#endif // __EDITOR_H__

/*

Invariante de representación:

El vector _editor contiene las palabras del texto en el orden en que aparecen y son palabras sin espacios ni signos de puntuación y sin espacios al principio/final.
El conjunto _conectivos contiene todas las palabras consideradas como conectivos.
El conjunto _vocabulario contiene todas las palabras no conectivas del texto, sin repeticiones.
El mapa _apariciones mapea cada palabra del texto, incluyendo conectivos, con el conjunto de posiciones en las que aparece.
El entero _conteo_palabras indica la cantidad de palabras no conectivas en el texto, incluyendo repeticiones.

Ejemplo que cumpla: 
_editor = ["Somos", "estudiantes", "de", "la", "Di", "Tella"];
_conectivos = {"de", "la"};
_vocabulario = {"Somos", "estudiantes", "Di", "Tella"};
-apariciones = 
    Somos: {0}; 
    estudiantes: {1};
    de: {2};
    la; {3};
    Di: {4};
    Tella: {5};
_conteo_palabras = 4;

Ejemplo que no cumpla:
_editor = ["Somos", "estudiantes", "de", "la", "Di", "Tella"];
_conectivos = {"de", "la"};
_vocabulario = {"Somos", "estudiantes", "de" "Di", "Tella"}; NO cumple con el invariante de representación ya que hay un conectivo dentro de _vocabulario. 
_apariciones =  
    Somos: {0}; 
    estudiantes: {1};
    de: {2};  
    la: {3};
    Di: {4};
    Tella: {5};
_conteo_palabras = 5; El número debería ser 4, no 5, pero en este caso se está considerando un conectivo. 


Otro ejemplo que no cumple (por las dudas): 
Ejemplo que no cumpla:
_editor = ["Somos", "estudiantes", "de", "la", "Di", "Tella."]
No cumple con el invariante de representación ya que signos de puntuación y tampoco cumple la Pre de la función Editor. 

*/