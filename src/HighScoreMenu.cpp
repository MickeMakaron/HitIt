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
#include "HighScoreMenu.hpp"
#include "VictoryMenu.hpp"
#include "Text.hpp"
#include "Button.hpp"
#include "TextField.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// STD - C++ Standard Library
#include <sstream>
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Graphics/RenderTarget.hpp"
////////////////////////////////////////////////

HighScoreMenu::HighScoreMenu(StateStack& stack, sf::RenderTarget& target, const std::string& midiFile, unsigned int score)
: MenuState(stack, target)
, mMidiFile(midiFile)
, mScore(score)
, mTextField(nullptr)
{
    sf::Text text;
    text.setFont(Assets::get(ResourceID::Font::OldGateLaneNF));
    text.setCharacterSize(300);
    text.setString("Woohoo!");

    mMenu.insert(new Text(text));


    sf::Color background = sf::Color::White;
    background.a = 180;
    setBackground(background);

    createList();
    loadButtons();
    if(mTextField)
        mTextField->toggleActivation();

    mMenu.setPosition(target.getView().getSize().x / 2.f, target.getView().getSize().y * 2.f / 5.f);
}

////////////////////////////////////////////////

void HighScoreMenu::loadButtons()
{
    sf::Text text;
    text.setFont(Assets::get(ResourceID::Font::OldGateLaneNF));

    text.setCharacterSize(100);
    text.setString("Done");
    Button* done = new Button(text, Assets::get(ResourceID::Sound::Button), [this]()
    {
        if(mTextField)
            mHighScore.insert(mMidiFile, mTextField->getString(), mScore);

        requestStackPop();
        requestStackPush(new VictoryMenu(getStack(), mTarget, mMidiFile));
    });

    sf::FloatRect menuRect = mMenu.getGlobalBounds();
    done->setPosition(menuRect.width / 2.f, mTarget.getView().getSize().y * 6.f / 7.f);
    mMenu.insert(done);
}

////////////////////////////////////////////////

void HighScoreMenu::createList()
{
    sf::FloatRect menuRect = mMenu.getGlobalBounds();
    sf::Vector2f pos(menuRect.width / 2.f, menuRect.height * 1.7f);

    sf::Text text;
    text.setFont(Assets::get(ResourceID::Font::OldGateLaneNF));
    text.setCharacterSize(100);

    std::ostringstream ss;
    ss << "Score: " << mScore;

    std::list<HighScore::Score> scores = mHighScore.getByTrack(mMidiFile);
    if(mHighScore.isNewRecord(scores, mScore))
        ss << "\tNEW!";

    text.setString(ss.str());
    Text* yourScore = new Text(text);
    yourScore->setOrigin(yourScore->getBoundingRect().width / 2.f, yourScore->getBoundingRect().height / 2.f);
    yourScore->setPosition(pos);
    mMenu.insert(yourScore);


    float yIncrement = 50.f;

    pos.y += yIncrement * 2.f;

    text.setCharacterSize(60);
    text.setString("Wall of fame");
    Text* scoreHeader = new Text(text);
    scoreHeader->setOrigin(scoreHeader->getBoundingRect().width / 2.f, scoreHeader->getBoundingRect().height / 2.f);
    scoreHeader->setPosition(pos);
    pos.y += yIncrement * 1.5f;
    mMenu.insert(scoreHeader);



    pos.x = mTarget.getView().getSize().x / 4.f;

    HighScore::Score score;
    score.score = mScore;
    score.name = "Type your name";
    text.setCharacterSize(50);


    auto iScore = mHighScore.insertRecord(scores, score);
    std::list<GUIElement*> entries;
    for(auto it = scores.begin(); it != scores.end(); it++)
    {
        GUIElement* entry;

        text.setString(it->name);
        if(it == iScore)
        {
            mTextField = new TextField(text, Assets::get(ResourceID::Sound::Button), 16);
            entry = mTextField;
        }
        else
            entry = new Text(text);

        entry->setPosition(pos);
        mMenu.insert(entry);


        std::ostringstream ss;
        ss << it->score;
        text.setString(ss.str());
        Text* scoreText = new Text(text);
        scoreText->setPosition(mTarget.getView().getSize().x - pos.x, pos.y);
        mMenu.insert(scoreText);

        pos.y += yIncrement;
    }
}
