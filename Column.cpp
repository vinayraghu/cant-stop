//
//  Column.cpp
//  cant-stop
//
//  Created by Vinay  Raghu on 10/17/15.
//  Copyright © 2015 Vinay  Raghu. All rights reserved.
//

#include "Column.hpp"
#include <string>

const int Column::colHeights[] = { 0, 0, 3, 5, 7, 9, 11, 13, 11, 9, 7, 5, 3 };

ostream& Column::print( ostream& out )
{
    cout << "\n" << colNumber << " ";
    cout << state() << "  ";
    for(int k=0;k<colLength;++k) {
        for(int z=0; z<5; z++) {
            if(markerArray[z] == k) {
                out<< colorNames[z][0];
                break;
            }// 51787073
        }
        if (k != colLength) {
            out << "-";
        }
    }
    return out;
}

const char* Column::state() {
    return statusNames[colState];
}

bool Column::startTower(Player *player) {
    if(state() == "AVAILABLE") {
        // Also check if the player's color isn't there already
        markerArray[0] = 0;
        return true;
    }
    else {
        return false;
    }
}

bool Column::move() {
    // Find out where the tower is
    int index = markerArray[0];

    if(index<colLength-2) {
        markerArray[0] = index+1;
        return true;
    }
    else if(index < colLength-1) {
        markerArray[0] = index+1;
        colState = 1; // set state to pending
        return true;
    }
    else {
        cout << "\nCannot perform move\n";
        return false; // Cannot move beyond the last
    }
}

void Column::stop() {
    cout << "\n\nInside stop";
    int index = markerArray[0]; // Find out where the tower is
    int c = player->color();
    cout << "\nColor \n" << player->color();
    // cout << player->color(); // there is some issue here
    // replace tower with appropriate tile
    markerArray[0] = 20; // Remove tower
    markerArray[c] = index; // Put the tile in that position
    cout << "\nSuccess here\n";
    if(index == colLength-1) {
        colState = 2;
        player->wonColumn(colNumber);
    }
}
void Column::bust() {
    markerArray[0] = 20; // White tower is nowhere in the column
    colState = 0; // set column to available 
}

void Column::wonColumn() {
    colState = 2;
}