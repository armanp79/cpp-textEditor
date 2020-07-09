#ifndef MOVEDOWN_HPP
#define MOVEDOWN_HPP

#include "Command.hpp"

class Down : public Command
{   
    public:
        Down();
        void execute(EditorModel& model) override;
        void undo(EditorModel& model) override;
    
    private:
        int rem_cursor;
        int rem_line;
};

#endif
