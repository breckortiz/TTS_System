#include "BasicVoice.h"
#include "HAL/Runnable.h"
#include "HAL/RunnableThread.h"
#include <sphelper.h>  // For SpFileStream

class FVoiceRunnable : public FRunnable
{
public:
    FString TextToSpeak;
    UBasicVoice* VoiceInstance;

    FVoiceRunnable(UBasicVoice* InVoiceInstance, const FString& InText)
        : VoiceInstance(InVoiceInstance), TextToSpeak(InText)
    {
    }

    virtual uint32 Run() override
    {
        if (VoiceInstance)
        {
            VoiceInstance->SpeakInThread(TextToSpeak);
        }
        return 0;
    }
    virtual void Exit() override
    {
        // Optional: If any cleanup is needed after the thread finishes
    }
};

UBasicVoice::UBasicVoice()
{
    pVoice = nullptr;
}

void UBasicVoice::SetSpeech(const FString& Text)
{
    FVoiceRunnable* VoiceRunnable = new FVoiceRunnable(this, Text);
    FRunnableThread* Thread = FRunnableThread::Create(VoiceRunnable, TEXT("VoiceRunnableThread"));
}

// Separate function to handle speech synthesis in the thread
void UBasicVoice::SpeakInThread(const FString& Text)
{
    // Initialize COM in this thread
    HRESULT hr_ = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    if (FAILED(hr_))
    {
        UE_LOG(LogTemp, Error, TEXT("ERROR: Failed to initialize COM in thread"));
        return;  // Handle initialization failure
    }

    // Create a local instance of pVoice inside the thread
    ISpVoice* LocalVoice = nullptr;
    hr_ = CoCreateInstance(CLSID_SpVoice, nullptr, CLSCTX_ALL, IID_ISpVoice, (void**)&LocalVoice);
    if (FAILED(hr_) || !LocalVoice)
    {
        UE_LOG(LogTemp, Error, TEXT("ERROR: Failed to create voice instance in thread"));
        CoUninitialize();
        return;
    }

    // Create a file stream for the .wav output
    CComPtr<ISpStream> spStream;
    CSpStreamFormat wavFormat;
    wavFormat.AssignFormat(SPSF_22kHz16BitMono);  // Example format

    FString FilePath = FPaths::ProjectSavedDir() + TEXT("GeneratedAudio/") + TEXT("VoiceOutput.wav");  // Save location
    hr_ = SPBindToFile(*FilePath, SPFM_CREATE_ALWAYS, &spStream, &wavFormat.FormatId(), wavFormat.WaveFormatExPtr());

    if (FAILED(hr_))
    {
        UE_LOG(LogTemp, Error, TEXT("ERROR: Failed to bind to output .wav file"));
        LocalVoice->Release();
        CoUninitialize();
        return;
    }

    // Set the output stream to the file stream
    LocalVoice->SetOutput(spStream, TRUE);

    // Ensure the input text is valid
    if (Text.IsEmpty())
    {
        UE_LOG(LogTemp, Warning, TEXT("WARNING: Input text is empty"));
        LocalVoice->Release();
        CoUninitialize();
        return;
    }

    // Convert FString to LPCWSTR for use with SAPI
    LPCWSTR TEMPlocalInput = *Text;

    // Speak text to the .wav file
    hr_ = LocalVoice->Speak(TEMPlocalInput, SPF_DEFAULT, NULL);
    if (FAILED(hr_))
    {
        UE_LOG(LogTemp, Error, TEXT("ERROR: Failed to speak text"));
    }

    // Release and clean up resources
    spStream->Close();
    LocalVoice->Release();
    CoUninitialize();
}

void UBasicVoice::OutSpeech()
{
    if (pVoice)
    {
        pVoice->Release();
        pVoice = nullptr;
    }
}

void UBasicVoice::initVoice()
{
    hr = CoInitialize(nullptr);
    if (SUCCEEDED(hr))
    {
        hr = CoCreateInstance(CLSID_SpVoice, nullptr, CLSCTX_ALL, IID_ISpVoice, (void**)&pVoice);
        if (FAILED(hr))
        {
            // Handle failure (e.g., log error, set pVoice to nullptr)
            pVoice = nullptr;
        }
    }
}

void UBasicVoice::ByeSpeech()
{
    // This is a pure virtual function, so it can remain empty here, and must be overridden in child classes.
}

UBasicVoice::~UBasicVoice()
{
    if (pVoice)
    {
        pVoice->Release();
        pVoice = nullptr;
    }

    CoUninitialize();
}
