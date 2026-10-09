#include <iostream>
using namespace std;

const int baris = 12;
const int kolom = 18;

class point{
private:
    int x_val;
    int y_val;

public:
    int getx() const {return x_val;}
    int gety() const {return y_val;}

    void setx(int x){
        x_val = x;
    }
    void sety(int y){
        y_val = y;
    }

    bool operator==(const point& other) const {
        return x_val == other.x_val && y_val == other.y_val;
    }
};

class lapangan {
private:
    char area[baris][kolom];

public:
    lapangan(){
        for(int i = 0; i < baris; i++){
            for(int j = 0; j < kolom; j++){
                area[i][j] = '.';
            }
        }

        for(int i = 0; i < baris; i++){
            area[i][kolom-1] = '#';
        }
    }

    void print (const point& robot, const point& bola, int arahrobot){
        char temparea[baris][kolom];

        for(int i = 0; i < baris; i++){
            for(int j = 0; j < kolom; j++){
                temparea[i][j] = area[i][j];
            }
        }
    }
};

int main(){

    return 0;
}