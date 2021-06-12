// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"


void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    //Copy the TXT file location into a FString called WordListPath
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    
    //Load the TXT file located in "WordListPath" into TArray<FString> Words.
    //We'll need to add the Wordlists Directory to the list of Additional Non-Asset Directories
    //to package in Project settings under Packaging.
    FFileHelper::LoadFileToStringArray(Words, *WordListPath);
    
    //Creating the Isogram TArray at the begining using GetValidWords function which works as a filter
    Isograms = GetValidWords(Words);

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
    //Selecting a random Isogram word
    HiddenWord = Isograms[FMath::RandRange(0,Isograms.Num()-1)];
        
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
    PrintLine((TEXT("The HiddenWord is: %s"), *HiddenWord)); //Debug Line
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

  
    //Checking if there's Bulls and/or cows
    FBullCowCount Score=GetBullCows(Guess);

    PrintLine(TEXT("You have %i Bulls and %i Cows"),Score.Bulls,Score.Cows);

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

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{

    FBullCowCount Count;

//Checking for each character of Guess if is same as HiddenWord
for (int32 GuessIndex=0; GuessIndex < Guess.Len(); GuessIndex++)
    {
     
     
        if (Guess[GuessIndex]==HiddenWord[GuessIndex])
        {
            Count.Bulls++;
            continue;
        }
        for(int32 HiddenIndex=0;HiddenIndex<HiddenWord.Len(); HiddenIndex++)
            {
                if(Guess[GuessIndex]==HiddenWord[HiddenIndex])
                {
                    Count.Cows++;
                    break;
                }
            }
    }
    return Count;
}