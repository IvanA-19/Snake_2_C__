#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include "vars.h"

void set_sounds(){
    game_music.openFromFile("sounds/music_game.ogg");

    apple_buffer.loadFromFile("sounds/apple_2.wav");
    apple_sound.setBuffer(apple_buffer);

    game_over_buffer.loadFromFile("sounds/game_over.wav");
    game_over_sound.setBuffer(game_over_buffer);

    yellow_apple_buffer.loadFromFile("sounds/yellow_apple.wav");
    yellow_apple_sound.setBuffer(yellow_apple_buffer);

    menu_buffer.loadFromFile("sounds/menu.wav");
    menu_sound.setBuffer(menu_buffer);

    enter_buffer.loadFromFile("sounds/enter.wav");
    enter_sound.setBuffer(enter_buffer);

    green_apple_buffer.loadFromFile("sounds/green_apple.wav");
    green_apple_sound.setBuffer(green_apple_buffer);

    heart_buffer.loadFromFile("sounds/heart.wav");
    heart_sound.setBuffer(heart_buffer);

    life_up_buffer.loadFromFile("sounds/life_up.wav");
    life_up_sound.setBuffer(life_up_buffer);
}

void set_fonts()
{
    font_menu.loadFromFile("fonts/BigOldBoldy-dEjR.ttf");
    switch (menu_type) {
        case 0:
            for (int i = 0; i < menu_items.size() - 3; i++) {
                text_menu_items.emplace_back(sf::Text());
                text_menu_items.back().setString(menu_items.at(i));
                text_menu_items.back().setFont(font_menu);
                text_menu_items.back().setCharacterSize(40);
            }
            text_menu_items.emplace_back(sf::Text());
            text_menu_items.back().setString(menu_items.at(5));
            text_menu_items.back().setFont(font_menu);
            text_menu_items.back().setCharacterSize(70);
            text_menu_items.emplace_back(sf::Text());
            text_menu_items.back().setString(menu_items.at(6));
            text_menu_items.back().setFont(font_menu);
            text_menu_items.back().setCharacterSize(15);
            text_menu_items.emplace_back(sf::Text());
            text_menu_items.back().setString(menu_items.at(7));
            text_menu_items.back().setFont(font_menu);
            text_menu_items.back().setCharacterSize(15);
            break;
        case 1:
            for (int i = 0; i < lose_menu_items.size() - 1; i++) {
                text_menu_items.emplace_back(sf::Text());
                if(i != 0) {
                    text_menu_items.back().setString(lose_menu_items.at(i));
                }
                else{
                    text_menu_items.back().setString(lose_menu_items.at(i) + std::to_string(game_state.score));
                }
                text_menu_items.back().setFont(font_menu);
                text_menu_items.back().setCharacterSize(40);
            }
            text_menu_items.emplace_back(sf::Text());
            text_menu_items.back().setString(lose_menu_items.at(3));
            text_menu_items.back().setFont(font_menu);
            text_menu_items.back().setCharacterSize(80);
            break;
        case 2:
            for (int i = 0; i < settings_menu_items.size() - 1; i++) {
                text_menu_items.emplace_back(sf::Text());
                text_menu_items.back().setString(settings_menu_items.at(i));
                text_menu_items.back().setFont(font_menu);
                text_menu_items.back().setCharacterSize(40);
            }
            text_menu_items.emplace_back(sf::Text());
            text_menu_items.back().setString(settings_menu_items.at(8));
            text_menu_items.back().setFont(font_menu);
            text_menu_items.back().setCharacterSize(60);
            break;
        case 3:
            for (int i = 0; i < control_menu_items.size() - 1; i++) {
                text_menu_items.emplace_back(sf::Text());
                text_menu_items.back().setString(control_menu_items.at(i));
                text_menu_items.back().setFont(font_menu);
                text_menu_items.back().setCharacterSize(40);
            }
            text_menu_items.emplace_back(sf::Text());
            text_menu_items.back().setString(control_menu_items.at(3));
            text_menu_items.back().setFont(font_menu);
            text_menu_items.back().setCharacterSize(40);
            break;
        case 4:
            for (int i = 0; i < difficulty_menu_items.size() - 1; i++) {
                text_menu_items.emplace_back(sf::Text());
                text_menu_items.back().setString(difficulty_menu_items.at(i));
                text_menu_items.back().setFont(font_menu);
                text_menu_items.back().setCharacterSize(40);
            }
            text_menu_items.emplace_back(sf::Text());
            text_menu_items.back().setString(difficulty_menu_items.at(7));
            text_menu_items.back().setFont(font_menu);
            text_menu_items.back().setCharacterSize(60);
            break;
        case 5:
            for (int i = 0; i < pause_menu_items.size() - 2; i++) {
                text_menu_items.emplace_back(sf::Text());
                text_menu_items.back().setString(pause_menu_items.at(i));
                if(i != 0) {
                    text_menu_items.back().setString(pause_menu_items.at(i));
                }
                else{
                    text_menu_items.back().setString(pause_menu_items.at(i) + std::to_string(game_state.score));
                }
                text_menu_items.back().setFont(font_menu);
                text_menu_items.back().setCharacterSize(40);
            }

            text_menu_items.emplace_back(sf::Text());
            text_menu_items.back().setString(pause_menu_items.at(3));
            text_menu_items.back().setFont(font_menu);
            text_menu_items.back().setCharacterSize(70);

            text_menu_items.emplace_back(sf::Text());
            text_menu_items.back().setString(pause_menu_items.at(4) + std::to_string(game_state.count_of_lives));
            text_menu_items.back().setFont(font_menu);
            text_menu_items.back().setCharacterSize(40);

            break;
        case 6:
            for (int i = 0; i < volume_menu_items.size() - 1; i++) {
                text_menu_items.emplace_back(sf::Text());
                if(i != 0) {
                    text_menu_items.back().setString(volume_menu_items.at(i));
                }
                else{
                    text_menu_items.back().setString(volume_menu_items.at(i) + std::to_string(volume_level) + " %");
                }
                text_menu_items.back().setFont(font_menu);
                text_menu_items.back().setCharacterSize(40);
            }
            text_menu_items.emplace_back(sf::Text());
            text_menu_items.back().setString(volume_menu_items.at(2));
            text_menu_items.back().setFont(font_menu);
            text_menu_items.back().setCharacterSize(50);
            break;
        case 7:
            for (int i = 0; i < level_menu_items.size() - 1; i++) {
                text_menu_items.emplace_back(sf::Text());
                text_menu_items.back().setString(level_menu_items.at(i));
                text_menu_items.back().setFont(font_menu);
                text_menu_items.back().setCharacterSize(40);
            }
            text_menu_items.emplace_back(sf::Text());
            text_menu_items.back().setString(level_menu_items.at(5));
            text_menu_items.back().setFont(font_menu);
            text_menu_items.back().setCharacterSize(60);
            break;
        case 8:
            for(int i = 0; i < help_menu_items.size() - 1; i++){
                text_menu_items.emplace_back(sf::Text());
                text_menu_items.back().setString(help_menu_items.at(i));
                text_menu_items.back().setFont(font_menu);
                text_menu_items.back().setCharacterSize(25);
                if(i == 0 || i == 8){
                    text_menu_items.back().setCharacterSize(32);
                }
            }
            text_menu_items.emplace_back(sf::Text());
            text_menu_items.back().setString(help_menu_items.at(9));
            text_menu_items.back().setFont(font_menu);
            text_menu_items.back().setCharacterSize(60);
            break;
        default:
            break;
    }
}

void set_graphics_fonts(){
    font_menu.loadFromFile("fonts/BigOldBoldy-dEjR.ttf");
    for (int i = 0; i < control_menu_items.size() - 1; i++) {
        text_menu_items.emplace_back(sf::Text());
        text_menu_items.back().setString(graphics_menu_items.at(i));
        text_menu_items.back().setFont(font_menu);
        text_menu_items.back().setCharacterSize(42);
    }
    text_menu_items.emplace_back(sf::Text());
    text_menu_items.back().setString(graphics_menu_items.at(2));
    text_menu_items.back().setFont(font_menu);
    text_menu_items.back().setCharacterSize(50);
}

void graphics_menu(sf::RenderWindow& graphics_window){
    const float menu_width = 554;
    float menu_height = 120;

    const float menu_position_x = (float(main_menu_width) - menu_width) / 2;
    float menu_position_y = (float(main_menu_height) - menu_height) / 2 - 30;

    graphics_window.clear(sf::Color(0, 0, 0));
    text_menu_items.at(2).move(menu_position_x - 70, 20);
    text_menu_items.at(2).setFillColor(sf::Color(30, 255,25));
    graphics_window.draw(text_menu_items.at(2));
    text_menu_items.at(graphics_color).setFillColor(sf::Color(30, 206, 150));

    for (int i = 0; i < graphics_menu_items.size() - 1; i++) {
        text_menu_items.at(i).move(menu_position_x + 25, menu_position_y - 75);
        menu_position_y += 60;
        graphics_window.draw(text_menu_items.at(i));
    }
}

void control_graphics_menu(sf::RenderWindow &graphics_window)
{
    sf::Event event;

    while (graphics_window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed){
            graphics_window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Enter:
                    enter_sound.play();
                    switch(graphics_color){
                        case 0:
                            enter_sound.play();
                            text_menu_items.clear();
                            low_graphics = false;
                            high_graphics = true;
                            graphics_switched = true;
                            set_fonts();
                            graphics_window.close();
                            break;
                        case 1:
                            enter_sound.play();
                            text_menu_items.clear();
                            set_fonts();
                            graphics_window.close();
                            break;
                    }
                    break;
                case sf::Keyboard::Down:
                    menu_sound.play();
                    graphics_color++;
                    if(graphics_color == 2){
                        graphics_color = 0;
                    }
                    graphics_pause = true;
                    break;
                case sf::Keyboard::Up:
                    menu_sound.play();
                    graphics_color--;
                    if(graphics_color == -1){
                        graphics_color = 1;
                    }
                    graphics_pause = true;
                    break;
                case sf::Keyboard::Escape:
                    set_fonts();
                    graphics_window.close();
                    break;
            }
        }
    }
}

void open_graphics_menu(){
    sf::RenderWindow graphics_window(sf::VideoMode(main_menu_width, main_menu_height - 180), "Snake", sf::Style::Close);
    auto image = sf::Image{};
    image.loadFromFile("images/icon.png");
    graphics_window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
    graphics_pause = true;
    while (graphics_window.isOpen()) {
        control_graphics_menu(graphics_window);
        set_graphics_fonts();
        if(graphics_pause){
            graphics_menu(graphics_window);
            text_menu_items.clear();
            graphics_pause = false;
            graphics_window.display();
        }
    }
}

void menu_control(sf::RenderWindow& window_main)
{
    sf::Event event;

    while (window_main.pollEvent(event))
    {
        if(event.type == sf::Event::Closed){
            exit_game = true;
            window_main.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Down:
                    menu_sound.play();
                    color_menu++;
                    if(color_menu == 5){
                        color_menu = 0;
                    }
                    pause_menu = true;
                    break;
                case sf::Keyboard::Up:
                    menu_sound.play();
                    color_menu--;
                    if(color_menu == -1){
                        color_menu = 4;
                    }
                    pause_menu = true;
                    break;
                    break;
                case sf::Keyboard::Enter:
                    switch(color_menu){
                        case 0:
                            window_main.close();
                            break;
                        case 1:
                            menu_type = 7;
                            break;
                        case 2:
                            menu_type = 2;
                            set_op = true;
                            break;
                        case 3:
                            menu_type = 8;
                            op_help = true;
                            break;
                        case 4:
                            exit_game = true;
                            break;
                        default:
                            break;
                    }
                    enter_sound.play();
                    window_main.close();
                    break;
            }
        }
    }
}

void draw_main_menu(sf::RenderWindow& window_main)
{
    const float menu_item_interval = 20;

    float menu_item_max_width = 0;
    float current_menu_item_offset_y = 0;

    const float menu_width = 554;
    float menu_height = 120;

    const float menu_position_x = (float(main_menu_width) - menu_width) / 2;
    float menu_position_y = (float(main_menu_height) - menu_height) / 2 - 30;

    const float pause_menu_position_x = (float(pause_menu_width) - menu_width) / 2;
    float pause_menu_position_y = (float(pause_menu_height) - menu_height) / 2 - 25;

    const float volume_menu_position_x = (float(volume_menu_width) - menu_width) / 2;
    float volume_menu_position_y = (float(volume_menu_height) - menu_height) / 2;

    switch(menu_type){
        case 0:
            window_main.clear(sf::Color(0, 0, 0));
            text_menu_items.at(5).move(menu_position_x + 106, 20);
            text_menu_items.at(5).setFillColor(sf::Color(0, 255,0));
            window_main.draw(text_menu_items.at(5));
            text_menu_items.at(color_menu).setFillColor(sf::Color(255, 255,0));

            text_menu_items.at(6).move(menu_position_x + 178, 550);
            text_menu_items.at(6).setFillColor(sf::Color(0, 255,127));
            window_main.draw(text_menu_items.at(6));

            text_menu_items.at(7).move(menu_position_x + 178, 575);
            text_menu_items.at(7).setFillColor(sf::Color(0, 255,127));
            window_main.draw(text_menu_items.at(7));

            break;
        case 1:
            window_main.clear(sf::Color(0, 0, 0));
            text_menu_items.at(0).setFillColor(sf::Color(0, 255,0));
            text_menu_items.at(lose_color).setFillColor(sf::Color(255, 255,0));
            text_menu_items.at(3).setFillColor(sf::Color(255, 0, 0));
            text_menu_items.at(3).move(menu_position_x - 72, 40);
            window_main.draw(text_menu_items.at(3));
            break;
        case 2:
            window_main.clear(sf::Color(0, 0, 0));
            text_menu_items.at(8).move(menu_position_x -85, 30);
            text_menu_items.at(settings_color).setFillColor(sf::Color(0, 0,255));
            text_menu_items.at(8).setFillColor(sf::Color(255, 255, 0));
            window_main.draw(text_menu_items.at(8));
            break;
        case 3:
            window_main.clear(sf::Color(0, 0, 0));
            text_menu_items.at(3).move(menu_position_x - 85, 20);
            text_menu_items.at(3).setFillColor(sf::Color(0, 255,0));
            window_main.draw(text_menu_items.at(3));
            text_menu_items.at(color_of_control).setFillColor(sf::Color(255, 0,0));
            break;
        case 4:
            window_main.clear(sf::Color(0, 0, 0));
            text_menu_items.at(7).move(menu_position_x - 102, 30);
            text_menu_items.at(difficulty_color).setFillColor(sf::Color(255, 0,255));
            text_menu_items.at(7).setFillColor(sf::Color(0, 250, 154));
            window_main.draw(text_menu_items.at(7));
            break;
        case 5:
            window_main.clear(sf::Color(0, 0, 0));
            text_menu_items.at(0).setFillColor(sf::Color(0, 255,0));
            text_menu_items.at(4).setFillColor(sf::Color(0, 255,0));
            text_menu_items.at(4).move(float(pause_menu_position_x * 3.75), pause_menu_position_y - 25);
            window_main.draw(text_menu_items.at(4));
            text_menu_items.at(pause_color).setFillColor(sf::Color(255, 255,0));
            text_menu_items.at(3).setFillColor(sf::Color(255, 0, 0));
            text_menu_items.at(3).move(pause_menu_position_x + 96, 25);
            window_main.draw(text_menu_items.at(3));
            break;
        case 6:
            window_main.clear(sf::Color(0, 0, 0));
            text_menu_items.at(0).setFillColor(sf::Color(124, 252,0));
            text_menu_items.at(volume_color).setFillColor(sf::Color(255, 0,255));
            text_menu_items.at(2).setFillColor(sf::Color(127, 255, 212));
            text_menu_items.at(2).move(volume_menu_position_x - 64, 40);
            window_main.draw(text_menu_items.at(2));
            break;
        case 7:
            window_main.clear(sf::Color(0, 0, 0));
            text_menu_items.at(5).move(menu_position_x - 25, 30);
            text_menu_items.at(level_color).setFillColor(sf::Color(0, 255,255));
            text_menu_items.at(5).setFillColor(sf::Color(0, 255, 0));
            window_main.draw(text_menu_items.at(5));
            break;
        case 8:
            window_main.clear(sf::Color(0, 0, 0));
            text_menu_items.at(9).move(menu_position_x + 175, 25);
            text_menu_items.at(9).setFillColor(sf::Color(0, 255,255));
            text_menu_items.at(9).setFillColor(sf::Color(148, 0, 211));
            text_menu_items.at(0).setFillColor(sf::Color(30, 144, 255));
            text_menu_items.at(1).setFillColor(sf::Color(0, 255, 0));
            text_menu_items.at(2).setFillColor(sf::Color(255, 215, 0));
            text_menu_items.at(3).setFillColor(sf::Color(255, 0, 0));
            text_menu_items.at(4).setFillColor(sf::Color(199, 21, 133));
            text_menu_items.at(5).setFillColor(sf::Color(123, 104, 238));
            text_menu_items.at(6).setFillColor(sf::Color(0, 255, 127));
            text_menu_items.at(7).setFillColor(sf::Color(0, 255, 127));
            text_menu_items.at(8).setFillColor(sf::Color(0, 255, 255));
            window_main.draw(text_menu_items.at(9));
            break;
    }

    if(menu_type == 8){
        for (int i = 0; i < help_menu_items.size() - 1; i++) {
            if(i != 4) {
                text_menu_items.at(i).move(menu_position_x, menu_position_y - 125);
            }
            else{
                text_menu_items.at(i).move(menu_position_x, menu_position_y - 130);
            }
            if(i != 4) {
                menu_position_y += 50;
            }
            else{
                menu_position_y += 75;
            }
            window_main.draw(text_menu_items.at(i));
        }
    }

    if(menu_type == 0){
        for (int i = 0; i < menu_items.size() - 3; i++) {
            text_menu_items.at(i).move(menu_position_x, menu_position_y - 50);
            menu_position_y += 60;
            window_main.draw(text_menu_items.at(i));
        }
    }

    if(menu_type == 1 || menu_type == 3) {
        for (int i = 0; i < menu_items.size() - 5; i++) {
            text_menu_items.at(i).move(menu_position_x, menu_position_y);
            menu_position_y += 60;
            window_main.draw(text_menu_items.at(i));
        }
    }
    else if(menu_type == 2){
        menu_position_y = 120;
        for (int i = 0; i < settings_menu_items.size() - 1; i++) {
            text_menu_items.at(i).move(menu_position_x, menu_position_y);
            menu_position_y += 60;
            window_main.draw(text_menu_items.at(i));
        }
    }
    else if(menu_type == 4){
        float menu_position_y = 140;
        for (int i = 0; i < difficulty_menu_items.size() - 1; i++) {
            text_menu_items.at(i).move(menu_position_x, menu_position_y);
            menu_position_y += 60;
            window_main.draw(text_menu_items.at(i));
        }
    }
    else if(menu_type == 5){
        for (int i = 0; i < pause_menu_items.size() - 2; i++) {
            if(i != 0) {
                text_menu_items.at(i).move(pause_menu_position_x, pause_menu_position_y);
            }
            else{
                text_menu_items.at(i).move(pause_menu_position_x - 25, pause_menu_position_y - 25);
            }
            pause_menu_position_y += 60;
            window_main.draw(text_menu_items.at(i));
        }
    }
    else if(menu_type == 6){
        for (int i = 0; i < volume_menu_items.size() - 1; i++) {
            text_menu_items.at(i).move(volume_menu_position_x - 15, volume_menu_position_y);
            volume_menu_position_y += 60;
            window_main.draw(text_menu_items.at(i));
        }
    }

    if(menu_type == 7){
        float menu_position_y = 100;
        for (int i = 0; i < level_menu_items.size() - 1; i++) {
            text_menu_items.at(i).move(menu_position_x, menu_position_y + 60);
            menu_position_y += 60;
            window_main.draw(text_menu_items.at(i));
        }
    }
}

void control_menu_control(sf::RenderWindow &window_main)
{
    sf::Event event;

    while (window_main.pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Enter:
                    enter_sound.play();
                    switch(color_of_control){
                        case 0:
                            type_of_control = 1;
                            menu_type = 2;
                            break;
                        case 1:
                            type_of_control = 2;
                            menu_type = 2;
                            break;
                        case 2:
                            menu_type = 2;
                            break;
                        default:
                            break;
                    }
                    window_main.close();
                    break;
                case sf::Keyboard::Down:
                    menu_sound.play();
                    color_of_control++;
                    if(color_of_control == 3){
                        color_of_control = 0;
                    }
                    control_pause = true;
                    break;
                case sf::Keyboard::Up:
                    menu_sound.play();
                    color_of_control--;
                    if(color_of_control == -1){
                        color_of_control = 2;
                    }
                    control_pause = true;
                    break;
                default:
                    break;
            }
        }
    }
}

void open_control_menu()
{
    sf::RenderWindow window_main(sf::VideoMode(main_menu_width, main_menu_height), "Type of control", sf::Style::Close);
    auto image = sf::Image{};
    image.loadFromFile("images/icon.png");
    window_main.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
    control_pause = true;
    while (window_main.isOpen()) {
        control_menu_control(window_main);
        if(control_pause){
            set_fonts();
            draw_main_menu(window_main);
            text_menu_items.clear();
            control_pause = false;
            window_main.display();
        }
    }
}

void draw_window_color(sf::RenderWindow& window_2)
{
    sf::Texture none_texture;
    sf::Sprite none;

    none_texture.loadFromFile("images/none.png");
    none.setTexture(none_texture);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            none.setPosition(float(j * field_color_cell_size), float(i * field_color_cell_size));
            window_2.draw(none);
        }
    }
}

void open_main_menu()
{
    sf::RenderWindow window_main(sf::VideoMode( main_menu_width, main_menu_height), "Main_menu", sf::Style::Close);
    auto image = sf::Image{};
    image.loadFromFile("images/icon.png");
    window_main.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
    pause_menu = true;
    while (window_main.isOpen()) {
        menu_control(window_main);
        if(pause_menu){
            set_fonts();
            draw_main_menu(window_main);
            text_menu_items.clear();
            pause_menu = false;
            window_main.display();
        }
    }
}


void help_menu_control(sf::RenderWindow &window_main)
{
    sf::Event event;

    while (window_main.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Enter) {
                menu_type = 0;
                op_help = true;
                window_main.close();
            }
        }
    }
}

void open_help_menu()
{
    sf::RenderWindow window_main(sf::VideoMode( main_menu_width, main_menu_height), "Help", sf::Style::Close);
    auto image = sf::Image{};
    image.loadFromFile("images/icon.png");
    window_main.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
    help_pause = true;
    while (window_main.isOpen()) {
        help_menu_control(window_main);
        if(help_pause){
            set_fonts();
            draw_main_menu(window_main);
            text_menu_items.clear();
            help_pause = false;
            window_main.display();
        }
    }
}

void chose_window_color(sf::RenderWindow& window_2){
    sf::Event event;

    while (window_2.pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Up:
                    menu_sound.play();
                    if (color != 7) {
                        color++;
                    }
                    else {
                        color = 1;
                    }
                    switch (color) {
                        case 2:
                            x = 152; y = 251; z = 152;
                            color_pause = false;
                            window_2.clear(sf::Color(x, y, z));
                            r = x; g = y; b = z;
                            break;
                        case 3:
                            x = 0; y = 255; z = 153;
                            color_pause = false;
                            window_2.clear(sf::Color(x, y, z));
                            r = x; g = y; b = z;
                            break;
                        case 4:
                            x = 147; y = 112; z = 219;
                            color_pause = false;
                            window_2.clear(sf::Color(x, y, z));
                            r = x; g = y; b = z;
                            break;
                        case 5:
                            x = 240; y = 128; z = 128;
                            color_pause = false;
                            window_2.clear(sf::Color(x, y, z));
                            r = x; g = y; b = z;
                            break;
                        case 6:
                            x = 240; y = 230; z = 140;
                            color_pause = false;
                            window_2.clear(sf::Color(x, y, z));
                            r = x; g = y; b = z;
                            break;
                        case 7:
                            x = 60; y = 179; z = 113;
                            color_pause = false;
                            window_2.clear(sf::Color(x, y, z));
                            r = x; g = y; b = z;
                            break;
                        default:
                            x = 127; y = 255; z = 212;
                            color_pause = false;
                            window_2.clear(sf::Color(x, y, z));
                            r = x; g = y; b = z;
                    }
                    break;

                case sf::Keyboard::Down:
                    menu_sound.play();
                    if (color != 1) {
                        color--;
                    }
                    else {
                        color = 7;
                    }
                    switch (color) {
                        case 2:
                            x = 152; y = 251; z = 152;
                            color_pause = false;
                            window_2.clear(sf::Color(x, y, z));
                            r = x; g = y; b = z;
                            break;
                        case 3:
                            x = 0; y = 255; z = 153;
                            color_pause = false;
                            window_2.clear(sf::Color(x, y, z));
                            r = x; g = y; b = z;
                            break;
                        case 4:
                            x = 147; y = 112; z = 219;
                            color_pause = false;
                            window_2.clear(sf::Color(x, y, z));
                            r = x; g = y; b = z;
                            break;
                        case 5:
                            x = 240; y = 128; z = 128;
                            color_pause = false;
                            window_2.clear(sf::Color(x, y, z));
                            r = x; g = y; b = z;
                            break;
                        case 6:
                            x = 240; y = 230; z = 140;
                            color_pause = false;
                            window_2.clear(sf::Color(x, y, z));
                            r = x; g = y; b = z;
                            break;
                        case 7:
                            x = 60; y = 179; z = 113;
                            color_pause = false;
                            window_2.clear(sf::Color(x, y, z));
                            r = x; g = y; b = z;
                            break;
                        default:
                            x = 127; y = 255; z = 212;
                            color_pause = false;
                            window_2.clear(sf::Color(x, y, z));
                            r = x; g = y; b = z;
                    }
                    break;


                case sf::Keyboard::Enter:
                    enter_sound.play();
                    window_2.close();
                    break;
            }

        }
    }
}

void set_window_color()
{
    sf::RenderWindow window_2(sf::VideoMode(window_color_width, window_color_height), "Field", sf::Style::Close);

    auto image = sf::Image{};
    image.loadFromFile("images/icon.png");
    window_2.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());

    window_2.clear(sf::Color(x, y, z));
    color_pause = false;

    while (window_2.isOpen()) {

        chose_window_color(window_2);

        if (!color_pause) {
            draw_window_color(window_2);
            window_2.display();
            color_pause = true;
        }
    }
}

void check_event_2(sf::RenderWindow& window_wall)
{
    sf::Event event;
    while (window_wall.pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Right:
                    menu_sound.play();
                    if (choice_wall != 7) {
                        choice_wall += 2;
                    }
                    else {
                        choice_wall = 1;
                    }
                    break;

                case sf::Keyboard::Left:
                    menu_sound.play();
                    if (choice_wall != 1) {
                        choice_wall -= 2;
                    }
                    break;
                case sf::Keyboard::Enter:
                    enter_sound.play();
                    switch (choice_wall) {
                        case 1:
                            wall = 0;
                            window_wall.close();
                            break;
                        case 3:
                            wall = 1;
                            window_wall.close();
                            break;
                        case 5:
                            wall = 2;
                            window_wall.close();
                            break;
                        case 7:
                            wall = 3;
                            window_wall.close();
                            break;
                        default:
                            break;
                    }
            }
        }
    }
}

void draw_arrow_2(sf::RenderWindow& window_wall)
{
    sf::Texture arrow_texture_2;
    sf::Sprite arrow_2;
    arrow_texture_2.loadFromFile("images/arrow_2.png");
    arrow_2.setTexture(arrow_texture_2);
    arrow_2.setPosition(float(choice_wall * wall_cell_size), float(4 * wall_cell_size));
    window_wall.draw(arrow_2);
}

void draw_wall_choice(sf::RenderWindow& window_wall)
{
    sf::Texture wall_texture;
    sf::Sprite wall;
    for (int i = 0; i < skin_length + 2; i++) {
        for (int j = 0; j < skin_count + 5; j++) {
            if(i != 0 && i != 5) {
                switch (j) {
                    case 1:
                        wall_texture.loadFromFile("images/wall.png");
                        wall.setTexture(wall_texture);
                        wall.setPosition(float(j * wall_cell_size), float(i * wall_cell_size));
                        window_wall.draw(wall);
                        break;
                    case 3:
                        wall_texture.loadFromFile("images/wall_2.png");
                        wall.setTexture(wall_texture);
                        wall.setPosition(float(j * wall_cell_size), float(i * wall_cell_size));
                        window_wall.draw(wall);
                        break;
                    case 5:
                        wall_texture.loadFromFile("images/wall_3.png");
                        wall.setTexture(wall_texture);
                        wall.setPosition(float(j * wall_cell_size), float(i * wall_cell_size));
                        window_wall.draw(wall);
                        break;
                    case 7:
                        wall_texture.loadFromFile("images/cactus_wall.png");
                        wall.setTexture(wall_texture);
                        wall.setPosition(float(j * wall_cell_size), float(i * wall_cell_size));
                        window_wall.draw(wall);
                        break;
                    default:
                        break;
                }
            }

        }
    }
    draw_arrow_2(window_wall);
}

void choose_wall()
{
    sf::RenderWindow window_wall(sf::VideoMode(wall_choice_width, wall_choice_height), "Wall", sf::Style::Close);

    auto image = sf::Image{};
    image.loadFromFile("images/icon.png");
    window_wall.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
    while (window_wall.isOpen()) {
        window_wall.clear(sf::Color(0, 250, 154));

        draw_wall_choice(window_wall);

        window_wall.display();
        sf::sleep(sf::milliseconds(100));
        window_wall.clear(sf::Color(255, 255, 255));

        check_event_2(window_wall);
    }
}

void check_event(sf::RenderWindow& window_1)
{
    sf::Event event;
    while (window_1.pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Right:
                    menu_sound.play();
                    if (choice != 9) {
                        choice += 2;
                    }
                    else {
                        choice = 1;
                    }
                    break;

                case sf::Keyboard::Left:
                    menu_sound.play();
                    if (choice != 1) {
                        choice -= 2;
                    }
                    break;
                case sf::Keyboard::Enter:
                    enter_sound.play();
                    switch (choice) {
                        case 1:
                            skin = 0;
                            break;
                        case 3:
                            skin = 1;
                            break;
                        case 5:
                            skin = 2;
                            break;
                        case 7:
                            skin = 3;
                            break;
                        case 9:
                            skin = 4;
                            break;
                        default:
                            break;
                    }
                    window_1.close();
                    break;
            }
        }
    }
}

void draw_arrow(sf::RenderWindow& window_1)
{
    sf::Texture arrow_texture;
    sf::Sprite arrow;
    arrow_texture.loadFromFile("images/arrow.png");
    arrow.setTexture(arrow_texture);
    arrow.setPosition(float(choice * skin_cell_size), float(5 * skin_cell_size));
    window_1.draw(arrow);
}

void draw_skin_choice(sf::RenderWindow& window_1) {
    sf::Texture skin_texture;
    sf::Sprite skin;
    for (int i = 0; i < skin_length + 5; i++) {
        for (int j = 0; j < skin_count + 5; j++) {
            if (i == 1) {
                switch (j) {
                    case 1:
                        skin_texture.loadFromFile("images/head.png");
                        skin.setTexture(skin_texture);
                        skin.setPosition(float(j * skin_cell_size), float(i * skin_cell_size));
                        window_1.draw(skin);
                        break;
                    case 3:
                        skin_texture.loadFromFile("images/head_1.png");
                        skin.setTexture(skin_texture);
                        skin.setPosition(float(j * skin_cell_size), float(i * skin_cell_size));
                        window_1.draw(skin);
                        break;
                    case 5:
                        skin_texture.loadFromFile("images/head_2.png");
                        skin.setTexture(skin_texture);
                        skin.setPosition(float(j * skin_cell_size), float(i * skin_cell_size));
                        window_1.draw(skin);
                        break;
                    case 7:
                        skin_texture.loadFromFile("images/head_3.png");
                        skin.setTexture(skin_texture);
                        skin.setPosition(float(j * skin_cell_size), float(i * skin_cell_size));
                        window_1.draw(skin);
                        break;
                    case 9:
                        skin_texture.loadFromFile("images/head_4.png");
                        skin.setTexture(skin_texture);
                        skin.setPosition(float(j * skin_cell_size), float(i * skin_cell_size));
                        window_1.draw(skin);
                        break;
                    default:
                        break;
                }
            } else {
                if (i != 0 && i != 5) {
                    switch (j) {
                        case 1:
                            skin_texture.loadFromFile("images/snake.png");
                            skin.setTexture(skin_texture);
                            skin.setPosition(float(j * skin_cell_size), float(i * skin_cell_size));
                            window_1.draw(skin);
                            break;
                        case 3:
                            skin_texture.loadFromFile("images/snake_1.png");
                            skin.setTexture(skin_texture);
                            skin.setPosition(float(j * skin_cell_size), float(i * skin_cell_size));
                            window_1.draw(skin);
                            break;
                        case 5:
                            skin_texture.loadFromFile("images/snake_2.png");
                            skin.setTexture(skin_texture);
                            skin.setPosition(float(j * skin_cell_size), float(i * skin_cell_size));
                            window_1.draw(skin);
                            break;
                        case 7:
                            skin_texture.loadFromFile("images/snake_3.png");
                            skin.setTexture(skin_texture);
                            skin.setPosition(float(j * skin_cell_size), float(i * skin_cell_size));
                            window_1.draw(skin);
                            break;
                        case 9:
                            skin_texture.loadFromFile("images/snake_4.png");
                            skin.setTexture(skin_texture);
                            skin.setPosition(float(j * skin_cell_size), float(i * skin_cell_size));
                            window_1.draw(skin);
                            break;
                        default:
                            break;
                    }
                }
            }
        }
        draw_arrow(window_1);
    }
}

void choose_skin()
{
    sf::RenderWindow window_1(sf::VideoMode(skin_choice_width, skin_choice_height), "Snake_skin", sf::Style::Close);

    auto image = sf::Image{};
    image.loadFromFile("images/icon.png");
    window_1.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());

    while (window_1.isOpen()) {
        window_1.clear(sf::Color(176, 224, 230));

        draw_skin_choice(window_1);

        window_1.display();
        sf::sleep(sf::milliseconds(100));
        window_1.clear(sf::Color(255, 255, 255));

        check_event(window_1);
    }
}

void difficulty_menu_control(sf::RenderWindow &window_main)
{
    sf::Event event;

    while (window_main.pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Enter:
                    enter_sound.play();
                    switch(difficulty_color){
                        case 0:
                            menu_type = 2;
                            game_state.speed = 120;
                            break;
                        case 1:
                            menu_type = 2;
                            game_state.speed = 90;
                            break;
                        case 2:
                            menu_type = 2;
                            game_state.speed = 60;
                            break;
                        case 3:
                            menu_type = 2;
                            game_state.speed = 30;
                            break;
                        case 4:
                            menu_type = 2;
                            game_state.speed = 15;
                            break;
                        case 5:
                            menu_type = 2;
                            game_state.speed = 10;
                            break;
                        case 6:
                            menu_type = 2;
                            break;
                        default:
                            break;
                    }
                    window_main.close();
                    break;
                case sf::Keyboard::Down:
                    menu_sound.play();
                    difficulty_color++;
                    if(difficulty_color == 7){
                        difficulty_color = 0;
                    }
                    difficulty_pause = true;
                    break;
                case sf::Keyboard::Up:
                    menu_sound.play();
                    difficulty_color--;
                    if(difficulty_color == -1){
                        difficulty_color = 6;
                    }
                    difficulty_pause = true;
                    break;
                default:
                    break;
            }
        }
    }
}

void open_difficulty_menu()
{
    sf::RenderWindow window_main(sf::VideoMode(main_menu_width, main_menu_height), "Difficulty", sf::Style::Close);
    auto image = sf::Image{};
    image.loadFromFile("images/icon.png");
    window_main.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
    difficulty_pause = true;
    while (window_main.isOpen()) {
        difficulty_menu_control(window_main);
        if(difficulty_pause){
            set_fonts();
            draw_main_menu(window_main);
            text_menu_items.clear();
            difficulty_pause = false;
            window_main.display();
        }
    }
}

void level_menu_control(sf::RenderWindow &window_main)
{
    sf::Event event;

    while (window_main.pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Enter:
                    enter_sound.play();
                    switch(level_color){
                        case 0:
                            menu_type = 0;
                            game_level = 0;
                            break;
                        case 1:
                            menu_type = 0;
                            game_level = 1;
                            break;
                        case 2:
                            game_level = 2;
                            menu_type = 0;
                            break;
                        case 3:
                            game_level = 3;
                            menu_type = 0;
                            break;
                        case 4:
                            op_main = true;
                            menu_type = 0;
                            break;
                        default:
                            break;
                    }
                    window_main.close();
                    break;
                case sf::Keyboard::Down:
                    menu_sound.play();
                    level_color++;
                    if(level_color == 5){
                        level_color = 0;
                    }
                    game_level_pause = true;
                    break;
                case sf::Keyboard::Up:
                    menu_sound.play();
                    level_color--;
                    if(level_color == -1){
                        level_color = 4;
                    }
                    game_level_pause = true;
                    break;
                default:
                    break;
            }
        }
    }
}

void open_level_menu()
{
    sf::RenderWindow window_main(sf::VideoMode(main_menu_width, main_menu_height - 100), "Level", sf::Style::Close);// открытие окна
    auto image = sf::Image{};
    image.loadFromFile("images/icon.png");
    window_main.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
    game_level_pause = true;
    while (window_main.isOpen()) {
        level_menu_control(window_main);
        if(game_level_pause){
            set_fonts();
            draw_main_menu(window_main);
            text_menu_items.clear();
            game_level_pause = false;
            window_main.display();
        }
    }
}

void set_volume_level(){
    game_music.setVolume(music_level);
    apple_sound.setVolume(float(volume_level));
    menu_sound.setVolume(float(volume_level));
    game_over_sound.setVolume(float(volume_level));
    yellow_apple_sound.setVolume(float(volume_level));
    green_apple_sound.setVolume(float(volume_level));
    enter_sound.setVolume(float(volume_level));
    heart_sound.setVolume(float(volume_level));
    life_up_sound.setVolume(float(volume_level));
}

void volume_menu_control(sf::RenderWindow& window_volume)
{
    sf::Event event;

    while (window_volume.pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Down:
                    menu_sound.play();
                    if(volume_level != 0){
                        volume_level -= 5;
                        if(volume_level % 15 == 0){
                            music_level -= 10;
                        }
                        set_volume_level();
                    }
                    pause = true;
                    break;
                case sf::Keyboard::Up:
                    menu_sound.play();
                    if(volume_level != 100){
                        volume_level += 5;
                        if(volume_level % 15 == 0){
                            music_level += 10;
                        }
                        set_volume_level();
                    }
                    pause = true;
                    break;
                case sf::Keyboard::Enter:
                    enter_sound.play();
                    menu_type = 2;
                    window_volume.close();
                    break;
                default:
                    break;
            }
        }
    }
}

void open_volume_menu(){
    sf::RenderWindow window_volume(sf::VideoMode(volume_menu_width, volume_menu_height), "Volume", sf::Style::Close);
    auto image = sf::Image{};
    image.loadFromFile("images/icon.png");
    window_volume.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
    pause = true;
    while (window_volume.isOpen()) {
        volume_menu_control(window_volume);
        if(pause){
            set_fonts();
            draw_main_menu(window_volume);
            text_menu_items.clear();
            pause = false;
            window_volume.display();
        }
    }
}

void settings_menu_control(sf::RenderWindow &window_main)
{
    sf::Event event;

    while (window_main.pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Enter:
                    enter_sound.play();
                    switch(settings_color){
                        case 0:
                            menu_type = 3;
                            break;
                        case 1:
                            set_window_color();
                            break;
                        case 2:
                            choose_skin();
                            break;
                        case 3:
                            choose_wall();
                            break;
                        case 4:
                            menu_type = 4;
                            break;
                        case 5:
                            menu_type = 6;
                            break;
                        case 6:
                            open_graphics_menu();
                            break;
                        case 7:
                            set_op = false;
                            menu_type = 0;
                            color_menu = 0;
                            break;
                        default:
                            break;
                    }
                    window_main.close();
                    break;
                case sf::Keyboard::Down:
                    menu_sound.play();
                    settings_color++;
                    if(settings_color == 8){
                        settings_color = 0;
                    }
                    pause = true;
                    break;
                case sf::Keyboard::Up:
                    menu_sound.play();
                    settings_color--;
                    if(settings_color == -1){
                        settings_color = 7;
                    }
                    pause = true;
                    break;
            }
        }
    }
}

void open_settings_menu()
{

    sf::RenderWindow window_main(sf::VideoMode(main_menu_width, main_menu_height), "Settings", sf::Style::Close);
    auto image = sf::Image{};
    image.loadFromFile("images/icon.png");
    window_main.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
    pause = true;
    while (window_main.isOpen()) {
        settings_menu_control(window_main);
        if(pause){
            set_fonts();
            draw_main_menu(window_main);
            text_menu_items.clear();
            pause = false;
            window_main.display();
        }
    }
}

int get_random_empty_cell()
{
    int empty_cell_count = 0;
    for (int j = 0; j < field_size_y; j++) {
        for (int i = 0; i < field_size_x; i++) {
            if (game_state.field[j][i] == FIELD_CELL_TYPE_NONE) {
                empty_cell_count++;
            }
        }
    }

    if (empty_cell_count == 0) {
        empty_cell_count = 1;
    }

    int target_empty_cell_index = rand() % empty_cell_count;
    int empty_cell_index = 0;

    for (int j = 0; j < field_size_y; j++) {
        for (int i = 0; i < field_size_x; i++) {
            if (game_state.field[j][i] == FIELD_CELL_TYPE_NONE) {
                if (empty_cell_index == target_empty_cell_index) {
                    return j * field_size_x + i;
                }
                empty_cell_index++;
            }
        }
    }

    return -1;
}

void add_apple()
{
    int apple_pos = get_random_empty_cell();
    if (apple_pos != -1) {
        game_state.field[apple_pos / field_size_x][apple_pos % field_size_x] = FIELD_CELL_TYPE_APPLE;
    }

}

void add_heart()
{
    int heart_pos = get_random_empty_cell();
    if (heart_pos != -1) {
        game_state.field[heart_pos / field_size_x][heart_pos % field_size_x] = FIELD_CELL_TYPE_HEART;
    }
}

void add_yellow_apple()
{
    int yellow_apple_pos = get_random_empty_cell();
    if (yellow_apple_pos != -1) {
        game_state.field[yellow_apple_pos / field_size_x][yellow_apple_pos % field_size_x] = FIELD_CELL_TYPE_YELLOW_APPLE;
    }
}

void add_green_apple()
{
    int green_apple_pos = get_random_empty_cell();
    if (green_apple_pos != -1) {
        game_state.field[green_apple_pos / field_size_x][green_apple_pos % field_size_x] = FIELD_CELL_TYPE_GREEN_APPLE;
    }
}

void clear_field()
{
    for (int j = 0; j < field_size_y; j++) {
        for (int i = 0; i < field_size_x; i++) {
            game_state.field[j][i] = FIELD_CELL_TYPE_NONE; // генерация пустых клеток
        }
    }

    for (int i = 0; i < game_state.snake_length; i++) //установка позиции змейки в начале
        game_state.field[game_state.snake_position_y][game_state.snake_position_x - i] = game_state.snake_length - i;


    switch(game_level) {
        case 0:
            for (int i = 0; i < field_size_x; i++) {
                if (i < 10 || field_size_x - i - 1 < 10) {
                    game_state.field[0][i] = FIELD_CELL_TYPE_WALL;
                    game_state.field[field_size_y - 1][i] = FIELD_CELL_TYPE_WALL; //генерация горизонтальных стен
                }
            }
            for (int j = 1; j < field_size_y - 1; j++) {
                if (j < 6 || field_size_y - j - 1 < 6) {
                    game_state.field[j][0] = FIELD_CELL_TYPE_WALL; // генерация уголка
                    game_state.field[j][field_size_x - 1] = FIELD_CELL_TYPE_WALL; // генерация вертикальных стен
                }
            }
            break;
        case 1:
            for (int i = 0; i < field_size_x; i++) {
                game_state.field[0][i] = FIELD_CELL_TYPE_WALL;
                game_state.field[field_size_y - 1][i] = FIELD_CELL_TYPE_WALL; //генерация горизонтальных сте
            }
            for (int j = 1; j < field_size_y - 1; j++) {
                game_state.field[j][0] = FIELD_CELL_TYPE_WALL; // генерация уголка
                game_state.field[j][field_size_x - 1] = FIELD_CELL_TYPE_WALL; // генерация вертикальных стен
            }

            for (int i = 0; i < field_size_x - 7; i++) {
                if (i > 6 && i < 14 || i > 19) {
                    game_state.field[4][i] = FIELD_CELL_TYPE_WALL;
                    game_state.field[field_size_y - 5][i] = FIELD_CELL_TYPE_WALL; //генерация горизонтальных стен
                }
            }
            for (int j = 1; j < field_size_y - 4; j++) {
                if (j > 4 && j < 7 || j > 11) {
                    game_state.field[j][7] = FIELD_CELL_TYPE_WALL; // генерация уголка
                    game_state.field[j][field_size_x - 8] = FIELD_CELL_TYPE_WALL; // генерация вертикальных стен
                }
            }
            break;
        case 2:
            for (int i = 0; i < field_size_y - 1; i++) {
                if(i == 4 || i == 5) {
                    game_state.field[i][5] = FIELD_CELL_TYPE_WALL;
                    game_state.field[i][6] = FIELD_CELL_TYPE_WALL;
                }
                if(i == 13 || i == 14){
                    game_state.field[i][5] = FIELD_CELL_TYPE_WALL;
                    game_state.field[i][6] = FIELD_CELL_TYPE_WALL;
                }
                if (i > 0 && i < 6 || i > 12){
                    game_state.field[i][15] = FIELD_CELL_TYPE_WALL;
                    game_state.field[i][16] = FIELD_CELL_TYPE_WALL;
                }
            }
            for(int j = 25; j < field_size_x - 1; j++){
                game_state.field[5][j] = FIELD_CELL_TYPE_WALL;
                game_state.field[6][j] = FIELD_CELL_TYPE_WALL;
                game_state.field[12][j] = FIELD_CELL_TYPE_WALL;
                game_state.field[13][j] = FIELD_CELL_TYPE_WALL;
            }
            for(int i = 0; i < field_size_x; i++){
                game_state.field[0][i] = FIELD_CELL_TYPE_WALL;
                game_state.field[field_size_y - 1][i] = FIELD_CELL_TYPE_WALL;
            }
            for (int j = 1; j < field_size_y - 1; j++) {
                game_state.field[j][0] = FIELD_CELL_TYPE_WALL; // генерация уголка
                game_state.field[j][field_size_x - 1] = FIELD_CELL_TYPE_WALL; // генерация вертикальных стен
            }
            break;

        case 3:
            for (int i = 0; i < field_size_x; i++) {
                if(i < 12 || i > 21) {
                    game_state.field[0][i] = FIELD_CELL_TYPE_WALL;
                    game_state.field[field_size_y - 1][i] = FIELD_CELL_TYPE_WALL;
                }
                if(i > 11 && i < 22){
                    game_state.field[5][i] = FIELD_CELL_TYPE_WALL;
                }
                if(i > 0 && i < 6 || i == 32){
                    game_state.field[5][i] = FIELD_CELL_TYPE_WALL;
                    game_state.field[13][i] = FIELD_CELL_TYPE_WALL;
                }
            }
            for (int j = 1; j < field_size_y - 1; j++) {
                if(j < 6 || j > 12) {
                    game_state.field[j][0] = FIELD_CELL_TYPE_WALL;
                    game_state.field[j][field_size_x - 1] = FIELD_CELL_TYPE_WALL;
                }
                if(j > 4 && j < 14){
                    game_state.field[j][6] = FIELD_CELL_TYPE_WALL;
                }
                if(j < 6 || j == 17){
                    game_state.field[j][11] = FIELD_CELL_TYPE_WALL;
                    game_state.field[j][22] = FIELD_CELL_TYPE_WALL;
                }
            }
            break;
        default:
            break;
    }

    add_green_apple(); // генерация зеленого ябллока
    add_apple(); // генерация красного яблока
}

void draw_field(sf::RenderWindow& window)
{
    sf::Texture none_texture;
    none_texture.loadFromFile("images/none.png");
    sf::Sprite none;
    none.setTexture(none_texture);

    sf::Texture snake_texture;
    sf::Sprite snake;

    sf::Texture snake_head_texture;
    sf::Sprite snake_head;

    switch (skin) {
        case 1:
            snake_texture.loadFromFile("images/snake_1.png");
            snake.setTexture(snake_texture);

            snake_head_texture.loadFromFile("images/head_1.png");
            snake_head.setTexture(snake_head_texture);
            break;
        case 2:
            snake_texture.loadFromFile("images/snake_2.png");
            snake.setTexture(snake_texture);

            snake_head_texture.loadFromFile("images/head_2.png");
            snake_head.setTexture(snake_head_texture);
            break;
        case 3:
            snake_texture.loadFromFile("images/snake_3.png");
            snake.setTexture(snake_texture);

            snake_head_texture.loadFromFile("images/head_3.png");
            snake_head.setTexture(snake_head_texture);
            break;
        case 4:
            snake_texture.loadFromFile("images/snake_4.png");
            snake.setTexture(snake_texture);

            snake_head_texture.loadFromFile("images/head_4.png");
            snake_head.setTexture(snake_head_texture);
            break;
        default:
            snake_texture.loadFromFile("images/snake.png");
            snake.setTexture(snake_texture);

            snake_head_texture.loadFromFile("images/head.png");
            snake_head.setTexture(snake_head_texture);
    }

    sf::Texture apple_texture;
    apple_texture.loadFromFile("images/apple.png");
    sf::Sprite apple;
    apple.setTexture(apple_texture);

    sf::Texture apple_green_texture;
    apple_green_texture.loadFromFile("images/apple_green.png");
    sf::Sprite apple_green;
    apple_green.setTexture(apple_green_texture);

    sf::Texture apple_yellow_texture;
    apple_yellow_texture.loadFromFile("images/yelow_apple.png");
    sf::Sprite apple_yellow;
    apple_yellow.setTexture(apple_yellow_texture);

    sf::Texture wall_texture;
    switch (wall) {
        case 1:
            wall_texture.loadFromFile("images/wall_2.png");
            break;
        case 2:
            wall_texture.loadFromFile("images/wall_3.png");
            break;
        case 3:
            wall_texture.loadFromFile("images/cactus_wall.png");
            break;
        default:
            wall_texture.loadFromFile("images/wall.png");
    }

    sf::Sprite wall;
    wall.setTexture(wall_texture);

    sf::Texture heart_texture;
    heart_texture.loadFromFile("images/life.png");
    sf::Sprite heart;
    heart.setTexture(heart_texture);

    for (int j = 0; j < field_size_y; j++) {
        for (int i = 0; i < field_size_x; i++) {
            switch (game_state.field[j][i]) {
                case FIELD_CELL_TYPE_NONE:
                    none.setPosition(float(i * cell_size), float(j * cell_size));
                    window.draw(none);
                    break;
                case FIELD_CELL_TYPE_APPLE:
                    apple.setPosition(float(i * cell_size), float(j * cell_size));
                    window.draw(apple);
                    break;
                case FIELD_CELL_TYPE_GREEN_APPLE:
                    apple_green.setPosition(float(i * cell_size), float(j * cell_size));
                    window.draw(apple_green);
                    break;
                case FIELD_CELL_TYPE_YELLOW_APPLE:
                    apple_yellow.setPosition(float(i * cell_size), float(j * cell_size));
                    window.draw(apple_yellow);
                    break;
                case FIELD_CELL_TYPE_WALL:
                    wall.setPosition(float(i * cell_size), float(j * cell_size));
                    window.draw(wall);
                    break;
                case FIELD_CELL_TYPE_HEART:
                    heart.setPosition(float(i * cell_size), float(j * cell_size));
                    window.draw(heart);
                    break;
                default:
                    if (game_state.field[j][i] == game_state.snake_length) {
                        float offset_x = snake_head.getLocalBounds().width / 2;
                        float offset_y = snake_head.getLocalBounds().height / 2;
                        snake_head.setPosition(float(i * cell_size + offset_x), float(j * cell_size + offset_y));
                        snake_head.setOrigin(offset_x, offset_y);
                        switch (game_state.snake_direction) {
                            case SNAKE_DIRECTION_RIGHT:
                                snake_head.setRotation(90);
                                break;
                            case SNAKE_DIRECTION_LEFT:
                                snake_head.setRotation(-90);
                                break;
                            case SNAKE_DIRECTION_DOWN:
                                snake_head.setRotation(180);
                                break;
                            case SNAKE_DIRECTION_UP:
                                snake_head.setRotation(0);
                                break;
                        }

                        window.draw(snake_head);
                    }
                    else {
                        snake.setPosition(float(i * cell_size), float(j * cell_size));
                        window.draw(snake);
                    }
            }
        }
    }
}

void grow_snake()
{
    for(int j = 0; j < field_size_y; j++) {
        for (int i = 0; i < field_size_x; i++) {
            if (game_state.field[j][i] > FIELD_CELL_TYPE_NONE) {
                game_state.field[j][i]++;
            }
        }
    }
}

void random_event()
{
    srand(time(nullptr));
    int random_trap;
    random_trap = rand() % 4;
    switch (random_trap) {
        case 0:
            invert_control = true;
            break;
        case 1:
            if (game_state.speed > 30) {
                game_state.speed = 40;
            }
            else{
                switch(game_state.speed){
                    case 30:
                        game_state.speed = 20;
                        break;
                    case 15:
                        game_state.speed = 10;
                        break;
                    case 10:
                        game_state.speed = 5;
                        break;
                }
            }
            break;
        case 2:
            if (game_state.score >= 10) {
                game_state.score -= 10;
            }
            else {
                game_state.score = 0;
            }
            score_decrease = true;
            break;
        case 3:
            game_state.snake_length += 3;
            length_increase = true;
            break;
        default:
            break;
    }
}

int random_bonus()
{
    srand(time(nullptr));
    int bonus;

    bonus = rand() % 5;

    switch(bonus) {
        case 0:
            game_state.score += 15;
            break;
        case 1:
            return 1;
        case 2:
            game_state.speed = 130;
            break;
        case 3:
            if (game_state.snake_length >= 9) {
                game_state.snake_length -= 5;
            }
            break;
        case 4:
            game_state.count_of_lives += 5;
            x = 0;
            y = 220;
            z = 255;
            lives_color = 5;
            break;
        default:
            break;
    }
    return 0;
}

void normal_game()
{
    game_state.speed = game_state.speed_last;
    if (lives_color == 0) {
        x = r; y = g; z = b;
    }
    invert_control = false;
    if (length_increase) {
        length_increase = false;
        game_state.snake_length -= 3;
    }
    if (score_decrease) {
        score_decrease = false;
        game_state.score = game_state.last_score;
    }
}

void pause_menu_control(sf::RenderWindow &window_pause, sf::RenderWindow& window)
{
    sf::Event event;

    while (window_pause.pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Enter:
                    enter_sound.play();
                    switch(pause_color){
                        case 1:
                            menu_type = 0;
                            game_music.setLoop(true);
                            game_music.play();
                            game_paused = false;
                            break;
                        case 2:
                            game_music.stop();
                            menu_type = 0;
                            window.close();
                            pause_menu = 0;
                            restart = false;
                            x = r; y = g; z = b;
                            normal_game();
                            break;

                    }
                    window_pause.close();
                    break;
                case sf::Keyboard::Down:
                    menu_sound.play();
                    pause_color++;
                    if(pause_color == 3){
                        pause_color = 1;
                    }
                    pause = true;
                    break;
                case sf::Keyboard::Up:
                    menu_sound.play();
                    pause_color--;
                    if(pause_color == 0){
                        pause_color = 2;
                    }
                    pause = true;
                    break;
            }
        }
    }
}

void open_pause_menu(sf::RenderWindow& window)
{
    sf::RenderWindow window_pause(sf::VideoMode(pause_menu_width, pause_menu_height), "Game pause", sf::Style::Close);
    auto image = sf::Image{};
    image.loadFromFile("images/icon.png");
    window_pause.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
    pause = true;
    while (window_pause.isOpen()) {
        pause_menu_control(window_pause, window);
        if(pause){
            set_fonts();
            draw_main_menu(window_pause);
            text_menu_items.clear();
            pause = false;
            window_pause.display();
        }
    }
}

void make_move()
{
    game_last_states.push_back(game_state);
    if (game_last_states.size() > 10) {
        game_last_states.erase(game_last_states.begin());
    }

    switch (game_state.snake_direction) {
        case SNAKE_DIRECTION_UP:
            game_state.snake_position_y--;
            if (game_state.snake_position_y < 0) {
                game_state.snake_position_y = field_size_y - 1;
            }
            break;
        case SNAKE_DIRECTION_RIGHT:
            game_state.snake_position_x++;
            if (game_state.snake_position_x > field_size_x - 1) {
                game_state.snake_position_x = 0;
            }
            break;
        case SNAKE_DIRECTION_DOWN:
            game_state.snake_position_y++;
            if (game_state.snake_position_y > field_size_y - 1) {
                game_state.snake_position_y = 0;
            }
            break;
        case SNAKE_DIRECTION_LEFT:
            game_state.snake_position_x--;
            if (game_state.snake_position_x < 0) {
                game_state.snake_position_x = field_size_x - 1;
            }
            break;
    }

    if (game_state.field[game_state.snake_position_y][game_state.snake_position_x] != FIELD_CELL_TYPE_NONE) {
        switch (game_state.field[game_state.snake_position_y][game_state.snake_position_x]) {
            case FIELD_CELL_TYPE_APPLE:
                game_state.last_score++;
                apple_sound.play();
                game_state.score++;
                game_state.snake_length++;
                count_of_apples++;
                if (count_of_apples == n) {
                    add_green_apple();
                    count_of_apples = 0;
                }
                count_of_red_apples++;
                if (count_of_red_apples == 5) {
                    add_heart();
                }
                if (game_state.score != 0 && game_state.score % 15 == 0) {
                    add_yellow_apple();
                }
                grow_snake();
                add_apple();
                break;
            case FIELD_CELL_TYPE_GREEN_APPLE:
                green_apple_sound.play();
                count_of_red_apples = 0;
                count_of_apples = 0;
                random_event();
                event_green = true;
                if (lives_color == 0) {
                    x = 50; y = 185; z = 50;
                }
                break;
            case FIELD_CELL_TYPE_YELLOW_APPLE:
                yellow_apple_sound.play();
                event_yellow = true;
                if (random_bonus() == 1) {
                    for (int m = 0; m < 2; m++) {
                        add_heart();
                    }
                }
                break;
            case FIELD_CELL_TYPE_HEART:
                count_of_hearts++;

                if(count_of_hearts != 3) {
                    heart_sound.play();
                }
                else{
                    life_up_sound.play();
                }

                if(count_of_hearts == 3){
                    game_state.count_of_lives++;
                    count_of_hearts = 0;
                }

                if(event_green) {
                    event_green = false;
                }
                normal_game();
                break;
            case FIELD_CELL_TYPE_WALL:
                game_over_sound.play();
                if (game_state.count_of_lives != 0) {
                    roll_back = true;
                    if (event_yellow) {
                        lives_color--;
                        switch (lives_color) {
                            case 4:
                                x = 255; y = 20; z = 147;
                                break;
                            case 3:
                                x = 255; y = 140; z = 0;
                                break;
                            case 2:
                                x = 139; y = 0; z = 139;
                                break;
                            case 1:
                                x = 255; y = 215; z = 0;
                                break;
                            default:
                                event_yellow = false;
                                x = r; y = g; z = b;
                        }
                    }

                }
                else {
                    game_over = true;
                }
                break;
            default:
                game_over_sound.play();
                if (game_state.field[game_state.snake_position_y][game_state.snake_position_x] > 1) {
                    if (game_state.count_of_lives != 0) {
                        roll_back = true;
                        if (event_yellow) {
                            //roll_back = true;
                            lives_color--;
                            switch (lives_color) {
                                case 4:
                                    x = 255;
                                    y = 20;
                                    z = 147;
                                    break;
                                case 3:
                                    x = 255;
                                    y = 140;
                                    z = 0;
                                    break;
                                case 2:
                                    x = 139;
                                    y = 0;
                                    z = 139;
                                    break;
                                case 1:
                                    x = 255;
                                    y = 255;
                                    z = 0;
                                    break;
                                default:
                                    x = r;
                                    y = g;
                                    z = b;
                            }
                        }
                    }
                    else {
                        game_over = true;
                    }
                }
        }
    }

    if (!roll_back) {
        for (int j = 0; j < field_size_y; j++) {
            for (int i = 0; i < field_size_x; i++) {
                if (game_state.field[j][i] > FIELD_CELL_TYPE_NONE) {
                    game_state.field[j][i]--;
                }

            }
        }

        game_state.field[game_state.snake_position_y][game_state.snake_position_x] = game_state.snake_length;
    }
}

void start_game()
{
    game_state.snake_position_x = field_size_x / 2;
    game_state.snake_position_y = field_size_y / 2;
    game_state.snake_length = 4;
    game_state.snake_direction = SNAKE_DIRECTION_RIGHT;
    game_state.score = 0;
    choice = 1;
    game_state.last_score = 0;
    game_over = false;
    exit_game = false;
    invert_control = false;
    event_green = false;
    count_of_apples = 0;
    count_of_red_apples = 0;
    game_state.count_of_lives = 0;
    length_increase = false;
    score_decrease = false;
    r = x, g = y, b = z;
    lives_color = 0;
    event_green = false;
    event_yellow = false;
    pause = false;
    color = 1;
    choice_wall = 1;
    win_game = false;
    clear_field();
}

void lose_menu_control(sf::RenderWindow &window_main)
{
    sf::Event event;

    while (window_main.pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Enter:
                    enter_sound.play();
                    switch(lose_color){
                        case 1:
                            lose_color = 1;
                            restart = true;
                            break;
                        case 2:
                            menu_type = 0;
                            color_menu = 0;
                            normal_game();
                            lose_color = 1;
                            restart = false;
                            break;
                        default:
                            break;
                    }
                    window_main.close();
                    break;
                case sf::Keyboard::Down:
                    menu_sound.play();
                    lose_color++;
                    if(lose_color == 3){
                        lose_color = 1;
                    }
                    pause = true;
                    break;
                case sf::Keyboard::Up:
                    menu_sound.play();
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

void open_lose_menu()
{
    sf::RenderWindow window_main(sf::VideoMode(main_menu_width, main_menu_height), "Game over", sf::Style::Close);
    auto image = sf::Image{};
    image.loadFromFile("images/icon.png");
    window_main.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
    pause = true;
    while (window_main.isOpen()) {
        lose_menu_control(window_main);
        if(pause){
            set_fonts();
            draw_main_menu(window_main);
            text_menu_items.clear();
            pause = false;
            window_main.display();
        }
    }
}

void game_control(bool& invert_control, sf::RenderWindow& window)
{
    sf::Event event;
    if (!invert_control) {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed) {
                int snake_direction_last = snake_direction_queue.empty() ? game_state.snake_direction : snake_direction_queue.at(0);
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        if (snake_direction_last != SNAKE_DIRECTION_UP && snake_direction_last != SNAKE_DIRECTION_DOWN && type_of_control != 2) {
                            if (snake_direction_queue.size() < 2) {
                                snake_direction_queue.insert(snake_direction_queue.begin(), SNAKE_DIRECTION_UP);
                            }
                        }
                        break;
                    case sf::Keyboard::Right:
                        if (snake_direction_last != SNAKE_DIRECTION_RIGHT && snake_direction_last != SNAKE_DIRECTION_LEFT && type_of_control != 2) {
                            if (snake_direction_queue.size() < 2) {
                                snake_direction_queue.insert(snake_direction_queue.begin(), SNAKE_DIRECTION_RIGHT);
                            }
                        }
                        break;
                    case sf::Keyboard::Down:
                        if (snake_direction_last != SNAKE_DIRECTION_DOWN && snake_direction_last != SNAKE_DIRECTION_UP && type_of_control != 2) {
                            if (snake_direction_queue.size() < 2) {
                                snake_direction_queue.insert(snake_direction_queue.begin(), SNAKE_DIRECTION_DOWN);
                            }
                        }
                        break;
                    case sf::Keyboard::Left:
                        if (snake_direction_last != SNAKE_DIRECTION_LEFT && snake_direction_last != SNAKE_DIRECTION_RIGHT && type_of_control != 2) {
                            if (snake_direction_queue.size() < 2) {
                                snake_direction_queue.insert(snake_direction_queue.begin(), SNAKE_DIRECTION_LEFT);
                            }
                        }
                        break;
                    case sf::Keyboard::W:
                        if (snake_direction_last != SNAKE_DIRECTION_UP && snake_direction_last != SNAKE_DIRECTION_DOWN && type_of_control == 2) {
                            if (snake_direction_queue.size() < 2) {
                                snake_direction_queue.insert(snake_direction_queue.begin(), SNAKE_DIRECTION_UP);
                            }
                        }
                        break;
                    case sf::Keyboard::D:
                        if (snake_direction_last != SNAKE_DIRECTION_RIGHT && snake_direction_last != SNAKE_DIRECTION_LEFT && type_of_control == 2) {
                            if (snake_direction_queue.size() < 2) {
                                snake_direction_queue.insert(snake_direction_queue.begin(), SNAKE_DIRECTION_RIGHT);
                            }
                        }
                        break;
                    case sf::Keyboard::S:
                        if (snake_direction_last != SNAKE_DIRECTION_DOWN && snake_direction_last != SNAKE_DIRECTION_UP && type_of_control == 2) {
                            if (snake_direction_queue.size() < 2) {
                                snake_direction_queue.insert(snake_direction_queue.begin(), SNAKE_DIRECTION_DOWN);
                            }
                        }
                        break;
                    case sf::Keyboard::A:
                        if (snake_direction_last != SNAKE_DIRECTION_LEFT && snake_direction_last != SNAKE_DIRECTION_RIGHT && type_of_control == 2) {
                            if (snake_direction_queue.size() < 2) {
                                snake_direction_queue.insert(snake_direction_queue.begin(), SNAKE_DIRECTION_LEFT);
                            }
                        }
                        break;
                    case sf::Keyboard::Space:
                        menu_type = 5;
                        game_paused = true;
                        break;
                    case sf::Keyboard::Tab:
                        game_music.stop();
                        break;
                    case sf::Keyboard::X:
                        game_music.setLoop(true);
                        game_music.play();
                        break;
                }
            }
        }
    }
    else {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                int snake_direction_last = snake_direction_queue.empty() ? game_state.snake_direction : snake_direction_queue.at(0);
                switch (event.key.code) {
                    case sf::Keyboard::Down:
                        if (snake_direction_last != SNAKE_DIRECTION_UP && snake_direction_last != SNAKE_DIRECTION_DOWN && type_of_control != 2) {
                            if (snake_direction_queue.size() < 2) {
                                snake_direction_queue.insert(snake_direction_queue.begin(), SNAKE_DIRECTION_UP);
                            }
                        }
                        break;
                    case sf::Keyboard::Up:
                        if (snake_direction_last != SNAKE_DIRECTION_DOWN && snake_direction_last != SNAKE_DIRECTION_UP && type_of_control != 2) {
                            if (snake_direction_queue.size() < 2) {
                                snake_direction_queue.insert(snake_direction_queue.begin(), SNAKE_DIRECTION_DOWN);
                            }
                        }
                        break;
                    case sf::Keyboard::Left:
                        if (snake_direction_last != SNAKE_DIRECTION_RIGHT && snake_direction_last != SNAKE_DIRECTION_LEFT && type_of_control != 2) {
                            if (snake_direction_queue.size() < 2) {
                                snake_direction_queue.insert(snake_direction_queue.begin(), SNAKE_DIRECTION_RIGHT);
                            }
                        }
                        break;
                    case sf::Keyboard::Right:
                        if (snake_direction_last != SNAKE_DIRECTION_LEFT && snake_direction_last != SNAKE_DIRECTION_RIGHT && type_of_control != 2) {
                            if (snake_direction_queue.size() < 2) {
                                snake_direction_queue.insert(snake_direction_queue.begin(), SNAKE_DIRECTION_LEFT);
                            }
                        }
                        break;
                    case sf::Keyboard::W:
                        if (snake_direction_last != SNAKE_DIRECTION_UP && snake_direction_last != SNAKE_DIRECTION_DOWN && type_of_control == 2) {
                            if (snake_direction_queue.size() < 2) {
                                snake_direction_queue.insert(snake_direction_queue.begin(), SNAKE_DIRECTION_DOWN);
                            }
                        }
                        break;
                    case sf::Keyboard::D:
                        if (snake_direction_last != SNAKE_DIRECTION_RIGHT && snake_direction_last != SNAKE_DIRECTION_LEFT && type_of_control == 2) {
                            if (snake_direction_queue.size() < 2) {
                                snake_direction_queue.insert(snake_direction_queue.begin(), SNAKE_DIRECTION_LEFT);
                            }
                        }
                        break;
                    case sf::Keyboard::S:
                        if (snake_direction_last != SNAKE_DIRECTION_DOWN && snake_direction_last != SNAKE_DIRECTION_UP && type_of_control == 2) {
                            if (snake_direction_queue.size() < 2) {
                                snake_direction_queue.insert(snake_direction_queue.begin(), SNAKE_DIRECTION_UP);
                            }
                        }
                        break;
                    case sf::Keyboard::A:
                        if (snake_direction_last != SNAKE_DIRECTION_LEFT && snake_direction_last != SNAKE_DIRECTION_RIGHT && type_of_control == 2) {
                            if (snake_direction_queue.size() < 2) {
                                snake_direction_queue.insert(snake_direction_queue.begin(), SNAKE_DIRECTION_RIGHT);
                            }
                        }
                        break;
                    case sf::Keyboard::Space:
                        menu_type = 5;
                        game_paused = true;
                        break;
                    case sf::Keyboard::Tab:
                        game_music.stop();
                        break;
                    case sf::Keyboard::X:
                        game_music.setLoop(true);
                        game_music.play();
                        break;
                }
            }
        }
    }
}

void check_win() {
    for (int i = 0; i < field_size_y; i++) {
        for (int j = 0; j < field_size_x; j++) {
            if (((game_state.field[i][j] != FIELD_CELL_TYPE_APPLE && game_state.field[i][j] != FIELD_CELL_TYPE_GREEN_APPLE &&
                  game_state.field[i][j] != FIELD_CELL_TYPE_YELLOW_APPLE &&
                  game_state.field[i][j] != FIELD_CELL_TYPE_HEART) ||
                 game_state.field[i][j] == FIELD_CELL_TYPE_WALL) && get_random_empty_cell() == -1) {
                win_game = true;
            }
        }
    }
}

void low_graphics_game()
{
    srand(time(nullptr));

    set_sounds();
    set_volume_level();

    while (true) {
        if(exit_game){
            break;
        }

        if(!restart && new_game){
            open_main_menu();
            r = x; g = y; b = z;
            game_state.speed_last = game_state.speed;
        }

        if(set_op){
            settings_color = 0;
            graphics_color = 0;
            open_settings_menu();
            new_game = false;
        }

        if(menu_type == 3){
            open_control_menu();
            color_of_control = 0;
        }

        if(menu_type == 4){
            open_difficulty_menu();
            difficulty_color = 0;
        }

        if(menu_type == 6){
            open_volume_menu();
        }

        if(!restart && !set_op && !new_game){
            open_main_menu();
            game_state.speed_last = game_state.speed;
            new_game = true;
        }

        if(set_op){
            settings_color = 0;
            graphics_color = 0;
            new_game = false;
            if(high_graphics && graphics_switched){
                high_graphics_game();
                break;
            }
            continue;
        }



        if(menu_type == 7){
            open_level_menu();
            level_color = 0;
            color_menu = 0;
        }

        if(op_main){
            op_main = false;
            continue;
        }

        if(menu_type == 8){
            open_help_menu();
            color_menu = 0;
        }

        if(op_help){
            op_help = false;
            continue;
        }

        if(exit_game){
            break;
        }

        start_game();

        sf::RenderWindow window(sf::VideoMode(window_width, window_height), "snake", sf::Style::Close);

        auto image = sf::Image{};
        image.loadFromFile("images/icon.png");
        window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());

        game_music.setLoop(true);
        game_music.play();

        while (window.isOpen()) {
            game_control(invert_control, window);

            if (!snake_direction_queue.empty()) {
                game_state.snake_direction = snake_direction_queue.back();
                snake_direction_queue.pop_back();
            }

            if (!game_paused) {
                if (!roll_back) {
                    make_move();
                }
                else {
                    if (!game_last_states.empty()) {
                        game_state = game_last_states.back();
                        game_last_states.pop_back();
                    }
                    else {
                        if(game_state.count_of_lives > 0) {
                            game_state.count_of_lives--;
                        }
                        roll_back = false;
                    }
                }
            }

            if (game_over) {
                if (!roll_back) {
                    game_music.stop();
                    sf::sleep(sf::seconds(1));
                    window.close();
                    lose_color = 1;
                    menu_type = 1;
                }
            }

            if (win_game) {
                game_music.stop();
                sf::sleep(sf::seconds(1));
                window.close();
            }

            if(game_paused){
                game_music.pause();
                open_pause_menu(window);
                new_game = true;
                restart = false;
                game_paused = false;
                pause_color = 1;
            }

            window.clear(sf::Color(x, y, z));
            draw_field(window);

            window.display();

            sf::sleep(sf::milliseconds(game_state.speed));

            check_win();
        }
        if(menu_type != 0) {
            lose_color = 1;
            open_lose_menu();
        }

        if (restart) {
            normal_game();
            lose_color = 1;
            snake_direction_queue.clear();
            game_last_states.clear();
            continue;
        }
    }
}