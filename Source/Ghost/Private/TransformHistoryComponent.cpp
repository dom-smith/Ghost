#include "TransformHistoryComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

UTransformHistoryComponent::UTransformHistoryComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    SetComponentTickEnabled(true);
}

void UTransformHistoryComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UTransformHistoryComponent::StartRecording()
{
    ClearHistory();
    bIsRecording = true;
    TimeAccumulator = 0.f;
    RecordedLength  = 0.f;
    RecordSample(0.f); // first sample
}

void UTransformHistoryComponent::StopRecording()
{
    bIsRecording = false;
}

void UTransformHistoryComponent::ClearHistory()
{
    Samples.Empty();
    RecordedLength = 0.f;
}

void UTransformHistoryComponent::PlayBack(bool bLoop /*=false*/, float OverrideDuration /*=0.f*/)
{
    if (Samples.Num() < 2) return;

    bIsPlaying    = true;
    PlaybackTime  = 0.f;
    bLooping      = bLoop;
    PlayDuration  = (OverrideDuration > 0.f) ? OverrideDuration : RecordedLength;
}

void UTransformHistoryComponent::RecordSample(float WorldTime)
{
    FRecordedTransform R;
    R.TimeStamp = WorldTime;
    R.Transform = GetOwner()->GetActorTransform();
    Samples.Add(R);
}

void UTransformHistoryComponent::ApplyPlayback(float Delta)
{
    if (!bIsPlaying || Samples.Num() < 2) return;

    PlaybackTime += Delta;
    float Alpha = PlaybackTime / PlayDuration;

    if (Alpha >= 1.f)
    {
        if (bLooping)
        {
            PlaybackTime = FMath::Fmod(PlaybackTime, PlayDuration);
            Alpha = PlaybackTime / PlayDuration;
        }
        else
        {
            bIsPlaying = false;
            return;
        }
    }

    // Find segment
    float TargetTime = Alpha * RecordedLength;
    int32 Index = 0;
    while (Index + 1 < Samples.Num() && Samples[Index + 1].TimeStamp < TargetTime)
        ++Index;

    const FRecordedTransform& A = Samples[Index];
    const FRecordedTransform& B = Samples[FMath::Min(Index + 1, Samples.Num() - 1)];

    float SegmentAlpha = (TargetTime - A.TimeStamp) / (B.TimeStamp - A.TimeStamp);
    FTransform LerpXform;
    LerpXform.Blend(A.Transform, B.Transform, SegmentAlpha);

    GetOwner()->SetActorTransform(LerpXform);
}

void UTransformHistoryComponent::TickComponent(float Delta, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(Delta, TickType, ThisTickFunction);

    if (bIsRecording)
    {
        TimeAccumulator += Delta;
        RecordedLength  += Delta;

        if (SamplingInterval <= 0.f || TimeAccumulator >= SamplingInterval)
        {
            TimeAccumulator = 0.f;
            RecordSample(RecordedLength);
        }
    }

    ApplyPlayback(Delta);
}
