
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Orb.h"
#include "Tic_Tac_Toe.generated.h"

UCLASS()
class COMPULSORY_1_API ATic_Tac_Toe : public APawn
{
	GENERATED_BODY()

public:
	ATic_Tac_Toe();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
		USpringArmComponent* SpringArm;

	UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AOrb> BP_Orb_Class;

	AOrb* Orb[3][3];
	AOrb* ScoreOrb1;
	AOrb* ScoreOrb2;
	void ChangeColor(int row, int column);

protected:
	virtual void BeginPlay() override;

private:	
	bool Player1 = true;
	bool GameOver = false;
	void Checkstate();
	void Draw();

};
