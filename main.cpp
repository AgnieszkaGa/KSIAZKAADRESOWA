#include <iostream>
#include <windows.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

struct Uzytkownik {
    int id;
    string nazwa, haslo;
};

struct NowyKontakt {

    int id, idZalogowanegoUzytkownika;
    string imie, nazwisko, numerTelefonu, adresZamieszkania, adresMail;
};

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

void wczytajUzytkownikowZPliku ( vector <Uzytkownik>  &uzytkownicy) {

    fstream plik ("Uzytkownicy.txt");
    if (!plik.is_open()) {
  //      cout<< "Nie mozna otworzyc pliku!";
        return;
            }

    string linia;

    while (getline(plik, linia)) {

        Uzytkownik uzytkownik;
        stringstream ss(linia);
        string pole;

        getline (ss, pole, '|');
        uzytkownik.id = stoi(pole);

        getline (ss, pole, '|');
        uzytkownik.nazwa = (pole);

        getline (ss, pole, '|');
        uzytkownik.haslo = (pole);

        uzytkownicy.push_back(uzytkownik);
    }
    plik.close();
}

void zapiszUzytkownikowDoPliku (const vector <Uzytkownik> &uzytkownicy) {
    ofstream plik ("Uzytkownicy.txt");
    if (!plik.is_open()) {
//        cout << "Nie mozna otworzyc pliku!" << endl;
        return;
    }

    for (const Uzytkownik &uzytkownik : uzytkownicy) {
        plik << uzytkownik.id << "|" << uzytkownik.nazwa << "|" << uzytkownik.haslo << "|" << endl;
    }
    plik.close();
}

void rejestracja ( vector <Uzytkownik> &uzytkownicy) {

    string nazwa, haslo;
    cout << "Podaj nazwe uzytkownika: " ;
    cin >> nazwa;

    for ( const Uzytkownik &uzytkownik : uzytkownicy) {
        if (uzytkownik.nazwa == nazwa) {
            cout << "Taki uzytkownik istnieje, wpisz inna nazwe uzytkownika" << endl;
            cin >> nazwa;
        }
    }

    cout << " Podaj haslo: " ;
    cin >> haslo;

    Uzytkownik nowyUzytkownik;
    nowyUzytkownik.nazwa = nazwa;
    nowyUzytkownik.haslo = haslo;
    nowyUzytkownik.id = uzytkownicy.empty() ? 1 : uzytkownicy.back().id + 1;

    uzytkownicy.push_back(nowyUzytkownik);

    cout << "Konto zostalo zalozone" << endl;
    Sleep (1000);

    zapiszUzytkownikowDoPliku (uzytkownicy);
}

int logowanie ( const vector <Uzytkownik> &uzytkownicy) {

    string nazwa, haslo;
    cout << " Podaj nazwe uzytkownika: ";
    cin >> nazwa;

    for (const Uzytkownik &uzytkownik : uzytkownicy) {
        if ( uzytkownik.nazwa == nazwa ) {
            for ( int proby = 0; proby <3; proby++) {
                cout << "Masz 3 proby wpisania hasla" << endl;
                cout << "Pozostalo prob:" << 3- proby << endl;
                cout << "-----------------------" << endl;
                cout << "Podaj haslo:" << endl;
                cin >> haslo;
                if ( uzytkownik.haslo == haslo) {
                    cout << " Zalogowales sie! " << endl;
                    Sleep (1000);
                    return uzytkownik.id;
                }
            }
            cout << "Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba" << endl;
            Sleep (3000);
            return 0;
        }
    }

    cout << " Nie ma uzytkownika z takim loginem. " << endl;
    Sleep(1500);
    return 0;
}

void zmianaHasla ( vector <Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika) {

    string haslo;
    cout << "Podaj nowe haslo: " << endl;
    cin >> haslo;

    for ( Uzytkownik &uzytkownik : uzytkownicy) {
        if (uzytkownik.id == idZalogowanegoUzytkownika) {
            uzytkownik.haslo = haslo;
            cout << " Haslo zostalo zmienione. " << endl;
            zapiszUzytkownikowDoPliku(uzytkownicy);
            Sleep (1500);
        }
    }
}

int dodajKontakt ( vector <NowyKontakt>  &kontakty, int idZalogowanegoUzytkownika, int ostatnieIdKontaktu) {

    NowyKontakt nowyKontakt;

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

    nowyKontakt.id = ostatnieIdKontaktu + 1 ;
    nowyKontakt.idZalogowanegoUzytkownika = idZalogowanegoUzytkownika;

    kontakty.push_back (nowyKontakt);

    fstream plik;
    plik.open ("ADRESACI.txt", ios::out | ios::app);

    if (!plik.is_open()) {
      //  cout << " Nie mozna otworzyc pliku! " << endl;
        return 0;
    }

    plik << nowyKontakt.id << "|" << nowyKontakt.idZalogowanegoUzytkownika << "|" << nowyKontakt.imie << "|" << nowyKontakt.nazwisko << "|" << nowyKontakt.numerTelefonu << "|" << nowyKontakt.adresMail << "|" <<  nowyKontakt.adresZamieszkania <<"|" << endl;
    plik.close();

    cout << " Kontakt zostal dodany. " << endl;
    system ("pause");
    return ostatnieIdKontaktu +1;
}

int wczytajKontaktyZPliku ( vector <NowyKontakt>  &kontakty, int idZalogowanegoUzytkownika) {

    NowyKontakt kontakt;
    int ostatnieIdKontaktu = 0;

    string linia;
    fstream plik;
    plik.open("ADRESACI.txt", ios::in );

    if (!plik.good()) {
//        cout<< "Nie mozna otworzyc pliku!";
        return ostatnieIdKontaktu;
    }

    while (getline(plik, linia)) {

        stringstream ss (linia);
        string pole;

        getline (ss, pole, '|');
        kontakt.id = stoi (pole);
        ostatnieIdKontaktu = kontakt.id;

        getline (ss, pole, '|');
        kontakt.idZalogowanegoUzytkownika = stoi (pole);

        if ( idZalogowanegoUzytkownika == kontakt.idZalogowanegoUzytkownika) {
            getline (ss, kontakt.imie, '|');
            getline (ss, kontakt.nazwisko, '|');
            getline (ss, kontakt.numerTelefonu, '|');
            getline (ss, kontakt.adresMail, '|');
            getline (ss, kontakt.adresZamieszkania, '|');

            kontakty.push_back(kontakt);
        }
    }
    plik.close();

    return ostatnieIdKontaktu ;
}

void wypiszDaneWyjsciowe( const NowyKontakt  &kontakt) {

    cout << " Id: " << kontakt.id << endl;
    cout << " Imie: " << kontakt.imie << endl;
    cout << " Nazwisko: " << kontakt.nazwisko << endl;
    cout << " Numer telefonu: " << kontakt.numerTelefonu << endl;
    cout << " E-mail: " << kontakt.adresMail << endl;
    cout << " Adres zamieszkania: " << kontakt.adresZamieszkania << endl;
    cout << endl;
}

void wyswietlListeKontaktow ( vector <NowyKontakt>  &kontakty ) {

    system ("cls");

    for (size_t i=0; i < kontakty.size(); i++) {
        cout << " >>> LISTA KONTAKTOW <<<<" <<endl << endl;
        wypiszDaneWyjsciowe (kontakty[i]);
    }
    system ("pause");
}

void wyszukajKontaktPoImieniu ( vector <NowyKontakt>  &kontakty) {

    system("cls");

    string szukaneImie;
    cout << " Podaj imie ktorego szukasz " << endl;
    szukaneImie = wczytajLinie();

    bool znaleziono = false;

    for ( NowyKontakt &kontakt : kontakty) {

        if (szukaneImie == kontakt.imie) {

            wypiszDaneWyjsciowe (kontakt);
            znaleziono = true;
        }
    }

    if (!znaleziono) {
        cout << "Kontakt o imieniu: " << szukaneImie << " - nie wystepuje w ksiazce adresowej " << endl;
    } else {
        cout << "Znaleziono  kontakt/y o imieniu " << szukaneImie << endl;
    }
    system ("pause");
}

void wyszukajKontaktPoNazwisku ( vector <NowyKontakt>  &kontakty) {

    system("cls");
    string szukaneNazwisko;

    cout << " Podaj nazwisko ktorego szukasz " << endl;
    szukaneNazwisko = wczytajLinie();

    bool znaleziono = false;

    for ( NowyKontakt &kontakt : kontakty) {

        if (szukaneNazwisko == kontakt.nazwisko) {
            wypiszDaneWyjsciowe (kontakt);
            znaleziono = true;
        }
    }

    if (!znaleziono) {
        cout << "Kontakt o nazwisku: " << szukaneNazwisko << " - nie wystepuje w ksiazce adresowej " << endl;
    } else {
        cout << "Znaleziono  kontakt/y o nazwisku "<< szukaneNazwisko << endl;
    }
    system ("pause");
}

int modyfikacjaPlikuZKontaktamiPoUsunieciu(int id) {

    int ostatnieIdKontaktu = 0;
    string linia, pole;

    ifstream plikWejsciowy("ADRESACI.txt");
    ofstream plikTymczasowy ("ADRESACI_TYMCZASOWI.txt");

    while (getline(plikWejsciowy, linia)) {
        istringstream iss(linia);
        string pole;
        getline(iss, pole, '|');

        if (stoi(pole) != id) {
            plikTymczasowy << linia << endl;
            ostatnieIdKontaktu = stoi(pole);
        }
    }
    plikWejsciowy.close();
    plikTymczasowy.close();
    remove("ADRESACI.txt");
    rename("ADRESACI_TYMCZASOWI.txt", "ADRESACI.txt");

    system ("pause");
    return ostatnieIdKontaktu;
}

int usunKontakt  ( vector <NowyKontakt>  &kontakty, int ostatnieIdKontaktu) {

    system("cls");
    int idDoUsuniecia = 0;

    if (kontakty.empty()) {
        cout << "Brak kontaktow." << endl;
        system("pause");
        return ostatnieIdKontaktu;
    }

    cout << "Podaj numer ID kontaktu do usuniecia: " << endl;
    idDoUsuniecia = wczytajLiczbeCalkowita();

    bool kontaktZnaleziony = false;

    for (vector  <NowyKontakt>::iterator itr = kontakty.begin(); itr != kontakty.end(); ++itr) {
        if (itr ->id == idDoUsuniecia) {
            kontaktZnaleziony = true;

            cout << "Czy na pewno chcesz usunac ten kontakt? (jesli tak wybierz nacisni klawisz t)" << endl;
            char potwierdzenie;
            cin >> potwierdzenie;

            if (potwierdzenie == 't' || potwierdzenie == 'T') {
                kontakty.erase(itr);
                ostatnieIdKontaktu = modyfikacjaPlikuZKontaktamiPoUsunieciu(idDoUsuniecia);
                cout << " Kontakt zostal usuniety " << endl;
            } else {
                cout << " Kontaktu nie usunieto. "  << endl;
            }
        }
    }


    if(!kontaktZnaleziony) {
        cout <<" Nie znaleziono kontaktu o podanym ID "<<endl;
    }
    system ("pause");

    return ostatnieIdKontaktu;
}

void modyfikacjaPlikuZKontaktamiPoEdycji(vector<NowyKontakt> &kontakty) {

    ifstream plikWejsciowy("ADRESACI.txt");
    ofstream plikTymczasowy("ADRESACI_TYMCZASOWI.txt");


    for (const NowyKontakt &kontakt : kontakty) {
        string linia;
        while (getline(plikWejsciowy, linia)) {
            istringstream iss(linia);
            string pole;
            getline(iss, pole, '|');

            if (kontakt.id == stoi(pole)) {
                plikTymczasowy << kontakt.id << "|" << kontakt.idZalogowanegoUzytkownika << "|"
                               << kontakt.imie << "|" << kontakt.nazwisko << "|"
                               << kontakt.numerTelefonu << "|" << kontakt.adresMail << "|"
                               << kontakt.adresZamieszkania << "|\n";
            } else {
                // Jeœli to nie jest kontakt do aktualizacji, po prostu zapisz liniê bez zmian
                plikTymczasowy << linia << "\n";
            }
        }
    }

    plikWejsciowy.close();
    plikTymczasowy.close();

    if (remove("ADRESACI.txt") != 0) {
        cout << "Blad usuwania pliku ADRESACI.txt" << endl;
    } else {
        if (rename("ADRESACI_TYMCZASOWI.txt", "ADRESACI.txt") != 0) {
            cout << "B³ad zmiany nazwy pliku." << endl;
        } else {
            cout << "Plik zaktualizowany pomyœlnie." << endl;
        }
    }

    system("pause");
}

void edytujKontakt(vector<NowyKontakt> &kontakty, int zalogowanyUzytkownikId) {

    system("cls");
    int idDoEdycji = 0;

    if (kontakty.empty()) {
        cout << "Brak kontaktow." << endl;
        system("pause");
        return;
    }

    bool kontaktZnaleziony = false;

    cout << "Podaj numer ID kontaktu do edycji: ";
    idDoEdycji = wczytajLiczbeCalkowita();

    for (NowyKontakt &kontakt : kontakty) {

        if (kontakt.id == idDoEdycji) {
            cout << "Aktualizacja kontaktu danych o ID " << idDoEdycji << endl;
            cout << "Wybierz numer danych do edycji:" << endl;
            cout << "1 - imie" << endl;
            cout << "2 - nazwisko" << endl;
            cout << "3 - numer telefonu" << endl;
            cout << "4 - adres e-mail" << endl;
            cout << "5 - adres zamieszkania" << endl;
            cout << "6 - Powrot" << endl;

            int wybor = wczytajLiczbeCalkowita();

            switch (wybor) {
            case 1:
                cout << "Wpisz nowe imiê: ";
                kontakt.imie = wczytajLinie();
                break;

            case 2:
                cout << "Wpisz nowe nazwisko: ";
                kontakt.nazwisko = wczytajLinie();
                break;

            case 3:
                cout << "Wpisz numer telefonu: ";
                kontakt.numerTelefonu = wczytajLinie();
                break;

            case 4:
                cout << "Wpisz adres e-mail: ";
                kontakt.adresMail = wczytajLinie();
                break;

            case 5:
                cout << "Wpisz adres zamieszkania: ";
                kontakt.adresZamieszkania = wczytajLinie();
                break;

            case 6:
                break;

            default:
                cout << "Nieprawid³owy wybor." << endl;
                break;
            }
            kontaktZnaleziony = true;
            modyfikacjaPlikuZKontaktamiPoEdycji(kontakty);
            break;
        } else {
            break;
        }
    }

    if (!kontaktZnaleziony) {
        cout << "Nie znaleziono kontaktu o podanym ID." << endl;
    }

    system("pause");
}

int main() {

    char wybor;
    vector <Uzytkownik> uzytkownicy;
    vector <NowyKontakt> kontakty;

    int idZalogowanegoUzytkownika = 0;
    int ostatnieIdKontaktu = 0;

    wczytajUzytkownikowZPliku(uzytkownicy);

    while(true) {

        cout << "<<<< MENU GLOWNE<<<<" << endl;
        cout << "---------------------" << endl;
        cout << " 1. Logowanie: " << endl;
        cout << " 2. Rejestracja: " << endl;
        cout << " 9. Zakoncz program " << endl;
        cout << "---------------------" << endl;
        cout << " Twoj wybor: " << endl;

        wybor = wczytajZnak();

        switch (wybor) {

        case '1':
            idZalogowanegoUzytkownika = logowanie (uzytkownicy);
            ostatnieIdKontaktu = wczytajKontaktyZPliku (kontakty, idZalogowanegoUzytkownika);
            break;

        case '2':
            rejestracja (uzytkownicy);
            break;

        case '9':
            exit (0);
            break;

        default:
            cout <<" Brak innych mozliwosci wyboru" << endl;
            break;
            system ("pasue");
        }

        while (idZalogowanegoUzytkownika) {
            system ("cls");

            cout << " >>> KSIAZKA ADESOWA <<<" << endl << endl;
            cout << "1. Wpisz nowy kontakt: " << endl;
            cout << "2. Wyszukaj kontakt po imieniu: " << endl;
            cout << "3. Wyszukaj kontakt po nazwisku: " << endl;
            cout << "4. Wyswietl liste kontaktow: " << endl;
            cout << "5. Usun kontakt: " << endl;
            cout << "6. Edytuj kontakt: " << endl;
            cout << "---------------------" << endl;
            cout << " 7. Zmiana hasla: " << endl;
            cout << " 8. Wylogowanie: " << endl;
            cout << "---------------------" << endl;
            cout << " Twoj wybor: " << endl;

            wybor = wczytajZnak();

            switch (wybor) {
            case '1':
                ostatnieIdKontaktu = dodajKontakt (kontakty, idZalogowanegoUzytkownika, ostatnieIdKontaktu);
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

            case '5':
                ostatnieIdKontaktu = usunKontakt(kontakty, ostatnieIdKontaktu);
                break;

            case '6':
                edytujKontakt(kontakty, idZalogowanegoUzytkownika);
                break;

            case '7':
                zmianaHasla(uzytkownicy, idZalogowanegoUzytkownika);
                break;

            case '8':
                kontakty.clear();
                idZalogowanegoUzytkownika = 0;
                break;

            default:
                cout << "Brak innej opcji do wyboru sprobo ponownie." << endl;
                system ("pause");
            }
        }
    }
    return 0;
}
