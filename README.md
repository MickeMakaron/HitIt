# HitIt
Top-down 2D game where the goal is to NOT hit the music.


##Description
In HitIt you control a character in musical danger. Music notes are literally descending upon you and it is up to you to hit it hard (without hitting the notes, of course).

HitIt uses MIDI files, which means that you can play against your favourite songs if you find MIDI versions of them. Simply put them in the "tracks" folder and they will show up in the track list in-game. 

######Note: Due to limitations caused by the MidiFile library, some MIDI tracks simply do not work for whatever reason.

###I just want to play the game
If you just want to download a copy, get it at [HitIt's web page](http://mikael.hernvall.com/hitit).

###I want to compile it myself
HitIt depends on the [SFML-2.1](http://www.sfml-dev.org/download/sfml/2.1/) and the [MidiFile](http://midifile.sapp.org/) libraries. These libraries are not included in this repository. So, to compile the game yourself you must first get these libraries. SFML-2.1 offers pre-built libraries, whereas MidiFile does not. 

If you are having trouble building the MidiFile library (which I had), you can download the copy I managed to build and used when making the game [here](http://mikael.hernvall.com/hitit/midifile). It is not certain it will work in your environment, though, so cross your fingers.

####Search directories
The following are the necessary search directories for your compiler to compile the game with the libraries.

#####Compilation
1. The "src" directory in the HitIt repository.
2. The "incl" directory in the HitIt repository.
3. The "include" directory in the SFML-2.1 package.
4. The "include" directory in the MidiFile package.

#####Linking
1. The "bin" directory in the SFML-2.1 package.
2. The "lib" directory in the SFML-2.1 package.
3. Whatever directory the MidiFile library was built to.

####Linking
Link to SFML-2.1's sfml-graphics, sfml-window, sfml-system and sfml-audio in that exact order. Also link to openal32.

Link to the MidiFile library file.

###Good luck!
