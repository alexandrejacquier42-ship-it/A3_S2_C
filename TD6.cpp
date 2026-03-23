#include <iostream>
#include<cmath>
using namespace std;

class Point {
    private :
        int x, y;
    
    public : 
        
        Point(int valX, int valY) {
            x = valX;
            y = valY;
        }
        
        double distance(Point &autre) {
            double x_dif = autre.x - this->x;
            double y_dif = autre.y - this->y;
            return sqrt(pow(x_dif,2)+pow(y_dif, 2));
        }

        Point milieu(Point &autre) {
            double milieu_x =  (this->x + autre.x)/2;
            double milieu_y =  (this->y + autre.y)/2;
            Point p_milieu(milieu_x, milieu_y);
            return p_milieu;
        }

        virtual void afficher() {
            cout <<"("<< x <<","<< y <<")"<< endl;
        }        
        int getX(){
            return x;
        }
        int getY(){
            return y;
        }
};

class Rectangle {
    private :
        Point hautGauche();
        int longueur, largeur;
        static int nbRectangles;
        Rectangle(Point &p1, Point &p2){
            largeur=p1.getX-p2.getX;
            longueur=p1.getY-p2.getY;
        }
    public :
        static int incr_nbRectangle (){
            nbRectangles ++;
        }

        static int decr_nbRectangle(){
            nbRectangles --;
        }
        Rectangle creerDepuisPoints(Point &p1, Point &p2){
            
        }
};

int main() {
    Point P1(0,0);
    Point P2(3,4);
    double d = P1.distance(P2);
    cout << "La distance entre P1 et P2 est : " << d << endl;
    Point pM = P1.milieu(P2);
    cout << "Le point milieu est : ";
    pM.afficher();
    return 0;
}