#include <iostream>   // Include iostream for input/output operations.
#include <cstdlib>    // Include cstdlib for system functions like clearing the screen and colors.
#include <ctime>      // Include ctime for random number seeding.

using namespace std;  // Use the standard namespace to avoid prefixing std:: before standard functions.

// Enumeration: enGameChoice
// Purpose: Defines the choices available in the game.
enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };

// Enumeration: enWinner
// Purpose: Defines possible winners for a round or game.
enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

// Structure: stRoundInfo
// Purpose: Stores details of a single round of the game.
struct stRoundInfo
{
    short RoundNumber = 0;          // Round number.
    enGameChoice Player1Choice;     // Player's choice.
    enGameChoice ComputerChoice;    // Computer's choice.
    enWinner Winner;                // Stores the winner of the round.
    string WinnerName;               // Stores the winner's name.
};

// Structure: stGameResults
// Purpose: Stores overall game results after all rounds are played.
struct stGameResults
{
    short GameRounds = 0;        // Number of rounds played.
    short Player1WinTimes = 0;   // Count of Player1's wins.
    short ComputerWinTimes = 0;  // Count of Computer's wins.
    short DrawTimes = 0;         // Number of rounds that ended in a draw.
    enWinner GameWinner;         // Stores the overall game winner.
    string WinnerName = "";      // Name of the game winner.
};

// Function: RandomNumber
// Purpose: Generates a random number within the given range [From, To].
int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

// Function: GetComputerChoice
// Purpose: Randomly selects the computer's choice.
enGameChoice GetComputerChoice()
{
    return (enGameChoice)RandomNumber(1, 3);
}

// Function: WhoWonTheRound
// Purpose: Determines the winner of a round based on player and computer choices.
enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
    if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
        return enWinner::Draw;

    switch (RoundInfo.Player1Choice)
    {
    case enGameChoice::Stone:
        return (RoundInfo.ComputerChoice == enGameChoice::Paper) ? enWinner::Computer : enWinner::Player1;
    case enGameChoice::Paper:
        return (RoundInfo.ComputerChoice == enGameChoice::Scissors) ? enWinner::Computer : enWinner::Player1;
    case enGameChoice::Scissors:
        return (RoundInfo.ComputerChoice == enGameChoice::Stone) ? enWinner::Computer : enWinner::Player1;
    }
}

// Function: WhoWonTheGame
// Purpose: Determines the final game winner based on win counts.
enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes)
{
    if (Player1WinTimes > ComputerWinTimes) return enWinner::Player1;
    else if (ComputerWinTimes > Player1WinTimes) return enWinner::Computer;
    else return enWinner::Draw;
}

// Function: ChoiceName
// Purpose: Converts an enGameChoice enum to a string representation.
string ChoiceName(enGameChoice Choice)
{
    string arrGameChoices[3] = { "Stone", "Paper", "Scissors" };
    return arrGameChoices[Choice - 1];
}

// Function: WinnerName
// Purpose: Converts an enWinner enum to a string representation.
string WinnerName(enWinner Winner)
{
    string arrWinnerName[3] = { "Player1", "Computer", "No Winner (Draw)" };
    return arrWinnerName[Winner - 1];
}

// Function: ReadHowManyRounds
// Purpose: Prompts the user to choose the number of rounds between 1 and 10.
short ReadHowManyRounds()
{
    short Rounds = 1;
    do
    {
        cout << "How many rounds do you want to play (1 to 10)? ";
        cin >> Rounds;
    } while (Rounds < 1 || Rounds > 10);

    return Rounds;
}

// Function: ReadPlayer1Choice
// Purpose: Prompts the player to input their choice.
enGameChoice ReadPlayer1Choice()
{
    short Choice;
    do
    {
        cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors? ";
        cin >> Choice;
    } while (Choice < 1 || Choice > 3);
    return (enGameChoice)Choice;
}

// Function: SetScreenColor
// Purpose: Changes console background color based on the winner.
void SetScreenColor(enWinner Winner)
{
    if (Winner == enWinner::Player1)
        system("color 2F"); // Green screen for Player1 win
    else if (Winner == enWinner::Computer)
        system("color 4F"); // Red screen for Computer win
    else
        system("color 6F"); // Yellow screen for Draw
}

// Function: PrintRoundResults
// Purpose: Displays the results of a single round and changes screen color.
void PrintRoundResults(stRoundInfo RoundInfo)
{
    cout << "\n____________ Round [" << RoundInfo.RoundNumber << "] ____________\n\n";
    cout << "Player1 Choice: " << ChoiceName(RoundInfo.Player1Choice) << endl;
    cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner   : [" << RoundInfo.WinnerName << "]\n";
    cout << "_________________________________________\n" << endl;

    SetScreenColor(RoundInfo.Winner);
}

// Function: PrintGameResults
// Purpose: Displays the overall game statistics and sets final screen color.
void PrintGameResults(stGameResults GameResults)
{
    cout << "\n\n____________________________________________________\n";
    cout << "                   +++ G A M E  O V E R +++\n";
    cout << "____________________________________________________\n\n";
    cout << "_________________ [Game Results] ___________________\n\n";
    cout << "Game Rounds        : " << GameResults.GameRounds << endl;
    cout << "Player1 Win Times  : " << GameResults.Player1WinTimes << endl;
    cout << "Computer Win Times : " << GameResults.ComputerWinTimes << endl;
    cout << "Draw Times         : " << GameResults.DrawTimes << endl;
    cout << "Final Winner       : " << GameResults.WinnerName << endl;
    cout << "____________________________________________________\n";

    SetScreenColor(GameResults.GameWinner);
}

// Function: PlayGame
// Purpose: Runs the game for a given number of rounds and determines the final winner.
stGameResults PlayGame(short HowManyRounds)
{
    stRoundInfo RoundInfo;
    short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

    for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
    {
        cout << "\nRound [" << GameRound << "] begins:\n";
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.Player1Choice = ReadPlayer1Choice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        if (RoundInfo.Winner == enWinner::Player1)
            Player1WinTimes++;
        else if (RoundInfo.Winner == enWinner::Computer)
            ComputerWinTimes++;
        else
            DrawTimes++;

        PrintRoundResults(RoundInfo);
    }

    return { HowManyRounds, Player1WinTimes, ComputerWinTimes, DrawTimes, WhoWonTheGame(Player1WinTimes, ComputerWinTimes), WinnerName(WhoWonTheGame(Player1WinTimes, ComputerWinTimes)) };
}

// Function: StartGame
// Purpose: Controls the game loop, allowing players to replay the game.
void StartGame()
{
    char PlayAgain = 'Y';

    do
    {
        system("cls");  // Clear screen
        system("color 0F"); // Reset to standard black background before starting

        short TotalRounds = ReadHowManyRounds();
        stGameResults GameResults = PlayGame(TotalRounds);

        PrintGameResults(GameResults); // Print the final stats using the new function

        cout << "\nDo you want to play again? (Y/N): ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

// Main Function
int main()
{
    srand((unsigned)time(NULL));  // Seed random number generator.
    StartGame();  // Start the game.
    return 0;
}