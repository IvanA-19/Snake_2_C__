#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int score = 10;
sf::Font font_menu;
vector <sf::Text> text_menu_items;
vector <string> menu_items = {"Start new game", "Settings", "Quit", "SNAKE"};
vector <string> lose_menu_items{"Your score: " + to_string(score), "Restart", "Exit to main menu", "GAME OVER"};
vector <string> settings_menu_items{"Field color", "Snake skin", "Walls", "Difficulty level", "Back to main menu", "Game settings"};

constexpr auto MENU_ITEM_RESTART = "Start new game";
constexpr auto MENU_ITEM_RESUME = "Resume the game";
constexpr auto MENU_ITEM_EXIT = "Exit the game";
constexpr auto MENU_ITEM_SETTINGS = "Settings";
constexpr auto MENU_ITEM_BACK = "Back to main menu";
constexpr auto MENU_ITEM_FIELD = "Field color";
constexpr auto MENU_ITEM_SKIN = "Snake skin";
constexpr auto MENU_ITEM_WALL = "Walls";
constexpr auto MENU_ITEM_DIFFICULTY = "Difficulty level";
constexpr auto MENU_MAIN = 0;
constexpr auto MENU_SETTINGS = 1;

const int cell_size = 32;
int window_height = 25;
int window_width = 35;
bool pause = false;
int color = 0;
int lose_color = 1;
int menu_type = 2;
int settings_color = 0;

void set_fonts()
{
    font_menu.loadFromFile("fonts/BigOldBoldy-dEjR.ttf");
    switch (menu_type) {
        case 0:
            for (int i = 0; i < menu_items.size() - 1; i++) {
                text_menu_items.emplace_back(sf::Text());
                text_menu_items.back().setString(menu_items.at(i));
                text_menu_items.back().setFont(font_menu);
                text_menu_items.back().setCharacterSize(40);
            }
            text_menu_items.emplace_back(sf::Text());
            text_menu_items.back().setString(menu_items.at(3));
            text_menu_items.back().setFont(font_menu);
            text_menu_items.back().setCharacterSize(70);
            break;
        case 1:
            for (int i = 0; i < lose_menu_items.size(); i++) {
                text_menu_items.emplace_back(sf::Text());
                text_menu_items.back().setString(lose_menu_items.at(i));
                text_menu_items.back().setFont(font_menu);
                text_menu_items.back().setCharacterSize(40);
            }
            text_menu_items.emplace_back(sf::Text());
            text_menu_items.back().setString(lose_menu_items.at(3));
            text_menu_items.back().setFont(font_menu);
            text_menu_items.back().setCharacterSize(70);
            break;
        case 2:
            for (int i = 0; i < settings_menu_items.size() - 1; i++) {
                text_menu_items.emplace_back(sf::Text());
                text_menu_items.back().setString(settings_menu_items.at(i));
                text_menu_items.back().setFont(font_menu);
                text_menu_items.back().setCharacterSize(40);
            }
            text_menu_items.emplace_back(sf::Text());
            text_menu_items.back().setString(settings_menu_items.at(5));
            text_menu_items.back().setFont(font_menu);
            text_menu_items.back().setCharacterSize(70);
            break;
    }
}

void menu_control(sf::RenderWindow& window) //выбор цвета фона
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed){
            window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Enter:
                    window.close();
                    break;
                case sf::Keyboard::Down:
                    color++;
                    if(color == 3){
                        color = 0;
                    }
                    pause = true;
                    break;
                case sf::Keyboard::Up:
                    color--;
                    if(color == -1){
                        color = 2;
                    }
                    pause = true;
                    break;
            }
        }
    }
}

void lose_menu_control(sf::RenderWindow &window)
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed){
            window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Enter:
                    window.close();
                    break;
                case sf::Keyboard::Down:
                    lose_color++;
                    if(lose_color == 3){
                        lose_color = 1;
                    }
                    pause = true;
                    break;
                case sf::Keyboard::Up:
                    lose_color--;
                    if(lose_color == 0){
                        lose_color = 2;
                    }
                    pause = true;
                    break;
            }
        }
    }
}

void settings_menu_control(sf::RenderWindow &window)
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed){
            window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Enter:
                    window.close();
                    break;
                case sf::Keyboard::Down:
                    settings_color++;
                    if(settings_color == 5){
                        settings_color = 0;
                    }
                    pause = true;
                    break;
                case sf::Keyboard::Up:
                    settings_color--;
                    if(settings_color == -1){
                        settings_color = 4;
                    }
                    pause = true;
                    break;
            }
        }
    }
}

void draw_main_menu(sf::RenderWindow& window)
{
    const float menu_item_interval = 20;

    float menu_item_max_width = 0;
    float current_menu_item_offset_y = 0;

    const float menu_width = 554;//menu_item_max_width;
    float menu_height = 120;//current_menu_item_offset_y;

    const float menu_position_x = (float(window_width * cell_size) - menu_width) / 2;
    float menu_position_y = (float(window_height * cell_size) - menu_height) / 2;
    switch(menu_type){
        case 0:
            text_menu_items.at(color).setFillColor(sf::Color(255, 255,0));
            text_menu_items.at(3).setFillColor(sf::Color(0, 255,0));
            break;
        case 1:
            text_menu_items.at(0).setFillColor(sf::Color(0, 255,0));
            text_menu_items.at(lose_color).setFillColor(sf::Color(0, 0,255));
            text_menu_items.at(3).setFillColor(sf::Color(255, 0, 0));
            break;
        case 2:
            text_menu_items.at(settings_color).setFillColor(sf::Color(0, 0,255));
            text_menu_items.at(5).setFillColor(sf::Color(255, 255, 0));
            break;
    }
    if(menu_type == 0 || menu_type == 1) {
        for (int i = 0; i < menu_items.size() - 1; i++) {
            text_menu_items.at(i).move(menu_position_x, menu_position_y);
            menu_position_y += 60;
            window.draw(text_menu_items.at(i));
        }
    }
    else{
        for (int i = 0; i < settings_menu_items.size(); i++) {
            text_menu_items.at(i).move(menu_position_x, menu_position_y);
            menu_position_y += 60;
            window.draw(text_menu_items.at(i));
        }
    }
}



void open_main_menu()
{
    sf::RenderWindow window(sf::VideoMode(window_width * cell_size, window_height * cell_size), "CmakeProject1", sf::Style::Close);
    // открытие окна
    pause = true;
    int c = 0;
    while (window.isOpen()) {
        menu_control(window);
        if(pause){
            set_fonts();
            draw_main_menu(window);
            text_menu_items.clear();
            pause = false;
            window.display();
        }
    }
}

void open_settings_menu()
{
    sf::RenderWindow window(sf::VideoMode(window_width * cell_size, window_height * cell_size), "CmakeProject1", sf::Style::Close);
    // открытие окна
    pause = true;
    while (window.isOpen()) {
        settings_menu_control(window);
        if(pause){
            set_fonts();
            draw_main_menu(window);
            text_menu_items.clear();
            pause = false;
            window.display();
        }
    }
}
void open_lose_menu()
{
    sf::RenderWindow window(sf::VideoMode(window_width * cell_size, window_height * cell_size), "CmakeProject1", sf::Style::Close);
    pause = true;
    while (window.isOpen()) {
        lose_menu_control(window);
        if(pause){
            set_fonts();
            draw_main_menu(window);
            text_menu_items.clear();
            pause = false;
            window.display();
        }
    }
}

int main()
{
    switch(menu_type){
        case 0:
            open_main_menu();
            break;
        case 1:
            open_lose_menu();
            break;
        case 2:
            open_settings_menu();
            break;
    }

    return 0;
}

