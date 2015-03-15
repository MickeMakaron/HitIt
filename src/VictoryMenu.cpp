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
// STD - C++ Standard Library
#include <sstream>
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "VictoryMenu.hpp"
#include "GameState.hpp"
#include "MainMenu.hpp"
#include "Button.hpp"
#include "Text.hpp"
#include "TrackMenu.hpp"
////////////////////////////////////////////////


VictoryMenu::VictoryMenu(StateStack& stack, sf::RenderTarget& target, const std::string& midiFile, unsigned int score)
: MenuState(stack, target)
, mMidiFile(midiFile)
, mScore(score)
{
    mHighScore.insert(midiFile, "Micke", score);

    sf::Text text;
    text.setFont(Assets::get(ResourceID::Font::OldGateLaneNF));
    text.setCharacterSize(300);
    text.setString("Woohoo!");

    mMenu.insert(new Text(text));
    mMenu.insert(getButtons());
    mMenu.setPosition(target.getView().getSize().x / 2.f, target.getView().getSize().y / 3.f);

    sf::Color background = sf::Color::Black;
    background.a = 120;
    setBackground(background);

    std::list<HighScore::Score> scores = mHighScore.getByTrack(midiFile);
    float y = 300.f;
    for(HighScore::Score score : scores)
    {
        sf::Text text;
        text.setFont(Assets::get(ResourceID::Font::OldGateLaneNF));
        text.setCharacterSize(50);
        std::ostringstream ss;
        ss << score.name << ": " << score.score;
        text.setString(ss.str());

        Text* scoreText = new Text(text);
        scoreText->setPosition(500.f, y);
        y += 50.f;
        mMenu.insert(scoreText);
    }


}

bool VictoryMenu::handleEvent(const sf::Event& event)
{
    MenuState::handleEvent(event);
    return false;
}

std::list<GUIElement*> VictoryMenu::getButtons()
{
    sf::Text buttonText;
    buttonText.setCharacterSize(100);
    buttonText.setFont(Assets::get(ResourceID::Font::OldGateLaneNF));

    buttonText.setString("Play again");
    Button* playSame = new Button
    (
        buttonText,
        mSoundPlayer,
        [this](){requestStackClear(); requestStackPush(new GameState(getStack(), mTarget, mMidiFile));}
    );

    buttonText.setString("Play another track");
    Button* playOther = new Button
    {
        buttonText,
        mSoundPlayer,
        [this](){requestStackClear(); requestStackPush(new TrackMenu(getStack(), mTarget));}
    };

    buttonText.setString("Go to main menu");
    Button* mainMenu = new Button
    (
        buttonText,
        mSoundPlayer,
        [this](){requestStackClear(); requestStackPush(new MainMenu(getStack(), mTarget));}
    );

    buttonText.setString("Insert score");
    Button* insertScore = new Button
    (
        buttonText,
        mSoundPlayer,
        [this](){mHighScore.insert(mMidiFile, "Micke", mScore);}
    );


    sf::FloatRect titleRect = mMenu.getGlobalBounds();
    sf::Vector2f pos(titleRect.width / 2.f, titleRect.height * 2.f);

    float yIncrement = buttonText.getGlobalBounds().height * 1.5f;
    playSame->setPosition(pos);
    pos.y += yIncrement;
    playOther->setPosition(pos);
    pos.y += yIncrement;
    mainMenu->setPosition(pos);
    pos.y += yIncrement;
    insertScore->setPosition(pos);

    return
    {
        playSame,
        playOther,
        mainMenu,
        insertScore,
    };
}


