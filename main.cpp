#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <sstream>
#include <vector>

using namespace std;

struct NowyKontakt {
    static int ostatnieID;
    int id;
    string imie, nazwisko, numerTelefonu, adresZamieszkania, adresMail;
};

int NowyKontakt ::ostatnieID = 0;

void wczytywanieOstatnieID() {
    fstream plik;
    plik.open("KSIAZKAADRESOWA.txt", ios::in);

    if (plik.is_open()) {
        string linia;
        while (getline(plik, linia)) {
            stringstream ss(linia);
            string pole;
            getline(ss, pole, '|');
            int id = stoi(pole);
            NowyKontakt::ostatnieID = max(NowyKontakt::ostatnieID, id);
        }
        plik.close();
    }
}

string wczytajLinie() {
    string wejscie;
    getline (cin, wejscie);
    return wejscie;
}

char wczytajZnak() {
    string wejscie = "";
    char znak = {0};

    while (true) {
        getline (cin, wejscie);

        if ( wejscie.length() == 1) {
            znak = wejscie [0];
            break;
        }
        cout << "Wpisz ponownie pojedynczy znak. " << endl;
    }
    return znak;
}

int wczytajLiczbeCalkowita() {

    string wejscie = "";
    int liczba = 0;

    while (true) {
        getline( cin, wejscie);

        stringstream myStream(wejscie);
        if (myStream >> liczba)
            break;
        cout << "To nie jest liczba. Wpisz ponownie" << endl;
    }
    return liczba;
}

void dodajKontakt ( vector <NowyKontakt>  &kontakty, int &iloscKontaktow) {

    NowyKontakt nowyKontakt;

    if (kontakty.empty()) {
        nowyKontakt.id = 1;
    } else {
        nowyKontakt.id = ++NowyKontakt::ostatnieID;
    }

    cout << " Podaj imie:  " << endl;
    nowyKontakt.imie = wczytajLinie();
    cout << " Podaj nazwisko: " << endl;
    nowyKontakt.nazwisko = wczytajLinie();
    cout << " Podaj numer telefonu: " << endl;
    nowyKontakt.numerTelefonu = wczytajLinie();
    cout << " Podaj  adres e-mailL " << endl;
    nowyKontakt.adresMail = wczytajLinie();
    cout << " Podaj  adres zamieszkania: " << endl;
    nowyKontakt.adresZamieszkania = wczytajLinie();

    kontakty.push_back (nowyKontakt);

    fstream plik;
    plik.open ("KSIAZKAADRESOWA.txt", ios::out | ios::app);

    if (!plik.is_open()) {
        cout << " Nie mozna otworzyc pliku! " << endl;
    }

    plik << nowyKontakt.id << "|" << nowyKontakt.imie << "|" << nowyKontakt.nazwisko << "|" << nowyKontakt.numerTelefonu << "|" << nowyKontakt.adresMail << "|" <<  nowyKontakt.adresZamieszkania <<"|" << endl;
    plik.close();

    iloscKontaktow = kontakty.size();

    cout << " Kontakt zostal dodany. " << endl;
    system ("pause");
}

void wczytajKontaktyZPliku ( vector <NowyKontakt>  &kontakty) {

    string linia;
    fstream plik;
    plik.open("KSIAZKAADRESOWA.txt", ios::in );

    if (!plik.good()) {
        cout<< "Nie mozna otworzyc pliku!";
    }

    while (getline(plik, linia)) {
        NowyKontakt kontakt;
        stringstream ss (linia);
        string pole;

        getline (ss, pole, '|');
        kontakt.id = stoi (pole);

        getline (ss, kontakt.imie, '|');
        getline (ss, kontakt.nazwisko, '|');
        getline (ss, kontakt.numerTelefonu, '|');
        getline (ss, kontakt.adresMail, '|');
        getline (ss, kontakt.adresZamieszkania, '|');
        kontakty.push_back(kontakt);
    }
    plik.close();
}


void listaKontaktow (const NowyKontakt &kontakt) {
    {
        cout << " Id: " << kontakt.id << endl;
        cout << " Imie: " << kontakt.imie << endl;
        cout << " Nazwisko: " << kontakt.nazwisko << endl;
        cout << " Numer telefonu: " << kontakt.numerTelefonu << endl;
        cout << " E-mail: " << kontakt.adresMail << endl;
        cout << " Adres zamieszkania: " << kontakt.adresZamieszkania << endl;
        cout << endl;
    }
}


void wyswietlListeKontaktow ( vector <NowyKontakt>  &kontakty) {

    for (size_t i = 0; i < kontakty.size(); i++) {
        listaKontaktow (kontakty[i]);
    }
    system ("pause");
}


void wyszukajKontaktPoImieniu ( vector <NowyKontakt>  &kontakty) {

    system("cls");

    string szukaneImie;
    int liczbaWystapienImienia = 0;

    cout << " Podaj imie ktorego szukasz " << endl;
    cin >> szukaneImie;

    for (size_t i=0; i<kontakty.size(); i++) {

        if (szukaneImie == kontakty[i].imie) {
            listaKontaktow (kontakty[i]);
            liczbaWystapienImienia++;
        }
    }

    if (liczbaWystapienImienia == 0) {
        cout << " Kontakt o imieniu: " << szukaneImie << " nie wystepuje w ksiazce adresowej " << endl;
    }
    system ("pause");
}

void wyszukajKontaktPoNazwisku ( vector <NowyKontakt>  &kontakty) {

    system("cls");

    string szukaneNazwisko;
    int liczbaWystapienNazwiska = 0;

    cout << " Podaj nazwisko ktorego szukasz: " << endl;
    cin >> szukaneNazwisko;

    for (size_t i = 0; i < kontakty.size() ; i++) {
        if ( szukaneNazwisko == kontakty[i].nazwisko) {
            listaKontaktow (kontakty[i]);
            liczbaWystapienNazwiska++;
        }
    }

    if (liczbaWystapienNazwiska == 0) {
        cout << " Kontakt o nazwisku: " << szukaneNazwisko << " nie wystepuje w ksiazce adresowej " << endl;
    }

    system ("pause");
}

void zapisKontaktowDoPliku (const vector <NowyKontakt> &kontakty) {
    fstream plik;
    plik.open("KSIAZKAADRESOWA.txt", ios::out);

    if(!plik.is_open()) {
        cout << " Nie mozna otworzyc pliku! " << endl;
    }

    for (const NowyKontakt &edytowanyKontakt: kontakty) {

        plik << edytowanyKontakt.id <<"|" << edytowanyKontakt.imie <<"|" << edytowanyKontakt.nazwisko <<"|" << edytowanyKontakt.numerTelefonu <<"|" << edytowanyKontakt.adresMail <<"|" << edytowanyKontakt.adresZamieszkania <<"|" << endl;
    }
    plik.close();
}

void edytujKontakt ( vector <NowyKontakt>  &kontakty, int id) {

    bool kontaktZnaleziony = false;

    for ( NowyKontakt &kontakt : kontakty) {

        if (kontakt.id == id) {
            kontaktZnaleziony = true;
            cout << " Wybierz numer danych do edycji: " << endl;
            cout << " 1 - imie" << endl;
            cout << " 2 - nazwisko" << endl;
            cout << " 3 - numer telefonu" << endl;
            cout << " 4 - adres mail" << endl;
            cout << " 5 - adres zamieszkania" << endl;
            system ("pause");

            int wybor = wczytajLiczbeCalkowita();


            switch (wybor) {
            case 1:
                cout << " Wpisz nowe imie: ";
                kontakt.imie = wczytajLinie();
                system ("pause");
                break;

            case 2:
                cout << " Wpisz nowe nazwisko: ";
                kontakt.nazwisko = wczytajLinie();
                system ("pause");
                break;

            case 3:
                cout << " Wpisz numer telefonu: ";
                kontakt.numerTelefonu = wczytajLinie();
                system ("pause");
                break;

            case 4:
                cout << " Wpisz adres e-mail: ";
                kontakt.adresMail = wczytajLinie();
                system ("pause");
                break;

            case 5:
                cout << " Wpisz adres zamieszkania: ";
                kontakt.adresZamieszkania = wczytajLinie();
                break;

            case 6:
                return;
                break;

            default:
                cout << " Nieprawidlowy wybor. " << endl;
                break;
            }

            zapisKontaktowDoPliku(kontakty);
            cout << "Dane kontaktu zakutalizowane" << endl;
            system ("pause");
            return;
        }
    }
    if (!kontaktZnaleziony) {
        cout << "Nie znaleziono kontaktu o podanym ID." << endl;
        system ("pause");
    }

}

bool usunKontakt  ( vector <NowyKontakt>  &kontakty, int id) {

    bool znaleziony = false;
    size_t indeksUsunietego = 0;

    for (size_t i = 0; i < kontakty.size(); i++) {
        if (kontakty[i].id == id) {
            znaleziony = true;
            indeksUsunietego = i;
            break;
        }
    }
    if (!znaleziony) {
        cout << "Nie znaleziono kontaktu o podanym ID." << endl;
        system ("pause");
        return false;
    }
    cout << "Czy na pewno chcesz usunac ten kontakt? (jesli tak wybierz nacisni klawisz t)" << endl;

    char potwierdzenie;
    cin >> potwierdzenie;

    if (potwierdzenie == 't' || potwierdzenie == 'T') {
        kontakty.erase(kontakty.begin() + indeksUsunietego);

        if (kontakty.empty()) {
            NowyKontakt::ostatnieID = 0;
        } else if (id == NowyKontakt::ostatnieID) {
            NowyKontakt::ostatnieID = kontakty.back().id;
        }

        fstream plik;
        plik.open("KSIAZKAADRESOWA.txt", ios::out | ios::trunc);

        if (!plik.is_open()) {
            cout << "Nie mozna otworzyc pliku!" << endl;
            system("pause");
            return false;
        }

        for (const NowyKontakt &kontakt : kontakty) {
            plik << kontakt.id << "|" << kontakt.imie << "|" << kontakt.nazwisko << "|" << kontakt.numerTelefonu << "|" << kontakt.adresMail << "|" << kontakt.adresZamieszkania << "|" << endl;
        }

        plik.close();

        cout << "Kontakt zosta usuniety." << endl;
        system ("pause");
        return true;
    } else {
        cout << "Nie usunieto kontaktu" << endl;
        system ("pause");
        return false;
    }
}

int main() {


    vector <NowyKontakt> kontakty;
    char wybor;

    wczytywanieOstatnieID();
    wczytajKontaktyZPliku (kontakty);

    while (true) {

        system ("cls");
        cout << " >>> KSIAZKA ADESOWA <<<" << endl << endl;
        cout << "1. Wpisz nowy kontakt: " << endl;
        cout << "2. Wyszukaj kontakt po imieniu: " << endl;
        cout << "3. Wyszukaj kontakt po nazwisku: " << endl;
        cout << "4. Wyswietl liste kontaktow: " << endl;
        cout << "5. Usun kontakt: " << endl;
        cout << "6. Edytuj kontakt: " << endl;
        cout << "9. Wyjdz z listy kontaktow: " << endl;

        wybor = wczytajZnak();

        int iloscKontaktow = 0;
        switch (wybor) {
        case '1':
            dodajKontakt ( kontakty, iloscKontaktow);
            break;

        case '2':
            wyszukajKontaktPoImieniu (kontakty);
            break;

        case '3':
            wyszukajKontaktPoNazwisku (kontakty);
            break;

        case '4':
            wyswietlListeKontaktow (kontakty);
            break;

        case '5': {
            cout << " Podaj nr ID kontaktu ktory chcesz usunac " << endl;
            int idUsuniecia = wczytajLiczbeCalkowita();
            usunKontakt(kontakty, idUsuniecia);
            break;
        }

        case '6': {
            cout << " Podaj nr ID kontaktu ktory chcesz edytowac " << endl;
            int idEdycji = wczytajLiczbeCalkowita();
            edytujKontakt(kontakty, idEdycji);
            break;
        }

        case '9':
            exit (0);
            break;
        default:
            ;
        }
    }

    return 0;
}

