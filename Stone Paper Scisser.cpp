
#include <iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

enum enGameChoice{Stone=1,Paper=2,Scissors=3};
enum enWinner{Player=1,Computer=2,Draw=3};

struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoice PlayerChoice=enGameChoice::Stone;
	enGameChoice ComputerChoice=enGameChoice::Stone;
	enWinner Winner=enWinner::Draw;
	string WinnerName="";

};

struct stGameResults
{
	short GameRounds = 0;
	short PlayerWinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes=0;
	enWinner GameWinner;
	string WinnerName="";

};

static int RandomNumber(int From, int To)
{
	int randomNumber=rand() % (To - From + 1) + From;
	return randomNumber;
}

static enGameChoice GetComputerChoice()
{

	return (enGameChoice)RandomNumber(1, 3);

}

static enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{

	if (RoundInfo.PlayerChoice ==RoundInfo.ComputerChoice)
	
		return enWinner::Draw;
	
	switch (RoundInfo.PlayerChoice)
	{
	case enGameChoice::Stone:
		return (RoundInfo.ComputerChoice== enGameChoice::Paper)?enWinner::Computer:enWinner::Player;
	case enGameChoice::Paper:
		return (RoundInfo.ComputerChoice == enGameChoice::Scissors) ? enWinner::Computer : enWinner::Player;
	case enGameChoice::Scissors:
		return (RoundInfo.ComputerChoice == enGameChoice::Stone) ? enWinner::Computer : enWinner::Player;
	}
	return enWinner::Draw;
}

static enWinner WhoWonTheGame(short PlayerWinTimes,short ComputerWinTimes)
{
	if (PlayerWinTimes > ComputerWinTimes)return enWinner::Player;
	else if (ComputerWinTimes > PlayerWinTimes)return enWinner::Computer;
	else return enWinner::Draw;

}

static string ChoiceName(enGameChoice Choice)
{
	string arrGameChoices[3] = { "Stone","Paper","Scissors" };
	return arrGameChoices[Choice - 1];
}

static string WinnerName(enWinner Winner)
{
	string arrWinnerName[3] = { "Player","Computer","No Winner(Draw)" };
	return arrWinnerName[Winner - 1];
}

static enGameChoice ReadPlayerChoice()
{
	short Choice;

	do {

		cout << "Your Choice : [1]:Stone, [2]:Paper, [3]:Scissors ? " << endl;
		cin >> Choice;

	} while (Choice < 1 || Choice>3);

	return (enGameChoice)Choice;

}

static void PrintRoundsResults(stRoundInfo RoundInfo)
{
		cout << "\n---------Results Round[" << RoundInfo.RoundNumber << "]----------\n" << endl;
		cout << "Your Choice     : " << ChoiceName(RoundInfo.PlayerChoice) << endl;
		cout << "Computer Choice : " << ChoiceName(RoundInfo.ComputerChoice) << endl;
		cout << "Round Winner    : [" << RoundInfo.WinnerName << "]\n";
		cout << "---------------------------------------------\n" << endl;
}

static int ReadRoundsNumber(string Message)
{

	int Number;
	do {
		cout << Message << endl;
		cin >> Number;

	} while (Number < 1 || Number>10);

	return Number;
}

static stGameResults PlayGame(short HowManyRounds)
{
	stRoundInfo RoundInfo;
	short PlayerWinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

	for (short GameRound = 1;GameRound <= HowManyRounds;GameRound++)
	{
		cout << "\nRound [" << GameRound << "] begins : \n";
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.PlayerChoice = ReadPlayerChoice();
		RoundInfo.ComputerChoice = GetComputerChoice(); 
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		if (RoundInfo.Winner == enWinner::Player)
			PlayerWinTimes++;
		else if (RoundInfo.Winner == enWinner::Computer)
			ComputerWinTimes++;
		else
			DrawTimes++;

		PrintRoundsResults(RoundInfo);

	}

	return { HowManyRounds,PlayerWinTimes,ComputerWinTimes,DrawTimes,
		WhoWonTheGame(PlayerWinTimes,ComputerWinTimes) }
	
;}

static void StartGame()
{
	char PlayerAgain = 'Y';
	
	do {
		system("cls");
		stGameResults GameResults = PlayGame(ReadRoundsNumber("How many the rounds game will be from 1 to 10 ?"));
		cout << "\nGame Over ! Winner : " << WinnerName(GameResults.GameWinner) << endl;
		
		cout << "\nDo you want to play again ? (Y/N) : ";
		cin >> PlayerAgain;
	} while (PlayerAgain == 'Y' || PlayerAgain == 'y');

}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	system("pause>0");
	return 0;

}
