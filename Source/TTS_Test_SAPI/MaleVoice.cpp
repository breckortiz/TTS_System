#include "MaleVoice.h"

AMaleVoice::AMaleVoice()
{
    // Initialize BasicVoiceComponent
    BasicVoiceComponent = CreateDefaultSubobject<UBasicVoice>(TEXT("BasicVoiceComponent"));
}

void AMaleVoice::SetSpeech(const FString& Text, const FString& FileName)
{
    BasicVoiceComponent->SetSpeech(Text, FileName); // Call SetSpeech on the BasicVoice component
}

void AMaleVoice::OutSpeech()
{
    BasicVoiceComponent->OutSpeech(); // Call OutSpeech on the BasicVoice component
}

void AMaleVoice::ByeSpeech()
{
    BasicVoiceComponent->ByeSpeech(); // Call ByeSpeech on the BasicVoice component
}
