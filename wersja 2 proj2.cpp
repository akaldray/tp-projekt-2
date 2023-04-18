#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <conio.h>
#include <ctime>

using namespace std;

void ekran_powitalny() {
    cout << "Zadanie 11\n\n";
    cout << "Autorki:\n";
    cout << "Nadia Tyburska 193329\n";
    cout << "Malgorzata Sokolinska 193434\n\n";
}

int rnd_losowanie(int n) {
    int liczba;
    srand(time(NULL));
    liczba = rand() % (n + 1);
    return liczba;
}

void wypisz_plansze(vector<queue<string>> plansza, int k, int w, int gracz) {
    //------
    for (int u = 0; u < k; u++) {
        cout << "------";
    }
    cout << endl;

    //klocki
    for (int j = 0; j < w; j++) {
        for (int i = 0; i < k; i++) {
            if (!plansza[i].empty()) {
                cout << plansza[i].front() << "  ";
                plansza[i].pop();
            }
            else
                cout << "      ";
        }cout << endl;
    }

    //ludzik
    for (int u = 0; u < gracz; u++) {
        cout << "      ";
    }
    cout << "=[]=  ";
    cout << endl;
    //------
    for (int u = 0; u < k; u++) {
        cout << "------";
    }
    cout << endl;
    //
}

void sterowanie_rozpiska() {
    cout << "Kliknij D aby poruszyc sie w prawo\nA aby poruszyc sie w lewo\nAby zbic bloczek kliknij W\nAby wyjsc z gry kliknij K\n\n";
}

int sprawdzanie(int liczba) {
    while (liczba < 1) {
        cout << "Bledna liczba - podaj inny parametr:\n";
        cin >> liczba;
    }
    return liczba;
}
int main()
{
    ekran_powitalny();
    bool koniecgry = 0;
    int k, b, r, n, rnd, w, gracz;
    int iloscruchow = 0;
    int zbite = 0;
    cout << "Podaj parametry:\n";

    cout << "Liczba wierszy:\n";
    cin >> w;
    w = sprawdzanie(w);

    cout << "Liczba kolumn:\n";
    cin >> k;
    k = sprawdzanie(k);
    gracz = k / 2;

    cout << "Liczba bloczkow w kolumnie:\n";
    cin >> b;
    while (b >= w || b < 1)
    {
        cout << "Bledna liczba - podaj inny parametr:\n";
        cin >> b;
    }

    cout << "Liczba r do dodawania bloczkow co ilosc r+rnd ruchow:\n";
    cin >> r;
    r = sprawdzanie(r);

    cout << "Maksymalna wartosc rnd:\n";
    cin >> n;
    n = sprawdzanie(n);
    rnd = rnd_losowanie(n);//zalozenie ze rnd jest ustalane tylko raz na poczatku gry
    vector<queue<string>> plansza;
    for (int i = 0; i < k; i++) {
        plansza.push_back(queue<string>());
    }
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < b; j++) {
            plansza[i].push("####");
        }
    }

    char sterowanie;
    while (!koniecgry)
    {
        system("cls");
        sterowanie_rozpiska();
        cout << "Zbite bloczki: " << zbite << endl;
        wypisz_plansze(plansza, k, w, gracz);

        cin >> sterowanie;
        switch (sterowanie) {
        case 'D':
        case 'd':
            if (gracz != k - 1)
                gracz++;
            break;
        case 'A':
        case 'a':
            if (gracz != 0)
                gracz--;
            break;
        case 'W':
        case 'w':
            if (plansza[gracz].size() != 0) {
                plansza[gracz].pop();
                iloscruchow++;
                zbite++;
            }
            break;
        case 'K':
        case 'k':
            return 0;
        default:
            break;
        }
        //dodawanie bloczkow
        if (iloscruchow % (r + rnd) == 0 && iloscruchow != 0)
        {
            //sprawdzanie czy bloczki dotkna gracza
            for (int i = 0; i < k; i++) {
                if ( plansza[i].size() == w) {
                    cout << "Koniec gry";
                    koniecgry = 1;
                    break;
                }
            }

            for (int i = 0; i < k; i++) {
                plansza[i].push("####");
            }
        }
        int suma_bloczkow_zero;
        suma_bloczkow_zero = 0;
        for (int i = 0; i < k; i++) {
            if (plansza[i].size() != 0) {
                suma_bloczkow_zero++;
            }
        }
        if (suma_bloczkow_zero == 0) {
            wypisz_plansze(plansza, k, w, gracz);
            cout << "Wygrana!";
            koniecgry = 1;
        }
    }
    return 0;

}
