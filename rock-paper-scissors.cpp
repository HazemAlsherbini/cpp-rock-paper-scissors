#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

enum enPlayingItems { Stone = 1, Paper = 2, Scissor = 3 };

enum enWhoWin { Player = 1, Computer = 2, NoOne = 3 };

struct strGameResults
{
    short GameRounds = 0;
    short PlayerWins = 0;
    short ComputerWins = 0;
    short DrawTimes = 0;
    enWhoWin FinalWinner;
};

struct strRoundResults
{
    short RoundNumber = 0;
    enPlayingItems PlayerChoice;
    enPlayingItems ComputerChoice;
    enWhoWin Winner;

};

int RandomNumbersInRange(int from, int to)
{
    int random = rand() % (to - from + 1) + from;
    return random;
}

short ReadingNumOfRounds()
{
    short NumberOfRounds;
    
    do {
    cout << "\nHow many rounds 1 to 10?\n";
    cin >> NumberOfRounds;
    } while (NumberOfRounds < 1 || NumberOfRounds > 10);

    return NumberOfRounds;
}

void RoundBegin(short NumOfRound)
{
    cout << "\nRound [" << NumOfRound << "] Begins:\n";
    cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissor ?\n";
}

enPlayingItems ReadingPlayerChoice()
{
    short choice = 0;
    while (choice < 1 || choice > 3)
    {
        cout << "\nEnter A Correct Choice: ";
        cin >> choice;
    }
    return (enPlayingItems)choice;
}

enPlayingItems ReadingComputerChoice()
{
    return (enPlayingItems)RandomNumbersInRange(1, 3);
}

string PrintChoice(enPlayingItems PlayerChoice)
{
    const string Choice[] = { "Stone" , "Paper" , "Scissor" };
    return Choice[PlayerChoice - 1];
}

enWhoWin DetermineRoundWinner(const strRoundResults& RoundResults)
{
    if (RoundResults.PlayerChoice == RoundResults.ComputerChoice)
        return enWhoWin::NoOne;

    switch (RoundResults.PlayerChoice)
    {
    case enPlayingItems::Stone :
        return (RoundResults.ComputerChoice == enPlayingItems::Paper) ? enWhoWin::Computer : enWhoWin::Player;

    case enPlayingItems::Paper:
        return (RoundResults.ComputerChoice == enPlayingItems::Scissor) ? enWhoWin::Computer : enWhoWin::Player;

    case enPlayingItems::Scissor:
        return (RoundResults.ComputerChoice == enPlayingItems::Stone) ? enWhoWin::Computer : enWhoWin::Player;

    default:
        return enWhoWin::NoOne;

    }

}

enWhoWin DetermineGameWinner(const strGameResults& GameResults)
{
    if (GameResults.PlayerWins > GameResults.ComputerWins)
        return enWhoWin::Player;
    else if (GameResults.ComputerWins > GameResults.PlayerWins)
        return enWhoWin::Computer;
    else
        return enWhoWin::NoOne;
}

string PrintWhoWin(enWhoWin WhoWin)
{
    const string Choice[] = { "Player" , "Computer" , "NoOne" };
    return Choice[WhoWin - 1];
}

void PrintRoundResult(const strRoundResults& RoundResults, short NumOfRound)
{
    cout << "\n__________________ Round [" << NumOfRound << "] ________________\n";
    cout << "\nPlayer   Choice: " << PrintChoice(RoundResults.PlayerChoice) << "\n";
    cout << "Computer Choice: " << PrintChoice(RoundResults.ComputerChoice) << "\n";
    cout << "Round Winner   : " << PrintWhoWin(RoundResults.Winner) << "\n\n";
    cout << "_______________________________________________\n";
}

void RingBell()
{
    cout << "\a";
}

void NumOfTabs(short NumberOfTabs)
{
    for (int i = 1; i <= NumberOfTabs; i++)
        cout << "\t";
}

void PrintFinalResults(const strGameResults& GameResults)
{
    cout << "\n\n";

    NumOfTabs(3);
    cout << "--------------------------------------------------\n";
    NumOfTabs(5);
    cout << "++ Game Over ++\n";
    NumOfTabs(3);
    cout << "__________________________________________________\n\n";

    NumOfTabs(3);
    cout << "_______________ [Game Results] ___________________\n";
    NumOfTabs(3);
    cout << "Game   Rounds       : " << GameResults.GameRounds << endl;
    NumOfTabs(3);
    cout << "Player Won Times    : " << GameResults.PlayerWins << endl;
    NumOfTabs(3);
    cout << "Computer Won Times  : " << GameResults.ComputerWins << endl;
    NumOfTabs(3);
    cout << "Draw   Times        : " << GameResults.DrawTimes << endl;
    NumOfTabs(3);
    cout << "Final Winner        : " << PrintWhoWin(GameResults.FinalWinner) << endl;

    NumOfTabs(3);
    cout << "__________________________________________________\n";

}

char ReadingYESorNO(string message)
{
    char Choice;
    do {
        NumOfTabs(3);
        cout << message;
        cin >> Choice;
        Choice = tolower(Choice);

    } while (Choice != 'y' && Choice != 'n');
    return Choice;
}

void ClearScreen() {
    system("cls");
}

bool PlayMore()
{
    char Choice = ReadingYESorNO("\nDo you Want To Play More? [Y] or [N] : ");

    if (Choice == 'y')
    {
        ClearScreen();
        return true;
    }
    else
        return false;
}

strGameResults PlayGame()
{
    strGameResults GameResults;
    GameResults.GameRounds = ReadingNumOfRounds();
    
    strRoundResults RoundResults;

    for (short Rounds = 1; Rounds <= GameResults.GameRounds; Rounds++)
    {
        RoundBegin(Rounds);
        RoundResults.PlayerChoice = ReadingPlayerChoice();
        RoundResults.ComputerChoice = ReadingComputerChoice();

        RoundResults.Winner = DetermineRoundWinner(RoundResults);
        PrintRoundResult(RoundResults , Rounds);

        if (RoundResults.Winner == enWhoWin::Player)
        {
            GameResults.PlayerWins++;
            system("color 2F");
        }
        else if (RoundResults.Winner == enWhoWin::Computer)
        {
            GameResults.ComputerWins++;
            RingBell();
            system("color 4F");
        }
        else
        {
            GameResults.DrawTimes++;
            system("color E0");
        }

        GameResults.FinalWinner = DetermineGameWinner(GameResults);
    }
    return GameResults;
}

void StartGame()
{

    do
    {
        system("color 0F");

        strGameResults GameResults = PlayGame();

        PrintFinalResults(GameResults);

    } while (PlayMore());
}

int main()
{
    srand((unsigned)time(NULL));
    StartGame();
}
