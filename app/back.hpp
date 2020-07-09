#ifndef BACK_HPP
#define BACK_HPP

#include "Command.hpp"

class Back : public Command
{
    public:
        Back();
        void execute(EditorModel& model) override;
        void undo(EditorModel& model) override;
    
    private:
        char deleted;
};

#endif
