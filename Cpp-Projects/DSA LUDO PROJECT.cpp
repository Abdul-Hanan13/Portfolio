#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

class DiceNode
{
    public:
    int value;
    DiceNode* next;
    
    DiceNode(int v)
    {
        value = v;
        next = NULL;
    }
};

class StackNode
{
    public:
    int p1;
    int p2;
    StackNode* next;
    
    StackNode(int a, int b)
    {
        p1 = a;
        p2 = b;
        next = NULL;
    }
};
  
class MoveStack
{
    public:
    StackNode* top;
    
    MoveStack()
    {
        top = NULL;
    }
    
    void push(int a, int b)
    {
        StackNode* newNode = new StackNode(a, b);
        newNode->next = top;
        top = newNode;
    }
    
    bool pop(int &a, int &b)
    {
        if (top == NULL)
        {
            return false;
        }
        StackNode* temp = top;
        a = temp->p1;
        b = temp->p2;
        top = top->next;
        delete temp;
        return true;
    }
 
};
  
class QueueNode
{
    public:
    string playerName;
    QueueNode* next;
    
    QueueNode(string name)
    {
        playerName = name;
        next = NULL;
    }
};

class TurnQueue
{
    public:
    QueueNode* front;
    QueueNode* rear;
    
    TurnQueue()
    {
        front = NULL;
        rear = NULL;
    }
    
    void enqueue(string name)
    {
        QueueNode* newNode = new QueueNode(name);
        if (rear == NULL)
        {
            front = newNode;
            rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }
    }
    
    string dequeue()
    {
        if (front == NULL)
        {
            return "";
        }
        QueueNode* temp = front;
        string name = temp->playerName;
        front = front->next;
        if (front == NULL)
        {
            rear = NULL;
        }
        delete temp;
        return name;
    }
};
 
class Player
{
    public:
    int pawn[2];
    string name;
    MoveStack* history;
    
    Player(string n)
    {
        name = n;
        pawn[0] = -1;
        pawn[1] = -1;
        history = new MoveStack();
    }
    
    bool allFinished()
    {
        if (pawn[0] == -2 && pawn[1] == -2)
        {
            return true;
        }
        return false;
    }
    
    bool canMove(int id, int dice)
    {
        if (id < 0 || id > 1 || pawn[id] == -2)
        {
            return false;
        }
        if (pawn[id] == -1)
        {
            if (dice == 6)
            {
                return true;
            }
            return false;
        }
        if (pawn[id] + dice <= 16)
        {
            return true;
        }
        return false;
    }
    
    void move(int id, int dice)
    {
        if (pawn[id] == -1 && dice == 6)
        {
            pawn[id] = 0;
        }
        else
        {
            pawn[id] = pawn[id] + dice;
            if (pawn[id] >= 16)
            {
                pawn[id] = -2;
            }
        }
    }
};

class Game
{
    private:
    Player *human;
    Player *ai;
    DiceNode* diceHead;
    TurnQueue* queue;
    
    public:
    Game()
    {
        srand(time(0));
        human = new Player("Human");
        ai = new Player("AI");
        diceHead = NULL;
        queue = new TurnQueue();
        
        system("cls");
        
        cout << "======WELCOME TO LUDO======  " << endl << endl;
        cout << "   TOSS START " << endl;
        int toss = rand() % 2;
        if (toss == 0) 
        {
            cout << "Human wins the toss!" << endl;
            queue->enqueue("Human");
            queue->enqueue("AI");
        }
        else 
        {
            cout << "AI wins the toss!" << endl;
            queue->enqueue("AI");
            queue->enqueue("Human");
        }
        cout << "Press Enter to start..." << endl;
        cin.get();
    }
    
    void addDice(int v)
    {
        DiceNode* newNode = new DiceNode(v);
        if (diceHead == NULL)
        {
            diceHead = newNode;
        }
        else
        {
            DiceNode* temp = diceHead;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }
    
    void clearDice()
    {
        while (diceHead != NULL)
        {
            DiceNode* temp = diceHead;
            diceHead = diceHead->next;
            delete temp;
        }
    }
    
    void checkHit(Player* active, Player* opponent, int id)
    {
        if (active->pawn[id] > 0)
        {
            for (int j = 0; j < 2; j = j + 1)
            {
                if (active->pawn[id] == opponent->pawn[j])
                {
                    opponent->pawn[j] = -1;
                    cout << "\nHIT!" << endl;
                }
            }
        }
    }
    
    void displayBoard()
    {
        string grid[5][5];
        for (int i = 0; i < 5; i = i + 1)
        {
            for (int j = 0; j < 5; j = j + 1)
            {
                grid[i][j] = "__";
            }
        }
        
        int stepCounter = 0;
       
        for (int i = 0; i < 5; i++) 
		{ 
            int row = 0, col = i;
            if (human->pawn[0] == stepCounter) 
			    grid[row][col] = (grid[row][col] == "H2") ? "HH" : "H1";
            if (human->pawn[1] == stepCounter) 
			    grid[row][col] = (grid[row][col] == "H1") ? "HH" : "H2";
            if (ai->pawn[0] == stepCounter) 
			    grid[row][col] = (grid[row][col] == "A2") ? "AA" : "A1";
            if (ai->pawn[1] == stepCounter)
			    grid[row][col] = (grid[row][col] == "A1") ? "AA" : "A2";
            stepCounter++;
        }
        
        for (int i = 1; i < 5; i++) 
		{ 
            int row = i, col = 4;
            if (human->pawn[0] == stepCounter) 
			    grid[row][col] = (grid[row][col] == "H2") ? "HH" : "H1";
            if (human->pawn[1] == stepCounter)
			    grid[row][col] = (grid[row][col] == "H1") ? "HH" : "H2";
            if (ai->pawn[0] == stepCounter)
			    grid[row][col] = (grid[row][col] == "A2") ? "AA" : "A1";
            if (ai->pawn[1] == stepCounter)
			    grid[row][col] = (grid[row][col] == "A1") ? "AA" : "A2";
            stepCounter++;
        }
        
        for (int i = 3; i >= 0; i--) 
		{ 
            int row = 4, col = i;
            if (human->pawn[0] == stepCounter) 
			    grid[row][col] = (grid[row][col] == "H2") ? "HH" : "H1";
            if (human->pawn[1] == stepCounter) 
			    grid[row][col] = (grid[row][col] == "H1") ? "HH" : "H2";
            if (ai->pawn[0] == stepCounter) 
			    grid[row][col] = (grid[row][col] == "A2") ? "AA" : "A1";
            if (ai->pawn[1] == stepCounter)
			    grid[row][col] = (grid[row][col] == "A1") ? "AA" : "A2";
            stepCounter++;
        }
        
        for (int i = 3; i >= 1; i--) 
		{ 
            int row = i, col = 0;
            if (human->pawn[0] == stepCounter)
			    grid[row][col] = (grid[row][col] == "H2") ? "HH" : "H1";
            if (human->pawn[1] == stepCounter) 
			    grid[row][col] = (grid[row][col] == "H1") ? "HH" : "H2";
            if (ai->pawn[0] == stepCounter) 
			    grid[row][col] = (grid[row][col] == "A2") ? "AA" : "A1";
            if (ai->pawn[1] == stepCounter)
			    grid[row][col] = (grid[row][col] == "A1") ? "AA" : "A2";
            stepCounter++;
        }
        
        cout << "\nBASE: Human[";
        if (human->pawn[0] == -1) 
		{  
		    cout << "H1 "; 
		}
        if (human->pawn[1] == -1) 
		{
		    cout << "H2 "; 
		}
        cout << "] AI[";
        if (ai->pawn[0] == -1) 
		{ 
		    cout << "A1 "; 
		}
        if (ai->pawn[1] == -1) 
		{ 
		    cout << "A2 "; 
		}
        cout << "]" << endl;
        cout << "Finish: Human[";
        if (human->pawn[0] == -2) 
		{
		    cout << "H1 "; 
		}
        if (human->pawn[1] == -2) 
		{  
		    cout << "H2 "; 
		}
        cout << "] AI[";
        if (ai->pawn[0] == -2) 
		{ 
		    cout << "A1 "; 
		}
        if (ai->pawn[1] == -2) 
		{  
		    cout << "A2 ";
	    }
        cout << "]" << endl;
        
        
        for (int i = 0; i < 5; i++) 
        {
            for (int j = 0; j < 5; j++) 
            {
                if (i >= 1 && i <= 3 && j >= 1 && j <= 3) 
                {
                    cout << "    ";
                }
                else 
                {
                    cout << "[" << grid[i][j] << "]";
                }
            }
            cout << endl;
        }
    }
    
    void start()
    {
        while (human->allFinished() == false && ai->allFinished() == false)
        {
            system("cls");
            displayBoard();
            string name = queue->dequeue();
            Player* curr = (name == "Human") ? human : ai;
            Player* opp = (name == "Human") ? ai : human;
            curr->history->push(curr->pawn[0], curr->pawn[1]);
            cout << "\n--- " << name << "'s Turn ---" << endl;
            
            if (name == "Human")
            {
                cout << "Press Enter to roll...";
                cin.get();
            }
            
            int sixes = 0;
            bool resetOccurred = false;
            
            while (true)
            {
                int r = (rand() % 6) + 1;
                cout << name << " rolled: " << r << endl;
                if (r == 6)
                {
                    sixes = sixes + 1;
                    if (sixes == 3)
                    {
                        cout << "TRIPLE SIX! Resetting position via Stack..." << endl;
                        curr->history->pop(curr->pawn[0], curr->pawn[1]);
                        resetOccurred = true;
                        clearDice();
                        break;
                    }
                    addDice(r);
                }
                else
                {
                    addDice(r);
                    break;
                }
            }
            
            if (resetOccurred == false)
            {
                DiceNode* dNode = diceHead;
                while (dNode != NULL)
                {
                    int val = dNode->value;
                    bool can0 = curr->canMove(0, val);
                    bool can1 = curr->canMove(1, val);
                    if (can0 || can1)
                    {
                        int choice = -1;
                        if (name == "Human")
                        {
                            while (true)
                            {
                                cout << "Move H1 or H2 for [" << val << "]? ";
                                string moveChoice;
                                cin >> moveChoice;
                                
                                if (moveChoice == "H1") 
								{ 
								    choice = 0;
							    }
                                else if (moveChoice == "H2")
							    {
								    choice = 1; 
								}
								
                                if (choice != -1 && curr->canMove(choice, val)) 
								{
								    break; 
								}
								cout << "Invalid choice or pawn finished/in base!" << endl;

                            }
                        }
                        else 
                        {
                            int f0 = (curr->pawn[0] == -1) ? 0 : curr->pawn[0] + val;
                            int f1 = (curr->pawn[1] == -1) ? 0 : curr->pawn[1] + val;

                            if (can0 && (f0 == opp->pawn[0] || f0 == opp->pawn[1])) 
							{ 
							    choice = 0; 
							}
                            else if (can1 && (f1 == opp->pawn[0] || f1 == opp->pawn[1])) 
							{ 
							    choice = 1; 
							}
                            else 
							{ 
							    choice = (can0) ? 0 : 1; 
							}
                            cout << "AI chose A" << choice + 1 << endl;
                        }
                        curr->move(choice, val);
                        checkHit(curr, opp, choice);
                        displayBoard();
                    }
                    dNode = dNode->next;
                }
            }
            
            clearDice();
            queue->enqueue(name);
            cout << "\nTurn finished. Press Enter...";
            cin.ignore();
            cin.get();
        }

        if (human->allFinished()) 
        {
            cout << "GAME OVER - HUMAN WINS!" << endl;
        }
        else 
        {
            cout << "GAME OVER - AI WINS!" << endl;
        }
    }
};

int main()
{
    Game ludo;
    ludo.start();
    return 0;
}


