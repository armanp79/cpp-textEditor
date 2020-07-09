// EditorModel.cpp
//
// ICS 45C Spring 2020
// Project #4: People Just Love to Play with Words
//
// Implementation of the EditorModel clas

#include "EditorModel.hpp"
#include "EditorException.hpp"
#include <string>
#include <map>
#include <utility>
#include "BooEditLog.hpp"

EditorModel::EditorModel()
{
}


int EditorModel::cursorLine() const
{
    return current_line;
}


int EditorModel::cursorColumn() const
{
    return col;
}

void EditorModel::setCursor(int c)
{
    col = c;
}

void EditorModel::setLine(int l)
{
    current_line = l;
}

int EditorModel::lineCount() const
{
    return wordMap.size();
}


const std::string& EditorModel::line(int lineNumber) const
{
    return wordMap.at(lineNumber);
}

const std::string& EditorModel::currentErrorMessage() const
{
    return error_mess;
}


void EditorModel::setErrorMessage(const std::string& errorMessage)
{
    error_mess = errorMessage;
}


void EditorModel::clearErrorMessage()
{
    error_mess = ""; 
}

// -------------------------------------------------- 
// Functions that move the cursor
// --------------------------------------------------

// Move cursor RIGHT
void EditorModel::moveRight()
{
    // if cursor is at end of line
    if ((col + 1) == (line(current_line).length() + 2))
    {
        if (current_line == lineCount()) // if cursor is on last line
        {
            throw EditorException("Already at end");
        }
        else // go to beginning of next line
        {
            col = 1;
            current_line++;
        }
    }
    else
    {
        col++;
    }
}


// Move cursor LEFT
void EditorModel::moveLeft()
{
    if (col == 1) // if cursor is at beginning of line
    {
        if (current_line == 1) // if cursor is on first line
        {
            throw EditorException("Already at beginning");
        }
        else // go to end of previous line
        {
            col = line(current_line - 1).length() + 1;
            current_line--;
        }
    }
    else
    {
        col--;
    }
}

// Move cursor UP
std::pair<int,int> EditorModel::moveUp()
{
    std::pair <int, int> col_line (cursorColumn(), cursorLine());
    if (cursorLine() != 1)
    {
        if (cursorColumn() > (line(current_line - 1)).length())
        {
            current_line--;
            col = line(current_line).length()+1;
        }
        else
        {
            current_line--;
        }
    }
    else
    {
        throw EditorException("Already at top");
    }
    return col_line;
}

// Move cursor DOWN
std::pair<int,int> EditorModel::moveDown()
{
    std::pair <int, int> col_line (cursorColumn(), cursorLine());
    if (cursorLine() != lineCount())
    {
        if (cursorColumn() > (wordMap[current_line+1]).length() )
        {
            current_line++;
            col = wordMap[current_line].length()+1;
        }
        else
        {
            current_line++;
        }
    }
    else
    {
        throw EditorException("Already at bottom");
    }
    return col_line;
}

// Move cursor HOME
int EditorModel::moveHome()
{
    int old_col = cursorColumn();
    col = 1;
    return old_col;
}

// Move cursor END
int EditorModel::moveEnd()
{
    int old_col = cursorColumn();
    col = line(current_line).length()+1;
    return old_col;
}

// -------------------------------------------------- 
// Functions that add/remove Text
// --------------------------------------------------

void EditorModel::addText(char letter)
{
    std::string oldLine = wordMap[current_line];
    oldLine.insert(cursorColumn()-1,1,letter);
    wordMap[current_line] = oldLine;
    moveRight();
}

char EditorModel::backspace()
{
    char charToDel = 0;
    if (cursorColumn() == 1)
    {
        if (cursorLine() == 1)
        {
            throw EditorException("Already at beginning");
        }
        else
        {
            joinLines();
        }
    }
    else
    {
        charToDel = line(cursorLine()).at(cursorColumn()-2);
        std::string oldLine = wordMap[current_line];
        oldLine.erase(cursorColumn()-2,1);
        wordMap[current_line] = oldLine;
        moveLeft();
    }
    return charToDel;
}

// --------------------------------------------------
// Functions that add/remove Lines
// --------------------------------------------------

void EditorModel::joinLines()
{
    std::map <int, std::string> new_map;
    int new_col = 1;
    for (auto kv:wordMap)
    {
        if (kv.first < current_line-1)
        {
            new_map[kv.first] = kv.second;
        }
        else if (kv.first == current_line -1)
        {
            std::string below = line(current_line);
            new_col = kv.second.length()+1;
            new_map[kv.first] = kv.second + below;
        }
        else if (kv.first == current_line)
        {
        }
        else
        {
            new_map[kv.first-1] = kv.second;
        }   
    }
    wordMap = new_map;
 
    current_line--;
    col = new_col;

}

void EditorModel::insertLine(int line,std::string words)
{
    std::map <int, std::string> new_map;
 
    for (auto kv:wordMap)
    {   
        if (kv.first < line)
        {   
            new_map[kv.first] = kv.second;
        }
        else if (kv.first == line)
        {   
            new_map[kv.first] = words;
            if (lineCount() !=1)
            {
                new_map[kv.first + 1] = kv.second;
            }
        }
        else
        {   
            new_map[kv.first+1] = kv.second;
        }
    }
    if (line > cursorLine())
    {
        new_map[line] = words;
    }
    wordMap = new_map;    

}





void EditorModel::newLine()
{
    if (cursorColumn() == 1) // if cursor is at beginning of line
    {
        std::map <int, std::string> new_map;
        for (auto kv:wordMap)
        {
            if (kv.first < current_line)
            {
                new_map[kv.first] = kv.second;
            }
            else if (kv.first == current_line)
            {
                new_map[kv.first] = "";
                new_map[kv.first+1] = kv.second;
            }
            else
            {
                new_map[kv.first+1] = kv.second;
            }
        }
        wordMap = new_map;
        current_line++;            
    }
    
    else if (cursorColumn() == line(current_line).length()+1) // if cursor is at end of line
    {
        if(cursorLine() != lineCount()) // if you are not on the last line
        {
            std::map <int, std::string> new_map;
            for (auto kv:wordMap)
            {
                if (kv.first < current_line)
                {
                    new_map[kv.first] = kv.second;
                }
                else if (kv.first == current_line)
                {
                    new_map[kv.first] = kv.second;
                    new_map[kv.first+1] = "";
                }
                else
                {
                    new_map[kv.first+1] = kv.second;
                }
            }
            wordMap = new_map;
            current_line++;
            col = 1;
        }
        else
        {
            current_line++;
            col = 1;
            wordMap[current_line] = "";
        }
    }
    else // cursor is in middle of line
    {
        std::map <int, std::string> new_map;
        for (auto kv:wordMap)
        {   
            if (kv.first < current_line)
            {   
                new_map[kv.first] = kv.second;
            }
            else if (kv.first == current_line)
            {
                std::string firstHalf = line(current_line).substr(0, cursorColumn() -1);
                std::string secHalf = line(current_line).substr(cursorColumn()-1);
                new_map[kv.first] = firstHalf;
                new_map[kv.first+1] = secHalf;
            }
            else
            {
                new_map[kv.first+1] = kv.second;
            }
        }
        wordMap = new_map;
        current_line++;
        col = 1;
    }
}

std::vector<std::string> EditorModel::delLine()
{
    //std::string* info = new std::string[3]
    //{line(current_line), std::to_string(cursorColumn()), std::to_string(cursorLine())};
    
    std::vector<std::string> info {line(current_line), std::to_string(cursorColumn()), std::to_string(cursorLine())};

    if (lineCount() != 1)
    {
        std::map <int, std::string> new_map;
        for (auto kv:wordMap)
        {
            if (kv.first < current_line)
            {
                new_map[kv.first] = kv.second;
            }
            else if (kv.first == current_line)
            {
            }
            else
            {
                new_map[kv.first-1] = kv.second;
            }
        }
        wordMap = new_map;
        // find cursor postion
        if (cursorLine()-1 == lineCount()) // if cursor is at bottom
        {
            if (col > line(current_line-1).length())
            {
                current_line--;
                col = line(current_line).length() + 1;
            }
            else
            {
                current_line--;
            }
        }
    }
    else
    {
        if (wordMap[1] == "")
        { throw EditorException("Already empty");}
        
        wordMap[1] = "";
        col = 1;
        current_line = 1;
    }
    return info;
}

