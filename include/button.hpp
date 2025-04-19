#ifndef BUTTON_HPP
#define BUTTON_HPP


#include <string>
class Button{
    public:
    // Define the different button states
    enum ButtonState { NORMAL, HOVERED, CLICKED, DISABLED };

    private:
    // Define the button parameters
    int btn_y{0};     // Top row
    int btn_x{0};      // Left column
    int btn_width{0};  // Button width in columns
    int btn_height{0};  // Button height in rows
    std::string btn_text{0}; // Button label
    ButtonState btn_state{NORMAL};

    public:
    int getX(){ return btn_x;}
    int getY(){ return btn_y;}
    int getWidth(){ return btn_width;}
    int getHeight(){ return btn_height;}
    std::string getLabel(){ return btn_text; }
    ButtonState getState(){ return btn_state;}


    // setters
    void setDemension(int width, int height){
        btn_width = width;
        btn_height = height;
    }

    void setOrigin(int x, int y){
        btn_x = x;
        btn_y = y;
    }

    void setText(std::string label){
        btn_text = label;
    }

    void setState(ButtonState state){
        btn_state = state;
    }

};


#endif
