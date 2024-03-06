// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "GameFramework/GameState.h"
#include "MultiplayerSessionsSubsystem.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();

	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		UMultiplayerSessionsSubsystem* Subsystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();
		check(Subsystem);
		if (NumberOfPlayers == Subsystem->DesiredNumPublicConections)
		{
			UWorld* World = GetWorld();
			if (World)
			{
				bUseSeamlessTravel = true;

				FString MatchType = Subsystem->DesiredMatchType;
				if(MatchType == "FreeForAll")
				{
					World->ServerTravel(FString("/Game/Maps/Level1?listen"));
				}
				else if(MatchType == "Teams")
				{
					World->ServerTravel(FString("/Game/Maps/Level2?listen"));
				}
				else if(MatchType == "CaptureTheFlag")
				{
					World->ServerTravel(FString("/Game/Maps/Level3?listen"));
				}
			}
		}
	}
}
