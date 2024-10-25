#include "VoiceCaller.h"
#include "MaleVoice.h"

// Sets default values
AVoiceCaller::AVoiceCaller()
{
    // Constructor remains empty for initialization logic
}

// Called when the game starts or when spawned
void AVoiceCaller::BeginPlay()
{
    //Super::BeginPlay();

    // Spawn an instance of AMaleVoice
    if (!MaleVoiceInstance)
    {
        FActorSpawnParameters SpawnParams;
        MaleVoiceInstance = GetWorld()->SpawnActor<AMaleVoice>(AMaleVoice::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

        if (MaleVoiceInstance)
        {
            // You might want to initialize the voice here if needed
        }
    }
}

// Function to speak the provided text
void AVoiceCaller::SpeakText(const FString& Text)
{
    if (MaleVoiceInstance)
    {
        // Set the input for MaleVoice and trigger speech
        MaleVoiceInstance->SetSpeech(Text); // Call SetSpeech with the text
    }
}
