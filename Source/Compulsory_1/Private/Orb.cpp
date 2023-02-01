
#include "Orb.h"

AOrb::AOrb()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

}


void AOrb::BeginPlay()
{
	Super::BeginPlay();
	
}

void AOrb::Setstate(STATE Instate)
{
	if (state == EMPTY)
	{
		state = Instate;
		UpdateMaterialFromState();
	}
}


void AOrb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOrb::SetScale(float Scale)
{
    SetActorScale3D(FVector(Scale, Scale, Scale));
}

AOrb::STATE AOrb::Getstate()
{
    return state;
}

void AOrb::UpdateMaterialFromState()
{
    Mesh->SetMaterial(0, StartColor);

    if (state == P1)
    {
        Mesh->SetMaterial(0, Blue);
    }
    else if (state == P2)
    {
        Mesh->SetMaterial(0, Yellow);
    }

}

