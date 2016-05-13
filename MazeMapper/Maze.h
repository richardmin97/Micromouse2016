#ifndef Maze_h
#define Maze_h

#include <string>

#include "BitVector256.h"
#include "MazeDefinitions.h"
#include "Dir.h"
#include "PathFinder.h"

class Maze {
protected:
    BitVector256 wallNS;
    BitVector256 wallEW;
    Dir heading;
    PathFinder *pathFinder;
    unsigned mouseX;
    unsigned mouseY;

    MouseMovement nextMovement;

    bool isOpen(unsigned x, unsigned y, Dir d) const;
    void setOpen(unsigned x, unsigned y, Dir d);

    void moveForward();
    void moveBackward();

    inline void turnClockwise() {
        heading = clockwise(heading);
    }

    inline void turnCounterClockwise() {
        heading = counterClockwise(heading);
    }

    inline void turnAround() {
        heading = opposite(heading);
    }

public:
    Maze(MazeDefinitions::MazeEncodingName name, PathFinder *pathFinder);

    inline bool wallInFront() const {
        return !isOpen(mouseX, mouseY, heading);
    }

    inline bool wallOnLeft() const {
        return !isOpen(mouseX, mouseY, counterClockwise(heading));
    }

    inline bool wallOnRight() const {
        return !isOpen(mouseX, mouseY, clockwise(heading));
    }

    /**
     * Start running the mouse through the maze.
     * Terminates when the PathFinder's nextMovement method returns MouseMovement::Finish.
     */
    void start();

};

#endif
