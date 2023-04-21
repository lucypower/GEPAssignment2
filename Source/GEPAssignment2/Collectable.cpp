#include "Collectable.h"

#include "Components/SphereComponent.h"


ACollectable::ACollectable()
{
	m_collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent = m_collision;
}

void ACollectable::BroadcastCollected(AController* causer)
{
	OnCollected.Broadcast(this, causer);
	Destroy();
}

