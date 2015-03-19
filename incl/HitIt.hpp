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

#ifndef HITIT_HITIT_HPP
#define HITIT_HITIT_HPP

////////////////////////////////////////////////
// HitIt internal headers
#include "StateStack.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Graphics/RenderWindow.hpp"
////////////////////////////////////////////////

class HitIt
{
    public:
        /**
         * \brief Constructor
         */
        HitIt();

        /**
         * \brief Destructor
         */
        ~HitIt();

        /**
         * \brief Run main loop
         */
        void run();

    private:
        /**
         * \struct WindowSettings
         *
         * Wrapper for window data, i.e. SFML video mode, window title and SFML window style.
         */
        struct WindowSettings
        {
            /**
             * \brief Constructor
             *
             * \param mode SFML Video mode object
             * \param title Window title
             * \param style SFML window style
             */
            WindowSettings(sf::VideoMode mode, std::string title, unsigned int style) : mode(mode), title(title), style(style){};
            sf::VideoMode   mode;   ///< SFML Video mode object
            std::string     title;  ///< Window title
            unsigned int    style;  ///< SFML window style
        };

        /**
         * \brief Get optimal window configuration for this computer
         *
         * \return window configuration.
         */
        WindowSettings getWindowSettings() const;

        /**
         * \brief Adjust viewport to fit current window settings
         */
        void updateViewport();

        /**
         * \brief Process input from input devices
         */
        void processInput();

        /**
         * \brief Clear, draw and display program graphics
         */
        void render();

    private:
        const sf::Vector2f  M_DRAW_SIZE = sf::Vector2f(1000.f, 1000.f); ///< Default draw size
        WindowSettings      mWindowSettings;                            ///< Optimal window settings for target computer
        sf::RenderWindow    mWindow;                                    ///< SFML window object
        StateStack          mStateStack;                                ///< State stack for program states
};

/************************************************
 * \class HitIt
 *
 * Main application loop. To run the program, declare
 * a HitIt object and call its run function.
 *
************************************************/

#endif // HITIT_HITIT_HPP
