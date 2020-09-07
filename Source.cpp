
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <string>
#include <sstream>


struct Player {
	char* mintasor[5];
	char padlovonal[7];
	char* fal[5];
	int pontszam;
	bool kezdojatekosjelzo;
};
struct Game {

	char ** korongok;
	int korongokszama;
	int * asztalcsempe;
	int *zsak;
	int *eldobott_csempek;
};

void EldobottCsempe(Game*game)
{
	bool ures_zsak = true;
	for (int j = 0; j < 5; j++)
	{
		if (game->zsak[j] > 0)
		{
			ures_zsak = false;
		}
	}
	if (ures_zsak)
	{
		for (int i = 0; i < 5; i++)
		{
			game->zsak[i] = game->eldobott_csempek[i];
		}
	}
}
int PontSzamitas(Player *player, int oszlop, int sor)
{
	int oszlopdbszam = 1;
	int sordbszam = 1;
	bool osszefuggo = true;
	for (int i = oszlop+1; i < 5 && osszefuggo; i++)
	{
		if (player->fal[i][sor] != '.')
		{
			oszlopdbszam++;
		}
		else
		{
			osszefuggo = false;
		}
	}
	osszefuggo = true;
	for (int i = oszlop-1; i >= 0 && osszefuggo; i--)
	{
		if (player->fal[i][sor] != '.')
		{
			oszlopdbszam++;
		}
		else
		{
			osszefuggo = false;
		}
	}
	osszefuggo = true;
	for (int i = sor+1; i < 5 && osszefuggo; i++)
	{
		if (player->fal[oszlop][i] != '.')
		{
			sordbszam++;
		}
		else
		{
			osszefuggo = false;
		}
	}
	osszefuggo = true;
	for (int i = sor-1; i >= 0 && osszefuggo; i--)
	{
		if (player->fal[oszlop][i] != '.')
		{
			sordbszam++;
		}
		else
		{
			osszefuggo = false;
		}
	}
	if (sordbszam == 1)
	{
		return oszlopdbszam;
	}
	else if (oszlopdbszam == 1)
	{
		return sordbszam;
	}
	else
	{
		return (sordbszam + oszlopdbszam);
	}
}
char ** KorongLetrehozas(int n) {


	char ** korongok = new char*[n];
	for (int i = 0; i < n; i++)
	{
		korongok[i] = new char[4];
	}
	return korongok;
}
char Csempefeltoltes(Game *jatek)
{
	bool jovalasztas = false;
	int darabszam = 0;
	char karakter = 'F';
	int i = 0;
	for (int i = 0; i < 5; i++)
	{
		darabszam += jatek->zsak[i];
	}
	/*if (darabszam == 0)
	{
		for (int i = 0; i < 5; i++)
		{
			jatek->zsak[i] = jatek->eldobott_csempek[i];

		}
	}*/
	while (!jovalasztas)
	{
		srand(time(NULL));
		int valasztas = rand() % darabszam;
		int hanyadik = 0;
		i = 0;
		karakter = 'F';
		while (hanyadik < valasztas)
		{
			hanyadik += jatek->zsak[i];
			if (hanyadik < valasztas)
			{
				i++;
			}
		}
		
		if (i == 0)
		{
			karakter = 'A';

		}
		else if (i == 1)
		{
			karakter = 'B';

		}
		else if (i == 2)
		{
			karakter = 'C';

		}
		else if (i == 3)
		{
			karakter = 'D';

		}
		else if (i == 4)
		{
			karakter = 'E';

		}
		if (jatek->zsak[i] != 0)

		{
			jovalasztas = true;
		}
	}
		jatek->zsak[i] -= 1;
		return karakter;

}
void TablaRajzolas(Game *jatek)
{
	std::cout << std::endl;
	std::cout << "Korongok: " << std::endl;
	for (int i = 0; i < jatek->korongokszama; i++)
	{
		
		std::cout << (i + 1) << " ";
		for (int j = 0; j < 4; j++)
		{
			
			std::cout << jatek->korongok[i][j]<<" ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << "Asztal közepén lévõ csempék: " << std::endl;
	char betuk[]{ 'A','B','C','D','E','X' };
	for (int i = 0; i < 6; i++)
	{
		std::cout << betuk[i] << " ";
		std::cout << jatek->asztalcsempe[i] << std::endl;

	}
}
void ForduloElokeszites(Game * jatek)
{
	for (int i = 0; i < jatek->korongokszama; i++)
	{
		
		for (int j = 0; j < 4; j++)
		{
			EldobottCsempe(jatek);
			char valasztott_csempe = Csempefeltoltes(jatek);
			jatek->korongok[i][j] = valasztott_csempe;
		}


	}
	jatek->asztalcsempe[5] = 1;
}
Player  *PlayerInit(int jatekosszam)
{
	if (jatekosszam == 2)
	{
		 Player *playertomb= new Player[2];
		 playertomb[0].pontszam = 0;
		 playertomb[1].pontszam = 0;
		for (int i = 0; i < 5; i++)
		{
			playertomb[0].fal[i] = new char[5];
			playertomb[1].fal[i] = new char[5];
			for (int j = 0; j < 5; j++)
			{
				playertomb[0].fal[i][j] ='.';
				playertomb[1].fal[i][j] = '.';
			}
		}
		for (int i = 0; i < 5; i++)
		{
			
				playertomb[0].mintasor[i] = new char[i+1];
				playertomb[1].mintasor[i] = new char[i+1];
				for (int j = 0; j <= i; j++)
				{
					playertomb[0].mintasor[i][j] = '-';
					playertomb[1].mintasor[i][j] = '-';
				}
			
			
		}
		for (int i = 0; i < 7; i++)
		{
			playertomb[0].padlovonal[i] = '_';
			playertomb[1].padlovonal[i] = '_';
		}
		return playertomb;
	}



	if (jatekosszam == 3)
	{
		Player *playertomb = new Player[3];
		playertomb[0].pontszam = 0;
		playertomb[1].pontszam = 0;
		playertomb[2].pontszam = 0;
		
		for (int i = 0; i < 5; i++)
		{
			playertomb[0].fal[i] = new char[5];
			playertomb[1].fal[i] = new char[5];
			playertomb[2].fal[i] = new char[5];
			for (int j = 0; j < 5; j++)
			{
				playertomb[0].fal[i][j] = '.';
				playertomb[1].fal[i][j] = '.';
				playertomb[2].fal[i][j] = '.';

			}
		}
		for (int i = 0; i < 5; i++)
		{
			
				playertomb[0].mintasor[i] = new char[i+1];
				playertomb[1].mintasor[i] = new char[i+1];
				playertomb[2].mintasor[i] = new char[i+1];

				for (int j = 0; j <= i; j++)
				{
					playertomb[0].mintasor[i][j] = '-';
					playertomb[1].mintasor[i][j] = '-';
					playertomb[2].mintasor[i][j] = '-';
				}
			
			
		}
		for (int i = 0; i < 7; i++)
		{
			playertomb[0].padlovonal[i] = '_';
			playertomb[1].padlovonal[i] = '_';
			playertomb[2].padlovonal[i] = '_';
		}
		return playertomb;
	}




	else
	{
		Player *playertomb = new Player[4];
		playertomb[0].pontszam = 0;
		playertomb[1].pontszam = 0;
		playertomb[2].pontszam = 0;
		playertomb[3].pontszam = 0;
		for (int i = 0; i < 5; i++)
		{
			playertomb[0].fal[i] = new char[5];
			playertomb[1].fal[i] = new char[5];
			playertomb[2].fal[i] = new char[5];
			playertomb[3].fal[i] = new char[5];
			for (int j = 0; j < 5; j++)
			{
				playertomb[0].fal[i][j] = '.';
				playertomb[1].fal[i][j] = '.';
				playertomb[2].fal[i][j] = '.';
				playertomb[3].fal[i][j] = '.';
			}
		}
		for (int i = 0; i < 5; i++)
		{
			
				playertomb[0].mintasor[i] = new char[i+1];
				playertomb[1].mintasor[i] = new char[i+1];
				playertomb[2].mintasor[i] = new char[i+1];
				playertomb[3].mintasor[i] = new char[i+1];

				for (int j = 0; j <= i; j++)
				{
					playertomb[0].mintasor[i][j] = '-';
					playertomb[1].mintasor[i][j] = '-';
					playertomb[2].mintasor[i][j] = '-';
					playertomb[3].mintasor[i][j] = '-';
				}
			
			/*else
			{
				playertomb[0].mintasor[0] = new char[1];
				playertomb[1].mintasor[0] = new char[1];
				playertomb[2].mintasor[0] = new char[1]
				playertomb[3].
				playertomb[0].mintasor[0][0] = '-';
				playertomb[1].mintasor[0][0] = '-';
				playertomb[2].mintasor[0][0] = '-';
				playertomb[3].mintasor[0][0] = '-';
			}*/
		}
		for (int i = 0; i < 7; i++)
		{
			playertomb[0].padlovonal[i] = '_';
			playertomb[1].padlovonal[i] = '_';
			playertomb[2].padlovonal[i] = '_';
			playertomb[3].padlovonal[i] = '_';
		}
		return playertomb;
	}
}
void PlayerRajzolas(Player  *player,int jatekossorszam)
{

	std::cout << "Éppen a(z) " << jatekossorszam << ". játékos köre van!" << std::endl;
	for (int i = 1; i < 6; i++)
	{
		std::cout << i << " ";
	}
	
	std::cout << "    Pontok: " << player->pontszam<< std::endl;
	for (int i = 0; i < 5; i++)
	{
		std::cout << player->fal[0][i] << " ";
	}
	std::cout << " 1" << "  ";
	std::cout << player->mintasor[0][0];
	std::cout << std::endl;


	for (int i = 0; i < 5; i++)
	{
		std::cout << player->fal[1][i] << " ";
	}
	std::cout << " 2" << "  ";
	std::cout << player->mintasor[1][0]<<player->mintasor[1][1];
	std::cout << std::endl;


	for (int i = 0; i < 5; i++)
	{
		std::cout << player->fal[2][i] << " ";
	}
	std::cout << " 3" << "  ";
	std::cout << player->mintasor[2][0] << player->mintasor[2][1]<<player->mintasor[2][2];
	std::cout << std::endl;

	for (int i = 0; i < 5; i++)
	{
		std::cout << player->fal[3][i] << " ";
	}
	std::cout << " 4" << "  ";
	std::cout << player->mintasor[3][0] << player->mintasor[3][1] << player->mintasor[3][2]<< player->mintasor[3][3];
	std::cout << std::endl;

	for (int i = 0; i < 5; i++)
	{
		std::cout << player->fal[4][i] << " ";
	}
	std::cout << " 5" << "  ";
	std::cout << player->mintasor[4][0] << player->mintasor[4][1] << player->mintasor[4][2] << player->mintasor[4][3]<< player->mintasor[4][4];
	std::cout << std::endl;
	std::cout << " ";
	for (int i = 0; i < 7; i++)
	{
		std::cout<<player->padlovonal[i] << "  ";
	}
	std::cout << std::endl;
	std::cout << "-1" << " " << "-1" << " " << "-2" << " " << "-2" << " " << "-2" << " " << "-3" << " " << "-3";

}
void Tobbijatekos(Player*playertomb[], int jatekosszam)
{
	system("cls");
	std::cout << "Ebben a részben a program megjeleníti az összes játékos tábláját!" << std::endl;
	for (int i = 0; i < jatekosszam; i++)
	{
		std::cout << std::endl;
		std::cout << (i + 1) << " jatekos: " << std::endl;
		PlayerRajzolas(playertomb[i], (i + 1));
	}
	system("pause");
	system("cls");


}
void CsempeValasztas(Game *game, Player *player,int jatekossorszam,Player playertomb[],int jatekosszam)
{
	
	int sorszam = game->korongokszama;
	char csempeszin = 'G';
	bool helyeskorongszin = false;
	bool helyessorszam = false;
	bool helyeskorong = false;
	bool helyescsempesorszam = false;
	int mintacsempesorszam = 6;
	int mintacsempesorszamindex = 6;
	int csempeszam = 0;
	int sorszamindex = 0;
	bool asztalkozepe = false;
	int asztalkozepeindex = 6;
	bool tobbijatekos = false;
	int mintasorindex = 6;
	int padlovonalindexszam = 6;
	std::string input = "";
	while (!helyessorszam&&!helyeskorong&&!helyeskorongszin)
	{
		system("cls");
		TablaRajzolas(game);

		std::cout << "Éppen a(z) " << jatekossorszam << ". játékos köre van!" << std::endl;
		std::cout << "Kérem adja meg a korong sorszámát!: " << std::endl;
		std::cout << "Amennyiben az asztal közepérõl szeretne venni adja meg a '0' sorszámot! "<<std::endl;
		std::cout << "Ha a többi játékos tábláját meg akarja nézni, kérem válasssza a 10-es számot!" << std::endl;
		std::cin >> input;
		std::stringstream myStream(input);
		if (myStream >> sorszam);

		if (sorszam <= game->korongokszama && sorszam>=0)
		{
			helyessorszam = true;
		}
		if (sorszam == 10)
		{
			tobbijatekos = true;
		}
		if (helyessorszam)
		{
			if (sorszam != 0)
			{
				sorszamindex = sorszam - 1;
			}
			else
			{
				sorszamindex = sorszam;
				asztalkozepe = true;
			}

			std::cout << "Kérem adja meg a csempe színét(A-B-C-D-E)!: " << std::endl;
			std::cin >> csempeszin;
			if (csempeszin == 'A' || csempeszin == 'B' || csempeszin == 'C' || csempeszin == 'D' || csempeszin == 'E')
			{
				helyeskorongszin = true;
			}

				if (helyeskorongszin)
				{
					
					if (!asztalkozepe)
					{
						for (int j = 0; j < 4; j++)
						{
							if (game->korongok[sorszamindex][j] == csempeszin)
							{
								helyeskorong = true;


							}
						}
						if (!helyeskorong)
						{
							std::cout << "Kérem olyan sorszámot és színt adjon meg, amelyik passzol." << std::endl;
							helyeskorongszin = false;
							helyessorszam = false;
							sorszam = game->korongokszama;
							csempeszin = 'G';
							
						}
					}
					else
					{
						char betuk[]{ 'A','B','C','D','E' };
						for (int i = 0; i < 5; i++)
						{
							if (betuk[i] == csempeszin)
							{
								asztalkozepeindex = i;
							}
						}
						csempeszam = game->asztalcsempe[asztalkozepeindex];
						game->asztalcsempe[asztalkozepeindex] = 0;

					}
				}
				if (!helyeskorongszin)
				{
					std::cout << "Kérem a csempe színét adja meg(A-B-C-D-E)!" << std::endl;
					helyessorszam = false;
					sorszam = game->korongokszama;
					csempeszin = 'G';
					
				}
			

			
		}
		if (!helyessorszam&&!tobbijatekos)
		{
			std::cout << "Kérem adjon meg olyan sorszámú korongott amely létezik." << std::endl;
			system("pause");
		}
		if (tobbijatekos)
		{
			//Tobbijatekos(playertomb, jatekosszam);
			system("cls");
			std::cout << "Ebben a részben a program megjeleníti az összes játékos tábláját!" << std::endl;
			for (int i = 0; i < jatekosszam; i++)
			{
				std::cout << std::endl;
				std::cout << (i + 1) << " jatekos: " << std::endl;
				PlayerRajzolas(&playertomb[i], (i + 1));
			}
			system("pause");
			system("cls");
			tobbijatekos = false;
		}
		system("cls");
	}


	
	while (!helyescsempesorszam)
	{
		
		bool rosszmintasorszam = false;
		system("cls");
		PlayerRajzolas(player,jatekossorszam);
		std::cout << std::endl;
		std::cout << "Éppen a(z) " << jatekossorszam << ". játékos köre van!" << std::endl;
		std::cout << "A választása: " << csempeszam << " db " << csempeszin << "színû csempe!" << std::endl;
		std::cout << "Kérem adja meg a mintasor sorszámát ahova tenni szeretné a csempéket!:" << std::endl;
		std::cout << "'0' jelöli ha a padlóvonalra szeretné tenni a csempéket!" << std::endl;
		std::cout << "Amennyiben egy mintasorban már van csempe, csak olyan színû csempéket tehet oda!" << std::endl;
		std::cout << "Csak olyan mintasorba teheti a kiválasztott csempéket, ahol a vele azonos sorszámú fal sorában nincsen olyan színû csempe" << std::endl;
		std::cin >> input;
		std::stringstream myStream(input);
		if (myStream >> mintacsempesorszam);
		if (mintacsempesorszam == 10)
		{
			tobbijatekos = true;
		}
		if (mintacsempesorszam <= 5 && mintacsempesorszam >= 0)
		{
			if (mintacsempesorszam > 0)
			{
				mintacsempesorszamindex = mintacsempesorszam - 1;

				for (int i = 0; i < 5 && !rosszmintasorszam; i++)
				{
					if (player->fal[mintacsempesorszamindex][i] == csempeszin)
					{

						rosszmintasorszam = true;

					}
					else if (i <= mintacsempesorszamindex)
					{
						char betuk[]{ 'A','B','C','D','E' };
						for (int j = 0; j < 5; j++)
						{
							if (betuk[j] != csempeszin)
							{
								if (player->mintasor[mintacsempesorszamindex][i] == betuk[j])
								{
									rosszmintasorszam = true;
								}
							}
						}
					}
					 if (i == 4 && !rosszmintasorszam)
					{
						helyescsempesorszam = true;
					}
				}
				if (rosszmintasorszam)
				{
					std::cout << "A mintasor melletti fal sorában már van ilyen színû csempe, kérem válasszon másikat, vagy a padlóvonalat!" << std::endl;
				}
			}
			else
			{
				helyescsempesorszam = true;
			}
			
		}
		else
		{
			std::cout << "Kérem 0-5 közötti számot adjon meg" << std::endl;
			mintacsempesorszam = 6;
			system("pause");
		}
	}
	
	if (sorszam != 0&&sorszam!=10)
	{
		
		for (int i = 0; i < 4; i++)
		{
			if (game->korongok[sorszamindex][i] == csempeszin)
			{
				game->korongok[sorszamindex][i] = '-';
				csempeszam++;
			}
			else
			{
				char betuk[]{ 'A','B','C','D','E' };
				for (int j = 0; j < 5; j++)
				{
					if (game->korongok[sorszamindex][i] == betuk[j])
					{
						game->asztalcsempe[j]++;
						game->korongok[sorszamindex][i] = '-';
					}
				}
			}
		}
		/*std::cout << "Anyádcsempe: " << csempeszam << std::endl;
		system("pause");*/

	}
	else if(sorszam!=10)
	{
		char betuk[]{ 'A','B','C','D','E' };
		for (int i = 0; i < 5; i++)
		{
			if (csempeszin == betuk[i])
			{
				if (game->asztalcsempe[5] == 1)
				{
					for (int j = 0; j < 7; j++)
					{
						if (player->padlovonal[i] == '_')
						{
							if (game->asztalcsempe[5] == 1)
							{
								player->padlovonal[j] = 'X';
								player->kezdojatekosjelzo = true;
								game->asztalcsempe[5] = 0;
								
							}
						}
					}
				}
				/*csempeszam = game->asztalcsempe[i];
				game->asztalcsempe[i] = 0;*/
				

			}
		}
	}
	
	if (sorszam != 10)
	{
		
		for (int i = 0; i < mintacsempesorszam; i++)
		{
			if (player->mintasor[mintacsempesorszamindex][i] == '-')
			{
				if (mintasorindex == 6)
				{
					mintasorindex = i;
				}
			}
		}
		bool padlovonalindex = false;
		for (int i = 0; i < 7 && !padlovonalindex; i++)
		{
			if (player->padlovonal[i] == '_')
			{
				padlovonalindexszam = i;
				padlovonalindex = true;
			}
		}
	}
	
	if (mintacsempesorszam > 0&&sorszam!=10)
	{
		for (int i = 0; i < csempeszam; i++)
		{
			if (mintasorindex + i <= mintacsempesorszamindex)
			{
				player->mintasor[mintacsempesorszamindex][mintasorindex + i] = csempeszin;
			}
			else
			{
				if (padlovonalindexszam == 7)
				{
					int i = 0;
					char betuk[]{ 'A','B','C','D','E' };
					for (int j = 0; j < 5; j++)
					{
						if (csempeszin == betuk[j])
						{
							i = j;
						}

					}
					game->eldobott_csempek[i]++;
				}
				else
				{

					player->padlovonal[padlovonalindexszam] = csempeszin;
					padlovonalindexszam++;


				}
			}
		}
	}
	else
	{
		for (int k = 0; k < csempeszam; k++)
		{
			if (padlovonalindexszam == 7)
			{

				int i = 0;
				char betuk[]{ 'A','B','C','D','E' };
				for (int j = 0; j < 5; j++)
				{
					if (csempeszin == betuk[j])
					{
						i = j;
					}

				}
				game->eldobott_csempek[i]++;
			}
			else
			{

				player->padlovonal[padlovonalindexszam] = csempeszin;
				padlovonalindexszam++;


			}
		}
	}
	/*std::cout << "Kérem adja meg egy csempe sorszámát!: " << std::endl;
	std::cout << "Amennyiben az asztal közepérõl szeretne venni adja meg a '0' számot! ";
	std::cin >> sorszam;
	std::cout << "Kérem adja meg a csempe színét(A-B-C-D-E)!: " << std::endl;
	std::cin >> csempeszin;*/

}
int TeliSorokSzamolasa(Player *player)
{
	int telisorokszama=0;
	bool teli = true;
	for (int i = 0; i < 5; i++)
	{
		teli = true;
		for (int j = 0; j < 5; j++)
		{
			if (player->fal[i][j] == '.')
			{
				teli = false;
			}
		}
		if (teli)
		{
			telisorokszama++ ;
		}
	}
	return telisorokszama;
}
int TelioszlopokSzamolasa(Player *player)
{
	int telioszlopokszama = 0;
	bool teli = true;
	for (int i = 0; i < 5; i++)
	{
		teli = true;
		for (int j = 0; j < 5; j++)
		{
			if (player->fal[i][j] == '.')
			{
				teli = false;
			}
		}
		if (teli)
		{
			telioszlopokszama++;
		}
	}
	return telioszlopokszama;
}
void FalraHelyezes(Game *game, Player *player,int jatekossorszam)
{
	int oszlopsorszam = 0;
	int oszlopsorszamindex = 0;
	bool helyesoszlopsorszam = false;
	char csempeszin = 'G';
	bool helyeslerakas = true;
	bool jooszlop[5] ={true,true,true,true,true};
	bool vanlehetsegeslepes = false;
	system("cls");
	PlayerRajzolas(player,jatekossorszam);
	for (int i = 0; i < 5; i++)
	{

		if (player->mintasor[i][i] != '-')
		{
			for (int j = 0; j < 5; j++)
			{
				for (int k = 0; k < 5; k++)
				{
					if (player->fal[j][k] == player->mintasor[i][i])
					{
						jooszlop[j] = false;
					}
				}
			}

			for (int j = 0; j < 5; j++)
			{
				if (jooszlop[j] == true)
				{
					vanlehetsegeslepes = true;
				}

			}


				if (vanlehetsegeslepes)
				{
					csempeszin = player->mintasor[i][i];
					while (!helyesoszlopsorszam)
					{
						std::cout << std::endl;
						std::cout << "Találtunk egy megtelt mintasort!" << std::endl;
						std::cout << "Kérem adja melyik oszlopba szeretné helyezni a '" << (i + 1) << "'-ik mintasor betelt '" << player->mintasor[i][i] << "' színû csempéjét!:" << std::endl;
						std::cin >> oszlopsorszam;

						if (oszlopsorszam >= 1 && oszlopsorszam <= 5)
						{
							if (player->fal[i][oszlopsorszam] == '.')
							{
								helyesoszlopsorszam = true;
								//player->fal[i][oszlopsorszam]=csempeszin;
							}
							else
							{
								std::cout << "Sajnos már van ott csempe, ahova tenni szeretné!\n" << std::endl;
								system("pause");

							}
							if (helyesoszlopsorszam)
							{
								oszlopsorszamindex = oszlopsorszam - 1;

								/*for (int j = 0; j < 5; j++)
								{
									for (int k = 0; k < 5; k++)
									{
										if (player->fal[j][k] == csempeszin || player->fal[j][k] == csempeszin)
										{
											helyeslerakas = false;
										}
									}
								}*/
								for (int j = 0; j < 5; j++)
								{
									if (player->fal[j][oszlopsorszamindex] == csempeszin)
									{
										helyeslerakas = false;
									}
								}

								if (helyeslerakas)
								{
									player->fal[i][oszlopsorszamindex] = csempeszin;
									player->pontszam += PontSzamitas(player, i, oszlopsorszamindex);
									for (int j = 0; j < 5; j++)
									{
										if ((i - j) >= 0)
										{
											player->mintasor[i][i - j] = '-';
											char betuk[]{ 'A','B','C','D','E' };
											for (int k = 0; k < 5; k++)
											{
												if (betuk[k] == csempeszin)
												{
													game->eldobott_csempek[k]++;
												}
											}
										}

									}
								}

							}
							else
							{
							}
						}
						else
						{
							std::cout << "Kérem 1-5 közötti számot adjon meg!" << std::endl;
							system("pause");
						}

					}
				}
				else
				{
					std::cout << "Nincs lehetséges lépés! Az össes mintasorban lévõ csempe a padlóvonalra kerül" << std::endl;
					system("pause");


				}
			
			
		}
	}
}
int Bonuszpontokszamitasa(Player *player)
{
	char csempeszin;
	int csempek[5] = { 0,0,0,0,0 };
	int bonuszpontok=0;
	int csempebonuszpont=0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			csempeszin = player->fal[i][j];
			char betuk[]{ 'A','B','C','D','E' };
			for(int k=0;k<5;k++)
			{
				if (betuk[k] == csempeszin)
				{
					csempek[k]++;
				}

			}

		}
	}
	for (int i = 0; i < 5; i++)
	{
		if (csempek[i] == 5)
		{
			csempebonuszpont += 10;
		}
	}
	bonuszpontok += csempebonuszpont;
	bonuszpontok += (TelioszlopokSzamolasa(player) * 7);
	bonuszpontok += (TeliSorokSzamolasa(player) * 2);
	std::cout << "Bónusz pontok:" << std::endl;
	std::cout << "Teli sorok száma: " << TeliSorokSzamolasa(player) << " Érte járó bónuszpont: " << (TeliSorokSzamolasa(player) * 2) << std::endl;
	std::cout << "Teli oszlopok száma: " << TelioszlopokSzamolasa(player) << " Érte járó bónuszpont: " << (TelioszlopokSzamolasa(player) * 7) << std::endl;
	std::cout << "Minden olyan csempéért járó bónuszpont, amibõl 5 darab van a falon: " << csempebonuszpont << std::endl;
	std::cout << "Így összesen" << bonuszpontok << "bónuszpont jár!" << std::endl;
	return bonuszpontok;
}
bool VaneCsempe(Game* game)
{
	bool van = false;
	for (int i = 0; i < game->korongokszama&&!van; i++)
	{
		for (int j = 0; j < 4&&!van; j++)
		{
			char betuk[]{ 'A','B','C','D','E' };
			for (int k = 0; k < 5&&!van; k++)
			{

				if (game->korongok[i][j]==betuk[k])
				{
					van = true;
				}
			}
		}
	}
	if (!van)
	{
		for (int i = 0; i < 5; i++)
		{
			if (game->asztalcsempe[i] != 0)
			{
				van = true;
			}
		}
	}
	return van;

}
bool vaneTeliMintasor(Player *player)
{
	bool vanlehetsegeslepes = false;




	for (int i = 0; i < 5; i++)
	{
		if (player->mintasor[i][i] != '-')
		{
			vanlehetsegeslepes = true;
		}
	}
			return vanlehetsegeslepes;
}
void Padlovonallevonas(Player *player,int jatekosszam)
{
	int padlovonaltomb[7] = { -1,-1,-2,-2,-2,-3,-3 };
	
	int levonas = 0;
	for (int j = 0; j < jatekosszam; j++)
	{
		for (int i = 0; i < 7; i++)
		{
			if (player->padlovonal[i] != '_')
			{
				levonas += padlovonaltomb[i];
				player->padlovonal[i] = '_';

			}
		}
	}
	player->pontszam += levonas;
	
	



}

int main()
{

	setlocale(LC_ALL, "");
	int csempek[5] = { 20,20,20,20,20 }; //csempék inicializálása
	int jatekosszam = 0;
	int db = 0;
	bool jatekvege = false;
	bool vanlehetsegeslepes = false;
	std::string input = "";
	while (jatekosszam > 4 || jatekosszam < 2)
	{
		std::cout << "Kérem adja meg hányan játsszák a játékot!(2-3-4): " << std::endl;
		std::cin >> input;
		std::stringstream myStream(input);
		if (myStream >> jatekosszam);
		
	}
	int korongok_szama = jatekosszam * 2 + 1;
	char** korongtomb = KorongLetrehozas(korongok_szama);
	bool van = false;
	Game jatek;
	jatek.korongok = korongtomb;
	jatek.korongokszama = korongok_szama;
	jatek.asztalcsempe = new int[6]{ 0,0,0,0,0,1 };
	jatek.zsak = csempek;
	jatek.eldobott_csempek = new int[5];
	Player *playertomb = PlayerInit(jatekosszam);
	int jatekosindex = 0;
	int kezdojatekosindex = 0;
	int zarojatekosindex = jatekosszam - 1;
	/*Player* player1 = &playertomb[0];
	Player *player2 = &playertomb[1];*/
	/*	for (int i = 0; i < korongok_szama; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				korongtomb[i][j] = Csempefeltoltes(&jatek);
			}*/
		ForduloElokeszites(&jatek);
		van = VaneCsempe(&jatek);
		
		while (!jatekvege)
		{
			van = VaneCsempe(&jatek);
			for (int i = 0; i < jatekosszam; i++)
			{

			
				if (playertomb[i].kezdojatekosjelzo == true)
				{
					kezdojatekosindex = i;
					playertomb[i].kezdojatekosjelzo = false; 
					zarojatekosindex = kezdojatekosindex - 1;
					if (kezdojatekosindex == 0)
					{
						zarojatekosindex = jatekosszam - 1;
					}
				}
			}

			while (van)
			{
				
					CsempeValasztas(&jatek, &playertomb[jatekosindex],(jatekosindex+1),playertomb,jatekosszam);
					system("cls");
					PlayerRajzolas(&playertomb[jatekosindex],(jatekosindex+1));
					system("pause");
					van=VaneCsempe(&jatek);
					if (jatekosindex == jatekosszam-1)
					{
						jatekosindex = 0;
					}
					else
					{
						jatekosindex++;
					}
					
			}
			jatekosindex = kezdojatekosindex;
			for (int i = 0; i < jatekosszam&&!vanlehetsegeslepes; i++)
			{
				vanlehetsegeslepes = vaneTeliMintasor(&playertomb[i]);
			}
			while(vanlehetsegeslepes)
			{
				vanlehetsegeslepes = false;
				for (int i = 0; i < jatekosszam && !vanlehetsegeslepes; i++)
				{
					vanlehetsegeslepes = vaneTeliMintasor(&playertomb[i]);
				}
				if (vanlehetsegeslepes)
				{
					FalraHelyezes(&jatek, &playertomb[jatekosindex], (jatekosindex + 1));
					system("cls");
					PlayerRajzolas(&playertomb[jatekosindex], (jatekosindex + 1));
					system("pause");
					if (jatekosindex == jatekosszam - 1)
					{
						jatekosindex = 0;
					}
					else
					{
						jatekosindex++;
					}
				}
			}
			ForduloElokeszites(&jatek);
			
			for (int i = 0; i < jatekosszam; i++)
			{
				if (TeliSorokSzamolasa(&playertomb[i]) > 0)
				{
					jatekvege = true;
				}
				Padlovonallevonas(&playertomb[i], jatekosszam);
			}

			if (!jatekvege)
			{
				system("cls");
				std::cout << "Vége van a körnek, indul a következõ!" << std::endl;
				system("pause");
			}
		}
	
		/*ForduloElokeszites(&jatek);
		std::cout << std::endl;
		TablaRajzolas(&jatek);
		std::cout << std::endl;
		PlayerRajzolas(&playertomb[0]);
		CsempeValasztas(&jatek,&playertomb[0]);
		system("pause");
		PlayerRajzolas(&playertomb[0]);

		system("pause");
		CsempeValasztas(&jatek,&playertomb[0]*/
		/*for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				std::cout << playertomb[0].fal[i][j] << " ";
			}
			std::cout << std::endl;
		}*/ 
		/*for (int i = 0; i < 5; i++)
		{
			std::cout << "Csempek szama: " << csempek[i] << std::endl;
		}
		std::cout << std::endl;*/
			


		
		/*std::cout << "darabszam" << db << std::endl;
			
		std::cin >> jatekosszam;*/

	return 0;

	
}