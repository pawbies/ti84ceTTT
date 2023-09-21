#include <ti/screen.h>
#include <ti/getcsc.h>
#include <stdio.h>

//i think the display length is 27 characters

class Game
{
private:
    char board[10];
    char currentPlayer;
    bool showTakenMessage;
    bool quit;

    void draw()
    {
        os_ClrHome();

        char line1[10];
        char line2[10];
        char line3[10];

        sprintf(line1, "%c | %c | %c", this->board[0], this->board[1], this->board[2]);
        sprintf(line2, "%c | %c | %c", this->board[3], this->board[4], this->board[5]);
        sprintf(line3, "%c | %c | %c", this->board[6], this->board[7], this->board[8]);

        os_PutStrLine(line1);
        boot_NewLine();
        os_PutStrLine("_________");
        boot_NewLine();
        os_PutStrLine(line2);
        boot_NewLine();
        os_PutStrLine("_________");
        boot_NewLine();
        os_PutStrLine(line3);
        boot_NewLine();
    }

    void getInput()
    {
        char question[30];
        sprintf(question, "Your move %c?", this->currentPlayer);
        os_PutStrLine(question);
        boot_NewLine();
        do
        {
            uint8_t key = os_GetCSC();
            if (!key) continue;
            int pos;
            switch (key)
            {
                case sk_0: pos = -1; break;
                case sk_1: pos = 6; break;
                case sk_2: pos = 7; break;
                case sk_3: pos = 8; break;
                case sk_4: pos = 3; break;
                case sk_5: pos = 4; break;
                case sk_6: pos = 5; break;
                case sk_7: pos = 0; break;
                case sk_8: pos = 1; break;
                case sk_9: pos = 2; break;
                case sk_Mode: quit = true; break;
                default: pos = -1; break;
            }
            if (quit) break;
            if (pos == -1) continue;
            if (this->board[pos] != ' ')
            {
                if (this->showTakenMessage)
                {
                    os_PutStrLine("This field is already taken");
                    boot_NewLine();
                    this->showTakenMessage = false;
                }
                continue;
            }
            this->showTakenMessage = true;

            this->board[pos] = currentPlayer;
            break;
        } while (true);
    }

    bool checkForEnd()
    {
        if (this->board[0] == this->board[1] && this->board[0] == this->board[2] && this->board[0] != ' ') return true; //row 1
        if (this->board[3] == this->board[4] && this->board[3] == this->board[5] && this->board[3] != ' ') return true; //row 2
        if (this->board[6] == this->board[7] && this->board[6] == this->board[8] && this->board[6] != ' ') return true; //row 3
        if (this->board[2] == this->board[5] && this->board[2] == this->board[8] && this->board[2] != ' ') return true; //col 1
        if (this->board[1] == this->board[4] && this->board[1] == this->board[7] && this->board[1] != ' ') return true; //col 2
        if (this->board[0] == this->board[3] && this->board[0] == this->board[6] && this->board[0] != ' ') return true; //col 3
        if (this->board[0] == this->board[4] && this->board[0] == this->board[8] && this->board[0] != ' ') return true; //diagonal 1
        if (this->board[2] == this->board[4] && this->board[2] == this->board[6] && this->board[2] != ' ') return true; //diagonal 2
        return false;
    }
    
public:
    Game(): board("         "), currentPlayer('O'), showTakenMessage(true), quit(false) {}

    void loop()
    {
        do 
        {
            currentPlayer = currentPlayer == 'X' ? 'O' : 'X';
            draw();
            getInput();
        } while (!checkForEnd() && !this->quit);
        
        os_ClrHome();
        if (!this->quit)
        {
            char winner[30];
            sprintf(winner, "The Winner is %c!", this->currentPlayer);
            os_PutStrLine(winner);
            while (!os_GetCSC());
        }
    }
};

int main(void)
{
    os_ClrHome();

    os_PutStrFull("Welcome to the game of TTT");
    while (!os_GetCSC());

    Game G = Game();
    G.loop();
    return 0;
}
