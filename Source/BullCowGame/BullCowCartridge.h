// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

struct FBullCowCount
{
	int32 Bulls=0;
	int32 Cows=0;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	void SetupGame();
	void EndGame();
	void ProcessGuess(const FString& Guess);
	bool IsIsogram(const FString& Word) const;
	TArray<FString> GetValidWords(const TArray<FString>& WordList) const;//Take a list of Words (defined in HiddenWordList.h) and extract isogram words.
	
	
	FBullCowCount GetBullCows(const FString& Guess) const;


	// Your declarations go below!
	private:
	FString HiddenWord;
	int32 Lives;
	bool bGameOver;
	TArray<FString> Isograms;//Isograms filtered from Words variable defined in HiddenWorldList.h
	TArray<FString> Words;// Video 69-> Changing  HiddenworldList.h to a TXT file to increase the speed.
	
};
