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
    int getx() const {
        return x_val;
    }
    int gety() const {
        return y_val;
    }
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

class robot {
protected:
    point posisi;
    int arah;
    int kecepatan;

public:
    robot(int x, int y, int dir) {
        posisi.setx(x);
        posisi.sety(y);
        arah = dir;
        kecepatan = 1;
    }

    point getposisi() const { 
        return posisi; 
    }

    int getarah() const { 
        return arah; 
    }

    void gerak(int arahbaru) {
        int xbaru = posisi.getx() + ax[arahbaru] * kecepatan;
        int ybaru = posisi.gety() + ay[arahbaru] * kecepatan;
        
        if (xbaru < 0 || xbaru >= kolom || ybaru < 0 || ybaru >= baris) {
            cout << "robot keluar lapangan\n";
        } else {
            arah = arahbaru;
            posisi.setx(xbaru);
            posisi.sety(ybaru);
        }
    }

    virtual void think(const point& posisibola) = 0; 
    
    bool cekbola(const point& posisibola) const {
        for (int i = 1; i <= 3; i++) {
            point depan;
            depan.setx(posisi.getx() + ax[arah] * i);
            depan.sety(posisi.gety() + ay[arah] * i);
            
            if (depan == posisibola) {
                return true;
            }
        }
        return false;
    }
};


class striker : public robot {
private:
    int kondisi; 

public:
    striker(int x, int y) : robot(x, y, 0) {
        kondisi = 0;
    }

    void think(const point& posisibola) {
        if (kondisi == 0 || kondisi == 1) {
            if (cekbola(posisibola)) {
                kondisi = 2; 
                cout << "Bola di depan\n";
            } else {
                kondisi = 1;
                cout << "Mencari bola\n";
            }
        } else if (kondisi == 2) {
            cout << "mode Kick.\n";
        }
    }

    bool siapnendang() const { 
        if (kondisi == 2) {
            return true;
        } else {
            return false;
        }
    }

    void reset() { 
        kondisi = 0; 
    }
};

class simulator {
private:
    field arena;
    ball bola;
    striker penyerang;
    int tick;

public:
    simulator() : bola(0, 0), penyerang(5, 6) {
        tick = 0;
    }

    void run() {
        while (tick < 50) { 
            cout << "\nTick " << tick << "\n";
            arena.print(penyerang.getposisi(), bola.getposisi(), penyerang.getarah());

            penyerang.think(bola.getposisi());

            if (penyerang.siapnendang()) {
                point depan;
                depan.setx(penyerang.getposisi().getx() + ax[penyerang.getarah()]);
                depan.sety(penyerang.getposisi().gety() + ay[penyerang.getarah()]);
                
                if (depan == bola.getposisi()) {
                    bola.kick(penyerang.getarah(), 6); 
                    penyerang.reset();
                    cout << "tendang bola\n";
                } else {
                    penyerang.gerak(penyerang.getarah()); 
                    cout << "mendekati bola.\n";
                }
            } else {
                penyerang.gerak(penyerang.getarah());
                cout << "gerak\n";
            }

            bola.update();

            if (bola.getposisi().getx() >= kolom - 1) {
                cout << "\nGOAL!\n";
                break;
            }

            tick++;
        }
        
        if (tick >= 50) {
            cout << "\nwaktu habis\n";
        }
    }
};


int main(){
    simulator upin;
    upin.run();

    return 0;
}