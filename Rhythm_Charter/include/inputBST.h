#ifndef INPUT_BST_H
#define INPUT_BST_H

#include <SFML/Graphics.hpp>

class InputBST
{
private:
    sf::Vector2f val;
    
        
    
public:
    InputBST();

    void importBST();
    void exportBST();
};

#endif