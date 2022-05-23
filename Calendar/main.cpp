#include <SFML/Graphics.hpp>

#include "LeftBar.h"
#include "Background.h"
#include "DaysOfTheWeek.h"
#include "DaysBoxes.h"
#include "Button.h"
#include "Logo.h"
#include "MonthAndYear.h"
#include "Functions.h"

#include <vector>
#include <time.h>

#pragma warning(disable : 4996)

int main()
{
    //Antialiasing
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    //Window
    sf::RenderWindow window(sf::VideoMode(1200, 610), "Calendar", 4U, settings);

    //Logo
    Logo logo;

    //Left bar
    LeftBar left;

    //Background
    Background background;

    //Font
    sf::Font font; font.loadFromFile("Fonts/WILD_WORLD.otf");

    //Month and Year

        //Getting actual month and year
        time_t theTime = time(NULL);
        struct tm* aTime = localtime(&theTime);
        int month = aTime->tm_mon + 1;
        int year = aTime->tm_year + 1900;

    MonthAndYear monthAndYear(month, year, font);

    //Days of the week
    std::vector<DaysOfTheWeek>daysoftheweek;

    for (int i = 0; i <= 6; i++)
    {
        sf::Vector2f position(293 + i * (68 + 20), 121);
        daysoftheweek.push_back(DaysOfTheWeek(i, position, font));
    }

    //Boxes of the day
    std::vector<DaysBoxes>daysboxes;

    int daysCount = 0;
    int weekDay = zellerArgorithm(monthAndYear.GetMonth(), monthAndYear.GetYear());
    for (int i = 0; i <= 5; i++)
    {
        for (int j = 0; j <= 6; j++)
        {
            if (daysCount < DaysCount(monthAndYear.GetMonth(), monthAndYear.GetYear()))
            {
                daysCount++;
            }
            else
            {
                daysCount = 50;
            }

            sf::Vector2f position(293 + j * (68 + 20), 151 + i * 72);
            daysboxes.push_back(DaysBoxes(position, font, daysCount, weekDay));
            weekDay--;
        }
    }

    //Buttons left bar
    std::vector<Button>button;
    button.push_back(Button(sf::Vector2f(20, 190), font, "HOME"));
    button.push_back(Button(sf::Vector2f(20, 290), font, "SETTINGS"));
    button.push_back(Button(sf::Vector2f(20, 390), font, "CREDITS"));
    button.push_back(Button(sf::Vector2f(20, 490), font, "EXIT"));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //Updates
        for (Button& button : button)
            button.Update(window);

        if (button[3].IsClicked(window))
            window.close();

        monthAndYear.Update(window);

        int daysCount = 0;
        int weekDay = zellerArgorithm(monthAndYear.GetMonth(), monthAndYear.GetYear());
        for (DaysBoxes& daysboxes : daysboxes)
        {
            if (weekDay <= 0)
            {
                if (daysCount < DaysCount(monthAndYear.GetMonth(), monthAndYear.GetYear()))
                    daysCount++;
                else
                    daysCount = 50;
            }
            daysboxes.Update(window ,daysCount , weekDay);
            weekDay--;
        }

        //Draw
        window.clear();

        background.Draw(window);

        for (DaysOfTheWeek& daysoftheweek : daysoftheweek)
            daysoftheweek.Draw(window);

        for (DaysBoxes& daysboxes : daysboxes)
            daysboxes.Draw(window);

        monthAndYear.Draw(window);

        left.Draw(window);

        logo.Draw(window);

        for (Button& button : button)
            button.Draw(window);

        window.display();
    }

    return 0;
}