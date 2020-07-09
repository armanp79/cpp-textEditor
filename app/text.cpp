#include "text.hpp"

Text::Text(char letter)
    : letter{letter}
{
}

void Text::execute(EditorModel& model)
{   
    model.addText(letter);
}       
        
void Text::undo(EditorModel& model)
{
    model.backspace();
}
