// fuer std::cout, ermoeglicht output auf der Konsole
#include <iostream>

// soll nur fuer die Veranschaulichung des Speichermanagements dienen, keine Angst
class Object
{
public:
    /* constructor */
    Object()
    {
        std::cout << "Object erstellt\n";
    }
    
    /* destructor, wird aufgerufen, wenn das objekt aus dem speicher entfernt wird.
       passiert meist, wenn das objekt out-of-scope ist
       nimmt keine parameter
    */
    ~Object()
    {
        std::cout << "Objekt zerstoert\n";
    }

    /* copy constructor, wird aufgerufen, wenn ein Objekt durch '=' erstellt wird
    
        Beispiel:
        Objekt a;        <= hier wird Objekt() aufgerufen
        Objekt b = a     <= hier wird der copy constructor aufgerufen, weil a nach b kopiert wird
    */
    Object(Object& other) // beachte das '&'
    {
        std::cout << "Objekt kopiert\n";
    }

    /* das const hier sagt dem compiler, dass diese funktion das objekt, auf dem sie aufgerufen wird, nicht veraendert */
    void print_something() const { std::cout << "Hello object\n"; }

}; //semikolon nicht vergessen

int main()
{
    /*
        Lambda syntax:

        auto lambda_name = [<closure>](<parameters>) -> <return_type> { <things_you_want_to_do> };
        Mit dem keyword 'auto' hilft dir der compiler den typen deiner variable rauszufinden, vor allem bei lambdas nuetzlich
    */
    auto basic_lambda = []() -> void { std::cout << "Hello world\n"; };

    /* 
        Closure:
        
        Lambdas sind wie normale Funktionen. Das heisst aber auch, dass sie keine sachen ausserhalb ihres eigenen scopes kennen
        
        Nicht funktionierendes Beispiel: 
        int my_number = 5;
        auto some_lambda = []() -> void { std::cout << my_number; };
        Das Beispiel wuerde nicht kompilieren, da some_lambda my_number nicht kennt. Deshalb muss my_number in der Closure erwaehnt werden.
    */
   int my_number = 5;
   auto closure_example = [my_number]() -> void { std::cout << my_number << '\n'; };

   /*
        caught-by-value vs. caught-by-reference

        Wenn du in C++ Objekte einfach so als Parameter uebergibst, wird das gesamte Objekt kopiert, was Performance kosten kann.
        Deshalb gibt es die Moeglichkeit, Parameter als Referenzuebergabe anzugeben. 
        Referenzen sind z.B. bei Python der default fuer die Parameteruebergabe. Also wenn du folgendes machst:
        
        def my_function(my_parameter):
            print(my_parameter)
        
        Dann wird my_parameter nicht beim Aufruf von my_function kopiert, sondern nur eine Referenz auf my_parameter uebergeben.

        C++ Beispiel:
        void my_function(Object a)  { ... }     <= a wird bei der Uebergabe kopiert, was bedeutet, dass der copy-constructor von Object aufgerufen wird, 
                                                   neues Objekt wird also erstellt
        void my_function(Object& a) { ... }     <= a wird als Referenz uebergeben, kein neues Objekt wird erstellt. Beachte das '&' nach Object

        Dasselbe gilt jetzt auch fuer Closures. Man kann die Argumente darin by-value oder by-reference uebergeben
   */
    Object my_object;
    auto by_value_example       = [my_object]() -> void { my_object.print_something(); };
    auto by_reference_example   = [&my_object]() -> void { my_object.print_something(); };

    basic_lambda();
    closure_example();
    by_value_example();
    by_reference_example();


    /*
        Das Programm hat jetzt folgenden Ablauf:
        
        1. basic_lambda wird deklariert und initialisiert
        2. closure_example wird deklariert und initialisiert. dabei wird my_number durch die closure gecaptured.
        3. my_object wird erstellt. konsolen-output: "Objekt erstellt"
        4. by_value_example wird deklariert und initialisiert. hierbei wird durch die closure my_object jetzt kopiert, also der
           copy-constructor aufgerufen. konsole-output: "Objekt kopiert"
        5. die lambdas werden aufgerufen und abgearbeitet. konsolen-output:
            Hello world
            5
            Hello object
            Hello object
        6. vor dem ende der main-funktion gehen die variablen out-of-scope und werden zerstoert.
           also wird der destructor von my_object aufgerufen und der destructor von der kopie von my_object, die in by_value_example drinsteckt
           konsolen-output:
           Objekt zerstoert
           Objekt zerstoert

        Gesamter Konsolenoutput:
        Objekt erstellt
        Objekt kopiert
        Hello world
        5
        Hello object
        Hello object
        Objekt zerstoert
        Objekt zerstoert
    */

    return 0;       // nicht pflicht, aber good-practice
}