#include <SFML/Graphics.hpp> //графическая библиотека
#include <SFML/Audio.hpp>
#include <cstdlib> //стандартная библиотека
#include <vector> //для использования std::vector
#include <windows.h>
#include <string>

using namespace std; //стандартное пространство имен

//Блок константных выражений для стандартных элементов на поле

const int skin_cell_size = 32;
const int skin_length = 2;
const int skin_count = 5; // количество скинов
const int skin_choice_height = (skin_length + 4) * skin_cell_size;
const int skin_choice_width = (skin_count + 6) * skin_cell_size;
int choice = 1;
int skin;

const int wall_cell_size = 32;
const int wall_length = 2;
const int wall_count = 3; // количество скинов
const int wall_choice_height = (wall_length + 3) * wall_cell_size;
const int wall_choice_width = (wall_count + 4) * wall_cell_size;
int choice_wall = 1;
int wall;

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

constexpr auto FIELD_CELL_TYPE_NONE = 0; //пустая клетка
constexpr auto FIELD_CELL_TYPE_APPLE = -1; //яблоко
constexpr auto FIELD_CELL_TYPE_WALL = -2; //стена
constexpr auto FIELD_CELL_TYPE_GREEN_APPLE = -3; //зеленое яблоко
constexpr auto FIELD_CELL_TYPE_HEART = -4; //сердечко
constexpr auto FIELD_CELL_TYPE_YELLOW_APPLE = -5; //желтое яблоко

//направления движения змейки

constexpr auto SNAKE_DIRECTION_UP = 0; //вверх
constexpr auto SNAKE_DIRECTION_RIGHT = 1; //вправо
constexpr auto SNAKE_DIRECTION_DOWN = 2; //вниз
constexpr auto SNAKE_DIRECTION_LEFT = 3; //влево

//размеры поля

const int field_size_x = 40; //количество клеток по длине
const int field_size_y = 25; //количество клеток по высоте
const int cell_size = 32; //размер клетки
const int window_width = field_size_x * cell_size; //длина поля
const int window_height = field_size_y * cell_size; //высота поля

const int main_menu_width = 25 * cell_size;
const int main_menu_height = 20 * cell_size;

const int pause_menu_width = 25 * cell_size;
const int pause_menu_height = 15 * cell_size;

const int volume_menu_width = 25 * cell_size;
const int volume_menu_height = 15 * cell_size;

int type_of_control; //вид управления

vector <int> snake_direction_queue; //массив для буфферизации управления, чтобы можно было лучше координировать змейку и делать более удобные маневры
int last_score = 0;
int score = 0; //переменная для подсчета количества очков
bool game_over = false; //переменнная, отвечающая за конец игры
bool game_paused = false; //переменная, отвечающая за паузу
int count_of_apples = 0; //количество яблок, необходимое для генерации других предметов
const int n = 10; //константа для генерации зеленого яблока
bool event_green = false; //случай съедения зеленого яблока
int speed = 100; //скорость змейки
int speed_last; //скорость по умолчанию
bool invert_control = false; //инверсия управления
bool length_increase = false; //увеличение длины
bool score_decrease = false; //уменьшение длины
int count_of_red_apples = 0; //количество красных яблок. Для генерации некоторы предметов
int x = 157, y = 255, z = 212, r, g, b; //цвет поля
int count_of_lives = 0; //количество жизней при неуязвимости
bool exit_game; // переменная, отвечающая за выход
bool immortality = false; // переменная, отвечающая за бессмертие
bool win_game = false;
bool new_game = true;

//структура с характеристиками змейкм

struct GameState {
    int field[field_size_y][field_size_x]; //матрица, задающая поле
    int snake_position_x = field_size_x / 2; //позиция змейки по x
    int snake_position_y = field_size_y / 2; //позицция змейки по y
    int snake_length = 4; //длиня змейки, равная изначально 4
    int snake_direction = SNAKE_DIRECTION_RIGHT; //направление движения, изначально вправо
};

GameState game_state; //текущая стадия игры
vector <GameState> game_last_states; //массив с сохранением стадии для отката назад
bool rall_back = false; //откат назад

sf::Font font_menu;
vector <sf::Text> text_menu_items;
vector <string> lose_menu_items{"Your score: ", "Restart", "Exit to main menu", "GAME OVER"};
vector<string> menu_items = {"Start new game", "Settings", "Quit", "SNAKE"};
vector <string> settings_menu_items{"Type of control", "Field color", "Snake skin", "Walls", "Difficulty level", "Volume", "Back to main menu", "Game settings"};
vector<string> control_menu_items = {"Cursors", "W, A, S, D", "Back to settings", "Type of game control"};
vector<string> difficulty_menu_items = {"Standart", "Yeasy", "Medium", "Hard", "Crazy", "Impossible", "Back to settings", "Difficulty level"};
vector <string> pause_menu_items = {"Score: ", "Resume", "Exit to main menu", "Pause"};
vector <string> volume_menu_items = {"Volume: ", "Exit to main menu", "Volume settings"};

bool set_op = false;

int color_menu = 0;
int menu_type = 0;
int lose_color = 1;
int settings_color = 0;
int color_of_control = 0;
int difficulty_color = 0;
int pause_color = 1;
int volume_color = 1;

int volume_level = 30;

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

void set_sounds(){
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
}

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
            for (int i = 0; i < lose_menu_items.size() - 1; i++) {
                text_menu_items.emplace_back(sf::Text());
                if(i != 0) {
                    text_menu_items.back().setString(lose_menu_items.at(i));
                }
                else{
                    text_menu_items.back().setString(lose_menu_items.at(i) + to_string(score));
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
            for (int i = 0; i < pause_menu_items.size() - 1; i++) {
                text_menu_items.emplace_back(sf::Text());
                if(i != 0) {
                    text_menu_items.back().setString(pause_menu_items.at(i));
                }
                else{
                    text_menu_items.back().setString(pause_menu_items.at(i) + to_string(score));
                }
                text_menu_items.back().setFont(font_menu);
                text_menu_items.back().setCharacterSize(40);
            }
            text_menu_items.emplace_back(sf::Text());
            text_menu_items.back().setString(pause_menu_items.at(3));
            text_menu_items.back().setFont(font_menu);
            text_menu_items.back().setCharacterSize(70);
            break;
        case 6:
            for (int i = 0; i < volume_menu_items.size() - 1; i++) {
                text_menu_items.emplace_back(sf::Text());
                if(i != 0) {
                    text_menu_items.back().setString(volume_menu_items.at(i));
                }
                else{
                    text_menu_items.back().setString(volume_menu_items.at(i) + to_string(volume_level) + " %");
                }
                text_menu_items.back().setFont(font_menu);
                text_menu_items.back().setCharacterSize(40);
            }
            text_menu_items.emplace_back(sf::Text());
            text_menu_items.back().setString(volume_menu_items.at(2));
            text_menu_items.back().setFont(font_menu);
            text_menu_items.back().setCharacterSize(50);
            break;
    }
}

void menu_control(sf::RenderWindow& window_main) //выбор цвета фона
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
                    if(color_menu == 3){
                        color_menu = 0;
                    }
                    pause_menu = true;
                    break;
                case sf::Keyboard::Up:
                    menu_sound.play();
                    color_menu--;
                    if(color_menu == -1){
                        color_menu = 2;
                    }
                    pause_menu = true;
                    break;
                case sf::Keyboard::End:
                    if(color_menu == 2){
                        immortality = true;
                    }
                    break;
                case sf::Keyboard::Home:
                    if(color_menu == 2){
                        immortality = false;
                    }
                    break;
                case sf::Keyboard::Enter:
                    switch(color_menu){
                        case 0:
                            window_main.close();
                            break;
                        case 1:
                            menu_type = 2;
                            set_op = true;
                            break;
                        case 2:
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

    const float menu_width = 554;//menu_item_max_width;
    float menu_height = 120;//current_menu_item_offset_y;

    const float menu_position_x = (float(main_menu_width) - menu_width) / 2;
    float menu_position_y = (float(main_menu_height) - menu_height) / 2;

    const float pause_menu_position_x = (float(pause_menu_width) - menu_width) / 2;
    float pause_menu_position_y = (float(pause_menu_height) - menu_height) / 2;

    const float volume_menu_position_x = (float(volume_menu_width) - menu_width) / 2;
    float volume_menu_position_y = (float(volume_menu_height) - menu_height) / 2;

    switch(menu_type){
        case 0:
            window_main.clear(sf::Color(0, 0, 0));
            text_menu_items.at(3).move(menu_position_x + 100, 20);
            text_menu_items.at(3).setFillColor(sf::Color(0, 255,0));
            window_main.draw(text_menu_items.at(3));
            text_menu_items.at(color_menu).setFillColor(sf::Color(255, 255,0));
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
            text_menu_items.at(pause_color).setFillColor(sf::Color(255, 255,0));
            text_menu_items.at(3).setFillColor(sf::Color(255, 0, 0));
            text_menu_items.at(3).move(pause_menu_position_x + 96, 40);
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
    }
    if(menu_type == 0 || menu_type == 1 || menu_type == 3) {
        for (int i = 0; i < menu_items.size() - 1; i++) {
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
        for (int i = 0; i < menu_items.size() - 1; i++) {
            text_menu_items.at(i).move(pause_menu_position_x, pause_menu_position_y);
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
    sf::RenderWindow window_2(sf::VideoMode(window_color_width, window_color_height), "Field", sf::Style::Close); // открытие окна

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
                if (choice_wall != 5) { //изменение количества выборов скина
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
                }
            }

        }
    }
    draw_arrow_2(window_wall);
}

void choose_wall()
{
    sf::RenderWindow window_wall(sf::VideoMode(wall_choice_width, wall_choice_height), "Wall", sf::Style::Close); // открытие окна
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
                if (choice != 9) { //изменение количества выборов скина
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
    sf::RenderWindow window_1(sf::VideoMode(skin_choice_width, skin_choice_height), "Snake_skin", sf::Style::Close); // открытие окна
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
                            speed = 120;
                            break;
                        case 1:
                            menu_type = 2;
                            speed = 90;
                            break;
                        case 2:
                            menu_type = 2;
                            speed = 60;
                            break;
                        case 3:
                            menu_type = 2;
                            speed = 30;
                            break;
                        case 4:
                            menu_type = 2;
                            speed = 15;
                            break;
                        case 5:
                            menu_type = 2;
                            speed = 10;
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
    sf::RenderWindow window_main(sf::VideoMode(main_menu_width, main_menu_height), "Difficulty", sf::Style::Close);// открытие окна
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

void set_volume_level(){
    apple_sound.setVolume(float(volume_level));
    menu_sound.setVolume(float(volume_level));
    game_over_sound.setVolume(float(volume_level));
    yellow_apple_sound.setVolume(float(volume_level));
    green_apple_sound.setVolume(float(volume_level));
    enter_sound.setVolume(float(volume_level));
    heart_sound.setVolume(float(volume_level));
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
                        set_volume_level();
                    }
                    pause = true;
                    break;
                case sf::Keyboard::Up:
                    menu_sound.play();
                    if(volume_level != 100){
                        volume_level += 5;
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
    sf::RenderWindow window_volume(sf::VideoMode(volume_menu_width, volume_menu_height), "Volume", sf::Style::Close);// открытие окна
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
    sf::RenderWindow window_main(sf::VideoMode(main_menu_width, main_menu_height), "Settings", sf::Style::Close);// открытие окна
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

//метод определения случайной пустой клетки для генерации яблок

int get_random_empty_cell()
{
    int empty_cell_count = 0; // количество пустых клеток на данный момент
    for (int j = 0; j < field_size_y; j++) {
        for (int i = 0; i < field_size_x; i++) {
            if (game_state.field[j][i] == FIELD_CELL_TYPE_NONE) {
                empty_cell_count++; // считаем количество пустых клеток
            }
        }
    }

    if (empty_cell_count == 0) {
        empty_cell_count = 1;
    }

    int target_empty_cell_index = rand() % empty_cell_count;
    int empty_cell_index = 0;

    //генерация и поиск случайной пустой клетки из общего количества

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
     // не осталсь пустых клеток
    return -1;
}

//методы получения предметов на поле

void add_apple()
{
    int apple_pos = get_random_empty_cell(); // получение координаты пустой клетки
    if (apple_pos != -1) { //проверка, нашлась ли пустая клетка
        game_state.field[apple_pos / field_size_x][apple_pos % field_size_x] = FIELD_CELL_TYPE_APPLE; // заменяем пустую клетку красным яблоком
    }

}

void add_heart() // метод работает аналогичнго предыдущему
{
    int heart_pos = get_random_empty_cell();
    if (heart_pos != -1) {
        game_state.field[heart_pos / field_size_x][heart_pos % field_size_x] = FIELD_CELL_TYPE_HEART;
    }
}

void add_yellow_apple() // желтое яблоко получаем также
{
    int yellow_apple_pos = get_random_empty_cell();
    if (yellow_apple_pos != -1) {
        game_state.field[yellow_apple_pos / field_size_x][yellow_apple_pos % field_size_x] = FIELD_CELL_TYPE_YELLOW_APPLE;
    }
}

void add_green_apple() //зеленое аналогично
{
    int green_apple_pos = get_random_empty_cell();
    if (green_apple_pos != -1) {
        game_state.field[green_apple_pos / field_size_x][green_apple_pos % field_size_x] = FIELD_CELL_TYPE_GREEN_APPLE;
    }
}

//метод очищения поля для генерации стен, первого зеленого и красного яблока, пустых клеток, змейки на анчальной позиции

void clear_field()
{
    for (int j = 0; j < field_size_y; j++) {
        for (int i = 0; i < field_size_x; i++) {
            game_state.field[j][i] = FIELD_CELL_TYPE_NONE; // генерация пустых клеток
        }
    }

    for (int i = 0; i < game_state.snake_length; i++) //установка позиции змейки в начале
        game_state.field[game_state.snake_position_y][game_state.snake_position_x - i] = game_state.snake_length - i;

    for (int i = 0; i < field_size_x; i++) {
       if (i < 10 || field_size_x - i - 1 < 10) {
           game_state.field[0][i] = FIELD_CELL_TYPE_WALL;
           game_state.field[field_size_y - 1][i] = FIELD_CELL_TYPE_WALL; //генерация горизонтальных стен
       }
    }

    for (int j = 1; j < field_size_y - 1; j++) {
        if (j < 8 || field_size_y - j - 1 < 8) {
           game_state.field[j][0] = FIELD_CELL_TYPE_WALL; // генерация уголка
           game_state.field[j][field_size_x - 1] = FIELD_CELL_TYPE_WALL; // генерация вертикальных стен
        }
    }

    add_green_apple(); // генерация зеленого ябллока
    add_apple(); // генерация красного яблока
}

//метод отрисовки поля

void draw_field(sf::RenderWindow& window)
{
    sf::Texture none_texture; //текстура пустой клетки
    none_texture.loadFromFile("images/none.png"); //загрузка изображения пустой клетки
    sf::Sprite none; //спрайт пустой клетки
    none.setTexture(none_texture); //установка текстуры

    // skeens
    sf::Texture snake_texture; //текстура змейки
    sf::Sprite snake; // спрайт

    sf::Texture snake_head_texture; //текстура головы змйки
    sf::Sprite snake_head; //спрайт

    switch (skin) {
    case 1:
        snake_texture.loadFromFile("images/snake_1.png"); //загрузка элеимента змейки
        snake.setTexture(snake_texture); //установка текстуры

        snake_head_texture.loadFromFile("images/head_1.png"); //загрузка ищображения
        snake_head.setTexture(snake_head_texture); //установка текстуры
        break;
    case 2:
        snake_texture.loadFromFile("images/snake_2.png"); //загрузка элеимента змейки
        snake.setTexture(snake_texture); //установка текстуры

        snake_head_texture.loadFromFile("images/head_2.png"); //загрузка ищображения
        snake_head.setTexture(snake_head_texture); //установка текстуры
        break;
    case 3:
        snake_texture.loadFromFile("images/snake_3.png"); //загрузка элеимента змейки
        snake.setTexture(snake_texture); //установка текстуры

        snake_head_texture.loadFromFile("images/head_3.png"); //загрузка ищображения
        snake_head.setTexture(snake_head_texture); //установка текстуры
        break;
    case 4:
        snake_texture.loadFromFile("images/snake_4.png"); //загрузка элеимента змейки
        snake.setTexture(snake_texture); //установка текстуры

        snake_head_texture.loadFromFile("images/head_4.png"); //загрузка ищображения
        snake_head.setTexture(snake_head_texture); //установка текстуры
        break;
    default:
        snake_texture.loadFromFile("images/snake.png"); //загрузка элеимента змейки
        snake.setTexture(snake_texture); //установка текстуры

        snake_head_texture.loadFromFile("images/head.png"); //загрузка ищображения
        snake_head.setTexture(snake_head_texture); //установка текстуры
    }

    sf::Texture apple_texture; //текстура красного яблока
    apple_texture.loadFromFile("images/apple.png"); //загрузка изображения
    sf::Sprite apple; //спрайт
    apple.setTexture(apple_texture); //установка текстуры

    sf::Texture apple_green_texture; //текстура зеленого яблока
    apple_green_texture.loadFromFile("images/apple_green.png"); //загрузка изображения
    sf::Sprite apple_green; //спрайт
    apple_green.setTexture(apple_green_texture); //установка текстуры

    sf::Texture apple_yellow_texture; //текстура желтого яблока
    apple_yellow_texture.loadFromFile("images/yelow_apple.png"); //загрузка изображения
    sf::Sprite apple_yellow; //спрайт
    apple_yellow.setTexture(apple_yellow_texture); //установка текстуры

    sf::Texture wall_texture; //текстура стены // // // // // //
    switch (wall) {
    case 1:
        wall_texture.loadFromFile("images/wall_2.png"); //загрузка изображения
        break;
    case 2:
        wall_texture.loadFromFile("images/wall_3.png"); //загрузка изображения
        break;
    default:
        wall_texture.loadFromFile("images/wall.png");
    }

    sf::Sprite wall; //спрайт
    wall.setTexture(wall_texture); //установка текстуры

    sf::Texture heart_texture; //текстура сердечка
    heart_texture.loadFromFile("images/life.png"); //загрузка изображения
    sf::Sprite heart; //спрайт
    heart.setTexture(heart_texture); //установка текстуры

    for (int j = 0; j < field_size_y; j++) {
        for (int i = 0; i < field_size_x; i++) {
            switch (game_state.field[j][i]) { //проверяем тип текстуры
            case FIELD_CELL_TYPE_NONE:
                none.setPosition(float(i * cell_size), float(j * cell_size));
                window.draw(none); //отрисовка пустой клетки
                break;
            case FIELD_CELL_TYPE_APPLE:
                apple.setPosition(float(i * cell_size), float(j * cell_size));
                window.draw(apple); //отрисовка красного  яблока
                break;
            case FIELD_CELL_TYPE_GREEN_APPLE:
                apple_green.setPosition(float(i * cell_size), float(j * cell_size));
                window.draw(apple_green); //отрисовка зеленого яблока
                break;
            case FIELD_CELL_TYPE_YELLOW_APPLE:
                apple_yellow.setPosition(float(i * cell_size), float(j * cell_size));
                window.draw(apple_yellow); //отрисовка желтого яблока
                break;
            case FIELD_CELL_TYPE_WALL:
                wall.setPosition(float(i * cell_size), float(j * cell_size));
                window.draw(wall); //отрисовка стены
                break;
            case FIELD_CELL_TYPE_HEART:
                heart.setPosition(float(i * cell_size), float(j * cell_size));
                window.draw(heart); //отрисовка сердечка
                break;
            default:
                if (game_state.field[j][i] == game_state.snake_length) {
                    float offset_x = snake_head.getLocalBounds().width / 2; //установка координат головы змейки
                    float offset_y = snake_head.getLocalBounds().height / 2;
                    snake_head.setPosition(float(i * cell_size + offset_x), float(j * cell_size + offset_y));
                    snake_head.setOrigin(offset_x, offset_y);
                    switch (game_state.snake_direction) { //поворот головы в зависимости от направления
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

                    window.draw(snake_head); // отрисовка головы
                }
                else {
                    snake.setPosition(float(i * cell_size), float(j * cell_size));
                    window.draw(snake); // отрисовка остальной змейки
                }
            }
        }
    }
}

//метод увеличения длины

void grow_snake()
{
    for (int j = 0; j < field_size_y; j++) {
        for (int i = 0; i < field_size_x; i++) {
            if (game_state.field[j][i] > FIELD_CELL_TYPE_NONE) { // проверяем текущую клетку
                game_state.field[j][i]++; // увеличиваем длину змейки
            }
        }
    }
}

//метод получения случайного события при съедении зеленого яблока

void random_event()
{
    srand(time(nullptr));
    int random_trap;
    random_trap = rand() % 4; //генерация случайного числа
    switch (random_trap) {
    case 0:
        invert_control = true; // инверсия управления
        break;
    case 1:
        if (speed > 30) {
            speed = 40; // ускорение
        }
        else{
            switch(speed){
                case 30:
                    speed = 20;
                    break;
                case 15:
                    speed = 10;
                    break;
                case 10:
                    speed = 5;
                    break;
            }
        }
        break;
    case 2:
        if (score >= 10) {
            score -= 10; //уменьшение счета
        }
        else {
            score = 0;
        }
        score_decrease = true; // запоминаем, что счет уменьшен для того, чтобы вернуться в начальное состояние
        break;
    case 3:
        game_state.snake_length += 3; // увеличение длины
        length_increase = true; //запоминаем, что длина была увеличена
        break;
    }
}

//метод получения случайного бонуса при съедении желтого яблока

int random_bonus()
{
    srand(time(nullptr));
    int bonus;
    if (immortality) {
        bonus = rand() % 4; // генерация случайного числа
    }
    else {
        bonus = rand() % 5;
    }
    switch (bonus) {
    case 0:
        score += 15; // увеличение счета
        break;
    case 1:
        return 1;
        break;
    case 2:
        speed = 130; // замедление
        break;
    case 3:
        if (game_state.snake_length >= 9) {
            game_state.snake_length -= 5; //уменьшение длины
        }
        break;
    case 4:
        count_of_lives = 5; // неуязвимость
        x = 0; y = 220; z = 255; // изменнение цвета поля при неуязвимости
        break;
    }
}

//восставновление настроек игры при сбросе эффекта зеленого яблока

void normal_game()
{
    speed = speed_last; // установка начального уровня скорости
    if (count_of_lives == 0) {
        x = r; y = g; z = b; // установка начального цыета поля
    }
    invert_control = false; // выключение инверсии
    if (length_increase) {
        length_increase = false; // переключение переменной, отвечающей за длину
        game_state.snake_length -= 3; // уменьшение длины
    }
    if (score_decrease) {
        score_decrease = false; //переключение переменной, отвечающей за счет
        score = last_score; // уменьшение счета
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
                            game_paused = false;
                            break;
                        case 2:
                            menu_type = 0;
                            window.close();
                            pause_menu = 0;
                            restart = false;
                            immortality = false;
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

//метод, отвечающий за движение и изменение поля

void make_move()
{
    // запоминаем позицию змейки на 10 передвижений

    game_last_states.push_back(game_state);
    if (game_last_states.size() > 10) {
        game_last_states.erase(game_last_states.begin());
    }

    //установка направления движения змейкм

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

    //если змейка с чем-то провзаимодействовала

    if (game_state.field[game_state.snake_position_y][game_state.snake_position_x] != FIELD_CELL_TYPE_NONE) {
        switch (game_state.field[game_state.snake_position_y][game_state.snake_position_x]) {
        case FIELD_CELL_TYPE_APPLE: // случай - яблоко
            last_score++; //предыдущий счет +1
            apple_sound.play();
            score++; //текущий счет +1
            game_state.snake_length++; // увеличение длины на 1
            count_of_apples++; // считаем количество съеденных яблок
            if (count_of_apples == n) { // если их 10 - гененрируем одно зеленое
                add_green_apple();
                count_of_apples = 0; // обнуляем количество съеденных до зеленого яблок
            }
            count_of_red_apples++; // считаем количество съеденных яблок для генерации сердечечка
            if (count_of_red_apples == 5) { // если 5 - гененрируем сердечко
                add_heart();
            }
            if (score != 0 && score % 15 == 0) { //генерация желтого яблока в случае, если съедено 15 красных
                add_yellow_apple();
            }
            grow_snake(); // увеличение змейки
            add_apple(); // генерация нового яблока
            break;
        case FIELD_CELL_TYPE_GREEN_APPLE: // случай - зеленое яблоко
            green_apple_sound.play();
            count_of_red_apples = 0; // подготовка к генерации сердечкка через 5 яблок
            count_of_apples = 0; // установка в 0 отсчета до следующего зеленого яблока
            random_event(); // получение случайной ловушки
            if (count_of_lives == 0 || immortality) { //если не включена неуязвимость или введен код бессмертия
                x = 50; y = 185; z = 50; //изменение цвета поля
            }
            break;
        case FIELD_CELL_TYPE_YELLOW_APPLE: // случай - желтое яблоко
            yellow_apple_sound.play();
            if (random_bonus() == 1) { // получение случайного бонуса
                for (int m = 0; m < 2; m++) {
                    add_heart(); // генерация двух сердечек в случае получения 1 в генераторе случайных чисел
                }
            }
            break;
        case FIELD_CELL_TYPE_HEART: // случай - сердечко
            heart_sound.play();
            normal_game(); // восставновление параметров игры
            if (immortality) {
                x = r; y = g; z = b;
            }
            break;
        case FIELD_CELL_TYPE_WALL: //случай - стена
            game_over_sound.play();
            if (count_of_lives != 0) { //если есть неуязвимость, проверяем, сколько осталось жизней
                rall_back = true; //откат включен
                if (!immortality) {//в случае, если не введен код бессмертия
                    count_of_lives--; // уменьшаем количество жизней
                    switch (count_of_lives) { //меняем фон
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
                        x = r; y = g; z = b;
                    }
                }
                else{
                    count_of_lives = 1;
                }
            }
            else {
                game_over = true;// иначе конец игры
            }
            break;
        default: // аналогично, если врезались в себя
            game_over_sound.play();
            if (game_state.field[game_state.snake_position_y][game_state.snake_position_x] > 1) {
                if (count_of_lives != 0) {
                    rall_back = true;
                    if (!immortality) {
                        count_of_lives--; // уменьшаем количество жизней
                        switch (count_of_lives) { //меняем фон
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
                            x = r; y = g; z = b;
                        }
                    }
                }
                else {
                    game_over = true;
                }
            }
        }
    }

    if (!rall_back) { //перемещение змейки
        for (int j = 0; j < field_size_y; j++) {
            for (int i = 0; i < field_size_x; i++) {
                if (game_state.field[j][i] > FIELD_CELL_TYPE_NONE) {
                    game_state.field[j][i]--;
                }

            }
        }

        game_state.field[game_state.snake_position_y][game_state.snake_position_x] = game_state.snake_length; // бновление информации об игре
    }
}

void start_game() // начало игры
{
    game_state.snake_position_x = field_size_x / 2; // установка змейки на начальную позицию
    game_state.snake_position_y = field_size_y / 2;
    game_state.snake_length = 4; // длина по умолчанию
    game_state.snake_direction = SNAKE_DIRECTION_RIGHT; // начальное направление - вправо
    score = 0; // счет равен 0
    choice = 1;
    last_score = 0; //обновление предыдущего счета
    game_over = false; // обновление значения конца игры
    exit_game = false; //обновление значения выхода из игры
    invert_control = false; // значение по умолчанию для инверсии
    event_green = false; //значение по умолчанию для съедения зеленых яблок
    count_of_apples = 0; //обновление количества яблок
    count_of_red_apples = 0; //обновление количества красных яблок
    count_of_lives = 0; //обновление количества жизней
    length_increase = false;  //значение по умолчанию для увеличения длины
    score_decrease = false; //значение по умолчанию для уменьшения длины
    r = x, g = y, b = z;
    pause = false;
    color = 1;
    choice_wall = 1;
    win_game = false;
    clear_field(); // очищение поля
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

//метод управления игрой

void game_control(bool& invert_control, sf::RenderWindow& window)
{
    sf::Event event;
    if (!invert_control) { // если управление инвертировано
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed) {
                int snake_direction_last = snake_direction_queue.empty() ? game_state.snake_direction : snake_direction_queue.at(0);
                switch (event.key.code) { // проверка нажатия той или иной клавиши
                case sf::Keyboard::Up:
                    if (snake_direction_last != SNAKE_DIRECTION_UP && snake_direction_last != SNAKE_DIRECTION_DOWN && type_of_control != 2) { // проверка направления, чтобы не врезаться в себя в обратную
                        //сторону. изменение направления движения. для остальных клавиш аналогично
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
                case sf::Keyboard::Space: // пробел
                    menu_type = 5;
                    game_paused = true; // установка игры на паузу
                    break;
                }
            }
        }
    }
    else { // аналогично для классического кправления
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
                    game_paused = true; // установка игры на паузу
                    break;
                }
            }
        }
    }
}


void check_win() {
    for (int i = 0; i < field_size_y; i++) {
        for (int j = 0; j < field_size_x; j++) {
            if (((game_state.field[i][j] != FIELD_CELL_TYPE_APPLE && game_state.field[i][j] != FIELD_CELL_TYPE_GREEN_APPLE && game_state.field[i][j] != FIELD_CELL_TYPE_YELLOW_APPLE && game_state.field[i][j] != FIELD_CELL_TYPE_HEART) || game_state.field[i][j] == FIELD_CELL_TYPE_WALL) && get_random_empty_cell() == -1) {
                win_game = true;
            }
        }
    }
}

int main() // main
{
    srand(time(nullptr)); //рандомизация

    set_sounds();
    set_volume_level();

    while (true) {
        if(exit_game){
            break;
        }

        // начало игры

        if(!restart && new_game){
            open_main_menu();
            r = x; g = y; b = z;
            speed_last = speed;
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
            speed_last = speed;
            new_game = true;
        }

        if(set_op){
            settings_color = 0;
            new_game = false;
            continue;
        }

        if(exit_game){
            break;
        }

        start_game();
        // скорость по умолчанию

        sf::RenderWindow window(sf::VideoMode(window_width, window_height), "snake", sf::Style::Close); // открытие окна

        while (window.isOpen()) { // пока окно открыто
            game_control(invert_control, window); // подключение управления

            if (!snake_direction_queue.empty()) { // буферизация управления
                game_state.snake_direction = snake_direction_queue.back();
                snake_direction_queue.pop_back();
            }

            if(immortality){
                count_of_lives = 1;
            }

            if (!game_paused) { //если не пауза
                if (!rall_back) { // если не откат
                    make_move(); //обновляем поле
                }
                else {
                    if (!game_last_states.empty()) { //откат
                        game_state = game_last_states.back();
                        game_last_states.pop_back();
                    }
                    else {
                        rall_back = false; // выключение отката
                    }
                }
            }

            if (game_over) { // если не откат и конец игры
                if (!rall_back) {
                    window.clear(sf::Color(255, 0, 0));
                    sf::sleep(sf::seconds(1)); // задержка на 1 секунду
                    window.close(); // закрытие окна
                    lose_color = 1;
                    menu_type = 1;
                }
            }

            if (win_game) {
                sf::sleep(sf::seconds(1)); // задержка на 1 секунду
                window.close();
            }

            if(game_paused){
                open_pause_menu(window);
                new_game = true;
                restart = false;
                game_paused = false;
                pause_color = 1;
            }

            window.clear(sf::Color(x, y, z)); //цвет поля
            draw_field(window); // отрисовка поля

            window.display(); // вывод окна

            sf::sleep(sf::milliseconds(speed)); // скорость

            check_win();
        }
        if(menu_type != 0) {
            lose_color = 1;
            open_lose_menu();
        }

        if (restart) {
            normal_game();
            immortality = false;
            lose_color = 1;
            snake_direction_queue.clear(); // очищение буфера уапрввления при начале новой игры
            game_last_states.clear(); //очищение буфера состояний игры
            continue; //возврат в начало цикла и начало новой игры
        }
    }

    return 0;
}
