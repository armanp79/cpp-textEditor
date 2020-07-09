// KeypressInteractionReader.cpp
//
// ICS 45C Spring 2020
// Project #4: People Just Want to Play with Words
//
// Implementation of the KeypressInteractionReader
//
// YOU WILL NEED TO IMPLEMENT SOME THINGS HERE

#include "KeypressInteractionReader.hpp"
#include "cursorRight.hpp"
#include "cursorLeft.hpp"
#include "text.hpp"
#include "back.hpp"
#include "nline.hpp"
#include "dline.hpp"
#include "moveUp.hpp"
#include "moveDown.hpp"
#include "moveHome.hpp"
#include "moveEnd.hpp"

// You will need to update this member function to watch for the right
// keypresses and build the right kinds of Interactions as a result.
//
// The reason you'll need to implement things here is that you'll need
// to create Command objects, which you'll be declaring and defining
// yourself; they haven't been provided already.
//
// I've added handling for "quit" here, but you'll need to add the others.

Interaction KeypressInteractionReader::nextInteraction()
{
    while (true)
    {
        Keypress keypress = keypressReader.nextKeypress();

        if (keypress.ctrl())
        {
            // The user pressed a Ctrl key (e.g., Ctrl+X); react accordingly

            switch (keypress.code())
            {
            case 'X':
                return Interaction::quit();
            case 'O':
                {
                    Right* r = new Right{};
                    return Interaction::command(r); 
                }
            case 'U':
                {
                    Left* l = new Left{};
                    return Interaction::command(l);
                }
            case 'Z':
                return Interaction::undo();
                
            case 'A':
                return Interaction::redo();
            case 'H':
                {
                    Back* b = new Back{};
                    return Interaction::command(b); 
                }
            case 'J': // case J and M are the same
            case 'M':
                {
                    Nline* n = new Nline{};
                    return Interaction::command(n);
                }
            case 'D':
                {
                    Dline* d = new Dline{};
                    return Interaction::command(d);
                }
            case 'I':
                {
                    Up* u = new Up{};
                    return Interaction::command(u);
                }
            case 'K':
                {   
                    Down* d = new Down{};
                    return Interaction::command(d);
                }
            
            case 'Y':
                {
                    Home* h = new Home{};
                    return Interaction::command(h);
                }
            case 'P':
                {
                    End* e = new End{};
                    return Interaction::command(e);
                }
            }


        }
        else
        {
            // The user pressed a normal key (e.g., 'h') without holding
            // down Ctrl; react accordingly
            char letter = keypress.code();
            Text* t = new Text{letter};
            return Interaction::command(t);
            
        }
    }
}

