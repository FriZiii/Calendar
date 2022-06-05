#include "InputOutputManager.h"

bool InputOutputManager::foundFile(int year, int month, int day)
{   
    this->year = year;
    this->month = month;
    this->day = day;

    std::string year_string = std::to_string(year);
    std::string month_string = std::to_string(month);
    std::string day_string = std::to_string(day);

    std::string fileName = year_string + month_string + day_string + ".txt";

    file.open(fileName, std::ios::in | std::ios::out);
    if (file.is_open())
    {
        return true;
    }
    return false;

    file.close();
}

void InputOutputManager::DrawTextFromFile(int year, int month, int day, sf:: Font & font, sf::RenderWindow &window, sf::Color maincolor)
{
    this->year = year;
    this->month = month;
    this->day = day;

    std::string year_string = std::to_string(year);
    std::string month_string = std::to_string(month);
    std::string day_string = std::to_string(day);

    std::string fileName = year_string + month_string + day_string + ".txt";

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setPosition(sf::Vector2f(919.0f, 140.0f));
    text.setFillColor(maincolor);

    std::fstream file_load;
    file_load.open(fileName,std::ios::in | std::ios::out);
    std::string line;

    if (file_load.good() == true)
    {
        while (!file_load.eof())
        {
            getline(file_load, line);
            output += line + '\n';
        }

        file_load.close();
    }

    text.setString(output);
    window.draw(text);
    output = "";

}