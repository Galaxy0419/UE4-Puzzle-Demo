#include "RemoteDoor.h"

void ARemoteDoor::BeginPlay()
{
	Super::BeginPlay();

	SwitchToListen->OnSwitchToggle.AddUObject(this, &ASimpleDoor::Open);
}
