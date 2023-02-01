
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Orb.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UMaterial;

UCLASS()
class COMPULSORY_1_API AOrb : public AActor
{
	GENERATED_BODY()
	
public:	

	AOrb();

	UPROPERTY(EditAnywhere)
		UMaterial* StartColor;

	UPROPERTY(EditAnywhere)
		UMaterial* Blue;

	UPROPERTY(EditAnywhere)
		UMaterial* Yellow;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;

	virtual void Tick(float DeltaTime) override;

	enum STATE { EMPTY, P1, P2 };

	void Setstate(STATE Instate);

	void SetScale(float Scale);

	STATE Getstate();



protected:

	virtual void BeginPlay() override;

private:
	STATE state = EMPTY;

	void UpdateMaterialFromState();

};
