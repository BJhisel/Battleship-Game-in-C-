#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
int x = 0, P = 10, A = 6, B = 5, D = 4, F = 4, L = 3; 
char visibleGameBoard[14][14];
char gameBoard[14][14] = {};
void activatedInvalidOption();
void activatedTrick();
void activatedTrickWinGame();
void attackPlayer(); 
void canceldGamesCount();
void commentWarning(int positionX, int positionY); 
void createStatsTop();
bool isAdjacent(int row, int col);
bool isValidPlacement(int row, int col, int size, int colSize, int orientation);
void placeShips(int size, int colSize, char shipType); 
void placeShipOnBoard(int row, int col, int size, int colSize, int orientation, char shipType); 
void principalMenu(); 
void printBoard(); 
void printVisibleBoard(); 
void showStatistics();
void sinkShips(char& letter); 
void startAgain();
void winnerInformation(); 
void gamePlayOption();
void goodbyeMessage();
void header();
bool activated;
int canceledGames = 0;
int gamesWin = 0;
int shipsLeft = 32;
int option;
string name;


    int main(){ 
    activated=false;
    srand(time(NULL));
    for (int i=0; i<14; i++){
        for (int j=0; j<14; j++){
            gameBoard[i][j]= ' ';
        }
    }
    
    for(int i=0; i<14; i++){
        for (int j = 0; j < 14; j++) {
            visibleGameBoard[i][j]= gameBoard[i][j];
        }
    }
    
    placeShips(5, 2, 'P');
    placeShips(3, 1, 'L');
    placeShips(4, 1, 'F');
    placeShips(5, 1, 'B');
    placeShips(6, 1, 'A');
    placeShips(4, 1, 'D');
         
    principalMenu();
}       

    
    void activatedInvalidOption(){

        if (option > 2 && option != 123 && option != 321) {
                 cout << "    Opcion incorrecta, por favor escriba nuevamente."; //Si cumple todas estas condiciones
                 cout<<endl;
                 gamePlayOption();
                }
             }

    void activatedTrick(){
        if(option == 123){ //Comando para ver el tablero oculto
            system("clear");
                activated=true;
                header();
                printVisibleBoard();
            }
    }
    
    void activatedTrickWinGame(){
        if(option==321){ //Comando para ganar la partida
                    system("clear");
                    winnerInformation();
            }
    }
    
    
    void attackPlayer(){
    int positionX, positionY; 
    char letter;
    cout<<endl;
    cout << "Ingrese la posición de ataque (X, Y). (Numero negativo para cancelar).";
        while (shipsLeft!=0) {
         cout<<endl;
         cout << "X: ";
            cin >> positionX;
            if (positionX < 0) {
                system("clear");
            printVisibleBoard();
        }
        
        cout << "Y: ";
            cin >> positionY;
            if (positionY < 0) {
            system("clear");
            printVisibleBoard();
        }
            if ((positionX > 13 || positionY > 13) && (positionX != 123 && positionY != 123) && (positionX != 321 && positionY != 321)) {
                 cout << "    Numero incorrecto, por favor escriba nuevamente."; //Si cumple todas estas condiciones
                }else{
                    commentWarning(positionX, positionY); //Si no, ha digitado cords normales
                }
        }
    }
    
    
    void canceldGamesCount() {
    system("clear");
    int anyNumber;
    printBoard();
    cout << "               Partida cancelada.                " << endl;
    canceledGames++;
    cout << endl;
    cout << "       Presiona un numero para continuar.";
    cin >> anyNumber;
    cout << endl;
    startAgain();
}


    void commentWarning(int positionX, int positionY) {
    char letter;
    if (gameBoard[positionX][positionY] == ' ') {
        x++;
        system("clear");
        sinkShips(letter);
        cout<<endl;
        cout << "_______________________________________________" << endl;
        cout<< endl;
        cout << "     NOTIFY: Usted NO ha acertado! " << endl;
        gameBoard[positionX][positionY] = 'O';
        visibleGameBoard[positionX][positionY] = 'O';
        printVisibleBoard();
        
    } else if ((gameBoard[positionX][positionY] == 'X') || (gameBoard[positionX][positionY] == 'O')) {
        x++;
        system("clear");
        sinkShips(letter);
        cout<<endl;
        cout << "_______________________________________________" << endl;
        cout<< endl;
        cout << "     NOTIFY: Usted ya ha atacado en esta posicion! " << endl;
        printVisibleBoard();
    } else  { //CONDICIONAL SI ACEPTÓ
        system("clear");
        letter = gameBoard[positionX][positionY]; //Remplaza la variable letra por la letra del barco al q le pegó
        sinkShips(letter); 
        gameBoard[positionX][positionY] = 'X';
        visibleGameBoard[positionX][positionY] = 'X';
        cout<<endl;
        cout << "_______________________________________________" << endl;
        cout<< endl;
        cout << "     NOTIFY: Usted ha acertado! " << endl;
        printVisibleBoard();
    }
}
    void gamePlayOption(){
        cout<<endl;
        cout<<"1. Atacar una coordenada."<<endl;
        cout<<"2. Cancelar partida."<<endl; 
        cin>>option;
        if(option==1){
            attackPlayer();
        }if(option==2){
            canceldGamesCount();
        }else{
            activatedTrick();
            activatedTrickWinGame();
            activatedInvalidOption();
        }
    }
    
    void goodbyeMessage(){
        system("clear");
        cout<<"Salida exitosa!";
        return;
    }
    
    void header(){
    cout << "          ______________________________" << endl;
    cout << "              _   _   _____   _   _     "<< endl;
    cout << "         .  /| |_| |/|  _  |/| '.| | *   "<< endl; 
    cout << "            ||_____|||_|||_|||_^___|    "<< endl;
    cout << "          ' |/____/ |/_/|/_/|/_//_/     "<< endl;
    cout << "               .                    '  " <<endl;     
    cout << "        *         S  H  I  P  S       *     "<< endl;
    cout << "          ______________________________" << endl;
    cout << endl;
    
    
}


    bool isAdjacent(int row, int col) {
    for (int i = row - 1; i <= row + 1; i++) {
        for (int j = col - 1; j <= col + 1; j++) {
            if (i >= 0 && i < 14 && j >= 0 && j < 14) {
                if (gameBoard[i][j] != ' ') {
                    return true;
                }
            }
        }
    }
    return false;
}

bool isValidPlacement(int row, int col, int size, int colSize, int orientation) {
    if (colSize == 1) {
        if (orientation == 0) {
            if (col + size >= 14) {
                return false;
            } else {
                for (int j = col; j < col + size; j++) {
                    if (gameBoard[row][j] != ' ' || isAdjacent(row, j)) {
                        return false;
                    }
                }
            }
        } else {
            if (row + size >= 14) {
                return false;
            } else {
                for (int i = row; i < row + size; i++) {
                    if (gameBoard[i][col] != ' ' || isAdjacent(i, col)) {
                        return false;
                    }
                }
            }
        }
    } else {
        if (orientation == 0) {
            if (col + colSize >= 14 || row + size >= 14) {
                return false;
            } else {
                for (int j = col; j < col + colSize; j++) {
                    for (int i = row; i < row + size; i++) {
                        if (gameBoard[i][j] != ' ' || isAdjacent(i, j)) {
                            return false;
                        }
                    }
                }
            }
        } else {
            if (row + colSize >= 14 || col + size >= 14) {
                return false;
            } else {
                for (int i = row; i < row + colSize; i++) {
                    for (int j = col; j < col + size; j++) {
                        if (gameBoard[i][j] != ' ' || isAdjacent(i, j)) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    
    return true;
}

void placeShipOnBoard(int row, int col, int size, int colSize, int orientation, char shipType) {
    if (colSize != 1) {
        if (orientation == 0) {
            for (int j = col; j < col + colSize; j++) {
                for (int i = row; i < row + size; i++) {
                    gameBoard[i][j] = shipType;
                }
            }
        } else {
            for (int i = row; i < row + colSize; i++) {
                for (int j = col; j < col + size; j++) {
                    gameBoard[i][j] = shipType;
                }
            }
        }
    } else {
        if (orientation == 0) {
            for (int j = col; j < col + size; j++) {
                gameBoard[row][j] = shipType;
            }
        } else {
            for (int i = row; i < row + size; i++) {
                gameBoard[i][col] = shipType;
            }
        }
    }
}

void placeShips(int size, int colSize, char shipType) {
    bool success = false;
    int row, col, orientation;
    
    while (!success) {
        row = rand() % 14;
        col = rand() % 14;
        orientation = rand() % 2;
        success = isValidPlacement(row, col, size, colSize, orientation);
    }
    
    placeShipOnBoard(row, col, size, colSize, orientation, shipType);
}


void principalMenu(){
    system("clear");
    int optionMenu;
    header();
    cout<<" "<<endl;
    cout<<"               Iniciar partida : 1 "<<endl;
    cout<<"             Mostrar estadisticas : 2 "<<endl;
    cout<<"              Finalizar partida : 3 "<<endl;
    cout<<" "<<endl;
    cout<<"          ______________________________"<<endl;
    cin>>optionMenu;
    system("clear");
    switch(optionMenu){
        case 1:
         header();
         printVisibleBoard();
         break;
        case 2: 
        showStatistics();
        break;
        case 3:
        goodbyeMessage();
        break;
        default: 
        cout<<"Opcion no valida!";
    }
    }
    


void printVisibleBoard() {
    
    if (activated==true) {
        printBoard();
    }else{
      cout << endl;
    cout << "    ";
    for (int i = 0; i < 14; i++) {
        if (i < 10) {
            cout << i << "  ";
        } else {
            cout << i << " ";
        }
    }
    cout << endl;
    cout << "    -----------------------------------------" << endl;
    
    
    for (int i = 0; i < 14; i++) {
        char columnBorder = 'A' + i; 
            cout << columnBorder << "  | ";
        for (int j = 0; j < 14; j++) {
            if (visibleGameBoard[i][j] == ' ') {
                cout << "." << "  ";
            } else {
                cout << visibleGameBoard[i][j] << "  ";
            }
        }
        
        cout << endl;
    }  
    }
    
    gamePlayOption();
}

void printBoard() {
    cout << endl;
    cout << "    ";
    for (int i = 0; i < 14; i++) {
        if (i < 10) {
            cout << i << "  ";
        } else {
            cout << i << " ";
        }
    }
    
    cout << "       ";
    
    for (int i = 0; i < 14; i++) {
        if (i < 10) {
            cout << i << "  ";
        } else {
            cout << i << " ";
        }
    }
    
    cout << endl;
    cout << "    -----------------------------------------" << "       " << "-----------------------------------------" << endl;

    for (int i = 0; i < 14; i++) {
        char columnBorder = 'A' + i; 
        cout << columnBorder << " | ";
        for (int j = 0; j < 14; j++) {
            
            if (visibleGameBoard[i][j] == ' ') {
                cout << "." << "  ";
            } else {
                cout << visibleGameBoard[i][j] << "  ";
            }
        }
        
        
        cout <<"   "<< columnBorder << " | ";

        
        for (int j = 0; j < 14; j++) {
            if (gameBoard[i][j] == ' ') {
                cout << "." << "  ";
            } else {
                cout << gameBoard[i][j] << "  ";
            }
        }
        
        cout << endl;
    }
}



void showStatistics(){
    int anyNumber;
    header(); 
     cout<<" "<<endl;
    cout<<"\t   Partidas canceladas :  "<< canceledGames << endl;
    cout<<"\t   Partidas ganadas :     "<< gamesWin << endl;
    cout<<"\t ______________________________"<<endl;
    cout<<"\n\t\tTop 5 de puntajes.";
    cout<<endl;cout<<endl;
    createStatsTop();
    cout<<"\t ______________________________"<<endl;
     cout << "\n    Presiona un numero para volver al menu: ";
    cin >> anyNumber;
    cout << endl;
    startAgain();
}

void sinkShips(char& letter) {
    header();
    cout << "      SINK SHIPS : " << endl;
    if (letter == 'P') {
        P--;
        shipsLeft--; //Contador que disminuye cada que un barco ha sido hundido (Num. de barcos= 6. Si barcos=0 entonces ha ganado)
        }if (P == 0) {
            cout << "     'Portaaviones' ha sido hundido!   ";
            
        }
       
    
    if (letter == 'A') {
        A--;
        shipsLeft--;
        }if (A == 0) {
            cout << "     'Acorazado' ha sido hundido!   " << endl;
            
        }
    
    if (letter == 'B') {
        B--;
        shipsLeft--; 
        }if (B == 0) {
            cout << "     'Buque' ha sido hundido!   ";
            
        }
    
    if (letter == 'D') {
        D--;
        shipsLeft--; 
        }if (D == 0) {
            cout << "     'Destructor' ha sido hundido!   " << endl;
            
        }
    
    if (letter == 'F') {
        F--;
        shipsLeft--; 
        }if (F == 0) {
            cout << "     'Fragata' ha sido hundido!   ";
            
        }
    
    if (letter == 'L') {
        L--;
        shipsLeft--; 
        }if (L == 0) {
            cout << "    'Lancha Rapida' ha sido hundida!   ";
            gamesWin++;
            
        }
    
    if (shipsLeft == 0) {
        gamesWin++;
        winnerInformation();
        showStatistics();
    }
    
}

void startAgain() {
    int answer;
    system("clear");
    main();
}
 
void winnerInformation(){
    
    int anyNumber;
    int P=196;
    header();
    cout << endl;
    cout << "             F E L I C I D A D E S!              " << endl;
    cout << "_______________________________________________  " << endl;
    cout << endl;
    cout << "         Has hundido todos los barcos!           " << endl;
    cout << "            Has ganado la partida!               " << endl;
    cout << "_______________________________________________  " << endl;
    gamesWin++;
    cout<<"               Ingrese su nombre: ";
    cin>>name;
    cout<<endl;
    cout<<"               Total Score: "<<P-x<<endl;
    cout<<endl;
    cout<<"       Presiona un numero para continuar.";cin>>anyNumber;
    startAgain();
 }
 
 void createStatsTop() {
     
    ofstream scoresFile("scores.txt", ios::app);
    scoresFile << name << ": " << P - x << endl;
    scoresFile.close();

    ifstream scoresReadFile("scores.txt");
    vector<pair<int, string>> scores;
    string line;

    while (getline(scoresReadFile, line)) {
        int score = stoi(line.substr(line.find(":") + 2));
        scores.push_back(make_pair(score, line));
    }

    scoresReadFile.close();
    sort(scores.rbegin(), scores.rend()); // Ordenar en orden descendente

    int topCount = min(5, static_cast<int>(scores.size()));
    for (int i = 0; i < topCount; i++) {
        cout <<"\t\t"<< scores[i].second << endl;
    }
}