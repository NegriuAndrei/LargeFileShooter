// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileWeapon.h"
#include "Projectile.h"
#include "Engine/SkeletalMeshSocket.h"

void AProjectileWeapon::Fire(const FVector& HitTarget)
{
	Super::Fire(HitTarget);

	//verificam sa nu se poata intampla asta doar pe server pentru a preveni trisarea, si oricum se face replicarea 
if(!HasAuthority()) return;
	
	APawn* InstigatorPawn = Cast<APawn>(GetOwner());
	
	const USkeletalMeshSocket* MuzzleFlashSocket= GetWeaponMesh()->GetSocketByName(FName("MuzzleFlash"));
	
	if(MuzzleFlashSocket)
	{
		FTransform SocketTransform =  MuzzleFlashSocket->GetSocketTransform(GetWeaponMesh());
		// From MuzzleFlash socket to hit location from TraceUnderCrosshair
		FVector ToTarget = HitTarget - SocketTransform.GetLocation();
		FRotator TargetRotation = ToTarget.Rotation();
		
		if(ProjectileClass && InstigatorPawn)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = GetOwner(); // apelam ownerul armei care sa fie si ownerul glontului
			SpawnParams.Instigator = InstigatorPawn;
			UWorld* World = GetWorld();
			if(World)
			{
				World->SpawnActor<AProjectile>(
					ProjectileClass,
					SocketTransform.GetLocation(),
					TargetRotation,
					SpawnParams					
				);
			}
		}
	
	}
	
}
