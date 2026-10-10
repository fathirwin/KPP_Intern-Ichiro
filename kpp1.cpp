#include <iostream>
using namespace std;

const int baris = 12;
const int kolom = 18;

const int ax[] = {1, 0, -1, 0};
const int ay[] = {0, -1, 0, 1};

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

class field {
private:
    char area[baris][kolom];

public:
    field(){
        for(int i = 0; i < baris; i++){
            for(int j = 0; j < kolom; j++){
                area[i][j] = '.';
            }
        }

        for(int i = 3; i < 9; i++){
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

        for (int i = 1; i <= 3; i++){ 
            for (int s = -i; s <= i; s++) {
                int sx = robot.getx() + ax[arahrobot] * i;
                int sy;
                
                if (arahrobot == 0 || arahrobot == 2) {
                    sy = robot.gety() + ay[arahrobot] * i + s;
                } else {
                    sy = robot.gety() + ay[arahrobot] * i;
                }
                
                if (sx >= 0 && sx < kolom && sy >= 0 && sy < baris) {
                    temparea[sy][sx] = '@';
                }
            }
        }

        if (bola.getx() >= 0 && bola.getx() < kolom && bola.gety() >= 0 && bola.gety() < baris) {
            temparea[bola.gety()][bola.getx()] = 'O';
        }

        if (robot.getx() >= 0 && robot.getx() < kolom && robot.gety() >= 0 && robot.gety() < baris) {
            temparea[robot.gety()][robot.getx()] = 'R';
        }

        //cout << "\033[H";
        for (int b = 0; b < baris; b++) {
            for (int k = 0; k < kolom; k++) {
                cout << temparea[b][k] << " ";
            }
            cout << "\n";
        }
        //cout << "\033[J" << flush;
    }
};

class ball {
private:
    point posisi; 
    int kx, ky;    

public:
    ball(int x, int y) {
        posisi.setx(x);
        posisi.sety(y);
        kx = 0;
        ky = 0;
    }

    point getposisi() const { 
        return posisi; 
    }

    void kick(int arah, int power) {
        kx = ax[arah] * power;
        ky = ay[arah] * power;
    }

    void update() {
        posisi.setx(posisi.getx() + kx);
        posisi.sety(posisi.gety() + ky);
        
        if (kx > 0) {
            kx = kx - 2;
            if (kx < 0) {
                kx = 0;
            }
        } else if (kx < 0) {
            kx = kx + 2;
            if (kx > 0) {
                kx = 0;
            }
        }

        if (ky > 0) {
            ky = ky - 2;
            if (ky < 0) {
                ky = 0;
            }
        } else if (ky < 0) {
            ky = ky + 2;
            if (ky > 0) {
                ky = 0;
            }
        }
    }
};


int main(){
    field arena;

    point robot;
    robot.setx(2);
    robot.sety(5); 

    point bola;
    bola.setx(4);
    bola.sety(3);

    int arahrobot = 0;

    arena.print(robot, bola, arahrobot);

    return 0;
}