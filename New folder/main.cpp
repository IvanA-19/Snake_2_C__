#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

int main()
{

    sf::Music music;
    sf::SoundBuffer buffer;

    buffer.loadFromFile("Sounds/1.wav");

    sf::Sound sound;
    sound.setBuffer(buffer);
    int i = 0;
    while(i != 5) {
        sound.play();
        sf::sleep(sf::seconds(3));
        i++;
    }

    //system("pause");


    return 0;
}
