#ifndef MOVEEND_HPP
#define MOVEEND_HPP

#include "Command.hpp"
#include <vector>

class End : public Command
{   
    public:
        End();
        void execute(EditorModel& model) override;
        void undo(EditorModel& model) override;
    
    private:
         int rem_cursor;
};

#endif
