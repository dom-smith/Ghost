#include "TransformHistoryLibrary.h"
#include "TransformHistoryComponent.h"
#include "GameFramework/Actor.h"

UTransformHistoryComponent* UTransformHistoryLibrary::AddTransformHistoryComponent(AActor* Target)
{
    if (!Target) return nullptr;
    return Cast<UTransformHistoryComponent>(Target->AddComponentByClass(UTransformHistoryComponent::StaticClass(), false, FTransform::Identity, false));
}
