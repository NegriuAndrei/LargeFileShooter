// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blaster/HUD/BlasterHUD.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

#define TRACE_LENGHT  80000.f


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLASTER_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCombatComponent();
	friend class ABlasterCharacter;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	// Adaugam clasa Blaster Character ca si clasa prietena clasei pentru a putea folosi functiile din ea
	// II da acces la tot cat si la private si protected

	void EquipWeapon(class AWeapon* WeaponToEquip);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void SetAiming(bool bIsAiming);

	UFUNCTION(Server, Reliable)
	void ServerSetAiming(bool bIsAiming);

	UFUNCTION()
	void OnRep_EquippedWeapon();
	void Fire();

	void FireButtonPressed(bool bPressed);

	UFUNCTION(Server, Reliable)
	void ServerFire(const FVector_NetQuantize& TraceHitTarget);

	//NetMulticast apelat de pe server functioneaza pe server si pe toti clientii, dar apelat de pe client merge doar pe acel client
	UFUNCTION(NetMulticast, Reliable)
	void MulticastFire(const FVector_NetQuantize& TraceHitTarget);

	void TraceUnderCrosshairs(FHitResult& TraceHitResult);

	void SetHUDCrosshairs(float DeltaTime);
private:
	class ABlasterCharacter* Character;
	class ABlasterPlayerController* Controller;
	class ABlasterHUD* HUD;
	
	UPROPERTY(ReplicatedUsing = OnRep_EquippedWeapon)
	 AWeapon* EquippedWeapon;
	
	UPROPERTY(Replicated)
	bool bAiming;

	UPROPERTY(EditAnywhere)
	float BaseWalkSpeed;

	UPROPERTY(EditAnywhere)
	float AimWalkSpeed;
	
	bool bFireButtonPressed;

/**
 *	HUD and Crosshairs
 */
	float CrosshairVelocityFactor;
	float CrosshairInAirFactor;
	float CrosshairAimFactor;
	float CrosshairShootingFactor;

	FVector HitTarget;

	FHUDPackage HUDPackage;

	/**
	 *	 Aiming and FOV
	 */

	//	FOV when not aiming, set to the camera`s base FOV in BeginPlay 
	float DefaultFOV;

	UPROPERTY(EditAnywhere, Category= Combat)
	float ZoomedFOV = 30.f;

	float CurrentFOV;

	UPROPERTY(EditAnywhere, Category= Combat)
	float ZoomInterpSpeed = 20.f;

	void InterpFOV(float DeltaTime);


	/**
	 * Automatic Fire
	 */

	FTimerHandle FireTimer;

	bool bCanFire = true;
	
	void StartFireTimer();
	void FireTimerFinished();
	
public:	

	
};