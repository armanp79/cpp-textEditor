#ifndef CURSORRIGHT_HPP
#define CURSORRIGHT_HPP

#include "Command.hpp"

class Right : public Command
{
    public:
        Right();
        void execute(EditorModel& model) override;
        void undo(EditorModel& model) override;
};

#endif
