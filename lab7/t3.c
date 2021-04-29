// Tic-tac-toe (T3) Network Game
// Jason Losh

//-----------------------------------------------------------------------------
// Compile notes for C99 code
//-----------------------------------------------------------------------------

// gcc -o t3 t3.c udp.c

//-----------------------------------------------------------------------------
// Device includes, defines, and assembler directives
//-----------------------------------------------------------------------------

#include <stdlib.h>          // EXIT_ codes
#include <stdbool.h>         // bool
#include <stdio.h>           // printf, scanf
#include <string.h>          // strlen, strcmp

#include "udp.h"

#define CLIENT_PORT 4096
#define SERVER_PORT 4097

void clearBoard(char board[3][3])
{
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            board[r][c] = '.';
}

// TODO: Add code to display the game board
void showBoard(char board[3][3])
{
    for(int i = 0; i<3 ; i++)
    {
        for(int j =0 ; j < 3; j++)
        {
            printf("%-3c", board[i][j]);
        }
        printf("\n");
    }
    
}

// TODO: Add code to determine if a winner (xo) has occurred
bool isWinner(char board[3][3], char xo)
{
    bool win;
    
    
            if((board[0][0] == xo && board [0][1] == xo && board[0][2])// horizontal check
            || (board[1][0] == xo && board [1][1] == xo && board[1][2])
            || (board[2][0] == xo && board [2][1] == xo && board[2][2])
            || (board[0][0] == xo && board [1][0] == xo && board[2][0])// vertical check
            || (board[0][1] == xo && board [1][1] == xo && board[2][1])
            || (board[0][2] == xo && board [1][2] == xo && board[2][2])
            || (board[0][0] == xo && board [1][1] == xo && board[2][2]) // diagonal check
            || (board[2][0] == xo && board [1][1] == xo && board[0][2]))
            {
                win = true;
            }
            else
            {
                win = false;
            }   
            
    return win;
    
}

// TODO: Add code to test if an x or o (xo) is a valid move
//       and then record in the game board
bool addMove(char board[3][3], char move[], char xo)
{
     bool ok = strlen(move) == 2; 
     int i , j;
     if(ok)
     {
         if(move[0] ==  'A' ||  move[0]  == 'B' || move[0]  == 'C')
         {
             if(move[1] == 1 ||  move[1]  == 2 || move[1]  == 3)
              {
                  bool ok = true;
                  switch (move[0])
                  {
                      case 'A' : 
                        i = 0;
                        break;
                      case 'B' :
                        i = 1;
                        break;
                      case 'C' :
                        i = 2;
                        break;
                    }
                   switch (move[1])
                   {
                       case 1 :
                           j = 1;
                           break;
                       case 2 :
                            j=2;
                            break;
                        case 3 :
                            j = 3;
                            break;
                    }
                    
                    board [i][j] = 'x';
                }
         }
    }
    else 
    {
        ok = false;
    }
    
    
    // ...
    return ok;
}

//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    char *remoteIp;
    char *role;
    char str[100], str2[100];
    char board[3][3];
    bool validMove;
    bool winner = false;
    int moveCount = 0;

    bool myTurn;
    char myLetter, opponentLetter;
    int remotePort;

    // TODO: Verify arguments are valie
     bool goodArguments;
    // ...
    if(argc == 3)
    {
        goodArguments = true;
    }
    
    bool client;
    if( (strcmp(argv[2],"accept")) == 0)
    {
        
        //printf("You selected to accept an invite.\n");
        
        //goodArguments = true;
        
        remoteIp = argv[1];
        client = false;
        role = argv[2];
    }
    else if ( (strcmp(argv[2],"invite")) == 0)
    {
        //printf("You selected to invite someone.\n");
        //goodArguments = true;
        
        remoteIp = argv[1];
        client = true;
        role = argv[2];
    }
    
    bool port;
    if(client)
    {
        port = openListenerPort(remoteIp,CLIENT_PORT);
    }
    else 
    {
        port = openListenerPort(remoteIp,SERVER_PORT);
    }
    
    if(!port)
    {
        printf("Unable to connect to port.\n");
        exit(1);
    }
    
    
    
    
    if (!goodArguments)
    {
        printf("usage: t3 IPV4_ADDRESS ROLE\n");
        printf("  where:\n");
        printf("  IPV4_ADDRESS is address of the remote machine\n");
        printf("  ROLE is either invite or accept\n");
        exit(EXIT_FAILURE);
    }
    else 
    {
        remoteIp = argv[1];
    }
    
    
    

    // TODO: Determine if client or server
    // A server will wait to accept an invitation to play
    // A client will send an invitation to play
    bool condition;
    if(client)
    {
        printf("Sending invite...\n");
        remotePort = SERVER_PORT;
        condition = sendData(remoteIp,CLIENT_PORT,role);
        if (condition)
        {
            printf("Invitation sent");
        }
        else
        {
            printf("Invitation not sent");
        }
            
    }
    else
    {
        printf("Waiting to receive an invite...\n");
        remotePort = CLIENT_PORT;
        receiveData(str, sizeof(str));
        
        printf("Invite received!\n");
        
        if(strcmp(str, "invite") != 0)
        {
            printf("You request is invalid\n");
            exit(1);
        }
    }
    
    
    //////////////////////////////////////////////////////////////////////

    
    closeListenerPort();
        
    // TODO: Open listener port number dependent on client/server role

    // TODO: Determine remote port that you will send data to
    //       If you are server, send to client port, and vice versa

    // Setup game
    clearBoard(board);

    // TODO: Determine whether it is your turn or not
    myTurn = !client;

    // TODO: Determine your letter (x or o) and your opponent's letter

    if(client)
    {
        myLetter = 'o';
        opponentLetter = 'X';
    }
    else
    {
        myLetter = 'o';
        opponentLetter = 'X';
    }
    
    // TODO: Add code to send an invite or wait to accept an invite

    // Start game loop, alternating turns
    while(!winner && moveCount != 9)
    {
        // get my move
        if (myTurn)
        {
            // TODO: add code your move here to get the move, validate move,
            //       show board, send move to remote port, and check for a winner
            validMove = false;
            while(!validMove)
            {
                printf("\nEnter your move (%c): ",myLetter);
                scanf("%s",str2);
                validMove = addMove(board, str2, myLetter);
            }
            sendData(remoteIp, remotePort, str2);
            showBoard(board);
            winner = isWinner(board,myLetter);
            if(winner)
            {
                printf("You (%c) won.\n",myLetter);
            }
        }
        // get opponent's move
        else
        {
            // TODO: add code to receive your opponent's move, validate move,
            //       show board, and check for a winner
            receiveData(str2, sizeof(str2));
            validMove = addMove(board, str2, opponentLetter);
            printf("Your opponent moved to %s\n",str2);
            showBoard(board);
            winner = isWinner(board, opponentLetter);
            if(winner)
            {
                printf("Your opponent (%c) won.\n", opponentLetter);
            }
        }

        // Increment move count, alternate turns
        moveCount++;
        myTurn = !myTurn;
    }
    if (!winner)
        printf("The game was a draw\n");


    // TO DO: Close listener port
    return EXIT_SUCCESS;
}
