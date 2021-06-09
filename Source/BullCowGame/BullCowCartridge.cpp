// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    
    SetupGame();

    PrintLine((TEXT("The HiddenWord is: %s"), *HiddenWord)); //Debug Line
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
     //if game is over then do ClearScreen and Setup the game
    if (bGameOver)
    {
        PrintLine(TEXT("Cleaning screen...\nNew game..."));
        //ClearScreen();
        SetupGame();
    }
    else
    {
        ProcessGuess(Input);        
    }
     

}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = TEXT("cake");
    //Set lives
    Lives = HiddenWord.Len();
    bGameOver=false;

    //Welcoming the player
    PrintLine(TEXT("Welcome to Bulls and Cows Game!!"));
    PrintLine(TEXT("Guess the  %i letter isometric word!"), HiddenWord.Len());
    PrintLine(TEXT("You've %i lives."),Lives);
    PrintLine(TEXT("Type in your guess.\nPress enter to continue..."));

    const TCHAR HW[]=TEXT ("cake");
    PrintLine(TEXT("The character 1 of the hidden word is: %c"), HW[0]);

        
}

void UBullCowCartridge::EndGame()
{
    bGameOver=true;
    PrintLine(TEXT("Press enter to play again..."));
    ClearScreen();
    
    
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{

  if (HiddenWord == Guess)
    {
        PrintLine(TEXT("******** You have won!!********"));
       // EndGame();
        return;
    }
  //Check If is  Isogram
     if (!IsIsogram(Guess))
        {
        //PrintLine(TEXT("No repeating letters, guess again"));
        return;
        }
    
    //Check Right Number Characters
    if (HiddenWord.Len()!=Guess.Len())
        {
        PrintLine(TEXT("The HiddenWord has %i characters!, Try again!"),HiddenWord.Len());
        return;
        }
    
    //Remove Life
    PrintLine(TEXT("Lost a life!"));
    --Lives;

    if (Lives<=0)
        {
        PrintLine(TEXT("You have no lives left!"));
        PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
        //EndGame();
        return;
        }

    //Show the player Bulls & Cows
    PrintLine(TEXT("Guess again, you have %i lives left"), Lives);
              
            
}

bool UBullCowCartridge::IsIsogram(FString Word) const
{
    //Comparison check matrix.
    for (int32 Index=0; Index<Word.Len(); ++Index)
    {
        for (int32 Comparison=Index+1; Comparison<Word.Len(); ++Comparison)
        {
            if (Word[Index]==Word[Comparison])
            {
                PrintLine(TEXT("The word has to be an Isogram!, the character %c is repeating!!"), Word[Comparison]);
                return false;
            }

        }

    }
return true;
}
