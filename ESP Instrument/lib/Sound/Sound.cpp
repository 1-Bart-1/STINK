#include "Sound.h"

Sound::Sound() {
}

void Sound::begin(){
    // configure the sampler
    SamplerConfig SConfig = Sampler.defaultConfig();
    // 8192 Hz at GPIO34 (default), 1024 sample (default), AC mode, 4 x sampling to reduce noise  
    SConfig.samplefrequency = 8192;
    SConfig.pin = micPin;
    SConfig.mode = SMODE_AC;
    SConfig.multisample = 4;
    Sampler.setConfig(SConfig);

    // configure the analyzer
    AnalyzerConfig PConfig = Processor.defaultConfig();

    // 8192 Hz, 512 bytes FFT, MAx466 mic = 5.012 mvs, gain approx 75 DbSPL (needs calibration)
    // 13 MFCC's,  6 ranges for Shamzam signatures
    PConfig.samplefreq = 8192;
    PConfig.gain = 75;
    PConfig.sensitivity = 5.012;
    Processor.setConfig(PConfig);

    Sampler.Begin();
}

void Sound::reset(){
    this->sourness = 0;
    this->average_sourness = 0;
}

void Sound::update(){
    this->measureSound();
    this->calculateSourness();
    this->calculateAverages();
}

void Sound::measureSound(){
    // We collect more samples than needed for the FFT signal, because standard Decibel measurement
    // requires a specific duration (there is even even an ISO standard for that)
    //
    Sampler.Collect(Samples, 1024);
    
    decibel_t dB = Processor.decibelSPL(Samples,1024);

    // Yin (Pitch) is a timedomain feature
    float Yin = Processor.getPitch(Samples);

    // Now Make a spectrum by processing the samples. True = to remove DC
    // Then create features, MFCC, Signature, depending on what we need
    // either use the local array, or use the cached data in the class
    //  the audiofeature enums are usd to find the feature in the array
    //
    Processor.doFft(Samples,true);
    float * Features  = Processor.getFeatures();
    float * Mfccs     = Processor.getMfcc();
    signature_t * Signature = Processor.getSignature();

    this->frequency = Features[Fpeakfreq];
    this->volume = dB;
    Serial.printf("dBSpl %d, Pitch %0f, Peakfreq %.2f, Crest %.2f, Rolloff %.2f etc etc\n", 
                dB, Yin, Features[Fpeakfreq], Features[Fcrest], Features[Frolloff]);
}


void Sound::calculateAverages(){
    static int counter = 0;
    average_sourness = (average_sourness * counter + sourness) / (counter + 1);
    average_volume = (average_volume * counter + volume) / (counter + 1);
    counter++;
}

void Sound::calculateSourness() {
    int arraySize = sizeof(frequencies) / sizeof(frequencies[0]);

    float nearest1 = std::numeric_limits<float>::max(); // Initialize with a large value
    float nearest2 = std::numeric_limits<float>::max(); // Initialize with a large value

    for (int i = 0; i < arraySize; i++) {
        float currentDistance = std::abs(frequencies[i] - this->frequency);
        
        if (currentDistance < nearest1) {
            nearest2 = nearest1; // Shift the previous nearest to the second nearest
            nearest1 = currentDistance; // Update the nearest
        } else if (currentDistance < nearest2) {
            nearest2 = currentDistance; // Update the second nearest
        }
    }

    this->sourness = min(nearest1, nearest2) / (nearest1 + nearest2) * 100;
}

float Sound::getAverageSourness(){
    return this->average_sourness;
}

float Sound::getAverageVolume(){
    return this->average_volume;
}

Sound sound;