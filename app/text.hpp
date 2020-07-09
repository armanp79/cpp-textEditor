#ifndef TEXT_HPP
#define TEXT_HPP

#include "Command.hpp"

class Text : public Command
{    
    public:
        Text(char letter);
        void execute(EditorModel& model) override;
        void undo(EditorModel& model) override;
    private:
        char letter;
};

#endif
