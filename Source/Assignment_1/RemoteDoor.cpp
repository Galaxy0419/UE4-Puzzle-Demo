#include "RemoteDoor.h"

void ARemoteDoor::BeginPlay()
{
	Super::BeginPlay();

	SwitchToListen->OnSwitchToggle.AddUObject(this, &ARemoteDoor::OnSwitchToggle);
}

void ARemoteDoor::OnSwitchToggle()
{
	Open();
}
