
#include <iostream>
#include "engine/audio/AudioMaster.h"
#include "engine/audio/Source.h"

int main()
{
    AudioMaster audioMaster;
    AudioMaster::setListenerData();

    ALuint buffer = audioMaster.loadSound("res/bounce.wav");
    Source source(glm::vec3{0, 0, 0});

    char c;

    do
    {
        std::cin >> c;

        if (c == 'p')
        {
            source.play(buffer);
        }
    } while(c != 'q');

    return 0;
}
