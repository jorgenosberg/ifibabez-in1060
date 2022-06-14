#include <VaxBuzzer.h>
#include <pitches.h>


/**
 * @brief Oppretter et nytt VaxBuzzer-objekt paa gitt pin.
 * Definerer ogsaa notene i melodien og deres varighet.
 * @param buzzerPin GPIO-pinen buzzeren er koblet til
 */
VaxBuzzer::VaxBuzzer(int buzzerPin)
{
    _buzzerPin = buzzerPin; // assigner buzzerPinen
    _playing = false;

    unsigned long previousMillis = 0; // variabel for non-blocking pauser
}

/**
 * @brief Spiller av en standardtone fra pitches.h (C4) med varighet paa 500 ms.
 */
void VaxBuzzer::playTone()
{
    unsigned long startTime = millis();
    tone(_buzzerPin, NOTE_C4, 500);
    unsigned long endTime = millis();
   
    while (endTime - startTime < 500) {
        setPlaying(true);
        endTime = millis();
    }

    stopTone();

    setPlaying(false);
}

/**
 * @brief Spiller av en gitt tone med en gitt varighet.
 * @param frequency : tonen fra pithces.h som skal spilles av
 * @param duration : varighet i millisekunder
 */
void VaxBuzzer::playTone(unsigned int frequency, unsigned long duration)
{
    unsigned long startTime = millis();
    tone(_buzzerPin, frequency, duration);
    unsigned long endTime = millis();
   
    while (endTime - startTime < 500) {
        setPlaying(true);
        endTime = millis();
    }

    stopTone();

    setPlaying(false);
}

/**
 * @brief Kaller noTone() paa buzzeren for aa stoppe tonen.
 */
void VaxBuzzer::stopTone() 
{
    noTone(_buzzerPin);
}

/**
 * @brief Endrer verdien av playing.
 * @param value : ny verdi
 */
void VaxBuzzer::setPlaying(bool value)
{
    _playing = value;
}

/**
 * @brief Sjekker om buzzeren spiller en tone.
 * @return true : hvis tone spilles
 * @return false : hvis buzzeren er av
 */
bool VaxBuzzer::isPlaying()
{
    return _playing;
}

/**
 * @brief Spiller en melodi med non-blocking timing.
 * Inspirert av Arduinos eget "blink without delay"-eksempel.
 * OBS - er ikke non-blocking naar den kalles fra utenfor seg 
 * selv. I saa fall blokkerer den traaden til metoden returnerer.
 */
void VaxBuzzer::playMelody(int* melody, int* noteDurations)
{
    int pauseBetweenNotes;
    unsigned long currentMillis = millis();

    for (int thisNote = 0; thisNote < sizeof(melody); thisNote++) {
        
        if (currentMillis - previousMillis >= pauseBetweenNotes) {
            previousMillis = currentMillis;
            
            int noteDuration = 1000 / noteDurations[thisNote];

            // spill tonen i gitt varighet
            tone(_buzzerPin, melody[thisNote], noteDuration);

            // regne ut pausen mellom tonene - proever her med self + 30%
            pauseBetweenNotes = noteDuration * 1.30;

            // stoppe tonen som blir spilt av
            stopTone();
        }
    }
}

/**
 * @brief Bruker playMelody() for aa spille av en enkel
 * treklang som startup-lyd.
 */
void VaxBuzzer::playStartupSound()
{
    int melody[3] = { // definerer melodien
        NOTE_C4, NOTE_E4, NOTE_G4,
        };

    int noteDurations[3] = { // og meloditonenes varighet
        4, 4, 4,
    };

    playMelody(melody, noteDurations);
}

/**
 * @brief Bruker playMelody() for aa spill av en invertert
 * treklang som en shutdown-lyd. Kan brukes hvis boksen skal slaas
 * av.
 */
void VaxBuzzer::playShutdownSound()
{
    int melody[3] = { // definerer melodien
        NOTE_G4, NOTE_E4, NOTE_C4,
        };

    int noteDurations[3] = { // og meloditonenes varighet
        4, 4, 4,
    };

    playMelody(melody, noteDurations);
}

