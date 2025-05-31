#include "Adicional.h"

Position2::Position2(int ind,int indj): i{ind}, j{indj}{};

Node::Node(): type{DEFAULT}, position{Position2{0,0}}, F{0}, G{0}, father{nullptr}{};