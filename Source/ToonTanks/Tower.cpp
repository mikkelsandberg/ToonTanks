// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);
  
  // Check to see if the Tank is in range
  if (InFireRange())
  {
    // If in range, rotate Turret toward Tank
    RotateTurret(Tank->GetActorLocation());
  }
}

void ATower::HandleDestruction()
{
  Super::HandleDestruction();

  Destroy();
}

void ATower::BeginPlay()
{
  Super::BeginPlay();

  Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

  GetWorldTimerManager().SetTimer(
      FireRateTimerHandle,
      this,
      &ATower::CheckFireCondition,
      FireRate,
      true);
}

void ATower::CheckFireCondition()
{
  if (Tank == nullptr)
  {
    return;
  }

  if (InFireRange() && Tank->bAlive)
  {
    Fire();
  }
}

bool ATower::InFireRange()
{
  // Find the distance to the Tank
  if (Tank)
  {
    FVector TankLocation = Tank->GetActorLocation();
    float Distance = FVector::Dist(GetActorLocation(), TankLocation);

    return Distance <= FireRange;
  }

  return false;
}
