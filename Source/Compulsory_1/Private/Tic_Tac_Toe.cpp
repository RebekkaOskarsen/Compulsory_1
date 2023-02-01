
#include "Tic_Tac_Toe.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


ATic_Tac_Toe::ATic_Tac_Toe()
{
 	
	PrimaryActorTick.bCanEverTick = true;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Springarm"));
    SpringArm->SetupAttachment(GetRootComponent());

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

    AutoPossessPlayer = EAutoReceiveInput::Player0;

}


void ATic_Tac_Toe::BeginPlay()
{
    SpringArm->TargetArmLength = 2000.f;
    SpringArm->SetRelativeRotation(FRotator(-70.f, 0.f, 0.f));

	Super::BeginPlay();

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            Orb[i][j] = GetWorld()->SpawnActor<AOrb>(BP_Orb_Class, FVector(i * 360, j * 360, 160), FRotator(0, 0, 0));
        }
    }

    ScoreOrb1 = GetWorld()->SpawnActor<AOrb>(BP_Orb_Class, FVector(360, 1200, 150), FRotator(0, 0, 0));
    ScoreOrb2 = GetWorld()->SpawnActor<AOrb>(BP_Orb_Class, FVector(360, 1520, 150), FRotator(0, 0, 0));

}


void ATic_Tac_Toe::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATic_Tac_Toe::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    DECLARE_DELEGATE_TwoParams(ChangeColorForSphere, const int, const int);
    PlayerInputComponent->BindAction<ChangeColorForSphere>("ChangeColor1", IE_Pressed, this, &ATic_Tac_Toe::ChangeColor, 0, 0);
    PlayerInputComponent->BindAction<ChangeColorForSphere>("ChangeColor2", IE_Pressed, this, &ATic_Tac_Toe::ChangeColor, 0, 1);
    PlayerInputComponent->BindAction<ChangeColorForSphere>("ChangeColor3", IE_Pressed, this, &ATic_Tac_Toe::ChangeColor, 0, 2);
    PlayerInputComponent->BindAction<ChangeColorForSphere>("ChangeColor4", IE_Pressed, this, &ATic_Tac_Toe::ChangeColor, 1, 0);
    PlayerInputComponent->BindAction<ChangeColorForSphere>("ChangeColor5", IE_Pressed, this, &ATic_Tac_Toe::ChangeColor, 1, 1);
    PlayerInputComponent->BindAction<ChangeColorForSphere>("ChangeColor6", IE_Pressed, this, &ATic_Tac_Toe::ChangeColor, 1, 2);
    PlayerInputComponent->BindAction<ChangeColorForSphere>("ChangeColor7", IE_Pressed, this, &ATic_Tac_Toe::ChangeColor, 2, 0);
    PlayerInputComponent->BindAction<ChangeColorForSphere>("ChangeColor8", IE_Pressed, this, &ATic_Tac_Toe::ChangeColor, 2, 1);
    PlayerInputComponent->BindAction<ChangeColorForSphere>("ChangeColor9", IE_Pressed, this, &ATic_Tac_Toe::ChangeColor, 2, 2);
}

void ATic_Tac_Toe::ChangeColor(int row, int column)
{
    if (GameOver == false)
    {
        if (Player1)
        {
            Orb[row][column]->Setstate(AOrb::P1);
            Player1 = false;
            Checkstate();
            Draw();
        }
        else
        {
            Orb[row][column]->Setstate(AOrb::P2);
            Player1 = true;
            Checkstate();
            Draw();
        }
    }
}

void ATic_Tac_Toe::Checkstate()
{
    if (Orb[0][0]->Getstate() == Orb[0][1]->Getstate()
        && Orb[0][1]->Getstate() == Orb[0][2]->Getstate() && Orb[0][0]->Getstate() != AOrb::EMPTY)
    {
         ScoreOrb1->Setstate(Orb[0][0]->Getstate());
         ScoreOrb2->Setstate(Orb[0][0]->Getstate());
        GameOver = true;
    }
    else if (Orb[1][0]->Getstate() == Orb[1][1]->Getstate()
        && Orb[1][1]->Getstate() == Orb[1][2]->Getstate() && Orb[1][0]->Getstate() != AOrb::EMPTY)
    {
         ScoreOrb1->Setstate(Orb[1][0]->Getstate());
         ScoreOrb2->Setstate(Orb[1][0]->Getstate());
        GameOver = true;
    }
    else if (Orb[2][0]->Getstate() == Orb[2][1]->Getstate()
        && Orb[2][1]->Getstate() == Orb[2][2]->Getstate() && Orb[2][0]->Getstate() != AOrb::EMPTY)
    {
         ScoreOrb1->Setstate(Orb[2][0]->Getstate());
         ScoreOrb2->Setstate(Orb[2][0]->Getstate());
        GameOver = true;
    }
    else if (Orb[0][0]->Getstate() == Orb[1][0]->Getstate()
        && Orb[1][0]->Getstate() == Orb[2][0]->Getstate() && Orb[0][0]->Getstate() != AOrb::EMPTY)
    {
         ScoreOrb1->Setstate(Orb[0][0]->Getstate());
         ScoreOrb2->Setstate(Orb[0][0]->Getstate());
        GameOver = true;
    }
    else if (Orb[0][1]->Getstate() == Orb[1][1]->Getstate()
        && Orb[1][1]->Getstate() == Orb[2][1]->Getstate() && Orb[0][1]->Getstate() != AOrb::EMPTY)
    {
         ScoreOrb1->Setstate(Orb[0][1]->Getstate());
         ScoreOrb2->Setstate(Orb[0][1]->Getstate());
        GameOver = true;
    }
    else if (Orb[0][2]->Getstate() == Orb[1][2]->Getstate()
        && Orb[1][2]->Getstate() == Orb[2][2]->Getstate() && Orb[0][2]->Getstate() != AOrb::EMPTY)
    {
         ScoreOrb1->Setstate(Orb[0][2]->Getstate());
         ScoreOrb2->Setstate(Orb[0][2]->Getstate());
        GameOver = true;
    }
    else if (Orb[0][0]->Getstate() == Orb[1][1]->Getstate()
        && Orb[1][1]->Getstate() == Orb[2][2]->Getstate() && Orb[0][0]->Getstate() != AOrb::EMPTY)
    {
         ScoreOrb1->Setstate(Orb[0][0]->Getstate());
         ScoreOrb2->Setstate(Orb[0][0]->Getstate());
        GameOver = true;
    }
    else if (Orb[0][2]->Getstate() == Orb[1][1]->Getstate()
        && Orb[1][1]->Getstate() == Orb[2][0]->Getstate() && Orb[0][2]->Getstate() != AOrb::EMPTY)
    {
         ScoreOrb1->Setstate(Orb[0][2]->Getstate());
         ScoreOrb2->Setstate(Orb[0][2]->Getstate());
        GameOver = true;
    }


}
void ATic_Tac_Toe::Draw()
{
    if (Orb[0][0]->Getstate() != AOrb::EMPTY 
        && Orb[0][1]->Getstate() != AOrb::EMPTY 
        && Orb[0][2]->Getstate() != AOrb::EMPTY
        && Orb[1][0]->Getstate() != AOrb::EMPTY 
        && Orb[1][1]->Getstate() != AOrb::EMPTY 
        && Orb[1][2]->Getstate() != AOrb::EMPTY
        && Orb[2][0]->Getstate() != AOrb::EMPTY 
        && Orb[2][1]->Getstate() != AOrb::EMPTY 
        && Orb[2][2]->Getstate() != AOrb::EMPTY)
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(1, 60.f, FColor::Black, FString("DRAW"));
        }
        
        GameOver = true;
    }
}