// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"



void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    
    
    SetupGame();
  
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
     //if game is over then do ClearScreen and Setup the game
    if (bGameOver)
    {
                  
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
    ClearScreen();
    PrintLine(TEXT("Welcome to Bulls and Cows Game!!"));
    PrintLine(TEXT("Guess the  %i letter isometric word!"), HiddenWord.Len());
    PrintLine(TEXT("You've %i lives."),Lives);
    PrintLine(TEXT("Type in your guess.\nPress enter to continue..."));

    //const TCHAR HW[]=TEXT ("cake");
    //PrintLine(TEXT("The character 1 of the hidden word is: %c"), HW[0]);

     PrintLine(TEXT("The Random number is: %i"),FMath::RandRange(0 , 10));
   
    
    //PrintLine((TEXT("The HiddenWord is: %s"), *HiddenWord)); //Debug Line
   PrintLine(TEXT("The number of possible words is: %i"), Words.Num()); 
   PrintLine(TEXT("The number of valid words is: %i"),GetValidWords(Words).Num());
        
}

void UBullCowCartridge::EndGame()
{
    bGameOver=true;

    PrintLine(TEXT("*************** GAME OVER ************"));
    PrintLine(TEXT("Press enter to play again..."));
    
    
    
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{

    if (HiddenWord == Guess)
        {
            bGameOver=true;
            PrintLine(TEXT("******** You have won!!********"));
            PrintLine(TEXT("Press enter to play again..."));
            return;
        }
  //Check If is  Isogram
     if (!IsIsogram(Guess))
        {
        PrintLine(TEXT("The word has to be an Isogram!"));
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
        EndGame();
        return;
        }

    //Show the player Bulls & Cows
    PrintLine(TEXT("Guess again, you have %i lives left"), Lives);
              
            
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    //Comparison check matrix.
    for (int32 Index=0; Index<Word.Len(); Index++)
    {
        for (int32 Comparison=Index+1; Comparison<Word.Len(); Comparison++)
        {
            if (Word[Index]==Word[Comparison])
            {
                
                return false;
            }

        }

    }
return true;
}


TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray <FString> ValidWords;
    
       for (FString WordCheck : WordList)
    {
        if (WordCheck.Len()>=4 && WordCheck.Len()<=8 && IsIsogram(WordCheck) )
        {
            ValidWords.Emplace(WordCheck);
        }
    } 
    return ValidWords;
    
    /* 
    for (int32 Index=0; Index<WordList.Num(); Index++)
    {
        if (WordList[Index].Len()>=4 && WordList[Index].Len()<=8 && IsIsogram(Words[Index])) //&& IsIsogram (CheckingWord[Index]))
        {
            ValidWords.Emplace(WordList[Index]);
        }
    } 
    return ValidWords;*/
}