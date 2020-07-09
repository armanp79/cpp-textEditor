#ifndef CURSORLEFT_HPP
#define CURSORLEFT_HPP

#include "Command.hpp"

class Left : public Command
{   
    public:
        Left();
        void execute(EditorModel& model) override;
        void undo(EditorModel& model) override;
};

#endif         
