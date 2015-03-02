/****************************************************************
****************************************************************
*
* HitIt - Top-down 2D game where the goal is NOT to hit the music.
* Copyright (C) 2015 Mikael Hernvall (mikael.hernvall@gmail.com)
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
****************************************************************
****************************************************************/

////////////////////////////////////////////////
// C++ Standard Library
#include <sstream>
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Window/Event.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "HitIt.hpp"
#include "TIME_PER_FRAME.hpp"
#include "GameState.hpp"
////////////////////////////////////////////////

HitIt::HitIt(unsigned int sizeX, unsigned int sizeY)
: mWindow(sf::VideoMode(sizeX, sizeY), "Hit it!", sf::Style::Titlebar | sf::Style::Close)
{
    mWindow.setMouseCursorVisible(false);
    TIME_PER_FRAME::setAsSeconds(1/60.f);

    mStateStack.push(new GameState(mStateStack));
}

////////////////////////////////////////////////

void HitIt::processInput()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        mStateStack.handleEvent(event);

        if(event.type == sf::Event::Closed)
            mWindow.close();
    }
}

////////////////////////////////////////////////

void HitIt::render()
{
    mWindow.clear();
    mStateStack.draw();
    mWindow.display();
}

////////////////////////////////////////////////

void HitIt::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time timePerFrame = sf::Time(sf::seconds(TIME_PER_FRAME::seconds()));
    while(mWindow.isOpen())
    {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;
        while (timeSinceLastUpdate > timePerFrame)
        {
            timeSinceLastUpdate -= timePerFrame;
            processInput();
            mStateStack.update();

            if(mStateStack.isEmpty())
                mWindow.close();
        }
        render();

        ////////////////////////////////////////////////
        // DEBUG - FPS COUNTER
        std::ostringstream stream;
        stream << "Hit it! | FPS: " << 1 / dt.asSeconds();
        mWindow.setTitle(stream.str());
        ////////////////////////////////////////////////
    }
}
