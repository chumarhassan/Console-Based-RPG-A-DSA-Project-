#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
struct LevelNode
{
    int levelNumber;
    string description;
    bool isCombat;
    LevelNode *prev;
    LevelNode *next;
};
struct PlayerCharacter
{
    string name;
    int health;
    int wisdom;
    int coins;
    int lives;
    string inventory[10];
    int attackPower;
};
struct Enemy
{
    string name;
    int health;
    int attack;
    int defense;
};
struct Question
{
    string text;
    string correctAnswer;
};
struct ShopItem
{
    string name;
    int cost;
    int effect;
};
class LevelProgression
{
private:
    LevelNode *head;
    LevelNode *currentLevel;
    PlayerCharacter player;
    vector<Question> puzzleQuestions;
    ShopItem shopInventory[2];
    bool levelCleared;
    set<int> askedQuestionIndices;
public:
    LevelProgression(string playerName) : head(nullptr), currentLevel(nullptr), levelCleared(false)
    {
        player.name = playerName;
        player.health = 100;
        player.wisdom = 80;
        player.coins = 10;
        player.lives = 3;
        player.attackPower = 10;
        for (int i = 0; i < 10; ++i)
        {
            player.inventory[i] = "";
        }

        shopInventory[0] = {"FIRST AID KIT", 10, 0};
        shopInventory[1] = {"SWORD", 20, 10};

        generatePuzzleQuestions();
    }

    void generatePuzzleQuestions()
    {
        srand(time(nullptr));
        puzzleQuestions.push_back({"**WHAT HAS KEYS BUT CAN'T OPEN LOCKS?**", "KEYBOARD"});
        puzzleQuestions.push_back({"**WHAT IS ALWAYS IN FRONT OF YOU BUT CAN'T BE SEEN?**", "FUTURE"});
        puzzleQuestions.push_back({"**WHAT BELONGS TO YOU BUT OTHER PEOPLE USE IT MORE THAN YOU DO?**", "NAME"});
        puzzleQuestions.push_back({"**WHAT COMES ONCE IN A MINUTE, TWICE IN A MOMENT, BUT NEVER IN A THOUSAND YEARS?**", "M"});
        puzzleQuestions.push_back({"**WHAT IS SO FRAGILE THAT SAYING ITS NAME BREAKS IT?**", "SILENCE"});
        puzzleQuestions.push_back({"**WHAT HAS A HEAD, A TAIL, IS BROWN, AND HAS NO LEGS?**", "PENNY"});
        puzzleQuestions.push_back({"**I SPEAK WITHOUT A MOUTH AND HEAR WITHOUT EARS. I HAVE NO BODY, BUT I COME ALIVE WITH THE WIND. WHAT AM I?**", "ECHO"});
        puzzleQuestions.push_back({"**THE MORE YOU TAKE, THE MORE YOU LEAVE BEHIND. WHAT AM I?**", "FOOTSTEPS"});
        puzzleQuestions.push_back({"**WHAT HAS ONE EYE BUT CAN'T SEE?**", "NEEDLE"});
        puzzleQuestions.push_back({"**WHAT RUNS BUT NEVER WALKS, HAS A MOUTH BUT NEVER TALKS?**", "RIVER"});
    }
    void addLevel(int levelNumber, string description, bool isCombat)
    {
        LevelNode *newNode = new LevelNode;
        newNode->levelNumber = levelNumber;
        newNode->description = description;
        newNode->isCombat = isCombat;
        newNode->prev = nullptr;
        newNode->next = nullptr;
        if (!head)
        {
            head = newNode;
            currentLevel = head;
        }
        else
        {
            LevelNode *temp = head;
            while (temp->next)
            {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->prev = temp;
        }
    }
    void moveToNextLevel()
    {
        if (currentLevel && currentLevel->next && levelCleared)
        {
            currentLevel = currentLevel->next;
            levelCleared = false;
        }
        else if (!levelCleared)
        {
            cout << "YOU MUST CLEAR THE CURRENT LEVEL BEFORE MOVING TO THE NEXT LEVEL." << endl;
        }
        else
        {
            cout << "YOU ARE AT THE FINAL LEVEL." << endl;
        }
    }
    void moveToPreviousLevel()
    {
        if (currentLevel && currentLevel->prev)
        {
            currentLevel = currentLevel->prev;
        }
        else
        {
            cout << "YOU ARE AT THE FIRST LEVEL." << endl;
        }
    }
    string getCurrentLevelDescription()
    {
        if (currentLevel)
            return currentLevel->description;
        else
            return "NO LEVEL AVAILABLE.";
    }
    void showInventory()
    {
        cout << "INVENTORY:" << endl;
        for (int i = 0; i < 10; ++i)
        {
            if (!player.inventory[i].empty())
            {
                cout << player.inventory[i] << endl;
            }
        }
    }
    void battleEnemy(Enemy &enemy)
    {
        cout << "YOU ENGAGE IN BATTLE WITH " << enemy.name << "!" << endl;
        while (player.health > 0 && enemy.health > 0)
        {
            cout << "CHOOSE AN ACTION: (A)TTACK, (D)EFEND: ";
            char action;
            cin >> action;
            if (action == 'a' || action == 'A')
            {
                int playerDamage = rand() % 20 + 1 + player.attackPower;
                enemy.health -= playerDamage;
                cout << "YOU ATTACK " << enemy.name << " FOR " << playerDamage << " DAMAGE." << endl;
                if (enemy.health <= 0)
                {
                    cout << "YOU DEFEATED " << enemy.name << "!" << endl;
                    player.coins += 10;
                    levelCleared = true;
                    break;
                }
            }
            else if (action == 'd' || action == 'D')
            {
                cout << "YOU DEFEND AGAINST THE ATTACK." << endl;
                continue;
            }
            else
            {
                cout << "INVALID ACTION. TRY AGAIN." << endl;
                continue;
            }
            int enemyDamage = (rand() % 20 + 1) + (currentLevel->levelNumber * 2);
            enemyDamage -= player.wisdom / 10;
            if (enemyDamage < 0)
                enemyDamage = 0;
            player.health -= enemyDamage;
            cout << enemy.name << " ATTACKS YOU FOR " << enemyDamage << " DAMAGE." << endl;
            if (player.health <= 0)
            {
                cout << "YOU WERE DEFEATED BY " << enemy.name << "!" << endl;
                player.lives--;
                if (player.lives > 0)
                {
                    cout << "YOU HAVE " << player.lives << " LIVES LEFT." << endl;
                    char choice;
                    cout << "DO YOU WANT TO RESTART THE CURRENT LEVEL? (Y/N): ";
                    cin >> choice;
                    if (choice == 'y' || choice == 'Y')
                    {
                        player.health = 100;
                        return;
                    }
                    else
                    {
                        cout << "GAME OVER! YOU HAVE RUN OUT OF LIVES." << endl;
                        exit(0);
                    }
                }
                else
                {
                    cout << "GAME OVER! YOU HAVE RUN OUT OF LIVES." << endl;
                    exit(0);
                }
                break;
            }
        }
    }
    void answerQuestion(Question &question, string answer)
    {
        cout << "QUESTION: " << question.text << endl;
        transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
        transform(question.correctAnswer.begin(), question.correctAnswer.end(), question.correctAnswer.begin(), ::tolower);
        if (answer == question.correctAnswer)
        {
            cout << "CORRECT ANSWER! YOUR WISDOM INCREASES." << endl;
            player.wisdom += 10;
            levelCleared = true;
        }
        else
        {
            cout << "INCORRECT ANSWER! YOUR HEALTH AND WISDOM DECREASE." << endl;
            player.health -= 20;
            player.wisdom -= 10;
            if (player.health <= 0)
            {
                player.lives--;
                if (player.lives > 0)
                {
                    cout << "YOU HAVE " << player.lives << " LIVES LEFT." << endl;
                    char choice;
                    cout << "DO YOU WANT TO RESTART THE CURRENT LEVEL? (Y/N): ";
                    cin >> choice;
                    if (choice == 'y' || choice == 'Y')
                    {
                        player.health = 100;
                        return;
                    }
                }
                else
                {
                    cout << "GAME OVER! YOU HAVE RUN OUT OF LIVES." << endl;
                    exit(0);
                }
            }
        }
    }
    void visitShop()
    {
        cout << "WELCOME TO THE SHOP!" << endl;
        displayStats();
        cout << "AVAILABLE ITEMS:" << endl;
        for (int i = 0; i < 2; ++i)
        {
            cout << i + 1 << ". " << shopInventory[i].name << " - COST: " << shopInventory[i].cost << " COINS, EFFECT: " << shopInventory[i].effect << endl;
        }
        cout << "YOU HAVE " << player.coins << " COINS." << endl;
        int itemNumber;
        cout << "ENTER THE NUMBER OF THE ITEM YOU WANT TO BUY (OR 0 TO LEAVE): ";
        cin >> itemNumber;
        if (itemNumber == 0)
        {
            cout << "EXITING THE SHOP." << endl;
            return;
        }
        if (itemNumber < 1 || itemNumber > 2)
        {
            cout << "INVALID ITEM NUMBER. RETURNING TO MAIN MENU." << endl;
            return;
        }
        if (player.coins >= shopInventory[itemNumber - 1].cost)
        {
            cout << "YOU BOUGHT " << shopInventory[itemNumber - 1].name << "." << endl;
            player.coins -= shopInventory[itemNumber - 1].cost;
            if (shopInventory[itemNumber - 1].name == "FIRST AID KIT")
            {
                player.health = 100;
            }
            else if (shopInventory[itemNumber - 1].name == "SWORD")
            {
                player.attackPower += 10;
            }
            for (int i = 0; i < 10; ++i)
            {
                if (player.inventory[i].empty())
                {
                    player.inventory[i] = shopInventory[itemNumber - 1].name;
                    break;
                }
            }
        }
        else
        {
            cout << "YOU DON'T HAVE ENOUGH COINS TO BUY THIS ITEM." << endl;
        }
    }
    void displayStats()
    {
        cout << "PLAYER STATS:" << endl;
        cout << "NAME: " << player.name << endl;
        cout << "HEALTH: " << player.health << endl;
        cout << "WISDOM: " << player.wisdom << endl;
        cout << "COINS: " << player.coins << endl;
        cout << "LIVES: " << player.lives << endl;
        cout << "ATTACK POWER: " << player.attackPower << endl;
        cout << "-------------------------------------------" << endl;
    }
    void startGame()
    {
        cout << "WELCOME TO RPG: THE SAVIOR OF PRINCESS!" << endl;
        cout << "PRESS ENTER TO CONTINUE...";
        cin.ignore(); 
        cin.get();   
        cout << "IN THE KINGDOM OF FARLANDIA, A GREAT EVIL HAS ARISEN." << endl;
        cout << "PRESS ENTER TO CONTINUE...";
        cin.ignore(); 
        cin.get();    
        cout << "THE DARK SORCERER MALVADOR HAS KIDNAPPED PRINCESS ELARA, THE BELOVED DAUGHTER OF KING ALDRIC." << endl;
        cout << "PRESS ENTER TO CONTINUE...";
        cin.ignore(); 
        cin.get();   
        cout << "THE KINGDOM IS IN CHAOS, AND ITS PEOPLE ARE LIVING IN FEAR." << endl;
        cout << "PRESS ENTER TO CONTINUE...";
        cin.ignore(); 
        cin.get();   
        cout << "IT IS UP TO YOU, THE BRAVE ADVENTURER, TO EMBARK ON A PERILOUS JOURNEY" << endl;
        cout << "PRESS ENTER TO CONTINUE...";
        cin.ignore(); 
        cin.get();    
        cout << "TO DEFEAT MALVADOR AND RESCUE PRINCESS ELARA FROM HIS CLUTCHES." << endl;
        cout << "PRESS ENTER TO CONTINUE...";
        cin.ignore(); 
        cin.get();    
        cout << "DO YOU HAVE WHAT IT TAKES TO BECOME THE SAVIOR OF PRINCESS?" << endl;
        cout << "PRESS ENTER TO CONTINUE...";
        cin.ignore(); 
        cin.get();   
        string playerName;
        cout << "ENTER YOUR CHARACTER'S NAME: ";
        cin >> playerName;
        player.name = playerName;
        bool replay = true;
        while (replay)
        {
            player.health = 100;
            player.wisdom = 80;
            player.coins = 10;
            player.lives = 3;
            player.attackPower = 10;
            for (int i = 0; i < 10; ++i)
            {
                player.inventory[i] = "";
            }
            currentLevel = nullptr;
            generateLevels();
            currentLevel = head;
            while (currentLevel)
            {
                displayStats();
                cout << "CURRENT LEVEL: " << currentLevel->levelNumber << " - " << getCurrentLevelDescription() << endl;
                if (currentLevel->isCombat)
                {
                    cout << "YOU ENCOUNTER AN ENEMY! PREPARE FOR BATTLE!" << endl;
                    Enemy enemy;
                    enemy.name = "EVIL MONSTER";
                    enemy.health = 50;
                    battleEnemy(enemy);
                }
                else
                {
                    cout << "ANSWER THE FOLLOWING QUESTION TO GAIN WISDOM:" << endl;
                    Question question = getRandomPuzzleQuestion();
                    string answer;
                    cout << question.text << endl;
                    cout << "YOUR ANSWER: ";
                    cin >> answer;
                    answerQuestion(question, answer);
                }
                if (player.lives > 0)
                {
                    if (levelCleared)
                    {
                        if (currentLevel->next == nullptr)
                        {
                            break;
                        }
                        else
                        {
                            while (true)
                            {
                                cout << "DO YOU WANT TO (M)OVE TO THE NEXT LEVEL, (B)ACK TO THE PREVIOUS LEVEL, (S)HOP, OR CHECK (I)NVENTORY? (M/B/S/I): ";
                                char choice;
                                cin >> choice;
                                if (choice == 'm' || choice == 'M')
                                {
                                    moveToNextLevel();
                                    break;
                                }
                                else if (choice == 'b' || choice == 'B')
                                {
                                    moveToPreviousLevel();
                                    break;
                                }
                                else if (choice == 's' || choice == 'S')
                                {
                                    visitShop();
                                    moveToNextLevel();
                                    break;
                                }
                                else if (choice == 'i' || choice == 'I')
                                {
                                    showInventory();
                                }
                                else
                                {
                                    cout << "INVALID CHOICE. PLEASE CHOOSE AGAIN." << endl;
                                }
                            }
                        }
                    }
                }
                else
                {
                    break;
                }
            }
            if (currentLevel && currentLevel->next == nullptr && levelCleared)
            {
                cout << "CONGRATULATIONS! YOU HAVE COMPLETED ALL LEVELS AND SAVED PRINCESS ELARA!" << endl;
            }
            else if (player.lives == 0)
            {
                cout << "GAME OVER! YOU HAVE RUN OUT OF LIVES." << endl;
            }
            cout << "DO YOU WANT TO PLAY AGAIN? (Y/N): ";
            char replayChoice;
            cin >> replayChoice;
       if (replayChoice != 'y' && replayChoice != 'Y')
            {
                replay = false;
            }
        }
    }
    Question getRandomPuzzleQuestion()
    {
        int index;
        do
        {
            index = rand() % puzzleQuestions.size();
        } while (askedQuestionIndices.find(index) != askedQuestionIndices.end());
        askedQuestionIndices.insert(index);
        return puzzleQuestions[index];
    }
    void generateLevels()
    {
        srand(time(nullptr));
        for (int i = 0; i < 9; ++i)
        {
            if (i % 2 == 0)
                addLevel(i + 1, "COMBAT CHALLENGE - FIGHT AGAINST THE ENEMY!", true);
            else
                addLevel(i + 1, "WISDOM CHALLENGE - ANSWER A QUESTION TO GAIN KNOWLEDGE!", false);
        }
        addLevel(10, "FINAL BOSS ROOM - DEFEAT THE ULTIMATE ENEMY AND ANSWER QUESTIONS!", true);
    }
};
int main()
{
    string playerName;
    LevelProgression game(playerName);
    game.startGame();
    return 0;
}
