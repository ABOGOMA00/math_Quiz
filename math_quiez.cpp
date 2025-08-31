#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

enum enqlevel { Easy = 1, Mid = 2, Hard = 3, MixLevel = 4 };
enum enop { Add = 1, sup = 2, Multi = 3, Div = 4, MixOp = 5 };

struct stlevel {
    int num1 = 0;
    int num2 = 0;
    int howmany = 0;
    int qlevel = 0;
};

struct stop {
    int num1 = 0;
    int num2 = 0;
    int rightanswer = 0;
    int useranswer = 0;
    int qop = 0;
};

struct stgameinfo {
    int countWin = 0;
    int countLose = 0;
    char play_again = ' ';
};

stlevel l;
stop m;
stgameinfo i;

int randomnums(int From, int To) {
    return rand() % (To - From + 1) + From;
}

void setLevel() {
    cout << "Enter Question Level Easy=1, Mid=2, Hard=3, Mix=4 : ";
    cin >> l.qlevel;
}

void setOpType() {
    cout << "Enter operation type Add=1, sup=2, Multi=3, Div=4, Mix=5 : ";
    cin >> m.qop;
}

void setHowMany() {
    cout << "How Many Questions do you want to answer : ";
    cin >> l.howmany;
}

void returnlevel() {
    int level = l.qlevel;
    if (l.qlevel == MixLevel)
        level = randomnums(1, 3); 
    switch (level) {
    case Easy: m.num1 = randomnums(1, 10); m.num2 = randomnums(1, 10); break;
    case Mid:  m.num1 = randomnums(1, 10); m.num2 = randomnums(10, 50); break;
    case Hard: m.num1 = randomnums(50, 100); m.num2 = randomnums(50, 100); break;
    }
}

void returnoptype() {
    int op = m.qop;
    if (m.qop == MixOp)
        op = randomnums(1, 4); 

    switch (op) {
    case Add:   m.rightanswer = m.num1 + m.num2; break;
    case sup:   m.rightanswer = m.num1 - m.num2; break;
    case Multi: m.rightanswer = m.num1 * m.num2; break;
    case Div:   if (m.num2 == 0) m.num2 = 1; m.rightanswer = m.num1 / m.num2; break;
    }
    m.qop = op; 
}

bool playagain() {
    cout << "Do you want to play again [Y],[N] : ";
    cin >> i.play_again;
    return (i.play_again == 'Y' || i.play_again == 'y');
}

void gameinfo() {
    cout << "-----------------------------------\n";
    if (i.countLose > i.countWin) {
        cout << "Final result is [ Lose ] \n\n";
        system("color C");
    }
       
    else {
        cout << "Final result is [ Win ] \n\n";
        system("color A");
    }
       
    cout << "-----------------------------------\n";

    cout << "Number of Questions : " << l.howmany << endl;
    cout << "Number of Right answers : " << i.countWin << endl;
    cout << "Number of Wrong answers : " << i.countLose << endl;
    cout << "------------------------------------------------\n";
}

void playGame() {
    do {
        i.countWin = i.countLose = 0;
        setHowMany();
        setLevel();
        setOpType();
        system("cls");

        for (int count = 0; count < l.howmany; count++) {
            returnlevel();
            returnoptype();
            cout << "Quisiton " << count+1 << " / " << l.howmany<<endl;
            if (m.qop == Add) {
                cout << m.num1 << " + " << m.num2 << " = ";
            }
            else if (m.qop == sup) {
                cout << m.num1 << " - " << m.num2 << " = ";
            }
            else if (m.qop == Multi) {
                cout << m.num1 << " * " << m.num2 << " = ";
            }
            else if (m.qop == Div) {
                cout << m.num1 << " / " << m.num2 << " = ";
            }

            cin >> m.useranswer;

            if (m.useranswer == m.rightanswer) {
                cout << " You win :) \n";
                i.countWin++;
                system("color A"); 
            }
            else {
                cout << " wrong answer :(\n";
                i.countLose++;
                system("color C"); 
                cout << "\a"; 
            }
        }
        gameinfo();

    } while (playagain());
}

int main() {
    srand((unsigned)time(NULL));
    playGame();
}
