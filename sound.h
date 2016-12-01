#include "game.h"

// Initialize the sound module
void Sound_Init(void);

// Set which sound should be played - only call for new sounds
void Set_Sound_Effect(Sound option);

// Play the currently set sound effect
// Stops the currently playing sound effect if there is one
void Play_Sound_Effect(void);

// Start playing the background music from the beginning
void Play_Background_Music(void);

// Stop playing the background music and reset the timers
void Stop_Background_Music(void);
