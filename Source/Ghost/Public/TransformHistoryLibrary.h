#pragma once
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TransformHistoryLibrary.generated.h"

class UTransformHistoryComponent;

UCLASS()
class GHOST_API UTransformHistoryLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    /** Adds a TransformHistoryComponent to any Actor at runtime. */
    UFUNCTION(BlueprintCallable, Category="Transform Ghost", meta=(WorldContext="WorldContextObject"))
    static UTransformHistoryComponent* AddTransformHistoryComponent(AActor* Target);
};
