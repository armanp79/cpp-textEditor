#ifndef MOVEHOME_HPP
#define MOVEHOME_HPP

#include "Command.hpp"

class Home : public Command
{   
    public:
        Home();
        void execute(EditorModel& model) override;
        void undo(EditorModel& model) override;
    
    private:
        int rem_cursor;
};

#endif
