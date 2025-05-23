#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TransformHistoryComponent.generated.h"

USTRUCT(BlueprintType)
struct FRecordedTransform
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    float TimeStamp = 0.f;

    UPROPERTY(BlueprintReadOnly)
    FTransform Transform;
};

UCLASS(meta=(BlueprintSpawnableComponent))
class GHOST_API UTransformHistoryComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UTransformHistoryComponent();

    /** Seconds between samples (0 == every tick). */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Transform Ghost")
    float SamplingInterval = 0.05f;

    /** Start capturing this actor’s transform. */
    UFUNCTION(BlueprintCallable, Category="Transform Ghost")
    void StartRecording();

    /** Stop capture and keep samples. */
    UFUNCTION(BlueprintCallable, Category="Transform Ghost")
    void StopRecording();

    /** Erase stored data. */
    UFUNCTION(BlueprintCallable, Category="Transform Ghost")
    void ClearHistory();

    /** Playback the path. If Duration <= 0, use original recorded duration. */
    UFUNCTION(BlueprintCallable, Category="Transform Ghost")
    void PlayBack(bool bLoop = false, float OverrideDuration = 0.f);

    /** Returns total recorded time span. */
    UFUNCTION(BlueprintPure, Category="Transform Ghost")
    float GetRecordedLength() const { return RecordedLength; }

    /** The array of samples (read‑only). */
    UPROPERTY(BlueprintReadOnly, Category="Transform Ghost")
    TArray<FRecordedTransform> Samples;

protected:
    virtual void TickComponent(float Delta, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    virtual void BeginPlay() override;

private:
    bool bIsRecording = false;
    bool bIsPlaying   = false;
    bool bLooping     = false;
    float PlayDuration = 0.f;
    float RecordedLength = 0.f;
    float TimeAccumulator = 0.f;
    float PlaybackTime    = 0.f;

    void RecordSample(float WorldTime);
    void ApplyPlayback(float Delta);
};
