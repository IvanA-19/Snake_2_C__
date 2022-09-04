#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <vector>

const int skin_cell_size = 32;
const int skin_length = 2;
const int skin_count = 5;
const int skin_choice_height = (skin_length + 4) * skin_cell_size;
const int skin_choice_width = (skin_count + 6) * skin_cell_size;
int choice = 1;
int skin = 0;

int count_of_hearts = 0;

const int wall_cell_size = 32;
const int wall_length = 2;
const int wall_count = 4;
const int wall_choice_height = (wall_length + 3) * wall_cell_size;
const int wall_choice_width = (wall_count + 5) * wall_cell_size;
int choice_wall = 1;
int wall = 0;

const int field_color_cell_size = 32;
const int window_color_height = 256;
const int window_color_width = 256;
bool pause = false;
bool restart = false;
int color = 1;

bool color_pause = true;
bool pause_menu = false;
bool control_pause = false;
bool difficulty_pause = false;
bool game_level_pause = false;
bool help_pause = false;

constexpr auto FIELD_CELL_TYPE_NONE = 0;
constexpr auto FIELD_CELL_TYPE_APPLE = -1;
constexpr auto FIELD_CELL_TYPE_WALL = -2;
constexpr auto FIELD_CELL_TYPE_GREEN_APPLE = -3;
constexpr auto FIELD_CELL_TYPE_HEART = -4;
constexpr auto FIELD_CELL_TYPE_YELLOW_APPLE = -5;

constexpr auto SNAKE_DIRECTION_UP = 0;
constexpr auto SNAKE_DIRECTION_RIGHT = 1;
constexpr auto SNAKE_DIRECTION_DOWN = 2;
constexpr auto SNAKE_DIRECTION_LEFT = 3;

const int field_size_x = 40;
const int field_size_y = 25;
const int cell_size = 32;
const int window_width = field_size_x * cell_size;
const int window_height = field_size_y * cell_size;

const int main_menu_width = 25 * cell_size;
const int main_menu_height = 20 * cell_size;

const int pause_menu_width = 25 * cell_size;
const int pause_menu_height = 15 * cell_size;

const int volume_menu_width = 25 * cell_size;
const int volume_menu_height = 15 * cell_size;

int type_of_control;

std::vector <int> snake_direction_queue;
bool game_over = false;
bool game_paused = false;
int count_of_apples = 0;
const int n = 10;
bool event_green = false;
bool event_yellow = false;
bool invert_control = false;
bool length_increase = false;
bool score_decrease = false;
int count_of_red_apples = 0;
int x = 157, y = 255, z = 212, r, g, b;
bool exit_game;
bool win_game = false;
bool new_game = true;

bool op_help = false;
bool set_op = false;
bool op_main = false;

struct GameState {
    int field[field_size_y][field_size_x];
    int snake_position_x = field_size_x / 2;
    int snake_position_y = field_size_y / 2;
    int snake_length = 4;
    int snake_direction = SNAKE_DIRECTION_RIGHT;
    int score = 0;
    int last_score = 0;
    int speed = 100;
    int speed_last;
    int count_of_lifes = 0;
};

GameState game_state;
std::vector <GameState> game_last_states;
bool rall_back = false;

sf::Font font_menu;

std::vector <sf::Text> text_menu_items;

std::vector <std::string> lose_menu_items{"Your score: ", "Restart", "Exit to main menu", "GAME OVER"};

std::vector<std::string> menu_items = {"Start new game", "Level", "Settings", "Help", "Quit", "SNAKE",
                                       "By Vanyok77797", "Version 4.2.3"};

std::vector <std::string> settings_menu_items{"Type of control", "Field color", "Snake skin", "Walls",
                                    "Difficulty level", "Volume", "Back to main menu", "Game settings"};

std::vector<std::string> control_menu_items = {"Cursors", "W, A, S, D", "Back to settings", "Type of game control"};

std::vector<std::string> difficulty_menu_items = {"Standard", "Easy", "Medium", "Hard", "Crazy", "Impossible",
                                        "Back to settings", "Difficulty level"};

std::vector <std::string> pause_menu_items = {"Score: ", "Resume", "Exit to main menu", "Pause", "Lives: "};

std::vector <std::string> volume_menu_items = {"Volume: ", "Exit to main menu", "Volume settings"};

std::vector <std::string> level_menu_items = {"Level 1", "Level 2", "Level 3", "Level 4", "Level 5",
                                    "Level 6" , "Level 7", "Back to main menu", "Choose level"};

std::vector<std::string> help_menu_items = {"Apples: ", "\t*Green - random trap", "\t*Golden - random bonus",
                                  "\t*Red - food for snake", "Heart - every 5 gives life,\nremoves bad effect",
                                  "Space - game pause", "Tab - to turn off the music",
                                  "X - to turn on the music", "Enter to close help", "Help"};

int color_menu = 0;
int menu_type = 0;
int lose_color = 1;
int settings_color = 0;
int color_of_control = 0;
int difficulty_color = 0;
int pause_color = 1;
int volume_color = 1;
int level_color = 0;
int lifes_color = 0;

int game_level = 0;
int volume_level = 30;
int music_level = 20;

sf::Sound apple_sound;
sf::SoundBuffer apple_buffer;

sf::Sound game_over_sound;
sf::SoundBuffer game_over_buffer;

sf::Sound yellow_apple_sound;
sf::SoundBuffer yellow_apple_buffer;

sf::Sound green_apple_sound;
sf::SoundBuffer green_apple_buffer;

sf::Sound menu_sound;
sf::SoundBuffer menu_buffer;

sf::Sound enter_sound;
sf::SoundBuffer enter_buffer;

sf::Sound heart_sound;
sf::SoundBuffer heart_buffer;

sf::Sound life_up_sound;
sf::SoundBuffer life_up_buffer;

sf::Music game_music;

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
            text_menu_items.back().setString(settings_menu_items.at(7));
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
            text_menu_items.back().setString(pause_menu_items.at(4) + std::to_string(game_state.count_of_lifes));
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
            text_menu_items.back().setString(level_menu_items.at(8));
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
            text_menu_items.at(7).move(menu_position_x -85, 30);
            text_menu_items.at(settings_color).setFillColor(sf::Color(0, 0,255));
            text_menu_items.at(7).setFillColor(sf::Color(255, 255, 0));
            window_main.draw(text_menu_items.at(7));
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
            text_menu_items.at(8).move(menu_position_x - 25, 30);
            text_menu_items.at(level_color).setFillColor(sf::Color(0, 255,255));
            text_menu_items.at(8).setFillColor(sf::Color(0, 255, 0));
            window_main.draw(text_menu_items.at(8));
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
        menu_position_y = 160;
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
        float menu_position_y = 140;
        for (int i = 0; i < level_menu_items.size() - 1; i++) {
            text_menu_items.at(i).move(menu_position_x, menu_position_y - 20);
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
            }
        }
    }
}



void open_control_menu()
{
    sf::RenderWindow window_main(sf::VideoMode(main_menu_width, main_menu_height), "Type of control", sf::Style::Close);
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
    // открытие окна
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
    sf::RenderWindow window_main(sf::VideoMode( main_menu_width, main_menu_height), "Main_menu", sf::Style::Close);
    // открытие окна
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

void chose_window_color(sf::RenderWindow& window_2) //выбор цвета фона
{
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
                if (i != 0 && i != 5) {
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
                }
            }

        }
    }
    draw_arrow_2(window_wall);
}

void choose_wall()
{
    sf::RenderWindow window_wall(sf::VideoMode(wall_choice_width, wall_choice_height), "Wall", sf::Style::Close);
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

void draw_skin_choice(sf::RenderWindow& window_1)
{
    sf::Texture skin_texture;
    sf::Sprite skin;
    for (int i = 0; i < skin_length + 5; i++) {
        for (int j = 0; j < skin_count + 5; j++) {
            switch (i) {
            case 1:
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
                }
                break;
            default:
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
                    }
                }
            }

        }
    }
    draw_arrow(window_1);
}

void choose_skin()
{
    sf::RenderWindow window_1(sf::VideoMode(skin_choice_width, skin_choice_height), "Snake_skin", sf::Style::Close);
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
            }
        }
    }
}

void open_difficulty_menu()
{
    sf::RenderWindow window_main(sf::VideoMode(main_menu_width, main_menu_height), "Difficulty", sf::Style::Close);
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
                            game_level = 4;
                            menu_type = 0;
                            break;
                        case 5:
                            game_level = 5;
                            menu_type = 0;
                            break;
                        case 6:
                            game_level = 6;
                            menu_type = 0;
                            break;
                        case 7:
                            op_main = true;
                            menu_type = 0;
                            break;
                    }
                    window_main.close();
                    break;
                case sf::Keyboard::Down:
                    menu_sound.play();
                    level_color++;
                    if(level_color == 8){
                        level_color = 0;
                    }
                    game_level_pause = true;
                    break;
                case sf::Keyboard::Up:
                    menu_sound.play();
                    level_color--;
                    if(level_color == -1){
                        level_color = 7;
                    }
                    game_level_pause = true;
                    break;
            }
        }
    }
}

void open_level_menu()
{
    sf::RenderWindow window_main(sf::VideoMode(main_menu_width, main_menu_height), "Level", sf::Style::Close);
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
            }
        }
    }
}

void open_volume_menu(){
    sf::RenderWindow window_volume(sf::VideoMode(volume_menu_width, volume_menu_height), "Volume", sf::Style::Close);
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
                            set_op = false;
                            menu_type = 0;
                            color_menu = 0;
                            break;
                    }
                    window_main.close();
                    break;
                case sf::Keyboard::Down:
                    menu_sound.play();
                    settings_color++;
                    if(settings_color == 7){
                        settings_color = 0;
                    }
                    pause = true;
                    break;
                case sf::Keyboard::Up:
                    menu_sound.play();
                    settings_color--;
                    if(settings_color == -1){
                        settings_color = 6;
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
            game_state.field[j][i] = FIELD_CELL_TYPE_NONE;
        }
    }

    for (int i = 0; i < game_state.snake_length; i++)
        game_state.field[game_state.snake_position_y][game_state.snake_position_x - i] = game_state.snake_length - i;


    switch(game_level) {
        case 0:
            for (int i = 0; i < field_size_x; i++) {
                if (i < 10 || field_size_x - i - 1 < 10) {
                    game_state.field[0][i] = FIELD_CELL_TYPE_WALL;
                    game_state.field[field_size_y - 1][i] = FIELD_CELL_TYPE_WALL;
                }
            }
            for (int j = 1; j < field_size_y - 1; j++) {
                if (j < 8 || field_size_y - j - 1 < 8) {
                    game_state.field[j][0] = FIELD_CELL_TYPE_WALL;
                    game_state.field[j][field_size_x - 1] = FIELD_CELL_TYPE_WALL;
                }
            }
            break;
        case 1:
            for (int i = 0; i < field_size_x; i++) {
                game_state.field[0][i] = FIELD_CELL_TYPE_WALL;
                game_state.field[field_size_y - 1][i] = FIELD_CELL_TYPE_WALL;
            }
            for (int j = 1; j < field_size_y - 1; j++) {
                game_state.field[j][0] = FIELD_CELL_TYPE_WALL;
                game_state.field[j][field_size_x - 1] = FIELD_CELL_TYPE_WALL;

            }

            for (int i = 0; i < field_size_x - 10; i++) {
                if (i > 9 && i < 17 || i > 22) {
                    game_state.field[5][i] = FIELD_CELL_TYPE_WALL;
                    game_state.field[field_size_y - 6][i] = FIELD_CELL_TYPE_WALL;
                }
            }
            for (int j = 1; j < field_size_y - 6; j++) {
                if (j > 5 && j < 10 || j > 14 && j < 30) {
                    game_state.field[j][10] = FIELD_CELL_TYPE_WALL;
                    game_state.field[j][field_size_x - 11] = FIELD_CELL_TYPE_WALL;
                }
            }
            break;
        case 2:
            for (int i = 0; i < field_size_y - 1; i++) {
                if(i == 5 || i == 6) {
                    game_state.field[i][6] = FIELD_CELL_TYPE_WALL;
                    game_state.field[i][7] = FIELD_CELL_TYPE_WALL;
                }
                if(i == 18 || i == 19){
                    game_state.field[i][6] = FIELD_CELL_TYPE_WALL;
                    game_state.field[i][7] = FIELD_CELL_TYPE_WALL;
                }
                if (i > 0 && i < 8 || i > 16){
                    game_state.field[i][17] = FIELD_CELL_TYPE_WALL;
                    game_state.field[i][18] = FIELD_CELL_TYPE_WALL;
                }
            }
            for(int j = 31; j < field_size_x - 1; j++){
                game_state.field[8][j] = FIELD_CELL_TYPE_WALL;
                game_state.field[9][j] = FIELD_CELL_TYPE_WALL;
                game_state.field[15][j] = FIELD_CELL_TYPE_WALL;
                game_state.field[16][j] = FIELD_CELL_TYPE_WALL;
            }
            for(int i = 0; i < field_size_x; i++){
                game_state.field[0][i] = FIELD_CELL_TYPE_WALL;
                game_state.field[field_size_y - 1][i] = FIELD_CELL_TYPE_WALL;
            }
            for (int j = 1; j < field_size_y - 1; j++) {
                game_state.field[j][0] = FIELD_CELL_TYPE_WALL;
                game_state.field[j][field_size_x - 1] = FIELD_CELL_TYPE_WALL;
            }
            break;

        case 3:
            for (int i = 0; i < field_size_x; i++) {
                if(i < 15 || i > 24) {
                    game_state.field[0][i] = FIELD_CELL_TYPE_WALL;
                    game_state.field[field_size_y - 1][i] = FIELD_CELL_TYPE_WALL;
                }
                if(i > 14 && i < 25){
                    game_state.field[7][i] = FIELD_CELL_TYPE_WALL;
                }
                if(i > 0 && i < 8 || i == 38){
                    game_state.field[8][i] = FIELD_CELL_TYPE_WALL;
                    game_state.field[16][i] = FIELD_CELL_TYPE_WALL;
                }
            }
            for (int j = 1; j < field_size_y - 1; j++) {
                if(j < 9 || j > 15) {
                    game_state.field[j][0] = FIELD_CELL_TYPE_WALL;
                    game_state.field[j][field_size_x - 1] = FIELD_CELL_TYPE_WALL;
                }
                if(j > 7 && j < 17){
                    game_state.field[j][8] = FIELD_CELL_TYPE_WALL;
                }
                if(j < 8 || j == 23){
                    game_state.field[j][14] = FIELD_CELL_TYPE_WALL;
                    game_state.field[j][25] = FIELD_CELL_TYPE_WALL;
                }
            }
            break;
        case 4:
            for (int i = 0; i < field_size_x; i++) {
                if(i < 17 || i > 22) {
                    game_state.field[0][i] = FIELD_CELL_TYPE_WALL;
                    game_state.field[field_size_y - 1][i] = FIELD_CELL_TYPE_WALL;
                }
                if(i > 4 && i < 16 || i > 23 && i < 35){
                    game_state.field[5][i] = FIELD_CELL_TYPE_WALL;
                    game_state.field[19][i] = FIELD_CELL_TYPE_WALL;
                }
                if(i == 6 || i == 33){
                    game_state.field[4][i] = FIELD_CELL_TYPE_WALL;
                    game_state.field[6][i] = FIELD_CELL_TYPE_WALL;
                    game_state.field[18][i] = FIELD_CELL_TYPE_WALL;
                    game_state.field[20][i] = FIELD_CELL_TYPE_WALL;
                }
                if(i == 9 || i == 11 || i == 28 || i == 30){
                    game_state.field[12][i] = FIELD_CELL_TYPE_WALL;
                }
            }
            for (int j = 1; j < field_size_y - 1; j++) {
                if(j < 10 || j > 14) {
                    game_state.field[j][0] = FIELD_CELL_TYPE_WALL;
                    game_state.field[j][field_size_x - 1] = FIELD_CELL_TYPE_WALL;
                }
                if(j < 10 || j > 14){
                    game_state.field[j][5] = FIELD_CELL_TYPE_WALL;
                    game_state.field[j][34] = FIELD_CELL_TYPE_WALL;
                }
                if(j > 4 && j < 10 || j < 20 && j > 14){
                    game_state.field[j][16] = FIELD_CELL_TYPE_WALL;
                    game_state.field[j][23] = FIELD_CELL_TYPE_WALL;
                }
                if(j > 10 && j < 14){
                    game_state.field[j][10] = FIELD_CELL_TYPE_WALL;
                    game_state.field[j][29] = FIELD_CELL_TYPE_WALL;
                }
            }
            break;
        case 5:
            for (int i = 0; i < field_size_x; i++) {
                game_state.field[0][i] = FIELD_CELL_TYPE_WALL;
                game_state.field[field_size_y - 1][i] = FIELD_CELL_TYPE_WALL;
                if(i > 3 && i < 18 || i > 21 && i < 36){
                    game_state.field[3][i] = FIELD_CELL_TYPE_WALL;
                    game_state.field[21][i] = FIELD_CELL_TYPE_WALL;
                }
                if(i > 6 && i < 34){
                    game_state.field[6][i] = FIELD_CELL_TYPE_WALL;
                    game_state.field[18][i] = FIELD_CELL_TYPE_WALL;
                }
                if(i > 9 && i < 18 || i > 21 && i < 30){
                    game_state.field[9][i] = FIELD_CELL_TYPE_WALL;
                    game_state.field[15][i] = FIELD_CELL_TYPE_WALL;
                }
            }
            for (int j = 1; j < field_size_y - 1; j++) {
                if(j < 11 || j > 13) {
                    game_state.field[j][0] = FIELD_CELL_TYPE_WALL;
                    game_state.field[j][field_size_x - 1] = FIELD_CELL_TYPE_WALL;
                }
                if(j > 2 && j < 22){
                    game_state.field[j][3] = FIELD_CELL_TYPE_WALL;
                    game_state.field[j][36] = FIELD_CELL_TYPE_WALL;
                }
                if(j > 5 && j < 11 || j > 13 && j < 19){
                    game_state.field[j][6] = FIELD_CELL_TYPE_WALL;
                    game_state.field[j][33] = FIELD_CELL_TYPE_WALL;
                }
                if(j > 8 && j < 16){
                    game_state.field[j][9] = FIELD_CELL_TYPE_WALL;
                    game_state.field[j][30] = FIELD_CELL_TYPE_WALL;
                }
            }
            break;
        case 6:
            for(int i = 0; i < field_size_x; i++){
                game_state.field[0][i] = FIELD_CELL_TYPE_WALL;
                game_state.field[field_size_y - 1][i] = FIELD_CELL_TYPE_WALL;
                if(i > 3 && i < 16){
                    game_state.field[15][i] = FIELD_CELL_TYPE_WALL;
                    game_state.field[9][i] = FIELD_CELL_TYPE_WALL;
                }
                if(i > 5 && i < 14){
                    game_state.field[18][i] = FIELD_CELL_TYPE_WALL;
                    game_state.field[6][i] = FIELD_CELL_TYPE_WALL;
                }
                if(i > 3 && i < 13){
                    game_state.field[21][i] = FIELD_CELL_TYPE_WALL;
                    game_state.field[3][i] = FIELD_CELL_TYPE_WALL;
                }
                if(i > 16 && i < 37){
                    game_state.field[9][i] = FIELD_CELL_TYPE_WALL;
                    game_state.field[15][i] = FIELD_CELL_TYPE_WALL;
                }
                if(i > 18 && i < 37){
                    game_state.field[3][i] = FIELD_CELL_TYPE_WALL;
                    game_state.field[21][i] = FIELD_CELL_TYPE_WALL;
                }
                if(i > 19 && i < 34){
                    game_state.field[6][i] = FIELD_CELL_TYPE_WALL;
                    game_state.field[18][i] = FIELD_CELL_TYPE_WALL;
                }
            }
            for (int j = 1; j < field_size_y - 1; j++) {
                if(j < 11 || j > 13) {
                    game_state.field[j][0] = FIELD_CELL_TYPE_WALL;
                    game_state.field[j][field_size_x - 1] = FIELD_CELL_TYPE_WALL;
                }
                if(j > 13 && j < 22 || j > 2 && j < 11){
                    game_state.field[j][3] = FIELD_CELL_TYPE_WALL;
                }
                if(j > 13 || j < 11){
                    game_state.field[j][16] = FIELD_CELL_TYPE_WALL;
                }
                if(j > 18 && j < 22 || j > 2 && j < 7){
                    game_state.field[j][13] = FIELD_CELL_TYPE_WALL;
                }
                if(j > 2 && j < 7 || j > 17 && j < 22){
                    game_state.field[j][19] = FIELD_CELL_TYPE_WALL;
                }
                if(j > 2 && j < 11 || j > 13 && j < 21){
                    game_state.field[j][36] = FIELD_CELL_TYPE_WALL;
                }
            }
            break;
    }

    add_green_apple();
    add_apple();
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
    for (int j = 0; j < field_size_y; j++) {
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
    }
}

int random_bonus()
{
    srand(time(nullptr));
    int bonus;

    bonus = rand() % 5;

    switch (bonus) {
    case 0:
        game_state.score += 15;
        break;
    case 1:
        return 1;
        break;
    case 2:
        game_state.speed = 130;
        break;
    case 3:
        if (game_state.snake_length >= 9) {
            game_state.snake_length -= 5;
        }
        break;
    case 4:
        game_state.count_of_lifes += 5;
        x = 0; y = 220; z = 255;
        event_yellow = true;
        lifes_color = 5;
        break;
    }
}

void normal_game()
{
    game_state.speed = game_state.speed_last;
    if (lifes_color == 0) {
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
            if (!event_yellow) {
                x = 50; y = 185; z = 50;
            }
            break;
        case FIELD_CELL_TYPE_YELLOW_APPLE:
            yellow_apple_sound.play();
            if (random_bonus() == 1) {
                for (int m = 0; m < 2; m++) {
                    add_heart();
                }
            }
            break;
        case FIELD_CELL_TYPE_HEART:
            count_of_hearts++;

            if(count_of_hearts != 5) {
                heart_sound.play();
            }
            else{
                life_up_sound.play();
            }

            if(count_of_hearts == 5){
                game_state.count_of_lifes++;
                count_of_hearts = 0;
            }

            event_green = false;
            normal_game();

            break;
        case FIELD_CELL_TYPE_WALL:
            game_over_sound.play();
            if (game_state.count_of_lifes != 0) {
                rall_back = true;
                if (event_yellow) {
                    lifes_color--;
                    switch (lifes_color) {
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
                        if(!event_green) {
                            x = r; y = g; z = b;
                        }
                        else{
                            x = 50; y = 185; z = 50;
                        }
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
                if (game_state.count_of_lifes != 0) {
                    rall_back = true;
                    if (event_yellow) {
                        lifes_color--;
                        switch (lifes_color) {
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
                                x = 255; y = 255; z = 0;
                                break;
                            default:
                                event_yellow = false;
                                if(!event_green) {
                                    x = r; y = g; z = b;
                                }
                                else{
                                    x = 50; y = 185; z = 50;
                                }
                        }
                    }
                }
                else {
                    game_over = true;
                }
            }
        }
    }

    if (!rall_back) {
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
    game_state.count_of_lifes = 0;
    length_increase = false;
    score_decrease = false;
    r = x, g = y, b = z;
    lifes_color = 0;
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

int main()
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
            new_game = false;
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

        game_music.setLoop(true);
        game_music.play();

        while (window.isOpen()) {
            game_control(invert_control, window);

            if (!snake_direction_queue.empty()) {
                game_state.snake_direction = snake_direction_queue.back();
                snake_direction_queue.pop_back();
            }

            if (!game_paused) {
                if (!rall_back) {
                    make_move();
                }
                else {
                    if (!game_last_states.empty()) {
                        game_state = game_last_states.back();
                        game_last_states.pop_back();
                    }
                    else {
                        if(game_state.count_of_lifes > 0) {
                            game_state.count_of_lifes--;
                        }
                        rall_back = false;
                    }
                }
            }

            if (game_over) {
                if (!rall_back) {
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

    return 0;
}
