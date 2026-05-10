#include <iostream>
#include<cmath>
#include<string>
#include <ctime>
#include <windows.h> //Cette bibliotech et son utilisation dans le main, je l'ai trouvé sur internet,
                     // cela sert juste à avoir une présentation correcte avec les accents ect... 

using namespace std;

class Capteur {
    private :
     int id;
     string unite;
    public :
        Capteur(int id, string unite){
            this->id=id;
            this->unite=unite;
        }
        int getId (){
            return this->id;
        }
        string getUnite (){
            return this->unite;
        }
        virtual void lireDonnee() = 0;
        virtual bool estEnAlerte() = 0;

        virtual ~Capteur() {}
};

class Thermometre : public Capteur {
    private :
        float temperature;
    public :
        Thermometre(int id) : Capteur(id, "°C") {
        }
        void lireDonnee() override {
            this->temperature=(rand()%116)-15;
            cout <<"Thermometre" << this->getId() <<":"<< this->temperature << this->getUnite() << endl;
        }
        bool estEnAlerte() override {
            if(this->temperature>80){
                return true;
            }
            else{
                return false;
            }
        }
};

class Pressiometre : public Capteur {
    private :
        float pression;
    public :
        Pressiometre(int id) : Capteur(id, " bar"){
        }
        void lireDonnee() override {
            this->pression=(rand()%51)/10;
            cout << "Pressiometre" << this->getId() <<":"<< this->pression<<this->getUnite()<<endl;
        }

        bool estEnAlerte() override{
            if(this->pression < 1.5){
                return true;
            }
            else{
                return false;
            }
        }
};

class UniteDeControle{
    private :
        Capteur* capteurs[10];
        int nbcapteur;
    public : 
        UniteDeControle (){
            nbcapteur=this->nbcapteur=0;

            for (int i=0; i<10; i++){
                this->capteurs[i]=nullptr;
            }
        }

        void ajouterCapteur(Capteur* c){
            if(this->nbcapteur>=10){
                cout <<"Erreur : il y a le nombre maximal de capteur"<<endl;
                delete c;
                return;
            }
            this->capteurs[this->nbcapteur]=c;
            this->nbcapteur++;
        }

        int inspecterSysteme() {
            int nbAlerte=0;
            for (int i=0; i<this->nbcapteur; i++){
                if (this->capteurs[i]!=nullptr){
                    this->capteurs[i]->lireDonnee();
                    if (this->capteurs[i]->estEnAlerte() == true) {
                    nbAlerte++;
                    }
                }
            }
            return nbAlerte;
        }
        ~UniteDeControle(){
            for (int i = 0; i < this->nbcapteur; i++) {
                if (this->capteurs[i] != nullptr) {
                    delete this->capteurs[i];
                    this->capteurs[i] = nullptr;
                }
            }
        }
};

int main() {
    SetConsoleOutputCP(65001); 
    srand(time(0));
    UniteDeControle uc;
    uc.ajouterCapteur(new Thermometre(1));
    uc.ajouterCapteur(new Thermometre(2));
    uc.ajouterCapteur(new Pressiometre(1));
    uc.ajouterCapteur(new Pressiometre(2));
    uc.ajouterCapteur(new Thermometre(3));

    int alertes = uc.inspecterSysteme();
    if (alertes > 0) {
        cout << "\n" << alertes << " capteur(s) en alerte !" << endl;
        cout <<"\nALERTE : Maintenance immédiate requise !"<< endl;
    } else {
        cout << "\nPas d'alerte." << endl;
    }
    return 0;
}