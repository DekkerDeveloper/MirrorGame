#include "MirrorPickUpComponent.h"

UMirrorPickUpComponent::UMirrorPickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;
}

void UMirrorPickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UMirrorPickUpComponent::OnSphereBeginOverlap);
}

void UMirrorPickUpComponent::OnSphereBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	AMirrorCharacter* Character = Cast<AMirrorCharacter>(OtherActor);
	if(Character)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
