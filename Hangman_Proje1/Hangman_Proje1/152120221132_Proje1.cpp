#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <ctime>
#include <string>

using namespace std;

extern vector<string> listTextFilesInFolder();
extern vector<string> readFileContent(const std::string& fileName);
extern void writetoFile(const std::string& dosyaAdi, const std::string& metin);
extern string formatDate(const std::string& format);
extern void updateFile(const std::string& fileName, int index, const std::string& yeniVeri);
extern string removeSpaces(const std::string& str);
extern string replaceTo(std::string& str, char replace = '_', char to = ' ');

vector<string> parts;

int row = 10;
int col = 33;
int chanceTotal = 10;
int firstWrongTotal = 0;
string formatliTarih = formatDate("%d-%m-%Y %H.%M");

void drawPart(string part) {

    system("cls");

    parts.push_back(part);

    bool poleIsExist = std::find(parts.begin(), parts.end(), "pole") != parts.end();
    bool ironIsExist = std::find(parts.begin(), parts.end(), "iron") != parts.end();
    bool ropeIsExist = std::find(parts.begin(), parts.end(), "rope") != parts.end();
    bool headIsExist = std::find(parts.begin(), parts.end(), "head") != parts.end();
    bool leftHandIsExist = std::find(parts.begin(), parts.end(), "leftHand") != parts.end();
    bool bodyIsExist = std::find(parts.begin(), parts.end(), "body") != parts.end();
    bool rightHandIsExist = std::find(parts.begin(), parts.end(), "rightHand") != parts.end();
    bool bottomIsExist = std::find(parts.begin(), parts.end(), "bottom") != parts.end();
    bool leftLegIsExist = std::find(parts.begin(), parts.end(), "leftLeg") != parts.end();
    bool rightLegIsExist = std::find(parts.begin(), parts.end(), "rightLeg") != parts.end();

    for (int i = 1; i <= row;i++) {
        cout << "|";

        int meridian = floor(col / 2);
        for (int j = 1; j <= col; j++) {

            if (j == meridian - 2 && i < 9 && i > 2 && poleIsExist)
                cout << "|";
            else if ((j == meridian - 1 || j == meridian || j == meridian + 1 || j == meridian + 2) && i == 2 && ironIsExist)
                cout << '_';
            else if ((j == meridian + 2) && (i == 3) && ropeIsExist)
                cout << "|";
            else if ((j == meridian + 2) && (i == 4) && headIsExist)
                cout << "O";
            else if ((j == meridian + 1) && (i == 5) && leftHandIsExist)
                cout << "/";
            else if ((j == meridian + 2) && (i == 5) && bodyIsExist)
                cout << "|";
            else if ((j == meridian + 3) && (i == 5) && rightHandIsExist)
                cout << "\\";
            else if ((j == meridian + 2) && (i == 6) && bottomIsExist)
                cout << "|";
            else if ((j == meridian + 1) && (i == 7) && leftLegIsExist)
                cout << "/";
            else if ((j == meridian + 3) && (i == 7) && rightLegIsExist)
                cout << "\\";
            else if (i != row && i != 1)
                cout << " ";

            if (i == row || i == 1)
                cout << "-";

            if (j == col)
                cout << "|" << endl;
        }
    }
}

void PrintMessage(string message, bool printTop = true, bool printBottom = true)
{
       
    updateFile(formatliTarih, 3, replaceTo(message));
    bool front = true;
    for (int i = message.length(); i < col + 2; i++)
    {
        if (front)
        {
            message = " " + message;
        }
        else
        {
            message = message + " ";
        }
        front = !front;
    }
    
    cout << message.c_str();
}

void PrintLetters(string input, char from, char to)
{
    string s;
    for (char i = from; i <= to; i++)
    {
        if (input.find(i) == string::npos)
        {
            s += i;
            s += " ";
        }
        else
            s += "  ";
    }
    PrintMessage(s, false, false);
}

void PrintAvailableLetters(string taken)
{
    PrintLetters(taken, 'A', 'M');
    cout << "" << endl;
    PrintLetters(taken, 'N', 'Z');
    cout << "" << endl;
}

void PrintGuessedWord(string guessed, char lastGuessed, bool isExist)
{
    string s;

    for (int i = 0; i < guessed.length(); i++)
    {
        s += toupper(guessed[i]);
        s += " ";
    }

    cout << "" << endl;
    cout << "-----------------------------------" << endl;
    PrintMessage(s, false);
    updateFile(formatliTarih, 2, removeSpaces(s));
    if (isExist)
    {
        cout << "" << endl;
        cout << "You used the letter " << lastGuessed << endl;
    }
    else {
           
    }   
    cout << "" << endl;

    cout << "-----------------------------------" << endl;

    PrintAvailableLetters(guessed);
    cout << "" << endl;
}

bool PrintWordAndCheckWin(string word, string guessed)
{
    bool won = true;
    string s;
    for (int i = 0; i < word.length(); i++)
    {
        if (guessed.find(word[i]) == string::npos)
        {
            won = false;
            s += "_ ";
        }
        else
        {
            s += word[i];
            s += " ";
        }
    }
    PrintMessage(s, false);
    return won;
}

int TriesLeft(string word, string guessed, char lastGuessed)
{
    int error = 0;
    int difference = 90;

    if (guessed.length() == 1) {
        for (int i = 0;i < word.length();i++) {
            int wordAscii = (int)word[i];
            int guessedAscii = (int)lastGuessed;
            if (difference > abs(wordAscii - guessedAscii)) {
                difference = abs(wordAscii - guessedAscii);
            }
        }
        if (difference == 0)  error = 0;
        if (difference > 0 && difference < 6) error++;
        if (difference >= 6 && difference < 11) error += 2;
        if (difference >= 11 && difference < 16) error += 3;
        if (difference >= 16 && difference < 21) error += 4;
        if (difference >= 21 && difference < 26) error += 5;
        firstWrongTotal = error;
    }
    else {
        error = firstWrongTotal;
        for (int i = 1; i < guessed.length(); i++)
        {
            if (word.find(guessed[i]) == string::npos)
                error++;
        }
    }
    return error;
}

void drawBodyChance(int chance)
{
    drawPart("");
    string bodyParts[10] = { "pole","iron","rope","head","leftHand","body","rightHand","bottom","leftLeg","rightLeg" };
    for (int i = 0; i < chanceTotal; i++)
    {
        if (i < chance)
            drawPart(bodyParts[i]);
    }
}

void CreateGame(string guessWord = "",int _chance = 0, string _guesses = "") {
    int chance = _chance;
    srand(time(0));
    string guesses;
    string words[3] = { "COUT","HANGMAN","CAR" };
    string wordToGuess;
    int pickedNumber = rand() % 3;

    wordToGuess = words[pickedNumber];
    if (guessWord != "") {
        wordToGuess = guessWord;
    }

    if (_guesses != "") {
        guesses = _guesses;
    }
    if (guessWord == "" && _guesses == ""){
        writetoFile(formatliTarih, wordToGuess);
        writetoFile(formatliTarih, std::to_string(chance));
        writetoFile(formatliTarih, "");
        writetoFile(formatliTarih, "");
    }

    drawPart(""); 
    if(guessWord != "" || _guesses != "")  drawBodyChance(chance);
    PrintGuessedWord(guesses, ' ', false);

    bool win = false;

    do
    {
        win = PrintWordAndCheckWin(wordToGuess, guesses);
        if (win)
            break;
        bool lastGuessIsExist = false;
        char x;
        cout << "" << endl;
        cout << ">"; cin >> x;
        x = (char)toupper(x);

        if (guesses.find(x) == string::npos)
            guesses += x;
        else
            lastGuessIsExist = true;

        chance = TriesLeft(wordToGuess, guesses, x);
        updateFile(formatliTarih, 1, std::to_string(chance));
        drawBodyChance(chance);
        PrintGuessedWord(guesses, x, lastGuessIsExist);
    } while (chance < chanceTotal);
    cout << "" << endl;

    if (win)
        PrintMessage("You won");
    else
        PrintMessage("Game over");

    system("pause");
    getchar();
    
}

void LoadGame() {
    system("cls");
    vector<string> files = listTextFilesInFolder();

    for (size_t i = 0; i < files.size(); i++) {
        const std::string& satir = files[i];
        std::cout << "Index: " << i << ", Satir: " << satir << std::endl;
    } 

    std::cout << "Listenen kayýtlarý yanýndaki deðeri giriniz:";

    int choice;

    std::cin >> choice;

    if(choice + 1 > files.size())
    {
        std::cout << "Doðru deðer girilmedi";
        exit(0);
    }
  
    vector<string> satirDizisi = readFileContent(files[choice]);
    size_t pos = files[choice].find(".txt");

    if (pos != std::string::npos) {
        files[choice].erase(pos, 4); 
    }

    formatliTarih = files[choice];
    CreateGame(satirDizisi[0], stoi(satirDizisi[1]), satirDizisi[2]);
}

int main()
{
    setlocale(LC_ALL, "Turkish");

    cout << "Baþlamak için seçiniz:\n";
    int choice;

    cout << "Yeni > 1\n";
    cout << "Kayýttan > 2\n";
    cout << "Çýkýþ > 3\n";
    cout << "Seçiniz:";

    cin >> choice;
   
    switch (choice)
    {
    case 1:
        CreateGame();
        break;
    case 2:
        LoadGame();
        break;
    case 3:
        exit(0);
        break;
    default:
        cout << "Yanlýþ tuþ girdiniz!";
        break;
    }
    return 0;
}
