// InteractionProcessor.cpp
//
// ICS 45C Spring 2020
// Project #4: People Just Love to Play with Words
//
// Implementation of the InteractionProcessor class

#include <vector>
#include <string>
#include "InteractionProcessor.hpp"
#include "EditorException.hpp"
#include "Interaction.hpp"
#include "Command.hpp"

// This function implements command execution, but does not handle "undo"
// and "redo"; you'll need to add that handling.

void InteractionProcessor::run()
{
    view.refresh();
    // Vector to keep track of all commands
    std::vector<Command*> pc;
    // Index to keep track of which command to undo or redo in vector
    int index = 0;

    while (true)
    {
        Interaction interaction = interactionReader.nextInteraction();

        if (interaction.type() == InteractionType::quit)
        {
            for (Command* i : pc) // deallocate all commands upon termination
            {
                delete i;
            }
            break;
        }
        else if (interaction.type() == InteractionType::undo)
        {
            if (index > 0)
            {
                Command* command = pc.at(index-1);
                try
                {
                    command->undo(model);
                    model.clearErrorMessage();
                    index--;
                }
                catch (EditorException& e)
                {
                    model.setErrorMessage(e.getReason());
                }
                view.refresh();
            }
        }
        else if (interaction.type() == InteractionType::redo)
        {
            if (index < pc.size())
            {
                Command* command = pc.at(index);
                try
                {
                 
                    command->execute(model);
                    model.clearErrorMessage();
                    index++;
                }
                catch (EditorException& e)
                {
                    model.setErrorMessage(e.getReason());
                }
                view.refresh();
            }
        }
        else if (interaction.type() == InteractionType::command)
        {
            Command* command = interaction.command();

            try
            {
                
                command->execute(model);
                model.clearErrorMessage();
                

                if (index != pc.size())
                {
                    // adjust previous command vector.
                    for (int i =0; i < (pc.size() - index);i++)
                    {
                        delete pc.back();
                        pc.pop_back();
                    }
                    pc.push_back(command);
                    index++;
                }
                else
                {
                    pc.push_back(command);
                    index++;
                }
            }
            catch (EditorException& e)
            {
                model.setErrorMessage(e.getReason());
            }

            view.refresh();

        }
    }
}

