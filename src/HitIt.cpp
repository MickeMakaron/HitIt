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
// HitIt internal headers
#include "HitIt.hpp"
#include "TIME_PER_FRAME.hpp"
#include "MenuThemeState.hpp"
#include "MainMenu.hpp"
#include "Assets.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Window/Event.hpp"
////////////////////////////////////////////////

HitIt::HitIt()
: mWindowSettings(getWindowSettings())
, mWindow(mWindowSettings.mode, mWindowSettings.title, mWindowSettings.style)
{
    updateViewport();

    mWindow.setVerticalSyncEnabled(true);
    mWindow.setMouseCursorVisible(false);
    mWindow.setKeyRepeatEnabled(false);
    TIME_PER_FRAME::setAsSeconds(1/60.f);

    Assets::setDirectory("assets/");

    mStateStack.push(new MenuThemeState(mStateStack, mWindow));
    mStateStack.push(new MainMenu(mStateStack, mWindow));
}

////////////////////////////////////////////////

HitIt::~HitIt()
{
    // Really make sure ALL resources are released.
    Assets::release();
}

////////////////////////////////////////////////

HitIt::WindowSettings HitIt::getWindowSettings() const
{
    /*
     * First set to desktop mode (not fullscreen)
     */
    sf::VideoMode mode = sf::VideoMode::getDesktopMode();
    std::string title = "Hit it!";
    unsigned int style = sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize;

    /*
     * Then search for valid fullscreen mode. If
     * found, set our configuration to that mode.
     */
    for(const sf::VideoMode& fullscreenMode : sf::VideoMode::getFullscreenModes())
        if(fullscreenMode.isValid())
        {
            mode = fullscreenMode;
            style = sf::Style::Fullscreen;
            break;
        }

    return WindowSettings(mode, title, style);
}

////////////////////////////////////////////////

void HitIt::updateViewport()
{
    sf::Vector2u windowSize = mWindow.getSize();
    float squareSize, left, top;
    if(windowSize.x < windowSize.y)
    {
        squareSize = windowSize.x;
        left = 0.f;
        top = ((windowSize.y - squareSize) / 2.f) / windowSize.y;
    }
    else
    {
        squareSize = windowSize.y;
        left = ((windowSize.x - squareSize) / 2.f) / windowSize.x;
        top = 0.f;
    }

    sf::View view;
    view.setViewport(sf::FloatRect(left, top, squareSize / windowSize.x, squareSize / windowSize.y));
    mWindow.setView(view);
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
        else if(event.type == sf::Event::Resized)
            updateViewport();
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
    }
}
