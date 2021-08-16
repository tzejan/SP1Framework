#include "Position.h"

Position::Position() : x_axis(0), y_axis(0)
{
}

Position::Position(int x, int y)
{
    if (x > -3 && y > -3 && x < 23 && y < 13) {
        x_axis = x;
        y_axis = y;
    }
    else {
        x_axis = 0;
        y_axis = 0;
    }
}

Position::~Position()
{
}

int Position::get_x_axis()
{
    return x_axis;
}

int Position::get_y_axis()
{
    return y_axis;
}

bool Position::get_out_of_bounds()
{
    if (y_axis < 0 || y_axis > 10 || x_axis < 0 || x_axis > 20) {
        return true;
    }
    return false;
}

void Position::set_x_axis(int x)
{
    x_axis = x;
}

void Position::set_y_axis(int y)
{
    y_axis = y;
}

void Position::set_coordinates(int x, int y)
{
    set_x_axis(x);
    set_y_axis(y);
}

bool Position::is_equal_position(Position& another_pos)
{
    if (another_pos.get_x_axis() != x_axis) return false;
    if (another_pos.get_y_axis() != y_axis) return false;
    return true;
}
