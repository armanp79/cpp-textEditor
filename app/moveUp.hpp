#ifndef MOVEUP_HPP
#define MOVEUP_HPP

#include "Command.hpp"
#include <vector>
#include <utility>

class Up : public Command
{   
    public:
        Up();
        void execute(EditorModel& model) override;
        void undo(EditorModel& model) override;
    
    private:
        int rem_cursor;
        int rem_line;
};

#endif
