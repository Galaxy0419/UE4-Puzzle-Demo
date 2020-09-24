#pragma once

#include "SimpleDoor.h"
#include "RemoteSwitch.h"
#include "RemoteDoor.generated.h"

UCLASS()
class ASSIGNMENT_API ARemoteDoor final : public ASimpleDoor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
	ARemoteSwitch *SwitchToListen;

public:
	void BeginPlay() override;
};
