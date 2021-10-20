#include <LiquidCrystal.h>
#include <Servo.h>

#define pinServo1 43
#define pinServo2 42 
#define pinServo3 41
#define pinServo4 40

Servo servo1; //base
Servo servo2; //up/down
Servo servo3; //cotovelo
Servo servo4; //garra

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int menuGeral = 2;
int menuNivel = 2;
int menuIniciante = 2;
int estado = 0;
int estadoNivel = 0;
int estadoIniciante = 0;
int habilitaMenu = 1;
int habilitaNivel = 0;
int selectNivel = 0;
int start = 0;
int desprint = 1;
int player = 1;
int selectIniciante = 0;
int game = 0;
int difficulty=8;
int leituraSensor[9];
int desabilitaLeitura[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
int peca = 0;
int primeiraVez = 1;

void setup()
{
    Serial.begin(9600);
    servo1.attach(pinServo1);
    servo2.attach(pinServo2);
    servo3.attach(pinServo3);
    servo4.attach(pinServo4);
    delay(10);
    lcd.begin(16, 2);
    lcd.blink();
    lcd.cursor();
    PrintTitle();
    mov_inicial();
    UpDown();
}
void loop()
{
    int botoesMenu;
    int botoesNivel;
    int botoesIniciante;
    int select;
    
    if(habilitaMenu == 1)
    {   
        botoesMenu = valorBotoes();
        select = menuGeralPrincipal(botoesMenu);
        selectmenuGeral(select);
    }
    
    if(habilitaNivel == 1)
    {
        botoesNivel = valorBotoes();
        selectNivel = menuNivelPrincipal(botoesNivel);
        selectmenuNivel(selectNivel);
    }
   
    if(start == 1)
    {
         selectNivel = 0;
         botoesIniciante = valorBotoes();
         selectIniciante =  menuIniciantePrincipal(botoesIniciante);
         selectmenuIniciante(selectIniciante);   
    }

    if(game == 1)
    {
        int board[9] = {0,0,0,0,0,0,0,0,0}; 
        int i; 
 
    unsigned turn;
    for(turn = 0; turn < 9 && win(board) == 0; ++turn) {
        if((turn+player) % 2 == 0)
            computerMove(board, turn);
        else {
            draw(board);
            playerMove(board);
        }
    }
    switch(win(board)) {
        case 0:
            draw(board);
            Serial.println("Empatou!\n");
            lcd.clear();
            lcd.setCursor(4,0);
            lcd.print("Empatou!"); 
            delay(3000);
            lcd.clear();
            break;
        case 1:
            draw(board);
            Serial.println("Voce perdeu!\n");
            lcd.clear();
            lcd.setCursor(2,0);
            lcd.print("Voce perdeu!"); 
            delay(3000);
            lcd.clear();
            break;
        case -1:
            draw(board);
            Serial.println("Voce ganhou!\n");
            lcd.clear();
            lcd.setCursor(2,0);
            lcd.print("Voce ganhou!"); 
            delay(3000);
            lcd.clear();
            break;
    }
    Serial.println("Arrume as pecas para jogar novamente e aperte RST");
    while(i == 0)
    {
    i = 0;
    lcd.setCursor(0,0);
    lcd.print("Arrume as pecas!");
    lcd.setCursor(0,1);
    lcd.print("RST - Novo Jogo."); 
    }
    }
}
/**********************INÍCIO INTERFACE**********************/
void PrintTitle()//Deixa o Título a mostra
{
    lcd.setCursor(0,0);
    lcd.print("J");
    delay(100);
    lcd.setCursor(1,0);
    lcd.print("O");
    delay(100);
    lcd.setCursor(2,0);
    lcd.print("G");
    delay(100);
    lcd.setCursor(3,0);
    lcd.print("O");
    delay(100);
    lcd.setCursor(4,0);
    lcd.print(" ");
    delay(50);
    lcd.setCursor(5,0);
    lcd.print("D");
    delay(100);
    lcd.setCursor(6,0);
    lcd.print("A");
    delay(100);
    lcd.setCursor(7,0);
    lcd.print(" ");
    delay(50);
    lcd.setCursor(8,0);
    lcd.print("V");
    delay(100);
    lcd.setCursor(9,0);
    lcd.print("E");
    delay(100);
    lcd.setCursor(10,0);
    lcd.print("L");
    delay(100);
    lcd.setCursor(11,0);
    lcd.print("H");
    delay(100);
    lcd.setCursor(12,0);
    lcd.print("A");
    delay(100);
    lcd.noCursor();
    lcd.noBlink();
    lcd.setCursor(13,0);
    lcd.print(" ");
    delay(250);
    lcd.setCursor(15,0);
    lcd.print("#");
    delay(250);
    lcd.setCursor(15,0);
    lcd.print(" ");
    lcd.setCursor(14,0);
    lcd.print("#");
    delay(650);
}
void desprintTitle()
{
    lcd.setCursor(0,1);
    lcd.print("             ");
    lcd.noBlink();
    lcd.noCursor();
    lcd.setCursor(14,0);
    lcd.print(" ");
    delay(250);
    lcd.setCursor(15,0);
    lcd.print("#");
    delay(250);
    lcd.setCursor(15,0);
    lcd.print(" ");
    delay(250);
    lcd.blink();
    lcd.cursor();
    lcd.setCursor(13,0);
    lcd.print(" ");
    delay(100);
    lcd.setCursor(12,0);
    lcd.print(" ");
    delay(50);
    lcd.setCursor(11,0);
    lcd.print(" ");
    delay(100);
    lcd.setCursor(10,0);
    lcd.print(" ");
    delay(100);
    lcd.setCursor(9,0);
    lcd.print(" ");
    delay(50);
    lcd.setCursor(8,0);
    lcd.print(" ");
    delay(100);
    lcd.setCursor(7,0);
    lcd.print(" ");
    delay(100);
    lcd.setCursor(6,0);
    lcd.print(" ");
    delay(100);
    lcd.setCursor(5,0);
    lcd.print(" ");
    delay(100);
    lcd.setCursor(4,0);
    lcd.print(" ");
    delay(100);
    lcd.setCursor(3,0);
    lcd.print(" ");
    delay(100);
    lcd.setCursor(2,0);
    lcd.print(" ");
    delay(100);
    lcd.setCursor(1,0);
    lcd.print(" ");
    delay(100);
    lcd.setCursor(0,0);
    lcd.print(" ");
    lcd.noBlink();
    lcd.noCursor();
    desprint = 0;
    delay(650);
}
void UpDown()
{
    lcd.blink();
    lcd.cursor();
    lcd.setCursor(0,1);
    lcd.print("Press UP/DOWN");
}
int valorBotoes()
{
    int botoes = 0;
    int x = analogRead (0);
    lcd.setCursor(0,0);

    if (x < 100)
    {
        botoes = 0;
    }
    else if (x < 200)
    {
        botoes = 1;//cima
    }
    else if (x < 400)
    {
        botoes = 2;//baixo
    }
    else if (x < 600)
    {
        botoes = 0;
    }
    else if (x < 800)
    {
        botoes = 3;//select
    }
    else
      botoes = 0;
    return botoes;
}
int menuGeralPrincipal(int botoes)// realiza leitura do shield
{
    int select;
    if (botoes != estado)
    {
        if (botoes == 1)
        {
            if(desprint == 1)
      {
          desprintTitle();
      }
            menuGeral = menuGeral - 1;
            if(menuGeral%2==0)
            {
                menuGeral = 2;
            }
            else
            {
                menuGeral = 1;
            }
            displaymenuGeral(menuGeral);
            primeiraVez = 0;
        }
        else if (botoes == 2)
        {
          if(desprint == 1)
      {
          desprintTitle();
      }
            menuGeral = menuGeral + 1;
            if(menuGeral%2==0)
            {
                menuGeral = 2;
            }
            else
            {
                menuGeral = 1;
            }
            displaymenuGeral(menuGeral);
            primeiraVez = 0;
        }
        else if (botoes == 3)
        {
            if(primeiraVez == 1)
            {
              return 0;
            }
            habilitaMenu = 0;
            select = -menuGeral-1;
            return select;
        }
        estado = botoes;
    }
    delay(5);
}
int menuNivelPrincipal(int botoes)
{
    if (botoes != estadoNivel)
    {
        if (botoes == 1)
        {
            menuNivel = menuNivel - 1;
            if(menuNivel<1)
            {
                menuNivel=8;
            }
            else if(menuNivel>8)
            {
                menuNivel=1;
            }
            displaymenuNivel(menuNivel);
        }
        else if (botoes == 2)
        {
            menuNivel = menuNivel + 1;
            if(menuNivel<1)
            {
                menuNivel=8;
            }
            else if(menuNivel>8)
            {
                menuNivel=1;
            }
            displaymenuNivel(menuNivel);
        }
        else if (botoes == 3)
        {
            if(selectNivel == 0)
              selectNivel++;
            else{
            habilitaNivel = 0;
            selectNivel = -menuNivel-1;
            return selectNivel;}
        }
        estadoNivel = botoes;
    }
    delay(5);
}
int menuIniciantePrincipal(int botoes)// realiza leitura do shield
{
    if (botoes != estadoIniciante)
    {
        if (botoes == 1)
        {
            menuIniciante = menuIniciante - 1;
            if(menuIniciante%2==0)
            {
                menuIniciante= 2;
            }
            else
            {
                menuIniciante = 1;
            }
        }
        else if (botoes == 2)
        {
            menuIniciante = menuIniciante + 1;
            if(menuIniciante%2==0)
            {
                menuIniciante = 2;
            }
            else
            {
                menuIniciante = 1;
            }
        }
        else if (botoes == 3)
        {
            if(selectIniciante==0)
                {selectIniciante++;}
            else{
            selectIniciante = -menuIniciante-1;
            return selectIniciante;}
        }
        displaymenuIniciante(menuIniciante);
        estadoIniciante = botoes;
    }
    delay(5);
}
void displaymenuGeral(int x)//Imprime opcoes no display
{
    lcd.noBlink();
    lcd.noCursor();
    switch (x)
    {
    case 1:
        lcd.clear();
        lcd.print ("Selec. uma opcao");
        lcd.setCursor (0,1);
        lcd.print ("1.Jogar");
        break;
    case 2:
        lcd.clear();
        lcd.print ("Selec. uma opcao");
        lcd.setCursor (0,1);
        lcd.print ("2.Dificuldade");
        break;
    }
}
void displaymenuIniciante(int x)//Imprime opcoes no display
{
    lcd.noBlink();
    lcd.noCursor();
    switch (x)
    {
    case 1:
        lcd.clear();
        lcd.print ("Quem ira comecar?");
        lcd.setCursor (4,1);
        lcd.print ("1.EU (X)");
        break;
    case 2:
        lcd.clear();
        lcd.print ("Quem ira comecar?");
        lcd.setCursor (4,1);
        lcd.print ("2.PC (O)");
        break;
    }
}
void displaymenuNivel(int x)
{
    switch (x)
    {
    case 1:
        lcd.clear();
        lcd.print ("Selec. nivel 1a8");
        lcd.setCursor (5,1);
        lcd.print ("-> ");
        lcd.setCursor (8,1);
        lcd.print ("1");
        lcd.setCursor (9,1);
        lcd.print (" <-");
        break;
    case 2:
        lcd.clear();
        lcd.print ("Selec. nivel 1a8");
        lcd.setCursor (5,1);
        lcd.print ("-> ");
        lcd.setCursor (8,1);
        lcd.print ("2");
        lcd.setCursor (9,1);
        lcd.print (" <-");
        break;
    case 3:
        lcd.clear();
        lcd.print ("Selec. nivel 1a8");
        lcd.setCursor (5,1);
        lcd.print ("-> ");
        lcd.setCursor (8,1);
        lcd.print ("3");
        lcd.setCursor (9,1);
        lcd.print (" <-");
        break;
    case 4:
        lcd.clear();
        lcd.print ("Selec. nivel 1a8");
        lcd.setCursor (5,1);
        lcd.print ("-> ");
        lcd.setCursor (8,1);
        lcd.print ("4");
        lcd.setCursor (9,1);
        lcd.print (" <-");
        break;
    case 5:
        lcd.clear();
        lcd.print ("Selec. nivel 1a8");
        lcd.setCursor (5,1);
        lcd.print ("-> ");
        lcd.setCursor (8,1);
        lcd.print ("5");
        lcd.setCursor (9,1);
        lcd.print (" <-");
        break;
    case 6:
        lcd.clear();
        lcd.print ("Selec. nivel 1a8");
        lcd.setCursor (5,1);
        lcd.print ("-> ");
        lcd.setCursor (8,1);
        lcd.print ("6");
        lcd.setCursor (9,1);
        lcd.print (" <-");
        break;
    case 7:
        lcd.clear();
        lcd.print ("Selec. nivel 1a8");
        lcd.setCursor (5,1);
        lcd.print ("-> ");
        lcd.setCursor (8,1);
        lcd.print ("7");
        lcd.setCursor (9,1);
        lcd.print (" <-");
        break;
    case 8:
        lcd.clear();
        lcd.print ("Selec. nivel 1a8");
        lcd.setCursor (5,1);
        lcd.print ("-> ");
        lcd.setCursor (8,1);
        lcd.print ("8");
        lcd.setCursor (9,1);
        lcd.print (" <-");
        break;
    }
}
void selectmenuGeral(int x)//chama funcao da opcao escolhida
{   
    switch (x)
    {
    case -2:
        start = 1;
        menuIniciantePrincipal(1);
        break;
    case -3:
        habilitaNivel = 1;
        menuNivelPrincipal(1);
        break;
    }
}
void selectmenuNivel(int x)
{
    switch (x)
    {

    case -2:
        difficulty = 1;
        start = 1;
        menuIniciantePrincipal(1);
        break;
    case -3:
        difficulty = 2;
        start = 1;
        menuIniciantePrincipal(1);
        break;
    case -4:
        difficulty = 3;
        start = 1;
        menuIniciantePrincipal(1);
        break;
    case -5:
        difficulty = 4;
        start = 1;
        menuIniciantePrincipal(1);
        break;
    case -6:
        difficulty = 5;
        start = 1;
        menuIniciantePrincipal(1);
        break;
    case -7:
        difficulty = 6;
        start = 1;
        menuIniciantePrincipal(1);
        break;
    case -8:
        difficulty = 7;
        start = 1;
        menuIniciantePrincipal(1);
        break;
    case -9:
       difficulty = 8;
       start = 1;
       menuIniciantePrincipal(1);
       break;
    }
}
void selectmenuIniciante(int x)//chama funcao da opcao escolhida
{   
    int botoesNivel;
    switch (x)
    {
    case -2:
        player = 1;
        displayJogo();
        start = 0;
        game = 1;
        break;
    case -3:
        player = 2;
        displayJogo();
        start = 0;
        game = 1;
        break;
    }
}
void displayJogo()
{
    lcd.blink();
    lcd.cursor();
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("Q");
    delay(100);
    lcd.setCursor(3,0);
    lcd.print("U");
    delay(100);
    lcd.setCursor(4,0);
    lcd.print("E");
    delay(100);
    lcd.setCursor(5,0);
    lcd.print(" ");
    delay(100);
    lcd.setCursor(6,0);
    lcd.print("O");
    delay(50);
    lcd.setCursor(7,0);
    lcd.print("S");
    delay(100);
    lcd.setCursor(8,0);
    lcd.print(" ");
    delay(100);
    lcd.setCursor(9,0);
    lcd.print("J");
    delay(50);
    lcd.setCursor(10,0);
    lcd.print("O");
    delay(100);
    lcd.setCursor(11,0);
    lcd.print("G");
    delay(100);
    lcd.setCursor(12,0);
    lcd.print("O");
    delay(100);
    lcd.setCursor(13,0);
    lcd.print("S");
    delay(100);
    lcd.setCursor(4,1);
    lcd.print("C");
    delay(100);
    lcd.setCursor(5,1);
    lcd.print("O");
    delay(100);
    lcd.setCursor(6,1);
    lcd.print("M");
    delay(100);
    lcd.setCursor(7,1);
    lcd.print("E");
    delay(100);
    lcd.setCursor(8,1);
    lcd.print("C");
    delay(100);
    lcd.setCursor(9,1);
    lcd.print("E");
    delay(100);
    lcd.setCursor(10,1);
    lcd.print("M");
    delay(2000);
    
    lcd.setCursor(10,1);
    lcd.print(" ");
    delay(100);
    lcd.setCursor(9,1);
    lcd.print(" ");
    delay(100);
    lcd.setCursor(8,1);
    lcd.print(" ");
    delay(100);
    lcd.setCursor(7,1);
    lcd.print(" ");
    delay(100); 
    lcd.setCursor(6,1);
    lcd.print(" ");
    delay(50);
    lcd.setCursor(5,1);
    lcd.print(" ");
    delay(100);
    lcd.setCursor(4,1);
    lcd.print(" ");
    delay(100);
    lcd.setCursor(13,0);
    lcd.print(" ");
    delay(50);
    lcd.setCursor(12,0);
    lcd.print(" ");
    delay(100);
    lcd.setCursor(11,0);
    lcd.print(" ");
    delay(100);
    lcd.setCursor(10,0);
    lcd.print(" ");
    delay(100);
    lcd.setCursor(9,0);
    lcd.print(" ");
    delay(100);
    lcd.setCursor(8,0);
    lcd.print(" ");
    delay(100);
    lcd.setCursor(7,0);
    lcd.print(" ");
    delay(100);
    lcd.setCursor(6,0);
    lcd.print(" ");
    delay(100);
    lcd.setCursor(5,0);
    lcd.print(" ");
    delay(100);
    lcd.setCursor(4,0);
    lcd.print(" ");
    delay(100);
    lcd.setCursor(3,0);
    lcd.print(" ");
    delay(100);
    lcd.setCursor(2,0);
    lcd.print(" ");
    lcd.noBlink();
    lcd.noCursor();
    delay(1500);
}
/**********************FIM INTERFACE********************************/

/**********************INÍCIO MOVIMENTAÇÃO BRAÇO********************/
void mov_inicial()
{
    servo2.write(50);
    delay(350);
    servo3.write(170);
    delay(500);
    servo1.write(150);
    delay(350);
    servo3.write(90);
    delay(350);
    servo4.write(30);
    delay(250);
}
void mov_peca_A()
{
    servo1.write(133);
    delay(500);
    servo3.write(130);
    delay(500);
    servo2.write(70);
    delay(500);
    servo4.write(179);
    delay(500);
    servo2.write(35);
    delay(250);
 
    
}
void mov_peca_B()
{
    servo1.write(137);
    delay(500);
    servo3.write(150);
    delay(500);
    servo2.write(75);
    delay(500);
    servo4.write(179);
    delay(250);
    servo2.write(35);
    delay(250);
}
void mov_peca_C()
{
    servo1.write(145);
    delay(500);
    servo3.write(174);
    delay(500);
    servo2.write(82);
    delay(500);
    servo4.write(179);
    delay(250);
    servo2.write(35);
    delay(250);
}
void mov_peca_D()
{
    servo1.write(123);
    delay(500);
    servo3.write(155);
    delay(500);
    servo2.write(75);
    delay(500);
    servo4.write(179);
    delay(500);
    servo2.write(35);
    delay(250);
}
void mov_peca_E()
{
    
    servo1.write(132);
    delay(500);
    servo3.write(173);
    delay(500);
    servo2.write(82);
    delay(500);
    servo4.write(179);
    delay(500);
    servo2.write(35);
    delay(250);
}
void mov_tab_0()
{
    servo1.write(62);
    delay(250);
    servo2.write(50);
    delay(250);
    servo3.write(120);
    delay(250);
    servo4.write(15);
    delay(250);
}
void mov_tab_1()
{
    servo1.write(73);
    delay(250);
    servo2.write(50);
    delay(250);
    servo3.write(90);
    delay(250);
    servo4.write(15);
    delay(250);
}
void mov_tab_2()
{
    servo1.write(102);
    delay(250);
    servo2.write(25);
    delay(250);
    servo3.write(90);
    delay(250);
    servo4.write(15);
    delay(250);
}
void mov_tab_3()
{
    servo1.write(70);
    delay(250);
    servo3.write(145);
    delay(250);
    servo2.write(76);
     delay(250);
    servo4.write(15);
    delay(250);
}
void mov_tab_4()
{
    servo1.write(85);
    delay(250);
    servo3.write(115);
    delay(250);
    servo2.write(76);
    delay(250);
    servo4.write(15);
    delay(250);
}
void mov_tab_5()
{
    servo1.write(99);
    delay(250);
    servo3.write(140);
    delay(250);
    servo2.write(75);
     delay(250);
    servo4.write(15);
    delay(250);
}
void mov_tab_6()
{
    servo1.write(73);
    delay(250);
    servo3.write(179);
    delay(250);
    servo2.write(110);
    delay(100);
    servo2.write(87);
     delay(250);
    servo4.write(15);
    delay(250);
}
void mov_tab_7()
{
    servo1.write(85);
    delay(250);
    servo3.write(170);
    delay(250);
    servo2.write(90);
     delay(250);
    servo4.write(15);
    delay(250);
}
void mov_tab_8()
{
    servo1.write(97);
    delay(250);
    servo3.write(170);
    delay(250);
    servo2.write(90);
     delay(250);
    servo4.write(15);
    delay(250);
}

/**********************FIM MOVIMENTAÇÃO BRAÇO***********************/

/**********************INÍCIO JOGO********************/
char displayChar(int c) {
    switch(c) {
        case -1:
            return 'X';
        case 0:
            return ' ';
        case 1:
            return 'O';
    }
}

void draw(int board[9]) {
    Serial.print(" ");Serial.print(displayChar(board[0])); Serial.print(" | ");Serial.print(displayChar(board[1])); Serial.print(" | ");Serial.print(displayChar(board[2])); Serial.println(" ");
    Serial.println("---+---+---");
    Serial.print(" ");Serial.print(displayChar(board[3])); Serial.print(" | ");Serial.print(displayChar(board[4])); Serial.print(" | ");Serial.print(displayChar(board[5])); Serial.println(" ");
    Serial.println("---+---+---");
    Serial.print(" ");Serial.print(displayChar(board[6])); Serial.print(" | ");Serial.print(displayChar(board[7])); Serial.print(" | ");Serial.print(displayChar(board[8])); Serial.println(" ");
}

int win(const int board[9]) {
    //list of possible winning positions
    unsigned wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int winPos;
    for(winPos = 0; winPos < 8; ++winPos) {
        if(board[wins[winPos][0]] != 0 && board[wins[winPos][0]] == board[wins[winPos][1]] && board[wins[winPos][0]] == board[wins[winPos][2]])
            return board[wins[winPos][2]];
    }
    return 0;
}

int minimax(int board[9], int player, int depth) {
    //check the positions for players
    int winner = win(board);
    if(winner != 0) return winner*player;

    int move = -1;
    int score = -2;
    int i;
    for(i = 0; i < 9; ++i) {
     
        if(board[i] == 0) {
            board[i] = player;
            int thisScore=0;
            if (depth<difficulty){
              thisScore = -minimax(board, player*-1,depth+1);
            }
            
            if(thisScore > score) {
                score = thisScore;
                move = i;
            }
            //choose the worst move for opponent
            board[i] = 0;
        }
    }
    if(move == -1) return 0;
    return score;
}

void computerMove(int board[9], int turn) {
    int move = -1;
    int score = -2;
    int i;

    if(turn == 0){
       Serial.println("\nPreparando jogo");
       lcd.cursor();
       lcd.blink();
       lcd.setCursor(0,0);
       lcd.print("Preparando jogo");
    }
    else{
    Serial.println("\nMinha vez...haha\n\n");
    lcd.noCursor();
    lcd.noBlink();
    lcd.clear();
    lcd.print("Minha vez...haha");
    }
    for(i = 0; i < 9; ++i) {
        if(board[i] == 0) {
            board[i] = 1;
            int tempScore = -minimax(board, -1, 0);
            board[i] = 0;
            if(tempScore > score) {
                score = tempScore;
                move = i;
            }
        }
    }
    //returns a score based on minimax tree at a given node.
    if(turn == 0){
    Serial.println("\nMinha vez...haha\n\n");
    lcd.clear();
    lcd.print("Minha vez...haha");
    }
    // pega peca
    if(peca == 0)
    {
      mov_peca_A();
    }
    else if(peca == 1)
    {
      mov_peca_B();
    }
    else if(peca == 2)
    {
      mov_peca_C();
    }
    else if(peca == 3)
    {
      mov_peca_D();
    }
    else if(peca == 4)
    {
      mov_peca_E();
    }
    //Leva peca ao lugar
    if(move == 0)
    {
      mov_tab_0();
      mov_inicial();
    }
    else if(move == 1)
    {
      mov_tab_1();
      mov_inicial();
    }
    else if(move == 2)
    {
      mov_tab_2();
      mov_inicial();
    }
    else if(move == 3)
    {
      mov_tab_3();
      mov_inicial();
    }
    else if(move == 4)
    {
      mov_tab_4();
      mov_inicial();
    }
    else if(move == 5)
    {
      mov_tab_5();
      mov_inicial();
    }
    else if(move == 6)
    {
      mov_tab_6();
      mov_inicial();
    }
    else if(move == 7)
    {
      mov_tab_7();
      mov_inicial();
    }
    else if(move == 8)
    {
      mov_tab_8();
      mov_inicial();
    }

    board[move] = 1;
    peca++;
    
}

void playerMove(int board[9]) {
  
    int move = 0;
    int valor = 10;

    lcd.clear();
    lcd.print("Sua vez de jogar");
    
    do {
        Serial.println("\nSua vez de jogar");
         
          while(valor==10){
          delay(100);
          if(desabilitaLeitura[0]==0 && board[0] != 1) 
          {   
          leituraSensor[0] = digitalRead(22);
            if(leituraSensor[0] == 0)
            {
              valor = 0;
              break;
            }
          }
          
          if(desabilitaLeitura[1]==0 && board[1] != 1) 
          {   
          leituraSensor[1] = digitalRead(24);
          if(leituraSensor[1] == 0)
            {
              valor = 1;
              break;
            }
          }
          
          if(desabilitaLeitura[2]==0 && board[2] != 1) 
          {  
          leituraSensor[2] = digitalRead(26);
          if(leituraSensor[2] == 0)
            {
              valor = 2;
              break;
            }
          }

          if(desabilitaLeitura[3]==0 && board[3] != 1) 
          {  
          leituraSensor[3] = digitalRead(28);
          if(leituraSensor[3] == 0)
            {
              valor = 3;
              break;
            }
          }

          if(desabilitaLeitura[4]==0 && board[4] != 1) 
          { 
          leituraSensor[4] = digitalRead(30);
          if(leituraSensor[4] == 0)
            {
              valor = 4;
              break;
            }
          }

          if(desabilitaLeitura[5]==0 && board[5] != 1) 
          { 
          leituraSensor[5] = digitalRead(32);
          if(leituraSensor[5] == 0)
            {
              valor = 5;
              break;
            }
          }

          if(desabilitaLeitura[6]==0 && board[6] != 1) 
          { 
          leituraSensor[6] = digitalRead(34);
          if(leituraSensor[6] == 0)
            {
              valor = 6;
              break;
            }
          }

          if(desabilitaLeitura[7]==0 && board[7] != 1) 
          {   
          leituraSensor[7] = digitalRead(36);
          if(leituraSensor[7] == 0)
            {
              valor = 7;
              break;
            }
          }

          if(desabilitaLeitura[8]==0 && board[8] != 1) 
          {  
          leituraSensor[8] = digitalRead(38);
          if(leituraSensor[8] == 0)
            {
              valor = 8;
              break;
            }
          }
            delay(100);
            }
        move = valor;
        desabilitaLeitura[valor] = 1;
      
        Serial.println("\n");
    } while ((move >= 9 || move < 0) || board[move] != 0);
    board[move] = -1;
    draw(board);
    delay(100);
}
/**********************FIM JOGO********************/
