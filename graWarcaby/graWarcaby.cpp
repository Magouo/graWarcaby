#include <iostream>
#include <vector>

using namespace std;

int PUSTE = 0;
int GRACZ = 1;
int AI = 2;

struct Pionek {
	int kogo;
	bool damka;
};

struct Ruch {
	int poczatkowyWiersz;
	int poczatkowaKolumna;
	int koncowyWiersz;
	int koncowaKolumna;
	bool bicie;
};

vector<vector<Pionek>> plansza(8, vector<Pionek>(8, { PUSTE, false }));

void stworzPlansze()
{
	for (int wiersz = 0; wiersz < 3; wiersz++)
	{
		for (int kolumna = 0; kolumna < 8; kolumna++)
		{
			if ((wiersz % 2 == 0 && kolumna % 2 == 1) || (wiersz % 2 == 1 && kolumna % 2 == 0))
			{
				plansza[wiersz][kolumna] = { GRACZ, false };
				plansza[7 - wiersz][7 - kolumna] = { AI, false };
			}
		}
	}
}

bool koniecGry()
{
	bool graczMaPionki = false;
	bool aiMaPonki = false;
	for (int wiersz = 0; wiersz < 8; wiersz++)
	{
		for (int kolumna = 0; kolumna < 8; kolumna++)
		{
			if (plansza[wiersz][kolumna].kogo == GRACZ)
			{
				graczMaPionki = true;
			}
			if (plansza[wiersz][kolumna].kogo == AI)
			{
				aiMaPonki = true;
			}
		}
	}
	return !(graczMaPionki && aiMaPonki);
}

void pokazPlansze()
{
	cout << " ";
	for (int kolumna = 0; kolumna < 8; kolumna++)
	{
		cout << kolumna << " ";
	}
	cout << endl;
	for (int wiersz = 0; wiersz < 8; wiersz++)
	{
		cout << wiersz << " ";
		for (int kolumna = 0; kolumna < 8; kolumna++)
		{
			if (plansza[wiersz][kolumna].kogo == PUSTE)
			{
				cout << ".";
			}
			else if (plansza[wiersz][kolumna].kogo == GRACZ)
			{
				if (plansza[wiersz][kolumna].damka)
				{
					cout << "D";
				}
				else {
					cout << "G";
				}
			}
			else if (plansza[wiersz][kolumna].kogo = AI)
			{
				if (plansza[wiersz][kolumna].damka)
				{
					cout << "Q";
				}
				else {
					cout << "A";
				}
			}
			cout << " ";
		}
		cout << endl;
	}
	cout << endl;
}

vector<Ruch> znajdzBicia(vector<vector<Pionek>>& plansza, int gracz)
{
	vector<Ruch> ruchy;
	for (int wiersz = 0; wiersz < 8; wiersz++)
	{
		for (int kolumna = 0; kolumna < 8; kolumna++)
		{
			if (plansza[wiersz][kolumna].kogo == gracz)
			{
				vector < pair<int, int>> kierunki;
				if (plansza[wiersz][kolumna].damka)
				{
					kierunki.push_back(make_pair(2, 2));
					kierunki.push_back(make_pair(2, -2));
					kierunki.push_back(make_pair(-2, 2));
					kierunki.push_back(make_pair(-2, -2));
				}
				else {
					if (gracz == GRACZ)
					{
						kierunki.push_back(make_pair(2, 2));
						kierunki.push_back(make_pair(2, -2));
					}
					else {
						kierunki.push_back(make_pair(-2, 2));
						kierunki.push_back(make_pair(-2, -2));
					}
				}
				for (int i = 0; i < kierunki.size(); i++)
				{
					int nowyWiersz = wiersz + kierunki[i].first;
					int nowaKolumna = kolumna + kierunki[i].second;
					int srodekWiersz = wiersz + kierunki[i].first / 2;
					int srodekKolumna = kolumna + kierunki[i].second / 2;
					if (nowyWiersz >= 0 && nowyWiersz < 8 && nowaKolumna >= 0 && nowaKolumna < 8 && plansza[nowyWiersz][nowaKolumna].kogo == PUSTE && plansza[srodekWiersz][srodekKolumna].kogo != gracz && plansza[srodekWiersz][srodekKolumna].kogo != PUSTE)
					{
						Ruch ruch = { wiersz, kolumna, nowyWiersz, nowaKolumna, true };
						ruchy.push_back(ruch);
					}
				}
			}
		}
	}
	return ruchy;
}

vector<Ruch> znajdzRuchy(vector<vector<Pionek>>& plansza, int gracz)
{
	vector<Ruch> ruchy = znajdzBicia(plansza, gracz);

	if (ruchy.empty())
	{
		for (int wiersz = 0; wiersz < 8; wiersz++)
		{
			for (int kolumna = 0; kolumna < 8; kolumna++)
			{
				if (plansza[wiersz][kolumna].kogo == gracz)
				{
					vector<pair<int, int>> kierunki;
					if (plansza[wiersz][kolumna].damka)
					{
						kierunki.push_back(make_pair(1, 1));
						kierunki.push_back(make_pair(1, -1));
						kierunki.push_back(make_pair(-1, 1));
						kierunki.push_back(make_pair(-1, -1));
					}
					else {
						if (gracz == GRACZ)
						{
							kierunki.push_back(make_pair(1, 1));
							kierunki.push_back(make_pair(1, -1));
						}
						else {
							kierunki.push_back(make_pair(-1, 1));
							kierunki.push_back(make_pair(-1, -1));
						}
					}
					for (int i = 0; i < kierunki.size(); i++)
					{
						int nowyWiersz = wiersz + kierunki[i].first;
						int nowaKolumna = kolumna + kierunki[i].second;
						if (nowyWiersz >= 0 && nowyWiersz < 8 && nowaKolumna >= 0 && nowaKolumna < 8 && plansza[nowyWiersz][nowaKolumna].kogo == PUSTE)
						{
							Ruch ruch = { wiersz, kolumna, nowyWiersz, nowaKolumna, false };
							ruchy.push_back(ruch);
						}
					}
				}
			}
		}
	}
	return ruchy;
}

void wykonajRuch(vector<vector<Pionek>>& plansza, Ruch ruch)
{
	plansza[ruch.koncowyWiersz][ruch.koncowaKolumna] = plansza[ruch.poczatkowyWiersz][ruch.poczatkowaKolumna];
	plansza[ruch.poczatkowyWiersz][ruch.poczatkowaKolumna] = { PUSTE, false };
	if (ruch.bicie)
	{
		int srodekWiersz = (ruch.poczatkowyWiersz + ruch.koncowyWiersz) / 2;
		int srodekKolumna = (ruch.poczatkowaKolumna + ruch.koncowaKolumna) / 2;
		plansza[srodekWiersz][srodekKolumna] = { PUSTE, false };
	}
	if (plansza[ruch.koncowyWiersz][ruch.koncowaKolumna].kogo == GRACZ && ruch.koncowyWiersz == 7)
	{
		plansza[ruch.koncowyWiersz][ruch.koncowaKolumna].damka = true;
	}
	else if (plansza[ruch.koncowyWiersz][ruch.koncowaKolumna].kogo == AI && ruch.koncowyWiersz == 0)
	{
		plansza[ruch.koncowyWiersz][ruch.koncowaKolumna].damka = true;
	}
}

void cofnijRuch(vector<vector<Pionek>>& plansza, Ruch ruch, Pionek zbityPionek)
{
	plansza[ruch.poczatkowyWiersz][ruch.poczatkowaKolumna] = plansza[ruch.koncowyWiersz][ruch.koncowaKolumna];
	plansza[ruch.koncowyWiersz][ruch.koncowaKolumna] = { PUSTE, false };
	if (ruch.bicie)
	{
		int srodekWiersz = (ruch.poczatkowyWiersz + ruch.koncowyWiersz) / 2;
		int srodekKolumna = (ruch.poczatkowaKolumna + ruch.koncowaKolumna) / 2;
		plansza[srodekWiersz][srodekKolumna] = zbityPionek;
	}
	plansza[ruch.poczatkowyWiersz][ruch.poczatkowaKolumna].damka = (ruch.poczatkowyWiersz == 0 && plansza[ruch.poczatkowyWiersz][ruch.poczatkowaKolumna].kogo == AI) || (ruch.poczatkowyWiersz == 7 && plansza[ruch.poczatkowyWiersz][ruch.poczatkowaKolumna].kogo == GRACZ);
}

int ocenaPlanszy(vector<vector<Pionek>>& plansza)
{
	int ocena = 0;
	for (int wiersz = 0; wiersz < 8; wiersz++)
	{
		for (int kolumna = 0; kolumna < 8; kolumna++)
		{
			if (plansza[wiersz][kolumna].kogo == AI)
			{
				if (plansza[wiersz][kolumna].damka)
				{
					ocena += 3;
				}
				else {
					ocena += 1;
				}
			}
			else if (plansza[wiersz][kolumna].kogo == GRACZ)
			{
				if (plansza[wiersz][kolumna].damka)
				{
					ocena -= 3;
				}
				else {
					ocena -= 1;
				}
			}
		}
	}
	return ocena;
}

int minimax(vector<vector<Pionek>>& plansza, int glebokosc, bool maksGracz)
{
	if (glebokosc == 0 || koniecGry())
	{
		return ocenaPlanszy(plansza);
	}
	if (maksGracz)
	{
		int maxOcena = -100;
		vector<Ruch> legalneRuchy = znajdzRuchy(plansza, AI);
		for (int i = 0; i < legalneRuchy.size(); i++)
		{
			Ruch ruch = legalneRuchy[i];
			Pionek zbityPionek = { PUSTE, false };
			if (ruch.bicie)
			{
				int srodekWiersz = (ruch.poczatkowyWiersz + ruch.koncowyWiersz) / 2;
				int srodekKolumna = (ruch.poczatkowaKolumna + ruch.koncowaKolumna) / 2;
				zbityPionek = plansza[srodekWiersz][srodekKolumna];
			}
			wykonajRuch(plansza, ruch);
			int ocena = minimax(plansza, glebokosc - 1, false);
			cofnijRuch(plansza, ruch, zbityPionek);
			if (ocena > maxOcena)
			{
				maxOcena = ocena;
			}
		}
		return maxOcena;
	}
	else {
		int minOcena = 100;
		vector<Ruch> legalneRuchy = znajdzRuchy(plansza, GRACZ);
		for (int i = 0; i < legalneRuchy.size(); i++)
		{
			Ruch ruch = legalneRuchy[i];
			Pionek zbityPionek = { PUSTE, false };
			if (ruch.bicie)
			{
				int srodekWiersz = (ruch.poczatkowyWiersz + ruch.koncowyWiersz) / 2;
				int srodekKolumna = (ruch.poczatkowaKolumna + ruch.koncowaKolumna) / 2;
				zbityPionek = plansza[srodekWiersz][srodekKolumna];
			}
			wykonajRuch(plansza, ruch);
			int ocena = minimax(plansza, glebokosc - 1, true);
			cofnijRuch(plansza, ruch, zbityPionek);
			if (ocena < minOcena)
			{
				minOcena = ocena;
			}
		}
		return minOcena;
	}
}

Ruch znajdzNajlepszyRuch(vector<vector<Pionek>>& plansza)
{
	int najlepszaOcena = -100;
	Ruch najlepszyRuch;
	vector<Ruch> legalneRuchy = znajdzRuchy(plansza, AI);
	vector<vector<Pionek>> kopiaPlanszy = plansza;
	for (int i = 0; i < legalneRuchy.size(); i++)
	{
		Ruch ruch = legalneRuchy[i];
		Pionek zbityPionek = { PUSTE, false };
		if (ruch.bicie)
		{
			int srodekWiersz = (ruch.poczatkowyWiersz + ruch.koncowyWiersz) / 2;
			int srodekKolumna = (ruch.poczatkowaKolumna + ruch.koncowaKolumna) / 2;
			zbityPionek = kopiaPlanszy[srodekWiersz][srodekKolumna];
		}
		wykonajRuch(kopiaPlanszy, ruch);
		int ocena = minimax(kopiaPlanszy, 3, false);
		cofnijRuch(kopiaPlanszy, ruch, zbityPionek);
		if (ocena > najlepszaOcena)
		{
			najlepszaOcena = ocena;
			najlepszyRuch = ruch;
		}
	}
	return najlepszyRuch;
}

void ruchGracza()
{
	int poczatkowyWiersz;
	int poczatkowaKolumna;
	int koncowyWiersz;
	int koncowaKolumna;
	cout << "Podaj swoj ruch (poczatkowy wiersz poczatkowaKolumna koncowyWiersz koncowaKolumna): ";
	cin >> poczatkowyWiersz >> poczatkowaKolumna >> koncowyWiersz >> koncowaKolumna;
	while ((isdigit(poczatkowyWiersz) && isdigit(poczatkowaKolumna) && isdigit(koncowyWiersz) && isdigit(koncowyWiersz)))
	{
		poczatkowyWiersz = 0;
		poczatkowaKolumna = 0;
		koncowyWiersz = 0;
		koncowaKolumna = 0;
		cout << "Podaj swoj ruch (poczatkowy wiersz poczatkowaKolumna koncowyWiersz koncowaKolumna): ";
		cin >> poczatkowyWiersz >> poczatkowaKolumna >> koncowyWiersz >> koncowaKolumna;
	}
	Ruch ruch = { poczatkowyWiersz, poczatkowaKolumna, koncowyWiersz, koncowaKolumna, false };
	vector<Ruch> legalneRuchy = znajdzRuchy(plansza, GRACZ);
	bool poprawnyRuch = false;
	for (int i = 0; i < legalneRuchy.size(); i++)
	{
		if (legalneRuchy[i].poczatkowyWiersz == ruch.poczatkowyWiersz && legalneRuchy[i].poczatkowaKolumna == ruch.poczatkowaKolumna && legalneRuchy[i].koncowyWiersz == ruch.koncowyWiersz && legalneRuchy[i].koncowaKolumna == ruch.koncowaKolumna)
		{
			poprawnyRuch = true;
			ruch.bicie = legalneRuchy[i].bicie;
			break;
		}
	}
	if (poprawnyRuch)
	{
		wykonajRuch(plansza, ruch);
	}
	else {
		cout << "Niepoprawny ruchh, sproboj ponownie" << endl;
		ruchGracza();
	}
}

void gra() {
	stworzPlansze();
	pokazPlansze();
	while (!koniecGry())
	{
		ruchGracza();
		if (koniecGry())
		{
			break;
		}
		cout << "Plansza przed ruchem AI: " << endl << endl;
		pokazPlansze();
		Ruch ruchAI = znajdzNajlepszyRuch(plansza);
		wykonajRuch(plansza, ruchAI);
		cout << "AI ruszylo sie z " << ruchAI.poczatkowyWiersz << ", " << ruchAI.poczatkowaKolumna << " na " << ruchAI.koncowyWiersz << ", " << ruchAI.koncowaKolumna << endl << endl;
		cout << "Plansza po ruchu: " << endl << endl;
		pokazPlansze();
	}
	if (ocenaPlanszy(plansza) > 0)
	{
		cout << " AI wygralo" << endl;
	}
	else {
		cout << "Wygrales" << endl;
	}
}

int main()
{
	gra();
	return 0;
}