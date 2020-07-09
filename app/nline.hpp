#ifndef NLINE_HPP
#define NLINE_HPP

#include "Command.hpp"
class Nline : public Command
{   
    public:
        Nline();
        void execute(EditorModel& model) override;
        void undo(EditorModel& model) override;
    
};

#endif
