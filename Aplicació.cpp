/*Tasca Pràctica d'Aplicació (Exercici de Classe)
Un servidor web necessita un mòdul de seguretat per gestionar les sessions dels usuaris connectats. Quan un usuari inicia una operació, es
crea un objecte SessioUsuari. Per motius de seguretat, quan la funció o el bloc de codi de l'operació acaba, la sessió s'ha de tancar
automàticament.
Atributs privats: • nomUsuari (std::string): El nom del compte. • tempsLlimitSegons (int): Temps màxim d'inactivitat permesa (en segons). Invariant: Sempre ha de ser un valor estrictament positiu ($>
0). • activa (bool): Indica si la sessió està oberta o tancada.Constructors:Constructor per defecte: Crea una sessió per a l'usuari "convidat" ambun límit de 300 segons.
Constructors
• Constructor per defecte: Crea una sessió per a l'usuari "convidat" amb un límit de 300 segons. • Constructor parametritzat (1 paràmetre): Rep el nomUsuari i assigna un límit per defecte de 600 segons. Atenció: Aquest constructor ha
de ser obligatòriament explicit per evitar que qualsevol text (string) es converteixi automàticament en una sessió de seguretat. • Constructor parametritzat complet: Rep nomUsuari i tempsLlimitSegons. Utilitza una llista d'inicialització i valida l'invariant (si el tempsés 0, l'assigna a 60 segons per seguretat).
Mètodes d'encapsulació i negoci: • getNomUsuari() const: Retorna el nom de l'usuari (mètode const). • isActiva() const: Retorna si la sessió està activa (mètode const). • ampliarTemps(int segons): Rebutja valors negatius o zero. Si és vàlid, suma els segons al límit actual. • tancarSessio(): Mètode privat d'ajuda que posa activa = false.
Destructor (~SessioUsuari()):Quan l'objecte surt d'àmbit (es destrueix), si la sessió encara està activa, crida a tancarSessio() i mostra un
missatge d'auditoria per pantalla:"[AUDITORIA] La sessió de '[nomUsuari]' s'ha tancat automàticament en sortir d'àmbit."*/

#include <iostream>
#include <string>

using namespace std;

class SessioUsuari {
private:
    string nomUsuari;
    int tempsLlimitSegons;
    bool activa;

    void tancarSessio() {
        activa = false;
    }

public:
    SessioUsuari() : nomUsuari("convidat"), tempsLlimitSegons(300), activa(true) {}

    explicit SessioUsuari(const string& nom) : nomUsuari(nom), tempsLlimitSegons(600), activa(true) {}

    SessioUsuari(const string& nom, int temps)
        : nomUsuari(nom), tempsLlimitSegons(temps > 0 ? temps : 60), activa(true) {
    }

    string getNomUsuari() const {
        return nomUsuari;
    }

    bool isActiva() const {
        if (activa) {
            return true;
        }
        else {
            return false;
        }
    }

    void ampliarTemps(int segons) {
        if (segons > 0) {
            tempsLlimitSegons += segons;
        }
    }

    ~SessioUsuari() {
        if (activa) {
            tancarSessio();
            cout << "AUDITORIA: La sessio de '" << nomUsuari << "' s'ha tancat automaticament en sortir d'ambit.\n";
        }
    }
};

int main() {
    {
        SessioUsuari s1("Anna", 100);
        s1.ampliarTemps(60);
    } 

    return 0;
}