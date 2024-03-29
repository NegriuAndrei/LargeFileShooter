// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Menu.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERSESSIONS_API UMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void MenuSetup(int32 NumberOfPublicConnection = 4, FString TypeOfMatch = FString(TEXT("FreeForAll")), FString LobbyPath= FString(TEXT("/Game/ThirdPerson/Maps/Lobby")));

protected:
	virtual bool Initialize() override;
	virtual void NativeDestruct() override;

	//
	// Callbacks for the custom delegates on the multiplayerSessionSubsystem
	//
	UFUNCTION()
	void OnCreateSession(bool bWasSuccessful);
	void OnFindSession(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful);
	void OnJoinSession(EOnJoinSessionCompleteResult::Type Result);
	UFUNCTION()
	void OnDestroySession(bool bWasSuccessful);
	UFUNCTION()
	void OnStartSession(bool bWasSuccessful);

private:
	UPROPERTY(meta= (BindWidget)) // asa facem link catre butonul declarat in widget
	class UButton* HostButton; // !!! trebuie sa aiba exact aceleasi nume !!!

	UPROPERTY(meta= (BindWidget))
	UButton* JoinButton;

	UFUNCTION()
	void HostButtonClicked();

	UFUNCTION()
	void JoinButtonClicked();

	void MenuTearDown();


	// Subsystem designed to handle all Online Session functionality
	class UMultiplayerSessionsSubsystem* MultiplayerSessionsSubsystem;
	
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "ture"))
	int32 NumPublicConnections{4};
	
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "ture"))
	FString MatchType{TEXT("FreeForAll")};
	FString PathToLobby{TEXT("")};
};
