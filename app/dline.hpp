#ifndef DLINE_HPP
#define DLINE_HPP

#include "Command.hpp"
#include <string>

class Dline : public Command
{   
    public:
        Dline();
        void execute(EditorModel& model) override;
        void undo(EditorModel& model) override;
    
    private:
        std::string words;
        int line;
        int column;
};

#endif
